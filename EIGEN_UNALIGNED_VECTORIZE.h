#pragma once
/*
用于决定是否允许对未对齐内存做SIMD矢量化。这个宏若被定义为 1，意思是：
        “即使数据不是严格 16 字节（SSE）、32 字节（AVX）对齐，
        Eigen 依然会用对应的 unaligned load/store 指令来做向量化计算

现代X86硬件（如Intel Core 2及以后、AMD Zen系列）对unaligned load性能损耗极小，基本和aligned没区别，解绑SIMD应用场景
*/
#define EIGEN_UNALIGNED_VECTORIZE 1