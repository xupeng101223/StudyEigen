#pragma once
#include "EIGEN_CONSTEXPR.h"
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <limits>
#include "is_arithmetic.h"
#include "conditional.h"

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

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE 
                Real epsilon()
        {
                return numext::numeric_limits<T>::epsilon();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE 
                int digits10()
        {
                return internal::default_digits10_impl<T>::run();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE
                int digits()
        {
                return internal::default_digits_impl<T>::run();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE
                int min_exponent()
        {
                return numext::numeric_limits<T>::min_exponent;
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE
                int max_exponent()
        {
                return numext::numeric_limits<T>::max_exponent;
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR static EIGEN_STRONG_INLINE
                Real dummy_precision()
        {
                // make sure to override this for floating-point types
                return Real(0);
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR
                static inline T highest() {
                return (numext::numeric_limits<T>::max)();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR
                static inline T lowest() {
                return IsInteger ? (numext::numeric_limits<T>::min)()
                        : static_cast<T>(-(numext::numeric_limits<T>::max)());
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR
                static inline T infinity() {
                return numext::numeric_limits<T>::infinity();
        }

        EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR
                static inline T quiet_NaN() {
                return numext::numeric_limits<T>::quiet_NaN();
        }
};
