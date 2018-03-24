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
 *    tests. Is not cryptographically secure. The LFSR has a maximal period
 *    of (2^16 - 1), for the correct choice of polynomials. This period is 
 *    pretty short for most random applications. Increasing the length of the
 *    state variable, and consequently the period, has serious implications 
 *    on performance. 
 * 
 *    @see lfsr.h
 * 
 *  - Shrinking Generator
 * 
 *    A shrinking generator composed of two 16 bit Galois LFSRs. This is 
 *    not cryptographically secure either. Due to the short periods of the
 *    included LFSRs, this generator has minimal applications in the real 
 *    world. It needs _much_ longer LFSRs to be useful.
 *    
 *    @see sg.h
 * 
 *  - Alternating Step Generator
 * 
 *    Composed of three 16 bit Galois LFSRs. This is not cryptographically
 *    secure. This is probably the optimal generator for relatively 
 *    non-critical random number generation. This generator produces a 
 *    reasonably good pseduo-random bit stream at a considerably lower 
 *    cost than other 'better' bit stream generation alogrithms.
 * 
 *    @see asg.h
 * 
 * Note that for all provided PRBS implementations, using default seeds and
 * polynomilals provides a deterministic PRBS. In cases where random numbers 
 * are required (as opposed to a predetermined pseudo random bitstream), the 
 * generators must be provided with true entropy.
 * 
 * One additional pseudo-random bytestream generation algorithm is available 
 * elsewhere in the EBS universe - the entropium PRNG, from AVR Crypto Lib
 * and provided from the EBS cryptolib library. Entropium uses a 512 bit 
 * core and SHA256 and XOR to generate the bytestream. Cryptographic 
 * properties of entropium don't seem to available. However, entropium is 
 * significantly more expensive in all respects. 
 * 
 * The following PRNGs look amusing but are not yet included here : 
 *  - TinyMT : The 32-bit variant of the Mersenne Twister may be able to run
 *             on constrained platforms, but seems still too heavy to 
 *             prioritize implementation
 *  - PCG : The permuted congruential generator, while probably heavier than
 *          LFSRs, may provide the best of multiple worlds. Implementation is
 *          currently deferred pending performance testing on the rand() LCG.
 * 
 * Of course, GCC/glibc's stdlib provides an LCG based rand() function which
 * can be used as well. A serious attempt to provide a stripped down version 
 * is not made. The combination of multiplication, non-2^N modulus, and 
 * constraints on state size seem unlikely to make it worth the effort beyond
 * whatever stdlib provides. 
 * 
 */

#ifndef PRBS_H
#define PRBS_H

#include "lfsr.h"
#include "sg.h"
#include "asg.h"

#endif
