/**@file
 * @brief  SIMD vector types defined with `__attribute__ ((vector_size ...`.
 * @author Igor Lesik 2022-2024
 * @copyright Igor Lesik 2024
 *
 */
#pragma once

#include <functional>

#include "rene/type_short_name.h"
#include "rene/gnu_attributes.h"

namespace rene::simd {

/// Compile-time SIMD vector type maker.
///
/// Metaprogramming facility to construct SIMD vector type in compile-time.
/// ```c++
/// simd::make<float,8>::type my_simd_vector;
/// static_assert(std::is_same<simd::F32x8, decltype(my_simd_vector)>::value);
/// ```
///
template <typename T, unsigned N> struct make {typedef void type;};


#define DEF_SIMD_VEC(Type,count) \
using Type##x##count = rene::Type RENE_ATTR_VEC(Type, count); \
/** Specialize template make<Type,count>::type */ \
template <> struct make<Type,count> {typedef simd::Type##x##count type;};

#define DEF_SIMD_VEC2(type)  DEF_SIMD_VEC(type, 2)
#define DEF_SIMD_VEC4(type)  DEF_SIMD_VEC(type, 4)  DEF_SIMD_VEC2(type)
#define DEF_SIMD_VEC8(type)  DEF_SIMD_VEC(type, 8)  DEF_SIMD_VEC4(type)
#define DEF_SIMD_VEC16(type) DEF_SIMD_VEC(type, 16) DEF_SIMD_VEC8(type)
#define DEF_SIMD_VEC32(type) DEF_SIMD_VEC(type, 32) DEF_SIMD_VEC16(type)
#define DEF_SIMD_VEC64(type) DEF_SIMD_VEC(type, 64) DEF_SIMD_VEC32(type)

DEF_SIMD_VEC64(u8) 
DEF_SIMD_VEC64(i8) 
DEF_SIMD_VEC32(u16)
DEF_SIMD_VEC32(i16)
DEF_SIMD_VEC16(u32)
DEF_SIMD_VEC16(i32)
DEF_SIMD_VEC16(f32)
DEF_SIMD_VEC8 (u64)
DEF_SIMD_VEC8 (i64)
DEF_SIMD_VEC8 (f64)
DEF_SIMD_VEC4 (u128)
DEF_SIMD_VEC4 (i128)


#undef DEF_SIMD_VEC
#undef DEF_SIMD_VEC2
#undef DEF_SIMD_VEC4
#undef DEF_SIMD_VEC8
#undef DEF_SIMD_VEC16
#undef DEF_SIMD_VEC32
#undef DEF_SIMD_VEC64

/// Get SIMD vector element value type.
///
/// Example:
/// ```c++
/// static_assert(std::is_same_v<float, simd::value_type<simd::f32x8>::type>);
/// ```
///
template <typename T>
struct value_type {
    using type = decltype(((T){})[0]);
};

/// Get SIMD vector length (number of elements).
///
/// Example:
/// ```c++
/// static_assert(simd::len<simd::u32x8>() == 8 and sizeof(simd::u32x8) == (4*8));
/// ```
///
/// Example:
/// ```c++
///    simd::u64x8 v;
///    static_assert(simd::len<decltype(v)>() == 8);
/// ```
template <typename T>
constexpr std::size_t len()
{
    return sizeof(T)/sizeof(typename value_type<T>::type);
}

/// Get SIMD vector length (number of elements).
///
/// Example:
/// ```c++
///    simd::u64x8 v;
///    static_assert(simd::len(v) == 8);
/// ```
template <typename T>
constexpr std::size_t len(T&)
{
    return simd::len<T>();
}

template<typename VT/*, typename... Args*/>
using foreach_fun_t = std::function<void(typename simd::value_type<VT>::type, std::size_t i/*, Args...*/)>;

template<typename VT/*, typename... Args*/>
void foreach(VT v, foreach_fun_t<VT/*,Args...*/> fun/*, Args... args*/)
{
    for (std::size_t i = 0; i < simd::len(v); ++i) {
        fun(v[i], i/*, args...*/);
    }
}

template<typename VT> concept IsIntegral = std::is_integral_v<typename simd::value_type<VT>::type>;
template<typename VT> concept IsSignedIntegral = std::is_integral_v<typename simd::value_type<VT>::type>
                                                && std::is_signed_v<typename simd::value_type<VT>::type>;
template<typename VT> concept IsFloatingPoint = std::is_floating_point_v<typename simd::value_type<VT>::type>;

} // end namespace simd
