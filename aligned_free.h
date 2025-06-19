#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstdlib>
#include "EIGEN_DEFAULT_ALIGN_BYTES.h"
#include "EIGEN_MALLOC_ALREADY_ALIGNED.h"

EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void aligned_free(void* ptr)
{
#if (EIGEN_DEFAULT_ALIGN_BYTES==0) || EIGEN_MALLOC_ALREADY_ALIGNED
        std::free(ptr);
#else
        handmade_aligned_free(ptr);
#endif
}