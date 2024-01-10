#include <span>
#include <vector>
#include <cassert>
#include <cstdlib>
//#include <cstdio>

#include "rene/array_view.h"
#include "rene/simd_types.h"
#include "rene/mdspan.h"

using rene::array_view;
using namespace rene;

template<typename T, std::size_t N>
static void fn_with_array_view_arg(std::span<T,N> a)
{
}

static void fn_with_int_array_view_arg(std::span<int> a)
{
}

static void test_c_array()
{
    alignas(simd::i32x8) int a[]{1, 2, 3, 4};

    array_view av(a);
    fn_with_array_view_arg(av);

    fn_with_array_view_arg(std::span(a));
    fn_with_array_view_arg<int,4>(a);
    fn_with_int_array_view_arg(a);
}

static void test_stl_array()
{
    alignas(simd::i32x8) std::array a{1, 2, 3, 4};

    array_view av(a);
    fn_with_array_view_arg(av);

    fn_with_array_view_arg(std::span(a));
    fn_with_array_view_arg<int,a.size()>(a);
    fn_with_int_array_view_arg(a);
}

static void test_stl_vector()
{
    std::vector a{1, 2, 3, 4};

    array_view av(a);
    fn_with_array_view_arg(av);
    assert(av.front() == av[0] && av[0] == 1);

    a.emplace_back(5);

    fn_with_array_view_arg(std::span(a));
    fn_with_array_view_arg<int,std::dynamic_extent>(a);
    fn_with_int_array_view_arg(a);

    av = a;
    assert(av.front() == av[0] && av[0] == 1);
    assert(av.back() == av[4] && av[4] == 5);
}

static void test_mdspan_1d()
{
    alignas(simd::i32x8) std::array a{1, 2, 3, 4, 5, 6, 7, 8};

    using int_vector_view = vector_view<int, std::experimental::extents<size_t, a.size()>>; 
    int_vector_view av(a.data());

    static_assert(av.rank() == 1);
    assert(av.rank() == 1);

    assert(av(0) == 1);
    assert(av[0] == 1);
    assert(av[7] == 8);
}

static void test_mdspan_2d()
{
    alignas(simd::i32x8) int a[4][2]{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    using int_matrix_view = matrix_view<int, std::experimental::extents<size_t, 4, 2>>; 
    int_matrix_view av(&a[0][0]);

    static_assert(av.rank() == 2);
    assert(av.rank() == 2);

    assert(av(0, 0) == 1);
    assert(av(0, 1) == 2);
    assert(av(3, 1) == 8);

    auto av2 = std::experimental::mdspan(&a[0][0], 4, 2);

    static_assert(av2.rank() == 2);
    assert(av2.rank() == 2);

    assert(av2(0, 0) == 1);
    assert(av2(0, 1) == 2);
    assert(av2(3, 1) == 8);
}

int main(void)
{
    test_c_array();
    test_stl_array();
    test_stl_vector();

    test_mdspan_1d();
    test_mdspan_2d();

    return EXIT_SUCCESS;
}
