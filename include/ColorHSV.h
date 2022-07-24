// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"

namespace color
{
    typedef uint32_t color_hsv_pack;
    typedef struct
    {
        uint16_t hue;
        uint8_t saturation;
        uint8_t value;
    } color_hsv;

    const uint8_t max_color = 255;
    const uint16_t red_to_yellow = 255;
    const uint16_t red_to_green = 510;
    const uint16_t green_to_cyan = 765;
    const uint16_t green_to_blue = 1020;
    const uint16_t blue_to_magenta = 1275;
    const uint16_t blue_to_red = 1530;

    const uint16_t hue_limit = 0xffff;
    const uint8_t saturation_limit = 0xff;
    const uint8_t value_limit = 0xff;

    class ColorHSV
    {
    private:
        union
        {
            color_hsv hsv;
            color_hsv_pack pack;
        };

    public:
        ColorHSV(color_hsv_pack pack = 0) : pack(pack) {}

        ColorHSV(uint16_t hue,
                 uint8_t saturation,
                 uint8_t value)
        {
            HSV(hue, saturation, value);
        }

        ColorHSV(ColorHSV &colorHSV)
        {
            HSV(colorHSV.Hue(),
                colorHSV.Saturation(),
                colorHSV.Value());
        }

        // ColorHSV(Color &color)
        // {
        //     // fromRGB(color.Pack());
        // }

        // member access
        inline uint16_t Hue() const { return hsv.hue; }
        inline uint8_t Saturation() const { return hsv.saturation; }
        inline uint8_t Value() const { return hsv.value; }
        color_hsv_pack Pack() const { return pack; }

        // member setters
        inline void Hue(uint16_t v) { hsv.hue = v; }
        inline void Saturation(uint8_t v) { hsv.saturation = v; }
        inline void Value(uint8_t v) { hsv.value = v; }

        // modify all
        inline void HSV(uint16_t h, uint8_t s, uint8_t v)
        {
            hsv.hue = h;
            hsv.saturation = s;
            hsv.value = v;
        }
        void Pack(color_hsv_pack v) { pack = v; }
        void Copy(ColorHSV &v) { pack = v.Pack(); }

        inline uint8_t biggest(Color &color)
        {
            uint8_t colorMax = color.Red();
            if (color.Green() > colorMax)
            {
                colorMax = color.Green();
            }
            if (color.Blue() > colorMax)
            {
                colorMax = color.Blue();
            }
            return colorMax;
        }
        inline uint8_t smallest(Color &color)
        {
            uint8_t colorMin = color.Red();
            if (color.Green() < colorMin)
            {
                colorMin = color.Green();
            }
            if (color.Blue() < colorMin)
            {
                colorMin = color.Blue();
            }
            return colorMin;
        }
    };

} // namespace pixel
