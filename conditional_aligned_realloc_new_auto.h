#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>
#include "NumTraits.h"
#include "destruct_elements_of_array.h"
#include "conditional_aligned_realloc.h"
#include "construct_elements_of_array.h"
#include "conditional_aligned_free.h"

template<typename T, bool Align> 
EIGEN_STRONG_INLINE
T* conditional_aligned_realloc_new_auto(T* pts, std::size_t new_size, std::size_t old_size)
{
        if (NumTraits<T>::RequireInitialization && (new_size < old_size))
        {
                destruct_elements_of_array(pts + new_size, old_size - new_size);
        }

        T* result = reinterpret_cast<T*>(conditional_aligned_realloc<Align>(reinterpret_cast<void*>(pts), sizeof(T) * new_size, sizeof(T) * old_size));

        if (NumTraits<T>::RequireInitialization && (new_size > old_size))
        {
                EIGEN_TRY
                {
                        construct_elements_of_array(result + old_size, new_size - old_size);
                }
                EIGEN_CATCH(...)
                {
                        conditional_aligned_free<Align>(result);
                        EIGEN_THROW;
                }
        }
        return result;
}