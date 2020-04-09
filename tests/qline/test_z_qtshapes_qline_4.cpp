#define BOOST_TEST_MODULE Z_QTShapes_QLine_4
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_QLine_4)
{
    z_qtshapes::ZQLine k(1, 2, 3, 4, 30);
    z_qtshapes::ZQLine l(1, 2, 3, 4, 20);

    k.translate(1, 1);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);

    k = z_qtshapes::ZQLine(2, 3, 4, 5, 30);
    k.translate(QPoint(-1, -1));
    BOOST_TEST(k.x1() == 1);
    BOOST_TEST(k.y1() == 2);
    BOOST_TEST(k.x2() == 3);
    BOOST_TEST(k.y2() == 4);

    k = z_qtshapes::ZQLine(1, 2, 3, 4, 30);
    k.translate(1, 1, 2);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);
    BOOST_TEST(k.angle() == 32);

    k = z_qtshapes::ZQLine(2, 3, 4, 5, 32);
    k.translate(QPoint(1, 1), 2);
    BOOST_TEST(k.x1() == 3);
    BOOST_TEST(k.y1() == 4);
    BOOST_TEST(k.x2() == 5);
    BOOST_TEST(k.y2() == 6);
    BOOST_TEST(k.angle() == 34);

    k = z_qtshapes::ZQLine(3, 4, 5, 6, 34);
    k.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(k.x1() == 4);
    BOOST_TEST(k.y1() == 5);
    BOOST_TEST(k.x2() == 6);
    BOOST_TEST(k.y2() == 7);
    BOOST_TEST(k.angle() == 124);

    k = z_qtshapes::ZQLine(4, 5, 6, 7, 124);
    k.translateRadians(QPoint(1, 1), M_PI/2);
    BOOST_TEST(k.x1() == 5);
    BOOST_TEST(k.y1() == 6);
    BOOST_TEST(k.x2() == 7);
    BOOST_TEST(k.y2() == 8);
    BOOST_TEST(k.angle() == 214);
}
