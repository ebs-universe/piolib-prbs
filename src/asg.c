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

#include "asg.h"

void asg_lfsr16_vInit(asg_lfsr16_t * asg, 
                     uint16_t seed_a, uint16_t taps_a, 
                     uint16_t seed_b, uint16_t taps_b,
                     uint16_t seed_c, uint16_t taps_c)
{
    lfsr16_vInit(&(asg->a), seed_a, taps_a);
    lfsr16_vInit(&(asg->b), seed_b, taps_b);
    lfsr16_vInit(&(asg->c), seed_c, taps_c);
}

void asg_lfsr32_vInit(asg_lfsr32_t * asg, 
                      uint32_t seed_a, uint32_t taps_a, 
                      uint32_t seed_b, uint32_t taps_b,
                      uint32_t seed_c, uint32_t taps_c)
{
    lfsr32_vInit(&(asg->a), seed_a, taps_a);
    lfsr32_vInit(&(asg->b), seed_b, taps_b);
    lfsr32_vInit(&(asg->c), seed_c, taps_c);
}

void asg_lfsr64_vInit(asg_lfsr64_t * asg, 
                      uint64_t seed_a, uint64_t taps_a, 
                      uint64_t seed_b, uint64_t taps_b,
                      uint64_t seed_c, uint64_t taps_c)
{
    lfsr64_vInit(&(asg->a), seed_a, taps_a);
    lfsr64_vInit(&(asg->b), seed_b, taps_b);
    lfsr64_vInit(&(asg->c), seed_c, taps_c);
}


void asg_lfsr16_vAddEntropy(asg_lfsr16_t * asg, uint8_t * entropy){
    lfsr16_vAddEntropy(&(asg->a), &entropy[0]);
    lfsr16_vAddEntropy(&(asg->b), &entropy[2]);
    lfsr16_vAddEntropy(&(asg->c), &entropy[4]);
}

void asg_lfsr32_vAddEntropy(asg_lfsr32_t * asg, uint8_t * entropy){
    lfsr32_vAddEntropy(&(asg->a), &entropy[0]);
    lfsr32_vAddEntropy(&(asg->b), &entropy[4]);
    lfsr32_vAddEntropy(&(asg->c), &entropy[8]);
}

void asg_lfsr64_vAddEntropy(asg_lfsr64_t * asg, uint8_t * entropy){
    lfsr64_vAddEntropy(&(asg->a), &entropy[0]);
    lfsr64_vAddEntropy(&(asg->b), &entropy[8]);
    lfsr64_vAddEntropy(&(asg->c), &entropy[16]);
}


uint8_t asg_lfsr16_cGetNextByte(asg_lfsr16_t * asg){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = asg_lfsr16_bGetNextBit(asg);
        byte |= bit<<i;
    }
    return byte;
}

uint8_t asg_lfsr32_cGetNextByte(asg_lfsr32_t * asg){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = asg_lfsr32_bGetNextBit(asg);
        byte |= bit<<i;
    }
    return byte;
}

uint8_t asg_lfsr64_cGetNextByte(asg_lfsr64_t * asg){
    int i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = asg_lfsr64_bGetNextBit(asg);
        byte |= bit<<i;
    }
    return byte;
}


int asg_lfsr16_bGetNextBit(asg_lfsr16_t * asg){
    int c; 
    c = lfsr16_bGetNextBit(&(asg->c));
    if (c){
        return lfsr16_bGetNextBit(&(asg->b));
    }
    else{
        return lfsr16_bGetNextBit(&(asg->a));
    }
}

int asg_lfsr32_bGetNextBit(asg_lfsr32_t * asg){
    int c; 
    c = lfsr32_bGetNextBit(&(asg->c));
    if (c){
        return lfsr32_bGetNextBit(&(asg->b));
    }
    else{
        return lfsr32_bGetNextBit(&(asg->a));
    }
}

int asg_lfsr64_bGetNextBit(asg_lfsr64_t * asg){
    int c; 
    c = lfsr64_bGetNextBit(&(asg->c));
    if (c){
        return lfsr64_bGetNextBit(&(asg->b));
    }
    else{
        return lfsr64_bGetNextBit(&(asg->a));
    }
}
