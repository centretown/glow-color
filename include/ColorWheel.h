// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace color
{
    typedef struct
    {
        uint16_t hue;
        uint8_t saturation;
        uint8_t luminance;
    } wheel_hsv;
    typedef uint32_t wheel_pack;

    class Color;

    class ColorWheel
    {
    private:
        union
        {
            wheel_hsv hsv;
            wheel_pack pack;
        };
        friend Color;

    public:
        ColorWheel(uint16_t hue,
                   uint8_t saturation,
                   uint8_t luminance)
        {
            hsv.hue = hue;
            hsv.saturation = saturation;
            hsv.luminance = luminance;
        }

        ColorWheel(wheel_pack pack) : pack(pack) {}
        inline wheel_pack Pack() const { return pack; }

        inline uint16_t Hue() const { return hsv.hue; };
        inline uint8_t Saturation() const { return hsv.saturation; };
        inline uint8_t Luminance() const { return hsv.luminance; };

        inline wheel_pack Pack(wheel_pack v) { return pack = v; }

        inline uint16_t Hue(uint16_t v) { return hsv.hue = v; };
        inline uint8_t Saturation(uint8_t v) { return hsv.saturation = v; };
        inline uint8_t Luminance(uint8_t v) { return hsv.luminance = v; };

        inline void operator()(uint16_t hue,
                        uint8_t saturation,
                        uint8_t luminance)
        {
            hsv.hue = hue;
            hsv.saturation = saturation;
            hsv.luminance = luminance;
        }
    };
} // namespace color
