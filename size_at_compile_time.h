#pragma once
#include "Dynamic.h"

template<int _Rows, int _Cols>
struct size_at_compile_time
{
        enum { ret = (_Rows == Dynamic || _Cols == Dynamic) ? Dynamic : _Rows * _Cols };
};