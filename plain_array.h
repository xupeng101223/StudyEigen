#pragma once
#include "compute_default_alignment.h"
#include "StorageOptions.h"
#include "EIGEN_ALIGN_TO_BOUNDARY.h"
#include "EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT.h"

template <typename T, int Size, int MatrixOrArrayOptions, int Alignment = (MatrixOrArrayOptions & DontAlign) ? 0 : compute_default_alignment<T, Size>::value>
struct plain_array
{
        T array[Size];
        plain_array() {}
};

template <typename T, int Size, int MatrixOrArrayOptions>
struct plain_array<T, Size, MatrixOrArrayOptions, 8>
{
        EIGEN_ALIGN_TO_BOUNDARY(8) T array[Size];
        plain_array() 
        {
                EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT(7);
        }
};

template <typename T, int Size, int MatrixOrArrayOptions>
struct plain_array<T, Size, MatrixOrArrayOptions, 16>
{
        EIGEN_ALIGN_TO_BOUNDARY(16) T array[Size];
        plain_array()
        {
                EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT(15);
        }
};

template <typename T, int Size, int MatrixOrArrayOptions>
struct plain_array<T, Size, MatrixOrArrayOptions, 32>
{
        EIGEN_ALIGN_TO_BOUNDARY(32) T array[Size];

        plain_array()
        {
                EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT(31);
        }
};

template <typename T, int Size, int MatrixOrArrayOptions>
struct plain_array<T, Size, MatrixOrArrayOptions, 64>
{
        EIGEN_ALIGN_TO_BOUNDARY(64) T array[Size];

        plain_array()
        {
                EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT(63);
        }
};

template <typename T, int MatrixOrArrayOptions, int Alignment>
struct plain_array<T, 0, MatrixOrArrayOptions, Alignment>
{
        T array[1];
        plain_array() {}
};
