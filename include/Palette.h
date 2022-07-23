// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Range.h"
#include "Math.h"
#include "gamma.h"

using glow::Range;

namespace color
{
    template <typename COLORTYPE, typename COLORPACK>
    class Palette : public Range
    {
    public:
        bool gamma;

        Palette(uint16_t length, bool gamma = true)
            : Range(0, length), gamma(gamma) {}

        // implement
        inline color_pack Gamma(color_pack c)
        {
            Color g(c);
            g(gamma8(g.Red()),
              gamma8(g.Green()),
              gamma8(g.Blue()));
            return g.Pack();
        }
    };
} // namespace color