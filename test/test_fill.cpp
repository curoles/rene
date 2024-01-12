#include <cassert>
#include <cstdlib>

#include "rene/op/fill.h"
#include "rene/simd_types.h"
#include "rene/simd_align.h"
#include "rene/aligned_allocator.h"
//#include "rene/mdarray.h"

using namespace rene;
using std::experimental::mdspan;

static void test_fill_array()
{
    alignas(simd::align<int>(8)) std::array a{1, 2, 3, 4, 5, 6, 7, 8};
    assert(simd::is_aligned(a.data(), 8));
    alignas(simd::align<int>(8)) std::array b{77, 77, 77, 77, 77, 77, 77, 77};
    rene::fill(std::span(a), 77);

    assert(std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b)));
}

static void test_fill_dynamic_array()
{
    rene::vector<int> a{1, 2, 3, 4};
    assert(std::span(a).extent == std::dynamic_extent);
    assert(simd::is_aligned(a.data(), 8));
    alignas(simd::align<int>(8)) std::array b{77, 77, 77, 77};
    rene::fill(std::span(a), 77);

    assert(std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b)));
}

static void test_fill_2d_array()
{
    alignas(simd::align<int>(8)) int a[4][2]{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    auto av = mdspan(&a[0][0], 4, 2);
    rene::fill(av, 77);

    assert(av(0, 0) == 77);
    assert(av(0, 1) == 77);
    assert(av(3, 1) == 77);
}

int main(void)
{
    test_fill_array();
    test_fill_dynamic_array();
    test_fill_2d_array();

    return EXIT_SUCCESS;
}
