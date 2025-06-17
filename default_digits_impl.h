#pragma once
#include <limits>
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_CONSTEXPR.h"

template< typename T,
        bool use_numeric_limits = std::numeric_limits<T>::is_specialized,
        bool is_integer = std::numeric_limits<T>::is_integer>
struct default_digits_impl
{
        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR
                static int run() { return std::numeric_limits<T>::digits; }
};