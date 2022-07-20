// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

uint16_t map_hue(uint16_t hue);
void map_hue_color(uint16_t hue,
                   uint8_t &r, uint8_t &g, uint8_t &b);
uint32_t apply_saturation_value(uint8_t sat, uint8_t val,
                                uint8_t r, uint8_t g, uint8_t b);
