// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Gradient.h"

namespace color
{
    typedef enum : uint8_t
    {
        VARY_NONE = 0,
        VARY_HUE = 1,
        VARY_SATURATION = 2,
        VARY_LUMINANCE = 4,
        VARY_HUE_SATURATION = VARY_HUE |
                              VARY_SATURATION,
        VARY_HUE_LUMINANCE = VARY_HUE |
                             VARY_LUMINANCE,
        VARY_SATURATION_LUMINANCE = VARY_SATURATION |
                                    VARY_LUMINANCE,
        VARY_ALL = VARY_HUE |
                   VARY_SATURATION |
                   VARY_LUMINANCE,
    } GradientTransition;

    class GradientPalette
    {
    private:
        GradientTransition varied = VARY_HUE;

        Gradient hueGradient;
        Gradient saturationGradient;
        Gradient luminanceGradient;

        uint16_t hue = 0;
        uint8_t saturation = 0;
        uint8_t luminance = 0;

        Color color;

        bool reverse = false;
        bool gamma = false;

    public:
        GradientPalette(GradientTransition v = VARY_HUE,
                        uint16_t hue = 0,
                        uint8_t saturation = 255,
                        uint8_t luminance = 255)
            : varied(v),
              hue(hue),
              saturation(saturation),
              luminance(luminance)
        {
            hueGradient.Size(hue_size);
            saturationGradient.Size(saturation_size);
            luminanceGradient.Size(luminance_size);
        }

        bool Gamma() { return gamma; }
        bool Gamma(bool v) { return gamma = v; }

        // modify
        inline Gradient &Hue() { return hueGradient; }
        inline Gradient &Saturation() { return saturationGradient; }
        inline Gradient &Luminance() { return luminanceGradient; }

        // implement
        inline color_pack Map(uint16_t index)
        {
            if (VARY_HUE & varied)
            {
                hue = hueGradient.Map(index);
            }
            if (VARY_SATURATION & varied)
            {
                saturation = saturationGradient.Map(index);
            }
            if (VARY_LUMINANCE & varied)
            {
                luminance = luminanceGradient.Map(index);
            }
            color.Wheel(hue, saturation, luminance, gamma);
            return color.Pack();
        }

        inline void Fit(Range &range)
        {
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

        inline bool Reverse()
        {
            return reverse;
        }

        inline bool Reverse(bool v)
        {
            hueGradient.Reverse(v);
            saturationGradient.Reverse(v);
            luminanceGradient.Reverse(v);
            return reverse = v;
        }

        inline GradientTransition Vary() const { return varied; }
        inline GradientTransition Vary(GradientTransition v) { return varied = v; }

        void operator()(uint16_t vHue = 0,
                        uint8_t vSaturation = 255,
                        uint8_t vLuminance = 255)
        {
            hue = vHue;
            saturation = vSaturation;
            luminance = vLuminance;
        }
    };
} // namespace color
