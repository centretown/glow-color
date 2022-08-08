// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Palette.h"

namespace color
{
    typedef enum : uint8_t
    {
        VARY_HUE,
        VARY_SATURATION,
        VARY_LUMINANCE,
    } GradientVaried;

    class GradientPalette : public Palette
    {
    private:
        GradientVaried varied = VARY_HUE;
        uint16_t values[3] = {0};
        Color color;

    public:
        GradientPalette(GradientVaried v,
                        uint16_t size = 0) : Palette(size)
        {
            Vary(v, size);
        }

        // access
        inline GradientVaried Vary() const { return varied; }
        inline uint16_t Hue() const { return values[VARY_HUE]; }
        inline uint16_t Saturation() const { return values[VARY_SATURATION]; }
        inline uint16_t Luminance() const { return values[VARY_LUMINANCE]; }

        // modify
        inline uint16_t Hue(uint16_t v) { return values[VARY_HUE] = v; }
        inline uint16_t Saturation(uint8_t v) { return values[VARY_SATURATION] = v; }
        inline uint16_t Luminance(uint8_t v) { return values[VARY_LUMINANCE] = v; }

        inline GradientVaried Vary(GradientVaried v,
                                   uint16_t transition_size = 0)
        {
            varied = v;
            if (transition_size > 0)
            {
                Size(transition_size);
            }
            else if (v == VARY_HUE)
            {
                Size(hue_size);
            }
            else
            {
                Size(saturation_size);
            }
            return varied;
        }

        // implement
        inline color_pack Map(uint16_t index)
        {
            values[varied] = index;
            color.Wheel(Hue(), Saturation(), Luminance(), gamma);
            return color.Pack();
        }
    };
} // namespace color
