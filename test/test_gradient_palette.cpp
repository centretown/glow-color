// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "Benchmark.h"
#include "Color.h"
#include "Gradient.h"
#include "GradientPalette.h"

using glow::print_line;

using color::Color;
using color::color_pack;
using color::Gradient;
using color::GradientPalette;
using color::hue_limit;
using color::hue_size;
using color::luminance_size;
using color::saturation_size;
using color::VARY_HUE;
using color::VARY_LUMINANCE;
using color::VARY_SATURATION;

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
    GradientPalette palette(VARY_HUE);
    Gradient &hue = palette.Hue();
    Gradient &saturation = palette.Saturation();
    Gradient &luminance = palette.Luminance();

    TEST_ASSERT_EQUAL(hue_size, hue.Size());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Size());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Size());

    TEST_ASSERT_EQUAL(hue_size, hue.Length());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Length());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Length());

    TEST_ASSERT_EQUAL(VARY_HUE, palette.Vary());

    const uint16_t test_end = 40;
    Range range(0, test_end);
    TEST_ASSERT_EQUAL(test_end, range.Length());
    palette.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    palette.Refit();
    TEST_ASSERT_EQUAL(1, hue.Increment());

    Color color;
    Putter putter;
    range(0, 40);

    hue(hue_red, hue_yellow);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    color.Wheel(hue_red, 255, 255);
    putter(color.Pack(), "red to yellow");
    range.SpinValues(putter, palette);

    hue(hue_magenta, hue_limit + hue_yellow);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    color.Wheel(hue_magenta, 255, 255);
    putter(color.Pack(), "magenta to yellow");
    range.SpinValues(putter, palette);

    hue(hue_cyan, hue_blue);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(hue.Length() / range.Length(), hue.Increment());
    color.Wheel(hue_cyan, 255, 255);
    putter(color.Pack(), "cyan to blue");
    range.SpinValues(putter, palette);

    color.Wheel(hue_blue, 255, 255);
    putter(color.Pack(), "blue to cyan");
    range.SpinValues(putter, palette, true); // reverse
}

void testSaturationGradient()
{
    GradientPalette palette(VARY_SATURATION);
    Gradient &hue = palette.Hue();
    Gradient &saturation = palette.Saturation();
    Gradient &luminance = palette.Luminance();

    TEST_ASSERT_EQUAL(hue_size, hue.Size());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Size());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Size());

    TEST_ASSERT_EQUAL(hue_size, hue.Length());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Length());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Length());

    TEST_ASSERT_EQUAL(VARY_SATURATION, palette.Vary());

    Color color;
    Putter putter;
    const uint16_t test_end = 40;
    Range range(0, test_end);

    saturation(127, 255);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(saturation.Length() / range.Length(), saturation.Increment());
    color.Wheel(hue_red, 255, 255);
    putter(color.Pack(), "127 to 255");
    range.SpinValues(putter, palette);

    saturation(0, 127);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(saturation.Length() / range.Length(), saturation.Increment());
    color.Wheel(hue_red, 255, 255);
    putter(color.Pack(), "0 to 127");
    range.SpinValues(putter, palette);
}

void testLuminanceGradient()
{
    GradientPalette palette(VARY_LUMINANCE);
    Gradient &hue = palette.Hue();
    Gradient &saturation = palette.Saturation();
    Gradient &luminance = palette.Luminance();

    TEST_ASSERT_EQUAL(hue_size, hue.Size());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Size());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Size());

    TEST_ASSERT_EQUAL(hue_size, hue.Length());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Length());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Length());

    TEST_ASSERT_EQUAL(VARY_LUMINANCE, palette.Vary());

    Color color;
    Putter putter;
    const uint16_t test_end = 40;
    Range range(0, test_end);

    luminance(127, 255);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(saturation.Length() / range.Length(), saturation.Increment());
    color.Wheel(hue_red, 255, 127);
    putter(color.Pack(), "127 to 255");
    range.SpinValues(putter, palette);

    luminance(0, 127);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(saturation.Length() / range.Length(), saturation.Increment());
    color.Wheel(hue_red, 127, 0);
    putter(color.Pack(), "0 to 127");
    range.SpinValues(putter, palette);
}

void testGradientPalettes()
{
    RUN_TEST(testHueGradient);
    RUN_TEST(testSaturationGradient);
    RUN_TEST(testLuminanceGradient);
}
