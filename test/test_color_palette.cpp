// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "Color.h"
#include "ColorPalette.h"

using color::Color;
using color::color_pack;
using color::ColorPalette;

void testColorPalette()
{
    const uint8_t tRed = 0x33;
    const uint8_t tGreen = 0x18;
    const uint8_t tBlue = 0xf0;

    Color c0(tRed, 0, 0);
    Color c1(tRed, tGreen, 0);
    Color c2(tRed, tGreen, tBlue);
    Color c3(0, tGreen, tBlue);
    Color c4(0, 0, tBlue);

    color_pack palette[] = {
        c0.Pack(),
        c1.Pack(),
        c2.Pack(),
        c3.Pack(),
        c4.Pack(),
    };

    uint16_t length = sizeof(palette) / sizeof(palette[0]);
    ColorPalette colorPalette(palette, length, false);

    TEST_ASSERT_EQUAL_HEX(5, colorPalette.Length());
    TEST_ASSERT_EQUAL_HEX(c0.Pack(), colorPalette.Map(0));
    TEST_ASSERT_EQUAL_HEX(c1.Pack(), colorPalette.Map(1));
    TEST_ASSERT_EQUAL_HEX(c2.Pack(), colorPalette.Map(2));
    TEST_ASSERT_EQUAL_HEX(c3.Pack(), colorPalette.Map(3));
    TEST_ASSERT_EQUAL_HEX(c4.Pack(), colorPalette.Map(4));
    TEST_ASSERT_EQUAL_HEX(c0.Pack(), colorPalette.Map(5));
    TEST_ASSERT_EQUAL_HEX(c1.Pack(), colorPalette.Map(6));

    Color color2(colorPalette.Map(2));
    TEST_ASSERT_EQUAL_HEX(c2.Red(), color2.Red());
    TEST_ASSERT_EQUAL_HEX(c2.Green(), color2.Green());
    TEST_ASSERT_EQUAL_HEX(c2.Blue(), color2.Blue());
    TEST_ASSERT_EQUAL_HEX(c2.White(), color2.White());
}

void testColorPalettes()
{
    RUN_TEST(testColorPalette);
}
