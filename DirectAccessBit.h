#pragma once
/*
描述矩阵、数组或表达式“是否支持高效的底层直接访问
也即是是否支持操作 .data() 或 operator[] 的方式，直接获取底层内存指针，高效地随机存取元素
*/
const unsigned int DirectAccessBit = 0x40;

/*
比如 某些View（如 A.transpose(), A.block(), A.rowwise().sum() 等），可能指向临时对象，或者并不是等间距内存。
比如 懒惰表达式（需要动态计算）。
比如 Sparse（稀疏）矩阵，不具有连续的底层内存。
这些是不能直接通过 .data() 或指针访问所有数据
*/