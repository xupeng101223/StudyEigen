#pragma once
#include <immintrin.h>

/*
__m128 也是一个 128 位（16 字节）的结构，本质上代表了一个 SSE/XMM 128 位寄存器，
和 __m128i 唯一的区别在于它用于**单精度浮点数（float）**的向量指令。
*/
typedef __m128  Packet4f;