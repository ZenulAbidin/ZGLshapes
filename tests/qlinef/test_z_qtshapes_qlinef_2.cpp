#define BOOST_TEST_MODULE Z_QTShapes_QLineF_2
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QLineF_2)
{
    z_qtshapes::ZQLineF h(0, 0, 0, 0, 10);
    h.setPoints(QPointF(1, 2), QPointF(3, 4), 30);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLineF(1, 2, 3, 4, 30);
    h.setPointsRadians(QPointF(5, 6), QPointF(7, 8), M_PI_2);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLineF(5, 6, 7, 8, 90);
    h.setCoords(1, 2, 3, 4);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLineF(1, 2, 3, 4, 90);
    h.setCoords(5, 6, 7, 8, 30);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLineF(5, 6, 7, 8, 30);
    h.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);
}
