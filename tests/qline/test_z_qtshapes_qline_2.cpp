#define BOOST_TEST_MODULE Z_QTShapes_QLine_2
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_QLine_2)
{
    z_qtshapes::ZQLine h(0, 0, 0, 0, 10);
    h.setPoints(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLine(1, 2, 3, 4, 30);
    h.setPointsRadians(QPoint(5, 6), QPoint(7, 8), M_PI_2);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLine(5, 6, 7, 8, 90);
    h.setCoords(1, 2, 3, 4);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLine(1, 2, 3, 4, 90);
    h.setCoords(5, 6, 7, 8, 30);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLine(5, 6, 7, 8, 30);
    h.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);
}
