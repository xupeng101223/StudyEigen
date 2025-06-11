#pragma once

template<typename T> struct unpacket_traits
{
        typedef T type;
        typedef T half;
        enum
        {
                size = 1,
                alignment = 1,
                vectorizable = false,
                masked_load_available = false,
                masked_store_available = false
        };
};

#include "LRF_SSE.h"

#ifdef LRF_SSE
#include "Packet4f.h"
#include "Packet4i.h"
#include "AlignmentType.h"
/*
��� traits �ṹ����ǡ����߱�����/�⣺
        �ҵ� SIMD ���� 16 �ֽڿ�
        4 �� float��
        ����ʸ�����Ż���
        ��ص����Ͱ����� Packet4i
*/

template<> 
struct unpacket_traits<Packet4f> {
        typedef float     type;
        typedef Packet4f  half;
        typedef Packet4i  integer_packet;
        enum 
        { 
                size = 4, 
                alignment = Aligned16, 
                vectorizable = true, 
                masked_load_available = false,
                masked_store_available = false 
        };
};
#endif