#define BOOST_TEST_MODULE Z_QTShapes_QLine_3
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QLine_3)
{
    z_qtshapes::ZQLine h(1, 2, 3, 4, 90);
    z_qtshapes::ZQLine i(-1, -2, -3, -4, 200);
    int a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0;
    qreal f2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(f2 == M_PI_2);


    BOOST_TEST(h.toString() == QString("ZQLine(1,2 to 3,4 90 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    h.toPath();
    h.toPath(world3, QPointF(1,1));
    h.contains(i);
    h.contains(QPoint(1,1));
    h.intersects(i);
    h.united(i);
    h.intersected(i);

    z_qtshapes::ZQLine kk(1, 2, 3, 4, 30);
    z_qtshapes::ZQLine k(1, 2, 3, 4, 30);
    z_qtshapes::ZQLine l(1, 2, 3, 4, 20);
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
}
