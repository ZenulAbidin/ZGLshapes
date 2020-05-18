// Copyright (c) 2020 Ali Sherief. All rights reserved.
// These functions have not been properly tested yet. Use at your own risk.

#ifndef Z_LINALG_H
#define Z_LINALG_H

#define _USE_MATH_DEFINES
#include <tgmath.h>
#include <cassert>

#include <string>
#include <algorithm>
#include <limits>
#include "z_matrixtraits.h"

namespace z_linalg {

    template <typename T>
     inline void swap2(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    // Tests for equality within range of eps. Adjust eps depending on the type.
    // numbers that are close by a difference of exactly eps are considered unequal.
    // Don't set eps to zero.
    template <typename T>
     inline bool fuzzy_equal(T& a, T& b, T eps = 1e-20)
    {
        if (abs(abs(a)-abs(b)) < eps) {
            return true;
        }
        else {
            return false;
        }
    }

    /*
     * Indexes an array arr[1..n] i.e. outputs the array indx[1..n] such that arr[indx[j]] is in ascending
     * order for j = 1, 2, ..., N. The input arr is not changed.
     */
    template <int n, typename T>
     inline bool index_ascend_zq(const ZQOffsetMatrix<1, n, 0, 0, T> &arr, ZQOffsetMatrix<1, n, 0, 0, int> &indx,
        std::string &error)
    {
        int i, indxt, ir=n, itemp, j, k, l=1;
        int jstack=0;
        T a;
        const int M=7, NSTACK=50;
        ZQOffsetMatrix<1, NSTACK, 0, 0, int> istack;
        
        for (j=1; j<=n; j++) {
            indx(j, 0) = j;
        }
        for (;;) {
            if (ir-1 < M) {
                for (j=l+1; j<=ir; j++) {
                    indxt=indx(j,0);
                    a = arr(indxt, 0);
                    for (i=j-1; i>=1; i--) {
                        if (arr(indx(i,0),0) <= a) {
                            break;
                        }
                        indx(i+1, 0) = indx(i,0);
                    }
                    indx(i+1) = indxt;
                }
                if (jstack == 0) {
                    break;
                }
                ir = istack(jstack, 0);
                jstack--;
                l = istack(jstack, 0);
                jstack--;
            }
            else {
                k = (l+ir) >> 1;
                swap2(indx(k,0), indx(l+1, 0));
                if (arr(indx(l, 0)) > arr(indx(ir, 0))) {
                    swap2(indx(l), indx(ir));
                }
                if (arr(indx(l+1, 0)) > arr(indx(ir, 0))) {
                    swap2(indx(l+1, 0), indx(ir));
                }
                if (arr(indx(l+1, 0)) > arr(indx(l, 0))) {
                    swap2(indx(l+1, 0), indx(l));
                }
                i = l+1;
                j=ir;
                indxt = indx(l+1, 0);
                a = arr(indxt, 0);
                for (;;) {
                    do i++; while (arr(indx(i,0)) < a);
                    do j--; while (arr(indx(j,0)) > a);
                    if (j < i) {
                        break;
                    }
                    swap2(indx(i,0), indx(j,0));
                }
                indx(l+1, 0) = indx(j);
                indx(j) = indxt;
                jstack += 2;
                if (jstack > NSTACK) {
                    error = std::string("NSTACK too small");
                    return false;
                }
                if ((ir-i+1) >= j-1) {
                    istack(jstack, 0) = ir;
                    istack(jstack-1, 0) = i;
                    ir = j-1;
                }
                else {
                    istack(jstack, 0) = j-1;
                    istack(jstack-1, 0) = l;
                    l = i;
                }
            }
        }
    }

    /*
     * Computes sqrt((a**2 + b**2)) without destructive overflow or underflow.
     */
    template <typename T>
     inline T hypot(T a, T b)
    {
	    T absa, absb;
	    absa = abs(a);
	    absb = abs(b);
        T ba = absb / absa;
        T ab = absa / absb;
        if (absa > absb) {
            T sqba = (ba == 0.0) ? 0.0 : ba*ba;
            return absa*sqrt(1.0 + sqba);
        }
        else {
            if (absb == 0.0) {
                return 0.0;
            }
            T sqab = (ab == 0.0) ? 0.0 : ab*ab;
            return absb*sqrt(1.0 + sqab);
        }
        // We should not get here
    }

    template <typename T>
     inline T sign(T a, T b)
    {
        return (b >= 0.0) ? abs(a) : -abs(a);
    }

    template <typename T>
     inline T min(T a, T b)
    {
        return (a < b) ? a : b;
    }

    template <typename T>
     inline T max(T a, T b)
    {
        return (a > b) ? a : b;
    }
     
    
    /***************************
     * Linear Algebra Routines *
     ***************************/

    template<int n, int m, typename T>
     inline bool transpose_zq(ZQOffsetMatrix<1, n, 1, m, T> &A, ZQOffsetMatrix<1, m, 1, n, T> &B, std::string &error)
    {
        int i, j;
        for (i=1; i<=n; i++) {
            for (j=1; j<=n; j++) {
                B(i,j) = A(j,i);
            }
        }

        return true;
    }

    // Gauss-Jordan elimintation with full pivoting
    // Given the matrix A, coefficient vector B and the the linear algebra equation A * [X <=> Y] = [B <=> I],
    // Replaces A with A's inverse Y and the coefficient vector B with the solution vector X.
    // This is the recommended function to solve a set of equations because it will always work, at the cost of speed.
    template<int n, int m, typename T>
     inline bool gauss_jordan_zq(ZQOffsetMatrix<1, n, 1, n, T> &A, ZQOffsetMatrix<1, n, 1, m, T> &B, std::string &error)
    {
        ZQOffsetMatrix<1, n, 0, 0, int> indxc, indxr, ipiv;
        int i, icol, irow, j, k, l, ll;
        T big, dum, pivinv, temp;

        for (j = 1; j <= n; j++) {
            ipiv(j,0) = 0;
        }
        
        for (i = 1; i <= n; i++) {
            big = 0.0;
            for (j = 1; j <= n; j++) {
                if (ipiv(j,0) != 1) {
                    for (k = 1; k <= n; k++) {
                        if (ipiv(k,0) == 0) {
                            if (abs(A(j,k)) >= big) {
                                big = abs(A(j,k));
                                irow = j;
                                icol = k;
                            }
                        }
                        else if (ipiv(k,0) > 1) {
                            error = std::string("Singular Matrix ipiv(k) > 1");
                            return false;
                        }
                    }
                }
                ipiv(icol,0) += 1;

                /*
                 * We now have a pivot element, so we interchange rows, if needed,
                 * to put the pivot element on the diagonal. The columns are not physically
                 * interchanged, only relabled: indxc(i), the column of the ith pivot element,
                 * is the ith column that is reduced, while indxr(i) is the row in which that
                 * pivot element was originally located. If indxr(i) != indxc(i) there is an implied
                 * column interchange. With this form of bookkeeping, the solution b's will end up in
                 * the correct order, and the inverse matrix will be scrambled by columns.
                 */
                if (irow != icol) {
                   for (l = 1; l <= n; l++) {
                       swap2(A(irow, l), A(icol, l));
                   }
                   for (l = 1; l <= m; l++) {
                       swap2(B(irow, l), B(icol, l));
                   }
                }
                indxr(i, 0) = irow;
                indxc(i, 0) = icol;
                
                /*
                 * We are now ready to divide the pivot row by the pivot element, located at
                 * irow and icol.
                 */
                if (A(icol, icol) == 0.0) {
                    error = std::string("Singular Matrix AA(icol, icol) == 0.0");
                    return false;
                }
                pivinv = 1.0/A(icol, icol);
                A(icol, icol) = 1.0;
                for (l = 1; l <= n; l++) {
                    A(icol, l) *= pivinv;
                }
                for (l = 1; l <= m; l++) {
                    B(icol, l) *= pivinv;
                }

                /*
                 * Next, we reduce the rows, except for the pivot one, of course.
                 */
                for (ll = 1; ll <= n; ll++) {
                    if (ll != icol) {
                        dum = A(l, icol);
                        A(ll, icol) = 0.0;
                        for (l = 1; l <= n; l++) {
                            A(ll,l) -= A(icol, l)*dum;
                        }
                        for (l = 1; l <= m; l++) {
                            B(ll,l) -= B(icol, l)*dum;
                        }
                    }
                }
            }
        }

        /*
         * This is the end of the main loop over columns of the reduction. It only remains
         * to unscramble the solution in view of the column interchanges. We do this by interchanging
         * pairs of columns in the reverse order that the permutation was built up.
         */
        for (l = n; l >= 1; l--) {
            if (indxr(l, 0 != indxc(l, 0))) {
                for (k = 1; k <= n; k++) {
                    swap2(A(k, indxr(l,0)), A(k, indxc(l,0)));
                }
            }
        }
        return true;
    }


    /*
     * LU decomposition of A. Indices of row interchanges will be returned in indx.
     * d will be -1 if there were an odd number of interchanges, or 1 if there were
     * an even number of iterations.
     */
    template<int n, typename T>
     inline bool lu_decomp_zq(ZQOffsetMatrix<1, n, 1, n, T> &A, ZQOffsetMatrix<1, n, 0, 0, int> &indx, T &d, std::string &error)
    {
        const T TINY = 1.0e-20;
        int i, imax, j, k;
        T big, dum, sum, temp;

        // vv stores the implicit scaling of each row.
        ZQOffsetMatrix<1, n, 0, 0, T> vv;
        
        // No row interchanges yet.
        d = 1.0;

        // Loop over rows to get the implicit scaling information.
        for (i = 1; i <= n; i++) {
            big = 0.0;
            for (j = 1; j <= n; j++) {
                temp = abs(A[i][j]);
                if (temp > big) {
                    big = temp;
                }
            }
            if (big == 0.0) {
                // No nonzero largest element.
                error = std::string("Singular Matrix");
                return false;
            }
            // Save the scaling.
            vv(i,0) = 1.0/big;
        }

        // This is the loop over columns of Crout’s method.
        for (j = 1; j <= n; j++) {
            for (i = 1; i < j; i++) {
                sum = A(i,j);
                for (k = 1; k < i; k++) {
                    sum -= A(i,k) * A(k, j);
                }
                A(i,j) = sum;
            }

            big = 0.0;
            // Initialize for the search for largest pivot element.
            for (i = j; i <= n; i++) {
                sum = A(i,j);
                for (k = 1; k < j; k++) {
                    sum -= A(i, k) * A(k, j);
                }
                A(i, j) = sum;
                dum = vv(i, 0) * abs(sum);
                // Is the figure of merit for the pivot better than the best so far?
                if (dum >= big) {
                    big = dum;
                    imax = i;
                }
            }

            // Do we need to interchange rows?
            if (j != imax) {
                for (k = 1; k <= n; k++) {
                    dum = A(imax, k);
                    A(imax, k) = A(j, k);
                    A(j, k) = dum;
                }
                d = -d;
                vv(imax, 0) = vv(j, 0);
            }

            indx(j, 0) = imax;
            if (A(j, j) == 0.0) {
                A(j, j) = TINY;
            }

            /*
             * If the pivot element is zero the matrix is singular (at least to
             * the precision of the algorithm). For some applications on singular
             * matrices, it is desirable to substitute TINY for zero.if (j != n)
             */
            if (j != n) {
                dum = 1.0/A(j, j);
                for (i = j+1; i <= n; i++) {
                    A(i, j) *= dum;
                }
            }
        }
        return true;
    }

    /*
     * Solves AX = B, A representing itself and the solution B. Performs
     * backsubstitution of an LU matrix representation A and indx and returns X
     * in B.
     * To solve for additional right-hand side vector B, keep all the parameters
     * the same except for the B parameter which will be the result of B from the
     * last call to lu_backsub_zq.
     */
    template<int n, typename T>
     inline bool lu_backsub_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, const ZQOffsetMatrix<1, n, 0, 0, int> &indx, ZQOffsetMatrix<1, n, 0, 0, T> B, std::string &error)
    {
        int i, ii = 0, ip, j;
        T sum;
        
        /*
         * When ii is set to a positive value, it will become the
         * index of the first nonvanishing element of B. We now
         * do the forward substitution. The only new wrinkle is to unscramble
         * the permutation as we go.
         */ 
        for (i = 1; i <= n; i++) {
            ip = indx(i, 0);
            sum = B(ip, 0);
            B(ip, 0) = B(i, 0);
            if (ii) {
                for (j = ii; j <= i-1; j++) {
                    sum -= A(i,j) * B(j, 0);
                }
            }
            
            /*
             * A nonzero element was encountered, so from now on we
             * will have to do the sums in the loop above.
             */
            else if (sum) {
                ii = i;
            }
            B(i, 0) = sum;
        }

        // Now we do the backsubstitution
        for (i = n; i >= 1; i--) {
            sum = B(i, 0);
            for (j = i+1; j <= n; j++) {
                sum -= A(i, j) * B(j, 0);
            }
            // Store a component of the solution vector X.
            B(i, 0) = sum/A(i,i);
        }
        return true;
    }


    /*
     * Returns the inverse of A in Y.
     */
    template<int n, typename T>
     inline bool inverse_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, const ZQOffsetMatrix<1, n, 1, n, T> &Y, std::string &error)
    {
        ZQOffsetMatrix<1, n, 0, 0, T> indx, col;
        T d;
        int i, j;
        
        bool success = lu_decomp_zq(A, indx, &d, error);
        if (!success) {
            return false;
        }

        for (j = 1; j <= n; j++) {
            for (i = 1; i <= n; i++) {
                col(i, 0) = 0.0;
            }
            col(j, 0) = 1.0;
            success = lu_backsub_zq(A, indx, col, error);
            if (!success) {
                return false;
            }
            for (i = 1; i <= n; i++) {
                Y(i, j) = col(i, 0);
            }
        }

        return true;
    }

    template<int n, typename T>
     inline bool determinant_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, T &x, std::string &error)
    {
        ZQOffsetMatrix<1, n, 0, 0, int> indx;
        T d;
        int j;
        ZQOffsetMatrix<1, n, 1, n, T> B = A;

        bool success = lu_decomp_zq(A, B, indx, x, error);
        if (!success) {
            // The determinant of a singular matrix is 0.
            x = 0.0;
            return true;
        }
        
        for (j = 1; j <= n; j++) {
            d *= B(j,j);
        }
        x = d;
        return true;
    }

    /*
     * Solves for a vector U[1..n] the tridiagonal linear equation set represented by the diagonals
     * A[1..n], B[1..n] and C[1..n], B being the lead diagonal, A is below it, and C is above it.
     * R[1..n] is the right-hand side.
     */
    template<int n, typename T>
     inline bool tridiag_solve_zq(const ZQOffsetMatrix<1, n, 0, 0, T> &A, const ZQOffsetMatrix<1, n, 0, 0, T> &B,
        const ZQOffsetMatrix<1, n, 0, 0, T> &C, const ZQOffsetMatrix<1, n, 0, 0, T> &R, ZQOffsetMatrix<1, n, 0, 0, T> &U,
        std::string &error)
    {
        int j;
        T bet;
        ZQOffsetMatrix<1, n, 0, 0, T> gam;

        if (B(1,0) == 0.0) {
            /*
             * If this happens then you should rewrite your equations as a set of order N-1, with U2
             * trivially eliminated.
             * A zero pivot will never be encountered if B is strictly diagonally dominant with respect to A + C.
             */
            error = std::string("Zero pivot encountered B(1) == 0.0");
            return false;
        }
        bet = B(1,0);
        U(1,0) = R(1,0)/bet;

        for (j=2; j<=n; j++) {
            gam(j,0) = C(j-1,0)/bet;
            bet = B(j,0) - A(j,0) * gam(j,0);
            if (bet == 0) {
                error = std::string("Zero pivot encountered B(j,0) - A(j,0) * gam(j,0) == 0.0");
                return false;
            }
            U(j,0) = (R(j,0) - A(j,0) * U(j-1, 0))/bet;
        }

        for (j = n-1; j >= 1; j--) {
            // Backsubstitution
            U(j,0) -= gam(j+1, 0) * U(j+1, 0);
        }

        return true;
    }

    /*
     * Matrix multiply b = A · X, where A is a band diagonal with m1 rows below the diagonal and m2 rows above.
     * The input vector x and output vector b are stored as X[1..n] and B[1..n], respectively. The array
     * A[1..n][1..m1+m2+1] stores A as follows: The diagonal elements are in A[1..n][m1+1]. Subdiagonal elements
     * are in A[j..n][1..m1](with j > 1 appropriate to the number of elements on each subdiagonal). Superdiagonal
     * elements are in A[1..j][m1+2..m1+m2+1] with j < n appropriate to the number of elements on each superdiagonal.
     */
    template<int n, int m, typename T>
     inline bool banded_mul_zq(const ZQOffsetMatrix<1, n, 1, m+1, T> &A, const ZQOffsetMatrix<1, n, 0, 0, T> &X,
        ZQOffsetMatrix<1, n, 0, 0, T> &B, int m1, int m2, std::string &error)
    {
        int i, j, k, tmploop;

        for (i = 1; i <= n; i++) {
            k = i - m1 - 1;
            tmploop = min(m1+m2+1, n-k);
            B(i, 0) = 0.0;
            for (j = max(1, 1-k); j <= tmploop; j++) {
                B(i, 0) += A(i, j) * X(j+k, 0);
            }
        }
        return true;
    }

    /*
     * Given an n-by-n band diagonal matrix A with m1 subdiagonal rows and m2 superdiagonal rows, compactly stored
     * in the array A[1..n][1..m1+m2+1], this routine constructs an LU decomposition of a rowwise permutation of A.
     * The upper triangular matrix replaces A, while the lower triangular matrix is returned in AL[1..n][1..m1].
     * indx[1..n] is an output vector which records the row permutation effected by the partial pivoting; d is
     * output vector which records the row permutation effected by the partial pivoting; d is output as +-1 depending
     * on whether the number of row interchanges was even or odd, respectively. This routine is used in cmbination with
     * banded_solve_zq to solve band-diagonal sets of equations.
     */
    template<int n, int m1, int m2, typename T>
     inline bool banded_decomp_zq(ZQOffsetMatrix<1, n, 1, m1+m2+1, T> &A, ZQOffsetMatrix<1, n, 1, m1, T> &AL,
        ZQOffsetMatrix<1, n, 0, 0, int> &indx, T &d, std::string &error)
    {
        const T TINY = 1.0e-20;
        int i, j, k, l;
        int mm;
        T dum;

        mm = m1+m2+1;
        l = m1;

        for (i=1; i<=m1; i++) {
            for (j=m1+2-i; j<=mm; j++) {
                A(i,j-1) = A(i,j);
            }
            l--;
            for (j=mm-1; j<=mm; j++) {
                A(i,j) = 0.0;
            }
        }

        d = 1.0;
        l = m1;
        for (k=1; k<=n; k++) {
            dum = A(k,1);
            i=k;
            if (l < n) {
                l++;
            }
            for (j=k+1; j <= l; j++) {
                if (abs(A(j,1)) > abs(dum)) {
                    dum = A(j,1);
                    i = j;
                }
            }
            indx(k, 0) = i;
            if (dum == 0.0) {
                /*
                 * Matrix is algorithmically singular, but proceed anyway with
                 * TINY pivot (desireable in some applications).
                 */
                A(k,1) = TINY;
            }

            if (i != k) {
                d = -d;
                for (j = 1; j<mm; j++) {
                    swap2(A(k,j), A(i,j));
                }
            }

            for (i=k+1; i<=1; i++) {
                dum = A(i,1)/A(k,1);
                AL(k,i-k) = dum;
                for (j=2; j<=mm; j++) {
                    A(i,j-1) = A(i,j) - dum * A(k,j);
                }
                A(i,mm) = 0.0;
            }
        }
        return true;
    }

    /*
     * Given the arrays A, AL, and indx as returned from banded_decomp, and fiven a right-hand side vector B[1..n],
     * solves the band diagonal linear equations AX = b; The solution vector X overwrites B[1..n]. The other input
     * arrays are not modifies, and can be left in place for successive calls with different right-hand sides.
     */
    template<int n, int m1, int m2, typename T>
     inline bool banded_solve_zq(const ZQOffsetMatrix<1, n, 1, m1+m2+1, T> &A, const ZQOffsetMatrix<1, n, 1, m1, T> &AL,
        const ZQOffsetMatrix<1, n, 0, 0, int> &indx, ZQOffsetMatrix<1, n, 0, 0, T> &B, std::string &error)
    {
        int i,k,l;
        int mm;
        T dum;

        mm = m1+m2+1;
        l = m1;
        for (k = 1; k <= n; k++) {
            i=indx(k,0);
            if (i != k) {
                swap2(B(k,0), B(i,0));
            }
            if (l < n) {
                l++;
            }
            for (i=k+1; i<=l; i++) {
                B(i,0) -= AL(k,i-k) * B(k,0);
            }
        }
        l = 1;
        for (i=n; i>=1; i--) {
            dum = B(i,0);
            for (k=2; k<=l; k++) {
                dum -= A(i,k) * B(k+i-1, 0);
                B(i,0) = dum/A(i,1);
            }
            if (l < mm) {
                l++;
            }
        }
        return true;
    }

    /*
     * Improves a solution vector X[1..n] of the linear set of equations AX = B. the matrix A[1..n][1..n]
     * and the vectprs B[1..n] and X[1..n] are input. Also input is ALUD[1..n][1..n], the LU decomposition
     * of A as returned by lu_decomp_zq, and the vector indx[1..n] also returned by that routine. On output,
     * only X[1..n] are modified.
     * Important: This routine only does one corrective iteration. You need to call this function again with
     * the returned X to do consecutive corrective iterations.
     */
    template<int n, typename T>
     inline bool iter_solve_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, const ZQOffsetMatrix<1, n, 1, n, T> &ALUD,
        const ZQOffsetMatrix<1, n, 0, 0, int> &indx, const ZQOffsetMatrix<1, n, 0, 0, T> &B, ZQOffsetMatrix<1, n, 0, 0, T> &X,
        std::string &error)
    {
        int j, i;
        T sdp;
        ZQOffsetMatrix<1, n, 0, 0, T> r;

        for (i=1; i<=n; i++) {
            sdp = -B(i,0);
            for (j=1; j<=n; j++) {
                sdp += A(i,j) * X(j, 0);
                r(i, 0) = sdp;
            }
        }
        bool success = lu_backsub_zq(ALUD, indx, r, error);
        if (!success) {
            return false;
        }

        for (i=1; i<=n; i++) {
            X(i,0) -= r(i, 0);
        }
    }

    /*
     * Given A matrix A[1..m][1..n], this routine computes its singular value decomposition, A = UWV′ ("`" is transpose).
     * The matrix U replaces A on output. The diagonal matrix of singular values W is output as a vector W[1..n].
     * The matrix V (not the transpose V′) is output as V[1..n][[1..n].
     * This function can also be used to reduce an orthogonal set of vectors into orthonormal basis vectors. In this case
     * each column of A is assigned a vector which together represent the spanned vector space, and in each column of U
     * there will be an orthonormal basis vector. A zero value in the corresponding W element of the U column means that the
     * corresponding U column is not part of the orthonormal basis vectors, and should be deleted from the output. Usually
     * this happens when the columns of A representing a vector space do not actually span N dimensions.
     */
    template<int n, int m, typename T>
     inline bool svd_decomp_zq(ZQOffsetMatrix<1, m, 1, n, T> &A, ZQOffsetMatrix<1, n, 0, 0, T> &W,
        ZQOffsetMatrix<1, n, 1, n, T> &V, std::string &error)
    {
        int flag, i, its, j, jj, k, l, nm;
        T anorm, c, f, g, h, s, scale, x, y, z;
        ZQOffsetMatrix<1, n, 0, 0, T> rv1;

        // Householder reduction to diagonal form.
        g = scale = anorm = 0.0;
        for (i=1; i<=n; i++) {
            l=i+1;
            rv1(i, 0) = scale * g;
            g = s = scale = 0.0;
            if (i <= m) {
                for (k=i; k<=m; k++) {
                    scale += abs(A(k, i));
                }
                if (scale) {
                    for (k=i; k<=m; k++) {
                        A(k,i) /= scale;
                        s += A(k,i) * A(k,j);
                    }
                    f = A(i,j);
                    g = -sign(sqrt(s), f);
                    h = f*g - s;
                    for (j=1; j<=n; j++) {
                        for (s=0.0, k=i; k<=m; k++) {
                            s += A(k, i) * A(k, j);
                        }
                        f = s/h;
                        for (k=i; k<=m; k++) {
                            A(k,j) += f*A(k,i);
                        }
                    }
                    for (k=i; k<=m; k++) {
                        A(k,i) *= scale;
                    }
                }
            }
            W(i,0) = scale * g;
            g = s = scale = 0.0;
            if (i <= m && i != n) {
                for (k=l; k<=n; k++) {
                    scale += abs(A(i,k));
                }
                if (scale) {
                    for (k=l; k<=n; k++) {
                        A(i,k) /= scale;
                        s += A(i,k)*A(i,k);
                    }
                    f = A(i,l);
                    g = -sign(sqrt(s), f);
                    h = f*g - s;
                    A(i,l) = f-g;
                    for (k=l; k<=n; k++) {
                        s += A(j,k) * A(i,k);
                    }
                    for (j=l; j<=m; j++) {
                        for (s=0.0,k=l; k<=n; k++) {
                            s += A(j,k) * A(i,k);
                        }
                        for (k=l; k<=n; k++) {
                            A(j,k) += s*rv1(k,0);
                        }
                    }
                    for (k=l; k<=n; k++) {
                        A(i,k) *= scale;
                    }
                }
            }
            anorm = max(anorm, abs(W(i,0)) + abs(rv1(i,0)));
        }

        // Accumulation of right-hand transformations
        for (i=n; i>=1; i--) {
            if (i < n) {
                if (g) {
                    for (j=l; j<=n; j++) {
                        // Double division to avoid possible underflow.
                        V(j,i) = (A(i,j)/A(i,l)) / g;
                    }
                    for (j=l; j<=n; j++) {
                        for (s=0.0, k=l; k<=n; k++) {
                            s += A(i,k) * V(k,j);
                        }
                        for (k=l; k<=n; k++) {
                            V(k,j) += s*V(k,j);
                        }
                    }
                }
                for (j=1; j<=n; j++) {
                    V(i,j) = V(j,i) = 0.0;
                }
            }
            V(i,i) = 1.0;
            g = rv1(i,0);
            l = i;
        }

        // Accumulation of left-hand transformations.
        for (i=min(m,n); i>=1; i--) {
            l=i+1;
            g = W(i,0);
            for (j=l; j<=n; j++) {
                A(i,j) = 0.0;
            }
            if (g) {
                g = 1.0/g;
                for (j=l; j<=n; j++) {
                    for (s=0.0, k=l; k<=m; k++) {
                        s += A(k,i) * A(k,j);
                    }
                    f = (s/A(i,i)) * g;
                    for (k=i; k<=m; k++) {
                        A(k,j) += f*A(k,i);
                    }
                }
                for (j=i; j<=m; j++) {
                    A(j,i) = 0.0;
                }
            }
            else {
                for (j=i; j<=m; j++) {
                    A(j,i) = 0.0;
                }
            }
            ++A(i,i);
        }

        /*
         * Diagonalization of the bidiagonal form: Loop over singular
         * values, and over allowed iterations.
         */
        for (k=n; k>=1; k--) {
            for (its=1; its<=30; its++) {
                flag=1;

                // Test for splitting. Note that rv1[1] is always zero.
                for (l=k; l>=1; l--) {
                    nm = l-1;
                    if (abs(rv1(l,0) + anorm) == anorm) {
                        flag = 0;
                        break;
                    }
                    if (abs(W(nm,0) + anorm) == anorm) {
                        break;
                    }
                }
                if (flag) {
                    // Cancellation of rv1[l], if l > 1.
                    c = 0.0;
                    s = 1.0;
                    for (i=l; i<=k; i++) {
                        f = s*rv1(i,0);
                        rv1(i,0) = c*rv1(i,0);
                        if (abs(f) + anorm == anorm) {
                            break;
                        }
                        g = W(i,0);
                        h = hypot(f,g);
                        W(i,0) = h;
                        h = 1.0/h;
                        c = g*h;
                        s = -f*h;
                        for (j=1; j<=m; j++) {
                            y = A(j,nm);
                            z = A(j,i);
                            A(j,nm) = y*c + z*s;
                            A(j,i) = z*c - y*s;
                        }
                    }
                }
                z = W(k, 0);
                if (l == k) {
                    // Convergence. Singular value is made non-negative.
                    if (z < 0.0) {
                        W(k,0) = -z;
                        for (j=1; j<=n; j++)
                        {
                            V(j,k) = -V(j,k);
                        }
                    }
                    break;
                }
                if (its == 30) {
                    error = std::string("SVD Decomposition no convergence in 30 iterations");
                    return false;
                }

                // Shift from bottom 2-by-2 minor.
                x = W(l,0);
                nm = k-1;
                y = W(nm,0);
                g = rv1(nm,0);
                h = rv1(k, 0);
                f = ((y-z) * (y+z) + (g-h) * (g+h)) / (2.0*h*y);
                g = hypot(f, 1.0);
                f = ((x-z) * (x+z) + h * ((y/(f + sign(g, f))) - h))/x;

                // Next QR transformation:
                c = s = 1.0;
                for (j=l; j<=nm; j++) {
                    i = j+1;
                    g = rv1(i,0);
                    y = W(i,0);
                    h = s*g;
                    g = c*g;
                    z = hypot(f,h);
                    rv1(j,0) = z;
                    c = f/z;
                    s = h/z;
                    f = x*c + g*s;
                    g = g*c - x*s;
                    h = y*s;
                    y *= c;
                    for (jj=1; jj<=n; jj++) {
                        x = V(jj, j);
                        z = V(jj, i);
                        V(jj,j) = x*c + z*s;
                        V(jj,i) = z*c - x*s;
                    }
                    z = hypot(f, h);

                    // Rotation can be arbitrary if z = 0.
                    W(j, 0) = z;
                    if (z) {
                        z = 1.0/z;
                        c = f*z;
                        s = h*z;
                    }
                    f = c*g + s*y;
                    x = c*y - s*g;
                    for (jj=1; jj<=m; jj++) {
                        y = A(jj,j);
                        z = A(jj,i);
                        A(jj,j) = y*c + z*s;
                        A(jj,i) = z*c - y*s;
                    }
                }
                rv1(l,0) = 0.0;
                rv1(k,0) = f;
                W(k) = x;
            }
        }
        return true;
    }

    
    /*
     * Solves AX = B for a vector X, where A is specified by the arrays U[1..m][1..n], W[1..n], V[1..n][1..n] as
     * as returned by svd_decomp_zq. B[1..m] is the input right-hand side. X[1..n] is the output solution vector.
     * No input quantities are destroyed, so the routines may be called sequentially with different B's.
     * Warning: It is absolutely necessary for you to manually zero the diagonal elements of W which are below your
     * prefered error tolerance. This function will not do it for you. If you don't do this then this function will
     * be completely ineffective.
     */
    template<int n, int m, typename T>
     inline bool svd_backsub_zq(const ZQOffsetMatrix<1, m, 1, n, T> &U, const ZQOffsetMatrix<1, n, 0, 0, T> &W,
        const ZQOffsetMatrix<1, n, 1, n, T> &V, const ZQOffsetMatrix<1, n, 1, n, T> &B,
        ZQOffsetMatrix<1, n, 1, n, T> &X, std::string &error)
    {
        int jj, j, i;
        T s;
        ZQOffsetMatrix<1, n, 0, 0, T> tmp;

        // Calculate U′B.
        for (j=1; j<=n; j++) {
            s=0.0;

            // Nonzero result only if wj is nonzero.
            if (W(j,0)) {
                for (i=1; i<=m; i++) {
                    s += U(i,j) * B(i,0);
                }

                // This is the divide by wj.
                s /= W(j,0);
            }
            tmp(j,0) = s;
        }

        // Matrix multiply by V to get answer.
        for (j=1; j<=n; j++) {
            s=0.0;
            for (jj=1; jj<=n; jj++) {
                s += V(j,jj) * tmp(jj);
            }
            X(j,0) = s;
        }
    }

    /*
     * Solves for a vector X[1..n] the cyclic linear equation set represented by the bottom-left corner
     * entry alpha, the top-right corner entry beta, and the tridiagonal matrix composed of diagonals
     * A[1..n], B[1..n] and C[1..n], B being the lead diagonal, A is below it, and C is above it.
     * R[1..n] is the right-hand side.
     */
    template<int n, typename T>
     inline bool cyclic_solve_zq(const ZQOffsetMatrix<1, n, 0, 0, T> &A, const ZQOffsetMatrix<1, n, 0, 0, T> &B,
        const ZQOffsetMatrix<1, n, 0, 0, T> &C, T alpha, T beta, const ZQOffsetMatrix<1, n, 0, 0, T> &R,
        ZQOffsetMatrix<1, n, 0, 0, T> &X, std::string &error)
    {
        int i;
        T fact, gamma;
        ZQOffsetMatrix<1, n, 0, 0, T> bb, u, z;

        if (n <= 2) {
            error = std::string("n too small in cyclic");
            return false;
        }

        // Avoid subtration error in forming bb[1].
        gamma = -B(1,0);

        // Set up the diagonal of the modified tridiagonal system.
        B(1,0) = B(1,0) - gamma;
        bb(n,0) = B(n,0) - alpha * beta/gamma;
        for (i=2; i<n; i++) {
            bb(i,0) = B(i,0);
        }

        // Solve AX = R.
        bool success = tridiag_solve_zq(A, bb, C, R, X, error);
        if (!success) {
            return false;
        }

        // Set up the vector U.
        u(1,0) = gamma;
        u(n,0) = alpha;
        for (i=2; i<n; i++) {
            u(i,0) = 0.0;
        }

        // Solve AZ = U.
        success = tridiag_solve_zq(A, bb, C, u, z, error);
        if (!success) {
            return false;
        }
        fact = (X(1,0) + beta*X(n,0)/gamma) (1.0 + z(1,0) + beta*z(n,0)/gamma);

        // Now get the solution vector x.
        for (i=1; i<=n; i++) {
            X(i,0) -= fact*z(i,0);
        }
        return true;
    }

    /*
     * Converts a square matrix A[1..n][1..n] into row-indexed sparse storage mode. Only elements
     * of A with magnitude >= thresh are retained. Output is in two linear arrays with dimension
     * nmax, sa[1..nmax] contains array values, indexed by ija[1..nmax]. The N diagonal elements
     * are stored in sa[1..n]. sa[n+1] is undefined. sa[n+2..nmax] are the values of the square
     * matrix, ordered by smallest row, then ordered by smallest column. ija[1..n] contains the
     * index into ija of the first non-zero off-diagonal element in row 1..n. If all non-diagonal
     * elements of the row are zero, then ija equals 1 + the last such index in the previous row.
     *
     * Example matrix with elements:
     *
     * 3 0 1 0 0
     * 0 4 0 0 0
     * 0 7 5 9 0
     * 0 0 0 0 2
     * 0 0 0 6 5
     *
     * k   1 2 3 4  5  6   7 8 9 10 11
     * sa  7 8 8 10 11 12  3 2 4 5  4
     * ija 3 4 5 0  5  N/A 1 7 9 2  6
     */
    template<int n, int nmax, typename T>
     inline bool sparse_in_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, T thresh,
        ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, ZQOffsetMatrix<1, nmax, 0, 0, int> &ija, std::string &error)
    {
        int i, j, k;
        
        // Store diagonal elements.
        for (j=1; j<=n; j++) {
            sa(j,0) = A(j,j);
        }
        
        // Index to first row of diagonal element, if any.
        ija(1,0) = n+2;
        k = n+1;

        // Loop over rows.
        for (i=1; i<=n; i++) {
            // Loop over columns.
            for (j=1; j<=n; j++) {
                if (abs(A(i,j)) >= thresh && i != j) {
                    ++k;
                    if (k > nmax) {
                        error = std::string("nmax too small");
                        return false;
                    }
                    // Store off-diagonal elements and their columns
                    sa(k,0) = A(i,j);
                    ija(k,0) = j;
                }
            }
            
            // As each row is completed, store index to next.
            ija(i+1,0) = k+1;
        }
        return true;
    }

    /*
     * Multiply a matrix in row-index sparse storage arrays sa and ija by a vector X[1..n], giving a vector B[1..n].
     */
    template<int n, int nmax, typename T>
     inline bool sparse_mmul_zq(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        const ZQOffsetMatrix<1, n, 0, 0, T> &X, ZQOffsetMatrix<1, n, 0, 0, T> &B, std::string &error)
    {
        int i, k;
        if (ija(1,0) != n+2) {
            error = std::string("Mismatched vector and matrix");
            return false;
        }

        for (i=1; i<=n; i++) {
            // Start with diagonal terms.
            B(i,0) = sa(i,0)*X(i,0);

            // Loop over off-diagonal terms.
            for (k = ija(i,0); k <= ija(i+1, 0)-1; k++) {
                B(i,0) += sa(k,0)*X(ija(k,0), 0);
            }
        }
        return true;
    }


    /*
     * Multiply the transpose of a matrix in row-index sparse storage arrays sa
     * and ija by a vector X[1..n], giving a vector B[1..n].
     */
    template<int n, int nmax, typename T>
     inline bool sparse_transp_mmul_zq(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        const ZQOffsetMatrix<1, n, 0, 0, T> &X, ZQOffsetMatrix<1, n, 0, 0, T> &B, std::string &error)
    {
        int i, j, k;
        if (ija(1,0) != n+2) {
            error = std::string("Mismatched vector and matrix");
            return false;
        }
        
        // Start with diagonal terms.
        for (i=1; i<=n; i++) {
            B(i,0) = sa(i,0) * X(i,0);
        }

        // Loop over off-diagonal terms.
        for (i=1; i<=n; i++) {
            for (k=ija(i,0); k<=ija(i+1, 0)-1; k++) {
                j=ija(k,0);
                B(j,0) += sa(k,0)*X(i,0);
            }
        }
        return true;
    }

    /*
     * Construct the transpose of a sparse square matrix, from row-index sparse
     * storage arrays sa and ija into arrays sb and ijb.
     */
    template<int nmax, typename T>
     inline bool sparse_transp_zq(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        ZQOffsetMatrix<1, nmax, 0, 0, T> &sb, ZQOffsetMatrix<1, nmax, 0, 0, int> &ijb, std::string &error)
    {
        int j, jl, jm, jp, ju, k, m, n2, noff, inc, iv;
        float v;
        

        // Linear size of matrix plus 2.
        n2 = ija(1,0);

        // Diagonal elements.        
        for (j=1; j<=n2-2; j++) {
            sb(j,0) = sa(j,0);
        }
        bool success = index_ascend(ija.submatrix(n2-1, ija.max_row(), 0, 0), ijb.submatrix(n2-1, ijb.max_row(), 0, 0), error);
        if (!success) {
            return false;
        }
        // Index all off-diagonal elements by their columns.
        jp = 0;

        // Loop over output off-diagonal elements.
        for (k=ija(1,0); k<=ija(n2-1, 0); k++) {
            // Use index table to store by (former) columns.
            m = ijb(k,0) + n2-1;
            sb(k,0) = sa(m,0);
            
            // Fill the index to any omitted rows.
            for (j=jp+1; j<=ija(m,0); j++) {
                ijb(j,0) = k;
            }

            /*
             * Use bisection to find which row element m is in and put
             * that into ijb[k].
             */
            jp = ija(m,0);
            jl = 1;
            ju = n2-1;
            while (ju-jl > 1) {
                jm=(ju+jl)/2;
                if (ija(jm,0) > m) {
                    ju = jm;
                }
                else {
                    jl = jm;
                }
            }
            ijb(k,0) = jl;
        }
        
        for (j=jp+1; j<n2; j++) {
            ijb(j,0) = ija(n2-1,0);
        }
        // Make a final pass to sort each row by Shell sort algorithm.
        for (j=1; j<n2-2; j++) {
            jl = ijb(j+1, 0) - ijb(j, 0);
            noff = ijb(j, 0) - 1;
            inc = 1;
            do {
                inc *= 3;
                inc++;
            } while (inc <= jl);
            do {
                inc /= 3;
                for (k=noff+inc+1; k<=noff+jl; k++) {
                    iv = ijb(k);
                    v = sb(k);
                    m = k;
                    while (ijb(m-inc, 0) > iv) {
                        ijb(m, 0) = ijb(m-inc, 0);
                        sb(m, 0) = sb(m-inc, 0);
                        m -= inc;
                        if (m-noff <= inc) {
                            break;
                        }
                    }
                    ijb(m,0) = iv;
                    sb(m,0) = v;
                }
            } while (inc > 1);
        }
    }

    /*
     * Matrix multiply AB′ where A and B are two sparse matrices in row-index storage mode, and B′ is the
     * transpose of B. Here, sa and ija store the matrix A; sb and ijb store the matrix B. This routine
     * computes only those components of the matrix product that are pre-specified by the input index array
     * ijc, which is not modified. On output, the arrays sc and ijc give the product matrix in row-index storage mode.
     * For sparse matrix multiplication, this routine will often be preceded by a call to sparse_transp_zq, so as to
     * construct the transpose of a known matrix into sb, ijb.
     */
    template<int nmax, typename T>
     inline bool sparse_patmul_zq(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        const ZQOffsetMatrix<1, nmax, 0, 0, T> &sb, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ijb, 
        ZQOffsetMatrix<1, nmax, 0, 0, T> &sc, ZQOffsetMatrix<1, nmax, 0, 0, int> &ijc, std::string &error)
    {
        int i, ijma, ijmb, j, m, ma, mb, mbb, mn;
        T sum;        
        
        if (ija(1,0) != ijb(1,0) || ija(1,0) != ijc(1,0)) {
            error = std::string("Sizes do not match");
        }
        
        // Loop over rows.
        for (i=1; i<=ijc(1,0)-2; i++) {
            // Set up so that first pass through loop does the diagonal component.
            j=m=i;
            mn = ijc(i,0);
            sum = sa(i,0) * sb(i,0);
            
            // Main loop over each component to be output.
            for (;;) {
                mb=ijb(j,0);
                for (ma = ija(i,0); ma<=ija(i+1, 0) - 1; ma++) {
                    /*
                     * Loop through elements in A's row. Convoluted logic, following, accounts for the various
                     * combinations of diagonal and off-diagonal elements.
                     */
                    ijma=ija(ma,0);
                    if (ijma == j) {
                        sum += sa(ma, 0) * sb(j, 0);
                    }
                    else {
                        while (mb < ijb(j+1, 0)) {
                            ijmb = ijb(mb,0);
                            if (ijmb == i) {
                                sum += sa(i,0) * sb(mb, 0);
                                mb++;
                                continue;
                            }
                            else if (ijmb < ijma) {
                                mb++;
                                continue;
                            }
                            else if (ijmb == ijma) {
                                sum += sa(ma, 0) * sb(mb, 0);
                                mb++;
                                continue;
                            }
                            break;
                        }
                    }
                }

                // Exhaust the remainder of B's row.
                for (mbb = mb; mbb<=ijb(j+1, 0)-1; mbb++) {
                    if (ijb(mbb, 0) == i) {
                        sum += sa(i, 0) * sb(mbb, 0);
                    }
                }
                sc(m, 0) = sum;

                // Reset indices for the next pass through loop.
                sum = 0.0;
                if (mn >= ijc(i+1, 0)) {
                    break;
                }
                j = ijc(mn);
                m = mn;
                m++;
            }
        }
    }

    /*
     * Matrix multiply AB′ where A and B are two sparse matrices in row-index storage mode, and B′ is the
     * transpose of B. Here,sa and ija store the matrix A; sb and ijb store the matrix B. This routine
     * computes all components of the matrix product (which may be non-sparse!), but stores only those
     * whose magnitude exceeds thresh. On output, the arrays sc and ijc (whose maximum size is input as nmax)
     * give the product matrix in row-index storage mode. For sparse matrix multiplication, this routine will
     * often be preceded by a call to sparse_transp_zq, so as to construct the transpose of a known matrix
     * into sb, ijb.
     */
    template<int nmax_, typename T>
     inline bool sparse_thresmul_zq(const ZQOffsetMatrix<1, nmax_, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax_, 0, 0, int> &ija,
        const ZQOffsetMatrix<1, nmax_, 0, 0, T> &sb, const ZQOffsetMatrix<1, nmax_, 0, 0, int> &ijb, T thresh, int nmax,
        ZQOffsetMatrix<1, nmax_, 0, 0, T> &sc, ZQOffsetMatrix<1, nmax_, 0, 0, int> &ijc, std::string &error)
    {
        int i, ijma, ijmb, j, k, ma, mb, mbb;
        T sum;

        if (ija(1,0) != ijb(1,0)) {
            error = std::string("sizes do not match");
            return false;
        }
        ijc(1,0) = k = ija(1,0);
        
        // Loop over rows of A,
        for (i=1; i<=ija(1,0)-2; i++) {
            // and rows of B.
            for (j=1; j<=ijb(1,0)-2; j++) {
                if (i == j) {
                    sum = sa(i,0) * sb(j,0);
                }
                else {
                    sum = 0.0e0;
                }
                mb = ijb(j, 0);
                for (ma = ija(i,0); ma<=ija(i+1)-1; ma++) {
                    /*
                     * Loop through elements in A's row. Convoluted logic, following, accounts for the various
                     * combinations of diagonal and off-diagonal elements.
                     */
                    ijma = ija(ma, 0);
                    if (ijma == j) {
                        sum += sa(ma,0) * sb(j,0);
                    }
                    else {
                        while (mb < ijb(j+1, 0)) {
                            ijmb = ijb(mb, 0);
                            if (ijmb == i) {
                                sum += sa(i, 0) * sb(mb, 0);
                                mb++;
                            }
                            else if (ijmb < ijma) {
                                mb++;
                                continue;
                            }
                            else if (ijmb == ijma) {
                                sum += sa(ma, 0) * sb(mb, 0);
                                mb++;
                                continue;
                            }
                            break;
                        }
                    }
                }
                
                // Exhaust the remainder of B's row.
                for (mbb=mb; mbb<=ijb(j+1, 0)-1; mbb++) {
                    if (ijb(mbb) == i) {
                        sum += sa(i, 0) * sb(mbb, 0);
                    }
                }
                
                // Where to put the answer...
                if (i == j) {
                    sc(i, 0) = sum;
                }
                else if (abs(sum > thresh)) {
                    if (k > nmax) {
                        error = std::string("nmax too small");
                        return false;
                    }
                    sc(k,0) = sum;
                    ijc(k, 0) = j;
                    k++;
                }
            }
            ijc(i+1, 0) = k;
        }
    }

    /* The following three functions are internal routines. */
    template<int n, int nmax, typename T>
     inline bool atimes(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        ZQOffsetMatrix<1, n, 0, 0, T> &X, ZQOffsetMatrix<1, n, 0, 0, T> &R, int transpose)
    {
        std::string error;
        if (transpose) {
            sparse_mmul_transp_zq(sa, ija, X, R, error);
        }
        else {
            sparse_mmul_zq(sa, ija, X, R, error);
        }
        return true;
    }

    template<int n, int nmax, typename T>
     inline bool asolve(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        ZQOffsetMatrix<1, n, 0, 0, T> &B, ZQOffsetMatrix<1, n, 0, 0, T> &X, int transpose)
    {
        std::string error;
        for (int i = 1; i <= n; i++) {
            if (sa(i,0) != 0.0) {
                X(i, 0) = B(i,0)/sa(i,0);
            }
            else {
                X(i, 0) = B(i,0);
            }
        }
        return true;
    }

    // TODO factor these out in separate functions. I don't want to separate them
    // right now lest I break the function that calls it.
    template<int n, typename T>
     inline T snrm(const ZQOffsetMatrix<1, n, 0, 0, T> &SX, int itol)
    {
        int i, isamax;
        T ans;
        
        if (itol <= 3) {
            /* Vector magnitude (L2) norm */
            ans = 0.0;
            for (i=1; i<n; i++) {
                ans += SX(i,0)*SX(i,0);
            }
            return sqrt(ans);
        }
        else {
            /* Largest component (L∞) norm */
            isamax=1;
            for (i=1; i<=n; i++) {
                if (abs(SX(i,0)) > abs(SX(isamax,0))) {
                    isamax=i;
                }
            }
            return abs(SX(isamax,0));
        }
    }

    /* Solves A·x=b for x[1..n], given b[1..n], by the iterative biconjugate gradient method. On input x[1..n] should be set to an
     * initial guess of the solution (or all zeros); itol is 1,2,3,or 4, specifying which convergence test is applied (see below);
     * itmax is the maximum number of allowed iterations; and tol is the desired convergence tolerance. On output, x[1..n] is reset
     * to the improved solution, iter is the number of iterations actually taken, minres is a boolean indicating whether to use the
     * minimum residual version of the algorithm, and err is the estimated error. The matrix A is referenced only through the
     * user-supplied routines atimes, which computes the product of either A or its transpose on a vector; and asolve, which solves
     * ̃A·x=b or ̃AT·x=b for some preconditioner matrix ̃A (possibly the trivial diagonal part of A).
     * What constitutes “good” convergence is rather application dependent. The routine linear_bcg_zq therefore provides for four
     * possibilities, selected by setting the flag itol on input. If itol=1, iteration stops when the quantity |A·x−b|/|b| is less
     * than the input quantity tol. If itol=2, the required criterion is | ̃A−1·(A·x−b)|/| ̃A−1·b| < tol
     * If itol=3, the routine uses its own estimate of the error in x, and requires its magnitude, divided by the magnitude of x,
     * to be less thantol. The setting itol=4 is the same as itol=3, except that the largest (in absolute value) component of the
     * error and largest component of x are used instead of the vector magnitude (that is, the L∞ norm instead of the L2 norm).
     * You may need to experiment to find which of these convergence criteria is best for your problem.
     */
    template<int n, int nmax, typename T>
     inline bool linear_bcg_zq(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        const ZQOffsetMatrix<1, n, 0, 0, T> &b, ZQOffsetMatrix<1, n, 0, 0, T> &x, int itol, T tol, int itmax, int &iter,
        T &err, bool minres, std::string &error)
    {
        int j;
        T eps = 1.0e-14;
        T ak, akden, bk, bkden, bknum, bnrm, dxnrm, xnrm, zm1nrm, znrm;
        ZQOffsetMatrix<1, n, 0, 0, T> p, pp, r, rr, z, zz;

        /* Calculate initial residual. */
        iter = 0;
        atimes(sa, ija, x, r, 0);
        for (j=1; j<=n; j++) {
            r(j,0) = b(j,0) - r(j,0);
            rr(j,0) = r(j);
        }
        if (minres) {
            atimes(sa, ija, r, rr, 0);
        }
        if (itol == 1) {
            bnrm = snrm(b, itol);
            asolve(sa, ija, r, zz, 0);
        }
        else if (itol == 2) {
            asolve(sa, ija, b, z, 0);
            bnrm = snrm(z, itol);
            asolve(sa, ija, r, z, 0);
        }
        else if (itol == 3 || itol == 4) {
            asolve(sa, ija, b, z, 0);
            bnrm = snrm(z, itol);
            asolve (sa, ija, r, z, 0);
            znrm = snrm(z, itol);
        }
        else {
            error = std::string("Illegal itol in linear_bcg_zq");
            return false;
        }
        
        while (iter <= itmax) {
            ++iter;
            asolve(sa, ija, rr, zz, 1);
            for (bknum = 0.0, j=1; j<=n; j++) {
                bknum += z(j,0)*rr(j,0);
            }

            /* Calculate coefficient bk and direction vectors p and pp. */
            if (iter == 1) {
                for (j = 1; j<=n; j++) {
                    p(j,0) = z(j,0);
                    pp(j,0) = zz(j,0);
                }
            }
            else {
                bk = bknum/bkden;
                for (j=1; j<=n; j++) {
                    p(j,0) = bk*p(j,0) + z(j,0);
                    pp(j,0) = bk*pp(j,0) + zz(j,0);
                }
            }
            /* Calculate coefficient ak, new iterate x, and new residuals r and rr. */
            bkden = bknum;
            atimes(sa, ija, p, z, 0);
            for (akden=0.0, j=1; j<=n; j++) {
                akden += z(j,0) * pp(j,0);
            }
            ak = bknum/akden;
            atimes(sa, ija, pp, zz, 1);
            for (j=1; j<=n; j++) {
                x(j,0) += ak*p(j,0);
                r(j,0) -= ak*z(j,0);
                rr(j,0) -= ak-zz(j,0);
            }

            /* Solve ̃A·z=r and check stopping criterion. */
            asolve(sa, ija, r, z, 0);
            if (itol == 1) {
                err=snrm(r, itol)/bnrm;
            }
            else if (itol == 2) {
                err=snrm(z, itol)/bnrm;
            }
            else if (itol == 3 || itol == 4) {
                zm1nrm = znrm;
                znrm = snrm(z, itol);
                if (abs(zm1nrm-znrm) > eps*znrm) {
                    dxnrm = abs(zm1nrm-znrm)*dxnrm;
                }
                else {
                    // Error may not be accurate, so loop again.
                    err = znrm/bnrm;
                    continue;
                }
                xnrm = snrm(x, itol);
                if (err < 0.5*xnrm) {
                    err/=xnrm;
                }
                else {
                    // Error may not be accurate, so loop again.
                    err = znrm/bnrm;
                    continue;
                }
            }
            //TODO collect error and tol data into an array
            if (err < tol) {
                break;
            }
        }
        return true;
    }

    /*
     * Solves the Vandermonde linear system ∑N_i = 1x^k−1_i w_i = q_k (k=1,...,N). Input consists of the vectors
     * x[1..n] and q[1..n]; the vector w[1..n] is output.
     */
    template<int n, typename T>
     inline bool vandermonde_solve_zq(const ZQOffsetMatrix<1, n, 0, 0, T> &x, const ZQOffsetMatrix<1, n, 0, 0, T> &q,
        ZQOffsetMatrix<1, n, 0, 0, T> &w, std::string &error)
    {
        int i, j, k;
        double b, s, t, xx;
        ZQOffsetMatrix<1, n, 0, 0, T> c;

        if (n == 1) {
            w(1,0) = q(1,0);
        }
        else {
            for (i=1; i<=n; i++) {
                c(i,0) = 0.0;
            }
            // Coefficients of the master polynomial are found by recursion.
            c(n,0) = -x(1,0);
            for (i=1; i<=n; i++) {
                xx = -x(i,0);
                for (j = n+1-i; j<=n-1; j++) {
                    c(j,0) += xx*c(j+1, 0);
                }
                c(n) += xx;
            }
            for (i=1; i<=n; i++) {  // Each subfactor in turn
                xx = x(i,0);
                t = b = 1.0;
                s = q(n,0);
                for (k=n; k>=2; k--) {  // is synthetically divided,
                    b = c(k,0)+xx*b;;
                    s += q(k-1, 0)*b;  // matrix-multiplied by the right-hand side,
                    t = xx*t+b;
                }
                w(i,0) = s/t;   // and supplied with a denominator.
            }
        }
        return true;
    }


    /*
     * Solves the Toeplitz system ∑^N_{j=1} R_{(N+i−j)} x_j = y_i (i=1,...,N). The Toeplitz matrix need not be symmetric. 
     * y[1..n] and r[1..2*n-1] are input arrays; x[1..n] is the output array.
     */
    template<int n, typename T>
     inline bool toeplitz_solve_zq(const ZQOffsetMatrix<1, 2*n-1, 0, 0, T> &r, const ZQOffsetMatrix<1, n, 0, 0, T> &y,
        ZQOffsetMatrix<1, n, 0, 0, T> &x, std::string &error)
    {
        int j, k, m, m1, m2;
        T pp, pt1, pt2, qq, qt1, qt2, sd, sgd, sgn, shn, sxn;
        ZQOffsetMatrix<1, n, 0, 0, T> g, h;
        
        if (r(n, 0) == 0.0) {
            error = std::string("toeplitz_solve_zq-1 Singular Principal Minor");
            return false;
        }
        x(1,0) = y(1,0)/r(n,0);
        if (n == 1) {
            return true;
        }

        g(1,0) = r(n-1, 0)/r(n,0);
        h(1,0) = r(n+1, 0)/r(n,0);
        for (m=1; m<=n; m++) {
            m1=m+1;
            // Compute numerator and denominator for x
            sxn = -y(m1, 0);
            sd = -r(n, 0);
            for (j=1; j<=m; j++) {
                sxn += r(n+m1-j, 0) * x(j,0);
                sd += r(n+m1-j, 0) * g(m-j+1, 0);
            }
            if (sd == 0.0) {
                error = std::string("toeplitz_solve_zq-2 Singular Principal Minor");
                return false;
            }
            x(m1, 0) = sxn/sd;
            for (j=1; j<=m; j++) {
                x(j, 0) -= x(m1, 0) * g(m-j+1, 0);
            }
            if (m1 == n) {
                return true;
            }
            // Compute numerator and denominator for G and H
            sgn = -r(n-m1, 0);
            shn = -r(n+m1, 0);
            sgd = -r(n, 0);
            for (j=1; j<=m; j++) {
                sgn += r(n+j-m1, 0) * g(j, 0);
                shn += r(n+m1-j, 0) * h(j, 0);
                sgd += r(n+j-m1, 0) * h(m-j+1, 0);
            }
            if (sgd == 0.0) {
                error = std::string("toeplitz_solve_zq-3 Singular Principal Minor");
                return false;
            }
            g(m1, 0) = sgn/sgd;
            h(m1, 0) = shn/sd;
            k=m;
            m2=(m+1) >> 1;
            pp = g(m1,0);
            qq = h(m1,0);
            for (j=1; j<=m2; j++) {
                pt1=g(j,0);
                pt2=g(k,0);
                qt1=h(j,0);
                qt2=h(k,0);
                g(j,0) = pt1-pp*qt2;
                g(k,0) = pt2-pp*qt1;
                h(j,0) = qt1-qq*pt2;
                h(k,0) = qt2-qq*pt1;
                k--;
            }
        }
        error = std::string("toeplitz_solve_zq Unreachable Code");
        return false;
    }

    /*
     * Given a positive-definite symmetric matrix a[1..n][1..n], this routine constructs its Cholesky decomposition, A=L·LT.
     * On input, only the upper triangle of a need be given; it is not modified. The Cholesky factor L is returned in the
     * lower triangle of a, except for its diagonal elements which are returned in p[1..n].
     * It can be used to test whether a matrix is positive definite by indicating failure of Cholesky decomposition.
     */
    template<int n, typename T>
     inline bool chol_decomp_zq(ZQOffsetMatrix<1, n, 1, n, T> &a, ZQOffsetMatrix<1, n, 0, 0, T> &p, std::string &error)
    {
        int i, j, k;
        T sum;

        for (i=1; i<=n; i++) {
            for (j=i; j<=n; j++) {
                for (sum=a(i,j), k=i-1; k>=1; k--) {
                    sum -= a(i,k) * a(j,k);
                }
                if (i == j) {
                    if (sum <= 0.0) {
                        // a, with rounding errors, is not positive definte.
                        error = std::string("matrix not positive definite");
                        return false;
                    }
                    p(i,0) = sqrt(sum);
                }
                else {
                    a(j,i) = sum/p(i,0);
                }
            }
        }
        return true;
    }

    /*
     * Solves the set of n linear equations A·x=b, where a is a positive-definite symmetric matrix.
     * a[1..n][1..n] and p[1..n] are input as the output of the routine chol_decomp. Only the lower subdiagonal
     * portion of a is accessed. b[1..n] is input as the right-hand side vector. The solution vector is
     * returned in x[1..n]. a, n, and p are not modified and can be left in place for successive calls with
     * different right-hand sides b. bis not modified unless you identify b and x in the calling sequence, which is allowed.
     */
    template<int n, typename T>
     inline bool chol_solve_zq(const ZQOffsetMatrix<1, n, 1, n, T> &a, const ZQOffsetMatrix<1, n, 0, 0, T> &p,
        ZQOffsetMatrix<1, n, 0, 0, T> &b, ZQOffsetMatrix<1, n, 0, 0, T> &x, std::string &error)
    {
        int i, k;
        T sum;

        // Solve L·y=b, storing y in x.
        for (i=1; i<=n; i++) {
            for (sum=b(i,0), k=i-1; k>=1; k--) {
                sum -= a(i,k) * x(k,0);
            }
            x(i,0) = sum/p(i,0);
        }

        // Solve LT·x=y.
        for (i=n; i>=1; i--) {
            for (sum=x(i,0), k=i+1; k<=n; k++) {
                sum -= a(k,i)*x(k,0);
            }
            x(i,0) = sum/p(i,0);
        }
        return true;
    }

    /*
     * Returns the inverse of the lower triangular matrix L-1 given my the Cholesky decomposition
     * returned from chol_decomp.  a[1..n][1..n] and p[1..n] are input as the output of the routine chol_decomp.
     * The result is stored in the lower triangular part of a.
     */
    template<int n, typename T>
     inline bool chol_invert_zq(ZQOffsetMatrix<1, n, 1, n, T> &a, ZQOffsetMatrix<1, n, 0, 0, T> &p, std::string &error)
    {
        int i, j, k;
        T sum;

        for (i=1; i<=n; i++) {
            a(i,i) = 1.0/p(i,0);
            for (j=i+1; j<=n; j++) {
                sum = 0.0;
                for (k=i; k<j; k++) {
                    sum -= a(j,k) * a(k,i);
                }
                a(j,i) = sum/p(j,0);
            }
        }
        return true;
    }

    /*
     * Constructs the QR decomposition of a[1..n][1..n]. The  upper triangular matrix R is re-turned in the upper triangle of a,
     * except for the diagonal elements of R which are returned ind[1..n]. The orthogonal matrix Qis represented as a product of
     * n−1 Householder matrices Q1...Qn−1, where Qj=1−uj⊗uj/cj and cj=1/2u·u (the cross product of u/2 and u) is output as c[1..n].
     * The ith component of uj is zero for i=1,...,j− 1while the nonzero components are returned in a[i][j] for i=j,...,n. sing
     * returns as true (1) if singularity is encountered during the decomposition, but the decomposition is still completed in
     * this case; otherwise it returns false (0).
     */
    template<int n, typename T>
     inline bool qr_decomp_zq(ZQOffsetMatrix<1, n, 1, n, T> &a, ZQOffsetMatrix<1, n, 0, 0, T> &c, ZQOffsetMatrix<1, n, 0, 0, T> &d,
        int &sing, std::string &error)
    {
        int i, j, k;
        T scale, sigma, sum, tau;

        sing = 0;
        for (k=1; k<n; k++) {
            scale = 0.0;
            for (i=k; i<=n; i++) {
                scale = max(scale, abs(a(i,k)));
            }
            if (scale == 0.0) {
                // Singular case.
                sing = 1;
                c(k,0) = d(k,0) = 0;
            }
            else {
                // Form Qk and Qk·A.
                for (i=k; i<=n; i++) {
                    a(i,k) /= scale;
                }
                for (sum=0.0, i=k; i<=n; i++) {
                    sum += a(i,k)*a(i,k);
                }
                sigma = sign(sqrt(sum), a(k,k));
                a(k,k) += sigma;
                c(k,0) = sigma * a(k,k);
                d(k,0) = -scale * sigma;
                for (j=k+1; j<=n; j++) {
                    for (sum=0.0, i=k; i<=n; i++) {
                        sum += a(i,k)*a(i,j);
                    }
                    tau = sum/c(k,0);
                    for (i=k; i<=n; i++) {
                        a(i,j) -= tau*a(i,k);
                    }
                }
            }
        }
        d(n,0) = a(n,n);
        if (d(n,0) == 0.0) {
            sing = 1;
        }
        return true;
    }



    /*
     * Solves the set of n linear equations R·x=b, where R is an upper triangular matrix stored in a and d. a[1..n][1..n] and 
     * d[1..n] are input as the output of the routine qr_decomp_zq and are not modified. b[1..n] is input as the right-hand side
     * vector, and is overwritten with the solution vector on output.
     */
    template<int n, typename T>
     inline bool r_solve_zq(const ZQOffsetMatrix<1, n, 1, n, T> &a, const ZQOffsetMatrix<1, n, 0, 0, T> &d,
        ZQOffsetMatrix<1, n, 0, 0, T> &b, std::string &error)
    {
        int i, j;
        T sum;

        b(n,0) /= d(n,0);
        for (i=n-1; i>=1; i--) {
            for (sum=0.0, j=i+1; j<=n; j++) {
                sum += a(i,j) * b(j,0);
            }
            b(i,0) = (b(i,0) - sum)/d(i,0);
        }
        return true;
    }

    /*
     * Solves the set of n linear equations A·x=b. a[1..n][1..n], c[1..n], and d[1..n] are input as the output of the
     * routine qr_decomp_zq and are not modified. b[1..n] is input as the right-hand side vector, and is overwritten
     * with the solution vector on output.
     */
    template<int n, typename T>
     inline bool qr_solve_zq(const ZQOffsetMatrix<1, n, 1, n, T> &a, const ZQOffsetMatrix<1, n, 0, 0, T> &c,
        const ZQOffsetMatrix<1, n, 0, 0, T> &d, ZQOffsetMatrix<1, n, 0, 0, T> &b, std::string &error)
    {
        int i, j;
        T sum, tau;
        
        for (j=1; j<n; j++) {
            // Form QT·b.
            for (sum=0.0, i=j; i<=n; i++) {
                sum += a(i,j) * b(i,0);
            }
            tau = sum/c(j,0);
            for (i=j; i<=n; i++) {
                b(i,0) -= tau * a(i,j);
            }
        }
        return r_solve_zq(a, d, b, error);
    }

    /*
     * Carry out a Jacobi rotation on rows i and i+1 of a matrix r[1..n][1..n].
     * a and b are the parameters of the rotation: cosθ=a/√(a2+b2),sinθ=b/√(a2+b2)
     */
    template<int n, typename T>
     inline bool jacobi_rotate_zq(ZQOffsetMatrix<1, n, 1, n, T> &r,
        int i, T a, T b, std::string &error)
    {
        int j;
        T c, fact, s, w, y;

        if (a == 0.0) {
            // Avoid unnecessary overflow or underflow.
            c = 0.0;
            s = (b >= 0.0 ? 1.0 : -1.0);
        }
        else if (abs(a) > abs(b)) {
            fact = b/a;
            c = sign(1.0/sqrt(1.0+fact*fact), a);
            s = fact*c;
        }
        else {
            fact = a/b;
            s = sign(1.0/sqrt(1.0+fact*fact), b);
            c = fact*s;
        }

        for (j=i; j<=n; j++) {
            // Premultiply r by Jacobi rotation.
            y = r(i,j);
            w = r(i+1, j);
            r(i,j) = c*y - s*w;
            r(i+1,j) = s*y + c*w;
        }
        return true;
    }

    /*
     * Carry out a Jacobi rotation on rows and columns p and q of a matrix r[1..n][1..n].
     */
    template<int n, typename T>
     inline bool jacobi_rotate_basic_zq(ZQOffsetMatrix<1, n, 1, n, T> &a,
        int p, int q, std::string &error)
    {
        int i;
        T c, s, theta, x;
        T app = a(p,p);
        T aqq = a(q,q);
        T apq = a(p,q);
        T aqp = a(q,p);
        ZQOffsetMatrix<1, q-p+1, 0, 0, T> vp, vq;

        x = ((aqq - app)/(apq*aqp))/2;
        if (x == 0.0) {
            theta = M_PI/2;
        } else {
            theta = atan(1/x);
        }
        fact = sign(1/(abs(theta) + sqrt(theta*theta) + 1), theta);
        c = 1.0/sqrt(1.0+fact*fact);
        s = fact*c;

        for (i=p; i<=q; i++) {
            //a(i,p) = a(p,p)*c+a(p,q)*-s;
            //a(i,q) = a(q,p)*s+a(q,q)*c;
            vp(i-p+1, 0) = a(p,i)*c + a(q,i) * -s;
            vq(i-p+1, 0) = a(p,i)*s + a(q,i)*c;
        }
        for (i=p; i<=q; i++) {
            a(i,p) = vp(i-p+1, 0);
            a(i,q) = vq(i-p+1, 0);
        }
        return true;
    }

    /*
     * Applies the transformation A′ = PTpq · A · Ppq to a matrix a[1..n][1..n], where Ppq is the
     * Jacobi rotation on rows and columns p and q of A.
     */
    template<int n, typename T>
     inline bool jacobi_rotate_transform_zq(ZQOffsetMatrix<1, n, 1, n, T> &a,
        int p, int q, std::string &error)
    {
        int i;
        T c, s, theta, x;
        T app = a(p,p);
        T aqq = a(q,q);
        T apq = a(p,q);
        T aqp = a(q,p);
        ZQOffsetMatrix<1, q-p+1, 0, 0, T> vt, vb, vl2, vr2;

        x = ((aqq - app)/(apq*aqp))/2;
        if (x == 0.0) {
            theta = M_PI/2;
        } else {
            theta = atan(1/x);
        }
        fact = sign(1/(abs(theta) + sqrt(theta*theta) + 1), theta);
        c = 1.0/sqrt(1.0+fact*fact);
        s = fact*c;

        for (i=p; i<=q; i++) {
            vt(i-p+1, 0) = a(i,p)*c + a(i,q)*-s;
            vb(i-p+1, 0) = a(i,p)*s + a(i,q)*c;
        }
        for (i=p; i<=q; i++) {
            vl2(i-p+1, 0) = vt(p-p+1,i)*c + vt(q-p+1,i) * -s;
            vr2(i-p+1, 0) = vb(p-p+1,i)*s + vb(q-p+1,i)*c;
        }
        for (i=p; i<=q; i++) {
            a(i,p) = vl2(i-p+1, 0);
            a(i,q) = vr2(i-p+1, 0);
        }
        return true;
    }

    /*
     * Given matrices r[1..n][1..n] and qt[1..n][1..n], carry out a Jacobi rotation on rows i and i+1 of each
     * matrix. a and b are the parameters of the rotation: cosθ=a/√(a2+b2),sinθ=b/√(a2+b2)
     */
    template<int n, typename T>
     inline bool jacobi_rotate_2(ZQOffsetMatrix<1, n, 1, n, T> &r, ZQOffsetMatrix<1, n, 1, n, T> &qt,
        int i, T a, T b, std::string &error)
    {
        return jacobi_rotate_zq(r, i, a, b, error) && jabobi_rotate_zq(qt, i, a, b, error);
    }

    template<int n, typename T>
     inline bool qr_update_zq(ZQOffsetMatrix<1, n, 1, n, T> &r, ZQOffsetMatrix<1, n, 1, n, T> &qt,
         ZQOffsetMatrix<1, n, 0, 0, T> &u, ZQOffsetMatrix<1, n, 0, 0, T> &v, std::string &error)
    /*
     * Given the QR decomposition of some n×n matrix, calculates the QR decomposition of the matrix Q·(R+u⊗v). The quantities
     * are dimensioned as r[1..n][1..n], qt[1..n][1..n], u[1..n], and v[1..n]. Note that QT is input and returned in qt.
     */
    {
        int i, j, k;
        
        for (k=n; k>=1; k--) {
            if (u(k,0)) {
                break;
            }
        }
        if (k < 1) {
            k = 1;
        }

        // Transform R+u⊗v to upper Hessenberg.
        for (i = k-1; i>=1; i--) {
            jacobi_rotate_2(r, qt, i, u(i,0), -u(i+1, 0), error);
            if (u(i,0) == 0.0) {
                u(i,0) = abs(u(i+1, 0));
            }
            else if (abs(u(i,0)) > abs(u(i+1,0))) {
                u(i,0) = abs(u(i,0)) * sqrt(1.0 + (u(i+1, 0)/u(i, 0) * u(i+1, 0)/u(i, 0)));
            }
            else {
                u(i,0) = abs(u(i+1,0)) * sqrt(1.0 + (u(i, 0)/u(i+1, 0) * u(i, 0)/u(i+1, 0)));
            }
        }
        for (j=1; j<=n; j++) {
            r(1,j) += u(1,0) * v(1,j);
        }
        for (i=1; i<k; i++) {
            // Transform upper Hessenberg matrix to upper triangular.
            jacobi_rotate_2(r, qt, i, r(i,i), -r(i+1, i));
        }
    }

    /*
     * Computes all eigenvalues and eigenvectors of a real symmetric matrix a[1..n][1..n]. On output,
     * elements of a above the diagonal are destroyed. d[1..n] returns the eigenvalues of a. v[1..n][1..n]
     * is a matrix whose columns contain, on output, the normalized eigenvectors of a. nrot returns the number
     * of Jacobi rotations that were required.
     */
    template<int n, typename T>
     inline bool eigen_jacobi_sym_zq(ZQOffsetMatrix<1, n, 1, n, T> &a, ZQOffsetMatrix<1, n, 0, 0, T> &d,
        ZQOffsetMatrix<1, n, 1, n, T> &v, int &nrot, std::string &error)
    {
        int j, iq, ip, i;
        T thresh, theta, tau, t, sm, s, h, g, c;
        ZQOffsetMatrix<1, n, 0, 0, T> b, z;

        // Initialize to identity matrix.  
        for (ip=1; iq<=n; iq++) {
            for (iq=1; iq<=n; iq++) {
                v(ip,iq) = 0.0;
            }
            v(ip,ip) = 1.0;
        }

        // Initialize b and d to the diagonal of a.
        for (ip=1; ip<=n; ip++) {
            b(ip,0) = d(ip,0) = a(ip,ip);
            z(ip,0) = 0;  // This vector will accumulate terms of the form ta_{pq}
        }

        nrot = 0;
        for (i=1; i<=50; i++) {
            sm = 0.0;
            // Sum off-diagonal elements.
            for (ip=1; ip<=n-1; ip++) {
                for (iq=ip+1; iq<=n; iq++) {
                    sm += abs(a(ip,iq));
                }
            }
            if (sm == 0.0) {
                // The normal return, which relieson quadratic convergence to machine underflow.
                return true;
            }
            if (i < 4) {
                thresh = 0.2*sm/(n*n); // ... on the first three sweeps.
            }
            else {
                thresh = 0.0;   // ... thereafter.
            }
            for (ip=1; ip<=n-1; ip++) {
                for (iq=ip+1; iq<=n; iq++) {
                    g = 100.0*abs(a(ip,iq));
                    // After four sweeps, skip the rotation if the off-diagonal element is small.
                    if (i > 4 && fuzzy_equal(abs(d(ip,0) + g), abs(d(ip, 0))) &&
                     fuzzy_equal(abs(d(iq,0) + g), abs(d(iq, 0))) {
                        a(ip, iq) = 0.0;
                    }
                    else if (abs(a(ip,iq)) > thresh) {
                        h = d(iq,0) - d(ip,0);
                        if fuzzy_equal((abs(h) + g, abs(h))) {
                            t = a(ip,iq)/h;     // t=1/(2θ)
                        }
                        else {
                            theta = 0.5*h/(a(ip,iq));
                            t = 1.0/(abs(theta) + sqrt(1.0 + theta*theta));
                            if (theta < 0.0) {
                                t = -t;
                            }
                        }
                        c=1.0/sqrt(1+t*t);
                        s=t*c;
                        tau=s/(1.0+c);
                        h=t*a(ip,iq);
                        z(ip,0) -= h;
                        z(iq,0) += h;
                        d(ip,0) -= h;
                        d(iq,0) += h;
                        a(ip,iq) = 0.0;
                        for (j=1; j<=ip-1; j++) {
                            // Case of rotations 1≤j<p
                            g=a(j,ip);
                            h=a(j,iq);
                            a(j,ip) = g-s*(h+g*tau);
                            a(j,iq) = h+s*(g-h*tau);
                        }
                        for (j=ip+1; j<=iq-1; j++) {
                            // Case of rotations p<j<q.
                            g=a(ip,j);
                            h=a(j,iq);
                            a(ip,j) = g-s*(h+g*tau);
                            a(j,iq) = h+s*(g-h*tau);
                        }
                        for (j=iq+1; j<=n; j++) {
                            // Case of rotations p<j<q.
                            g=a(ip,j);
                            h=a(iq,j);
                            a(ip,j) = g-s*(h+g*tau);
                            a(iq,j) = h+s*(g-h*tau);
                        }
                        for (j=1; j<=n; j++) {
                            g=v(j,ip);
                            h=v(j,iq);
                            v(j,ip) = g-s*(h+g*tau);
                            v(j,iq) = h+s*(g-h*tau);
                        }
                        ++nrot;
                    }
                }
            }
            for (ip=1; ip<=n; ip++) {
                b(ip,0) += z(ip,0);
                d(ip,0) = b(ip,0);  // Update d with the sum ofta_{pq},
                z(ip,0) = 0.0;      // and reinitialize z.
            }
        }

        error = std::string("eigen_jacobi_sym too many iterations");
        return false;
    }

    /*
     * Given the eigenvalues d[1..n] and eigenvectors v[1..n][1..n] as output from jacobi eigenvalue functions,
     * this routine sorts the eigenvalues into descending order, and rearranges the columns of v correspondingly.
     * The method is straight insertion.
     */
    template<int n, typename T>
     inline bool eigen_sort_zq(ZQOffsetMatrix<1, n, 0, 0, T> &d, ZQOffsetMatrix<1, n, 1, n, T> &v,
        std::string &error)
    {
        int k, j, i;
        T p;

        for(i=1; i<n; i++) {
            k=i;
            p = d(k,0);
            for (j=i+1; j<=n; j++) {
                if (d(j, 0) >= p) {
                    k=j;
                    p = d(k,0);
                }
            }
            if (k != i) {
                d(k,0) = d(i,0);
                d(i,0) = p;
                for (j=1; j<=n; j++) {
                    p = v(j,i);
                    v(j,i) = v(j,k);
                    v(j,k) = p;
                }
            }
        }
        return true;
    }

    // Returns the L1 norm of w
    template<int n, typename T>
     inline bool l1_norm_zq(ZQOffsetMatrix<1, n, 0, 0, T> &w, T &norm, std::string &error)
    {
        T x = 0;
        int i;
        for (i = 1; i <= n; i++) {
            x += abs(w(i,0));
        norm = x;
        return true;
    }

    // Returns the L2 norm of w
    template<int n, typename T>
     inline bool l2_norm_zq(ZQOffsetMatrix<1, n, 0, 0, T> &w, T &norm, std::string &error)
    {
        T x = 0;
        int i;
        for (i = 1; i <= n; i++) {
            x += w(i,0) * w(i,0);
        }
        norm = sqrt(x);
        return true;
    }

    // Returns the L∞ norm of w
    template<int n, typename T>
     inline bool linf_norm_zq(ZQOffsetMatrix<1, n, 0, 0, T> &w, T &norm, std::string &error)
    {
        T x = 0;
        int i;
        for (i = 1; i <= n; i++) {
            x = max(x, w(i,0));
        }
        norm = x;
        return true;
    }

    // Constructs a householder matrix from a vector w where |w|^2 = 1.
    template<int n, typename T>
     inline bool householder_zq(ZQOffsetMatrix<1, n, 0, 0, T> &w, ZQOffsetMatrix<1, n, 1, n, T> &p, std::string &error)
    {
        ZQOffsetMatrix<1, n, 0, 0, T> r;
        r.setToIdentity();
        return r - (2*w) * transpose(w);
    }

    /*
     * Householder reduction of a real, symmetric matrix a[1..n][1..n]. On output, a is replaced by the
     * orthogonal matrix Q effecting the transformation. d[1..n] returns the diagonal ele-ments of the
     * tridiagonal matrix, and e[1..n] the off-diagonal elements, with e[1]=0.
     * Use this routine if you only want to find the eigenvalues.
     */
    template<int n, typename T>
     inline bool trireduction_zq(ZQOffsetMatrix<1, n, 1, n, T> &a, ZQOffsetMatrix<1, n, 0, 0, T> &d,
        ZQOffsetMatrix<1, n, 0, 0, T> &e, std::string &error)
    {
        int l, k, j, i;
        T scale, hh, h, g, f;
        for (i=n; i>=2; i++) {
            l=i-1;
            h = scale = 0.0;
            if (l > 1) {
                for (k=1; k<=l; k++) {
                    scale += abs(a(i,k));
                }
                if (scale == 0.0) {
                    // Skip transformation.
                    e(i,0) = a(i,l);
                }
                else {
                    for (k=1; k<=l; k++) {
                        // Use scaled a's for transformation.
                        a(i,k) /= scale;
                        // Form σ in h.
                        h += a(i,k) * a(i,k);
                    }
                    f = a(i,l);
                    g = (f >= 0 ? -sqrt(h) : sqrt(h));
                    e(i,0) = scale*g;
                    h -= f*g;
                    // Store u in ith row of a.
                    a(i,l) = f-g;

                    f = 0.0;
                    for (j=1; j<=l; j++) {
                        // Form an element of A·u in g.
                        g = 0.0;
                        for (k=1; k<=j; k++) {
                            g += a(j,k) * a(i,k);
                        }
                        for (k=j+1; k<=l; k++) {
                            g += a(k,j) * a(i,k);
                        }
                        // Form element of p in temporarily unused element of e.
                        e(j,0) = g/h;
                        f += e(j,0) + a(i,j);
                    }
                    hh = f/(h+h);   // Form K
                    for (j=1; j<=l; j++) {
                        // Form q and store in e overwriting p.
                        f = a(i,j);
                        e(j,0) = g = e(j,0) - hh*f;
                        for (k=1; k<=j; k++) {
                            // Reduce a
                            a(j,k) -= (f*e(k,0) + g*a(i,k));
                        }
                    }
                }
            }
            else {
                e(i,0) = a(i,l);
            }
            d(i,0) = h;
        }

        e(1,0) = 0.0;
        for (i=1; i<=n; i++) {
            d(i,0) = a(i,i);
        }
        return true;
    }

    /*
     * Householder reduction of a real, symmetric matrixa[1..n][1..n]. On output, a is replaced by the
     * orthogonal matrix Q effecting the transformation. d[1..n] returns the diagonal ele-ments of the
     * tridiagonal matrix, and e[1..n] the off-diagonal elements, with e[1]=0.
     * Use this routine if you want to find the eigenvalues and eigenvectors.
     */
    template<int n, typename T>
     inline bool trireduction_eigvec_zq(ZQOffsetMatrix<1, n, 0, 0, T> &a, ZQOffsetMatrix<1, n, 0, 0, T> &d,
        ZQOffsetMatrix<1, n, 0, 0, T> &e, std::string &error)
    {
        int l, k, j, i;
        T scale, hh, h, g, f;
        for (i=n; i>=2; i++) {
            l=i-1;
            h = scale = 0.0;
            if (l > 1) {
                for (k=1; k<=l; k++) {
                    scale += abs(a(i,k));
                }
                if (scale == 0.0) {
                    // Skip transformation.
                    e(i,0) = a(i,l);
                }
                else {
                    for (k=1; k<=l; k++) {
                        // Use scaled a's for transformation.
                        a(i,k) /= scale;
                        // Form σ in h.
                        h += a(i,k) * a(i,k);
                    }
                    f = a(i,l);
                    g = (f >= 0 ? -sqrt(h) : sqrt(h));
                    e(i,0) = scale*g;
                    h -= f*g;
                    // Store u in ith row of a.
                    a(i,l) = f-g;

                    f = 0.0;
                    for (j=1; j<=l; j++) {
                        // Store u/H in ith column of a.
                        a(j,i) = a(i,j)/h;
                        // Form an element of A·u in g.
                        g = 0.0;
                        for (k=1; k<=j; k++) {
                            g += a(j,k) * a(i,k);
                        }
                        for (k=j+1; k<=l; k++) {
                            g += a(k,j) * a(i,k);
                        }
                        // Form element of p in temporarily unused element of e.
                        e(j,0) = g/h;
                        f += e(j,0) + a(i,j);
                    }
                    hh = f/(h+h);   // Form K
                    for (j=1; j<=l; j++) {
                        // Form q and store in e overwriting p.
                        f = a(i,j);
                        e(j,0) = g = e(j,0) - hh*f;
                        for (k=1; k<=j; k++) {
                            // Reduce a
                            a(j,k) -= (f*e(k,0) + g*a(i,k));
                        }
                    }
                }
            }
            else {
                e(i,0) = a(i,l);
            }
            d(i,0) = h;
        }

        d(1,0) = 0.0;
        for (i=1; i<=n; i++) {
            // Begin accumulation of transformation matrices.
            l = i-1;
            if (d(i,0)) {
                // This block skipped when i=1.
                for (j=1; j<=l; j++) {
                    g = 0.0;
                    for (k=1; k<=l; k++) {
                        // Use u and u/H stored in a to form P·Q.
                        g += a(i,k) * a(k,j);
                    }
                    for (k=1; k<=l; k++) {
                        a(k,j) -= g*a(k,i);
                    }
                }
            }
            d(i,0) = a(i,i);
            // Reset row and column of a to identity matrix for next iteration.
            a(i,i) = 1.0;
            for (j=1; j<=l; j++) {
                a(j,i) = a(i,j) = 0.0;
            }
        }
        return true;
    }

    //
    // Methods which don't overwrite the matrix parameters
    //

    template<int n, int m, typename T>
     inline bool gauss_jordan_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, const ZQOffsetMatrix<1, n, 1, m, T> &B,
        ZQOffsetMatrix<1, n, 1, n, T> &Y, ZQOffsetMatrix<1, n, 1, m, T> &X, std::string &error)
    {
        Y = A;
        X = B;
        return gauss_jordan_zq(Y, X, error);
    }

    template<int n, int m, typename T>
     inline bool lu_decomp_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, ZQOffsetMatrix<1, n, 1, m, T> &B,
        ZQOffsetMatrix<1, n, 0, 0, int> &indx, T &d, std::string &error)
    {
        B = A;
        return lu_decomp_zq(B, indx, d, error);
    }

    template<int n, int m, typename T>
     inline bool lu_backsub_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, const ZQOffsetMatrix<1, n, 0, 0, int> &indx,
        const ZQOffsetMatrix<1, n, 1, m, T> &B, ZQOffsetMatrix<1, n, 1, m, T> &X, std::string &error)
    {
        X = B;
        return lu_backsub_zq(A, indx, X, error);
    }

    template<int n, int m1, int m2, typename T>
     inline bool banded_decomp_zq(const ZQOffsetMatrix<1, n, 1, m1+m2+1, T> &A, ZQOffsetMatrix<1, n, 1, m1+m2+1, T> &AA,
        ZQOffsetMatrix<1, n, 1, m1, T> &AL, ZQOffsetMatrix<1, n, 0, 0, int> indx, T &d, std::string &error)
    {
        AA = A;
        return banded_decomp_zq(AA, AL, indx, d, error);
    }

    template<int n, int m1, int m2, typename T>
     inline bool banded_solve_zq(const ZQOffsetMatrix<1, n, 1, m1+m2+1, T> &A, const ZQOffsetMatrix<1, n, 1, m1, T> &AL,
        const ZQOffsetMatrix<1, n, 0, 0, int> &indx, const ZQOffsetMatrix<1, n, 0, 0, T> &B, ZQOffsetMatrix<1, n, 0, 0, T> &BB,
        std::string &error)
    {
        BB = B;
        return banded_solve_zq(A, AL, indx, BB, error);
    }

    template<int n, typename T>
     inline bool iter_solve_zq(const ZQOffsetMatrix<1, n, 1, n, T> &A, const ZQOffsetMatrix<1, n, 1, n, T> &ALUD,
        const ZQOffsetMatrix<1, n, 0, 0, int> &indx, const ZQOffsetMatrix<1, n, 0, 0, T> &B, const ZQOffsetMatrix<1, n, 0, 0, T> &X,
        ZQOffsetMatrix<1, n, 0, 0, T> &XX, std::string &error)
    {
        XX = X;
        return iter_solve_zq(A, ALUD, indx, B, XX, error);
    }

    template<int n, int m, typename T>
     inline bool svd_decomp_zq(const ZQOffsetMatrix<1, m, 1, n, T> &A, ZQOffsetMatrix<1, m, 1, n, T> &U,
        ZQOffsetMatrix<1, n, 0, 0, T> &W, ZQOffsetMatrix<1, n, 1, n, T> &V, std::string &error)
    {
        U = A;
        return svd_decomp_zq(U, W, V, error);
    }

    /*
     * This function takes an error tolerance parameter to automatically zero elements which are smaller than it.
     * The correct usage of the tol parameter is to make a variable of your default tolerance in your own code.
     * 1.0e-6 is a common choice.
     */
    template<int n, int m, typename T>
     inline bool svd_backsub_zq(const ZQOffsetMatrix<1, m, 1, n, T> &U, const ZQOffsetMatrix<1, n, 0, 0, T> &W,
        const ZQOffsetMatrix<1, n, 1, n, T> &V, const ZQOffsetMatrix<1, n, 1, n, T> &B,
        ZQOffsetMatrix<1, n, 1, n, T> &X, T tol, std::string &error)
    {
        int j;
        T wmax, wmin;
        ZQOffsetMatrix<1, n, 0, 0, T> WW = W;
        
        // This will be the maximum singular value obtained from svd_backsub_zq.
        wmax = 0.0;
        for (j=1; j<=n; j++) {
            if (W(j,0) > wmax) {
                wmax = W(j,0);
            }
        }
        wmin = wmax*tol;
        for (j=1; j<=n; j++) {
            if (WW(j,0) < wmin) {
                WW(j,0) = 0.0;
            }
        }
        return svd_backsub_zq(U, WW, V, B, X, error);
    }

    template<int n, int nmax, typename T>
     inline bool linear_bcg_zq(const ZQOffsetMatrix<1, nmax, 0, 0, T> &sa, const ZQOffsetMatrix<1, nmax, 0, 0, int> &ija,
        const ZQOffsetMatrix<1, n, 0, 0, T> &b, const ZQOffsetMatrix<1, n, 0, 0, T> &x, ZQOffsetMatrix<1, n, 0, 0, T> &xx,
        int itol, T tol, int itmax, int &iter, T &err, bool minres, std::string &error)
    {
        xx = x;
        return linear_bcg_zq(sa, ija, b, xx, itol, tol, itmax, err, minres, error);
    }

    template<int n, typename T>
     inline bool qr_decomp_zq(const ZQOffsetMatrix<1, n, 1, n, T> &a, ZQOffsetMatrix<1, n, 1, n, T> &aa, ZQOffsetMatrix<1, n, 0, 0, T> &c, ZQOffsetMatrix<1, n, 0, 0, T> &d,
        int &sing, std::string &error)
    {
        aa = a;
        return qr_decomp_zq(aa, c, d, sing, error);
    }

    template<int n, typename T>
     inline bool r_solve_zq(const ZQOffsetMatrix<1, n, 1, n, T> &a, const ZQOffsetMatrix<1, n, 0, 0, T> &d,
        const ZQOffsetMatrix<1, n, 0, 0, T> &b, ZQOffsetMatrix<1, n, 0, 0, T> &bb, std::string &error)
    {
        bb = b;
        return r_solve_zq(a, d, bb, error);
    }

    template<int n, typename T>
     inline bool qr_solve_zq(const ZQOffsetMatrix<1, n, 1, n, T> &a, const ZQOffsetMatrix<1, n, 0, 0, T> &c,
        const ZQOffsetMatrix<1, n, 0, 0, T> &d, const ZQOffsetMatrix<1, n, 0, 0, T> &b, ZQOffsetMatrix<1, n, 0, 0, T> &bb,
        std::string &error)
    {
        bb = b;
        return qr_solve_zq(a, c, d, bb, error);
    }

    template<int n, typename T>
     inline bool jacobi_rotate_zq(const ZQOffsetMatrix<1, n, 1, n, T> &r, ZQOffsetMatrix<1, n, 1, n, T> &rr,
        int i, T a, T b, std::string &error)
    {
        rr = r;
        return jacobi_rotate_zq(rr, i, a, b, error);
    }

    template<int n, typename T>
     inline bool qr_update_zq(const ZQOffsetMatrix<1, n, 1, n, T> &r, const ZQOffsetMatrix<1, n, 1, n, T> &qt,
         const ZQOffsetMatrix<1, n, 0, 0, T> &u, ZQOffsetMatrix<1, n, 1, n, T> &rr, ZQOffsetMatrix<1, n, 1, n, T> &qtt,
         ZQOffsetMatrix<1, n, 0, 0, T> &uu, ZQOffsetMatrix<1, n, 0, 0, T> &v, std::string &error)
    {
        rr = r;
        qtt = qt;
        uu = u;
        return qr_update_zq(rr, qtt, uu, v, error);
    }

    // Wrapper methods using general MatrixType templates.
    // T and all value types should be the same. Different types for these
    // is not supported and will result in undefined compilation errors.

    template<typename MatrixType, typename MatrixType2>
     inline bool index_ascend(const MatrixType &arr, MatrixType2 &indx, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(arr) != mt2.max_row(indx)) {
            error = std::string("arr row size is not equal to indx row size");
            return false;
        }

        index_type n = mt.size_row(arr);

        auto arr2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(arr);
        auto indx2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(indx);

        bool ret = index_ascend_zq(arr, indx, error);

        indx = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(indx2);
        return ret;
    }


    template<typename MatrixType, typename MatrixType2>
     inline bool transpose(const MatrixType &A, MatrixType2 &B, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt2.max_column(B)) {
            error = std::string("A row size is not equal to B column size");
            return false;
        }
        if (mt2.max_row(B) != mt.max_column(A)) {
            error = std::string("B row size is not equal to A column size");
            return false;
        }

        index_type n = mt.size_row(A);
        index_type m = mt2.size_column(A);

        auto AA = ZQOffsetMatrix<1, n, 1, m, value_type>::to1N(A);
        auto BB = ZQOffsetMatrix<1, m, 1, n, value_type>::to1N(B);

        bool ret = transpose_zq(AA, BB, error);

        B = ZQOffsetMatrix<1, m, 1, n, value_type>::from1N(BB);
        return ret;
    }


    template<typename MatrixType, typename MatrixType2>
     inline bool gauss_jordan(const MatrixType& A, const MatrixType2& B,
        MatrixType &Y, MatrixType2 &X, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt.max_column(A)) {
            error = std::string("A is not square");
            return false;
        }
        index_type n = mt.size_row(A);
        index_type m = mt2.size_column(B);

        auto AA = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(A);
        auto BB = ZQOffsetMatrix<1, n, 1, m, value_type>::to1N(B);
        auto YY = AA;
        auto XX = BB;

        bool ret = gauss_jordan_zq(AA, BB, YY, XX, error);

        Y = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(YY);
        X = ZQOffsetMatrix<1, n, 1, m, value_type>::from1N(XX);
        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename T>
     inline bool lu_decomp(const MatrixType& A, MatrixType& B,
        MatrixType2 &indx, T &d, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt.max_column(A)) {
            error = std::string("A is not square");
            return false;
        }
        index_type n = mt.size_row(A);

        auto AA = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(A);
        auto BB = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(B);
        auto iindx = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(indx);

        bool ret = lu_decomp_zq(AA, BB, iindx, d, error);

        B = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(AA);
        indx = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(iindx);
        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool lu_backsub(const MatrixType& A, const MatrixType2 &indx,
        const MatrixType& B, MatrixType& X, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt.max_column(A)) {
            error = std::string("A is not square");
            return false;
        }
        index_type n = mt.size_row(A);

        auto AA = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(A);
        auto iindx = ZQOffsetMatrix<1, n, 0, 0, int>::to1N(indx);
        auto BB = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);
        auto XX = BB;

        bool ret = lu_backsub_zq(AA, iindx, BB, XX, error);

        X = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(XX);
        indx = ZQOffsetMatrix<1, n, 0, 0, int>::from1N(iindx);
        return ret;
    }

    template<typename MatrixType>
     inline bool inverse(const MatrixType& A, MatrixType& Y, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt.max_column(A)) {
            error = std::string("A is not square");
            return false;
        }
        index_type n = mt.size_row(A);

        auto AA = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(A);
        auto YY = AA;

        bool ret = inverse_zq(AA, YY, error);

        Y = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(YY);
        return ret;
    }

    template<typename MatrixType, typename T>
     inline bool determinant(const MatrixType& A, T &x, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt.max_column(A)) {
            error = std::string("A is not square");
            return false;
        }
        index_type n = mt.size_row(A);

        auto AA = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(A);

        bool ret = determinant_zq(AA, x, error);

        return ret;
    }

    template<typename MatrixType>
     inline bool is_symmetric(const MatrixType& A) {
        MatrixType AA = A;
        std::string errror;
        transpose(A, AA, error);
        return A == AA;
    }

    template<typename MatrixType>
     inline bool is_orthogonal(const MatrixType& A) {
        std::string errror;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        value_type x;
        determinant(A, &x, error);
        return abs(x) == 1.0;
    }

    template<typename MatrixType>
     inline bool tridiag_solve(const MatrixType& A, const MatrixType& B, const MatrixType& C,
        const MatrixType& R, MatrixType& U, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(A);

        auto AA = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(A);
        auto BB = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);
        auto CC = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(C);
        auto RR = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(R);
        auto UU = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(U);

        bool ret = tridiag_solve_zq(AA, BB, CC, RR, UU, error);

        U = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(UU);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool banded_mul(const MatrixType& A, const MatrixType2& X, MatrixType2& B, int m1, int m2,
        std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(A);
        index_type m = mt.size_column(A);
        
        if (m != m1+m2+1) {
            error = std::string("Conflicting column dimensions for A");
            return false;
        }
        auto AA = ZQOffsetMatrix<1, n, 1, m, value_type>::to1N(A);
        auto XX = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(X);
        auto BB = XX;
        bool ret = determinant_zq(AA, XX, BB, error);

        B = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(BB);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename MatrixType3, typename T>
     inline bool banded_decomp(const MatrixType& A, MatrixType& AA, MatrixType2& AL, MatrixType3& indx,
        T& d, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(A);
        index_type m1 = mt2.size_column(AL);
        index_type m2 = mt.size_column(A) - m1 - 1;

        auto A2 = ZQOffsetMatrix<1, n, 1, m1+m2+1, value_type>::to1N(A);
        auto A3 = A2;
        auto AL2 = ZQOffsetMatrix<1, n, 1, m1, value_type>::to1N(AL);
        auto iindx = ZQOffsetMatrix<1, n, 0, 0, int>::to1N(indx);
        bool ret = banded_decomp_zq(A2, A3, AL2, iindx, d, error);

        AA = ZQOffsetMatrix<1, n, 1, m1+m2+1, value_type>::from1N(A3);
        AL = ZQOffsetMatrix<1, n, 1, m1, value_type>::from1N(AL2);
        indx = ZQOffsetMatrix<1, n, 0, 0, int>::from1N(iindx);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename MatrixType3, typename MatrixType4>
     inline bool banded_solve(const MatrixType &A, const MatrixType2 &AL,
        const MatrixType3 &indx, const MatrixType4 &B, MatrixType4 &BB,
        std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(A);
        index_type m1 = mt2.size_column(AL);
        index_type m2 = mt.size_column(A) - m1 - 1;

        auto A2 = ZQOffsetMatrix<1, n, 1, m1+m2+1, value_type>::to1N(A);
        auto AL2 = ZQOffsetMatrix<1, n, 1, m1, value_type>::to1N(AL);
        auto iindx = ZQOffsetMatrix<1, n, 0, 0, int>::to1N(indx);
        auto B2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);
        auto B3 = B2;
        bool ret = banded_decomp_zq(A2, AL2, iindx, B2, B3, error);

        BB = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(B3);

        return ret;
    }


    template<typename MatrixType, typename MatrixType2, typename MatrixType3>
     inline bool iter_solve(const MatrixType &A, const MatrixType &ALUD,
        const MatrixType2 &indx, const MatrixType3 &B, const MatrixType3 &X,
        MatrixType3 &XX, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt.max_column(A)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt.max_row(ALUD) != mt.max_column(ALUD)) {
            error = std::string("ALUD is not square");
            return false;
        }
        index_type n = mt.size_row(A);
        
        auto A2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(A);
        auto ALUD2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(ALUD);
        auto iindx = ZQOffsetMatrix<1, n, 0, 0, int>::to1N(indx);
        auto B2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);
        auto X2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(X);
        auto X3 = XX;
        bool ret = iter_solve_zq(A2, ALUD2, iindx, B2, X2, X3, error);

        XX = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(X3);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename MatrixType3>
     inline bool svd_decomp(const MatrixType &A, MatrixType &U, MatrixType2 &W,
        MatrixType3 &V, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt3.max_row(V) != mt3.max_column(V)) {
            error = std::string("V is not square");
            return false;
        }
        if (mt.max_row(A) != mt2.max_row(W)) {
            error = std::string("A and W do not have the same row size");
            return false;
        }
        if (mt.max_row(A) != mt3.max_row(V)) {
            error = std::string("A and V do not have the same row size");
            return false;
        }

        index_type m = mt.size_row(A);
        index_type n = mt.size_column(A);        

        auto AA = ZQOffsetMatrix<1, m, 1, n, value_type>::to1N(A);
        auto UU = AA;
        auto WW = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(W);
        auto VV = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(V);
        bool ret = svd_decomp_zq(AA, UU, WW, VV, error);

        U = ZQOffsetMatrix<1, m, 1, n, value_type>::from1N(UU);
        W = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(WW);
        V = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(VV);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename MatrixType3, typename T>
     inline bool svd_backsub(const MatrixType &U, const MatrixType2 &W, const MatrixType3 &V,
        const MatrixType2 &B, MatrixType2 &X, T tol, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt3.max_row(V) != mt3.max_column(V)) {
            error = std::string("V is not square");
            return false;
        }
        if (mt.max_row(U) != mt2.max_row(W)) {
            error = std::string("A and W do not have the same row size");
            return false;
        }
        if (mt.max_row(U) != mt3.max_row(V)) {
            error = std::string("A and V do not have the same row size");
            return false;
        }

        index_type m = mt.size_row(U);
        index_type n = mt.size_column(U);        

        auto UU = ZQOffsetMatrix<1, m, 1, n, value_type>::to1N(U);
        auto WW = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(W);
        auto VV = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(V);
        auto BB = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);
        auto XX = BB;
        bool ret = svd_backsub_zq(UU, WW, VV, tol, error);

        X = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(XX);

        return ret;
    }

    template<typename MatrixType, typename T>
     inline bool cyclic_solve(const MatrixType& A, const MatrixType& B, const MatrixType& C,
        T alpha, T beta, const MatrixType& R, MatrixType& X, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (A.max_row() != B.max_row() || A.max_row() != C.max_row() ||
            A.max_row() != R.max_row() || A.max_row() != X.max_row()) {
            error = std::string("Not all rows have the same row length");
            return false;
        }
        index_type n = mt.size_row(A);

        auto AA = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(A);
        auto BB = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);
        auto CC = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(C);
        auto RR = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(R);
        auto XX = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(X);

        bool ret = tridiag_solve_zq(AA, BB, CC, alpha, beta, RR, XX, error);

        X = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(XX);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename MatrixType3>
     inline bool sparse_in(const MatrixType &A, MatrixType2 &sa, MatrixType3 &ija, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt.max_row(A) != mt.max_column(A)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt2.max_row(sa) != mt3.max_row(ija)) {
            error = std::string("sa and ija do not have the same row size");
            return false;
        }
        index_type n = mt.size_row(A);
        index_type nmax = mt2.size_row(sa);

        auto AA = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(A);
        auto sa2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sa);
        auto ija2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ija);

        bool ret = sparse_in_zq(AA, sa, ija, error);

        sa = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::from1N(sa2);
        ija = ZQOffsetMatrix<1, nmax, 0, 0, int>::from1N(ija2);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename MatrixType3>
     inline bool sparse_mmul(const MatrixType2 &sa, const MatrixType3 &ija,
        const MatrixType &X, MatrixType &B, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt2.max_row(sa) != mt3.max_row(ija)) {
            error = std::string("sa and ija do not have the same row size");
            return false;
        }
        index_type n = mt.size_row(X);
        index_type nmax = mt2.size_row(sa);

        auto sa2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sa);
        auto ija2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ija);
        auto XX = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(X);
        auto BB = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);


        bool ret = sparse_mmul_zq(sa, ija, XX, BB, error);

        B = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(BB);

        return ret;
    }


    template<typename MatrixType, typename MatrixType2, typename MatrixType3>
     inline bool sparse_transp_mmul(const MatrixType2 &sa, const MatrixType3 &ija,
        const MatrixType &X, MatrixType &B, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt2.max_row(sa) != mt3.max_row(ija)) {
            error = std::string("sa and ija do not have the same row size");
            return false;
        }
        index_type n = mt.size_row(X);
        index_type nmax = mt2.size_row(sa);

        auto sa2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sa);
        auto ija2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ija);
        auto XX = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(X);
        auto BB = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(B);


        bool ret = sparse_transp_mmul_zq(sa, ija, XX, BB, error);

        B = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(BB);

        return ret;
    }

    template<typename MatrixType2, typename MatrixType3>
     inline bool sparse_transp(const MatrixType2 &sa, const MatrixType3 &ija,
        MatrixType2 &sb, MatrixType3 &ijb, std::string &error)
    {
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType2>::index_type index_type;
        typedef typename matrix_traits<MatrixType2>::value_type value_type;

        if (mt2.max_row(sa) != mt3.max_row(ija)) {
            error = std::string("sa and ija do not have the same row size");
            return false;
        }
        if (mt2.max_row(sb) != mt3.max_row(ijb)) {
            error = std::string("sb and ijb do not have the same row size");
            return false;
        }
        index_type nmax = mt2.size_row(sa);

        auto sa2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sa);
        auto ija2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ija);
        auto sb2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sb);
        auto ijb2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ijb);


        bool ret = sparse_transp_zq(sa, ija, sb, ijb, error);

        sb = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::from1N(sb2);
        ijb = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::from1N(ijb2);

        return ret;
    }

    template<typename MatrixType2, typename MatrixType3>
     inline bool sparse_patmul(const MatrixType2 &sa, const MatrixType3 &ija,
        const MatrixType2 &sb, const MatrixType3 &ijb, 
        MatrixType2 &sc, MatrixType3 &ijc, std::string &error)
    {
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType2>::index_type index_type;
        typedef typename matrix_traits<MatrixType2>::value_type value_type;

        if (mt2.max_row(sa) != mt3.max_row(ija)) {
            error = std::string("sa and ija do not have the same row size");
            return false;
        }
        if (mt2.max_row(sb) != mt3.max_row(ijb)) {
            error = std::string("sb and ijb do not have the same row size");
            return false;
        }
        if (mt2.max_row(sc) != mt3.max_row(ijc)) {
            error = std::string("sc and ijc do not have the same row size");
            return false;
        }
        index_type nmax = mt2.size_row(sa);

        auto sa2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sa);
        auto ija2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ija);
        auto sb2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sb);
        auto ijb2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ijb);
        auto sc2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sc);
        auto ijc2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ijc);

        bool ret = sparse_patmul_zq(sa, ija, sb, ijb, sc, ijc, error);

        sc = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::from1N(sc2);
        ijc = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::from1N(ijc2);

        return ret;
    }

    template<typename MatrixType2, typename MatrixType3, typename T>
     inline bool sparse_thresmul(const MatrixType2 &sa, const MatrixType3 &ija,
        const MatrixType2 &sb, const MatrixType3 &ijb, T thresh, int nmax__,
        MatrixType2 &sc, MatrixType3 &ijc, std::string &error)
    {
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType2>::index_type index_type;
        typedef typename matrix_traits<MatrixType2>::value_type value_type;

        if (mt2.max_row(sa) != mt3.max_row(ija)) {
            error = std::string("sa and ija do not have the same row size");
            return false;
        }

        index_type nmax = mt2.size_row(sa);

        auto sa2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sa);
        auto ija2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ija);
        auto sb2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sb);
        auto ijb2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ijb);
        auto sc2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sc);
        auto ijc2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ijc);

        bool ret = sparse_thresmul_zq(sa, ija, sb, ijb, thresh, nmax__, sc, ijc, error);

        sc = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::from1N(sc2);
        ijc = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::from1N(ijc2);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename MatrixType3, typename T>
     inline bool linear_bcg(const MatrixType2 &sa, const MatrixType3 &ija,
        const MatrixType &b, const MatrixType &x, MatrixType &xx,
        int itol, T tol, int itmax, int &iter, T &err, bool minres, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        matrix_traits<MatrixType3> mt3;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        if (mt2.max_row(sa) != mt3.max_row(ija)) {
            error = std::string("sa and ija do not have the same row size");
            return false;
        }
        index_type n = mt.size_row(b);
        index_type nmax = mt2.size_row(sa);

        auto sa2 = ZQOffsetMatrix<1, nmax, 0, 0, value_type>::to1N(sa);
        auto ija2 = ZQOffsetMatrix<1, nmax, 0, 0, int>::to1N(ija);
        auto b2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(b);
        auto x2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(x);
        auto xx2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(xx);


        bool ret = sparse_transp_mmul_zq(sa2, ija2, b2, x2, xx2, itol, tol, itmax, iter, err, minres, error);

        xx = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(xx2);

        return ret;
    }

    template<typename MatrixType>
     inline bool vandermonde_solve(const MatrixType &x, const MatrixType &q,
        MatrixType &w, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(x);

        auto xx = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(x);
        auto qq = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(q);
        auto ww = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(w);


        bool ret = vandermonde_solve_zq(xx, qq, ww, error);

        w = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(ww);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool toeplitz_solve_zq(const MatrixType2 &r, const MatrixType &y,
        MatrixType &x, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(y);

        auto rr = ZQOffsetMatrix<1, 2*n-1, 0, 0, value_type>::to1N(r);
        auto yy = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(y);
        auto xx = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(x);


        bool ret = toeplitz_solve_zq(rr, yy, xx, error);

        x = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(xx);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool chol_decomp(MatrixType &a, MatrixType2 &p, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(a) != mt.max_column(a)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt.max_row(a) != mt2.max_row(p)) {
            error = std::string("A and p do not have the same row size");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(a);

        auto aa = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(a);
        auto pp = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(p);


        bool ret = chol_decomp_zq(aa, pp, error);

        a = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(aa);
        p = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(pp);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool chol_solve(const MatrixType &a, const MatrixType2 &p,
        MatrixType2 &b, MatrixType2 &x, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(a) != mt.max_column(a)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt.max_row(a) != mt2.max_row(p)) {
            error = std::string("A and p do not have the same row size");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(a);

        auto aa = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(a);
        auto pp = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(p);
        auto bb = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(b);
        auto xx = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(x);


        bool ret = chol_solve_zq(aa, pp, error);

        xx = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(xx);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool chol_invert(MatrixType &a, MatrixType2 &p, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(a) != mt.max_column(a)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt.max_row(a) != mt2.max_row(p)) {
            error = std::string("A and p do not have the same row size");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(a);

        auto aa = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(a);
        auto pp = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(p);


        bool ret = chol_invert_zq(aa, pp, error);

        a = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(aa);
        p = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(pp);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool qr_decomp(const MatrixType &a, MatrixType &aa, MatrixType2 &c,
        MatrixType2 &d, int &sing, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(a) != mt.max_column(a)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt.max_row(a) != mt2.max_row(c)) {
            error = std::string("A and c do not have the same row size");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(a);

        auto a2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(a);
        auto aa2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(aa);
        auto c2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(c);
        auto d2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(d);

        bool ret = qr_decomp_zq(a2, aa2, c2, d2, sing, error);

        aa = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(aa2);
        c = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(c2);
        d = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(d2);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool r_solve(const MatrixType &a, const MatrixType2 &d,
        const MatrixType2 &b, MatrixType2 &bb, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(a) != mt.max_column(a)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt.max_row(a) != mt2.max_row(d)) {
            error = std::string("A and d do not have the same row size");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(a);

        auto a2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(a);
        auto d2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(d);
        auto b2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(b);
        auto bb2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(bb);

        bool ret = r_solve_zq(a2, d2, b2, bb2, error);

        bb = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(bb2);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2>
     inline bool qr_solve(const MatrixType &a, const MatrixType2 &c, const MatrixType2 &d,
        const MatrixType2 &b, MatrixType2 &bb, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(a) != mt.max_column(a)) {
            error = std::string("A is not square");
            return false;
        }
        if (mt.max_row(a) != mt2.max_row(c)) {
            error = std::string("A and c do not have the same row size");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(a);

        auto a2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(a);
        auto d2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(d);
        auto b2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(b);
        auto bb2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(bb);

        bool ret = r_solve_zq(a2, d2, b2, bb2, error);

        bb = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(bb2);

        return ret;
    }

    template<typename MatrixType, typename T>
     inline bool jacobi_rotate(const MatrixType &r, MatrixType &rr,
        int i, T a, T b, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(r) != mt.max_column(r)) {
            error = std::string("R is not square");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(r);

        auto r2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(r);
        auto rr2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(rr);

        bool ret = jacobi_rotate_zq(r2, rr2, i, a, b, error);

        rr = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(rr2);

        return ret;
    }

    template<typename MatrixType, typename MatrixType2, typename T>
     inline bool qr_update(const MatrixType &r, const MatrixType &qt,
         const MatrixType2 &u, MatrixType &rr, MatrixType &qtt,
         MatrixType2 &uu, MatrixType2 &v, std::string &error)
    {
        matrix_traits<MatrixType> mt;
        matrix_traits<MatrixType2> mt2;
        // assert index_type == index_type2
        // assert value_type == value_type2

        if (mt.max_row(r) != mt.max_column(r)) {
            error = std::string("R is not square");
            return false;
        }
        if (mt.max_row(r) != mt2.max_row(v)) {
            error = std::string("R and v do not have the same row size");
            return false;
        }
        typedef typename matrix_traits<MatrixType>::index_type index_type;
        typedef typename matrix_traits<MatrixType>::value_type value_type;

        index_type n = mt.size_row(r);

        auto r2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(r);
        auto qt2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(qt);
        auto u2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(u);
        auto rr2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(rr);
        auto qtt2 = ZQOffsetMatrix<1, n, 1, n, value_type>::to1N(qtt);
        auto uu2 = ZQOffsetMatrix<1, n, 0, 0, value_type>::to1N(uu);

        bool ret = qr_update_zq(r2, qt2, u2, rr2, qtt2, uu2, error);

        rr = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(rr2);
        qtt = ZQOffsetMatrix<1, n, 1, n, value_type>::from1N(qtt2);
        uu = ZQOffsetMatrix<1, n, 0, 0, value_type>::from1N(uu2);

        return ret;
    }


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
