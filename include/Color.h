// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "gamma.h"
#include "sine.h"
#include "Math.h"
#include "ColorWheel.h"

using glow::Max;
using glow::Min;

namespace color
{
    // color schemes (harmonies)
    enum : uint8_t
    {
        SCHEME_COMPLEMENTARY,       // 2 hues, opposing ends of wheel (180 deg)
        SCHEME_SPLIT_COMPLEMENTARY, // 3 hues, 1 key & 2 next to key's complement
        SCHEME_ANALOGOUS,           // 3 hues, positioned next to each other
        SCHEME_TRIADIC,             // 3 hues, evenly spaced (120 deg)
        SCHEME_TETRADIC,            // 1 key, 4 hues equidistant from key
        SCHEME_SQUARE,              // 4 hues evenly spaced (90 deg)
        SCHEME_MONOCHROMATIC,       // 1 hue different tones, shades or tints
    };

    const uint16_t hue_limit = 1530;
    const uint16_t hue_segment = hue_limit / 6;
    const uint16_t hue_red = 0;
    const uint16_t hue_yellow = hue_segment;
    const uint16_t hue_green = hue_segment * 2;
    const uint16_t hue_cyan = hue_segment * 3;
    const uint16_t hue_blue = hue_segment * 4;
    const uint16_t hue_magenta = hue_segment * 5;

    // doubled to allow ranges like:
    // blue-yellow 1020 - 1785
    const uint16_t hue_size = hue_limit * 2;
    const uint8_t saturation_size = 0xff;
    const uint8_t luminance_size = 0xff;
    const uint8_t rgb_limit = 0xff;

    typedef uint32_t color_pack;

    typedef enum : uint8_t
    {
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_RED,
        COLOR_WHITE,
    } PRIMARY;

    typedef struct
    {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t white;
    } color_rgbw;

    typedef struct
    {
        uint8_t element;
        operator uint8_t() { return element; }
        inline uint8_t operator=(uint8_t &v)
        {
            return element = v;
        }
        inline uint8_t operator=(const uint8_t v)
        {
            return element = v;
        }
        inline uint8_t &operator&=(uint8_t v)
        {
            return element &= v;
        }
        inline uint8_t &operator|=(uint8_t v)
        {
            return element |= v;
        }
        inline uint8_t &operator^=(uint8_t v)
        {
            return element ^= v;
        }
        inline uint8_t operator&(uint8_t v) const
        {
            return element & v;
        }
        inline uint8_t operator|(uint8_t v) const
        {
            return element | v;
        }
        inline uint8_t operator^(uint8_t v) const
        {
            return element ^ v;
        }
        inline uint8_t operator>>(uint8_t v)
        {
            return element >> v;
        }
    } color_element;

    class Color
    {
    private:
        union
        {

            struct
            {
                uint8_t blue;
                uint8_t green;
                uint8_t red;
                uint8_t white;
            };
            color_rgbw rgbw;
            color_pack pack;
            color_element elements[4];
        };

    public:
        Color(color_pack pack = 0) : pack(pack) {}

        Color(uint8_t red, uint8_t green,
              uint8_t blue, uint8_t white = 0)
        {
            RGBW(red, green, blue, white);
        }

        Color(Color &color)
        {
            Pack(color.Pack());
        }

        // access member

        inline uint8_t Red() const { return rgbw.red; }
        inline uint8_t Green() const { return rgbw.green; }
        inline uint8_t Blue() const { return rgbw.blue; }
        inline uint8_t White() const { return rgbw.white; }
        inline color_pack Pack() const { return pack; }

        // modify member

        // inline color_element &Element(PRIMARY i) { return elements[i]; }
        inline color_element &RED() { return elements[COLOR_RED]; }
        inline color_element &GREEN() { return elements[COLOR_GREEN]; }
        inline color_element &BLUE() { return elements[COLOR_BLUE]; }
        inline color_element &WHITE() { return elements[COLOR_WHITE]; }

        inline void Red(uint8_t r) { rgbw.red = r; }
        inline void Green(uint8_t g) { rgbw.green = g; }
        inline void Blue(uint8_t b) { rgbw.blue = b; }
        inline void White(uint8_t w) { rgbw.white = w; }

        // modify all members: color_pack

        inline color_pack Pack(color_pack v) { return pack = v; }

        inline void Copy(Color &v) { Pack(v.pack); }

        // modify all members: color_rgbw

        inline void RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        {
            RGBW(r, g, b);
        }
        inline void GBR(uint8_t g = 0, uint8_t b = 0, uint8_t r = 0)
        {
            RGBW(r, g, b);
        }
        inline void BGR(uint8_t b = 0, uint8_t g = 0, uint8_t r = 0)
        {
            RGBW(r, g, b);
        }

        inline void RGBW(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t w = 0)
        {
            rgbw.red = r;
            rgbw.green = g;
            rgbw.blue = b;
            rgbw.white = w;
        }

        // modify all members: operators

        inline Color &operator=(const Color &other)
        {
            Pack(other.Pack());
            return *this;
        }

        inline Color &operator=(const color_pack other)
        {
            Pack(other);
            return *this;
        }

        inline color_pack operator()() const
        {
            return pack;
        }

        inline color_pack operator()(color_pack v)
        {
            pack = v;
            return pack;
        }

        inline Color &operator()(int8_t r,
                                 int8_t g,
                                 int8_t b,
                                 int8_t w = 0)
        {
            RGBW(r, g, b, w);
            return *this;
        }

        inline color_pack AND(uint8_t mask)
        {
            return Color(RED() &= mask,
                         GREEN() &= mask,
                         BLUE() &= mask,
                         WHITE() &= mask)
                .Pack();
        }
        inline color_pack OR(int8_t mask)
        {
            return Color(RED() |= mask,
                         GREEN() |= mask,
                         BLUE() |= mask,
                         WHITE() |= mask)
                .Pack();
        }
        inline color_pack XOR(int8_t mask)
        {
            return Color(RED() ^= mask,
                         GREEN() ^= mask,
                         BLUE() ^= mask,
                         WHITE() ^= mask)
                .Pack();
        }

        inline color_pack operator&(int8_t mask)
        {
            return AND(mask);
        }

        inline color_pack operator|(int8_t mask)
        {
            return OR(mask);
        }

        inline color_pack operator^(int8_t mask)
        {
            return XOR(mask);
        }

        inline Color &operator&=(int8_t mask)
        {
            Pack(AND(mask));
            return *this;
        }

        inline Color &operator|=(int8_t mask)
        {
            Pack(OR(mask));
            return *this;
        }

        inline Color &operator^=(int8_t mask)
        {
            Pack(XOR(mask));
            return *this;
        }

        inline color_pack Gamma()
        {
            RGBW(gamma8(rgbw.red),
                 gamma8(rgbw.green),
                 gamma8(rgbw.blue),
                 gamma8(rgbw.white));
            return Pack();
        }

        inline color_pack Sine()
        {
            RGBW(sine8(rgbw.red),
                 sine8(rgbw.green),
                 sine8(rgbw.blue),
                 sine8(rgbw.white));
            return Pack();
        }

    public:
        void Wheel(uint16_t hue,
                   uint8_t saturation,
                   uint8_t luminance,
                   bool gamma = false);

        void Wheel(wheel_pack pack,
                   bool gamma = false)
        {
            ColorWheel wheel(pack);
            Wheel(wheel.hsv.hue,
                  wheel.hsv.saturation,
                  wheel.hsv.luminance,
                  gamma);
        }

        wheel_pack ToWheel();

        // SCHEME_COMPLEMENTARY,       // 2 hues, opposing ends of wheel (180 deg)
        // SCHEME_SPLIT_COMPLEMENTARY, // 3 hues, 1 key & 2 next to key's complement
        // SCHEME_ANALOGOUS,           // 3 hues, positioned next to each other
        // SCHEME_TRIADIC,             // 3 hues, evenly spaced (120 deg)
        // SCHEME_TETRADIC,            // 1 key, 4 hues equidistant from key
        // SCHEME_SQUARE,              // 4 hues evenly spaced (90 deg)
        // SCHEME_MONOCHROMATIC,       // 1 hue different tones, shades or tints

        void Complementary(uint16_t hue,
                           uint16_t saturation,
                           uint16_t luminance)
        {
        }

        // void SplitComplementary(uint16_t hue,
        //                         uint16_t saturation,
        //                         uint16_t luminance,
        //                         bool gamma = false);
    };
} // namespace color
