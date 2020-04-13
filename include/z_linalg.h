#ifndef Z_LINALG_H
#define Z_LINALG_H

#define _USE_MATH_DEFINES
#include <tgmath.h>
#include <cassert>

#include <QtWidgets>
//FIXME require QtGui in cmake?
#include <QGenericMatrix>

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
    };

    // specialization of the matrix traits for built-in two-dimensional
    // arrays
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
    };
     
     
    // Swap rows i and k of a matrix A
    // Note that due to the reference, both dimensions are preserved for
    // built-in arrays
    template<typename MatrixType>
     inline void swap_rows(MatrixType& A,
                     typename matrix_traits<MatrixType>::index_type i,
                     typename matrix_traits<MatrixType>::index_type k)
    {
      matrix_traits<MatrixType> mt;
      typedef typename matrix_traits<MatrixType>::index_type index_type;
     
      // check indices
      assert(mt.min_row(A) <= i);
      assert(i <= mt.max_row(A));
     
      assert(mt.min_row(A) <= k);
      assert(k <= mt.max_row(A));
     
      for (index_type col = mt.min_column(A); col <= mt.max_column(A); ++col)
        std::swap(mt.element(A, i, col), mt.element(A, k, col));
    }


     
    // divide row i of matrix A by v
    template<typename MatrixType>
     inline void divide_row(MatrixType& A,
                      typename matrix_traits<MatrixType>::index_type i,
                      typename matrix_traits<MatrixType>::value_type v)
    {
      matrix_traits<MatrixType> mt;
      typedef typename matrix_traits<MatrixType>::index_type index_type;
     
      assert(mt.min_row(A) <= i);
      assert(i <= mt.max_row(A));
     
      assert(v != 0);
     
      for (index_type col = mt.min_column(A); col <= mt.max_column(A); ++col)
        mt.element(A, i, col) /= v;
    }
     
    // in matrix A, add v times row k to row i
    template<typename MatrixType>
     inline void add_multiple_row(MatrixType& A,
                      typename matrix_traits<MatrixType>::index_type i,
                      typename matrix_traits<MatrixType>::index_type k,
                      typename matrix_traits<MatrixType>::value_type v)
    {
      matrix_traits<MatrixType> mt;
      typedef typename matrix_traits<MatrixType>::index_type index_type;
     
      assert(mt.min_row(A) <= i);
      assert(i <= mt.max_row(A));
     
      assert(mt.min_row(A) <= k);
      assert(k <= mt.max_row(A));
     
      for (index_type col = mt.min_column(A); col <= mt.max_column(A); ++col)
        mt.element(A, i, col) += v * mt.element(A, k, col);
    }
     
    // convert A to reduced row echelon form
    template<typename MatrixType>
     inline void toRref(MatrixType& A)
    {
      matrix_traits<MatrixType> mt;
      typedef typename matrix_traits<MatrixType>::index_type index_type;
     
      index_type lead = mt.min_row(A);
     
      for (index_type row = mt.min_row(A); row <= mt.max_row(A); ++row)
      {
        if (lead > mt.max_column(A))
          return;
        index_type i = row;
        while (mt.element(A, i, lead) == 0)
        {
          ++i;
          if (i > mt.max_row(A))
          {
            i = row;
            ++lead;
            if (lead > mt.max_column(A))
              return;
          }
        }
        swap_rows(A, i, row);
        divide_row(A, row, mt.element(A, row, lead));
        for (i = mt.min_row(A); i <= mt.max_row(A); ++i)
        {
          if (i != row)
            add_multiple_row(A, i, row, -mt.element(A, i, lead));
        }
      }
    }

    template<typename MatrixType>
     inline MatrixType rref(const MatrixType& A)
    {

      MatrixType B = A;
      toRref(B);
      return B;
    }

    template<typename MatrixType>
     inline int rank(MatrixType &A) {
        matrix_traits<MatrixType> mt;
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        MatrixType B = rref(A);
        int r = 0;
        for (index_type i = mt.min_row(A); i <= mt.max_row(A); i++) {
            for (index_type j = mt.min_column(A); j <= mt.max_column(A); j++) {
                if (B(i, j) != 0) {
                    goto outer_loop;
                }
            }
            continue;
outer_loop:
            r += 1;
            continue;
        }
        return r;

    }

}

#endif
