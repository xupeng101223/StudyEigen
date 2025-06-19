#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>
#include "EIGEN_TRY.h"
#include "EIGEN_CATCH.h"
#include "EIGEN_THROW.h"
#include "destruct_elements_of_array.h"

template<typename T> 
EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE 
T* construct_elements_of_array(T* ptr, std::size_t size)
{
        std::size_t i;
        EIGEN_TRY
        {
                for (i = 0; i < size; ++i) ::new (ptr + i) T;
                return ptr;
        }
        EIGEN_CATCH(...)
        {
                destruct_elements_of_array(ptr, i);
                EIGEN_THROW;
        }
        return NULL;
}