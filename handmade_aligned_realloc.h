#pragma once
#include "EIGEN_STRONG_INLINE.h"
#include <cstddef>
#include "EIGEN_DEFAULT_ALIGN_BYTES.h"
#include "eigen_assert.h"
#include <cstdlib>
#include "handmade_aligned_malloc.h"
#include <cstring>

EIGEN_STRONG_INLINE
void* handmade_aligned_realloc(void* ptr, std::size_t size, std::size_t = 0)
{
        if (ptr == 0) 
                return handmade_aligned_malloc(size);

        void* original = *(reinterpret_cast<void**>(ptr) - 1);
        std::ptrdiff_t previous_offset = static_cast<char*>(ptr) - static_cast<char*>(original);
        original = std::realloc(original, size + EIGEN_DEFAULT_ALIGN_BYTES);
        if (original == 0)
                return 0;

        void* aligned = reinterpret_cast<void*>((reinterpret_cast<std::size_t>(original) & ~(std::size_t(EIGEN_DEFAULT_ALIGN_BYTES - 1))) + EIGEN_DEFAULT_ALIGN_BYTES);
        void* previous_aligned = static_cast<char*>(original) + previous_offset;
        if (aligned != previous_aligned)
                std::memmove(aligned, previous_aligned, size);

        *(reinterpret_cast<void**>(aligned) - 1) = original;
        return aligned;
}