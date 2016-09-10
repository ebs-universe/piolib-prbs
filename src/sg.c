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

#include "sg.h"

void sg_lfsr16_vInit(sg_lfsr16_t * sg, 
                     uint16_t seed_a, uint16_t taps_a, 
                     uint16_t seed_b, uint16_t taps_b)
{
    lfsr_vInit(&(sg->a), seed_a, taps_a);
    lfsr_vInit(&(sg->b), seed_b, taps_b);
}

void sg_lfsr16_vAddEntropy(sg_lfsr16_t * sg, uint8_t * entropy){
    lfsr_vAddEntropy(&(sg->a), &entropy[0]);
    lfsr_vAddEntropy(&(sg->b), &entropy[2]);
}

uint8_t sg_lfsr16_cGetNextByte(sg_lfsr16_t * sg){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = sg_lfsr16_bGetNextBit(sg);
        byte |= bit<<i;
    }
    return byte;
}

int sg_lfsr16_bGetNextBit(sg_lfsr16_t * sg){
    int a, b; 
    a = lfsr_bGetNextBit(&(sg->a));
    b = lfsr_bGetNextBit(&(sg->b));
    while(!a){
        a = lfsr_bGetNextBit(&(sg->a));
        b = lfsr_bGetNextBit(&(sg->b));
    }
    return b;
}
