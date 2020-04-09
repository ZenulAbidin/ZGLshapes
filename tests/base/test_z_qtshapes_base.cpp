#define BOOST_TEST_MODULE Z_QTShapes_Base
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

BOOST_AUTO_TEST_CASE(Z_Base)
{
    BOOST_TEST(z_qtshapes::normalizedAngle(10) == 10);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(10.1), 10.1));
    BOOST_TEST(z_qtshapes::normalizedAngle(5850) == 90);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(5850.1), 90.1));
    BOOST_TEST(z_qtshapes::normalizedAngle(5760) == 0);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(5760.1)+1, 0.1+1)); // qFuzzyCompare not reliable with near-zero values
    BOOST_TEST(z_qtshapes::normalizedAngle(-10) == 350);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(-10.1), 349.9));
    BOOST_TEST(z_qtshapes::normalizedAngle(-5850) == 270);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(-5850.1), 269.9));
}
