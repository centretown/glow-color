// Copyright (c) 2022 Dave Marsh. See LICENSE.

// #define UNITY_INCLUDE_PRINT_FORMATTED
// #include <unity.h>
#include "Palette.h"

namespace color
{
    range_pack Palette::Span()
    {
        if (End() > size)
        {
            Range range(Pack());
            uint16_t diff = End() - size;
            // TEST_ASSERT_EQUAL(2, diff);
            if (diff > Begin())
            {
                uint16_t rem = diff - Begin();
                // TEST_ASSERT_EQUAL(2, rem);
                // shift Begin to zero
                range <<= diff - rem;
                // chop off the remainder
                range -= rem;
            }
            else
            {
                // shift until in bounds
                range <<= diff;
            }
            Pack(range.Pack());
        }
        return Pack();
    }

} // namespace color
