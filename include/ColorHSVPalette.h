// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorHSV.h"
#include "Palette.h"

namespace color
{
    class ColorHSVPalette : public Palette<ColorHSV, color_hsv_pack>
    {
    private:
        color_hsv_pack hsv;

    public:
        ColorHSVPalette(color_hsv_pack hsv,
                        uint16_t length)
            : Palette(length) {}

        // implement
        inline color_pack Map(uint16_t index)
        {
            uint16_t length = Length();
            if (length == 0)
            {
                return 0;
            }
            // return palette[Begin() + index % length];
            return 0;
        }
    };

} // namespace color
