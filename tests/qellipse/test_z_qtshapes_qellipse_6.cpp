#define BOOST_TEST_MODULE Z_QTShapes_QEllipse_6
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QEllipse_6)
{
    z_qtshapes::ZQEllipse n(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 1+1+3+1);
    BOOST_TEST(n.py2() == 2+1+4+1);

    n = z_qtshapes::ZQEllipse(2, 3, 4, 5, 30);
    n.adjust(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(n.px1() == 1);
    BOOST_TEST(n.py1() == 2);
    BOOST_TEST(n.px2() == 2-1+4-1);
    BOOST_TEST(n.py2() == 3-1+5-1);

    n = z_qtshapes::ZQEllipse(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 1+1+3+1);
    BOOST_TEST(n.py2() == 2+1+4+1);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQEllipse(2, 3, 4, 5, 32);
    n.adjust(QPoint(1, 1), QPoint(1, 1), 2);
    BOOST_TEST(n.px1() == 3);
    BOOST_TEST(n.py1() == 4);
    BOOST_TEST(n.px2() == 2+1+4+1);
    BOOST_TEST(n.py2() == 3+1+5+1);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQEllipse(3, 4, 5, 6, 34);
    n.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.px1() == 4);
    BOOST_TEST(n.py1() == 5);
    BOOST_TEST(n.px2() == 3+1+5+1);
    BOOST_TEST(n.py2() == 4+1+6+1);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQEllipse(4, 5, 6, 7, 124);
    n.adjustRadians(QPoint(1, 1), QPoint(1, 1), M_PI/2);
    BOOST_TEST(n.px1() == 5);
    BOOST_TEST(n.py1() == 6);
    BOOST_TEST(n.px2() == 4+1+6+1);
    BOOST_TEST(n.py2() == 5+1+7+1);
    BOOST_TEST(n.angle() == 214);
}
