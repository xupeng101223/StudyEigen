#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include "plain_array.h"
#include "smart_copy.h"
#include "smart_move.h"
#include "Index.h"
#include <algorithm>

struct plain_array_helper 
{
        template<typename T, int Size, int MatrixOrArrayOptions, int Alignment>
        EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE static void
        copy(const plain_array<T, Size, MatrixOrArrayOptions, Alignment>& src, const Eigen::Index size, plain_array<T, Size, MatrixOrArrayOptions, Alignment>& dst)
        {
                smart_copy(src.array, src.array + size, dst.array);
        }

        template<typename T, int Size, int MatrixOrArrayOptions, int Alignment>
        EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE static void 
        swap(plain_array<T, Size, MatrixOrArrayOptions, Alignment>& a, const Eigen::Index a_size, plain_array<T, Size, MatrixOrArrayOptions, Alignment>& b, const Eigen::Index b_size)
        {
                if (a_size < b_size) {
                        std::swap_ranges(b.array, b.array + a_size, a.array);
                        smart_move(b.array + a_size, b.array + b_size, a.array + a_size);
                }
                else if (a_size > b_size) {
                        std::swap_ranges(a.array, a.array + b_size, b.array);
                        smart_move(a.array + b_size, a.array + a_size, b.array + b_size);
                }
                else {
                        std::swap_ranges(a.array, a.array + a_size, b.array);
                }
        }
};