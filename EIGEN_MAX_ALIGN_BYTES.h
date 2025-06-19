#pragma once
#include "LRF_AVX.h"
#include "LRF_SSE.h"

#ifdef LRF_AVX
#define EIGEN_MAX_ALIGN_BYTES 32
#else
#define EIGEN_MAX_ALIGN_BYTES 16
#endif