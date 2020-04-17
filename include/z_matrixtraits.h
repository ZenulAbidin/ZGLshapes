#ifndef Z_MATRIXTRAITS_H
#define Z_MATRIXTRAITS_H

#include <cassert>
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
      static void set_element(const MatrixType &A,
                                index_type i, index_type k, value_type x)
      { A.set(i, k, x); }
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
      static void set_element(const ZQMatrix<M, N, T> &A,
                                index_type i, index_type k, value_type x)
      { A.set(i, k, x); }
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
      static void set_element(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &A,
                                index_type i, index_type k, value_type x)
      { A.set(i, k, x); }
    };

}

#endif
