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
这个 traits 结构体就是“告诉编译器/库：
        我的 SIMD 包是 16 字节宽，
        4 个 float，
        可以矢量化优化，
        相关的整型包类型 Packet4i
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