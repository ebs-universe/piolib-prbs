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
 * @file lfsr.c
 * @brief Implementation of the lfsr prbs generator
 * 
 * See lfsr.h for usage documentation. Implementation 
 * documentation should be added to this file as some point. 
 * 
 * @see lfsr.h
 */

#include "lfsr.h"


void lfsr16_vInit(lfsr16_t * lfsrp, uint16_t seed, uint16_t taps){
    lfsrp->_lfsr = seed;
    lfsrp->_taps = taps;
}

void lfsr32_vInit(lfsr32_t * lfsrp, uint32_t seed, uint32_t taps){
    lfsrp->_lfsr = seed;
    lfsrp->_taps = taps;
}

void lfsr64_vInit(lfsr64_t * lfsrp, uint64_t seed, uint64_t taps){
    lfsrp->_lfsr = seed;
    lfsrp->_taps = taps;
}


void lfsr16_vAddEntropy(lfsr16_t * lfsrp, uint8_t * entropy){
    lfsrp->_lfsr = entropy[0] << 8 | entropy[1];
}

void lfsr32_vAddEntropy(lfsr32_t * lfsrp, uint8_t * entropy){
    lfsrp->_lfsr = (uint32_t)entropy[0] << 24 | (uint32_t)entropy[1] << 16 | 
                   (uint32_t)entropy[2] << 8  | (uint32_t)entropy[3];
}

void lfsr64_vAddEntropy(lfsr64_t * lfsrp, uint8_t * entropy){
    lfsrp->_lfsr = (uint64_t)entropy[0] << 56 | (uint64_t)entropy[1] << 48 | 
                   (uint64_t)entropy[2] << 40 | (uint64_t)entropy[3] << 32 |
                   (uint64_t)entropy[4] << 24 | (uint64_t)entropy[5] << 16 | 
                   (uint64_t)entropy[6] << 8  | (uint64_t)entropy[7];
}


uint8_t lfsr16_cGetNextByte(lfsr16_t *lfsrp){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = lfsr16_bGetNextBit(lfsrp);
        byte |= bit<<i;
    }
    return byte;
}

uint8_t lfsr32_cGetNextByte(lfsr32_t *lfsrp){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = lfsr32_bGetNextBit(lfsrp);
        byte |= bit<<i;
    }
    return byte;
}

uint8_t lfsr64_cGetNextByte(lfsr64_t *lfsrp){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = lfsr64_bGetNextBit(lfsrp);
        byte |= bit<<i;
    }
    return byte;
}


int lfsr16_bGetNextBit(lfsr16_t * lfsrp){
    int lsb = lfsrp->_lfsr & 1;
    (lfsrp->_lfsr) >>= 1;                   /* Shift register */
    if (lsb == 1)                           /* Only apply toggle mask if output bit is 1*/
        (lfsrp->_lfsr) ^= (lfsrp->_taps);   /* Apply toggle mask, value has 1 at bits 
                                               corresponding to taps, 0 elsewhere. */
    return lsb;
}

int lfsr32_bGetNextBit(lfsr32_t * lfsrp){
    int lsb = lfsrp->_lfsr & 1;
    (lfsrp->_lfsr) >>= 1;                   /* Shift register */
    if (lsb == 1)                           /* Only apply toggle mask if output bit is 1*/
        (lfsrp->_lfsr) ^= (lfsrp->_taps);   /* Apply toggle mask, value has 1 at bits 
                                               corresponding to taps, 0 elsewhere. */
        return lsb;
}

int lfsr64_bGetNextBit(lfsr64_t * lfsrp){
    int lsb = lfsrp->_lfsr & 1;
    (lfsrp->_lfsr) >>= 1;                   /* Shift register */
    if (lsb == 1)                           /* Only apply toggle mask if output bit is 1*/
        (lfsrp->_lfsr) ^= (lfsrp->_taps);   /* Apply toggle mask, value has 1 at bits 
                                               corresponding to taps, 0 elsewhere. */
        return lsb;
}
