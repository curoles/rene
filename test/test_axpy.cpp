#include <cassert>
#include <cstdlib>

#include "rene/blas/1/axpy.h"
#include "rene/simd_types.h"
#include "rene/simd_align.h"
#include "rene/aligned_allocator.h"
//#include "rene/mdarray.h"

using namespace rene;
//using std::experimental::mdspan;

static void test_axpy_a_eq_1()
{
    alignas(simd::align<int>(8))       std::array a{1, 2, 3, 4, 5, 6, 7, 8};
    alignas(simd::align<int>(8)) const std::array b{1, 2, 3, 4, 5, 6, 7, 8};
    alignas(simd::align<int>(8)) const std::array c{2, 4, 6, 8, 10, 12, 14, 16};

    rene::blas::axpy(1, std::span(a), std::span(b));

    assert(std::equal(std::begin(a), std::end(a), std::begin(c), std::end(c)));
}

static void test_axpy_a_neq_1()
{
    alignas(simd::align<int>(8))       std::array a{1, 2, 3, 4, 5, 6, 7, 8};
    alignas(simd::align<int>(8)) const std::array b{1, 2, 3, 4, 5, 6, 7, 8};
    alignas(simd::align<int>(8)) const std::array c{1*3, 2*3, 3*3, 4*3, 5*3, 6*3, 7*3, 8*3};

    rene::blas::axpy(2, std::span(a), std::span(b));

    assert(std::equal(std::begin(a), std::end(a), std::begin(c), std::end(c)));
}

int main(void)
{
    test_axpy_a_eq_1();
    test_axpy_a_neq_1();

    return EXIT_SUCCESS;
}
