#pragma once

#include <stdint.h>

/**
 *  @brief     Matrix inverse for positive definite matrices
 *  @return    false if matrix not positive definite, true ok
 *  @author    Scott Morris
 *  @date      May 2023
 **/
uint16_t ConvertToBAM(const double angle);

double ConvertFromBAM(const uint16_t angle);