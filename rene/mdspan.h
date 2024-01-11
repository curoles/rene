/*
 * https://github.com/kokkos/mdspan
 * https://stackoverflow.com/questions/75778573/what-is-an-mdspan-and-what-is-it-used-for
 */
#pragma once

#include <cstddef>
#include "experimental/mdspan"

namespace rene {

/*template<
    class ElementType,
    class Extents,
    class LayoutPolicy = std::experimental::layout_right,
    class AccessorPolicy = std::experimental::default_accessor<ElementType>
>
using tensor_view = std::experimental::mdspan<ElementType, Extents, LayoutPolicy, AccessorPolicy>;*/

template<class Extents>
concept MatrixExtents = requires(Extents extents) {
    extents.rank() == 2;
};

/*template<
    class ElementType,
    MatrixExtents Extents,
    class LayoutPolicy = std::experimental::layout_right,
    class AccessorPolicy = std::experimental::default_accessor<ElementType>
>
using matrix_view = std::experimental::mdspan<ElementType, Extents, LayoutPolicy, AccessorPolicy>;*/


template<class Extents>
concept VectorExtents = requires(Extents extents) {
    extents.rank() == 1;
};

/*template<
    class ElementType,
    VectorExtents Extents,
    class LayoutPolicy = std::experimental::layout_right,
    class AccessorPolicy = std::experimental::default_accessor<ElementType>
>
using vector_view = std::experimental::mdspan<ElementType, Extents, LayoutPolicy, AccessorPolicy>;*/

template<class Extents>
constexpr std::size_t product_of_extents(const Extents& e)
{
    std::size_t prod = 1;
    for (std::size_t r = 0; r < e.rank(); ++r) {
        prod *= static_cast<std::size_t>(e.extent(r));
    }
    return prod;
}

} // namespace rene
