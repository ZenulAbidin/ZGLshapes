#ifndef Z_MATRIXTRAITS_H
#define Z_MATRIXTRAITS_H

#include <cassert>
#include <QGenericMatrix>
#include <QMatrix4x4>
#include "z_matrix.h"
#include "z_offsetmatrix.h"

namespace z_linalg {

    // Matrix traits: This describes how a matrix is accessed. By
    // externalizing this information into a traits class, the same code
    // can be used both with native arrays and matrix classes. To use the
    // default implementation of the traits class, a matrix type has to
    // provide the following definitions as members:
    //
    // * typedef ... index_type;
    //   - The type used for indexing (e.g. size_t)
    // * typedef ... value_type;
    //   - The element type of the matrix (e.g. double)
    // * index_type min_row() const;
    //   - returns the minimal allowed row index
    // * index_type max_row() const;
    //   - returns the maximal allowed row index
    // * index_type min_column() const;
    //   - returns the minimal allowed column index
    // * index_type max_column() const;
    //   - returns the maximal allowed column index
    // * value_type& operator()(index_type i, index_type k)
    //   - returns a reference to the element i,k, where
    //     min_row() <= i <= max_row()
    //     min_column() <= k <= max_column()
    // * value_type operator()(index_type i, index_type k) const
    //   - returns the value of element i,k
    // * ZQOffsetMatrix<1, max_row()+1, 1, max_column()+1, value_type> to1N(MatrixType const& A)
    //   - converts to a matrix class with 1-based indices. Not supported for built-in arrays.
    // * MatrixType from1N(ZQOffsetMatrix<1, max_row()+1, 1, max_column()+1, value_type> const& A)
    //   - converts a matrix class with 1-based indices to the original class. Not supported for built-in arrays.
    //
    // Note that the functions are all inline and simple, so the compiler
    // should completely optimize them away.
    template<typename MatrixType> struct matrix_traits
    {
      typedef typename MatrixType::index_type index_type;
      typedef typename MatrixType::value_type value_type;
      static index_type min_row(MatrixType const& A)
      { return A.min_row(); }
      static index_type max_row(MatrixType const& A)
      { return A.max_row(); }
      static index_type min_column(MatrixType const& A)
      { return A.min_column(); }
      static index_type max_column(MatrixType const& A)
      { return A.max_column(); }
      static value_type& element(MatrixType& A, index_type i, index_type k)
      { return A(i,k); }
      static value_type element(MatrixType const& A, index_type i, index_type k)
      { return A(i,k); }
      static value_type *data(MatrixType const& A)
      { value_type *a = A.data(); return a; }
      static MatrixType fromData(value_type *d)
      { return MatrixType(d); }
      static ZQOffsetMatrix<1, max_row()+1, 1, max_column()+1, value_type> to1N(MatrixType const& A)
      {return ZQOffsetMatrix<1, max_row()+1, 1, max_column()+1, value_type>(A.data()); }
      static MatrixType from1N(ZQOffsetMatrix<1, max_row()+1, 1, max_column()+1, value_type> const& A)
      {return MatrixType(A.data()); }
    };

    // specialization of the matrix traits for built-in two-dimensional
    // arrays
    template<typename T, std::size_t rows, std::size_t columns>
     struct matrix_traits<T[rows][columns]>
    {
      typedef std::size_t index_type;
      typedef T value_type;
      static index_type min_row(T const (&)[rows][columns])
      { return 0; }
      static index_type max_row(T const (&)[rows][columns])
      { return rows-1; }
      static index_type min_column(T const (&)[rows][columns])
      { return 0; }
      static index_type max_column(T const (&)[rows][columns])
      { return columns-1; }
      static value_type& element(T (&A)[rows][columns],
                                 index_type i, index_type k)
      { return A[i][k]; }
      static value_type element(T const (&A)[rows][columns],
                                index_type i, index_type k)
      { return A[i][k]; }
      static ZQOffsetMatrix<1, rows, 1, columns, value_type> to1N(T const (&A)[rows][columns])
      { assert(false /* "Conversion from built-in array to ZQOffsetMatrix is not supported. Use one of the other array classes." */ ); return ZQOffsetMatrix<1, rows, 1, columns, value_type>(); }
      static T* from1N(ZQOffsetMatrix<1, rows, 1, columns, value_type> const& A)
      { assert(false /* "Conversion from ZQOffsetMatrix to built-in array is not supported. Use one of the other array classes." */ ); return nullptr; }
    };

    template<> struct matrix_traits<QMatrix4x4>
    {
      typedef int index_type;
      typedef float value_type;
      static index_type min_row(const QMatrix4x4 &)
      { return 0; }
      static index_type max_row(const QMatrix4x4 &)
      { return 3; }
      static index_type min_column(const QMatrix4x4 &)
      { return 0; }
      static index_type max_column(const QMatrix4x4 &)
      { return 3; }
      static value_type& element(QMatrix4x4 &A,
                                 index_type i, index_type k)
      { return A(i, k); }
      static value_type element(const QMatrix4x4 &A,
                                index_type i, index_type k)
      { return A(i, k); }
      static ZQOffsetMatrix<1, 4, 1, 4, value_type> to1N(QMatrix4x4 const& A)
      { return ZQOffsetMatrix<1, 4, 1, 4, value_type>(A.data()); }
      static QMatrix4x4 from1N(ZQOffsetMatrix<1, 4, 1, 4, value_type> const& A)
      { return QMatrix4x4(A.data()); }
    };

    template <int N, int M, typename T>
    struct matrix_traits<QGenericMatrix<N, M, T>>
    {
      typedef int index_type;
      typedef T value_type;
      static index_type min_row(const QGenericMatrix<N, M, T> &)
      { return 0; }
      static index_type max_row(const QGenericMatrix<N, M, T> &)
      { return M-1; }
      static index_type min_column(const QGenericMatrix<N, M, T> &)
      { return 0; }
      static index_type max_column(const QGenericMatrix<N, M, T> &)
      { return N-1; }
      static value_type& element(QGenericMatrix<N, M, T> &A,
                                 index_type i, index_type k)
      { return A(i, k); }
      static value_type element(const QGenericMatrix<N, M, T> &A,
                                index_type i, index_type k)
      { return A(i, k); }
      static ZQOffsetMatrix<1, M, 1, N, value_type> to1N(QGenericMatrix<N, M, T> const& A)
      { return ZQOffsetMatrix<1, M, 1, N, value_type>(A.data()); }
      static QGenericMatrix<N, M, T> from1N(ZQOffsetMatrix<1, M, 1, N, value_type> const& A)
      { return QGenericMatrix<N, M, T>(A.data()); }
    };

    template <int M, int N, typename T>
    struct matrix_traits<ZQMatrix<M, N, T>>
    {
      typedef int index_type;
      typedef T value_type;
      static index_type min_row(const ZQMatrix<M, N, T> &)
      { return 0; }
      static index_type max_row(const ZQMatrix<M, N, T> &)
      { return M-1; }
      static index_type min_column(const ZQMatrix<M, N, T> &)
      { return 0; }
      static index_type max_column(const ZQMatrix<M, N, T> &)
      { return N-1; }
      static value_type& element(ZQMatrix<M, N, T> &A,
                                 index_type i, index_type k)
      { return A(i, k); }
      static value_type element(const ZQMatrix<M, N, T> &A,
                                index_type i, index_type k)
      { return A(i, k); }
      static ZQOffsetMatrix<1, M, 1, N, value_type> to1N(ZQMatrix<M, N, T> const& A)
      { return ZQOffsetMatrix<1, M, 1, N, value_type>(A.data()); }
      static ZQMatrix<M, N, T> from1N(ZQOffsetMatrix<1, M, 1, N, value_type> const& A)
      { return ZQMatrix<M, N, T>(A.data()); }
    };

    template <int minM, int maxM, int minN, int maxN, typename T>
    struct matrix_traits<ZQOffsetMatrix<minM, maxM, minN, maxN, T>>
    {
      typedef int index_type;
      typedef T value_type;
      static index_type min_row(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &)
      { return minM; }
      static index_type max_row(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &)
      { return maxM; }
      static index_type min_column(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &)
      { return minN; }
      static index_type max_column(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &)
      { return maxN; }
      static value_type& element(ZQOffsetMatrix<minM, maxM, minN, maxN, T> &A,
                                 index_type i, index_type k)
      { return A(i, k); }
      static value_type element(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &A,
                                index_type i, index_type k)
      { return A(i, k); }
      static ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, value_type> to1N(ZQOffsetMatrix<minM, maxM, minN, maxN, T> const& A)
      { return ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, value_type>(A.data()); }
      static ZQOffsetMatrix<minM, maxM, minN, maxN, T> from1N(ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, value_type> const& A)
      { return ZQOffsetMatrix<minM, maxM, minN, maxN, T>(A.data()); }
    };

}

#endif
