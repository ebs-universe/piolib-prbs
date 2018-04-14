# Copyright (c)
# (c) 2015-16 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
#
# This file is part of serial-test.
#
# serial-test is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# serial-test is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with serial-test.  If not, see <http://www.gnu.org/licenses/>.

"""
Random number generation testing script
"""

from __future__ import print_function
import argparse
import threading
import datetime
import time
import yaml
from collections import OrderedDict
from pymodbus.client.sync import ModbusSerialClient as ModbusClient
from pymodbus import mei_message


words_per_channel = 0
total_words_per_channel = 0
throughput = 0
next_update = None
next_dump = None

MODBUS_ADDRESS = 5

TEST_BASE_ADDRESS = 10

ADDR_ENTROPY_TAP = TEST_BASE_ADDRESS
ADDR_LFSR16_TAP = TEST_BASE_ADDRESS + 1
ADDR_LFSR32_TAP = TEST_BASE_ADDRESS + 2
ADDR_LFSR64_TAP = TEST_BASE_ADDRESS + 3
ADDR_SG16_TAP = TEST_BASE_ADDRESS + 4
ADDR_SG32_TAP = TEST_BASE_ADDRESS + 5
ADDR_SG64_TAP = TEST_BASE_ADDRESS + 6
ADDR_ASG16_TAP = TEST_BASE_ADDRESS + 7
ADDR_ASG32_TAP = TEST_BASE_ADDRESS + 8
ADDR_ASG64_TAP = TEST_BASE_ADDRESS + 9
ADDR_ENTROPIUM_TAP = TEST_BASE_ADDRESS + 10
ADDR_RAND_TAP = TEST_BASE_ADDRESS + 11

SOURCES_LIST = [
    ('entropy', ADDR_ENTROPY_TAP),
    ('lfsr16', ADDR_LFSR16_TAP),
    ('lfsr32', ADDR_LFSR32_TAP),
    ('lfsr64', ADDR_LFSR64_TAP),
    ('sg16', ADDR_SG16_TAP),
    ('sg32', ADDR_SG32_TAP),
    ('sg64', ADDR_SG64_TAP),
    ('asg16', ADDR_ASG16_TAP),
    ('asg32', ADDR_ASG32_TAP),
    ('asg64', ADDR_ASG64_TAP),
    ('entropium', ADDR_ENTROPIUM_TAP),
    ('rand', ADDR_RAND_TAP),
]


def get_sources():
    sources = OrderedDict()
    for s, a in SOURCES_LIST:
        sources[s] = a
    return sources


def dump_status():
    global throughput
    global next_dump
    global total_words_per_channel

    print('{0}:: {1} bits/s/tap :: Total : {2} bits/tap'
          ''.format(datetime.datetime.now(),
                    throughput * 16, total_words_per_channel * 16))


def update_status():
    global words_per_channel
    global total_words_per_channel
    global throughput
    global next_update

    throughput = words_per_channel

    total_words_per_channel += words_per_channel
    words_per_channel = 0

    dump_status()

    next_update += 1
    threading.Timer(next_update - time.time(), update_status).start()


def get_deviceinfo():
    rq = mei_message.ReadDeviceInformationRequest(unit=5, read_code=0x03)
    rr = mclient.execute(rq)
    return {
        'vendor_name': rr.information[0],
        'vendor_url': rr.information[3],
        'hardware_name': rr.information[4],
        'hardware_variant': rr.information[5],
        'hardware_revision': rr.information[1],
        'firmware_name': rr.information[6],
        'firmware_revision': rr.information[2],
        'serial_no': ''.join(['{:02x}'.format(ord(b)) for b in rr.information[0x80]]),
    }


def generate_runinfo(rtime, filenames):
    fileinfo = {k: f for k, f in filenames}
    runinfo = {
        'runtype': "Random Bit Streams",
        'rundate': rtime,
        'device': get_deviceinfo(),
        'datafiles': fileinfo,
        'runlength': 0,
    }
    with open('data/runinfo-{0}.yaml'.format(rtime), 'w') as f:
        yaml.dump(runinfo, f)


def finalize_runinfo(rtime):
    with open('data/runinfo-{0}.yaml'.format(rtime)) as f:
        runinfo = yaml.load(f)
    runinfo['runlength'] = total_words_per_channel * 16
    with open('data/runinfo-{0}.yaml'.format(rtime), 'w') as f:
        yaml.dump(runinfo, f)


def acquire(source_addr):
    global words_per_channel
    global next_update
    next_update = time.time()
    update_status()
    sources = get_sources()
    if source_addr in sources.keys():
        addr = sources[args.source]
    elif source_addr == 'all':
        addr = None
    else:
        raise NotImplementedError("{0} source is not recognized"
                                  "".format(args.source))
    rtime = int(time.time())
    if not addr:
        filenames = [(key, '{0}_{1}.dat'.format(key, rtime))
                     for key in sources.keys()]
    else:
        filenames = [(source_addr, '{0}_{1}.dat'.format(source_addr, rtime))]
    files = [(sources[s], open('data/{0}'.format(f), 'wb'))
             for s, f in filenames]
    generate_runinfo(rtime, filenames)
    try:
        while True:
            response = mclient.read_holding_registers(files[0][0], len(files),
                                                      unit=MODBUS_ADDRESS)
            words_per_channel += 1
            rval = response.registers
            for i in range(len(files)):
                files[i][1].write(str(bin(rval[i]))[2:])
    finally:
        finalize_runinfo(rtime)
        for s, f in files:
            f.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--port', default='/dev/ttyACM1',
                        help="Serial Port",)
    parser.add_argument('-b', '--baudrate', default=256000, type=int,
                        help="Baud Rate. Not applicable to USB CDC links")
    parser.add_argument('source', choices=['entropy', 'all',
                                           'lfsr16', 'lfsr32', 'lfsr64',
                                           'sg16', 'sg32', 'sg64',
                                           'asg16', 'asg32', 'asg64',
                                           'entropium', 'rand'],
                        default='entropy', help='Data stream to use')
    args = parser.parse_args()
    mclient = ModbusClient(method='rtu', port=args.port, timeout=0.1,
                           baudrate=args.baudrate)
    mclient.connect()
    try:
        acquire(args.source)
    finally:
        mclient.close()
