// // Copyright (c) 2022 Dave Marsh. See LICENSE.

// #pragma once

// #include "GradientPalette.h"

// namespace color
// {
//     template <typename T>
//     class Gradient : public GradientPalette
//     {
//     private:
//         T span;
//         const T limit = (T)-1;

//     public:
//         Gradient(color_hsv_pack pack = 0,
//                  bool gamma = false,
//                  T span = (T)-1)
//             : GradientPalette(pack, gamma), span(span) {}

//         Gradient(ColorHSV &colorHSV,
//                  bool gamma = false,
//                  T span = (T)-1)
//             : GradientPalette(colorHSV, gamma), span(span) {}

//         T Span() { return span; }
//         void Span(T v) { span = v; }

//     };

// } // namespace color
