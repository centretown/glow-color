// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Palette.h"

namespace color
{
    class ColorPalette : public Palette
    {
    private:
        const color_pack *palette;

    public:
        ColorPalette(const color_pack *palette,
                     uint16_t v)
            : Palette(v), palette(palette) {}

        // implement
        inline color_pack Map(uint16_t index)
        {
            Color color(palette[Begin() + index % Length()]);
            if (gamma)
            {
                color = color.Gamma();
            }
            return color.Pack();
        }
    };
} // namespace color
