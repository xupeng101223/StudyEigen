#pragma once
#include "GenericNumTraits.h"

template<typename T> struct NumTraits;

template<>
struct NumTraits<float>:
        GenericNumTraits<float>
{
        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static inline
                float dummy_precision() { return 1e-5f; }
};