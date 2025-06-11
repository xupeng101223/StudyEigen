#pragma once
#include "LRF_STRONG_INLINE.h"

template<typename T, int unique_id = 0>
struct eigen_packet_wrapper
{
        LRF_STRONG_INLINE operator T& () { return m_val; }
        LRF_STRONG_INLINE operator const T& () const { return m_val; }
        LRF_STRONG_INLINE eigen_packet_wrapper() {}
        LRF_STRONG_INLINE eigen_packet_wrapper(const T& v) : m_val(v) {}
        LRF_STRONG_INLINE eigen_packet_wrapper& operator=(const T& v)
        {
                m_val = v;
                return *this;
        }
        T m_val;
};