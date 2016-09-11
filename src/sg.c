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

#include "sg.h"

void sg_lfsr16_vInit(sg_lfsr16_t * sg, 
                     uint16_t seed_a, uint16_t taps_a, 
                     uint16_t seed_b, uint16_t taps_b)
{
    lfsr16_vInit(&(sg->a), seed_a, taps_a);
    lfsr16_vInit(&(sg->b), seed_b, taps_b);
}

void sg_lfsr32_vInit(sg_lfsr32_t * sg, 
                     uint32_t seed_a, uint32_t taps_a, 
                     uint32_t seed_b, uint32_t taps_b)
{
    lfsr32_vInit(&(sg->a), seed_a, taps_a);
    lfsr32_vInit(&(sg->b), seed_b, taps_b);
}

void sg_lfsr64_vInit(sg_lfsr64_t * sg, 
                     uint64_t seed_a, uint64_t taps_a, 
                     uint64_t seed_b, uint64_t taps_b)
{
    lfsr64_vInit(&(sg->a), seed_a, taps_a);
    lfsr64_vInit(&(sg->b), seed_b, taps_b);
}


void sg_lfsr16_vAddEntropy(sg_lfsr16_t * sg, uint8_t * entropy){
    lfsr16_vAddEntropy(&(sg->a), &entropy[0]);
    lfsr16_vAddEntropy(&(sg->b), &entropy[2]);
}

void sg_lfsr32_vAddEntropy(sg_lfsr32_t * sg, uint8_t * entropy){
    lfsr32_vAddEntropy(&(sg->a), &entropy[0]);
    lfsr32_vAddEntropy(&(sg->b), &entropy[4]);
}

void sg_lfsr64_vAddEntropy(sg_lfsr64_t * sg, uint8_t * entropy){
    lfsr64_vAddEntropy(&(sg->a), &entropy[0]);
    lfsr64_vAddEntropy(&(sg->b), &entropy[8]);
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

uint8_t sg_lfsr32_cGetNextByte(sg_lfsr32_t * sg){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = sg_lfsr32_bGetNextBit(sg);
        byte |= bit<<i;
    }
    return byte;
}

uint8_t sg_lfsr64_cGetNextByte(sg_lfsr64_t * sg){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = sg_lfsr64_bGetNextBit(sg);
        byte |= bit<<i;
    }
    return byte;
}


int sg_lfsr16_bGetNextBit(sg_lfsr16_t * sg){
    int a, b; 
    a = lfsr16_bGetNextBit(&(sg->a));
    b = lfsr16_bGetNextBit(&(sg->b));
    while(!a){
        a = lfsr16_bGetNextBit(&(sg->a));
        b = lfsr16_bGetNextBit(&(sg->b));
    }
    return b;
}

int sg_lfsr32_bGetNextBit(sg_lfsr32_t * sg){
    int a, b; 
    a = lfsr32_bGetNextBit(&(sg->a));
    b = lfsr32_bGetNextBit(&(sg->b));
    while(!a){
        a = lfsr32_bGetNextBit(&(sg->a));
        b = lfsr32_bGetNextBit(&(sg->b));
    }
    return b;
}

int sg_lfsr64_bGetNextBit(sg_lfsr64_t * sg){
    int a, b; 
    a = lfsr64_bGetNextBit(&(sg->a));
    b = lfsr64_bGetNextBit(&(sg->b));
    while(!a){
        a = lfsr64_bGetNextBit(&(sg->a));
        b = lfsr64_bGetNextBit(&(sg->b));
    }
    return b;
}
