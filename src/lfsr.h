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
 * @file lfsr.h
 * @brief Interface and usage of the lfsr prbs generator.
 *
 * This file provides the Linear Feedback Shift Register generator for 
 * psuedo random bit sequences. It is intended for use in BER and protocol 
 * tests and should not be considered crytptographically secure. 
 * 
 * An alternating step generator or shrinking generator can be constructed 
 * of these LFSRs which have relatively better cryptographic properties. 
 * Implementations of the SG and ASG based on the LFSR presented here are 
 * included in the library and can be found in sg.h and asg.h.
 * 
 * @see prbs.c
 * 
 * This library uses hardcoded polynomials for performace reasons. 
 * Polynomials need to be primitive and cannot be generated from entropy in 
 * any case. Primitive polynomials from Xilinx application note XAPP052 are
 * used by default, this can be changed only by changing the preprocessor 
 * definitions in this file. If multiple LFSRs are instantiated, they will 
 * all use the same polynomials. While non-idea, this is not as bad as it 
 * sounds. Any reasonable polynomial which works with randomly generated 
 * seeds will have exactly the same period anyway. The LFSR's seed can be 
 * set to a different value using the AddEntropy function.
 * 
 * @see <https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf>
 * 
 */

#ifndef PRBS_LFSR_H
#define PRBS_LFSR_H

#include<stdint.h>

#define LFSR16_SEED     0xACE1
#define LFSR16_TAPS     0xD008

#define LFSR32_SEED     0xDEADACE1
#define LFSR32_TAPS     0x80200003

#define LFSR64_SEED     0x12345678DEADACE1
#define LFSR64_TAPS     0xD800000000000000


/**
 * @brief Primary 16 bit LFSR typedef
 * 
 * The core of LFSR16 PRBS implementation is made of a uint16_t, which 
 * represents a 16 bit Linear Feedback Shift Register. The value should
 * not be used directly, the functions listed in the interface can be 
 * used to operate on the LFSR. 
 * 
 * The LFSR implemented is a binary Galois LFSR.
 */
typedef uint16_t lfsr16_t;

typedef uint32_t lfsr32_t;

typedef uint64_t lfsr64_t;

/**
  * Initialize a ::lfsr16_t structure using the default seed and 
  * polynomial (taps).
  * 
  * @param lfsrp Pointer to the ::lfsr16_t to be initialized.
  */
void lfsr16_vInit(lfsr16_t * lfsrp);

void lfsr32_vInit(lfsr32_t * lfsrp);

void lfsr64_vInit(lfsr64_t * lfsrp);

/**
 * Add entropy to a ::lfsr16_t structure. This function simply replaces 
 * the seed with the provided entropy.
 * 
 * @param lfsrp Pointer to the ::lfsr16_t.
 * @param entropy Pointer to a buffer containing the atleast 2 bytes of 
 *                 entropy, preferably from a random source, 
 */
void lfsr16_vAddEntropy(lfsr16_t * lfsrp, void * entropy);

void lfsr32_vAddEntropy(lfsr32_t * lfsrp, void * entropy);

void lfsr64_vAddEntropy(lfsr64_t * lfsrp, void * entropy);

/**
  * Get the next byte in the pseudo random binary sequence.
  * 
  * @param lfsrp Pointer to the ::lfsr16_t.
  * @return The next byte in the sequence.
  */
uint8_t lfsr16_cGetNextByte(lfsr16_t * lfsrp);

uint8_t lfsr32_cGetNextByte(lfsr32_t * lfsrp);

uint8_t lfsr64_cGetNextByte(lfsr64_t * lfsrp);

/**
  * Get the next bit in the pseudo random binary sequence.
  * 
  * @param lfsrp Pointer to the ::lfsr16_t.
  * @return The next bit in the sequence.
  */
int lfsr16_bGetNextBit(lfsr16_t * lfsrp);

int lfsr32_bGetNextBit(lfsr32_t * lfsrp);

int lfsr64_bGetNextBit(lfsr64_t * lfsrp);
#endif
