// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Palette.h"

namespace color
{
    class GradientPalette;
    class Gradient : public Palette
    {
    private:
        uint16_t increment = 1;
        friend GradientPalette;

    public:
        Gradient(uint16_t size = 1) : Palette(size) {}

        inline uint16_t Fit(Range &range)
        {
            uint16_t i = Length() / range.Length();
            return increment = (i < 1) ? 1 : i;
        }

        inline uint16_t Refit()
        {
            return increment = 1;
        }

        inline uint16_t Map(uint16_t index)
        {
            return Begin() + (increment * index) % Length();
        }

        inline const uint16_t Increment() const { return increment; }
    };
} // namespace color
