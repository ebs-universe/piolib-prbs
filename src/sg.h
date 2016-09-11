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
 * @file sg.h
 * @brief Interface and usage of the shrinking prbs generator.
 *
 * This file provides a Shrinking Generator based on the Linear Feedback 
 * Shift Register generator for generating psuedo random bit sequences. 
 * 
 * @see sg.c
 */

#ifndef PRBS_SG_H
#define PRBS_SG_H

#include<stdint.h>
#include "lfsr.h"

/**
 * @brief 16 bit LFSR based Shrinking Generator struct typedef
 * 
 * The core of SG PRBS implementation is made of this struct, which represents
 * a LFSR16 based shrinking generator. Values in the struct should not be used 
 * directly. The functions listed in the interface can be used to operate on 
 * the SG. 
 */
typedef struct SG_LFSR16_t{
    lfsr16_t a;     /**< @brief LFSR16 A */
    lfsr16_t b;     /**< @brief LFSR16 B */
} sg_lfsr16_t;

typedef struct SG_LFSR32_t{
    lfsr32_t a;     /**< @brief LFSR16 A */
    lfsr32_t b;     /**< @brief LFSR16 B */
} sg_lfsr32_t;

typedef struct SG_LFSR64_t{
    lfsr64_t a;     /**< @brief LFSR16 A */
    lfsr64_t b;     /**< @brief LFSR16 B */
} sg_lfsr64_t;


/**
  * Initialize a ::sg_lfsr16_t structure using the specified seeds and 
  * polynomials (taps).
  * 
  * @param *sg Pointer to the ::sg_lfsr16_t structure to be initialized.
  * @param seed_a Seed value for the A shift register.
  * @param taps_a Taps for the A shift register.
  * @param seed_b Seed value for the B shift register.
  * @param taps_b Taps for the B shift register.
  */
void sg_lfsr16_vInit(sg_lfsr16_t * sg, 
                     uint16_t seed_a, uint16_t taps_a, 
                     uint16_t seed_b, uint16_t taps_b);

void sg_lfsr32_vInit(sg_lfsr32_t * sg, 
                     uint32_t seed_a, uint32_t taps_a, 
                     uint32_t seed_b, uint32_t taps_b);

void sg_lfsr64_vInit(sg_lfsr64_t * sg, 
                     uint64_t seed_a, uint64_t taps_a, 
                     uint64_t seed_b, uint64_t taps_b);


/**
 * Add entropy to a ::sg_lfsr16_t structure. This function simply replaces 
 * the seeds with the provided entropy.
 * 
 * @param *sg Pointer to the ::sg_lfsr16_t structure.
 * @param *entropy Pointer to a buffer containing the atleast 4 bytes of 
 *                 entropy, preferably from a random source, 
 */
void sg_lfsr16_vAddEntropy(sg_lfsr16_t * sg, uint8_t * entropy);

void sg_lfsr32_vAddEntropy(sg_lfsr32_t * sg, uint8_t * entropy);

void sg_lfsr64_vAddEntropy(sg_lfsr64_t * sg, uint8_t * entropy);


/**
  * Get the next byte in the pseudo random binary sequence.
  * 
  * @param *sg Pointer to the ::sg_lfsr16_t structure.
  * @return The next byte in the sequence.
  */
uint8_t sg_lfsr16_cGetNextByte(sg_lfsr16_t * sg);

uint8_t sg_lfsr32_cGetNextByte(sg_lfsr32_t * sg);

uint8_t sg_lfsr64_cGetNextByte(sg_lfsr64_t * sg);


/**
  * Get the next bit in the pseudo random binary sequence.
  * 
  * @param *sg Pointer to the ::sg_lfsr16_t structure.
  * @return The next bit in the sequence.
  */
int sg_lfsr16_bGetNextBit(sg_lfsr16_t * sg);

int sg_lfsr32_bGetNextBit(sg_lfsr32_t * sg);

int sg_lfsr64_bGetNextBit(sg_lfsr64_t * sg);

#endif
