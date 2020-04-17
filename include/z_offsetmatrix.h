#ifndef Z_OFFSETMATRIX_H
#define Z_OFFSETMATRIX_H

#include <cassert>
#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace z_linalg {

    /*
     * Note: C++ doesn't know when it needs to upcast a primitive type in a template,
     * therefore you must always cast your scaling factors to T when using the operator* and operator/ functions.
     * In particular, a ZQOffsetMatrix<... qreal> can't be mutiplied or divided by an int and the int needs to be
     * casted into qreal first.
     */
    template <int minM, int maxM, int minN, int maxN, typename T>
     class ZQOffsetMatrix {
    public:

        inline ZQOffsetMatrix();
        inline ZQOffsetMatrix(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other);
        explicit inline ZQOffsetMatrix(const T *values);

        static inline ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, T> to1Based(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &A);
        static inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> from1Based(const ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, T> &A);

        inline const T& operator()(int row, int column) const;
        inline T& operator()(int row, int column);
        inline void set(int row, int column, T value);

        inline bool isIdentity() const;
        inline void setToIdentity();

        inline void fill(T value);

        inline int min_row() const { return minM; }
        inline int max_row() const { return maxM; }
        inline int size_row() const { return maxM-minM+1; }
        inline int min_column() const { return minN; }
        inline int max_column() const { return maxN; }
        inline int size_column() const { return maxN-minN+1; }

        inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> transposed() const;

        inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& operator+=(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other);
        inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& operator-=(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other);
        inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& operator*=(T factor);
        inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& operator/=(T divisor);

        inline bool operator==(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other) const;
        inline bool operator!=(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other) const;

        inline void copyDataTo(T *values) const;

        inline T *data() { return *m; }
        inline const T *data() const { return *m; }
        inline const T *constData() const { return *m; }


        T m[maxN-minN+1][maxM-minM+1];    // Column-major order to match OpenGL.

        explicit inline ZQOffsetMatrix(int) {}       // Construct without initializing identity matrix.

        QString toString() const;

        template<int minM_, int maxM_, int minN_, int maxN_, typename T_>
         friend inline ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_> operator+(const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& m1, const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& m2);
        template<int minM_, int maxM_, int minN_, int maxN_, typename T_>
         friend inline ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_> operator-(const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& m1, const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& m2);
        template<int minN_, int maxN_, int minM1_, int maxM1_, int minM2_, int maxM2_, typename T_>
         friend inline ZQOffsetMatrix<minM2_, maxM2_, minM1_, maxM1_, T_> operator*(const ZQOffsetMatrix<minM2_, maxM2_, minN_, maxN_, T_>& m1, const ZQOffsetMatrix<minN_, maxN_, minM1_, maxM1_, T_>& m2);
        template<int minM_, int maxM_, int minN_, int maxN_, typename T_>
         friend inline ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_> operator-(const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& matrix);
        template<int minM_, int maxM_, int minN_, int maxN_, typename T_>
         friend inline ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_> operator*(T_ factor, const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& matrix);
        template<int minM_, int maxM_, int minN_, int maxN_, typename T_>
         friend inline ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_> operator*(const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& matrix, T_ factor);
        template<int minM_, int maxM_, int minN_, int maxN_, typename T_>
         friend inline ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_> operator/(const ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T_>& matrix, T_ divisor);

    };

    template <int minM, int maxM, int minN, int maxN, typename T>
     QDebug operator<<(QDebug dbg, const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &m);
    template <int minM, int maxM, int minN, int maxN, typename T>
     std::ostream operator<<(std::ostream dbg, const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &m);
    template <int minM, int maxM, int minN, int maxN, typename T>
     QDataStream& operator<<(QDataStream &stream, const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &matrix);
    template <int minM, int maxM, int minN, int maxN, typename T>
     QDataStream& operator>>(QDataStream &stream, ZQOffsetMatrix<minM, maxM, minN, maxN, T> &matrix);

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>::ZQOffsetMatrix()
    {
        setToIdentity();
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>::ZQOffsetMatrix(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                m[col][row] = other.m[col][row];
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>::ZQOffsetMatrix(const T *values)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                m[col][row] = values[row * (maxN-minN+1) + col];
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, T> ZQOffsetMatrix<minM, maxM, minN, maxN, T>::to1Based(const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &A)
    {
        ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, T> B;
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                B.m[col][row] = A(row+minM, col+minN);
        return B;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> ZQOffsetMatrix<minM, maxM, minN, maxN, T>::from1Based(const ZQOffsetMatrix<1, maxM-minM+1, 1, maxN-minN+1, T> &A)
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> B;
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                B.m[col][row] = A.m[col][row];
        return B;
    }


    template <int minM, int maxM, int minN, int maxN, typename T>
    inline const T& ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator()(int row, int column) const
    {
        assert(row >= minM /* "Row index is less than the allowed range" */);
        assert(row <= maxM /* "Row index is greater than the allowed range" */);
        assert(column >= minN /* "Column index is less than the allowed range" */);
        assert(column <= maxN /* "Column index is greater than the allowed range" */);
        return m[column-minN][row-minM];
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
    inline T& ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator()(int row, int column)
    {
        assert(row >= minM /* "Row index is less than the allowed range" */);
        assert(row <= maxM /* "Row index is greater than the allowed range" */);
        assert(column >= minN /* "Column index is less than the allowed range" */);
        assert(column <= maxN /* "Column index is greater than the allowed range" */);
        return m[column-minN][row-minM];
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
    inline void ZQOffsetMatrix<minM, maxM, minN, maxN, T>::set(int row, int column, T value)
    {
        assert(row >= minM /* "Row index is less than the allowed range" */);
        assert(row <= maxM /* "Row index is greater than the allowed range" */);
        assert(column >= minN /* "Column index is less than the allowed range" */);
        assert(column <= maxN /* "Column index is greater than the allowed range" */);
        m[column-minN][row-minM] = value;
    }


    template <int minM, int maxM, int minN, int maxN, typename T>
     inline bool ZQOffsetMatrix<minM, maxM, minN, maxN, T>::isIdentity() const
    {
        for (int row = 0; row <= maxM-minM; ++row) {
            for (int col = 0; col <= maxN-minN; ++col) {
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

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline void ZQOffsetMatrix<minM, maxM, minN, maxN, T>::setToIdentity()
    {
        for (int row = 0; row <= maxM-minM; ++row) {
            for (int col = 0; col <= maxN-minN; ++col) {
                if (row == col)
                    m[col][row] = 1.0f;
                else
                    m[col][row] = 0.0f;
            }
        }
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline void ZQOffsetMatrix<minM, maxM, minN, maxN, T>::fill(T value)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                m[col][row] = value;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> ZQOffsetMatrix<minM, maxM, minN, maxN, T>::transposed() const
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> result(1);
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                result.m[row][col] = m[col][row];
        return result;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> operator+(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& m1, const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& m2)
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> result(1);
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                result.m[col][row] = m1.m[col][row] + m2.m[col][row];
        return result;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> operator-(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& m1, const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& m2)
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> result(1);
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                result.m[col][row] = m1.m[col][row] - m2.m[col][row];
        return result;
    }

    template <int minN, int maxN, int minM1, int maxM1, int minM2, int maxM2, typename T>
     inline ZQOffsetMatrix<minM2, maxM2, minM1, maxM1, T> operator*(const ZQOffsetMatrix<minM2, maxM2, minN, maxN, T>& m1, const ZQOffsetMatrix<minN, maxN, minM1, maxM1, T>& m2)
    {
        ZQOffsetMatrix<minM2, maxM2, minM1, maxM1, T> result(1);
        for (int row = 0; row <= maxM2-minM2; ++row) {
            for (int col = 0; col <= maxM1-minM1; ++col) {
                T sum(0.0f);
                for (int j = 0; j <= maxN-minN; ++j)
                    sum += m1.m[j][row] * m2.m[col][j];
                result.m[col][row] = sum;
            }
        }
        return result;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> operator-(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& matrix)
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> result(1);
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                result.m[col][row] = -matrix.m[col][row];
        return result;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> operator*(T factor, const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& matrix)
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> result(1);
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                result.m[col][row] = matrix.m[col][row] * factor;
        return result;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T> operator*(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& matrix, T factor)
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> result(1);
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                result.m[col][row] = matrix.m[col][row] * factor;
        return result;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>operator/(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& matrix, T divisor)
    {
        ZQOffsetMatrix<minM, maxM, minN, maxN, T> result(1);
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                result.m[col][row] = matrix.m[col][row] / divisor;
        return result;
    }
    

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator+=(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                m[col][row] += other.m[col][row];
        return *this;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator-=(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                m[col][row] -= other.m[col][row];
        return *this;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator*=(T factor)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                m[col][row] *= factor;
        return *this;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline ZQOffsetMatrix<minM, maxM, minN, maxN, T>& ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator/=(T divisor)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                m[col][row] /= divisor;
        return *this;
    }


    template <int minM, int maxM, int minN, int maxN, typename T>
     inline void ZQOffsetMatrix<minM, maxM, minN, maxN, T>::copyDataTo(T *values) const
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                values[row * (maxN-minN+1) + col] = T(m[col][row]);
    }


    template <int minM, int maxM, int minN, int maxN, typename T>
     inline bool ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator==(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other) const
    {
        for (int row = 0; row <= maxM-minM; ++row) {
            for (int col = 0; col <= maxN-minN; ++col) {
                if (m[col][row] != other.m[col][row])
                    return false;
            }
        }
        return true;
    }

    template <int minM, int maxM, int minN, int maxN, typename T>
     inline bool ZQOffsetMatrix<minM, maxM, minN, maxN, T>::operator!=(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& other) const
    {
        for (int row = 0; row <= maxM-minM; ++row) {
            for (int col = 0; col <= maxN-minN; ++col) {
                if (m[col][row] != other.m[col][row])
                    return true;
            }
        }
        return false;
    }

    template<int minM, int maxM, int minN, int maxN, typename TT>
     QString ZQOffsetMatrix<minM, maxM, minN, maxN, TT>::toString() const
    {
        std::ostringstream o;
        ZQOffsetMatrix<minM, maxM, minN, maxN, TT> a = *this;
        o << "ZQOffsetMatrix<" << minN << "-" << maxN << ", " << minM << "-" << maxM
            << ", " << QTypeInfo<TT>::name()
            << ">(" << std::endl << std::setw(10);
        for (int row = 0; row <= maxM-minM; ++row) {
            for (int col = 0; col <= maxN-minN; ++col) {
                o << a.m[col][row];
                if (col != maxN-minN)
                    o << std::setw(10);
            }
            o << std::endl;
            if (row != maxM-minM)
                o << std::setw(10);
        }
        o << std::setw(0) << ")";
        return QString(o.str().c_str());
        
    }

    template<int minM, int maxM, int minN, int maxN, typename TT>
    QDebug operator<<(QDebug dbg, const ZQOffsetMatrix<minM, maxM, minN, maxN, TT> &m)
    {
        dbg << m.toString();
        return dbg;
    }


    template <int minM, int maxM, int minN, int maxN, typename T>
     std::ostream operator<<(std::ostream dbg, const ZQOffsetMatrix<minM, maxM, minN, maxN, T> &m)
    {
        dbg << m.toString();
        return dbg;
    }

    template<int minM, int maxM, int minN, int maxN, typename TT>
    QDataStream& operator<<(QDataStream &stream, const ZQOffsetMatrix<minM, maxM, minN, maxN, TT> &matrix)
    {
        for (int row = 0; row <= maxM-minM; ++row)
            for (int col = 0; col <= maxN-minN; ++col)
                stream << double(matrix(row, col));
        return stream;
    }

    template<int minM, int maxM, int minN, int maxN, typename TT>
    QDataStream& operator>>(QDataStream &stream, ZQOffsetMatrix<minM, maxM, minN, maxN, TT> &matrix)
    {
        double x;
        for (int row = 0; row <= maxM-minM; ++row) {
            for (int col = 0; col <= maxN-minN; ++col) {
                stream >> x;
                matrix(row, col) = TT(x);
            }
        }
        return stream;
    }

}

#endif
