#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>

template<typename T> 
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void destruct_elements_of_array(T* ptr, std::size_t size)
{
        if (ptr) while (size) ptr[--size].~T();
}