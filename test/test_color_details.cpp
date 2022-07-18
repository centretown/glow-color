// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"

#include "Color.h"

using color::Color;
using color::color_element;
using color::color_pack;
using color::color_rgbw;

void testColorDetail()
{
    TEST_ASSERT_EQUAL_HEX(sizeof(uint32_t), sizeof(Color));

    const uint8_t tRed = 0xef;
    const uint8_t tGreen = 0x43;
    const uint8_t tBlue = 0x21;
    const uint8_t tWhite = 0x99;
    Color color;
    TEST_ASSERT_EQUAL(0, color.Red());
    TEST_ASSERT_EQUAL(0, color.Green());
    TEST_ASSERT_EQUAL(0, color.Blue());
    TEST_ASSERT_EQUAL(0, color.White());

    color.Red(tRed);
    TEST_ASSERT_EQUAL(tRed, color.Red());
    color.Green(tGreen);
    TEST_ASSERT_EQUAL(tGreen, color.Green());
    color.Blue(tBlue);
    TEST_ASSERT_EQUAL(tBlue, color.Blue());
    color.White(tWhite);
    TEST_ASSERT_EQUAL(tWhite, color.White());

    TEST_ASSERT_EQUAL(tRed, color.Red());
    TEST_ASSERT_EQUAL(tGreen, color.Green());
    TEST_ASSERT_EQUAL(tBlue, color.Blue());
    TEST_ASSERT_EQUAL(tWhite, color.White());

    Color other(color);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(tWhite, other.White());

    other.RGB();
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.Copy(color);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(tWhite, other.White());

    other.RGBW();
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.RGBW(tRed, tGreen, tBlue, tWhite);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(tWhite, other.White());

    other.RGB();
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.RGB(tRed);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.GBR(tGreen, tBlue);
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());
}

void testColorOperators()
{
    const uint8_t tRed = 15;
    const uint8_t tGreen = 23;
    const uint8_t tBlue = 44;
    const uint8_t tWhite = 244;
    Color source(tRed, tGreen, tBlue, tWhite);
    Color target = source;

    TEST_ASSERT_EQUAL(tRed, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());

    TEST_ASSERT_EQUAL(tRed, target.Red());
    TEST_ASSERT_EQUAL(tGreen, target.Green());
    TEST_ASSERT_EQUAL(tBlue, target.Blue());
    TEST_ASSERT_EQUAL(tWhite, target.White());

    target = 0;
    TEST_ASSERT_EQUAL(0, target.Red());
    TEST_ASSERT_EQUAL(0, target.Green());
    TEST_ASSERT_EQUAL(0, target.Blue());
    TEST_ASSERT_EQUAL(0, target.White());

    target = source;
    TEST_ASSERT_EQUAL(tRed, target.Red());
    TEST_ASSERT_EQUAL(tGreen, target.Green());
    TEST_ASSERT_EQUAL(tBlue, target.Blue());
    TEST_ASSERT_EQUAL(tWhite, target.White());

    target = 0;
    TEST_ASSERT_EQUAL(0, target.Red());
    TEST_ASSERT_EQUAL(0, target.Green());
    TEST_ASSERT_EQUAL(0, target.Blue());
    TEST_ASSERT_EQUAL(0, target.White());

    target(tRed, 0, 0);
    TEST_ASSERT_EQUAL(tRed, target.Red());
    TEST_ASSERT_EQUAL(0, target.Green());
    TEST_ASSERT_EQUAL(0, target.Blue());
    TEST_ASSERT_EQUAL(0, target.White());

    target(tRed, tBlue, 0);
    TEST_ASSERT_EQUAL(tRed, target.Red());
    TEST_ASSERT_EQUAL(tBlue, target.Green());
    TEST_ASSERT_EQUAL(0, target.Blue());
    TEST_ASSERT_EQUAL(0, target.White());

    source = 0;
    target = source(tRed, tGreen, tBlue, tWhite);
    TEST_ASSERT_EQUAL(tRed, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());
    TEST_ASSERT_EQUAL(tRed, target.Red());
    TEST_ASSERT_EQUAL(tGreen, target.Green());
    TEST_ASSERT_EQUAL(tBlue, target.Blue());
    TEST_ASSERT_EQUAL(tWhite, target.White());

    target = 0;
    target = source;
    TEST_ASSERT_EQUAL(tRed, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());
    TEST_ASSERT_EQUAL(tRed, target.Red());
    TEST_ASSERT_EQUAL(tGreen, target.Green());
    TEST_ASSERT_EQUAL(tBlue, target.Blue());
    TEST_ASSERT_EQUAL(tWhite, target.White());

    target = 0;
    target = source(0, 0, tBlue);
    TEST_ASSERT_EQUAL(0, source.Red());
    TEST_ASSERT_EQUAL(0, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(0, source.White());
    TEST_ASSERT_EQUAL(0, target.Red());
    TEST_ASSERT_EQUAL(0, target.Green());
    TEST_ASSERT_EQUAL(tBlue, target.Blue());
    TEST_ASSERT_EQUAL(0, target.White());

    target(0, 0, 0, tWhite);
    TEST_ASSERT_EQUAL(0, target.Red());
    TEST_ASSERT_EQUAL(0, target.Green());
    TEST_ASSERT_EQUAL(0, target.Blue());
    TEST_ASSERT_EQUAL(tWhite, target.White());
}

void testColorElements()
{
    const uint8_t tRed = 99;
    const uint8_t tGreen = 83;
    const uint8_t tBlue = 144;
    const uint8_t tWhite = 2;

    Color source;
    source(tRed, tGreen, tBlue, tWhite);
    TEST_ASSERT_EQUAL(tRed, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());

    color_element &red = source.RED();
    color_element &green = source.GREEN();
    color_element &blue = source.BLUE();
    color_element &white = source.WHITE();

    TEST_ASSERT_EQUAL(tRed, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tBlue, blue);
    TEST_ASSERT_EQUAL(tWhite, white);

    red = blue = white = tGreen;
    TEST_ASSERT_EQUAL(tGreen, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tGreen, blue);
    TEST_ASSERT_EQUAL(tGreen, white);

    source(0);

    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(0, green);
    TEST_ASSERT_EQUAL(0, blue);
    TEST_ASSERT_EQUAL(0, white);

    red = tRed;
    TEST_ASSERT_EQUAL(tRed, red);
    TEST_ASSERT_EQUAL(0, green);
    TEST_ASSERT_EQUAL(0, blue);
    TEST_ASSERT_EQUAL(0, white);

    source = 0;
    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(0, green);
    TEST_ASSERT_EQUAL(0, blue);
    TEST_ASSERT_EQUAL(0, white);

    green = tGreen;
    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(0, blue);
    TEST_ASSERT_EQUAL(0, white);

    blue = tBlue;
    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tBlue, blue);
    TEST_ASSERT_EQUAL(0, white);

    white = tWhite;
    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tBlue, blue);
    TEST_ASSERT_EQUAL(tWhite, white);

    red = tRed;
    TEST_ASSERT_EQUAL(tRed, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tBlue, blue);
    TEST_ASSERT_EQUAL(tWhite, white);

    TEST_ASSERT_EQUAL(tRed, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());

    red &= 0;
    TEST_ASSERT_EQUAL(0, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());

    red |= tRed;
    TEST_ASSERT_EQUAL(tRed, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tBlue, blue);
    TEST_ASSERT_EQUAL(tWhite, white);

    red ^= tRed;
    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tBlue, blue);
    TEST_ASSERT_EQUAL(tWhite, white);

    TEST_ASSERT_EQUAL(0, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());

    blue = red;
    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(0, blue);
    TEST_ASSERT_EQUAL(tWhite, white);

    TEST_ASSERT_EQUAL(0, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(0, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());

    blue = tBlue;
    TEST_ASSERT_EQUAL(0, red);
    TEST_ASSERT_EQUAL(tGreen, green);
    TEST_ASSERT_EQUAL(tBlue, blue);
    TEST_ASSERT_EQUAL(tWhite, white);

    TEST_ASSERT_EQUAL(0, source.Red());
    TEST_ASSERT_EQUAL(tGreen, source.Green());
    TEST_ASSERT_EQUAL(tBlue, source.Blue());
    TEST_ASSERT_EQUAL(tWhite, source.White());

    source.WHITE() = 255;
    TEST_ASSERT_EQUAL(255, source.White());

    source.WHITE() ^= 255;
    TEST_ASSERT_EQUAL(0, source.White());

    source.WHITE() |= 255;
    TEST_ASSERT_EQUAL(255, source.White());

    source.WHITE() &= 15;
    TEST_ASSERT_EQUAL(15, source.White());
}

void testColorDetails()
{
    RUN_TEST(testColorDetail);
}