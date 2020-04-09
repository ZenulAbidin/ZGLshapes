#define BOOST_TEST_MODULE Z_QTShapes_QTri_4
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_QTri_4)
{
    z_qtshapes::ZQTri g(1, 2, 3, 4, 5, 6, 90);
    g.setFirst(QPoint(10, 20));
    BOOST_TEST(g.first().x() == 10);
    BOOST_TEST(g.first().y() == 20);

    g = z_qtshapes::ZQTri(10, 20, 3, 4, 5, 6, 90);
    g.setSecond(QPoint(30, 40));
    BOOST_TEST(g.second().x() == 30);
    BOOST_TEST(g.second().y() == 40);

    g = z_qtshapes::ZQTri(10, 20, 30, 40, 5, 6, 90);
    g.setThird(QPoint(50, 60));
    BOOST_TEST(g.third().x() == 50);
    BOOST_TEST(g.third().y() == 60);

    g = z_qtshapes::ZQTri(10, 20, 30, 40, 50, 60, 90);
    g.setX1(31);
    BOOST_TEST(g.x1() == 31);

    g = z_qtshapes::ZQTri(31, 20, 30, 40, 50, 60, 90);
    g.setY1(32);
    BOOST_TEST(g.y1() == 32);

    g = z_qtshapes::ZQTri(31, 32, 30, 40, 50, 60, 90);
    g.setX2(33);
    BOOST_TEST(g.x2() == 33);

    g = z_qtshapes::ZQTri(31, 32, 33, 40, 50, 60, 90);
    g.setY2(34);
    BOOST_TEST(g.y2() == 34);

    g = z_qtshapes::ZQTri(31, 32, 33, 34, 50, 60, 90);
    g.setX3(35);
    BOOST_TEST(g.x3() == 35);

    g = z_qtshapes::ZQTri(31, 32, 33, 34, 35, 60, 90);
    g.setY3(36);
    BOOST_TEST(g.y3() == 36);
}
