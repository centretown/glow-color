// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientPalette.h"
#include "HSV.h"

namespace color
{
  class HueGradient : public GradientPalette<hue_limit>
  {
  public:
    HueGradient(color_hsv_pack hue = 0)
        : GradientPalette(hue) {}

    // implement
    inline color_pack Map(uint16_t index)
    {
      hue.Hue(Begin() + (increment * index) % Length());
      return ToRGB(hue.Pack());
    }
  };
} // namespace color
