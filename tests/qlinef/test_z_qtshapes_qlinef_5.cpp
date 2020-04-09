#define BOOST_TEST_MODULE Z_QTShapes_QLineF_5
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QLineF_5)
{
    z_qtshapes::ZQLineF k(1, 2, 3, 4, 20);
    z_qtshapes::ZQLineF l(1, 2, 3, 4, 20);
    z_qtshapes::ZQLineF m = l.translated(1, 1);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    m = l.translated(QPointF(-1, -1));
    BOOST_TEST(m.x1() == 0);
    BOOST_TEST(m.y1() == 1);
    BOOST_TEST(m.x2() == 2);
    BOOST_TEST(m.y2() == 3);
    m = l.translated(10,10,2);
    BOOST_TEST(m.x1() == 11);
    BOOST_TEST(m.y1() == 12);
    BOOST_TEST(m.x2() == 13);
    BOOST_TEST(m.y2() == 14);
    BOOST_TEST(m.angle() = 22);
    m = l.translated(QPointF(1, 1), 4);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.angle() = 24);
    m = l.translatedRadians(QPointF(10, 10), M_PI/2);
    BOOST_TEST(m.x1() == 11);
    BOOST_TEST(m.y1() == 12);
    BOOST_TEST(m.x2() == 13);
    BOOST_TEST(m.y2() == 14);
    BOOST_TEST(m.angle() = 112);
    m = l.translatedRadians(1, 1, M_PI/2);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.angle() = 112);
}
