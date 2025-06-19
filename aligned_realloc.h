#pragma once
#include "EIGEN_STRONG_INLINE.h"
#include "EIGEN_DEFAULT_ALIGN_BYTES.h"
#include "EIGEN_MALLOC_ALREADY_ALIGNED.h"
#include <cstddef>
#include <cstdlib>
#include "eigen_assert.h"
#include "handmade_aligned_realloc.h"

EIGEN_STRONG_INLINE 
void* aligned_realloc(void* ptr, std::size_t new_size, std::size_t old_size)
{
        void* result;
#if (EIGEN_DEFAULT_ALIGN_BYTES==0) || EIGEN_MALLOC_ALREADY_ALIGNED
        result = std::realloc(ptr, new_size);
#else
        result = handmade_aligned_realloc(ptr, new_size, old_size);
#endif
        return result;
}