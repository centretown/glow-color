// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Palette.h"

namespace color
{
    class GradientPalette;
    class Gradient : public Palette
    {
    private:
        Range fit;
        friend GradientPalette;

    public:
        Gradient(uint16_t size = 1) : Palette(size)
        {
            fit = Pack();
        }

        inline void Fit(Range &range)
        {
            fit = range;
        }

        inline void Refit()
        {
            fit = Pack();
        }

        inline uint16_t Map(uint16_t index)
        {
            return Begin() + (index - fit.Begin()) * Length() / fit.Length();
        }

        inline const uint16_t FitLength() const { return fit.Length(); }
    };
} // namespace color
