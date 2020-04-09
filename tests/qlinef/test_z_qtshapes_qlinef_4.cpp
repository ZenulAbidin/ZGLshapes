#define BOOST_TEST_MODULE Z_QTShapes_QLineF_4
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QLineF_4)
{
    z_qtshapes::ZQLineF kk(1, 2, 3, 4, 30);
    z_qtshapes::ZQLineF k(1, 2, 3, 4, 30);
    z_qtshapes::ZQLineF l(1, 2, 3, 4, 20);
    if (kk == k) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (kk != l) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    k.translate(1, 1);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);

    k = z_qtshapes::ZQLineF(2, 3, 4, 5, 30);
    k.translate(QPointF(-1, -1));
    BOOST_TEST(k.x1() == 1);
    BOOST_TEST(k.y1() == 2);
    BOOST_TEST(k.x2() == 3);
    BOOST_TEST(k.y2() == 4);

    k = z_qtshapes::ZQLineF(1, 2, 3, 4, 30);
    k.translate(1, 1, 2);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);
    BOOST_TEST(k.angle() == 32);

    k = z_qtshapes::ZQLineF(2, 3, 4, 5, 32);
    k.translate(QPointF(1, 1), 2);
    BOOST_TEST(k.x1() == 3);
    BOOST_TEST(k.y1() == 4);
    BOOST_TEST(k.x2() == 5);
    BOOST_TEST(k.y2() == 6);
    BOOST_TEST(k.angle() == 34);

    k = z_qtshapes::ZQLineF(3, 4, 5, 6, 34);
    k.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(k.x1() == 4);
    BOOST_TEST(k.y1() == 5);
    BOOST_TEST(k.x2() == 6);
    BOOST_TEST(k.y2() == 7);
    BOOST_TEST(k.angle() == 124);

    k = z_qtshapes::ZQLineF(4, 5, 6, 7, 124);
    k.translateRadians(QPointF(1, 1), M_PI/2);
    BOOST_TEST(k.x1() == 5);
    BOOST_TEST(k.y1() == 6);
    BOOST_TEST(k.x2() == 7);
    BOOST_TEST(k.y2() == 8);
    BOOST_TEST(k.angle() == 214);
}
