#pragma once
#include "evaluator_traits_base.h"

template<typename T> 
struct evaluator_traits;

template<typename T>
struct evaluator_traits
        : public evaluator_traits_base<T>
{};