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

    const uint16_t hue_limit = 1530;
    const uint8_t saturation_limit = 0xff;
    const uint8_t value_limit = 0xff;

    class Wheel
    {
    private:
        union
        {
            color_hsv hsv;
            color_hsv_pack pack;
        };

    public:
        Wheel(color_hsv_pack pack = 0) : pack(pack) {}

        Wheel(uint16_t hue,
                 uint8_t saturation,
                 uint8_t value)
        {
            HSV(hue, saturation, value);
        }

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
        inline void HSV(uint16_t hue, uint8_t saturation, uint8_t value)
        {
            hsv.hue = hue;
            hsv.saturation = saturation;
            hsv.value = value;
        }
        void Pack(color_hsv_pack v) { pack = v; }
    };

} // namespace pixel
