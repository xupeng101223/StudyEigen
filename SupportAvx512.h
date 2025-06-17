#pragma once
#include <intrin.h>
#include <iostream>
#include "EIGEN_STRONG_INLINE.h"

EIGEN_STRONG_INLINE bool SupportAvx512() {
        int cpuInfo[4] = { 0, 0, 0, 0 };
        __cpuidex(cpuInfo, 7, 0);
        bool avx512f = (cpuInfo[1] & (1 << 16)) != 0;
        return avx512f;
}