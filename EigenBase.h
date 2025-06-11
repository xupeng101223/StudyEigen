#pragma once
/** \class EigenBase
���ã�����Eigen��ض������������ࡣ�������Ͷ����ê���CRTPģ�����ռλ��

���ڱ��ʽģ��ͨ�����жϣ����κ������Ķ��������̳��������
û�г�Ա����
�����������eval()�Ƚӿ�
����С��ʿ�������Ҫ�Զ����㷨�����ԶԽ�EigenBase���������о���/���ʽ���͡�
*/

#include "EIGEN_DEVICE_FUNC.h"
#include "EIGEN_DEFAULT_DENSE_INDEX_TYPE.h"
#include "EIGEN_CONSTEXPR.h"
#include "EIGEN_NOEXCEPT.h"
#include "Index.h"

namespace Eigen {
        template<typename Derived>
        struct EigenBase
        {
                typedef Eigen::Index Index;

                /** \returns a reference to the derived object */
                EIGEN_DEVICE_FUNC Derived& derived()
                { 
                        return *static_cast<Derived*>(this);
                }

                /** \returns a const reference to the derived object */
                EIGEN_DEVICE_FUNC const Derived& derived() const
                { 
                        return *static_cast<const Derived*>(this);
                }

                EIGEN_DEVICE_FUNC inline Derived& const_cast_derived() const
                {
                        return *static_cast<Derived*>(const_cast<EigenBase*>(this));
                }

                EIGEN_DEVICE_FUNC inline const Derived& const_derived() const
                {
                        return *static_cast<const Derived*>(this);
                }

                /** \returns the number of rows. \sa cols(), RowsAtCompileTime */
                EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR inline Index rows() const EIGEN_NOEXCEPT 
                { 
                        return derived().rows();
                }

                /** \returns the number of columns. \sa rows(), ColsAtCompileTime*/
                EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR inline Index cols() const EIGEN_NOEXCEPT
                {
                        return derived().cols();
                }

                /** \returns the number of coefficients, which is rows()*cols().
                  * \sa rows(), cols(), SizeAtCompileTime. */
                EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR inline Index size() const EIGEN_NOEXCEPT 
                { 
                        return rows() * cols();
                }
        };
} // end namespace Eigen