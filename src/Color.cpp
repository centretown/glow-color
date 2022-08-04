// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Color.h"

namespace color
{
    void Color::Wheel(uint16_t hue,
                      uint8_t saturation,
                      uint8_t luminance,
                      bool gamma)
    {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;

        hue %= hue_limit;
        if (hue < hue_green)
        {
            if (hue < hue_yellow)
            {
                red = rgb_limit;
                green = hue;
            }
            else // yellow to green
            {
                red = hue_green - hue;
                green = rgb_limit;
            }
        }
        else if (hue < hue_blue)
        {
            if (hue < hue_cyan)
            {
                green = rgb_limit;
                blue = hue - hue_green;
            }
            else // cyan to blue
            {
                green = hue_blue - hue;
                blue = rgb_limit;
            }
        }
        else if (hue < hue_limit)
        {
            if (hue < hue_magenta)
            {
                blue = rgb_limit;
                red = hue - hue_blue;
            }
            else // magenta to red
            {
                blue = hue_limit - hue;
                red = rgb_limit;
            }
        }
        else
        {
            red = rgb_limit;
        }

        uint16_t saturation_multiplier = 1 + saturation;
        uint16_t saturation_added = hue_segment - saturation;
        uint16_t luminance_multiplier = 1 + luminance;

        if (gamma)
        {
            red = gamma8(red);
            green = gamma8(green);
            blue = gamma8(blue);
        }

        uint16_t color_result = (red * saturation_multiplier) >> 8;
        color_result += saturation_added;
        rgbw.red = (color_result * luminance_multiplier) >> 8;

        color_result = (green * saturation_multiplier) >> 8;
        color_result += saturation_added;
        rgbw.green = (color_result * luminance_multiplier) >> 8;

        color_result = (blue * saturation_multiplier) >> 8;
        color_result += saturation_added;
        rgbw.blue = (color_result * luminance_multiplier) >> 8;
    }

    wheel_pack Color::ToWheel()
    {
        uint16_t color_max = Max(red, Max(green, blue));
        uint16_t color_min = Min(red, Min(green, blue));
        uint16_t color_diff = color_max - color_min;

        uint16_t luminance = color_max;
        uint16_t saturation =
            (color_max == 0) ? 0
                             : (color_diff * saturation_size) / color_max;

        uint16_t hue;
        if (color_diff == 0)
        {
            hue = 0;
        }
        else
        {
            uint16_t hue_factor = 0;
            if (color_max == red)
            {
                hue_factor = (hue_segment * (green - blue) / color_diff) + hue_limit;
            }
            else if (color_max == green)
            {
                hue_factor = (hue_segment * (blue - red) / color_diff) + hue_green;
            }
            else if (color_max == blue)
            {
                hue_factor = (hue_segment * (red - green) / color_diff) + hue_blue;
            }

            hue = hue_factor % hue_limit;
        }

        return ColorWheel(hue, (uint8_t)saturation, (uint8_t)luminance).Pack();
    }

} // namespace color
