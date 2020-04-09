#define BOOST_TEST_MODULE Z_QTShapes_QLine_6
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_QLine_6)
{
    z_qtshapes::ZQLine k(1, 2, 3, 4, 30);
    z_qtshapes::ZQLine l(1, 2, 3, 4, 20);

    z_qtshapes::ZQLine o = k;
    o.adjust(1, 1, 1, 1);
    BOOST_TEST(o.x1() == 2);
    BOOST_TEST(o.y1() == 3);
    BOOST_TEST(o.x2() == 4);
    BOOST_TEST(o.y2() == 5);

    o = z_qtshapes::ZQLine(2, 3, 4, 5, 30);
    o.adjust(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(o.x1() == 1);
    BOOST_TEST(o.y1() == 2);
    BOOST_TEST(o.x2() == 3);
    BOOST_TEST(o.y2() == 4);

    o = z_qtshapes::ZQLine(1, 2, 3, 4, 30);
    o.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(o.x1() == 2);
    BOOST_TEST(o.y1() == 3);
    BOOST_TEST(o.x2() == 4);
    BOOST_TEST(o.y2() == 5);
    BOOST_TEST(o.angle() == 32);

    o = z_qtshapes::ZQLine(2, 3, 4, 5, 32);
    o.adjust(QPoint(1, 1), QPoint(1, 1), 2);
    BOOST_TEST(o.x1() == 3);
    BOOST_TEST(o.y1() == 4);
    BOOST_TEST(o.x2() == 5);
    BOOST_TEST(o.y2() == 6);
    BOOST_TEST(o.angle() == 34);

    o = z_qtshapes::ZQLine(3, 4, 5, 6, 34);
    o.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(o.x1() == 4);
    BOOST_TEST(o.y1() == 5);
    BOOST_TEST(o.x2() == 6);
    BOOST_TEST(o.y2() == 7);
    BOOST_TEST(o.angle() == 124);

    o = z_qtshapes::ZQLine(4, 5, 6, 7, 124);
    o.adjustRadians(QPoint(1, 1), QPoint(1, 1), M_PI/2);
    BOOST_TEST(o.x1() == 5);
    BOOST_TEST(o.y1() == 6);
    BOOST_TEST(o.x2() == 7);
    BOOST_TEST(o.y2() == 8);
    BOOST_TEST(o.angle() == 214);
}
