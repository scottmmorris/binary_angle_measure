#include "bam.h"
#include <stdio.h>
#include <math.h>

double bam_lookup[16] = {180.0, 90.0, 45.0, 22.5, 11.25, 5.625, 2.8125, 1.40625, 0.703125, 0.3515625, 0.17578125, 0.087890625, 0.0439453125, 0.02197265625, 0.01098632813, 0.00549316406};

uint16_t ConvertToBAM(const double angle) {
    double num = angle;
    uint16_t res = 0;
    
    if(num == 360.0) return 0.0;

    for(int i = 15; i >=0; --i) {
        if(num >= bam_lookup[15 - i]) {
            num -= bam_lookup[15 - i];
            res += pow(2, i);
        }
    }
    return res;
}

double ConvertFromBAM(const uint16_t angle) {
    uint16_t tmp = angle;
    double res = 0;
    for (uint8_t i = 0; i < 16; i++) {
        res += bam_lookup[i] * ((tmp & 0x8000) >> 15);
        tmp <<= 1;
    }
    return res;
}