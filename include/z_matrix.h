#ifndef Z_MATRIX_H
#define Z_MATRIX_H

#include <cassert>
#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "z_offsetmatrix.h"

namespace z_linalg {

    /*
     * Note: C++ doesn't know when it needs to upcast a primitive type in a template,
     * therefore you must always cast your scaling factors to T when using the operator* and operator/ functions.
     * In particular, a ZQMatrix<... qreal> can't be mutiplied or divided by an int and the int needs to be
     * casted into qreal first.
     */
    template <int M, int N, typename T>
     class ZQMatrix {
    public:

        inline ZQMatrix();
        inline ZQMatrix(const ZQMatrix<M, N, T>& other);
        explicit inline ZQMatrix(const T *values);

        static inline ZQOffsetMatrix<1, M, 1, N, T> to1Based(const ZQMatrix<M, N, T> &A);
        static inline ZQMatrix<M, N, T> from1Based(const ZQOffsetMatrix<1, M, 1, N, T> &A);

        inline const T& operator()(int row, int column) const;
        inline T& operator()(int row, int column);

        inline bool isIdentity() const;
        inline void setToIdentity();

        inline void fill(T value);

        inline int size_row() const { return M; }
        inline int size_column() const { return N; }

        inline ZQMatrix<M, N, T> transposed() const;

        inline ZQMatrix<M, N, T>& operator+=(const ZQMatrix<M, N, T>& other);
        inline ZQMatrix<M, N, T>& operator-=(const ZQMatrix<M, N, T>& other);
        inline ZQMatrix<M, N, T>& operator*=(T factor);
        inline ZQMatrix<M, N, T>& operator/=(T divisor);

        inline bool operator==(const ZQMatrix<M, N, T>& other) const;
        inline bool operator!=(const ZQMatrix<M, N, T>& other) const;

        inline void copyDataTo(T *values) const;

        inline T *data() { return *m; }
        inline const T *data() const { return *m; }
        inline const T *constData() const { return *m; }


        T m[N][M];    // Column-major order to match OpenGL.

        explicit inline ZQMatrix(int) {}       // Construct without initializing identity matrix.

        QString toString() const;

        template<int M_, int N_, typename T_>
         friend inline ZQMatrix<M_, N_, T_> operator+(const ZQMatrix<M_, N_, T_>& m1, const ZQMatrix<M_, N_, T_>& m2);
        template<int M_, int N_, typename T_>
         friend inline ZQMatrix<M_, N_, T_> operator-(const ZQMatrix<M_, N_, T_>& m1, const ZQMatrix<M_, N_, T_>& m2);
        template<int N_, int M1_, int M2_, typename T_>
         friend inline ZQMatrix<M2_, M1_, T_> operator*(const ZQMatrix<M2_, N_, T_>& m1, const ZQMatrix<N_, M1_, T_>& m2);
        template<int M_, int N_, typename T_>
         friend inline ZQMatrix<M_, N_, T_> operator-(const ZQMatrix<M_, N_, T_>& matrix);
        template<int M_, int N_, typename T_>
         friend inline ZQMatrix<M_, N_, T_> operator*(T_ factor, const ZQMatrix<M_, N_, T_>& matrix);
        template<int M_, int N_, typename T_>
         friend inline ZQMatrix<M_, N_, T_> operator*(const ZQMatrix<M_, N_, T_>& matrix, T_ factor);
        template<int M_, int N_, typename T_>
         friend inline ZQMatrix<M_, N_, T_> operator/(const ZQMatrix<M_, N_, T_>& matrix, T_ divisor);

    };

    template <int M, int N, typename T>
     QDebug operator<<(QDebug dbg, const ZQMatrix<M, N, T> &m);
    template <int M, int N, typename T>
     std::ostream operator<<(std::ostream dbg, const ZQMatrix<M, N, T> &m);
    template <int M, int N, typename T>
     QDataStream& operator<<(QDataStream &stream, const ZQMatrix<M, N, T> &matrix);
    template <int M, int N, typename T>
     QDataStream& operator>>(QDataStream &stream, ZQMatrix<M, N, T> &matrix);

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>::ZQMatrix()
    {
        setToIdentity();
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>::ZQMatrix(const ZQMatrix<M, N, T>& other)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                m[col][row] = other.m[col][row];
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>::ZQMatrix(const T *values)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                m[col][row] = values[row * (N) + col];
    }

    template <int M, int N, typename T>
     inline ZQOffsetMatrix<1, M, 1, N, T> ZQMatrix<M, N, T>::to1Based(const ZQMatrix<M, N, T> &A)
    {
        ZQOffsetMatrix<1, M, 1, N, T> B;
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                B.m[col][row] = A(row, col);
        return B;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T> ZQMatrix<M, N, T>::from1Based(const ZQOffsetMatrix<1, M, 1, N, T> &A)
    {
        ZQMatrix<M, N, T> B;
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                B.m[col][row] = A.m[col][row];
        return B;
    }

    template <int M, int N, typename T>
    inline const T& ZQMatrix<M, N, T>::operator()(int row, int column) const
    {
        assert(row >= 0 && row <= M && column >= 0 && column <= N);
        return m[column][row];
    }

    template <int M, int N, typename T>
    inline T& ZQMatrix<M, N, T>::operator()(int row, int column)
    {
        assert(row >= 0 && row <= M && column >= 0 && column <= N);
        return m[column][row];
    }

    template <int M, int N, typename T>
     inline bool ZQMatrix<M, N, T>::isIdentity() const
    {
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                if (row == col) {
                    if (m[col][row] != 1.0f)
                        return false;
                } else {
                    if (m[col][row] != 0.0f)
                        return false;
                }
            }
        }
        return true;
    }

    template <int M, int N, typename T>
     inline void ZQMatrix<M, N, T>::setToIdentity()
    {
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                if (row == col)
                    m[col][row] = 1.0f;
                else
                    m[col][row] = 0.0f;
            }
        }
    }

    template <int M, int N, typename T>
     inline void ZQMatrix<M, N, T>::fill(T value)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                m[col][row] = value;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T> ZQMatrix<M, N, T>::transposed() const
    {
        ZQMatrix<M, N, T> result(1);
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                result.m[row][col] = m[col][row];
        return result;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T> operator+(const ZQMatrix<M, N, T>& m1, const ZQMatrix<M, N, T>& m2)
    {
        ZQMatrix<M, N, T> result(1);
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                result.m[col][row] = m1.m[col][row] + m2.m[col][row];
        return result;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T> operator-(const ZQMatrix<M, N, T>& m1, const ZQMatrix<M, N, T>& m2)
    {
        ZQMatrix<M, N, T> result(1);
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                result.m[col][row] = m1.m[col][row] - m2.m[col][row];
        return result;
    }

    // Just your friendly reminder that the order of templates specified below does NOT reflect on the order used in variable names.  
    template <int N, int M1, int M2, typename T>
     inline ZQMatrix<M2, M1, T> operator*(const ZQMatrix<M2, N, T>& m1, const ZQMatrix<N, M1, T>& m2)
    {
        ZQMatrix<M2, M1, T> result(1);
        for (int row = 0; row < M2; ++row) {
            for (int col = 0; col < M1; ++col) {
                T sum(0.0f);
                for (int j = 0; j < N; ++j)
                    sum += m1.m[j][row] * m2.m[col][j];
                result.m[col][row] = sum;
            }
        }
        return result;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T> operator-(const ZQMatrix<M, N, T>& matrix)
    {
        ZQMatrix<M, N, T> result(1);
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                result.m[col][row] = -matrix.m[col][row];
        return result;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T> operator*(T factor, const ZQMatrix<M, N, T>& matrix)
    {
        ZQMatrix<M, N, T> result(1);
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                result.m[col][row] = matrix.m[col][row] * factor;
        return result;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T> operator*(const ZQMatrix<M, N, T>& matrix, T factor)
    {
        ZQMatrix<M, N, T> result(1);
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                result.m[col][row] = matrix.m[col][row] * factor;
        return result;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>operator/(const ZQMatrix<M, N, T>& matrix, T divisor)
    {
        ZQMatrix<M, N, T> result(1);
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                result.m[col][row] = matrix.m[col][row] / divisor;
        return result;
    }
    

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>& ZQMatrix<M, N, T>::operator+=(const ZQMatrix<M, N, T>& other)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                m[col][row] += other.m[col][row];
        return *this;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>& ZQMatrix<M, N, T>::operator-=(const ZQMatrix<M, N, T>& other)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                m[col][row] -= other.m[col][row];
        return *this;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>& ZQMatrix<M, N, T>::operator*=(T factor)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                m[col][row] *= factor;
        return *this;
    }

    template <int M, int N, typename T>
     inline ZQMatrix<M, N, T>& ZQMatrix<M, N, T>::operator/=(T divisor)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                m[col][row] /= divisor;
        return *this;
    }


    template <int M, int N, typename T>
     inline void ZQMatrix<M, N, T>::copyDataTo(T *values) const
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                values[row * (N) + col] = T(m[col][row]);
    }


    template <int M, int N, typename T>
     inline bool ZQMatrix<M, N, T>::operator==(const ZQMatrix<M, N, T>& other) const
    {
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                if (m[col][row] != other.m[col][row])
                    return false;
            }
        }
        return true;
    }

    template <int M, int N, typename T>
     inline bool ZQMatrix<M, N, T>::operator!=(const ZQMatrix<M, N, T>& other) const
    {
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                if (m[col][row] != other.m[col][row])
                    return true;
            }
        }
        return false;
    }

    template<int M, int N, typename TT>
     QString ZQMatrix<M, N, TT>::toString() const
    {
        std::ostringstream o;
        ZQMatrix<M, N, TT> a = *this;
        o << "ZQMatrix<" << N << ", " << M
            << ", " << QTypeInfo<TT>::name()
            << ">(" << std::endl << std::setw(10);
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                o << a.m[col][row];
                if (col != N)
                    o << std::setw(10);
            }
            o << std::endl;
            if (row != M)
                o << std::setw(10);
        }
        o << std::setw(0) << ")";
        return QString(o.str().c_str());
        
    }

    template<int M, int N, typename TT>
    QDebug operator<<(QDebug dbg, const ZQMatrix<M, N, TT> &m)
    {
        dbg << m.toString();
        return dbg;
    }


    template <int M, int N, typename T>
     std::ostream operator<<(std::ostream dbg, const ZQMatrix<M, N, T> &m)
    {
        dbg << m.toString();
        return dbg;
    }

    template<int M, int N, typename TT>
    QDataStream& operator<<(QDataStream &stream, const ZQMatrix<M, N, TT> &matrix)
    {
        for (int row = 0; row < M; ++row)
            for (int col = 0; col < N; ++col)
                stream << double(matrix(row, col));
        return stream;
    }

    template<int M, int N, typename TT>
    QDataStream& operator>>(QDataStream &stream, ZQMatrix<M, N, TT> &matrix)
    {
        double x;
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                stream >> x;
                matrix(row, col) = TT(x);
            }
        }
        return stream;
    }

}

#endif
