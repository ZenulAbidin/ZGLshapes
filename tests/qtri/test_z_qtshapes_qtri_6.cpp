#define BOOST_TEST_MODULE Z_QTShapes_QTri_6
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_QTri_6)
{
    z_qtshapes::ZQTri l(1, 2, 3, 4, 5, 6, 20);
    z_qtshapes::ZQTri m = l.translated(1, 1);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.x3() == 6);
    BOOST_TEST(m.y3() == 7);
    m = l.translated(QPoint(-1, -1));
    BOOST_TEST(m.x1() == 0);
    BOOST_TEST(m.y1() == 1);
    BOOST_TEST(m.x2() == 2);
    BOOST_TEST(m.y2() == 3);
    BOOST_TEST(m.x3() == 4);
    BOOST_TEST(m.y3() == 5);
    m = l.translated(10,10,2);
    BOOST_TEST(m.x1() == 11);
    BOOST_TEST(m.y1() == 12);
    BOOST_TEST(m.x2() == 13);
    BOOST_TEST(m.y2() == 14);
    BOOST_TEST(m.x3() == 15);
    BOOST_TEST(m.y3() == 16);
    BOOST_TEST(m.angle() = 22);
    m = l.translated(QPoint(1, 1), 4);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.x3() == 6);
    BOOST_TEST(m.y3() == 7);
    BOOST_TEST(m.angle() = 24);
    m = l.translatedRadians(QPoint(10, 10), M_PI/2);
    BOOST_TEST(m.x1() == 11);
    BOOST_TEST(m.y1() == 12);
    BOOST_TEST(m.x2() == 13);
    BOOST_TEST(m.y2() == 14);
    BOOST_TEST(m.x3() == 15);
    BOOST_TEST(m.y3() == 16);
    BOOST_TEST(m.angle() = 112);
    m = l.translatedRadians(1, 1, M_PI/2);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.x3() == 6);
    BOOST_TEST(m.y3() == 7);
    BOOST_TEST(m.angle() = 112);
}
