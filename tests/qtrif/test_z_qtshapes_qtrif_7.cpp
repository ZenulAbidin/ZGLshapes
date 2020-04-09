#define BOOST_TEST_MODULE Z_QTShapes_QTriF_7
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QTriF_7)
{
    z_qtshapes::ZQTriF n(1, 2, 3, 4, 5, 6, 30);
    n.adjust(1, 1, 1, 1, 1, 1);
    BOOST_TEST(n.x1() == 2);
    BOOST_TEST(n.y1() == 3);
    BOOST_TEST(n.x2() == 4);
    BOOST_TEST(n.y2() == 5);
    BOOST_TEST(n.x3() == 6);
    BOOST_TEST(n.y3() == 7);

    n = z_qtshapes::ZQTriF(2, 3, 4, 5, 6, 7, 30);
    n.adjust(QPointF(-1, -1), QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(n.x1() == 1);
    BOOST_TEST(n.y1() == 2);
    BOOST_TEST(n.x2() == 3);
    BOOST_TEST(n.y2() == 4);
    BOOST_TEST(n.x3() == 5);
    BOOST_TEST(n.y3() == 6);

    n = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6, 30);
    n.adjust(1, 1, 1, 1, 1, 1, 2);
    BOOST_TEST(n.x1() == 2);
    BOOST_TEST(n.y1() == 3);
    BOOST_TEST(n.x2() == 4);
    BOOST_TEST(n.y2() == 5);
    BOOST_TEST(n.x3() == 6);
    BOOST_TEST(n.y3() == 7);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQTriF(2, 3, 4, 5, 6, 7, 32);
    n.adjust(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1), 2);
    BOOST_TEST(n.x1() == 3);
    BOOST_TEST(n.y1() == 4);
    BOOST_TEST(n.x2() == 5);
    BOOST_TEST(n.y2() == 6);
    BOOST_TEST(n.x3() == 7);
    BOOST_TEST(n.y3() == 8);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQTriF(3, 4, 5, 6, 7, 8, 34);
    n.adjustRadians(1, 1, 1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.x1() == 4);
    BOOST_TEST(n.y1() == 5);
    BOOST_TEST(n.x2() == 6);
    BOOST_TEST(n.y2() == 7);
    BOOST_TEST(n.x3() == 8);
    BOOST_TEST(n.y3() == 9);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQTriF(4, 5, 6, 7, 8, 9, 124);
    n.adjustRadians(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1), M_PI/2);
    BOOST_TEST(n.x1() == 5);
    BOOST_TEST(n.y1() == 6);
    BOOST_TEST(n.x2() == 7);
    BOOST_TEST(n.y2() == 8);
    BOOST_TEST(n.x3() == 9);
    BOOST_TEST(n.y3() == 10);
    BOOST_TEST(n.angle() == 214);
}
