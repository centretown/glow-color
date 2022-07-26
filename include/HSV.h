// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "Color.h"
#include "Wheel.h"

namespace color
{
    color_pack ToRGB(color_hsv_pack HSV);

    inline uint8_t apply(uint8_t color,
                         uint16_t saturation_multiplier,
                         uint16_t value_multiplier,
                         uint8_t saturation_added);
} // namespace color
