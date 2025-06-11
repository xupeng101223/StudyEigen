#pragma once
#include "evaluator_traits.h"

template< typename T,
        typename Kind = typename evaluator_traits<typename T::NestedExpression>::Kind,
        typename Scalar = typename T::Scalar>
struct unary_evaluator;

