#pragma once

#include "rene/array_view.h"
#include "rene/gnu_attributes.h"

namespace rene {

template<typename T>
    requires std::is_arithmetic_v<T>
RENE_ATTR_WO(2,1)
void array_scale(std::size_t size, T a[], T factor) {
    for (size_t i = 0; i < size; ++i) {
        a[i] = a[i] * factor;
    }
}

template<typename T, std::size_t N>
    requires std::is_arithmetic_v<T>
array_view<T,N> array_scale(array_view<T,N> a, T factor) {
    array_scale(a.size(), a.data(), factor);
    return a;
}

}
