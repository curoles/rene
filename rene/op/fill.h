/**@file
 * @brief
 * @author Igor Lesik 2024
 * @copyright 2024 Igor Lesik
 *
 */
#pragma once

#include <span>

#include "rene/mdspan.h"
#include "rene/gnu_attributes.h"
#include "rene/simd_align.h"

namespace rene {

template<typename T>
    requires std::is_arithmetic_v<T>
RENE_ATTR_WO(2,1)
void fill(std::size_t size, T a[], T filler)
{
    for (size_t i = 0; i < size; ++i) {
        a[i] = filler;
    }
}

template<typename T, std::size_t N>
    requires std::is_arithmetic_v<T>
void fill(std::span<T,N> a, T filler)
{
    T* data = a.data();
    SPAN_HINT_ALIGN(data, N)

    fill(a.size(), data, filler);
}

template<typename T, class Extents>
    requires std::is_arithmetic_v<T>
void fill(std::experimental::mdspan<T,Extents> a, T filler)
{
    T* data = a.data_handle();
    MDSPAN_HINT_ALIGN(data, Extents)

    fill(a.size(), data, filler);
}

} // namespace rene
