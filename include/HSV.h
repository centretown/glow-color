// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "Color.h"
#include "ColorHSV.h"

namespace color
{
    color_pack ToRGB(color_hsv_pack HSV);
    inline uint16_t mapHue(uint16_t hue);
    color_pack mapHueToColor(uint16_t mapped_hue);
    inline color_pack redToGreen(uint16_t mapped_hue);
    inline color_pack greenToBlue(uint16_t mapped_hue);
    inline color_pack blueToRed(uint16_t mapped_hue);
    color_pack applySaturationValue(color_pack pack, ColorHSV& hsv);
    inline uint8_t apply(uint8_t color,
                         uint16_t saturation_multiplier,
                         uint16_t value_multiplier,
                         uint8_t saturation_added);
} // namespace color
