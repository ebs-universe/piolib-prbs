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
 * @file asg.h
 * @brief Interface and usage of the alternating step prbs generator.
 *
 * This file provides a Alternating Step Generator based on the Linear 
 * Feedback Shift Register generator for generating psuedo random bit 
 * sequences. 
 * 
 * While this is not cryptographically secure either, it is probably good 
 * enough for relatively non-critical random number generation. It
 * produces a reasonably good pseduo-random bit stream at a considerably 
 * lower cost than other 'better' bit stream generation alogrithms.
 * 
 * @see asg.c
 */

#ifndef PRBS_ASG_H
#define PRBS_ASG_H

#include<stdint.h>
#include "lfsr.h"

/**
 * @brief 16 bit LFSR based Alternating Step Generator struct typedef
 * 
 * The core of ASG PRBS implementation is made of this struct, which represents
 * a LFSR16 based alternating step generator. Values in the struct should not 
 * be used directly. The functions listed in the interface can be used to operate
 * on the ASG. 
 */
typedef struct ASG_LFSR16_t{
    lfsr16_t a;     /**< @brief LFSR16 A */
    lfsr16_t b;     /**< @brief LFSR16 B */
    lfsr16_t c;     /**< @brief LFSR16 C */
} asg_lfsr16_t;

typedef struct ASG_LFSR32_t{
    lfsr32_t a;     /**< @brief LFSR16 A */
    lfsr32_t b;     /**< @brief LFSR16 B */
    lfsr32_t c;     /**< @brief LFSR16 C */
} asg_lfsr32_t;

typedef struct ASG_LFSR64_t{
    lfsr64_t a;     /**< @brief LFSR16 A */
    lfsr64_t b;     /**< @brief LFSR16 B */
    lfsr64_t c;     /**< @brief LFSR16 C */
} asg_lfsr64_t;


/**
  * Initialize an ::asg_lfsr16_t structure using the default seeds and 
  * polynomials (taps). Entropy may be added after using the AddEntropy
  * function
  * 
  * @param asg Pointer to the ::asg_lfsr16_t structure to be initialized.
  */
void asg_lfsr16_vInit(asg_lfsr16_t * asg);

void asg_lfsr32_vInit(asg_lfsr32_t * asg);

void asg_lfsr64_vInit(asg_lfsr64_t * asg);


/**
 * Add entropy to an ::asg_lfsr16_t structure. This function simply replaces 
 * the seeds with the provided entropy.
 * 
 * @param asg Pointer to the ::asg_lfsr16_t structure.
 * @param entropy Pointer to a buffer containing the atleast 6 bytes of 
 *                 entropy, preferably from a random source, 
 */
void asg_lfsr16_vAddEntropy(asg_lfsr16_t * asg, void * entropy);

void asg_lfsr32_vAddEntropy(asg_lfsr32_t * asg, void * entropy);

void asg_lfsr64_vAddEntropy(asg_lfsr64_t * asg, void * entropy);


/**
  * Get the next byte in the pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr16_t structure.
  * @return The next byte in the sequence.
  */
uint8_t asg_lfsr16_cGetNextByte(asg_lfsr16_t * asg);

uint8_t asg_lfsr32_cGetNextByte(asg_lfsr32_t * asg);

uint8_t asg_lfsr64_cGetNextByte(asg_lfsr64_t * asg);


/**
  * Get the next bit in the pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr16_t structure.
  * @return The next bit in the sequence.
  */
int asg_lfsr16_bGetNextBit(asg_lfsr16_t * asg);

int asg_lfsr32_bGetNextBit(asg_lfsr32_t * asg);

int asg_lfsr64_bGetNextBit(asg_lfsr64_t * asg);

#endif
