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
RENE_ATTR_RW(2,1) RENE_ATTR_RO(3,1)
void add(std::size_t size, T a[], const T b[])
{
    for (size_t i = 0; i < size; ++i) {
        a[i] += b[i];
    }
}

template<typename T, std::size_t N>
    requires std::is_arithmetic_v<T>
void add(std::span<T,N> a, std::span<const T,N> b)
{
    T* a_data = a.data();
    SPAN_HINT_ALIGN(a_data, N)
    T const* b_data = b.data();
    SPAN_HINT_ALIGN(b_data, N)

    add(a.size(), a_data, b_data);
}

template<typename T, class Extents>
    requires std::is_arithmetic_v<T>
void add(std::experimental::mdspan<T,Extents> a, std::experimental::mdspan<const T,Extents> b)
{
    T* a_data = a.data_handle();
    MDSPAN_HINT_ALIGN(a_data, Extents)
    T const* b_data = b.data_handle();
    MDSPAN_HINT_ALIGN(b_data, Extents)

    add(a.size(), a_data, b_data);
}

} // namespace rene
