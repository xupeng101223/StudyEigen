#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include "IntPtr.h"
#include "eigen_assert.h"
#include <cstring>
#include <algorithm>

template<typename T, bool UseMemcpy>
struct smart_copy_helper;

template<typename T>
struct smart_copy_helper<T, true>
{
        EIGEN_DEVICE_FUNC static EIGEN_STRONG_INLINE void
                run(const T* start, const T* end, T* target)
        {
                IntPtr size = IntPtr(end) - IntPtr(start);
                if (size == 0) return;
                eigen_assert(start != 0 && end != 0 && target != 0);
                std::memcpy(target, start, size);
        }
};

template<typename T> struct smart_copy_helper<T, false> 
{
        EIGEN_DEVICE_FUNC static EIGEN_STRONG_INLINE void 
                run(const T* start, const T* end, T* target)
        {
                std::copy(start, end, target);
        }
};