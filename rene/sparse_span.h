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
    std::size_t _Extent = std::dynamic_extent,
    std::size_t _SparseExtent = std::dynamic_extent // full size, non empty plus empty
>
class sparse_span
{
public:
    // member types
    using element_type           = _Type;
    using value_type             = std::remove_cv_t<_Type>;
    using size_type              = std::size_t;
    using position_type          = _PosType;
    using pos_pointer            = _PosType*;
    //using val_pos_ref            = std::pair<value_type&, position_type>;
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
    size_t _M_sparse_extent; // need to store actual size if _SparseExtent==dynamic

    // std::span avoids using extra variable if _Extent != dynamic_extent
    //[[no_unique_address]] __detail::__extent_storage<extent> _M_extent;

    // member constants
public:
    static constexpr std::size_t extent = _Extent;
    static constexpr std::size_t sparse_extent = _SparseExtent;

    // constructors, copy and assignment
public:

    constexpr
    sparse_span() noexcept
        requires ((_Extent + 1u) <= 1u)
    : _M_ptr(nullptr), _M_pos_ptr(nullptr),
    _M_extent(0), _M_sparse_extent(_SparseExtent)
    { }

    constexpr
    sparse_span(pointer data_ptr, pos_pointer pos_ptr,
       std::size_t count, std::size_t sparse_count) noexcept
    : _M_ptr(data_ptr), _M_pos_ptr(pos_ptr),
    _M_extent(count), _M_sparse_extent(sparse_count)
    {
        if constexpr (_Extent != std::dynamic_extent) {
            /*__glibcxx_*/assert(count == _Extent);
        }
        if constexpr (_SparseExtent != std::dynamic_extent) {
            /*__glibcxx_*/assert(sparse_count == _SparseExtent);
        }
    }

    template<std::size_t _ArrayExtent>
	constexpr
	sparse_span(std::array<_Type, _ArrayExtent>& __darr,
                std::array<_PosType, _ArrayExtent>& __parr,
                std::size_t sparse_count) noexcept
	: sparse_span(__darr.data(),
        __parr.data(), _ArrayExtent, sparse_count)
	{ }

    constexpr
    sparse_span(const sparse_span&) noexcept = default;

    ~sparse_span() noexcept = default;

    constexpr sparse_span&
    operator=(const sparse_span&) noexcept = default;

    constexpr
    sparse_span(_Type data[], _PosType pos[], std::size_t sparse_count) noexcept
    : _M_ptr(data), _M_pos_ptr(pos),
    _M_extent(_Extent), _M_sparse_extent(sparse_count)
    {
        static_assert(_Extent != std::dynamic_extent);
    }

    // observers
public:
    constexpr size_type
    data_size() const noexcept
    { return this->_M_extent; }

    constexpr size_type
    data_size_bytes() const noexcept
    { return this->_M_extent * sizeof(element_type); }

    [[nodiscard]] constexpr bool
    data_empty() const noexcept
    { return data_size() == 0; }

    constexpr size_type
    size() const noexcept
    { return this->_M_sparse_extent; }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return size() == 0; }

    // element access

#if 0
    constexpr val_pos_ref
    data_front() const noexcept
    {
        /*__glibcxx_*/assert(!empty());
        return std::pair<value_type&, positi    std::size_t _SparseExtent = std::dynamic_extent, // full size, non empty plus emptyon_type&>(*this->_M_ptr, *this->_M_pos_ptr);
    }

    constexpr val_pos_ref
    data_back() const noexcept
    {
        /*__glibcxx_*/assert(!empty());
        return std::pair<value_type&, position_type&>(
            *(this->_M_ptr + (size() - 1)),
            *(this->_M_pos_ptr + (size() - 1)));
    }
#endif

    // assume positions are sorted
    // FIXME TODO bisection
    constexpr value_type
    operator[](size_type requested_pos) const noexcept
    {
        /*__glibcxx_*/assert(requested_pos < size());
        value_type val{}; // init with 0
        for (size_type i = 0; i < data_size(); ++i) {
            size_type pos = static_cast<size_type>(_M_pos_ptr[i]);
            if (pos == requested_pos) {
                return _M_ptr[i];
            }
            // optimization, `pos` not found in the array of positions,
            // assume sorted positions
            if (requested_pos < pos) {
                break;
            }
        }
        return val;
    }

    constexpr pointer
    data() const noexcept
    { return this->_M_ptr; }

    constexpr pos_pointer
    positions() const noexcept
    { return this->_M_pos_ptr; }
};



// deduction guides

template<typename _Type, typename _PosType>
sparse_span(_Type*, _PosType*, std::size_t,
    std::size_t) -> sparse_span<_Type, _PosType, std::dynamic_extent, std::dynamic_extent>;

template<typename _Type, typename _PosType, std::size_t _ArrayExtent>
sparse_span(_Type(&)[_ArrayExtent], _PosType(&)[_ArrayExtent],
    std::size_t) -> sparse_span<_Type, _PosType, _ArrayExtent, std::dynamic_extent>;

template<typename _Type, typename _PosType, std::size_t _ArrayExtent>
sparse_span(std::array<_Type,_ArrayExtent>&,
    std::array<_PosType,_ArrayExtent>&,
    std::size_t) -> sparse_span<_Type, _PosType, _ArrayExtent, std::dynamic_extent>;

} // namespace rene