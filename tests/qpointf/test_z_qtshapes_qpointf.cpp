#define BOOST_TEST_MODULE Z_QTShapes_QPointF
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"


BOOST_AUTO_TEST_CASE(Z_QPointF)
{
    z_qtshapes::ZQPointF p(2.1,3.1);
    BOOST_TEST(p.toString() == QString("ZQPointF(2.1,3.1)"));
    BOOST_TEST(p.toQPoint().x() == 2.1);
    BOOST_TEST(p.toQPoint().y() == 3.1);
}

