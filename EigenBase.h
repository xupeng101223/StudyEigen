#pragma once
/** \class EigenBase
作用：所有Eigen相关对象的最根基基类。用作类型定义的锚点和CRTP模板参数占位。

用于表达式模板通用性判断（“任何像矩阵的东西”都继承自这个）
没有成员变量
定义最基本的eval()等接口
调试小贴士：如果需要自定义算法，可以对接EigenBase，兼容所有矩阵/表达式类型。
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