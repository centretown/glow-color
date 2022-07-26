// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Wheel.h"
#include "Color.h"
#include "Palette.h"

namespace color
{
    template <uint16_t EXTENT>
    class GradientPalette : public Palette
    {
    protected:
        Wheel hue;
        uint16_t increment = 1;

    public:
        GradientPalette(color_hsv_pack pack)
            : Palette(EXTENT)
        {
            hue.Pack(pack);
        }

        // access
        inline color_hsv_pack Hue() { return hue.Pack(); }

        // modify

        inline void Hue(color_hsv_pack v) { hue.Pack(v); }

        inline uint16_t Fit(range_pack pack)
        {
            Range range(pack);
            increment = Length() / range.Length();
            if (increment < 1)
            {
                increment = 1;
            }
            return increment;
        }

        inline uint16_t Refit()
        {
            return increment = 1;
        }
    };

} // namespace color
