/**@file
 * @brief     Generalized number 1
 * @author    Igor Lesik 2024
 * @copyright 2024 Igor Lesik
 *
 */
#pragma once

#include <type_traits>

namespace rene {

template<typename T>
inline constexpr T identity_number() {
    if constexpr (std::is_integral<T>::value) {
        return 1;
    }
    else if constexpr (std::is_floating_point<T>::value) {
        return 1.0;
    }
    else {
        return 1;
    }
};


} // namespace rene