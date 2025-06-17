#pragma once
#include "EIGEN_STRONG_INLINE.h"
#include "unary_evaluator.h"

template< typename T> 
struct evaluator;

template<typename T>
struct evaluator : public unary_evaluator<T>
{
        typedef unary_evaluator<T> Base;
        EIGEN_STRONG_INLINE explicit evaluator(const T& xpr)
                : Base(xpr)
        {}
};


template<typename T>
struct evaluator<const T>
        : evaluator<T>
{
        EIGEN_STRONG_INLINE explicit evaluator(const T& xpr)
                : evaluator<T>(xpr)
        {}
};