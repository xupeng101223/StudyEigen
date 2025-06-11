#pragma once
template<typename T, typename U> struct is_same { enum { value = 0 }; };
template<typename T> struct is_same<T, T> { enum { value = 1 }; };