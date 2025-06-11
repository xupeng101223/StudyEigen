#include "pch.h"
#include "DenseCoeffsBase.h"

namespace Eigen
{
        template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
        class TestDenseCoeffsBaseMatrix:
                public DenseCoeffsBase<TestDenseCoeffsBaseMatrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>, ReadOnlyAccessors>
        {
        public:
                Index rows() const { return 0; };
                Index cols() const { return 0; };

                enum 
                {
                        RowsAtCompileTime = _Rows,
                        ColsAtCompileTime = _Cols,
                        Flags = 0
                };
        };

        template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
        struct traits<TestDenseCoeffsBaseMatrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>>
        {
        private:
                enum { size = size_at_compile_time<_Rows, _Cols>::ret };
                typedef typename find_best_packet<_Scalar, size>::type PacketScalar;
                enum {
                        row_major_bit = _Options & RowMajor ? RowMajorBit : 0,
                        is_dynamic_size_storage = (_MaxRows == Dynamic || _MaxCols == Dynamic),
                        max_size = is_dynamic_size_storage ? Dynamic : _MaxRows * _MaxCols,
                        default_alignment = compute_default_alignment<_Scalar, max_size>::value,
                        actual_alignment = ((_Options & DontAlign) == 0) ? default_alignment : 0,
                        required_alignment = unpacket_traits<PacketScalar>::alignment,
                        packet_access_bit = (packet_traits<_Scalar>::Vectorizable &&
                                (EIGEN_UNALIGNED_VECTORIZE || (actual_alignment >= required_alignment))) ? PacketAccessBit : 0
                };

        public:
                typedef _Scalar Scalar;
                typedef Dense StorageKind;
                typedef Index StorageIndex;
                typedef MatrixXpr XprKind;

                enum {
                        RowsAtCompileTime = _Rows,
                        ColsAtCompileTime = _Cols,
                        MaxRowsAtCompileTime = _MaxRows,
                        MaxColsAtCompileTime = _MaxCols,
                        Flags = compute_matrix_flags<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>::ret,
                        Options = _Options,
                        InnerStrideAtCompileTime = 1,
                        OuterStrideAtCompileTime = (Options & RowMajor) ? ColsAtCompileTime : RowsAtCompileTime,
                        EvaluatorFlags = LinearAccessBit | DirectAccessBit | packet_access_bit | row_major_bit,
                        Alignment = actual_alignment
                };
        };
}

TEST(TestDenseCoeffsBase, Test0) 
{
        using TDCB  = Eigen::DenseCoeffsBase<Eigen::TestDenseCoeffsBaseMatrix<float, 100, 100, RowMajor, 128, 128>, ReadOnlyAccessors>;
        std::cout << typeid(TDCB::Base).name() << std::endl;
        std::cout << typeid(TDCB::StorageKind).name() << std::endl;
        std::cout << typeid(TDCB::Scalar).name() << std::endl;
        std::cout << typeid(TDCB::PacketScalar).name() << std::endl;

        TDCB tdcb;
        std::cout << tdcb.rows() << std::endl;
        std::cout << tdcb.rowIndexByOuterInner(10,10) << std::endl;
}


namespace Eigen
{
        template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
        class Test1DenseCoeffsBaseMatrix :
                public DenseCoeffsBase<Test1DenseCoeffsBaseMatrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>, ReadOnlyAccessors>
        {
        public:
                Index rows() const { return 0; };
                Index cols() const { return 0; };

                enum
                {
                        RowsAtCompileTime = _Rows,
                        ColsAtCompileTime = _Cols,
                        Flags = 0
                };
        };

        template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
        struct traits<Test1DenseCoeffsBaseMatrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>>
        {
        private:
                enum { size = size_at_compile_time<_Rows, _Cols>::ret };
                typedef typename find_best_packet<_Scalar, size>::type PacketScalar;
                enum {
                        row_major_bit = _Options & RowMajor ? RowMajorBit : 0,
                        is_dynamic_size_storage = (_MaxRows == Dynamic || _MaxCols == Dynamic),
                        max_size = is_dynamic_size_storage ? Dynamic : _MaxRows * _MaxCols,
                        default_alignment = compute_default_alignment<_Scalar, max_size>::value,
                        actual_alignment = ((_Options & DontAlign) == 0) ? default_alignment : 0,
                        required_alignment = unpacket_traits<PacketScalar>::alignment,
                        packet_access_bit = (packet_traits<_Scalar>::Vectorizable &&
                                (EIGEN_UNALIGNED_VECTORIZE || (actual_alignment >= required_alignment))) ? PacketAccessBit : 0
                };

        public:
                typedef _Scalar Scalar;
                typedef Dense StorageKind;
                typedef Index StorageIndex;
                typedef MatrixXpr XprKind;

                enum {
                        RowsAtCompileTime = _Rows,
                        ColsAtCompileTime = _Cols,
                        MaxRowsAtCompileTime = _MaxRows,
                        MaxColsAtCompileTime = _MaxCols,
                        Flags = compute_matrix_flags<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>::ret,
                        Options = _Options,
                        InnerStrideAtCompileTime = 1,
                        OuterStrideAtCompileTime = (Options & RowMajor) ? ColsAtCompileTime : RowsAtCompileTime,
                        EvaluatorFlags = LinearAccessBit | DirectAccessBit | packet_access_bit | row_major_bit,
                        Alignment = actual_alignment
                };
        };
}


TEST(TestDenseCoeffsBase, Test1)
{
}