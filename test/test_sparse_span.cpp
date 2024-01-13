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


template<typename T, typename P, std::size_t N>
static void fn_with_span_arg(rene::sparse_span<T,P,N> a)
{
}

/*static void fn_with_int_span_arg(rene::sparse_span<int,uint8_t> a)
{
}*/

static void test_c_array()
{
    alignas(simd::align<int>(8)) int a[]{1, 2, 3, 4};
    uint8_t p[]{3, 7, 15, 100};

    rene::sparse_span av(a, p, 4);
    fn_with_span_arg(av);

    assert(av[2].first == 3 && av[2].second == 15);

    // case ([],[])
    fn_with_span_arg(rene::sparse_span(a, p));
    fn_with_span_arg<int,uint8_t,4>(rene::sparse_span(a, p));

    fn_with_span_arg(rene::sparse_span(a, p, 4));
    fn_with_span_arg<int,uint8_t,4>(rene::sparse_span<int,uint8_t,4>(a, p, 4));
}

static void test_stl_array()
{
    alignas(simd::align<int>(8)) std::array a{1, 2, 3, 4};
    std::array<uint8_t,4> p{3, 7, 15, 100};

    rene::sparse_span av(a.data(), p.data(), 4);
    fn_with_span_arg(av);

    //fn_with_span_arg(rene::sparse_span(a, p));
    //fn_with_span_arg<int,uint8_t,4>(rene::sparse_span(a, p));

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
