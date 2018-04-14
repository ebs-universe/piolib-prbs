

#include "test_random.h"
#include "bsp/hal/uc.h"
#include <stdlib.h>

static unsigned int buffer[ENTROPY_POOL_LENGTH];
static lfsr16_t lfsr16;
static lfsr32_t lfsr32;
static lfsr64_t lfsr64;
static sg_lfsr16_t sg16;
static sg_lfsr32_t sg32;
static sg_lfsr64_t sg64;
static asg_lfsr16_t asg16;
static asg_lfsr32_t asg32;
static asg_lfsr64_t asg64;


uint16_t entropy_tap(uint16_t __attribute__((unused))addr){
    return(entropy_get_byte() << 8 | entropy_get_byte());
}

uint16_t lfsr16_tap(uint16_t __attribute__((unused))addr){
    return(lfsr16_cGetNextByte(&lfsr16) << 8 | lfsr16_cGetNextByte(&lfsr16));
}

uint16_t lfsr32_tap(uint16_t __attribute__((unused))addr){
    return(lfsr32_cGetNextByte(&lfsr32) << 8 | lfsr32_cGetNextByte(&lfsr32));
}

uint16_t lfsr64_tap(uint16_t __attribute__((unused))addr){
    return(lfsr64_cGetNextByte(&lfsr64) << 8 | lfsr64_cGetNextByte(&lfsr64));
}

uint16_t sg16_tap(uint16_t __attribute__((unused))addr){
    return(sg_lfsr16_cGetNextByte(&sg16) << 8 | sg_lfsr16_cGetNextByte(&sg16));
}

uint16_t sg32_tap(uint16_t __attribute__((unused))addr){
    return(sg_lfsr32_cGetNextByte(&sg32) << 8 | sg_lfsr32_cGetNextByte(&sg32));
}

uint16_t sg64_tap(uint16_t __attribute__((unused))addr){
    return(sg_lfsr64_cGetNextByte(&sg64) << 8 | sg_lfsr64_cGetNextByte(&sg64));
}

uint16_t asg16_tap(uint16_t __attribute__((unused))addr){
    return(asg_lfsr16_cGetNextByte(&asg16) << 8 | asg_lfsr16_cGetNextByte(&asg16));    
}

uint16_t asg32_tap(uint16_t __attribute__((unused))addr){
    return(asg_lfsr32_cGetNextByte(&asg32) << 8 | asg_lfsr32_cGetNextByte(&asg32));    
}

uint16_t asg64_tap(uint16_t __attribute__((unused))addr){
    return(asg_lfsr64_cGetNextByte(&asg64) << 8 | asg_lfsr64_cGetNextByte(&asg64));
}

uint16_t entropium_tap(uint16_t __attribute__((unused))addr){
    return(entropium_getRandomByte() << 8 | entropium_getRandomByte());
}

uint16_t rand_tap(uint16_t __attribute__((unused))addr){
    return(rand());
}

void random_test_init(void){
    uint8_t i;
    entropy_init();

    for (i=0; i<ENTROPY_POOL_LENGTH; i++){
        buffer[i] = entropy_get_byte() << 8 | entropy_get_byte();
    }
    
    lfsr16_vAddEntropy(&lfsr16, (void *)buffer);
    lfsr32_vAddEntropy(&lfsr32, (void *)buffer);
    lfsr64_vAddEntropy(&lfsr64, (void *)buffer);
    sg_lfsr16_vAddEntropy(&sg16, (void *)buffer);
    sg_lfsr32_vAddEntropy(&sg32, (void *)buffer);
    sg_lfsr64_vAddEntropy(&sg64, (void *)buffer);
    asg_lfsr16_vAddEntropy(&asg16, (void *)buffer);
    asg_lfsr32_vAddEntropy(&asg32, (void *)buffer);
    asg_lfsr64_vAddEntropy(&asg64, (void *)buffer);
    entropium_addEntropy(ENTROPY_POOL_LENGTH * 16, (void *)buffer);
    srand(buffer[0]);
    
    ucdm_redirect_regr_func(ADDR_ENTROPY_TAP,   &entropy_tap);
    ucdm_redirect_regr_func(ADDR_LFSR16_TAP,    &lfsr16_tap);
    ucdm_redirect_regr_func(ADDR_LFSR32_TAP,    &lfsr32_tap);
    ucdm_redirect_regr_func(ADDR_LFSR64_TAP,    &lfsr64_tap);
    ucdm_redirect_regr_func(ADDR_SG16_TAP,      &sg16_tap);
    ucdm_redirect_regr_func(ADDR_SG32_TAP,      &sg32_tap);
    ucdm_redirect_regr_func(ADDR_SG64_TAP,      &sg64_tap);
    ucdm_redirect_regr_func(ADDR_ASG16_TAP,     &asg16_tap);
    ucdm_redirect_regr_func(ADDR_ASG32_TAP,     &asg32_tap);
    ucdm_redirect_regr_func(ADDR_ASG64_TAP,     &asg64_tap);
    ucdm_redirect_regr_func(ADDR_ENTROPIUM_TAP, &entropium_tap);
    ucdm_redirect_regr_func(ADDR_RAND_TAP,      &rand_tap);
}
