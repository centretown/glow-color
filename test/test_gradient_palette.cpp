// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "HSV.h"
#include "Wheel.h"
#include "HueGradient.h"
#include "SaturationGradient.h"
#include "ValueGradient.h"

using color::Color;
using color::color_hsv_pack;
using color::Wheel;
using color::hue_limit;
using color::HueGradient;
using color::saturation_limit;
using color::SaturationGradient;
using color::ToRGB;
using color::value_limit;
using color::ValueGradient;

template <typename GRADIENT, typename PUTTTER>
void testGradient(Wheel &colorHSV, PUTTTER &PUT, uint16_t LIMIT)
{
    GRADIENT gradient(colorHSV.Pack());
    TEST_ASSERT_EQUAL(LIMIT, gradient.Size());
    TEST_ASSERT_EQUAL(LIMIT, gradient.Length());
    gradient.Span(0, 128);
    TEST_ASSERT_EQUAL(128, gradient.Length());

    Color color(gradient.Map(0));
    Color expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());
    TEST_ASSERT_EQUAL(expected.Red(), color.Red());
    TEST_ASSERT_EQUAL(expected.Green(), color.Green());
    TEST_ASSERT_EQUAL(expected.Blue(), color.Blue());

    // colorHSV.Hue(1);
    PUT(1);
    color(gradient.Map(1));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    // colorHSV.Hue(127);
    PUT(127);
    color(gradient.Map(127));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    // colorHSV.Hue(0);
    PUT(0);
    color(gradient.Map(128));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    gradient(0, 129);
    // colorHSV.Hue(128);
    PUT(128);
    color(gradient.Map(128));
    expected(ToRGB(colorHSV.Pack()));
    TEST_ASSERT_EQUAL(expected.Pack(), color.Pack());

    gradient(128, LIMIT);
    TEST_ASSERT_EQUAL(128, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT, gradient.End());
    gradient.Span();
    TEST_ASSERT_EQUAL(128, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT, gradient.End());

    ++gradient;
    TEST_ASSERT_EQUAL(128, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT + 1, gradient.End());
    gradient.Span();
    TEST_ASSERT_EQUAL(127, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT, gradient.End());

    gradient -= 127;
    TEST_ASSERT_EQUAL(127, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT - 127, gradient.End());

    gradient(0, LIMIT + 2);
    TEST_ASSERT_EQUAL(LIMIT, gradient.Size());
    TEST_ASSERT_EQUAL(0, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT + 2, gradient.End());
    TEST_ASSERT_EQUAL(LIMIT + 2, gradient.Length());
    gradient.Span();
    TEST_ASSERT_EQUAL(LIMIT, gradient.Size());
    TEST_ASSERT_EQUAL(0, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT, gradient.End());
    TEST_ASSERT_EQUAL(LIMIT, gradient.Length());

    gradient(0, LIMIT + 2);
    TEST_ASSERT_EQUAL(LIMIT, gradient.Size());
    TEST_ASSERT_EQUAL(0, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT + 2, gradient.End());
    TEST_ASSERT_EQUAL(LIMIT + 2, gradient.Length());
    gradient.Span();
    TEST_ASSERT_EQUAL(LIMIT, gradient.Size());
    TEST_ASSERT_EQUAL(0, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT, gradient.End());
    TEST_ASSERT_EQUAL(LIMIT, gradient.Length());

    gradient(15, LIMIT - 15);
    TEST_ASSERT_EQUAL(LIMIT, gradient.Size());
    TEST_ASSERT_EQUAL(15, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT - 15, gradient.End());
    TEST_ASSERT_EQUAL(LIMIT - 30, gradient.Length());
    gradient.Span();
    TEST_ASSERT_EQUAL(LIMIT, gradient.Size());
    TEST_ASSERT_EQUAL(15, gradient.Begin());
    TEST_ASSERT_EQUAL(LIMIT - 15, gradient.End());
    TEST_ASSERT_EQUAL(LIMIT - 30, gradient.Length());
    TEST_ASSERT_EQUAL(LIMIT - 30, gradient.Length());

    Range range(0, 30);
    uint16_t increment = gradient.Fit(range.Pack());
    TEST_ASSERT_EQUAL(gradient.Length() / range.Length(), increment);
    increment = gradient.Refit();
    TEST_ASSERT_EQUAL(1, increment);
}

void testHueGradient()
{
    Wheel colorHSV(0);
    auto put = [&](uint16_t v)
    {
        colorHSV.Hue(v);
    };
    testGradient<HueGradient>(colorHSV, put, hue_limit);
}

void testSaturationGradient()
{
    Wheel colorHSV(0);
    auto put = [&](uint16_t v)
    {
        colorHSV.Saturation(v);
    };
    testGradient<SaturationGradient>(colorHSV, put, saturation_limit);
}

void testValueGradient()
{
    Wheel colorHSV(0);
    auto put = [&](uint16_t v)
    {
        colorHSV.Value(v);
    };
    testGradient<ValueGradient>(colorHSV, put, value_limit);
}

void testGradientPalettes()
{
    RUN_TEST(testHueGradient);
    RUN_TEST(testSaturationGradient);
    RUN_TEST(testValueGradient);
}
