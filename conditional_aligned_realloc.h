#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>
#include "aligned_realloc.h"

template<bool Align> 
EIGEN_STRONG_INLINE
void* conditional_aligned_realloc(void* ptr, std::size_t new_size, std::size_t old_size)
{
        return aligned_realloc(ptr, new_size, old_size);
}

template<> 
EIGEN_STRONG_INLINE
void* conditional_aligned_realloc<false>(void* ptr, std::size_t new_size, std::size_t)
{
        return std::realloc(ptr, new_size);
}
