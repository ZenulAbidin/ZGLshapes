#define BOOST_TEST_MODULE Z_QTShapes_QTriF_3
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QTriF_3)
{
    z_qtshapes::ZQTriF g(10, 20, 30, 40, 50, 60, 90);
    g.setCoords(1, 2, 3, 4, 5, 6);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);

    g = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6, 90);
    g.setCoords(10, 20, 30, 40, 50, 60, 30);
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 30);
    g.setCoordsRadians(1, 2, 3, 4, 5, 6, M_PI_2);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);
    BOOST_TEST(g.angle() == 90);

    qreal a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0, g2 = 0, h2 = 0;

    z_qtshapes::ZQTriF h(1, 2, 3, 4, 5, 6, 90);
    h.getCoords(&a2, &b2, &c2, &d2, &e2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);

    h.getCoords(&a2, &b2, &c2, &d2, &e2, &f2, &g2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);
    BOOST_TEST(g2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &e2, &f2, &h2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);
    BOOST_TEST(h2 == M_PI_2);
}
