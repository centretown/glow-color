// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "Benchmark.h"
#include "Color.h"
#include "Gradient.h"
#include "GradientPalette.h"

using glow::print_line;

using color::CHANGE_HUE;
using color::CHANGE_LUMINANCE;
using color::CHANGE_SATURATION;
using color::Color;
using color::color_pack;
using color::Gradient;
using color::GradientPalette;
using color::hue_limit;
using color::hue_size;
using color::luminance_size;
using color::saturation_size;

using color::hue_blue;
using color::hue_cyan;
using color::hue_green;
using color::hue_limit;
using color::hue_magenta;
using color::hue_red;
using color::hue_yellow;

uint32_t accum = 0;

struct Putter
{
    const char *label = "";
    char buffer[80];
    Color first, last;
    uint16_t counter = 0;

    void operator()(color_pack c, const char *l)
    {
        first = c;
        label = l;
        counter = 0;
    }

    void Put(uint16_t index, color_pack color)
    {
        last(color);
        accum += color;
        counter++;
    }

    void Update()
    {
        snprintf(buffer, sizeof(buffer),
                 "%s %u\n\tr=%u,g=%u,b=%u -> r=%u,g=%u,b=%u\n",
                 label, counter,
                 first.Red(),
                 first.Green(),
                 first.Blue(),
                 last.Red(),
                 last.Green(),
                 last.Blue());
        print_line(buffer);
    }
};

void testHueGradient()
{
    GradientPalette palette(CHANGE_HUE);
    Gradient &hue = palette.Hue();
    Gradient &saturation = palette.Saturation();
    Gradient &luminance = palette.Luminance();

    TEST_ASSERT_EQUAL(hue_size, hue.Size());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Size());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Size());

    TEST_ASSERT_EQUAL(hue_size, hue.Length());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Length());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Length());

    TEST_ASSERT_EQUAL(CHANGE_HUE, palette.Change());

    const uint16_t test_end = 40;
    Range range(0, test_end);
    TEST_ASSERT_EQUAL(test_end, range.Length());
    hue.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    hue.Refit();
    TEST_ASSERT_EQUAL(1, hue.Increment());

    Color color;
    Putter putter;
    range(0, 40);

    hue(hue_red, hue_yellow);
    hue.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    color.Wheel(hue_red, 255, 255);
    putter(color.Pack(), "red to yellow");
    range.SpinValues(putter, palette);

    hue(hue_magenta, hue_limit + hue_yellow);
    hue.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    color.Wheel(hue_magenta, 255, 255);
    putter(color.Pack(), "magenta to yellow");
    range.SpinValues(putter, palette);

    hue(hue_cyan, hue_blue);
    hue.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    color.Wheel(hue_cyan, 255, 255);
    putter(color.Pack(), "cyan to blue");
    range.SpinValues(putter, palette);

    color.Wheel(hue_blue, 255, 255);
    putter(color.Pack(), "blue to cyan");
    range.SpinValues(putter, palette, true);
}

void testSaturationGradient()
{
    GradientPalette palette(CHANGE_SATURATION);
    Gradient &hue = palette.Hue();
    Gradient &saturation = palette.Saturation();
    Gradient &luminance = palette.Luminance();

    TEST_ASSERT_EQUAL(hue_size, hue.Size());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Size());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Size());

    TEST_ASSERT_EQUAL(hue_size, hue.Length());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Length());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Length());

    TEST_ASSERT_EQUAL(CHANGE_SATURATION, palette.Change());
}

void testLuminanceGradient()
{
    GradientPalette palette(CHANGE_LUMINANCE);
    Gradient &hue = palette.Hue();
    Gradient &saturation = palette.Saturation();
    Gradient &luminance = palette.Luminance();

    TEST_ASSERT_EQUAL(hue_size, hue.Size());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Size());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Size());

    TEST_ASSERT_EQUAL(hue_size, hue.Length());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Length());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Length());

    TEST_ASSERT_EQUAL(CHANGE_LUMINANCE, palette.Change());
}

void testGradientPalettes()
{
    RUN_TEST(testHueGradient);
    RUN_TEST(testSaturationGradient);
    RUN_TEST(testLuminanceGradient);
}
