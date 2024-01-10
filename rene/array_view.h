#pragma once

#include <span>

namespace rene {

template<typename T, std::size_t N = std::dynamic_extent>
using array_view = std::span<T,N>;

}
