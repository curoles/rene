#include <span>
#include <vector>
#include <cassert>
#include <cstdlib>
//#include <cstdio>

#include "rene/simd_types.h"
#include "rene/mdspan.h"

using namespace rene;
using std::experimental::mdspan;
using std::experimental::extents;

static void test_mdspan_1d()
{
    alignas(simd::i32x8) std::array a{1, 2, 3, 4, 5, 6, 7, 8};

    using int_vector_view = mdspan<int, extents<size_t, a.size()>>;
    int_vector_view av(a.data());

    static_assert(av.rank() == 1);
    assert(av.rank() == 1);

    assert(av(0) == 1);
    assert(av[0] == 1);
    assert(av[7] == 8);

    auto av2 = mdspan(a.data(), a.size());
    av2(7) = av2(0) + av2(1);
    assert(av2[7] == 3);
}

static void test_mdspan_2d()
{
    alignas(simd::i32x8) int a[4][2]{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    using int_matrix_view = mdspan<int, extents<size_t, 4, 2>>;
    int_matrix_view av(&a[0][0]);

    static_assert(av.rank() == 2);
    assert(av.rank() == 2);

    assert(av(0, 0) == 1);
    assert(av(0, 1) == 2);
    assert(av(3, 1) == 8);

    auto av2 = mdspan(&a[0][0], 4, 2);

    static_assert(av2.rank() == 2);
    assert(av2.rank() == 2);

    assert(av2(0, 0) == 1);
    assert(av2(0, 1) == 2);
    assert(av2(3, 1) == 8);
}

int main(void)
{
    test_mdspan_1d();
    test_mdspan_2d();

    return EXIT_SUCCESS;
}
