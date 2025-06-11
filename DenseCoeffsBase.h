#pragma once
/*
DenseCoeffsBase
作用：为“具有密集系数（contiguous coefficient）存取能力”的表达式/对象提供统一接口。

提供分支：有直接内存访问和无直接内存访问两种子类，根据类型和存储方式（如plain矩阵或表达式）
提供coeff()、coeffRef()等低级访问接口
硬件层牵引：这里设计和SIMD/vectorization相关，“直接访问”意味着能做到对内存批量操作（如SSE/AVX指令，配合内存对齐）。
*/
#include "AccessorLevels.h"
#include "EigenBase.h"
#include "traits.h"
#include "packet_traits.h"
#include "conditional.h"
#include "is_arithmetic.h"
#include "add_const_on_value_type_if_arithmetic.h"
#include "LRF_STRONG_INLINE.h"

namespace Eigen 
{
        template<typename Derived, int Level> class DenseCoeffsBase;

        template<typename Derived>
        class DenseCoeffsBase<Derived, ReadOnlyAccessors> : public EigenBase<Derived>
        {
        public:
                typedef typename traits<Derived>::StorageKind StorageKind;
                typedef typename traits<Derived>::Scalar Scalar;
                typedef typename packet_traits<Scalar>::type PacketScalar;


                /*
                目标：描述 coeff() 的返回类型。
                        coeff() 是 Eigen 取矩阵/表达式中某个元素的主力方法。
                        但 Eigen 所支持的“数据类型系统”极为广泛，包括：
                                真实的底层存储（真矩阵、真数组），可以返回元素引用
                                组合表达式（比如a + b、block.submatrix()等），只能返回临时值
                                标量元素有基本类型（算术型如 float/double/int）、也可能是自定义类型
                        
                        是否支持lvalue（Flags & LvalueBit）：引用返回最优
                        LvalueBit 表示该表达式元素能成为“左值”，即可以取引用、可被赋值、拥有确定且持久的地址（如普通矩阵/数组）。
                        Matrix<T, ...> 这种就有 LvalueBit
                        a + b 组合表达式没法取引用（因为不是实际存储），没有 LvalueBit
                        若支持，应该返回 const Scalar&（引用访问，只读但无copy，性能最优）

                        继续判断 Scalar 是否为算术类型
                        有些类型（比如 float、int），const float、const int 这些在某些平台下不能做为函数返回值类型（会有警告或二义性），而自定义类型 const T 则无此问题。
                        所以：如果是算术类型（is_arithmetic），直接返回 Scalar（拷贝），保证兼容性、不引入警告
                        如果不是，则返回 const Scalar（按值返回，但加 const，提升安全）
                */
                typedef typename conditional<bool(traits<Derived>::Flags& LvalueBit),
                        const Scalar&,
                        typename conditional<is_arithmetic<Scalar>::value, Scalar, const Scalar>::type
                >::type CoeffReturnType;

                typedef typename add_const_on_value_type_if_arithmetic<
                        typename packet_traits<Scalar>::type
                >::type PacketReturnType;

                typedef EigenBase<Derived> Base;
                using Base::rows;
                using Base::cols;
                using Base::size;
                using Base::derived;

                LRF_STRONG_INLINE Index rowIndexByOuterInner(Index outer, Index inner) const
                {
                        return int(Derived::RowsAtCompileTime) == 1 ? 0
                                : int(Derived::ColsAtCompileTime) == 1 ? inner
                                : int(Derived::Flags) & RowMajorBit ? outer
                                : inner;
                }

                LRF_STRONG_INLINE Index colIndexByOuterInner(Index outer, Index inner) const
                {
                        return int(Derived::ColsAtCompileTime) == 1 ? 0
                                : int(Derived::RowsAtCompileTime) == 1 ? inner
                                : int(Derived::Flags) & RowMajorBit ? inner
                                : outer;
                }

                ///** Short version: don't use this function, use
                //  * \link operator()(Index,Index) const \endlink instead.
                //  *
                //  * Long version: this function is similar to
                //  * \link operator()(Index,Index) const \endlink, but without the assertion.
                //  * Use this for limiting the performance cost of debugging code when doing
                //  * repeated coefficient access. Only use this when it is guaranteed that the
                //  * parameters \a row and \a col are in range.
                //  *
                //  * If EIGEN_INTERNAL_DEBUGGING is defined, an assertion will be made, making this
                //  * function equivalent to \link operator()(Index,Index) const \endlink.
                //  *
                //  * \sa operator()(Index,Index) const, coeffRef(Index,Index), coeff(Index) const
                //  */
                //LRF_STRONG_INLINE CoeffReturnType coeff(Index row, Index col) const
                //{
                //        return internal::evaluator<Derived>(derived()).coeff(row, col);
                //}

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType coeffByOuterInner(Index outer, Index inner) const
        //        {
        //                return coeff(rowIndexByOuterInner(outer, inner),
        //                        colIndexByOuterInner(outer, inner));
        //        }

        //        /** \returns the coefficient at given the given row and column.
        //          *
        //          * \sa operator()(Index,Index), operator[](Index)
        //          */
        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType operator()(Index row, Index col) const
        //        {
        //                eigen_assert(row >= 0 && row < rows()
        //                        && col >= 0 && col < cols());
        //                return coeff(row, col);
        //        }

        //        /** Short version: don't use this function, use
        //          * \link operator[](Index) const \endlink instead.
        //          *
        //          * Long version: this function is similar to
        //          * \link operator[](Index) const \endlink, but without the assertion.
        //          * Use this for limiting the performance cost of debugging code when doing
        //          * repeated coefficient access. Only use this when it is guaranteed that the
        //          * parameter \a index is in range.
        //          *
        //          * If EIGEN_INTERNAL_DEBUGGING is defined, an assertion will be made, making this
        //          * function equivalent to \link operator[](Index) const \endlink.
        //          *
        //          * \sa operator[](Index) const, coeffRef(Index), coeff(Index,Index) const
        //          */

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType
        //                coeff(Index index) const
        //        {
        //                EIGEN_STATIC_ASSERT(internal::evaluator<Derived>::Flags & LinearAccessBit,
        //                        THIS_COEFFICIENT_ACCESSOR_TAKING_ONE_ACCESS_IS_ONLY_FOR_EXPRESSIONS_ALLOWING_LINEAR_ACCESS)
        //                        eigen_internal_assert(index >= 0 && index < size());
        //                return internal::evaluator<Derived>(derived()).coeff(index);
        //        }


        //        /** \returns the coefficient at given index.
        //          *
        //          * This method is allowed only for vector expressions, and for matrix expressions having the LinearAccessBit.
        //          *
        //          * \sa operator[](Index), operator()(Index,Index) const, x() const, y() const,
        //          * z() const, w() const
        //          */

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType
        //                operator[](Index index) const
        //        {
        //                EIGEN_STATIC_ASSERT(Derived::IsVectorAtCompileTime,
        //                        THE_BRACKET_OPERATOR_IS_ONLY_FOR_VECTORS__USE_THE_PARENTHESIS_OPERATOR_INSTEAD)
        //                        eigen_assert(index >= 0 && index < size());
        //                return coeff(index);
        //        }

        //        /** \returns the coefficient at given index.
        //          *
        //          * This is synonymous to operator[](Index) const.
        //          *
        //          * This method is allowed only for vector expressions, and for matrix expressions having the LinearAccessBit.
        //          *
        //          * \sa operator[](Index), operator()(Index,Index) const, x() const, y() const,
        //          * z() const, w() const
        //          */

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType
        //                operator()(Index index) const
        //        {
        //                eigen_assert(index >= 0 && index < size());
        //                return coeff(index);
        //        }

        //        /** equivalent to operator[](0).  */

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType
        //                x() const { return (*this)[0]; }

        //        /** equivalent to operator[](1).  */

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType
        //                y() const
        //        {
        //                EIGEN_STATIC_ASSERT(Derived::SizeAtCompileTime == -1 || Derived::SizeAtCompileTime >= 2, OUT_OF_RANGE_ACCESS);
        //                return (*this)[1];
        //        }

        //        /** equivalent to operator[](2).  */

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType
        //                z() const
        //        {
        //                EIGEN_STATIC_ASSERT(Derived::SizeAtCompileTime == -1 || Derived::SizeAtCompileTime >= 3, OUT_OF_RANGE_ACCESS);
        //                return (*this)[2];
        //        }

        //        /** equivalent to operator[](3).  */

        //        EIGEN_DEVICE_FUNC
        //                EIGEN_STRONG_INLINE CoeffReturnType
        //                w() const
        //        {
        //                EIGEN_STATIC_ASSERT(Derived::SizeAtCompileTime == -1 || Derived::SizeAtCompileTime >= 4, OUT_OF_RANGE_ACCESS);
        //                return (*this)[3];
        //        }

        //        /** \internal
        //          * \returns the packet of coefficients starting at the given row and column. It is your responsibility
        //          * to ensure that a packet really starts there. This method is only available on expressions having the
        //          * PacketAccessBit.
        //          *
        //          * The \a LoadMode parameter may have the value \a #Aligned or \a #Unaligned. Its effect is to select
        //          * the appropriate vectorization instruction. Aligned access is faster, but is only possible for packets
        //          * starting at an address which is a multiple of the packet size.
        //          */

        //        template<int LoadMode>
        //        EIGEN_STRONG_INLINE PacketReturnType packet(Index row, Index col) const
        //        {
        //                typedef typename internal::packet_traits<Scalar>::type DefaultPacketType;
        //                eigen_internal_assert(row >= 0 && row < rows() && col >= 0 && col < cols());
        //                return internal::evaluator<Derived>(derived()).template packet<LoadMode, DefaultPacketType>(row, col);
        //        }


        //        /** \internal */
        //        template<int LoadMode>
        //        EIGEN_STRONG_INLINE PacketReturnType packetByOuterInner(Index outer, Index inner) const
        //        {
        //                return packet<LoadMode>(rowIndexByOuterInner(outer, inner),
        //                        colIndexByOuterInner(outer, inner));
        //        }

        //        /** \internal
        //          * \returns the packet of coefficients starting at the given index. It is your responsibility
        //          * to ensure that a packet really starts there. This method is only available on expressions having the
        //          * PacketAccessBit and the LinearAccessBit.
        //          *
        //          * The \a LoadMode parameter may have the value \a #Aligned or \a #Unaligned. Its effect is to select
        //          * the appropriate vectorization instruction. Aligned access is faster, but is only possible for packets
        //          * starting at an address which is a multiple of the packet size.
        //          */

        //        template<int LoadMode>
        //        EIGEN_STRONG_INLINE PacketReturnType packet(Index index) const
        //        {
        //                EIGEN_STATIC_ASSERT(internal::evaluator<Derived>::Flags & LinearAccessBit,
        //                        THIS_COEFFICIENT_ACCESSOR_TAKING_ONE_ACCESS_IS_ONLY_FOR_EXPRESSIONS_ALLOWING_LINEAR_ACCESS)
        //                        typedef typename internal::packet_traits<Scalar>::type DefaultPacketType;
        //                eigen_internal_assert(index >= 0 && index < size());
        //                return internal::evaluator<Derived>(derived()).template packet<LoadMode, DefaultPacketType>(index);
        //        }

        //protected:
        //        // explanation: DenseBase is doing "using ..." on the methods from DenseCoeffsBase.
        //        // But some methods are only available in the DirectAccess case.
        //        // So we add dummy methods here with these names, so that "using... " doesn't fail.
        //        // It's not private so that the child class DenseBase can access them, and it's not public
        //        // either since it's an implementation detail, so has to be protected.
        //        void coeffRef();
        //        void coeffRefByOuterInner();
        //        void writePacket();
        //        void writePacketByOuterInner();
        //        void copyCoeff();
        //        void copyCoeffByOuterInner();
        //        void copyPacket();
        //        void copyPacketByOuterInner();
        //        void stride();
        //        void innerStride();
        //        void outerStride();
        //        void rowStride();
        //        void colStride();
        };
}