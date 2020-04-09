#define BOOST_TEST_MODULE Z_QTShapes_QEllipse_5
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QEllipse_5)
{
    z_qtshapes::ZQEllipse l(1, 2, 3, 4, 20);
    z_qtshapes::ZQEllipse m = l.translated(1, 1);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    m = l.translated(QPoint(-1, -1));
    BOOST_TEST(m.px1() == 0);
    BOOST_TEST(m.py1() == 1);
    m = l.translated(10,10,2);
    BOOST_TEST(m.px1() == 11);
    BOOST_TEST(m.py1() == 12);
    BOOST_TEST(m.angle() = 22);
    m = l.translated(QPoint(1, 1), 4);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    BOOST_TEST(m.angle() = 24);
    m = l.translatedRadians(QPoint(10, 10), M_PI/2);
    BOOST_TEST(m.px1() == 11);
    BOOST_TEST(m.py1() == 12);
    BOOST_TEST(m.angle() = 112);
    m = l.translatedRadians(1, 1, M_PI/2);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    BOOST_TEST(m.angle() = 112);
}
