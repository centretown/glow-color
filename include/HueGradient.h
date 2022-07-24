// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientPalette.h"
#include "HSV.h"

namespace color
{
  class HueGradient : public GradientPalette<0xffff>
  {
  public:
    HueGradient(color_hsv_pack hue = 0)
        : GradientPalette(hue) {}

    // implement
    inline color_pack Map(uint16_t index)
    {
      hue.Hue(Begin() + index % Length());
      return ToRGB(hue.Pack());
    }
  };
} // namespace color
