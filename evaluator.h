#pragma once
#include "LRF_STRONG_INLINE.h"
#include "unary_evaluator.h"

template< typename T> 
struct evaluator;

template<typename T>
struct evaluator : public unary_evaluator<T>
{
        typedef unary_evaluator<T> Base;
        LRF_STRONG_INLINE explicit evaluator(const T& xpr)
                : Base(xpr)
        {}
};


template<typename T>
struct evaluator<const T>
        : evaluator<T>
{
        LRF_STRONG_INLINE explicit evaluator(const T& xpr)
                : evaluator<T>(xpr)
        {}
};