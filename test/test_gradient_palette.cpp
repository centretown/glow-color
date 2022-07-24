// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "HueGradient.h"
#include "HSV.h"
#include "ColorHSV.h"
// #include "SaturationGradient.h"
// #include "ValueGradient.h"

using color::Color;
using color::color_hsv_pack;
using color::ColorHSV;
using color::hue_limit;
using color::HueGradient;
using color::ToRGB;
// using color::SaturationGradient;

void testHueGradient()
{
    ColorHSV colorHSV(0, 15, 15);
    HueGradient hueGradient(colorHSV.Pack());
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Size());
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Length());
    hueGradient.Span(0, 128);
    // hueGradient(0, 128);
    TEST_ASSERT_EQUAL(128, hueGradient.Length());

    Color color(hueGradient.Map(0));
    Color expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());
    TEST_ASSERT_EQUAL(expected.Red(), color.Red());
    TEST_ASSERT_EQUAL(expected.Green(), color.Green());
    TEST_ASSERT_EQUAL(expected.Blue(), color.Blue());

    colorHSV.Hue(1);
    color(hueGradient.Map(1));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    colorHSV.Hue(127);
    color(hueGradient.Map(127));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    colorHSV.Hue(0);
    color(hueGradient.Map(128));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    hueGradient(0, 129);
    colorHSV.Hue(128);
    color(hueGradient.Map(128));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    hueGradient(128, 256);
    TEST_ASSERT_EQUAL(128, hueGradient.Begin());
    TEST_ASSERT_EQUAL(256, hueGradient.End());
    hueGradient.Span();
    TEST_ASSERT_EQUAL(128, hueGradient.Begin());
    TEST_ASSERT_EQUAL(256, hueGradient.End());

    ++hueGradient;
    TEST_ASSERT_EQUAL(128, hueGradient.Begin());
    TEST_ASSERT_EQUAL(257, hueGradient.End());

    hueGradient -= 128;
    TEST_ASSERT_EQUAL(128, hueGradient.Begin());
    TEST_ASSERT_EQUAL(129, hueGradient.End());
    TEST_ASSERT_EQUAL(1, hueGradient.Length());
    hueGradient.Span();
    TEST_ASSERT_EQUAL(128, hueGradient.Begin());
    TEST_ASSERT_EQUAL(129, hueGradient.End());
    TEST_ASSERT_EQUAL(1, hueGradient.Length());

    hueGradient(0, hue_limit + 2);
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Size());
    TEST_ASSERT_EQUAL(0, hueGradient.Begin());
    TEST_ASSERT_EQUAL(hue_limit + 2, hueGradient.End());
    TEST_ASSERT_EQUAL(hue_limit + 2, hueGradient.Length());
    hueGradient.Span();
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Size());
    TEST_ASSERT_EQUAL(0, hueGradient.Begin());
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.End());
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Length());

    hueGradient(512, hue_limit + 2);
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Size());
    TEST_ASSERT_EQUAL(512, hueGradient.Begin());
    TEST_ASSERT_EQUAL(hue_limit + 2, hueGradient.End());
    TEST_ASSERT_EQUAL(hue_limit + 2 - hueGradient.Begin(), hueGradient.Length());
    hueGradient.Span();
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Size());
    TEST_ASSERT_EQUAL(510, hueGradient.Begin());
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.End());
    TEST_ASSERT_EQUAL(hue_limit - hueGradient.Begin(), hueGradient.Length());

    hueGradient(15, hue_limit - 15);
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Size());
    TEST_ASSERT_EQUAL(15, hueGradient.Begin());
    TEST_ASSERT_EQUAL(hue_limit - 15, hueGradient.End());
    TEST_ASSERT_EQUAL(hue_limit - 30, hueGradient.Length());
    hueGradient.Span();
    TEST_ASSERT_EQUAL(hue_limit, hueGradient.Size());
    TEST_ASSERT_EQUAL(15, hueGradient.Begin());
    TEST_ASSERT_EQUAL(hue_limit - 15, hueGradient.End());
    TEST_ASSERT_EQUAL(hue_limit - 30, hueGradient.Length());
    TEST_ASSERT_EQUAL(1500, hueGradient.Length());

    Range range(0, 30);
    uint16_t increment = hueGradient.Fit(range.Pack());
    TEST_ASSERT_EQUAL(hueGradient.Length() / range.Length(), increment);
    increment = hueGradient.Refit();
    TEST_ASSERT_EQUAL(1, increment);
}

void testGradientPalettes()
{
    RUN_TEST(testHueGradient);
}
