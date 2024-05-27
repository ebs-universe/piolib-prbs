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

#include "lfsr.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name Alternating Step Generator Typedefs
 * 
 * These types contain the core of Alternating Step Generators. Each is 
 * composed of three LFSRs of appropriate sizes. 
 * 
 * Values in the struct should not be used directly. The functions listed in 
 * the interface can be used to operate on the ASG. 
 */
/**@{*/ 

/**
 * @brief 16 bit LFSR based Alternating Step Generator
 */
typedef struct ASG_LFSR16_t{
    lfsr16_t a;     /**< @brief LFSR16 A */
    lfsr16_t b;     /**< @brief LFSR16 B */
    lfsr16_t c;     /**< @brief LFSR16 C */
} asg_lfsr16_t;

/**
 * @brief 32 bit LFSR based Alternating Step Generator
 */
typedef struct ASG_LFSR32_t{
    lfsr32_t a;     /**< @brief LFSR16 A */
    lfsr32_t b;     /**< @brief LFSR16 B */
    lfsr32_t c;     /**< @brief LFSR16 C */
} asg_lfsr32_t;

/**
 * @brief 64 bit LFSR based Alternating Step Generator
 */
typedef struct ASG_LFSR64_t{
    lfsr64_t a;     /**< @brief LFSR16 A */
    lfsr64_t b;     /**< @brief LFSR16 B */
    lfsr64_t c;     /**< @brief LFSR16 C */
} asg_lfsr64_t;
/**@}*/ 


/**
 * @name Alternating Step Generator Initialization Functions
 * 
 * Intialize the alternating step generator's LFSRs with the default seed. 
 * These functions are superceded by the AddEntropy functions, and is retained 
 * here for backwards compatibility.
 * 
 * Applications should avoid using these.
 */
/**@{*/ 

/**
  * @brief Initialize a ::asg_lfsr16_t structure using the default seeds
  * 
  * @param asg Pointer to the ::asg_lfsr16_t structure to be initialized.
  */
void asg_lfsr16_vInit(asg_lfsr16_t * asg);

/**
  * @brief Initialize a ::asg_lfsr32_t structure using the default seeds
  * 
  * @param asg Pointer to the ::asg_lfsr32_t structure to be initialized.
  */
void asg_lfsr32_vInit(asg_lfsr32_t * asg);

/**
  * @brief Initialize a ::asg_lfsr64_t structure using the default seeds
  * 
  * @param asg Pointer to the ::asg_lfsr64_t structure to be initialized.
  */
void asg_lfsr64_vInit(asg_lfsr64_t * asg);
/**@}*/ 


/**
 * @name Alternating Step Generator Add Entropy Functions
 * 
 * Add entropy to the alternating step gnerator. These functions simply 
 * replace the contained LFSRs with the provided entropy bytes. With the 
 * deprecation of the ASG Initialization functions, applications must call 
 * this function and provide some entropy before the SG is usable. 
 * 
 * If randomness is required, entropy should come from a random source.
 * If determinism is required, the default seed or another predetermined 
 * constant may be used. 
 */
/**@{*/ 

/**
 * @brief Add entropy to a ::asg_lfsr16_t structure. 
 * 
 * @param asg Pointer to the ::asg_lfsr16_t structure.
 * @param entropy buffer containing the atleast 6 bytes of entropy
 */
void asg_lfsr16_vAddEntropy(asg_lfsr16_t * asg, void * entropy);

/**
 * @brief Add entropy to a ::asg_lfsr32_t structure. 
 * 
 * @param asg Pointer to the ::asg_lfsr32_t structure.
 * @param entropy buffer containing the atleast 12 bytes of entropy
 */
void asg_lfsr32_vAddEntropy(asg_lfsr32_t * asg, void * entropy);

/**
 * @brief Add entropy to a ::asg_lfsr64_t structure. 
 * 
 * @param asg Pointer to the ::asg_lfsr64_t structure.
 * @param entropy buffer containing the atleast 24 bytes of entropy
 */
void asg_lfsr64_vAddEntropy(asg_lfsr64_t * asg, void * entropy);
/**@}*/ 


/**
 * @name Alternating Step Generator Get Next Byte Functions
 * 
 * Get the next byte in the Alternating Step Generator's pseudo random 
 * binary sequence. This function constructs the byte by repeatedly calling 
 * the bit generation functions. 
 * 
 */
/**@{*/ 

/**
  * @brief Get the next byte in the ASG16 pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr16_t structure.
  * @return The next byte in the sequence.
  */
uint8_t asg_lfsr16_cGetNextByte(asg_lfsr16_t * asg);

/**
  * @brief Get the next byte in the ASG32 pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr32_t structure.
  * @return The next byte in the sequence.
  */
uint8_t asg_lfsr32_cGetNextByte(asg_lfsr32_t * asg);

/**
  * @brief Get the next byte in the ASG64 pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr64_t structure.
  * @return The next byte in the sequence.
  */
uint8_t asg_lfsr64_cGetNextByte(asg_lfsr64_t * asg);
/**@}*/ 


/**
 * @name Alternating Step Generator Get Next Bit Functions
 * 
 * Get the next bit in the Alternating Step Generator's pseudo random 
 * binary sequence. This is the functional core of the ASG implementation.
 */
/**@{*/ 

/**
  * @brief Get the next bit in the ASG16 pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr16_t structure.
  * @return The next bit in the sequence.
  */
int asg_lfsr16_bGetNextBit(asg_lfsr16_t * asg);

/**
  * @brief Get the next bit in the ASG32 pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr32_t structure.
  * @return The next bit in the sequence.
  */
int asg_lfsr32_bGetNextBit(asg_lfsr32_t * asg);

/**
  * @brief Get the next bit in the ASG64 pseudo random binary sequence.
  * 
  * @param asg Pointer to the ::asg_lfsr64_t structure.
  * @return The next bit in the sequence.
  */
int asg_lfsr64_bGetNextBit(asg_lfsr64_t * asg);
/**@}*/ 

#ifdef __cplusplus
}
#endif

#endif
