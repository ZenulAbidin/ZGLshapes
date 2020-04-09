#define BOOST_TEST_MODULE Z_QTShapes_QTriF_9
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QTriF_9)
{
    z_qtshapes::ZQTriF h(1, 2, 3, 4, 5, 6, 90);
    z_qtshapes::ZQTriF g(-1, -2, -3, -4, -5, -6, 200);    

    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPoint(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQTriF q(1, 2, 3, 4, 5, 6, 30);
    z_qtshapes::ZQTriF r(1, 2, 3, 4, 5, 6, 20);
    z_qtshapes::ZQTriF s(1, 2, 3, 4, 5, 6, 20);
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


/*TODO
    z_qtshapes::ZQTriF t(0, 0, 2, 0, 0, 1, 0);
    z_qtshapes::ZQTriF u(0, 0, 1, 0, 0, 1, 0);
    z_qtshapes::ZQTriF v(0, 0, 1, 0, 0, 2, 0);
    z_qtshapes::ZQTriF w(0, 0, 2, 0, 0, 2, 0);
    BOOST_TEST(t.isAcute());
    BOOST_TEST(u.isRight());
    BOOST_TEST(v.isObtuse());
    BOOST_TEST(t.isIso());
    BOOST_TEST(w.isEquilateral());
    BOOST_TEST(v.isScalene());
*/
}
