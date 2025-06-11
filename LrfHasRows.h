#pragma once
#include <concepts>
#include <type_traits>
#include "Index.h"

template<typename T>
concept LrfHasRows = requires(T a) 
{
        { a.rows() } -> std::convertible_to<Eigen::Index>;
};