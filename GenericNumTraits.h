#pragma once
#include "EIGEN_CONSTEXPR.h"
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <limits>
#include "is_arithmetic.h"
#include "conditional.h"
#include "default_digits10_impl.h"
#include "default_digits_impl.h"

template<typename T> 
struct GenericNumTraits
{
        enum 
        {
                IsInteger = std::numeric_limits<T>::is_integer,
                IsSigned = std::numeric_limits<T>::is_signed,
                IsComplex = 0,
                RequireInitialization = is_arithmetic<T>::value ? 0 : 1,
                ReadCost = 1,
                AddCost = 1,
                MulCost = 1
        };

        typedef T Real;
        typedef typename conditional<IsInteger, typename conditional<sizeof(T) <= 2, float, double>::type, T>::type NonInteger;
        typedef T Nested;
        typedef T Literal;

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE Real 
        epsilon()
        {
                return std::numeric_limits<T>::epsilon();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE int 
        digits10()
        {
                return default_digits10_impl<T>::run();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE int 
        digits()
        {
                return default_digits_impl<T>::run();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE int 
        min_exponent()
        {
                return std::numeric_limits<T>::min_exponent;
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE int
        max_exponent()
        {
                return std::numeric_limits<T>::max_exponent;
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE Real 
        dummy_precision()
        {
                return Real(0);
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE T
        highest() {
                return (std::numeric_limits<T>::max)();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE T
        lowest() {
                return IsInteger ? (std::numeric_limits<T>::min)()
                        : static_cast<T>(-(std::numeric_limits<T>::max)());
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE T
        infinity() 
        {
                return std::numeric_limits<T>::infinity();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE T
        quiet_NaN() 
        {
                return std::numeric_limits<T>::quiet_NaN();
        }
};
