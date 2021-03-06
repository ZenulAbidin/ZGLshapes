#define BOOST_TEST_MODULE Z_QTShapes_QTriF_2
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QTriF_2)
{
    z_qtshapes::ZQTriF g(-1, -2, -3, -4, -5, -6, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 100);
    z_qtshapes::ZQTriF h = g.rotated(10);
    BOOST_TEST(h.x1() == -1);
    BOOST_TEST(h.y1() == -2);
    BOOST_TEST(h.x2() == -3);
    BOOST_TEST(h.y2() == -4);
    BOOST_TEST(h.x3() == -5);
    BOOST_TEST(h.y3() == -6);
    BOOST_TEST(h.angle() == 110);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 110);
    z_qtshapes::ZQTriF i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x1() == -1);
    BOOST_TEST(i.y1() == -2);
    BOOST_TEST(i.x2() == -3);
    BOOST_TEST(i.y2() == -4);
    BOOST_TEST(i.x3() == -5);
    BOOST_TEST(i.y3() == -6);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 10);
    g.setCoords(QPointF(10, 20), QPointF(30, 40), QPointF(50, 60));
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);

    g = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 10);
    g.setCoords(QPointF(1, 2), QPointF(3, 4), QPointF(5, 6), 30);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6, 30);
    g.setCoordsRadians(QPointF(10, 20), QPointF(30, 40), QPointF(50, 60), M_PI_2);
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);
    BOOST_TEST(g.angle() == 90);
}
