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
RENE_ATTR_RW(2,1)
void scale(std::size_t size, T a[], T factor)
{
    for (size_t i = 0; i < size; ++i) {
        a[i] *= factor;
    }
}

template<typename T, std::size_t N>
    requires std::is_arithmetic_v<T>
void scale(std::span<T,N> a, T factor)
{
    T* data = a.data();
    assert(simd::is_aligned(data, N));
    data = assume_aligned<simd::align<T>(N)>(data);

    scale(a.size(), data, factor);
}

template<typename T, class Extents>
    requires std::is_arithmetic_v<T>
void scale(std::experimental::mdspan<T,Extents> a, T factor)
{
    T* data = a.data_handle();
    assert(simd::is_aligned(data, product_of_extents(a.extents())));
    data = assume_aligned<simd::align<T>(product_of_extents(Extents{}))>(data);

    scale(a.size(), data, factor);
}

} // namespace rene
