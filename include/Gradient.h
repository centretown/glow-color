// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Palette.h"

namespace color
{
    class Gradient : public Palette
    {
    public:
        Gradient(uint16_t size = 1) : Palette(size) {}
    };
} // namespace color
