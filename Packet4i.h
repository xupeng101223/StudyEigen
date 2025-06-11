#pragma once
#include <immintrin.h>
#include "eigen_packet_wrapper.h"

/*
__m128i ��һ�� 128 λ��16 �ֽڣ��Ľṹ��
���� Intel SSE/SSE2 ָ���������ڴ洢���� SIMD ���ݵļĴ������ͣ��ڵײ��Ӧ�� XMM �Ĵ�����
ÿ�� __m128i �����ɣ�
        16 �� 8 λ������int8 �� uint8��
        8 �� 16 λ������int16 �� uint16��
        4 �� 32 λ������int32 �� uint32��
        2 �� 64 λ������int64 �� uint64��
���뷽�棬__m128i ͨ��Ҫ�� 16 �ֽڶ��룬�������ܱ� SSE ָ���Ч����
*/

typedef __m128i Packet4i;
