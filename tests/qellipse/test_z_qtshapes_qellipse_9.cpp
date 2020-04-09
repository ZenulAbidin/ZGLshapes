#define BOOST_TEST_MODULE Z_QTShapes_QEllipse_9
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QEllipse_9)
{
    z_qtshapes::ZQEllipse l(1, 2, 3, 4, 20);
    QMargins ma(1,1,1,1);
    z_qtshapes::ZQEllipse ra;
    ra = l + ma;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 1+1+3+1);
    BOOST_TEST(ra.py2() == 2+1+4+1);
    BOOST_TEST(ra.angle() == 20);
    ra = ma + l;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 1+1+3+1);
    BOOST_TEST(ra.py2() == 2+1+4+1);
    BOOST_TEST(ra.angle() == 20);
    ra = l - ma;
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 1-1+3-1);
    BOOST_TEST(ra.py2() == 2-1+4-1);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsAdded(ma);
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 1+1+3+1);
    BOOST_TEST(ra.py2() == 2+1+4+1);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsRemoved(ma);
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 1-1+3-1);
    BOOST_TEST(ra.py2() == 2-1+4-1);
    BOOST_TEST(ra.angle() == 20);
}

