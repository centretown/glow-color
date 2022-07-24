// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "HSV.h"

namespace color
{
    color_pack ToRGB(color_hsv_pack HSV)
    {
        ColorHSV colorHSV(HSV);
        color_pack pack = mapHueToColor(colorHSV.Hue());
        pack = applySaturationValue(pack, colorHSV);
        return pack;
    }

    inline color_pack mapHueToColor(uint16_t mapped_hue)
    {
        if (mapped_hue < red_to_green)
        {
            return redToGreen(mapped_hue);
        }

        if (mapped_hue < green_to_blue)
        {
            return greenToBlue(mapped_hue);
        }

        if (mapped_hue < blue_to_red)
        {
            return blueToRed(mapped_hue);
        }

        // full red
        Color color(max_color, 0, 0);
        return color.Pack();
    }

    inline color_pack redToGreen(uint16_t mapped_hue)
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

    inline color_pack greenToBlue(uint16_t mapped_hue)
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

    inline color_pack blueToRed(uint16_t mapped_hue)
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

    inline color_pack applySaturationValue(color_pack pack, ColorHSV &hsv)
    {
        uint16_t saturation_multiplier = 1 + hsv.Saturation(); // s1 1 to 256; same reason
        uint16_t value_multiplier = 1 + hsv.Value();           // v1 1 to 256; allows >>8 instead of /255
        uint8_t saturation_added = 255 - hsv.Saturation();     // s2 255 to 0

        Color color(pack);

        uint8_t applied = apply(color.Red(),
                                saturation_multiplier,
                                value_multiplier,
                                saturation_added);
        color.Red(applied);

        applied = apply(color.Green(),
                        saturation_multiplier,
                        value_multiplier,
                        saturation_added);
        color.Green(applied);

        applied = apply(color.Blue(),
                        saturation_multiplier,
                        value_multiplier,
                        saturation_added);
        color.Blue(applied);
        return color.Pack();
    }

    inline uint8_t apply(uint8_t color,
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
