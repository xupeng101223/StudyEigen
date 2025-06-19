#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>
#include "conditional_aligned_malloc.h"
#include "NumTraits.h"
#include "EIGEN_TRY.h"
#include "EIGEN_CATCH.h"
#include "EIGEN_THROW.h"
#include "construct_elements_of_array.h"
#include "conditional_aligned_free.h"

template<typename T, bool Align>
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
T* conditional_aligned_new_auto(std::size_t size)
{
        if (size == 0)
                return 0;

        T* result = reinterpret_cast<T*>(conditional_aligned_malloc<Align>(sizeof(T) * size));
        if (NumTraits<T>::RequireInitialization)
        {
                EIGEN_TRY
                {
                        construct_elements_of_array(result, size);
                }
                EIGEN_CATCH(...)
                {
                        conditional_aligned_free<Align>(result);
                        EIGEN_THROW;
                }
        }
        return result;
}