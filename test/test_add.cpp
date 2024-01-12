#include <cassert>
#include <cstdlib>

#include "rene/op/add.h"
#include "rene/simd_types.h"
#include "rene/simd_align.h"
#include "rene/aligned_allocator.h"
//#include "rene/mdarray.h"

using namespace rene;
using std::experimental::mdspan;

static void test_add_array()
{
    alignas(simd::align<int>(8))       std::array a{1, 2, 3, 4, 5, 6, 7, 8};
    alignas(simd::align<int>(8)) const std::array b{1, 2, 3, 4, 5, 6, 7, 8};
    alignas(simd::align<int>(8)) const std::array c{2, 4, 6, 8, 10, 12, 14, 16};

    rene::add(std::span(a), std::span(b));

    assert(std::equal(std::begin(a), std::end(a), std::begin(c), std::end(c)));
}

static void test_add_dynamic_array()
{
          rene::vector<int> a{1, 2, 3, 4};
    const rene::vector<int> b{5, 6, 7, 8};
    const rene::vector<int> c{6, 8, 10, 12};

    rene::add(std::span(a), std::span(b));

    assert(std::equal(std::begin(a), std::end(a), std::begin(c), std::end(c)));
}

static void test_add_2d_array()
{
    alignas(simd::align<int>(8))       int a[4][2]{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    alignas(simd::align<int>(8)) const int b[4][2]{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    alignas(simd::align<int>(8)) const int c[4][2]{{2, 4}, {6, 8}, {10, 12}, {14, 16}};

    auto av = mdspan(&a[0][0], 4, 2);
    auto bv = mdspan(&b[0][0], 4, 2);
    auto cv = mdspan(&c[0][0], 4, 2);

    rene::add(av, bv);

    assert(av.extent(0) == 4);
    assert(av.extent(1) == 2);

    for (std::size_t row = 0; row < av.extent(0); ++row) {
        for (std::size_t col = 0; col < av.extent(1); ++col) {
            assert(av(row, col) == cv(row, col));
        }
    }
}

int main(void)
{
    test_add_array();
    test_add_dynamic_array();
    test_add_2d_array();

    return EXIT_SUCCESS;
}
