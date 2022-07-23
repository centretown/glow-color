// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Palette.h"

namespace color
{
    class ColorPalette : public Palette<Color, color_pack>
    {
    private:
        const color_pack *palette;

    public:
        ColorPalette(const color_pack *palette,
                     uint16_t length, bool gamma = false)
            : Palette(length, gamma),
              palette(palette) {}

        // implement
        inline color_pack Map(uint16_t index)
        {
            uint16_t length = Length();
            if (length == 0)
            {
                return 0;
            }

            color_pack c = palette[Begin() + index % length];
            if (gamma)
            {
                c = Gamma(c);
            }
            return c;
        }
    };
} // namespace color
