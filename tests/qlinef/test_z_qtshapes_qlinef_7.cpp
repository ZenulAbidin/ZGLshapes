#define BOOST_TEST_MODULE Z_QTShapes_QLineF_7
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QLineF_7)
{
    z_qtshapes::ZQLineF k(1, 2, 3, 4, 20);
    z_qtshapes::ZQLineF l(1, 2, 3, 4, 20);

    z_qtshapes::ZQLineF p = l.adjusted(1, 1, 1, 1);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    p = l.adjusted(QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(p.x1() == 0);
    BOOST_TEST(p.y1() == 1);
    BOOST_TEST(p.x2() == 2);
    BOOST_TEST(p.y2() == 3);
    p = l.adjusted(10, 10, 10, 10, 2);
    BOOST_TEST(p.x1() == 11);
    BOOST_TEST(p.y1() == 12);
    BOOST_TEST(p.x2() == 13);
    BOOST_TEST(p.y2() == 14);
    BOOST_TEST(p.angle() = 22);
    p = l.adjusted(QPointF(1, 1), QPointF(1, 1), 4);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.angle() = 24);
    p = l.adjustedRadians(QPointF(10, 10), QPointF(10, 10), M_PI/2);
    BOOST_TEST(p.x1() == 11);
    BOOST_TEST(p.y1() == 12);
    BOOST_TEST(p.x2() == 13);
    BOOST_TEST(p.y2() == 14);
    BOOST_TEST(p.angle() = 112);
    p = l.adjustedRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.angle() = 112);
}
