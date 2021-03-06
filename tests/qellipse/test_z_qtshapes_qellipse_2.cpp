#define BOOST_TEST_MODULE Z_QTShapes_QEllipse_2
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QEllipse_2)
{
    z_qtshapes::ZQEllipse g(-1, -2, 3, 4, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQEllipse(-1, -2, 3, 4, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQEllipse h = g.rotated(10);
    BOOST_TEST(h.x() == -1);
    BOOST_TEST(h.y() == -2);
    BOOST_TEST(h.width() == 3);
    BOOST_TEST(h.height() == 4);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQEllipse i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x() == -1);
    BOOST_TEST(i.y() == -2);
    BOOST_TEST(i.width() == 3);
    BOOST_TEST(i.height() == 4);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQEllipse(-1, -2, 3, 4, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQEllipse(-1, -2, 3, 4, 10);
    g.setCoords(QPoint(10, 20), QPoint(30, 40));
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 30);
    BOOST_TEST(g.py2() == 40);

    g = z_qtshapes::ZQEllipse(10, 20, 30, 40, 10);
    g.setCoords(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 3);
    BOOST_TEST(g.py2() == 4);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQEllipse(1, 2, 3, 4, 30);
    g.setCoordsRadians(QPoint(10, 20), QPoint(30, 40), M_PI_2);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 30);
    BOOST_TEST(g.py2() == 40);
    BOOST_TEST(g.angle() == 90);
}
