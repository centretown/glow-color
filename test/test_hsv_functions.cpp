// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"

#include "Range.h"
#include "Color.h"
#include "ColorHSV.h"

using glow::Benchmark;
using glow::print_line;

using color::Color;
using color::ColorWheel;
using color::hue_limit;
using color::luminance_size;
using color::saturation_size;
using color::wheel_hsv;
using color::wheel_pack;

using color::hue_blue;
using color::hue_cyan;
using color::hue_green;
using color::hue_limit;
using color::hue_magenta;
using color::hue_red;
using color::hue_yellow;

uint64_t bench_accum = 0;

void testBenchHSV()
{
    set_real_time(true);
    Benchmark benchmark;
    benchmark.Begin("testBenchHSV");

    uint16_t hue = 0;
    uint8_t saturation = 15;
    uint8_t luminance = 15;

    for (hue = 0; hue < hue_limit; hue++)
    {
        uint32_t colorHSV = ColorHSV(hue, saturation, luminance);
        bench_accum += colorHSV;
    }
    benchmark.End();
    set_real_time(false);
}

void testBenchWheel()
{
    set_real_time(true);
    Benchmark benchmark;
    benchmark.Begin("testBenchWheel");

    Color color;
    for (uint16_t hue = 0; hue < hue_limit; hue++)
    {
        color.Wheel(hue, 15, 15);
        bench_accum += color.Pack();
    }
    benchmark.End();
    set_real_time(false);
}

void testCompareWheelHSV()
{
    uint16_t hue = 0;
    uint8_t saturation = 0;
    uint8_t luminance = 0;

    Color color;

    for (hue = 0; hue < hue_limit; hue++)
    {
        color.Wheel(hue, saturation, luminance);

        uint32_t colorHSV = ColorHSV(hue, saturation, luminance);

        TEST_ASSERT_EQUAL_HEX(colorHSV, color.Pack());

        bench_accum += colorHSV + color.Pack();
    }

    for (saturation = 0; saturation < saturation_size; saturation++)
    {
        color.Wheel(hue, saturation, luminance);

        uint32_t colorHSV = ColorHSV(hue, saturation, luminance);

        TEST_ASSERT_EQUAL_HEX(colorHSV, color.Pack());

        bench_accum += colorHSV + color.Pack();
    }

    for (luminance = 0; luminance < luminance_size; luminance++)
    {
        color.Wheel(hue, saturation, luminance);

        uint32_t colorHSV = ColorHSV(hue, saturation, luminance);

        TEST_ASSERT_EQUAL_HEX(colorHSV, color.Pack());

        bench_accum += colorHSV + color.Pack();
    }
}

void showColor(Color color, bool crlf = true)
{
    char buffer[32];
    snprintf(buffer, sizeof(buffer),
             "(r=%x, g=%x, b=%x)",
             color.Red(),
             color.Green(),
             color.Blue());
    print_line(buffer, crlf);
}

void showWheel(ColorWheel wheel, bool crlf = true)
{
    char buffer[32];
    snprintf(buffer, sizeof(buffer),
             "(h=%x, s=%x, l=%x)",
             wheel.Hue(),
             wheel.Saturation(),
             wheel.Luminance());
    print_line(buffer, crlf);
}

void showHSL(uint16_t &hue,
             uint8_t &saturation,
             uint8_t &luminance, bool crlf = true)
{
    char buffer[32];
    snprintf(buffer, sizeof(buffer),
             "(h=%x, s=%x, l=%x)",
             hue,
             saturation,
             luminance);
    print_line(buffer, crlf);
}

void testCompareWheelToWheel()
{

    Color color;
    Color colorA;

    uint16_t hue = hue_green;
    uint8_t saturation = saturation_size;
    uint8_t luminance = luminance_size;
    showHSL(hue, saturation, luminance, false);
    showColor(color);

    ColorWheel wheel(hue, saturation, luminance);
    color.Wheel(hue, saturation, luminance);
    colorA.Wheel(wheel.Pack());
    showHSL(hue, saturation, luminance, false);
    showWheel(wheel, false);
    showColor(color);
    TEST_ASSERT_EQUAL_HEX(colorA.Pack(), color.Pack());

    color.Wheel(hue, saturation, luminance);
    wheel(hue, saturation, luminance);
    showColor(color, false);
    showHSL(hue, saturation, luminance, false);
    showWheel(wheel, true);
    wheel_pack wp = color.ToWheel();
    showWheel(wheel, true);
    colorA.Wheel(wp);
    showColor(color, true);
    TEST_ASSERT_EQUAL_HEX(colorA.Pack(), color.Pack());

    hue = 0x0f;
    saturation = saturation_size / 2;
    luminance = luminance_size;
    showHSL(hue, saturation, luminance, false);
    color.Wheel(hue, saturation, luminance);
    showColor(color, true);
    colorA.Wheel(color.ToWheel());
    TEST_ASSERT_EQUAL_HEX(colorA.Pack(), color.Pack());
}

void testHSVFunctions()
{
    RUN_TEST(testBenchWheel);
    RUN_TEST(testBenchHSV);
    RUN_TEST(testCompareWheelHSV);
    RUN_TEST(testCompareWheelToWheel);
}
