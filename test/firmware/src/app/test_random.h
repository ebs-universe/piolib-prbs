

#ifndef TEST_RANDOM_H
#define TEST_RANDOM_H

#include "application.h"
#include <prbs/prbs.h>
#include <crypto/entropium/entropium.h>

#define ENTROPY_POOL_LENGTH     16

uint16_t entropy_tap(uint16_t __attribute__((unused))addr);
uint16_t lfsr16_tap(uint16_t __attribute__((unused))addr);
uint16_t lfsr32_tap(uint16_t __attribute__((unused))addr);
uint16_t lfsr64_tap(uint16_t __attribute__((unused))addr);
uint16_t sg16_tap(uint16_t __attribute__((unused))addr);
uint16_t sg32_tap(uint16_t __attribute__((unused))addr);
uint16_t sg64_tap(uint16_t __attribute__((unused))addr);
uint16_t asg16_tap(uint16_t __attribute__((unused))addr);
uint16_t asg32_tap(uint16_t __attribute__((unused))addr);
uint16_t asg64_tap(uint16_t __attribute__((unused))addr);
uint16_t entropium_tap(uint16_t __attribute__((unused))addr);
uint16_t rand_tap(uint16_t __attribute__((unused))addr);
void random_test_init(void);                        

#endif
