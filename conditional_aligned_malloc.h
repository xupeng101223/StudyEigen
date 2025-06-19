#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstdlib>
#include "aligned_malloc.h"

template<bool Align>
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void* conditional_aligned_malloc(std::size_t size)
{
        return aligned_malloc(size);
}

template<>
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void* conditional_aligned_malloc<false>(std::size_t size)
{
        void* result = std::malloc(size);
        return result;
}