#ifndef Z_LINALG_H
#define Z_LINALG_H

#define _USE_MATH_DEFINES
#include <tgmath.h>
#include <cassert>

#include <QtWidgets>
#include "z_matrixtraits.h"

namespace z_linalg {

    template <typename T>
     inline void swap2(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
     
    
    /***************************
     * Linear Algebra Routines *
     ***************************/

    // Gauss-Jordan elimintation with full pivoting
    // Given the matrix A, coefficient vector B and the the linear algebra equation A * [X <=> Y] = [B <=> I],
    // returns the inverse of A, Y, in IA and the solution vector X. I being the identity matrix.
/*
    template<typename MatrixType>
     inline void gauss_jordan_full(const MatrixType& A, const MatrixType& B,
        MatrixType &Y, MatrixType &X)
    {
        matrix_traits<MatrixType> mt;
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        Y = A;
        X = B;
        assert(A.max_row() == A.max_column());
        ZQOffsetMatrix<1, A.max_row(), 0, 0, qreal> indxc, indxr, ipiv;
        index_type i, icol, irow, j, k, l, ll;
        value_type big, dum, pivinv, temp;

        for (j = 1; j <= n; j++) {
            ipiv(j,0) = 0;
        }
        
        for (i = 1; i <= n; i++) {
            big = 0.0;
            for (j = 1; j <= n; j++) {
                if (ipiv(j,0) != 1) {
                    for (k = 1; k <= n; k++) {
                        if (ipiv(k,0) == 0) {
//TODO Convert args to ZQOffsetMatrix.
                            if (abs(a(j,k) 
                        }
                    }
                }
            }
        }

    }  
*/

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
