/*
 * https://github.com/kokkos/mdspan
 * https://stackoverflow.com/questions/75778573/what-is-an-mdspan-and-what-is-it-used-for
 */
#pragma once

//#include <mdspan>
#include <cstddef>

namespace rene {

template<typename T, std::size_t NDIM>
class mdarray
{
public:
    T* data;
    size_t size;

public:
    ~mdarray() = default;

    mdarray() = default;

    mdarray(const mdarry&) = default;

};

//using vector=
//using matrix

}
