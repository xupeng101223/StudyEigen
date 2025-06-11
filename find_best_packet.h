#pragma once
#include "packet_traits.h"
#include "find_best_packet_helper.h"

template<typename T, int Size>
struct find_best_packet
{
        typedef typename find_best_packet_helper<Size, typename packet_traits<T>::type>::type type;
};