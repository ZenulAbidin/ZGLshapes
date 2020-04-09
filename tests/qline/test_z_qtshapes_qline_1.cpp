#define BOOST_TEST_MODULE Z_QTShapes_QLine_1
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_QLine_1)
{
    z_qtshapes::ZQLine a;
    BOOST_TEST(a.x1() == 0);
    BOOST_TEST(a.y1() == 0);
    BOOST_TEST(a.x2() == 0);
    BOOST_TEST(a.y2() == 0);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQLine(QPoint(1,2), QPoint(3,4));
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQLine(QPoint(1,2), QPoint(3,4), 10);
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQLine::fromPolar(2, 90);
    BOOST_TEST(a.x1() == 0);
    BOOST_TEST(a.y1() == 0);
    BOOST_TEST(a.x2() == 0);
    BOOST_TEST(a.y2() == -2);
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQLine h(0, 0, 0, 0, 10);
    h.rotate(10);
    BOOST_TEST(h.angle() == 20);
    h = z_qtshapes::ZQLine(0, 0, 0, 0, 20);
    h.rotateRadians(M_PI_2);
    BOOST_TEST(h.angle() == 110);
    z_qtshapes::ZQLine i = h.rotated(10);
    BOOST_TEST(i.x1() == 0);
    BOOST_TEST(i.y1() == 0);
    BOOST_TEST(i.x2() == 0);
    BOOST_TEST(i.y2() == 0);
    BOOST_TEST(i.angle() == 120);
    z_qtshapes::ZQLine j = h.rotatedRadians(M_PI_2);
    BOOST_TEST(j.x1() == 0);
    BOOST_TEST(j.y1() == 0);
    BOOST_TEST(j.x2() == 0);
    BOOST_TEST(j.y2() == 0);
    BOOST_TEST(j.angle() == 200);

    h = z_qtshapes::ZQLine(0, 0, 0, 0, 110);
    h.setAngle(10);
    BOOST_TEST(h.angle() == 10);
}
