#pragma once
namespace Eigen
{
        /** \internal
  *
  * \class DenseStorage
  * \ingroup Core_Module
  *
  * \brief Stores the data of a matrix
  *
  * This class stores the data of fixed-size, dynamic-size or mixed matrices
  * in a way as compact as possible.
  *
  * \sa Matrix
  */
        template<typename T, int Size, int _Rows, int _Cols, int _Options> class DenseStorage;

        // purely fixed-size matrix
        template<typename T, int Size, int _Rows, int _Cols, int _Options> class DenseStorage
        {
                internal::plain_array<T, Size, _Options> m_data;
        public:
                EIGEN_DEVICE_FUNC DenseStorage() {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN(Index size = Size)
                }
                EIGEN_DEVICE_FUNC
                        explicit DenseStorage(internal::constructor_without_unaligned_array_assert)
                        : m_data(internal::constructor_without_unaligned_array_assert()) {}
#if !EIGEN_HAS_CXX11 || defined(EIGEN_DENSE_STORAGE_CTOR_PLUGIN)
                EIGEN_DEVICE_FUNC
                        DenseStorage(const DenseStorage& other) : m_data(other.m_data) {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN(Index size = Size)
                }
#else
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage&) = default;
#endif
#if !EIGEN_HAS_CXX11
                EIGEN_DEVICE_FUNC
                        DenseStorage& operator=(const DenseStorage& other)
                {
                        if (this != &other) m_data = other.m_data;
                        return *this;
                }
#else
                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage&) = default;
#endif
#if EIGEN_HAS_RVALUE_REFERENCES
#if !EIGEN_HAS_CXX11
                EIGEN_DEVICE_FUNC DenseStorage(DenseStorage&& other) EIGEN_NOEXCEPT
                        : m_data(std::move(other.m_data))
                {
                }
                EIGEN_DEVICE_FUNC DenseStorage& operator=(DenseStorage&& other) EIGEN_NOEXCEPT
                {
                        if (this != &other)
                                m_data = std::move(other.m_data);
                        return *this;
                }
#else
                EIGEN_DEVICE_FUNC DenseStorage(DenseStorage&&) = default;
                EIGEN_DEVICE_FUNC DenseStorage& operator=(DenseStorage&&) = default;
#endif
#endif
                EIGEN_DEVICE_FUNC DenseStorage(Index size, Index rows, Index cols) {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN({})
                                eigen_internal_assert(size == rows * cols && rows == _Rows && cols == _Cols);
                        EIGEN_UNUSED_VARIABLE(size);
                        EIGEN_UNUSED_VARIABLE(rows);
                        EIGEN_UNUSED_VARIABLE(cols);
                }
                EIGEN_DEVICE_FUNC void swap(DenseStorage& other) {
                        numext::swap(m_data, other.m_data);
                }
                EIGEN_DEVICE_FUNC static EIGEN_CONSTEXPR Index rows(void) EIGEN_NOEXCEPT { return _Rows; }
                EIGEN_DEVICE_FUNC static EIGEN_CONSTEXPR Index cols(void) EIGEN_NOEXCEPT { return _Cols; }
                EIGEN_DEVICE_FUNC void conservativeResize(Index, Index, Index) {}
                EIGEN_DEVICE_FUNC void resize(Index, Index, Index) {}
                EIGEN_DEVICE_FUNC const T* data() const { return m_data.array; }
                EIGEN_DEVICE_FUNC T* data() { return m_data.array; }
        };

        // null matrix
        template<typename T, int _Rows, int _Cols, int _Options> class DenseStorage<T, 0, _Rows, _Cols, _Options>
        {
        public:
                EIGEN_DEVICE_FUNC DenseStorage() {}
                EIGEN_DEVICE_FUNC explicit DenseStorage(internal::constructor_without_unaligned_array_assert) {}
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage&) {}
                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage&) { return *this; }
                EIGEN_DEVICE_FUNC DenseStorage(Index, Index, Index) {}
                EIGEN_DEVICE_FUNC void swap(DenseStorage&) {}
                EIGEN_DEVICE_FUNC static EIGEN_CONSTEXPR Index rows(void) EIGEN_NOEXCEPT { return _Rows; }
                EIGEN_DEVICE_FUNC static EIGEN_CONSTEXPR Index cols(void) EIGEN_NOEXCEPT { return _Cols; }
                EIGEN_DEVICE_FUNC void conservativeResize(Index, Index, Index) {}
                EIGEN_DEVICE_FUNC void resize(Index, Index, Index) {}
                EIGEN_DEVICE_FUNC const T* data() const { return 0; }
                EIGEN_DEVICE_FUNC T* data() { return 0; }
        };

        // more specializations for null matrices; these are necessary to resolve ambiguities
        template<typename T, int _Options> class DenseStorage<T, 0, Dynamic, Dynamic, _Options>
        : public DenseStorage<T, 0, 0, 0, _Options> { };

        template<typename T, int _Rows, int _Options> class DenseStorage<T, 0, _Rows, Dynamic, _Options>
        : public DenseStorage<T, 0, 0, 0, _Options> { };

        template<typename T, int _Cols, int _Options> class DenseStorage<T, 0, Dynamic, _Cols, _Options>
        : public DenseStorage<T, 0, 0, 0, _Options> { };

        // dynamic-size matrix with fixed-size storage
        template<typename T, int Size, int _Options> class DenseStorage<T, Size, Dynamic, Dynamic, _Options>
        {
                internal::plain_array<T, Size, _Options> m_data;
                Index m_rows;
                Index m_cols;
        public:
                EIGEN_DEVICE_FUNC DenseStorage() : m_rows(0), m_cols(0) {}
                EIGEN_DEVICE_FUNC explicit DenseStorage(internal::constructor_without_unaligned_array_assert)
                        : m_data(internal::constructor_without_unaligned_array_assert()), m_rows(0), m_cols(0) {}
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage& other)
                        : m_data(internal::constructor_without_unaligned_array_assert()), m_rows(other.m_rows), m_cols(other.m_cols)
                {
                        internal::plain_array_helper::copy(other.m_data, m_rows * m_cols, m_data);
                }
                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage& other)
                {
                        if (this != &other)
                        {
                                m_rows = other.m_rows;
                                m_cols = other.m_cols;
                                internal::plain_array_helper::copy(other.m_data, m_rows * m_cols, m_data);
                        }
                        return *this;
                }
                EIGEN_DEVICE_FUNC DenseStorage(Index, Index rows, Index cols) : m_rows(rows), m_cols(cols) {}
                EIGEN_DEVICE_FUNC void swap(DenseStorage& other)
                {
                        internal::plain_array_helper::swap(m_data, m_rows * m_cols, other.m_data, other.m_rows * other.m_cols);
                        numext::swap(m_rows, other.m_rows);
                        numext::swap(m_cols, other.m_cols);
                }
                EIGEN_DEVICE_FUNC Index rows() const { return m_rows; }
                EIGEN_DEVICE_FUNC Index cols() const { return m_cols; }
                EIGEN_DEVICE_FUNC void conservativeResize(Index, Index rows, Index cols) { m_rows = rows; m_cols = cols; }
                EIGEN_DEVICE_FUNC void resize(Index, Index rows, Index cols) { m_rows = rows; m_cols = cols; }
                EIGEN_DEVICE_FUNC const T* data() const { return m_data.array; }
                EIGEN_DEVICE_FUNC T* data() { return m_data.array; }
        };

        // dynamic-size matrix with fixed-size storage and fixed width
        template<typename T, int Size, int _Cols, int _Options> class DenseStorage<T, Size, Dynamic, _Cols, _Options>
        {
                internal::plain_array<T, Size, _Options> m_data;
                Index m_rows;
        public:
                EIGEN_DEVICE_FUNC DenseStorage() : m_rows(0) {}
                EIGEN_DEVICE_FUNC explicit DenseStorage(internal::constructor_without_unaligned_array_assert)
                        : m_data(internal::constructor_without_unaligned_array_assert()), m_rows(0) {}
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage& other)
                        : m_data(internal::constructor_without_unaligned_array_assert()), m_rows(other.m_rows)
                {
                        internal::plain_array_helper::copy(other.m_data, m_rows * _Cols, m_data);
                }

                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage& other)
                {
                        if (this != &other)
                        {
                                m_rows = other.m_rows;
                                internal::plain_array_helper::copy(other.m_data, m_rows * _Cols, m_data);
                        }
                        return *this;
                }
                EIGEN_DEVICE_FUNC DenseStorage(Index, Index rows, Index) : m_rows(rows) {}
                EIGEN_DEVICE_FUNC void swap(DenseStorage& other)
                {
                        internal::plain_array_helper::swap(m_data, m_rows * _Cols, other.m_data, other.m_rows * _Cols);
                        numext::swap(m_rows, other.m_rows);
                }
                EIGEN_DEVICE_FUNC Index rows(void) const EIGEN_NOEXCEPT { return m_rows; }
                EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR Index cols(void) const EIGEN_NOEXCEPT { return _Cols; }
                EIGEN_DEVICE_FUNC void conservativeResize(Index, Index rows, Index) { m_rows = rows; }
                EIGEN_DEVICE_FUNC void resize(Index, Index rows, Index) { m_rows = rows; }
                EIGEN_DEVICE_FUNC const T* data() const { return m_data.array; }
                EIGEN_DEVICE_FUNC T* data() { return m_data.array; }
        };

        // dynamic-size matrix with fixed-size storage and fixed height
        template<typename T, int Size, int _Rows, int _Options> class DenseStorage<T, Size, _Rows, Dynamic, _Options>
        {
                internal::plain_array<T, Size, _Options> m_data;
                Index m_cols;
        public:
                EIGEN_DEVICE_FUNC DenseStorage() : m_cols(0) {}
                EIGEN_DEVICE_FUNC explicit DenseStorage(internal::constructor_without_unaligned_array_assert)
                        : m_data(internal::constructor_without_unaligned_array_assert()), m_cols(0) {}
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage& other)
                        : m_data(internal::constructor_without_unaligned_array_assert()), m_cols(other.m_cols)
                {
                        internal::plain_array_helper::copy(other.m_data, _Rows * m_cols, m_data);
                }
                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage& other)
                {
                        if (this != &other)
                        {
                                m_cols = other.m_cols;
                                internal::plain_array_helper::copy(other.m_data, _Rows * m_cols, m_data);
                        }
                        return *this;
                }
                EIGEN_DEVICE_FUNC DenseStorage(Index, Index, Index cols) : m_cols(cols) {}
                EIGEN_DEVICE_FUNC void swap(DenseStorage& other) {
                        internal::plain_array_helper::swap(m_data, _Rows * m_cols, other.m_data, _Rows * other.m_cols);
                        numext::swap(m_cols, other.m_cols);
                }
                EIGEN_DEVICE_FUNC EIGEN_CONSTEXPR Index rows(void) const EIGEN_NOEXCEPT { return _Rows; }
                EIGEN_DEVICE_FUNC Index cols(void) const EIGEN_NOEXCEPT { return m_cols; }
                EIGEN_DEVICE_FUNC void conservativeResize(Index, Index, Index cols) { m_cols = cols; }
                EIGEN_DEVICE_FUNC void resize(Index, Index, Index cols) { m_cols = cols; }
                EIGEN_DEVICE_FUNC const T* data() const { return m_data.array; }
                EIGEN_DEVICE_FUNC T* data() { return m_data.array; }
        };

        // purely dynamic matrix.
        template<typename T, int _Options> class DenseStorage<T, Dynamic, Dynamic, Dynamic, _Options>
        {
                T* m_data;
                Index m_rows;
                Index m_cols;
        public:
                EIGEN_DEVICE_FUNC DenseStorage() : m_data(0), m_rows(0), m_cols(0) {}
                EIGEN_DEVICE_FUNC explicit DenseStorage(internal::constructor_without_unaligned_array_assert)
                        : m_data(0), m_rows(0), m_cols(0) {}
                EIGEN_DEVICE_FUNC DenseStorage(Index size, Index rows, Index cols)
                        : m_data(internal::conditional_aligned_new_auto<T, (_Options& DontAlign) == 0>(size)), m_rows(rows), m_cols(cols)
                {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN({})
                                eigen_internal_assert(size == rows * cols && rows >= 0 && cols >= 0);
                }
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage& other)
                        : m_data(internal::conditional_aligned_new_auto<T, (_Options& DontAlign) == 0>(other.m_rows* other.m_cols))
                        , m_rows(other.m_rows)
                        , m_cols(other.m_cols)
                {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN(Index size = m_rows * m_cols)
                                internal::smart_copy(other.m_data, other.m_data + other.m_rows * other.m_cols, m_data);
                }
                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage& other)
                {
                        if (this != &other)
                        {
                                DenseStorage tmp(other);
                                this->swap(tmp);
                        }
                        return *this;
                }
#if EIGEN_HAS_RVALUE_REFERENCES
                EIGEN_DEVICE_FUNC
                        DenseStorage(DenseStorage&& other) EIGEN_NOEXCEPT
                        : m_data(std::move(other.m_data))
                        , m_rows(std::move(other.m_rows))
                        , m_cols(std::move(other.m_cols))
                {
                        other.m_data = nullptr;
                        other.m_rows = 0;
                        other.m_cols = 0;
                }
                EIGEN_DEVICE_FUNC
                        DenseStorage& operator=(DenseStorage&& other) EIGEN_NOEXCEPT
                {
                        numext::swap(m_data, other.m_data);
                        numext::swap(m_rows, other.m_rows);
                        numext::swap(m_cols, other.m_cols);
                        return *this;
                }
#endif
                EIGEN_DEVICE_FUNC ~DenseStorage() { internal::conditional_aligned_delete_auto<T, (_Options& DontAlign) == 0>(m_data, m_rows * m_cols); }
                EIGEN_DEVICE_FUNC void swap(DenseStorage& other)
                {
                        numext::swap(m_data, other.m_data);
                        numext::swap(m_rows, other.m_rows);
                        numext::swap(m_cols, other.m_cols);
                }
                EIGEN_DEVICE_FUNC Index rows(void) const EIGEN_NOEXCEPT { return m_rows; }
                EIGEN_DEVICE_FUNC Index cols(void) const EIGEN_NOEXCEPT { return m_cols; }
                void conservativeResize(Index size, Index rows, Index cols)
                {
                        m_data = internal::conditional_aligned_realloc_new_auto<T, (_Options & DontAlign) == 0>(m_data, size, m_rows * m_cols);
                        m_rows = rows;
                        m_cols = cols;
                }
                EIGEN_DEVICE_FUNC void resize(Index size, Index rows, Index cols)
                {
                        if (size != m_rows * m_cols)
                        {
                                internal::conditional_aligned_delete_auto<T, (_Options& DontAlign) == 0>(m_data, m_rows * m_cols);
                                if (size > 0) // >0 and not simply !=0 to let the compiler knows that size cannot be negative
                                        m_data = internal::conditional_aligned_new_auto<T, (_Options & DontAlign) == 0>(size);
                                else
                                        m_data = 0;
                                EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN({})
                        }
                        m_rows = rows;
                        m_cols = cols;
                }
                EIGEN_DEVICE_FUNC const T* data() const { return m_data; }
                EIGEN_DEVICE_FUNC T* data() { return m_data; }
        };

        // matrix with dynamic width and fixed height (so that matrix has dynamic size).
        template<typename T, int _Rows, int _Options> class DenseStorage<T, Dynamic, _Rows, Dynamic, _Options>
        {
                T* m_data;
                Index m_cols;
        public:
                EIGEN_DEVICE_FUNC DenseStorage() : m_data(0), m_cols(0) {}
                explicit DenseStorage(internal::constructor_without_unaligned_array_assert) : m_data(0), m_cols(0) {}
                EIGEN_DEVICE_FUNC DenseStorage(Index size, Index rows, Index cols) : m_data(internal::conditional_aligned_new_auto<T, (_Options& DontAlign) == 0>(size)), m_cols(cols)
                {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN({})
                                eigen_internal_assert(size == rows * cols && rows == _Rows && cols >= 0);
                        EIGEN_UNUSED_VARIABLE(rows);
                }
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage& other)
                        : m_data(internal::conditional_aligned_new_auto<T, (_Options& DontAlign) == 0>(_Rows* other.m_cols))
                        , m_cols(other.m_cols)
                {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN(Index size = m_cols * _Rows)
                                internal::smart_copy(other.m_data, other.m_data + _Rows * m_cols, m_data);
                }
                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage& other)
                {
                        if (this != &other)
                        {
                                DenseStorage tmp(other);
                                this->swap(tmp);
                        }
                        return *this;
                }
#if EIGEN_HAS_RVALUE_REFERENCES
                EIGEN_DEVICE_FUNC
                        DenseStorage(DenseStorage&& other) EIGEN_NOEXCEPT
                        : m_data(std::move(other.m_data))
                        , m_cols(std::move(other.m_cols))
                {
                        other.m_data = nullptr;
                        other.m_cols = 0;
                }
                EIGEN_DEVICE_FUNC
                        DenseStorage& operator=(DenseStorage&& other) EIGEN_NOEXCEPT
                {
                        numext::swap(m_data, other.m_data);
                        numext::swap(m_cols, other.m_cols);
                        return *this;
                }
#endif
                EIGEN_DEVICE_FUNC ~DenseStorage() { internal::conditional_aligned_delete_auto<T, (_Options& DontAlign) == 0>(m_data, _Rows * m_cols); }
                EIGEN_DEVICE_FUNC void swap(DenseStorage& other) {
                        numext::swap(m_data, other.m_data);
                        numext::swap(m_cols, other.m_cols);
                }
                EIGEN_DEVICE_FUNC static EIGEN_CONSTEXPR Index rows(void) EIGEN_NOEXCEPT { return _Rows; }
                EIGEN_DEVICE_FUNC Index cols(void) const EIGEN_NOEXCEPT { return m_cols; }
                EIGEN_DEVICE_FUNC void conservativeResize(Index size, Index, Index cols)
                {
                        m_data = internal::conditional_aligned_realloc_new_auto<T, (_Options & DontAlign) == 0>(m_data, size, _Rows * m_cols);
                        m_cols = cols;
                }
                EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE void resize(Index size, Index, Index cols)
                {
                        if (size != _Rows * m_cols)
                        {
                                internal::conditional_aligned_delete_auto<T, (_Options& DontAlign) == 0>(m_data, _Rows * m_cols);
                                if (size > 0) // >0 and not simply !=0 to let the compiler knows that size cannot be negative
                                        m_data = internal::conditional_aligned_new_auto<T, (_Options & DontAlign) == 0>(size);
                                else
                                        m_data = 0;
                                EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN({})
                        }
                        m_cols = cols;
                }
                EIGEN_DEVICE_FUNC const T* data() const { return m_data; }
                EIGEN_DEVICE_FUNC T* data() { return m_data; }
        };

        // matrix with dynamic height and fixed width (so that matrix has dynamic size).
        template<typename T, int _Cols, int _Options> class DenseStorage<T, Dynamic, Dynamic, _Cols, _Options>
        {
                T* m_data;
                Index m_rows;
        public:
                EIGEN_DEVICE_FUNC DenseStorage() : m_data(0), m_rows(0) {}
                explicit DenseStorage(internal::constructor_without_unaligned_array_assert) : m_data(0), m_rows(0) {}
                EIGEN_DEVICE_FUNC DenseStorage(Index size, Index rows, Index cols) : m_data(internal::conditional_aligned_new_auto<T, (_Options& DontAlign) == 0>(size)), m_rows(rows)
                {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN({})
                                eigen_internal_assert(size == rows * cols && rows >= 0 && cols == _Cols);
                        EIGEN_UNUSED_VARIABLE(cols);
                }
                EIGEN_DEVICE_FUNC DenseStorage(const DenseStorage& other)
                        : m_data(internal::conditional_aligned_new_auto<T, (_Options& DontAlign) == 0>(other.m_rows* _Cols))
                        , m_rows(other.m_rows)
                {
                        EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN(Index size = m_rows * _Cols)
                                internal::smart_copy(other.m_data, other.m_data + other.m_rows * _Cols, m_data);
                }
                EIGEN_DEVICE_FUNC DenseStorage& operator=(const DenseStorage& other)
                {
                        if (this != &other)
                        {
                                DenseStorage tmp(other);
                                this->swap(tmp);
                        }
                        return *this;
                }
#if EIGEN_HAS_RVALUE_REFERENCES
                EIGEN_DEVICE_FUNC
                        DenseStorage(DenseStorage&& other) EIGEN_NOEXCEPT
                        : m_data(std::move(other.m_data))
                        , m_rows(std::move(other.m_rows))
                {
                        other.m_data = nullptr;
                        other.m_rows = 0;
                }
                EIGEN_DEVICE_FUNC
                        DenseStorage& operator=(DenseStorage&& other) EIGEN_NOEXCEPT
                {
                        numext::swap(m_data, other.m_data);
                        numext::swap(m_rows, other.m_rows);
                        return *this;
                }
#endif
                EIGEN_DEVICE_FUNC ~DenseStorage() { internal::conditional_aligned_delete_auto<T, (_Options& DontAlign) == 0>(m_data, _Cols * m_rows); }
                EIGEN_DEVICE_FUNC void swap(DenseStorage& other) {
                        numext::swap(m_data, other.m_data);
                        numext::swap(m_rows, other.m_rows);
                }
                EIGEN_DEVICE_FUNC Index rows(void) const EIGEN_NOEXCEPT { return m_rows; }
                EIGEN_DEVICE_FUNC static EIGEN_CONSTEXPR Index cols(void) { return _Cols; }
                void conservativeResize(Index size, Index rows, Index)
                {
                        m_data = internal::conditional_aligned_realloc_new_auto<T, (_Options & DontAlign) == 0>(m_data, size, m_rows * _Cols);
                        m_rows = rows;
                }
                EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE void resize(Index size, Index rows, Index)
                {
                        if (size != m_rows * _Cols)
                        {
                                internal::conditional_aligned_delete_auto<T, (_Options& DontAlign) == 0>(m_data, _Cols * m_rows);
                                if (size > 0) // >0 and not simply !=0 to let the compiler knows that size cannot be negative
                                        m_data = internal::conditional_aligned_new_auto<T, (_Options & DontAlign) == 0>(size);
                                else
                                        m_data = 0;
                                EIGEN_INTERNAL_DENSE_STORAGE_CTOR_PLUGIN({})
                        }
                        m_rows = rows;
                }
                EIGEN_DEVICE_FUNC const T* data() const { return m_data; }
                EIGEN_DEVICE_FUNC T* data() { return m_data; }
        };
}