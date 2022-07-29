// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Palette.h"

namespace color
{
    class GradientPalette;
    class Gradient : public Palette
    {
    private:
        uint16_t fitLength = 1;
        friend GradientPalette;

    public:
        Gradient(uint16_t size = 1) : Palette(size)
        {
            fitLength = Length();
        }

        inline uint16_t Fit(Range &range)
        {
            return fitLength = range.Length();
        }

        inline uint16_t Refit()
        {
            return fitLength = Length();
        }

        inline uint16_t Map(uint16_t index)
        {
            return ((fitLength * index) / Length()) + Begin();
        }

        inline const uint16_t FitLength() const { return fitLength; }
    };
} // namespace color
