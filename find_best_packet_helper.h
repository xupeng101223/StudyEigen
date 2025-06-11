#pragma once
#include "Dynamic.h"
#include "unpacket_traits.h"
#include "is_same.h"

/*
�鿴PacketType �Ƿ�����ѵĴ���ṹ
����ζ��ֻҪ������һ�����㣬��"�ݹ����"��ѡ��ǰ PacketType ��Ϊ��Ѱ�����
����һ��ģ��ݹ�Ĵ���trueΪ�ݹ���ֹ����
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