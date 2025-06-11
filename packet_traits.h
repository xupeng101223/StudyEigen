#pragma once
#include "default_packet_traits.h"
#include "LRF_SSE.h"
#include "LRF_AVX.h"

template<typename T> 
struct packet_traits 
        : default_packet_traits
{
        typedef T type;
        typedef T half;
        enum {
                Vectorizable = 0,
                size = 1,
                AlignedOnScalar = 0,
                HasHalfPacket = 0
        };

        enum {
                HasAdd = 0,
                HasSub = 0,
                HasMul = 0,
                HasNegate = 0,
                HasAbs = 0,
                HasAbs2 = 0,
                HasMin = 0,
                HasMax = 0,
                HasConj = 0,
                HasSetLinear = 0
        };
};

#ifdef LRF_SSE
#include "Packet4f.h"
#include "EIGEN_FAST_MATH.h"
/*
��ε������ǡ����߿⣺
        ���� float ʱ�� Packet4f ���SIMD���ͣ�
        ��Щ��ѧ������ʸ����ʵ�֣���Щû�С���
        �����ڻ������Щ���������ȣ�
        �����Զ��� SIMD �汾�򽵼��� for-loop ����ʵ��
*/

template <>
struct packet_traits<float> 
        : default_packet_traits
{
        typedef Packet4f type;
        typedef Packet4f half;
        enum {
                Vectorizable = 1,
                AlignedOnScalar = 1,
                size = 4,
                HasHalfPacket = 0,

                HasCmp = 1,
                HasDiv = 1,
                HasSin = EIGEN_FAST_MATH,
                HasCos = EIGEN_FAST_MATH,
                HasLog = 1,
                HasLog1p = 1,
                HasExpm1 = 1,
                HasNdtri = 1,
                HasExp = 1,
                HasBessel = 1,
                HasSqrt = 1,
                HasRsqrt = 1,
                HasTanh = EIGEN_FAST_MATH,
                HasErf = EIGEN_FAST_MATH,
                HasBlend = 1,
                HasCeil = 1,
                HasFloor = 1,

#ifdef EIGEN_VECTORIZE_SSE4_1
                HasRound = 1,
#endif
                HasRint = 1
        };
};
#endif

#ifdef LRF_AVX
#include "Packet4f.h"
#include "Packet8f.h"
#include "EIGEN_FAST_MATH.h"

template<>
struct packet_traits<float> : default_packet_traits
{
        typedef Packet8f type;
        typedef Packet4f half;
        enum {
                Vectorizable = 1,
                AlignedOnScalar = 1,
                size = 8,
                HasHalfPacket = 1,

                HasCmp = 1,
                HasDiv = 1,
                HasSin = EIGEN_FAST_MATH,
                HasCos = EIGEN_FAST_MATH,
                HasLog = 1,
                HasLog1p = 1,
                HasExpm1 = 1,
                HasExp = 1,
                HasNdtri = 1,
                HasBessel = 1,
                HasSqrt = 1,
                HasRsqrt = 1,
                HasTanh = EIGEN_FAST_MATH,
                HasErf = EIGEN_FAST_MATH,
                HasBlend = 1,
                HasRound = 1,
                HasFloor = 1,
                HasCeil = 1,
                HasRint = 1
        };
};
#endif