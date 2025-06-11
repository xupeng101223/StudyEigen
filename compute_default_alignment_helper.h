#pragma once
#include "EIGEN_MIN_ALIGN_BYTES.h"

/*
�����ڵݹ���㡰����ڴ�����ֽ�������ģ��Ԫ����
        ArrayBytes��Ŀ����������ֽ���
        AlignmentBytes����ǰ���ԵĶ����ֽ�����ÿ�εݹ����Сһ�룩
        Match���Ƿ�����������Ҳ���ǡ���ǰ alignment �ǲ��� ArrayBytes ��Լ����
        TryHalf���Ƿ񻹿��Լ������Ը�Сһ���Ķ��뷽ʽ������ AlignmentBytes > 16��
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