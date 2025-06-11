#pragma once
#include <concepts>
#include <type_traits>

template<typename T, typename Dest>
concept LrfHasEvalTo = requires(const T & a, Dest & dst) {
        { a.evalTo(dst) } -> std::same_as<void>;
};