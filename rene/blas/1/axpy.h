/**@file
 * @brief     BLAS "axpy" is y ← 𝛼x + y
 * @author    Igor Lesik 2024
 * @copyright 2024 Igor Lesik
 *
 */
#pragma once

#include <span>

#include "rene/mdspan.h"
#include "rene/gnu_attributes.h"
#include "rene/simd_align.h"
#include "rene/identity_number.h"

namespace rene::blas {

/** y ← 𝛼x + y
 * 
 */
template<typename T>
    requires std::is_arithmetic_v<T>
RENE_ATTR_RW(2,1) RENE_ATTR_RO(3,1)
void axpy(std::size_t size, T x[], const T y[], T a)
{
    if (a == identity_number<T>()) {
        for (size_t i = 0; i < size; ++i) {
            x[i] = x[i] + y[i];
        }
    }
    else {
        for (size_t i = 0; i < size; ++i) {
            x[i] = a*x[i] + y[i];
        }
    }
}

/** y ← 𝛼x + y
 * 
 */
template<typename T, std::size_t N>
    requires std::is_arithmetic_v<T>
void axpy(T a, std::span<T,N> x, std::span<const T,N> y)
{
    if constexpr (N == std::dynamic_extent) {
        assert(x.size() <= y.size());
    }
    T* x_data = x.data();
    SPAN_HINT_ALIGN(x_data, N)
    T const* y_data = y.data();
    SPAN_HINT_ALIGN(y_data, N)

    axpy(x.size(), x_data, y_data, a);
}

} // namespace rene::blas