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

#include "lfsr.h"


/**
 * @name Shrinking Generator Typedefs
 * 
 * These types contain the core of Shrinking Generators. Each is composed of 
 * two LFSRs of appropriate sizes. 
 * 
 * Values in the struct should not be used directly. The functions listed in 
 * the interface can be used to operate on the SG. 
 */
/**@{*/ 

/**
 * @brief 16 bit LFSR based Shrinking Generator
 */
typedef struct SG_LFSR16_t{
    lfsr16_t a;     /**< @brief LFSR16 A */
    lfsr16_t b;     /**< @brief LFSR16 B */
} sg_lfsr16_t;

/**
 * @brief 32 bit LFSR based Shrinking Generator
 */
typedef struct SG_LFSR32_t{
    lfsr32_t a;     /**< @brief LFSR32 A */
    lfsr32_t b;     /**< @brief LFSR32 B */
} sg_lfsr32_t;

/**
 * @brief 64 bit LFSR based Shrinking Generator
 */
typedef struct SG_LFSR64_t{
    lfsr64_t a;     /**< @brief LFSR64 A */
    lfsr64_t b;     /**< @brief LFSR64 B */
} sg_lfsr64_t;
/**@}*/ 


/**
 * @name Shrinking Generator Initialization Functions
 * 
 * Intialize the shrinking generator's LFSRs with the default seed. These 
 * functions are superceded by the AddEntropy functions, and is retained 
 * here for backwards compatibility.
 * 
 * Applications should avoid using these.
 */
/**@{*/ 

/**
  * @brief Initialize a ::sg_lfsr16_t structure using the default seeds
  * 
  * @param sg Pointer to the ::sg_lfsr16_t structure to be initialized.
  */
void sg_lfsr16_vInit(sg_lfsr16_t * sg);

/**
  * @brief Initialize a ::sg_lfsr32_t structure using the default seeds
  * 
  * @param sg Pointer to the ::sg_lfsr32_t structure to be initialized.
  */
void sg_lfsr32_vInit(sg_lfsr32_t * sg);

/**
  * @brief Initialize a ::sg_lfsr64_t structure using the default seeds
  * 
  * @param sg Pointer to the ::sg_lfsr64_t structure to be initialized.
  */
void sg_lfsr64_vInit(sg_lfsr64_t * sg);
/**@}*/ 

/**
 * @name Shrinking Generator Add Entropy Functions
 * 
 * Add entropy to the shrinking gnerator. These functions simply replaces 
 * the contained LFSRs with the provided entropy bytes. With the deprecation 
 * of the SG Initialization functions, applications must call this function 
 * and provide some entropy before the SG is usable. 
 * 
 * If randomness is required, entropy should come from a random source.
 * If determinism is required, the default seed or another predetermined 
 * constant may be used. 
 * 
 */
/**@{*/ 

/**
 * @brief Add entropy to a ::sg_lfsr16_t structure. 
 * 
 * @param sg Pointer to the ::sg_lfsr16_t structure.
 * @param entropy buffer containing the atleast 4 bytes of entropy
 */
void sg_lfsr16_vAddEntropy(sg_lfsr16_t * sg, void * entropy);

/**
 * @brief Add entropy to a ::sg_lfsr32_t structure. 
 * 
 * @param sg Pointer to the ::sg_lfsr32_t structure.
 * @param entropy buffer containing the atleast 8 bytes of entropy
 */
void sg_lfsr32_vAddEntropy(sg_lfsr32_t * sg, void * entropy);

/**
 * @brief Add entropy to a ::sg_lfsr64_t structure. 
 * 
 * @param sg Pointer to the ::sg_lfsr64_t structure.
 * @param entropy buffer containing the atleast 8 bytes of entropy
 */
void sg_lfsr64_vAddEntropy(sg_lfsr64_t * sg, void * entropy);
/**@}*/ 


/**
 * @name Shrinking Generator Get Next Byte Functions
 * 
 * Get the next byte in the Shrinking Generator's pseudo random binary 
 * sequence. This function constructs the byte by repeatedly calling 
 * the bit generation functions. 
 * 
 */
/**@{*/ 

/**
  * Get the next byte in the SG16 pseudo random binary sequence.
  * 
  * @param sg Pointer to the ::sg_lfsr16_t structure.
  * @return The next byte in the sequence.
  */
uint8_t sg_lfsr16_cGetNextByte(sg_lfsr16_t * sg);

/**
  * Get the next byte in the SG32 pseudo random binary sequence.
  * 
  * @param sg Pointer to the ::sg_lfsr32_t structure.
  * @return The next byte in the sequence.
  */
uint8_t sg_lfsr32_cGetNextByte(sg_lfsr32_t * sg);

/**
  * Get the next byte in the SG64 pseudo random binary sequence.
  * 
  * @param sg Pointer to the ::sg_lfsr64_t structure.
  * @return The next byte in the sequence.
  */
uint8_t sg_lfsr64_cGetNextByte(sg_lfsr64_t * sg);
/**@}*/ 


/**
 * @name Shrinking Generator Get Next Bit Functions
 * 
 * Get the next bit in the Shrinking Generator's pseudo random binary sequence. 
 * This is the functional core of the SG implementation.
 */
/**@{*/ 

/**
  * @brief Get the next bit in the SG16 pseudo random binary sequence.
  * 
  * @param sg Pointer to the ::sg_lfsr16_t structure.
  * @return The next bit in the sequence.
  */
int sg_lfsr16_bGetNextBit(sg_lfsr16_t * sg);

/**
  * @brief Get the next bit in the SG32 pseudo random binary sequence.
  * 
  * @param sg Pointer to the ::sg_lfsr32_t structure.
  * @return The next bit in the sequence.
  */
int sg_lfsr32_bGetNextBit(sg_lfsr32_t * sg);

/**
  * @brief Get the next bit in the SG64 pseudo random binary sequence.
  * 
  * @param sg Pointer to the ::sg_lfsr64_t structure.
  * @return The next bit in the sequence.
  */
int sg_lfsr64_bGetNextBit(sg_lfsr64_t * sg);
/**@}*/ 

#endif
