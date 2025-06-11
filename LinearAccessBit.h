#pragma once
/*
该表达式（数组/矩阵/子块等）可以被**（高效地）当作一维线性数组（vector）访问**，
即支持以单一索引coeff(int)方式直接且快速地取/改每一个元素，中间无复杂下标计算或间接跳步。
*/
const unsigned int LinearAccessBit = 0x10;