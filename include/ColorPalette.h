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
            return palette[Begin() + index % Length()];
        }
    };
} // namespace color
