#include <span>
#include <vector>
#include <cassert>
#include <cstdlib>
//#include <cstdio>

#include "rene/simd_types.h"
#include "rene/simd_align.h"
#include "rene/aligned_allocator.h"

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
    alignas(simd::align<int>(8)) int a[]{1, 2, 3, 4};

    std::span av(a);
    fn_with_array_view_arg(av);

    fn_with_array_view_arg(std::span(a));
    fn_with_array_view_arg<int,4>(a);
    fn_with_int_array_view_arg(a);
}

static void test_stl_array()
{
    alignas(simd::align<int>(8)) std::array a{1, 2, 3, 4};

    std::span av(a);
    fn_with_array_view_arg(av);

    fn_with_array_view_arg(std::span(a));
    fn_with_array_view_arg<int,a.size()>(a);
    fn_with_int_array_view_arg(a);
}

static void test_stl_vector()
{
    rene::vector<int> a{1, 2, 3, 4};

    std::span av(a);
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

int main(void)
{
    test_c_array();
    test_stl_array();
    test_stl_vector();

    return EXIT_SUCCESS;
}
