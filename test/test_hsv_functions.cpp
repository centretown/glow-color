// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"

#include "Range.h"
#include "Color.h"
#include "ColorHSV.h"

using glow::Benchmark;
// using glow::Range;

using color::Color;
// using color::color_pack;
// using color::color_rgbw;
using color::hue_limit;
using color::luminance_size;
using color::saturation_size;

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

void testCompare()
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
}

void testHSVFunctions()
{
    RUN_TEST(testBenchWheel);
    RUN_TEST(testBenchHSV);
    // RUN_TEST(testCompare);
}

// for (saturation = 0; saturation < saturation_limit; saturation++)
// {
//     color.Wheel(hue, saturation, luminance);

//     uint32_t colorHSV = ColorHSV(hue, saturation, luminance);

//     TEST_ASSERT_EQUAL_HEX(colorHSV, color.Pack());

//     bench_accum += colorHSV + color.Pack();
// }
// for (luminance = 0; luminance < luminance_limit; luminance++)
// {
//     color.Wheel(hue, saturation, luminance);

//     uint32_t colorHSV = ColorHSV(hue, saturation, luminance);

//     TEST_ASSERT_EQUAL_HEX(colorHSV, color.Pack());

//     bench_accum += colorHSV + color.Pack();
// }
