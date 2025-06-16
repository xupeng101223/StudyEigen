#pragma once
#include "UIntPtr.h"
#include "eigen_assert.h"
#define EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT(sizemask, vec) \
    eigen_assert((UIntPtr(vec) & (sizemask)) == 0);
