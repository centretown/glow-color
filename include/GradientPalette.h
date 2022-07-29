// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Gradient.h"

namespace color
{
    typedef enum : uint8_t
    {
        CHANGE_NONE = 0,
        CHANGE_HUE = 1,
        CHANGE_SATURATION = 2,
        CHANGE_LUMINANCE = 4,
        CHANGE_ALL = CHANGE_HUE |
                     CHANGE_SATURATION |
                     CHANGE_LUMINANCE,
    } GradientChange;

    class GradientPalette
    {
    private:
        GradientChange change = CHANGE_NONE;

        Gradient hueGradient;
        Gradient saturationGradient;
        Gradient luminanceGradient;

        uint16_t hue = 0;
        uint8_t saturation = 0;
        uint8_t luminance = 0;

        Color color;

    public:
        GradientPalette(GradientChange flag = CHANGE_HUE,
                        uint16_t hue = 0,
                        uint8_t saturation = 255,
                        uint8_t luminance = 255)
            : change(flag),
              hue(hue),
              saturation(saturation),
              luminance(luminance)
        {
            hueGradient.Size(hue_size);
            saturationGradient.Size(saturation_size);
            luminanceGradient.Size(luminance_size);
        }

        inline void Reset(GradientChange vFlag = CHANGE_HUE,
                          uint16_t vHue = 0,
                          uint8_t vSaturation = 0,
                          uint8_t vLuminance = 0)
        {
            change = vFlag;
            hue = vHue;
            saturation = vSaturation;
            luminance = vLuminance;
        }

        // modify
        inline Gradient &Hue() { return hueGradient; }
        inline Gradient &Saturation() { return saturationGradient; }
        inline Gradient &Luminance() { return luminanceGradient; }

        // implement
        inline color_pack Map(uint16_t index)
        {
            if (CHANGE_HUE & change)
            {
                hue = hueGradient.Map(index);
            }
            if (CHANGE_SATURATION & change)
            {
                saturation = saturationGradient.Map(index);
            }
            if (CHANGE_LUMINANCE & change)
            {
                luminance = luminanceGradient.Map(index);
            }
            color.Wheel(hue, saturation, luminance);
            return color.Pack();
        }

        inline void Fit(range_pack pack)
        {
            Range range(pack);
            hueGradient.Fit(range);
            saturationGradient.Fit(range);
            luminanceGradient.Fit(range);
        }

        void Refit()
        {
            hueGradient.Refit();
            saturationGradient.Refit();
            luminanceGradient.Refit();
        }

        const GradientChange Change() { return change; }
    };
} // namespace color
