#pragma once
#include "Dynamic.h"
#include "unpacket_traits.h"
#include "is_same.h"

/*
查看PacketType 是否是最佳的打包结构
这意味着只要有任意一个满足，就"递归结束"，选当前 PacketType 作为最佳包类型
这是一个模板递归的处理，true为递归终止条件
*/
template<int Size, typename PacketType, bool Stop = 
        Size == Dynamic ||
        (Size % unpacket_traits<PacketType>::size) == 0 || 
        is_same<PacketType, typename unpacket_traits<PacketType>::half>::value>
struct find_best_packet_helper;

template< int Size, typename PacketType>
struct find_best_packet_helper<Size, PacketType, true>
{
        typedef PacketType type;
};

template<int Size, typename PacketType>
struct find_best_packet_helper<Size, PacketType, false>
{
        typedef typename find_best_packet_helper<Size, typename unpacket_traits<PacketType>::half>::type type;
};