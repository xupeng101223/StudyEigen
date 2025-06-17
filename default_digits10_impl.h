#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_CONSTEXPR.h"
#include <cmath>
#include <limits>

template< typename T,
        bool use_numeric_limits = std::numeric_limits<T>::is_specialized,
        bool is_integer = std::numeric_limits<T>::is_integer>
struct default_digits10_impl
{
        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static 
                int run() { return std::numeric_limits<T>::digits10; }
};

//template<typename T>
//struct default_digits10_impl<T, false, false>
//{
//        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static 
//                int run() 
//        {
//                using std::log10;
//                using std::ceil;
//                typedef typename T Real;
//                return int(ceil(-log10(std::numeric_limits<T>::epsilon())));
//        }
//};
//
//template<typename T>
//struct default_digits10_impl<T, false, true>
//{
//        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static
//                int run() { return 0; }
//};