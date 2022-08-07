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
        Range fit;
        bool reverse = false;

        uint16_t size = 1;
        bool gamma = false;
        bool sine = false;

    public:
        Palette(uint16_t v = 1)
        {
            size = (v < 1) ? 1 : v;
            Resize(0, size);
            fit = Pack();
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

        inline void Fit(Range &range)
        {
            fit = range;
        }

        inline void Refit()
        {
            fit = Pack();
        }

        inline bool Reverse()
        {
            return reverse;
        }

        inline bool Reverse(bool v)
        {
            return reverse = v;
        }

        // use Span to constrain Range resizes
        range_pack Span();

        inline bool IsMininmum() { return (Begin() == 0 && End() == 1); }

        inline uint16_t Map(uint16_t index)
        {
            if (reverse)
            {
                return End() - (index - fit.Begin()) * Length() / fit.Length();
            }
            return Begin() + (index - fit.Begin()) * Length() / fit.Length();
        }

        inline const uint16_t FitLength() const { return fit.Length(); }

        uint16_t Size(uint16_t v)
        {
            size = v;
            Span(0, size);
            return size;
        }
    };

} // namespace color