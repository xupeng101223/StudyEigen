#pragma once
/*
PacketAccessBit 是 Eigen 库内部用来标记一个表达式（比如矩阵、向量或其组合表达式）是否支持“分块（packet）高速矢量化访问”的静态（编译期）标志
*/
const unsigned int PacketAccessBit = 0x8;