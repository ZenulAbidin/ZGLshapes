#define BOOST_TEST_MODULE Z_QTShapes_QTri_5
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_QTri_5)
{
    z_qtshapes::ZQTri g(31, 32, 33, 34, 35, 36, 90);
    g.translate(1, 1);
    BOOST_TEST(g.x1() == 32);
    BOOST_TEST(g.y1() == 33);
    BOOST_TEST(g.x2() == 34);
    BOOST_TEST(g.y2() == 35);
    BOOST_TEST(g.x3() == 36);
    BOOST_TEST(g.y3() == 37);

    g = z_qtshapes::ZQTri(32, 33, 34, 35, 36, 37, 90);
    g.translate(QPoint(-1, -1));
    BOOST_TEST(g.x1() == 31);
    BOOST_TEST(g.y1() == 32);
    BOOST_TEST(g.x2() == 33);
    BOOST_TEST(g.y2() == 34);
    BOOST_TEST(g.x3() == 35);
    BOOST_TEST(g.y3() == 36);

    g = z_qtshapes::ZQTri(31, 32, 33, 34, 35, 36, 90);
    g.translate(1, 1, 2);
    BOOST_TEST(g.x1() == 32);
    BOOST_TEST(g.y1() == 33);
    BOOST_TEST(g.x2() == 34);
    BOOST_TEST(g.y2() == 35);
    BOOST_TEST(g.x3() == 36);
    BOOST_TEST(g.y3() == 37);
    BOOST_TEST(g.angle() == 92);

    g = z_qtshapes::ZQTri(32, 33, 34, 35, 36, 37, 92);
    g.translate(QPoint(1, 1), 2);
    BOOST_TEST(g.x1() == 33);
    BOOST_TEST(g.y1() == 34);
    BOOST_TEST(g.x2() == 35);
    BOOST_TEST(g.y2() == 36);
    BOOST_TEST(g.x3() == 37);
    BOOST_TEST(g.y3() == 38);
    BOOST_TEST(g.angle() == 94);

    g = z_qtshapes::ZQTri(33, 34, 35, 36, 37, 38, 94);
    g.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(g.x1() == 34);
    BOOST_TEST(g.y1() == 35);
    BOOST_TEST(g.x2() == 36);
    BOOST_TEST(g.y2() == 37);
    BOOST_TEST(g.x3() == 38);
    BOOST_TEST(g.y3() == 39);
    BOOST_TEST(g.angle() == 184);

    g = z_qtshapes::ZQTri(34, 35, 36, 37, 38, 39, 184);
    g.translateRadians(QPoint(1, 1), M_PI/2);
    BOOST_TEST(g.x1() == 35);
    BOOST_TEST(g.y1() == 36);
    BOOST_TEST(g.x2() == 37);
    BOOST_TEST(g.y2() == 38);
    BOOST_TEST(g.x3() == 39);
    BOOST_TEST(g.y3() == 40);
    BOOST_TEST(g.angle() == 274);
}
