#pragma once

#include <span>

#define RENE_ATTR_WO(ref_index, size_index) __attribute__((access(write_only, ref_index, size_index)))

namespace rene {

template<typename T, std::size_t N = std::dynamic_extent>
using array_view = std::span<T,N>;

}
