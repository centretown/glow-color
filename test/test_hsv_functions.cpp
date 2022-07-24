// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"

#include "Range.h"
#include "ColorHSV.h"
#include "hsv_test.h"
#include "HSV.h"
#include "HSV.1.h"

using glow::Benchmark;
using glow::Range;

using color::Color;
using color::color_hsv_pack;
using color::color_pack;
using color::color_rgbw;
using color::ColorHSV;
using color::hue_limit;

const uint16_t HSV_TEST_LIMIT = hue_limit;
uint64_t accum = 0;

struct PutOriginal
{
    color_pack color = 0;

    uint16_t Put(uint16_t index, color_hsv_pack &hsv)
    {
        ColorHSV hsvColor(hsv + index);
        color_rgbw rgbw = {0, 0, 0};
        uint16_t mapped_hue = map_hue(hsvColor.Hue());
        map_hue_color(mapped_hue,
                      rgbw.red, rgbw.green, rgbw.blue);
        color = apply_saturation_value(hsvColor.Saturation(), hsvColor.Value(),
                                       rgbw.red, rgbw.green, rgbw.blue);
        accum += color;
        return index;
    }

    void Update()
    {
    }
};

struct PutCurrent
{
    color_pack color = 0;
    uint16_t Put(uint16_t index, color_hsv_pack &hsv)
    {
        color = color::ToRGB(hsv + index);
        accum += color;
        return index;
    }

    void Update()
    {
    }
};

struct PutNew
{
    color_pack color = 0;
    uint16_t Put(uint16_t index, color_hsv_pack &hsv)
    {
        color = color::ToRGB_1(hsv + index);
        accum += color;
        return index;
    }

    void Update()
    {
    }
};

void testHueVarianceOriginal()
{
    set_real_time(true);
    Benchmark benchmark;
    benchmark.Begin("testHueVarianceOriginal");

    ColorHSV hsv(0);
    PutOriginal putter;

    Range(0, HSV_TEST_LIMIT).Spin(putter, hsv.Pack());
    benchmark.End();

    set_real_time(false);

    if (accum < 1)
    {
        glow::print_line("hello", true);
    }
}

void testHueVarianceCurrent()
{
    set_real_time(true);
    Benchmark benchmark;
    benchmark.Begin("testHueVarianceCurrent");

    PutCurrent putter;
    ColorHSV hsv(0);

    Range(0, HSV_TEST_LIMIT).Spin(putter, hsv.Pack());
    benchmark.End();

    set_real_time(false);

    if (accum < 1)
    {
        glow::print_line("hello", true);
    }
}

void testHueVarianceNew()
{
    set_real_time(true);
    Benchmark benchmark;
    benchmark.Begin("testHueVarianceNew");

    PutNew putter;
    ColorHSV hsv(0);

    Range(0, HSV_TEST_LIMIT).Spin(putter, hsv.Pack());
    benchmark.End();

    set_real_time(false);

    if (accum < 1)
    {
        glow::print_line("hello", true);
    }
}

void testHSVFunctions()
{
    RUN_TEST(testHueVarianceOriginal);
    RUN_TEST(testHueVarianceCurrent);
    RUN_TEST(testHueVarianceNew);
}
