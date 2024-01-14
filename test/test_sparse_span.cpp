#include <span>
#include <vector>
#include <cassert>
#include <cstdlib>
//#include <cstdio>

#include "rene/simd_types.h"
#include "rene/simd_align.h"
#include "rene/aligned_allocator.h"
#include "rene/sparse_span.h"

using namespace rene;


template<typename T, typename P, std::size_t N, std::size_t SZ>
static void fn_with_span_arg(rene::sparse_span<T,P,N,SZ> a)
{
}

static void test_c_array()
{
    alignas(simd::align<int>(8)) int a[]{1, 2, 3, 4};
    uint8_t p[]{3, 7, 15, 100};

    rene::sparse_span<int,uint8_t> av(a, p, 4, 101);
    fn_with_span_arg(av);

    for (size_t i = 0; i < 101; ++i) {
        if (i == 3) assert(av[i] == 1);
        else if (i == 7) assert(av[i] == 2);
        else if (i == 15) assert(av[i] == 3);
        else if (i == 100) assert(av[i] == 4);
        else assert(av[i] == 0);
    }

    // case ([],[])
    fn_with_span_arg(rene::sparse_span(a, p, 101));
    fn_with_span_arg<int,uint8_t,4>(rene::sparse_span(a, p, 101));

    fn_with_span_arg(rene::sparse_span<int,uint8_t,4,101>(a, p, 4, 101));
    fn_with_span_arg<int,uint8_t,std::dynamic_extent,std::dynamic_extent>(
        rene::sparse_span(a, p, 4, 101));
}

static void test_stl_array()
{
    alignas(simd::align<int>(8)) std::array a{1, 2, 3, 4};
    std::array<uint8_t,4> p{3, 7, 15, 100};

    rene::sparse_span<int,uint8_t> av(a.data(), p.data(), 4, 101);
    fn_with_span_arg(av);

    fn_with_span_arg(rene::sparse_span(a, p, 101));
    fn_with_span_arg<int,uint8_t,4,std::dynamic_extent>(
        rene::sparse_span(a, p, 101));

    //fn_with_span_arg(std::span(a));
    //fn_with_span_arg<int,a.size()>(a);
    //fn_with_int_span_arg(a);
}
#if 0
static void test_stl_vector()
{
    rene::vector<int> a{1, 2, 3, 4};

    std::span av(a);
    fn_with_span_arg(av);
    assert(av.front() == av[0] && av[0] == 1);

    a.emplace_back(5);

    fn_with_span_arg(std::span(a));
    fn_with_span_arg<int,std::dynamic_extent>(a);
    fn_with_int_span_arg(a);

    av = a;
    assert(av.front() == av[0] && av[0] == 1);
    assert(av.back() == av[4] && av[4] == 5);
}
#endif
int main(void)
{
    test_c_array();
    test_stl_array();
    //test_stl_vector();

    return EXIT_SUCCESS;
}
