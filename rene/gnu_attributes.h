/**@file
 * @brief
 * @author Igor Lesik 2024
 * @copyright 2024 Igor Lesik
 *
 */
#pragma once

#ifdef __GNUC__
#define RENE_ATTR_WO(ref_index, size_index) __attribute__((access(write_only, ref_index, size_index)))
#define RENE_ATTR_RO(ref_index, size_index) __attribute__((access(read_only, ref_index, size_index)))
#define RENE_ATTR_RW(ref_index, size_index) __attribute__((access(read_write, ref_index, size_index)))
#else
#define RENE_ATTR_WO(ref_index, size_index)
#define RENE_ATTR_RO(ref_index, size_index)
#define RENE_ATTR_RW(ref_index, size_index)
#endif

#define RENE_ATTR_VEC(type, count) __attribute__((vector_size(sizeof(type)*count)))
