#pragma once
/*
区分矩阵/数组底层数据的访问级别（权限和细节）的标志。
它直接影响你能用什么方式操作矩阵元素——包括只读、读写、是否能直接操作底层内存等。
*/

enum AccessorLevels {
        //只读访问，只能通过成员函数（如 .coeff(i, j)）来读取元素
        ReadOnlyAccessors,

        //可读可写访问，依然通过成员函数（如.coeff(i, j)、.coeffRef(i, j)）进行
        WriteAccessors,

        //直接只读访问底层数据（通常允许你拿到底层.data() 或 operator[]，直接用指针只读）
        DirectAccessors,

        //直接读写底层数据，既能拿到底层的指针，也允许你对其赋值、修改
        DirectWriteAccessors
};