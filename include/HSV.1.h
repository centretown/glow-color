// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "Color.h"
#include "ColorHSV.h"

namespace color
{
    color_pack ToRGB_1(color_hsv_pack HSV);
    inline uint16_t mapHue_1(uint16_t hue);
    color_pack mapHueToColor_1(uint16_t mapped_hue);
    inline color_pack redToGreen_1(uint16_t mapped_hue);
    inline color_pack greenToBlue_1(uint16_t mapped_hue);
    inline color_pack blueToRed_1(uint16_t mapped_hue);
    color_pack applySaturationValue_1(color_pack pack, ColorHSV& hsv);
    inline uint8_t apply_1(uint8_t color,
                         uint16_t saturation_multiplier,
                         uint16_t value_multiplier,
                         uint8_t saturation_added);
} // namespace color
