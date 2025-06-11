#pragma once
#include "RowMajorBit.h"
#include "StorageOptions.h"
#include "DirectAccessBit.h"
#include "LvalueBit.h"
#include "NestByRefBit.h"

template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
class compute_matrix_flags
{
        enum { row_major_bit = Options & RowMajor ? RowMajorBit : 0 };
public:
        enum { ret = DirectAccessBit | LvalueBit | NestByRefBit | row_major_bit };
};
