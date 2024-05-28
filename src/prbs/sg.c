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
 * @file sg.c
 * @brief Implementation of the SG prbs generator
 * 
 * See sg.h for usage documentation. Implementation 
 * documentation should be added to this file as some point. 
 *
 */

#include "sg.h"

void sg_lfsr16_vInit(sg_lfsr16_t * sg)
{
    lfsr16_vInit(&(sg->a));
    lfsr16_vInit(&(sg->b));
}

void sg_lfsr32_vInit(sg_lfsr32_t * sg)
{
    lfsr32_vInit(&(sg->a));
    lfsr32_vInit(&(sg->b));
}

void sg_lfsr64_vInit(sg_lfsr64_t * sg)
{
    lfsr64_vInit(&(sg->a));
    lfsr64_vInit(&(sg->b));
}


void sg_lfsr16_vAddEntropy(sg_lfsr16_t * sg, void * entropy){
    lfsr16_vAddEntropy(&(sg->a), (void *)(uint16_t *)entropy);
    lfsr16_vAddEntropy(&(sg->b), (void *)((uint16_t *)entropy + 1));
}

void sg_lfsr32_vAddEntropy(sg_lfsr32_t * sg, void * entropy){
    lfsr32_vAddEntropy(&(sg->a), (void *)(uint32_t *)entropy);
    lfsr32_vAddEntropy(&(sg->b), (void *)((uint32_t *)entropy + 1));
}

void sg_lfsr64_vAddEntropy(sg_lfsr64_t * sg, void * entropy){
    lfsr64_vAddEntropy(&(sg->a), (void *)(uint64_t *)entropy);
    lfsr64_vAddEntropy(&(sg->b), (void *)((uint64_t *)entropy + 1));
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
