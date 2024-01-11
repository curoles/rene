#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace rene {

template<size_t alignment, typename T>
T* assume_aligned(T* p)
{
    static_assert(alignment >= alignof(T));
    static_assert(std::has_single_bit(alignment));
    return reinterpret_cast<T*>(__builtin_assume_aligned(p, alignment));
}

} // namespace rene


namespace rene::simd {

constexpr std::size_t max_vlen =
#ifdef __x86_64__
    #ifdef __AVX512F__
        64
    #elif defined(__AVX2__)
        32
    #elif defined(__AVX__)
        16
    #else
        8
    #endif
#else
    8
#endif
;

constexpr std::size_t align_(std::size_t value_size, std::size_t count, std::size_t vlen) {
    return ((value_size * count) >= vlen)?
        vlen :
        (vlen/2 <= value_size)? value_size : simd::align_(value_size, count, vlen/2);
}

constexpr std::size_t align(std::size_t value_size, std::size_t count) {
    return simd::align_(value_size, count, simd::max_vlen);
}

template<typename T>
constexpr std::size_t align(std::size_t count) {
    return simd::align(sizeof(T), count);
}

template<typename T>
constexpr bool is_aligned(T* ptr, std::size_t count) {
    return ((uintptr_t)ptr & (simd::align<T>(count) - 1)) == 0;
}

} // namespace rene::simd
