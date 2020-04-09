#define BOOST_TEST_MODULE Z_QTShapes_QRectF_8
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QRectF_8)
{
    z_qtshapes::ZQRectF h(1, 2, 3, 4, 90);
    z_qtshapes::ZQRectF g(-1, -2, -3, -4, 200);

    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPointF(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQRectF q(1, 2, 3, 4, 30);
    z_qtshapes::ZQRectF r(1, 2, 3, 4, 20);
    z_qtshapes::ZQRectF s(1, 2, 3, 4, 20);
    if (r == s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (q != s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }
}
