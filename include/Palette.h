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
    // color harmonies
    enum : uint8_t
    {
        SCHEME_COMPLEMENTARY,       // 2 hues, opposing ends of wheel (180 deg)
        SCHEME_SPLIT_COMPLEMENTARY, // 3 hues, 1 key & 2 next to key's complement
        SCHEME_ANALOGOUS,           // 3 hues, positioned next to each other
        SCHEME_TRIADIC,             // 3 hues, evenly spaced (120 deg)
        SCHEME_TETRADIC,            // 1 key, 4 hues equidistant from key
        SCHEME_SQUARE,              // 4 hues evenly spaced (90 deg)
        SCHEME_MONOCHROMATIC,       // 1 hue different tones, shades or tints
    };

    class Palette : public Range
    {
    protected:
        uint16_t size = 1;
        bool gamma = false;
        bool sine = false;

    public:
        Palette(uint16_t v = 1)
        {
            size = (v < 1) ? 1 : v;
            Resize(0, size);
        }

        bool Gamma() { return gamma; }
        bool Gamma(bool v) { return gamma = v; }
        bool Sine() { return sine; }
        bool Sine(bool v) { return sine = v; }

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