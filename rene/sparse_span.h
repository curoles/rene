/**@file
 * @brief     Like std::span but for sparse array
 * @author    Igor Lesik 2022-2024
 * @copyright Igor Lesik 2024
 *
 * @see /usr/include/c++/11/span
 */
#pragma once

#include <span>
#include <array>
#include <cstddef>
#include <cassert>

namespace rene {

template<
    typename _Type,
    typename _PosType,
    size_t _Extent = std::dynamic_extent
>
class sparse_span
{
public:
    // member types
    using element_type           = _Type;
    using value_type             = std::remove_cv_t<_Type>;
    using size_type              = size_t;
    using position_type          = _PosType;
    using pos_pointer            = _PosType*;
    using val_pos_ref            = std::pair<value_type&, position_type&>;
    using difference_type        = ptrdiff_t;
    using pointer                = _Type*;
    using const_pointer          = const _Type*;
    using reference              = element_type&;
    using const_reference        = const element_type&;
    //using iterator = __gnu_cxx::__normal_iterator<pointer, span>;
    //using reverse_iterator       = std::reverse_iterator<iterator>;

private:
    pointer _M_ptr;
    pos_pointer _M_pos_ptr;
    size_t _M_extent; // need to store actual size if _Extent==dynamic

    // std::span avoids using extra variable if _Extent != dynamic_extent
    //[[no_unique_address]] __detail::__extent_storage<extent> _M_extent;

    // member constants
public:
    static constexpr size_t extent = _Extent;

    // constructors, copy and assignment
public:

    constexpr
    sparse_span() noexcept
        requires ((_Extent + 1u) <= 1u)
    : _M_ptr(nullptr), _M_pos_ptr(nullptr), _M_extent(0)
    { }

    constexpr
    sparse_span(pointer data_ptr, pos_pointer pos_ptr, size_t count) noexcept
    : _M_ptr(data_ptr), _M_pos_ptr(pos_ptr), _M_extent(count)
    {
        if constexpr (_Extent != std::dynamic_extent) {
            /*__glibcxx_*/assert(count == _Extent);
        }
    }

    template<typename _T, typename _P, size_t _ArrayExtent>
	    //requires __is_compatible_array<const _Tp, _ArrayExtent>::value
	constexpr
	sparse_span(/*const*/ std::array<_T, _ArrayExtent>& __darr,
                /*const*/ std::array<_P, _ArrayExtent>& __parr) noexcept
	: sparse_span(/*static_cast<pointer>*/(__darr.data()),
        /*static_cast<pointer>*/(__parr.data()), _ArrayExtent)
	{ }

    constexpr
    sparse_span(const sparse_span&) noexcept = default;

    ~sparse_span() noexcept = default;

    constexpr sparse_span&
    operator=(const sparse_span&) noexcept = default;

    constexpr
    sparse_span(_Type data[], _PosType pos[]) noexcept
    : _M_ptr(data), _M_pos_ptr(pos), _M_extent(_Extent)
    {
        static_assert(_Extent != std::dynamic_extent);
    }

    // observers
public:
    constexpr size_type
    size() const noexcept
    { return this->_M_extent; }

    constexpr size_type
    size_bytes() const noexcept
    { return this->_M_extent * sizeof(element_type); }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return size() == 0; }

    // element access

    constexpr val_pos_ref
    front() const noexcept
    {
        /*__glibcxx_*/assert(!empty());
        return std::pair<value_type&, position_type&>(*this->_M_ptr, *this->_M_pos_ptr);
    }

    constexpr val_pos_ref
    back() const noexcept
    {
        /*__glibcxx_*/assert(!empty());
        return std::pair<value_type&, position_type&>(
            *(this->_M_ptr + (size() - 1)),
            *(this->_M_pos_ptr + (size() - 1)));
    }

    constexpr val_pos_ref
    operator[](size_type __idx) const noexcept
    {
        /*__glibcxx_*/assert(__idx < size());
        return std::pair<value_type&, position_type&>(
            *(this->_M_ptr + __idx),
            *(this->_M_pos_ptr + __idx));
    }

    constexpr pointer
    data() const noexcept
    { return this->_M_ptr; }

    constexpr pos_pointer
    positions() const noexcept
    { return this->_M_pos_ptr; }
};



// deduction guides

template<typename _Type, typename _PosType, size_t _ArrayExtent>
sparse_span(_Type(&)[_ArrayExtent],
    _PosType(&)[_ArrayExtent]) -> sparse_span<_Type, _PosType, _ArrayExtent>;


} // namespace rene