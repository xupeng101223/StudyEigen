#pragma once
/** \ingroup enums
  * Enum for indicating whether a buffer is aligned or not. */
enum AlignmentType {
        Unaligned = 0,          /**< Data pointer has no specific alignment. */
        Aligned8 = 8,            /**< Data pointer is aligned on a 8 bytes boundary. */
        Aligned16 = 16,         /**< Data pointer is aligned on a 16 bytes boundary. */
        Aligned32 = 32,         /**< Data pointer is aligned on a 32 bytes boundary. */
        Aligned64 = 64,         /**< Data pointer is aligned on a 64 bytes boundary. */
        Aligned128 = 128,      /**< Data pointer is aligned on a 128 bytes boundary. */
        AlignedMask = 255,
        Aligned = 16,             /**< \deprecated Synonym for Aligned16. */
#if EIGEN_MAX_ALIGN_BYTES==128
        AlignedMax = Aligned128
#elif EIGEN_MAX_ALIGN_BYTES==64
        AlignedMax = Aligned64
#elif EIGEN_MAX_ALIGN_BYTES==32
        AlignedMax = Aligned32
#elif EIGEN_MAX_ALIGN_BYTES==16
        AlignedMax = Aligned16
#elif EIGEN_MAX_ALIGN_BYTES==8
        AlignedMax = Aligned8
#elif EIGEN_MAX_ALIGN_BYTES==0
        AlignedMax = Unaligned
#else
#error Invalid value for EIGEN_MAX_ALIGN_BYTES
#endif
};
