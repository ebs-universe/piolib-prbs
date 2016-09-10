/* 
   Copyright (c)
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
   This file is part of
   Embedded bootstraps : prbs library
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

/**
 * @file prbs.h
 * @brief Interface and usage of prbs generators.
 *
 * This library provides generators for psuedo random bit sequences. 
 * 
 * The following generators are currently implemented :
 * 
 *  - Linear Feedback Shift Register (16 bit)
 * 
 *    A 16 bit Galois LFSR implementation, intended for BER and protocol 
 *    tests. Is not cryptographically secure. 
 * 
 *    @see lfsr.h
 * 
 *  - Shrinking Generator
 * 
 *    A shrinking generator composed of two 16 bit Galois LFSRs. This is 
 *    not cryptographically secure either, but is probably good enough for 
 *    relatively non-critical random number generation. This generator
 *    produces a reasonably good pseduo-random bit stream at a considerably 
 *    lower cost than other 'better' bit stream generation alogrithms.
 * 
 *    @see sg.h
 * 
 * Note that for all provided PRBS implementations, using default seeds and
 * polynomilals provides a deterministic PRBS. In cases where random numbers 
 * are required (as opposed to a predetermined pseudo random bitstream), the 
 * generators must be provided with true entropy.
 * 
 * One additional pseudo-random bitstream generation algorithm is available 
 * elsewhere in the EBS universe - the entropium PRNG, from AVR Crypto Lib
 * and provided from the EBS cryptolib library. Entropium uses a 512 byte 
 * core and SHA256 and XOR to generate the bytestream. Cryptographic 
 * properties of entropium don't seem to available. However, entropium is 
 * significantly more expensive in all respects. 
 * 
 */

#ifndef PRBS_H
#define PRBS_H

#include "lfsr.h"
#include "sg.h"

#endif