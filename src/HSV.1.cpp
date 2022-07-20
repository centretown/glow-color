// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "HSV.1.h"

namespace color
{
    color_pack ToRGB_1(color_hsv_pack HSV)
    {
        ColorHSV colorHSV(HSV);
        uint16_t mappedHue = mapHue_1(colorHSV.Hue());
        color_pack pack = mapHueToColor_1(mappedHue);
        pack = applySaturationValue_1(pack, colorHSV);
        return pack;
    }

    inline uint16_t mapHue_1(uint16_t hue)
    {
        const uint32_t actual_ticks = 1530;
        const uint32_t half_limit = 32768; // 0x8000
        const uint32_t limit = 65536;      // 0x10000
        uint32_t mapped_hue = hue;
        mapped_hue *= actual_ticks;
        mapped_hue += half_limit;
        mapped_hue /= limit;
        return static_cast<uint16_t>(mapped_hue);
    }

    color_pack mapHueToColor_1(uint16_t mapped_hue)
    {
        if (mapped_hue < red_to_green)
        {
            return redToGreen_1(mapped_hue);
        }

        if (mapped_hue < green_to_blue)
        {
            return greenToBlue_1(mapped_hue);
        }

        if (mapped_hue < blue_to_red)
        {
            return blueToRed_1(mapped_hue);
        }

        // full red
        Color color(max_color, 0, 0);
        return color.Pack();
    }

    inline color_pack redToGreen_1(uint16_t mapped_hue)
    {
        Color color;
        if (mapped_hue < red_to_yellow)
        {
            color.Red(max_color);
            color.Green(static_cast<uint8_t>(mapped_hue));
        }
        else // yellow to green
        {
            color.Red(static_cast<uint8_t>(red_to_green - mapped_hue));
            color.Green(max_color);
        }
        return color.Pack();
    }

    inline color_pack greenToBlue_1(uint16_t mapped_hue)
    {
        Color color;
        if (mapped_hue < green_to_cyan)
        {
            color.Green(max_color);
            color.Blue(static_cast<uint8_t>(mapped_hue - red_to_green));
        }
        else // cyan to blue
        {
            color.Green(static_cast<uint8_t>(green_to_blue - mapped_hue));
            color.Blue(max_color);
        }
        return color.Pack();
    }

    inline color_pack blueToRed_1(uint16_t mapped_hue)
    {
        Color color;
        if (mapped_hue < blue_to_magenta)
        {
            color.Blue(max_color);
            color.Red(static_cast<uint8_t>(mapped_hue - green_to_blue));
        }
        else // magenta to red
        {
            color.Blue(static_cast<uint8_t>(blue_to_red - mapped_hue));
            color.Red(max_color);
        }
        return color.Pack();
    }

    color_pack applySaturationValue_1(color_pack pack, ColorHSV& hsv)
    {
        uint16_t saturation_multiplier = 1 + hsv.Saturation(); // s1 1 to 256; same reason
        uint16_t value_multiplier = 1 + hsv.Value();           // v1 1 to 256; allows >>8 instead of /255
        uint8_t saturation_added = 255 - hsv.Saturation();     // s2 255 to 0

        Color color(pack);

        uint8_t applied = apply_1(color.Red(),
                                saturation_multiplier,
                                value_multiplier,
                                saturation_added);
        color.Red(applied);

        applied = apply_1(color.Green(),
                        saturation_multiplier,
                        value_multiplier,
                        saturation_added);
        color.Green(applied);

        applied = apply_1(color.Blue(),
                        saturation_multiplier,
                        value_multiplier,
                        saturation_added);
        color.Blue(applied);
        return color.Pack();
    }

    inline uint8_t apply_1(uint8_t color,
                         uint16_t saturation_multiplier,
                         uint16_t value_multiplier,
                         uint8_t saturation_added)
    {
        uint16_t color_result = color * saturation_multiplier;
        color_result >>= 8; // divide by 255
        color_result += saturation_added;
        color_result *= value_multiplier;
        color_result >>= 8; // shift to lower 8
        return static_cast<uint8_t>(color_result);
    }
} // namespace color
