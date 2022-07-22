// // Copyright (c) 2022 Dave Marsh. See LICENSE.

// #define UNITY_INCLUDE_PRINT_FORMATTED

// #include <unity.h>

// #include "HueGradient.h"
// #include "SaturationGradient.h"
// #include "ValueGradient.h"

// using color::HueGradient;
// using color::SaturationGradient;

// void testGradientPaletteContructors()
// {
//     HueGradient hueGradient;
//     TEST_ASSERT_EQUAL(hue_limit, hueGradient.Span());
//     TEST_ASSERT_EQUAL(false, hueGradient.Gamma());
//     TEST_ASSERT_EQUAL(0, hueGradient.HSV().Pack());

//     ColorHSV colorHSV(23, 127, 127);
//     SaturationGradient satGradient(colorHSV, true, 25);
//     TEST_ASSERT_EQUAL(25, satGradient.Span());
//     TEST_ASSERT_EQUAL(true, satGradient.Gamma());
//     TEST_ASSERT_EQUAL(colorHSV.Pack(), satGradient.HSV().Pack());
//     TEST_ASSERT_EQUAL(colorHSV.Hue(), satGradient.HSV().Hue());
//     TEST_ASSERT_EQUAL(colorHSV.Saturation(), satGradient.HSV().Saturation());
//     TEST_ASSERT_EQUAL(colorHSV.Value(), satGradient.HSV().Value());

//     colorHSV.HSV(0x8000, 0xc0, 0x12);
//     ValueGradient valGradient(colorHSV.Pack(), false, 0x80);
//     TEST_ASSERT_EQUAL_HEX8(0x80, valGradient.Span());
//     TEST_ASSERT_EQUAL(false, valGradient.Gamma());
//     TEST_ASSERT_EQUAL_HEX32(colorHSV.Pack(), valGradient.HSV().Pack());
//     TEST_ASSERT_EQUAL_HEX16(colorHSV.Hue(), valGradient.HSV().Hue());
//     TEST_ASSERT_EQUAL_HEX8(colorHSV.Saturation(), valGradient.HSV().Saturation());
//     TEST_ASSERT_EQUAL_HEX8(colorHSV.Value(), valGradient.HSV().Value());
// }

// void testGradientPalette()
// {
// }

// void testGradientPalettes()
// {
//     RUN_TEST(testGradientPaletteContructors);
//     RUN_TEST(testGradientPalette);
// }