#pragma once
/*
�ж�ĳ�������ǲ��ǡ���������
*/
template<typename T> struct is_arithmetic { enum { value = false }; };


template<> struct is_arithmetic<float> { enum { value = true }; };