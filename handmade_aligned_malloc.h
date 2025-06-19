#pragma once
#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>
#include "EIGEN_DEFAULT_ALIGN_BYTES.h"
#include "eigen_assert.h"
#include <cstdlib>

EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
void* handmade_aligned_malloc(std::size_t size, std::size_t alignment = EIGEN_DEFAULT_ALIGN_BYTES)
{
        eigen_assert(
                alignment >= sizeof(void*) && 
                (alignment & (alignment - 1)) == 0 && 
                "Alignment must be at least sizeof(void*) and a power of 2");

        void* original = std::malloc(size + alignment);
        if (original == 0) return 0;

        void* aligned = reinterpret_cast<void*>((reinterpret_cast<std::size_t>(original) & ~(std::size_t(alignment - 1))) + alignment);
        *(reinterpret_cast<void**>(aligned) - 1) = original;
        return aligned;
}