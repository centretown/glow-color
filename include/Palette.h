// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Range.h"
#include "Math.h"

using glow::Range;

namespace color
{
    template <typename COLORTYPE, typename COLORPACK>
    class Palette : public Range
    {
    private:
        bool gamma = false;

    public:
        Palette(uint16_t length)
            : Range(0, length), gamma(gamma) {}

        // access
        inline bool Gamma() { return gamma; }

        // modify
        inline void Gamma(bool v) { gamma = v; }

    };
} // namespace color