#define BOOST_TEST_MODULE Z_QTShapes_QEllipseF_1
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QEllipseF_1)
{
    z_qtshapes::ZQEllipseF a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipseF(QPointF(1,2), QPointF(3,4));
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipseF(QPointF(10,20), QPointF(30,40), 10);
    BOOST_TEST(a.x() == 10);
    BOOST_TEST(a.y() == 20);
    BOOST_TEST(a.width() == 30);
    BOOST_TEST(a.height() == 40);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQEllipseF(1, 2, 3, 4);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipseF(10, 20, 30, 40, 90);
    BOOST_TEST(a.x() == 10);
    BOOST_TEST(a.y() == 20);
    BOOST_TEST(a.width() == 30);
    BOOST_TEST(a.height() == 40);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
}
