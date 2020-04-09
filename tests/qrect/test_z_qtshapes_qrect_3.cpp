#define BOOST_TEST_MODULE Z_QTShapes_QRect_3
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QRect_3)
{
    z_qtshapes::ZQRect g(10, 20, 30, 40, 90);
    g.setCoords(1, 2, 3, 4);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 3);
    BOOST_TEST(g.py2() == 4);

    g = z_qtshapes::ZQRect(1, 2, 3, 4, 90);
    g.setCoords(10, 20, 30, 40, 30);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 30);
    BOOST_TEST(g.py2() == 40);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQRect(10, 20, 30, 40, 30);
    g.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 3);
    BOOST_TEST(g.py2() == 4);
    BOOST_TEST(g.angle() == 90);

    int a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0;
    qreal f2 = 0;

    z_qtshapes::ZQRect h(1, 2, 3, 4, 90);
    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(f2 == M_PI_2);
}
