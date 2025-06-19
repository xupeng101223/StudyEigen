#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include <utility>

template<typename T> 
EIGEN_DEVICE_FUNC T* smart_move(T* start, T* end, T* target)
{
        return std::move(start, end, target);
}