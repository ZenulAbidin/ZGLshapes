#define BOOST_TEST_MODULE Z_QTShapes_QPoint
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

// ZQPoint/ZQPointF were hardly modified from the original
// Still, we tinkered with a lot of functions so make sure they work properly.
BOOST_AUTO_TEST_CASE(Z_QPoint)
{
    z_qtshapes::ZQPoint p(2,3);
    BOOST_TEST(p.toString() == QString("ZQPoint(2,3)"));
    BOOST_TEST(p.toQPoint().x() == 2);
    BOOST_TEST(p.toQPoint().y() == 3);
}
