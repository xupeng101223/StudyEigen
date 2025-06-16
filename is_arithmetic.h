#pragma once
/*
判断某种类型是不是“算术类型
*/
template<typename T> struct is_arithmetic { enum { value = false }; };


template<> struct is_arithmetic<float> { enum { value = true }; };