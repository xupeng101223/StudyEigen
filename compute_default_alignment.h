#pragma once
#include "Dynamic.h"
#include "EIGEN_MAX_STATIC_ALIGN_BYTES.h"
#include "EIGEN_MAX_ALIGN_BYTES.h"
#include "compute_default_alignment_helper.h"

template<typename T, int Size>
struct compute_default_alignment {
        enum { value = compute_default_alignment_helper<Size * sizeof(T), EIGEN_MAX_STATIC_ALIGN_BYTES>::value };
};

template<typename T>
struct compute_default_alignment<T, Dynamic> {
        enum { value = EIGEN_MAX_ALIGN_BYTES };
};
