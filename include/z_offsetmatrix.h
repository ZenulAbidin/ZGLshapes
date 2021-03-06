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

        constexpr inline const int min_row() const { return minM; }
        constexpr inline const int max_row() const { return maxM; }
        constexpr inline const int size_row() const { return maxM-minM+1; }
        constexpr inline const int min_column() const { return minN; }
        constexpr inline const int max_column() const { return maxN; }
        constexpr inline const int size_column() const { return maxN-minN+1; }

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

        template <int minM_, int maxM_, int minN_, int maxN_>
         friend inline ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T> submatrix(const ZQOffsetMatrix<minM, maxM, minN, maxN, T>& m1, int row1, int row2, int col1, int col2) {
            assert(row1 == minM_ /* "Starting row subindex is different from supplied starting row dimension" */);
            assert(row2 == maxM_ /* "Ending row subindex is different from supplied ending row dimension" */);
            assert(col1 == minN_ /* "Starting column subindex is different from supplied starting column dimension" */);
            assert(col2 == maxN_ /* "Ending column subindex is different from supplied ending column dimension" */);
            assert(minM_ >= minM /* "Row dimension is less than the allowed range" */);
            assert(maxM_ <= maxM /* "Row dimension is greater than the allowed range" */);
            assert(minN_ >= minN /* "Column dimension is less than the allowed range" */);
            assert(maxN_ <= maxN /* "Column dimension is greater than the allowed range" */);
            assert(row1 <= row2 /* "Starting row subindex is greater than the ending subindex" */);
            assert(col1 <= col2 /* "Starting column subindex is greater than the ending subindex" */);
            ZQOffsetMatrix<minM_, maxM_, minN_, maxN_, T> A;
            for (int row = row1; row <= row2; ++row)
                for (int col = col1; col <= col2; ++col)
                    A.m[col-col1][row-row1] = m1.m[col-minN][row-minM];
            return A;
        }

       template<maxM_, maxN_>
         friend inline ZQOffsetMatrix<minM, maxM_, minN, maxN_, T> concat(ZQOffsetMatrix<minM, maxM, minN, maxN, T> m1, ZQOffsetMatrix<minM, maxM_-maxM, minN, maxN_-maxN, T> m2,
            T fillval=0.0) {
            assert(M_ > M /* "concatenated row size is less than original row size" */);
            assert(N_ > N /* "concatenated column size is less than original column size" */);
            ZQOffsetMatrix<minM, maxM_, minN, maxN_, T> A;
            A.fill(fillval);
            for (int row = 0; row <= maxM-minM; ++row) {
                for (int col = 0; col <= maxN-minN; ++col)
                    A.m[col][row] = m1.m[col][row];
            }
            for (int row = 0; row <= maxM_-maxM; ++row) {
                for (int col = 0; col <= maxN_-maxN; ++col)
                    A.m[col+N][row+M] = m2.m[col][row];
            }
            return A;
        }


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
