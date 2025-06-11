#pragma once
#include "traits.h"

template<typename T>
struct evaluator_traits_base
{
        typedef typename storage_kind_to_evaluator_kind<typename traits<T>::StorageKind>::Kind Kind;
        typedef typename storage_kind_to_shape<typename traits<T>::StorageKind>::Shape Shape;
};