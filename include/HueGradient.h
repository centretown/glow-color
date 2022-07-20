// // Copyright (c) 2022 Dave Marsh. See LICENSE.

// #pragma once

// #include "Gradient.h"

// namespace color
// {
//     class HueGradient : public Gradient<uint16_t>
//     // {
//     // public:
//     //     HueGradient(color_hsv_pack pack = 0,
//     //                        bool gamma = false,
//     //                        uint16_t span = (uint16_t)-1)
//     //         : Gradient(pack, gamma, span) {}

//     //     HueGradient(ColorHSV &colorHSV,
//     //                        bool gamma = false,
//     //                        uint16_t span = (uint16_t)-1)
//     //         : Gradient(colorHSV, gamma, span) {}

//     //     virtual color_pack Get(uint16_t index) { return 0; }
//     };

// } // namespace color

/*!
  @brief   Fill NeoPixel strip with one or more cycles of hues.
           Everyone loves the rainbow swirl so much, now it's canon!
  @param   first_hue   Hue of first pixel, 0-65535, representing one full
                       cycle of the color wheel. Each subsequent pixel will
                       be offset to complete one or more cycles over the
                       span of the strip.
  @param   reps        Number of cycles of the color wheel over the span
                       of the strip. Default is 1. Negative values can be
                       used to reverse the hue order.
  @param   saturation  Saturation (optional), 0-255 = gray to pure hue,
                       default = 255.
  @param   brightness  Brightness/value (optional), 0-255 = off to max,
                       default = 255. This is distinct and in combination
                       with any configured global strip brightness.
  @param   gammify     If true (default), apply gamma correction to colors
                       for better appearance.
*/
// void Adafruit_NeoPixel::rainbow(uint16_t first_hue, int8_t reps,
//   uint8_t saturation, uint8_t brightness, bool gammify) {
//   for (uint16_t i=0; i<numLEDs; i++) {
//     uint16_t hue = first_hue + (i * reps * 65536) / numLEDs;
//     uint32_t color = ColorHSV(hue, saturation, brightness);
//     if (gammify) color = gamma32(color);
//     setPixelColor(i, color);
//   }
// }
