#define BOOST_TEST_MODULE Z_QTShapes_QEllipse_7
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QEllipse_7)
{
    z_qtshapes::ZQEllipse l(1, 2, 3, 4, 20);
    z_qtshapes::ZQEllipse p = l.adjusted(1, 1, 1, 1);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 1+1+3+1);
    BOOST_TEST(p.py2() == 2+1+4+1);

    p = l.adjusted(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(p.px1() == 0);
    BOOST_TEST(p.py1() == 1);
    BOOST_TEST(p.px2() == 1-1+3-1);
    BOOST_TEST(p.py2() == 2-1+4-1);

    p = l.adjusted(10, 10, 10, 10, 2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 1+10+3+10);
    BOOST_TEST(p.py2() == 2+10+4+10);
    BOOST_TEST(p.angle() = 22);

    p = l.adjusted(QPoint(1, 1), QPoint(1, 1), 4);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 1+1+3+1);
    BOOST_TEST(p.py2() == 2+1+4+1);
    BOOST_TEST(p.angle() = 24);

    p = l.adjustedRadians(QPoint(10, 10), QPoint(10, 10), M_PI/2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 1+10+3+10);
    BOOST_TEST(p.py2() == 2+10+4+10);
    BOOST_TEST(p.angle() = 112);

    p = l.adjustedRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 1+1+3+1);
    BOOST_TEST(p.py2() == 2+1+4+1);
    BOOST_TEST(p.angle() = 112);

    BOOST_TEST(l.toString() == QString("ZQEllipse(1,2 size 3x4 20 degrees)"));
}
