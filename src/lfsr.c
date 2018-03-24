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


void lfsr16_vInit(lfsr16_t * lfsrp){
    *lfsrp = LFSR16_SEED;
}

void lfsr32_vInit(lfsr32_t * lfsrp){
    *lfsrp = LFSR32_SEED;
}

void lfsr64_vInit(lfsr64_t * lfsrp){
    *lfsrp = LFSR64_SEED;
}


void lfsr16_vAddEntropy(lfsr16_t * lfsrp, void * entropy){
    *lfsrp = *(uint16_t*)entropy;
}

void lfsr32_vAddEntropy(lfsr32_t * lfsrp, void * entropy){
    *lfsrp = *(uint32_t*)entropy;
}

void lfsr64_vAddEntropy(lfsr64_t * lfsrp, void * entropy){
    *lfsrp = *(uint64_t*)entropy;
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
    int lsb = *lfsrp & 1;
    *lfsrp >>= 1;                   /* Shift register */
    if (lsb == 1){                  /* Only apply toggle mask if output bit is 1*/
        *lfsrp ^= LFSR16_TAPS;      /* Apply toggle mask, value has 1 at bits corresponding to taps, 0 elsewhere. */
    }
    return lsb;
}

int lfsr32_bGetNextBit(lfsr32_t * lfsrp){
    int lsb = *lfsrp & 1;
    *lfsrp >>= 1;                   
    if (lsb == 1){                          
        *lfsrp ^= LFSR32_TAPS;   
    }
    return lsb;
}

int lfsr64_bGetNextBit(lfsr64_t * lfsrp){
    int lsb = *lfsrp & 1;
    *lfsrp >>= 1;
    if (lsb == 1){
        *lfsrp ^= LFSR64_TAPS;
    }
    return lsb;
}
