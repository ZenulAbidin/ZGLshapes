#define BOOST_TEST_MODULE Z_QTShapes_MatrixTraits
#include <boost/test/included/unit_test.hpp>

#include <QGenericMatrix>
#include <array>
#include <initializer_list>
#include "z_matrixtraits.h"
#include "z_matrix.h"
#include "z_offsetmatrix.h"

using namespace z_linalg;

/*
display *values@12
display {row, col}
display values[row * (maxN-minN+1) + col]

display *values@12
display {row, col}
display values[col * (maxM-minM+1) + row]

*/

BOOST_AUTO_TEST_CASE(Z_MatrixTraits)
{
    qreal M[3][4] = { {  1, 2, -1,  -4 },
                     {  2, 3, -1, -11 },
                     { -2, 0, -3,  22 } };

    QGenericMatrix<4, 3, qreal> M2(&std::array<qreal, 12>({
        1, 2, -1, -4,
        2, 3, -1, -11,
        -2, 0, -3, 22})[0]);

    ZQMatrix<3, 4, qreal> M3(&std::array<qreal, 16>({
        1, 2, -1, -4,
        2, 3, -1, -11,
        -2, 0, -3, 22})[0]);


    ZQOffsetMatrix<11, 13, 5, 8, qreal> M4(&std::array<qreal, 16>({
        1, 2, -1, -4,
        2, 3, -1, -11,
        -2, 0, -3, 22})[0]);

    ZQOffsetMatrix<1, 3, 1, 4, qreal> XT(&std::array<qreal, 16>({
        1, 2, -1, -4,
        2, 3, -1, -11,
        -2, 0, -3, 22})[0]);


    matrix_traits<qreal[3][4]> mt;
    matrix_traits<QGenericMatrix<4, 3, qreal>> mt2;
    matrix_traits<ZQMatrix<3, 4, qreal>> mt3;
    matrix_traits<ZQOffsetMatrix<11, 13, 5, 8, qreal>> mt4;

    BOOST_TEST(mt.min_row(M) == 0);
    BOOST_TEST(mt.max_row(M) == 2);
    BOOST_TEST(mt.min_column(M) == 0);
    BOOST_TEST(mt.max_column(M) == 3);

    BOOST_TEST(mt2.min_row(M2) == 0);
    BOOST_TEST(mt2.max_row(M2) == 2);
    BOOST_TEST(mt2.min_column(M2) == 0);
    BOOST_TEST(mt2.max_column(M2) == 3);

    BOOST_TEST(mt3.min_row(M3) == 0);
    BOOST_TEST(mt3.max_row(M3) == 2);
    BOOST_TEST(mt3.min_column(M3) == 0);
    BOOST_TEST(mt3.max_column(M3) == 3);

    BOOST_TEST(mt4.min_row(M4) == 11);
    BOOST_TEST(mt4.max_row(M4) == 13);
    BOOST_TEST(mt4.min_column(M4) == 5);
    BOOST_TEST(mt4.max_column(M4) == 8);

    BOOST_TEST(mt.element(M, 0, 0) == 1);
    BOOST_TEST(mt2.element(M2, 0, 0) == 1);
    BOOST_TEST(mt3.element(M3, 0, 0) == 1);
    BOOST_TEST(mt4.element(M4, 11, 5) == 1);


    ZQOffsetMatrix<1, 3, 1, 4, qreal> RR3 = ZQMatrix<3, 4, qreal>::to1Based(M3);
    ZQOffsetMatrix<1, 3, 1, 4, qreal> RR4 = ZQOffsetMatrix<11, 13, 5, 8, qreal>::to1Based(M4);
    
    if (RR3 == XT) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (RR4 == XT) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    ZQMatrix<3, 4, qreal> S3 = ZQMatrix<3, 4, qreal>::from1Based(RR3);
    ZQOffsetMatrix<11, 13, 5, 8, qreal> S4 = ZQOffsetMatrix<11, 13, 5, 8, qreal>::from1Based(RR4);

    if (S3 == M3) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (S4 == M4) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    
    // Allows us to stay in the function debugging the other values.
    auto foo = 2;
}
