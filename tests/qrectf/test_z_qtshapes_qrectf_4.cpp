#define BOOST_TEST_MODULE Z_QTShapes_QRectF_4
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QRectF_4)
{
    z_qtshapes::ZQRectF g(31, 32, 33, 34, 90);
    g.translate(1, 1);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);

    g = z_qtshapes::ZQRectF(32, 33, 34, 35, 90);
    g.translate(QPointF(-1, -1));
    BOOST_TEST(g.px1() == 31);
    BOOST_TEST(g.py1() == 32);

    g = z_qtshapes::ZQRectF(31, 32, 33, 34, 90);
    g.translate(1, 1, 2);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);
    BOOST_TEST(g.angle() == 92);

    g = z_qtshapes::ZQRectF(32, 33, 34, 35, 92);
    g.translate(QPointF(1, 1), 2);
    BOOST_TEST(g.px1() == 33);
    BOOST_TEST(g.py1() == 34);
    BOOST_TEST(g.angle() == 94);

    g = z_qtshapes::ZQRectF(33, 34, 35, 36, 94);
    g.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(g.px1() == 34);
    BOOST_TEST(g.py1() == 35);
    BOOST_TEST(g.angle() == 184);

    g = z_qtshapes::ZQRectF(34, 35, 36, 37, 184);
    g.translateRadians(QPointF(1, 1), M_PI/2);
    BOOST_TEST(g.px1() == 35);
    BOOST_TEST(g.py1() == 36);
    BOOST_TEST(g.angle() == 274);
}
