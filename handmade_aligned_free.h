#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstdlib>

EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void handmade_aligned_free(void* ptr)
{
        if (ptr) std::free(*(reinterpret_cast<void**>(ptr) - 1));
}