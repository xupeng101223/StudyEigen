#pragma once
#include <immintrin.h>
#include "eigen_packet_wrapper.h"

/*
__m128i 是一个 128 位（16 字节）的结构。
它是 Intel SSE/SSE2 指令集定义的用于存储整数 SIMD 数据的寄存器类型，在底层对应着 XMM 寄存器，
每个 __m128i 能容纳：
        16 个 8 位整数（int8 或 uint8）
        8 个 16 位整数（int16 或 uint16）
        4 个 32 位整数（int32 或 uint32）
        2 个 64 位整数（int64 或 uint64）
对齐方面，__m128i 通常要求 16 字节对齐，这样才能被 SSE 指令高效访问
*/

typedef __m128i Packet4i;
