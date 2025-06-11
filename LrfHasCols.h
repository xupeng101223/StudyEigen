#pragma once
#include <concepts>
#include <type_traits>
#include "Index.h"

template<typename T>
concept LrfHasCols = requires(T a)
{
        { a.cols() } -> std::convertible_to<Eigen::Index>;
};