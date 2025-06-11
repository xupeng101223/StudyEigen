#pragma once
#include "EIGEN_MIN_ALIGN_BYTES.h"

/*
编译期递归计算“最佳内存对齐字节数”的模板元函数
        ArrayBytes：目标数组的总字节数
        AlignmentBytes：当前尝试的对齐字节数（每次递归会缩小一半）
        Match：是否能整除——也就是“当前 alignment 是不是 ArrayBytes 的约数”
        TryHalf：是否还可以继续尝试更小一档的对齐方式（比如 AlignmentBytes > 16）
*/
template<
        int ArrayBytes, 
        int AlignmentBytes,
        bool Match = bool((ArrayBytes% AlignmentBytes) == 0),
        bool TryHalf = bool(EIGEN_MIN_ALIGN_BYTES < AlignmentBytes) 
>
struct compute_default_alignment_helper
{
        enum { value = 0 };
};

template<int ArrayBytes, int AlignmentBytes, bool TryHalf>
struct compute_default_alignment_helper<ArrayBytes, AlignmentBytes, true, TryHalf> // Match
{
        enum { value = AlignmentBytes };
};

template<int ArrayBytes, int AlignmentBytes>
struct compute_default_alignment_helper<ArrayBytes, AlignmentBytes, false, true> // Try-half
{
        enum { value = compute_default_alignment_helper<ArrayBytes, AlignmentBytes / 2>::value };
};