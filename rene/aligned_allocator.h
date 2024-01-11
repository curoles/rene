#pragma once

#include <cstdlib>
#include <vector>
#include "rene/simd_align.h"

namespace rene {

template<class T>
class aligned_allocator : public std::allocator<T>
{
public:
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T               value_type;

    template<class U>
    struct rebind
    {
        typedef aligned_allocator<U> other;
    };

    aligned_allocator() : std::allocator<T>() {}

    aligned_allocator(const aligned_allocator& other) : std::allocator<T>(other) {}

    template<class U>
    aligned_allocator(const aligned_allocator<U>& other) : std::allocator<T>(other) {}

    ~aligned_allocator() {}

    pointer allocate(size_type num, const void* /*hint*/ = 0)
    {
        constexpr size_type alignment = simd::max_vlen;
        size_type size = ((num * sizeof(T) + alignment) / alignment) * alignment;
        return static_cast<pointer>( std::aligned_alloc(alignment, size) );
    }

    void deallocate(pointer p, size_type /*num*/)
    {
        std::free(p);
    }
};

template<typename T>
using vector = std::vector<T, rene::aligned_allocator<T> >;

} // namespace rene
