#include <cassert>
#include <cstdlib>

#include "rene/scale.h"
#include "rene/simd_types.h"
#include "rene/simd_align.h"
#include "rene/aligned_allocator.h"
//#include "rene/mdarray.h"

using namespace rene;
using std::experimental::mdspan;

static void test_scale_array()
{
    alignas(simd::align<int>(8)) std::array a{1, 2, 3, 4};
    assert(simd::is_aligned(a.data(), 8));
    alignas(simd::align<int>(8)) std::array b{2, 4, 6, 8};
    rene::scale(std::span(a), 2);

    assert(std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b)));
}

static void test_scale_dynamic_array()
{
    rene::vector<int> a{1, 2, 3, 4};
    assert(std::span(a).extent == std::dynamic_extent);
    assert(simd::is_aligned(a.data(), 8));
    alignas(simd::align<int>(8)) std::array b{2, 4, 6, 8};
    rene::scale(std::span(a), 2);

    assert(std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b)));
}

static void test_scale_2d_array()
{
    alignas(simd::align<int>(8)) int a[4][2]{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    auto av = mdspan(&a[0][0], 4, 2);
    rene::scale(av, 2);

    assert(av(0, 0) == 1*2);
    assert(av(0, 1) == 2*2);
    assert(av(3, 1) == 8*2);
}

int main(void)
{
    test_scale_array();
    test_scale_dynamic_array();
    test_scale_2d_array();

    return EXIT_SUCCESS;
}
