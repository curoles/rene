#include <cassert>
#include <cstdlib>

#include "rene/scale.h"
#include "rene/simd_types.h"
#include "rene/simd_align.h"
#include "rene/mdarray.h"

using namespace rene;

static void test_scale_array()
{
    alignas(simd::align<int>(8)) std::array a{1, 2, 3, 4};
    alignas(simd::align<int>(8)) std::array b{2, 4, 6, 8};
    rene::array_scale(std::span(a), 2);

    assert(std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b)));
}

static void test_2()
{
}

static void test_3()
{
}

int main(void)
{
    test_scale_array();
    test_2();
    test_3();

    return EXIT_SUCCESS;
}
