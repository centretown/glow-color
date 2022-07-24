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
    private:
        static uint16_t const minimum_size = 1;

    protected:
        uint16_t size = minimum_size;

    public:
        Palette(uint16_t v)
        {
            size = (v < minimum_size) ? minimum_size : v;
            Resize(0, size);
        }

        const uint16_t Size() const { return size; }

        // use Span to safely resize range
        range_pack Span(uint16_t begin, uint16_t end)
        {
            Resize(begin, end);
            return Span();
        }

        // use Span to constrain Range resizes
        range_pack Span();

        inline bool IsMininmum() { return (Begin() == 0 && End() == 1); }
    };
} // namespace color