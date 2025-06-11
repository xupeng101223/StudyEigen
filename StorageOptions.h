#pragma once
enum StorageOptions
{
        //按列优先（列主序）存储，即内存中先按列排列，同 Fortran 语言一致，也是 Eigen 的默认存储方式
        ColMajor = 0,
        
        //按行优先（行主序）存储，内存中先按行排列，通常 C 语言数组是行主序
        RowMajor = 0x1,

        //Eigen 优化行为，如果矩阵满足向量化要求则自动对齐，提升计算性能
        AutoAlign = 0,
        
        //禁用自动对齐（通常用于兼容一些低级内存管理需求）
        DontAlign = 0x2
};