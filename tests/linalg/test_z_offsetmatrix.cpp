#define BOOST_TEST_MODULE Z_QTShapes_OffsetMatrix
#include <boost/test/included/unit_test.hpp>
#include <array>
#include <initializer_list>
#include <vector>
#include <iostream>

#include "z_linalg.h"

using namespace z_linalg;

BOOST_AUTO_TEST_CASE(Z_OffsetMatrix)
{
    ZQOffsetMatrix<11, 14, 5, 8, qreal> A(&std::array<qreal, 16>({
        7,	12,	1,	14,
        2,	13,	8,	11,
        16,	3,	10,	5,
        9, 	6,	15,	4})[0]);
    ZQOffsetMatrix<12, 13, 6, 7, qreal> Asub(&std::array<qreal, 4>({
        13,	8,
        3,	10})[0]);
   ZQOffsetMatrix<11, 14, 5, 8, qreal> AA(&std::array<qreal, 16>({
        7,	12,	1,	14,
        2,	13,	8,	11,
        16,	3,	10,	5,
        9, 	6,	15,	4})[0]);
    ZQOffsetMatrix<11, 14, 5, 8, qreal>B(&std::array<qreal, 16>({
        -7,	-12, -1, -14,
        -2,	-13, -8, -11,
        -16, -3, -10, -5,
        -9,  -6, -15, -4})[0]);
    ZQOffsetMatrix<11, 14, 5, 8, qreal> C(&std::array<qreal, 16>({
        -14, -24, -2,  -28,
        -4,	 -26, -16, -22,
        -32, -6,  -20, -10,
        -18, -12, -30, -8})[0]);
    ZQOffsetMatrix<11, 14, 5, 8, qreal> D(&std::array<qreal, 16>({
        3.5, 6,   0.5, 7,
        1,   6.5, 4,   5.5,
        8,   1.5, 5,   2.5,
        4.5, 3,   7.5, 2})[0]);
   ZQOffsetMatrix<11, 14, 5, 8, qreal> I(&std::array<qreal, 16>({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1})[0]);
    ZQOffsetMatrix<5, 8, 11, 14, qreal> II(&std::array<qreal, 16>({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1})[0]);

    ZQOffsetMatrix<11, 14, 5, 8, qreal>  U1(&std::array<qreal, 16>({
        0,	0, 0, 0,
        0,	0, 0, 0,
        0,  0, 0, 0,
        0,  0, 0, 0})[0]);

    ZQOffsetMatrix<11, 14, 5, 8, qreal>  U2(&std::array<qreal, 16>({
            1,	1, 1, 1,
            1,	1, 1, 1,
            1,  1, 1, 1,
            1,  1, 1, 1})[0]);

    ZQOffsetMatrix<11, 14, 11, 14, qreal> A3(&std::array<qreal, 16>({
        7,	12,	1,	14,
        2,	13,	8,	11,
        16,	3,	10,	5,
        9, 	6,	15,	4})[0]);

    ZQOffsetMatrix<5, 8, 5, 8, qreal> A4(&std::array<qreal, 16>({
        7,	12,	1,	14,
        2,	13,	8,	11,
        16,	3,	10,	5,
        9, 	6,	15,	4})[0]);

    BOOST_TEST(A(11,5) + A(11,6) + A(11,7) + A(11,8) == 34);
    BOOST_TEST(A(11,5) + A(12,5) + A(13,5) + A(14,5) == 34);
    if (-A == B) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (B + A == U1) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (A == AA) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (A != B) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (-A == B) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (B - A == C) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (B * qreal(2) == C) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (qreal(2) * B == C) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (A / qreal(2) == D) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (D * qreal(2) == A) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (I.isIdentity()) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (!A.isIdentity()) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (A*II == A3) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    if (II*A == A4) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    ZQOffsetMatrix<11, 14, 5, 8, qreal> DD = A;
    DD/=qreal(2);
    if (DD == D) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    DD*=qreal(2);
    if (DD == A) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    DD+=B;
    if (DD == U1) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    DD-=B;
    if (DD == A) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
    DD.fill(1);
    if (DD == U2) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    auto Atemp = submatrix<12,13,6,7>(A, 12,13,6,7);
    if (Atemp == Asub) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    // Beware, qreal maps to double on most systems. So QTypeInfo on qreal will return double.
    BOOST_TEST(A.toString() == QString("ZQOffsetMatrix<5-8, 11-14, double>(\n\
         7        12         1        14\n\
         2        13         8        11\n\
        16         3        10         5\n\
         9         6        15         4\n\
)"));
}
