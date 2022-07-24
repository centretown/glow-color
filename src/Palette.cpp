// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Palette.h"

namespace color
{
    range_pack Palette::Span()
    {
        if (End() > size)
        {
            Range range(Pack());
            uint16_t diff = End() - size;
            if (diff > Begin())
            {
                uint16_t rem = diff - Begin();
                // shift Begin to zero
                range <<= rem;
                // chop off the remainder
                range -= diff - rem;
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
