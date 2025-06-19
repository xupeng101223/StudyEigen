#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstdlib>
#include "aligned_free.h"

template<bool Align> 
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void conditional_aligned_free(void* ptr)
{
        aligned_free(ptr);
}

template<> 
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void conditional_aligned_free<false>(void* ptr)
{
        std::free(ptr);
}