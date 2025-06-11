#pragma once
#include "conditional.h"
#include "is_arithmetic.h"
#include "add_const_on_value_type.h"

template<typename T> struct add_const_on_value_type_if_arithmetic
{
        typedef typename conditional<
                is_arithmetic<T>::value,
                        T, 
                        typename add_const_on_value_type<T>::type>::type type;
};