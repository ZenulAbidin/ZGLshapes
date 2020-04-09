#define BOOST_TEST_MODULE Z_QTShapes_QTriF_1
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QTriF_1)
{
    z_qtshapes::ZQTriF a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTriF(QPointF(1,2), QPointF(3,4), QPointF(5,6));
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.x3() == 5);
    BOOST_TEST(a.y3() == 6);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTriF(QPointF(10,20), QPointF(30,40), QPointF(50,60), 10);
    BOOST_TEST(a.x1() == 10);
    BOOST_TEST(a.y1() == 20);
    BOOST_TEST(a.x2() == 30);
    BOOST_TEST(a.y2() == 40);
    BOOST_TEST(a.x3() == 50);
    BOOST_TEST(a.y3() == 60);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6);
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.x3() == 5);
    BOOST_TEST(a.y3() == 6);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 90);
    BOOST_TEST(a.x1() == 10);
    BOOST_TEST(a.y1() == 20);
    BOOST_TEST(a.x2() == 30);
    BOOST_TEST(a.y2() == 40);
    BOOST_TEST(a.x3() == 50);
    BOOST_TEST(a.y3() == 60);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
}
