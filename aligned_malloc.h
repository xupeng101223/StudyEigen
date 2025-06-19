#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include "EIGEN_DEFAULT_ALIGN_BYTES.h"
#include "EIGEN_MALLOC_ALREADY_ALIGNED.h"
#include <cstddef>
#include <cstdlib>
#include "eigen_assert.h"
#include "handmade_aligned_malloc.h"

EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void* aligned_malloc(std::size_t size)
{
        void* result;
#if (EIGEN_DEFAULT_ALIGN_BYTES == 0) || EIGEN_MALLOC_ALREADY_ALIGNED
        result = std::malloc(size);

#if EIGEN_DEFAULT_ALIGN_BYTES==16
        eigen_assert((size < 16 || (std::size_t(result) % 16) == 0));
#endif

#else
        result = handmade_aligned_malloc(size);
#endif
        return result;
}