// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Range.h"
#include "Math.h"
#include "gamma.h"

using glow::Range;
using glow::range_pack;

namespace color
{
    class Palette : public Range
    {
    protected:
        uint16_t size = 1;

    public:
        Palette(uint16_t v = 1)
        {
            size = (v < 1) ? 1 : v;
            Resize(0, size);
        }

        uint16_t Size() { return size; }

        // use Span to safely resize range
        range_pack Span(uint16_t begin, uint16_t end)
        {
            Resize(begin, end);
            return Span();
        }

        // use Span to constrain Range resizes
        range_pack Span();

        inline bool IsMininmum() { return (Begin() == 0 && End() == 1); }

    protected:
        uint16_t Size(uint16_t v)
        {
            size = v;
            Span(0, size);
            return size;
        }
    };
} // namespace color