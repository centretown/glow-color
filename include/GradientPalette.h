// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorHSV.h"
#include "Color.h"
#include "Palette.h"

namespace color
{
    template <uint16_t EXTENT>
    class GradientPalette : public Palette
    {
    protected:
        ColorHSV hue;

    public:
        GradientPalette(color_hsv_pack pack)
            : Palette(EXTENT)
        {
            hue.Pack(pack);
        }

        // access
        inline color_hsv_pack Hue() { return hue.Pack(); }
        inline void Hue(color_hsv_pack v) { hue.Pack(v); }
    };

} // namespace color
