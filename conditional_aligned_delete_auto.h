#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>
#include "destruct_elements_of_array.h"
#include "NumTraits.h"
#include "conditional_aligned_free.h"


template<typename T, bool Align> 
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE 
void conditional_aligned_delete_auto(T* ptr, std::size_t size)
{
        if (NumTraits<T>::RequireInitialization)
                destruct_elements_of_array<T>(ptr, size);
        conditional_aligned_free<Align>(ptr);
}