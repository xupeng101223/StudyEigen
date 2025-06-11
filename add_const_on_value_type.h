#pragma once
template<typename T> struct add_const_on_value_type { typedef const T type; };
template<typename T> struct add_const_on_value_type<T&> { typedef T const& type; };
template<typename T> struct add_const_on_value_type<T*> { typedef T const* type; };
template<typename T> struct add_const_on_value_type<T* const> { typedef T const* const type; };
template<typename T> struct add_const_on_value_type<T const* const> { typedef T const* const type; };