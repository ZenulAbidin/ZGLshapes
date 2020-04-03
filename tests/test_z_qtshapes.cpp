#define BOOST_TEST_MODULE Z_QTShapes
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

// Some test cases may be removed on the assumption that the corresponding classes
// and methods are "grandfathered", not changed after they are published.

BOOST_AUTO_TEST_CASE(Z_Base)
{
    BOOST_TEST(z_qtshapes::normalizedAngle(10) == 10);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(10.1), 10.1));
    BOOST_TEST(z_qtshapes::normalizedAngle(5850) == 90);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(5850.1), 90.1));
    BOOST_TEST(z_qtshapes::normalizedAngle(5760) == 0);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(5760.1), 0.1));
    BOOST_TEST(z_qtshapes::normalizedAngle(-10) == 350);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(-10.1), 350.1));
    BOOST_TEST(z_qtshapes::normalizedAngle(-5850) == 270);
    BOOST_TEST(qFuzzyCompare(z_qtshapes::normalizedAngle(-5850.1), 270.1));
}

// ZQPoint/ZQPointF were hardly modified from the original
// Still, we tinkered with a lot of functions so make sure they work properly.
BOOST_AUTO_TEST_CASE(Z_QPoint)
{
    z_qtshapes::ZQPoint p(2,3);
    BOOST_TEST(p.toString() == QString("ZQPoint(2,3)"));
    BOOST_TEST(p.toQPoint().x() == 2);
    BOOST_TEST(p.toQPoint().y() == 3);
}

BOOST_AUTO_TEST_CASE(Z_QPointF)
{
    z_qtshapes::ZQPointF p(2.1,3.1);
    BOOST_TEST(p.toString() == QString("ZQPointF(2.1,3.1)"));
    BOOST_TEST(p.toQPoint().x() == 2.1);
    BOOST_TEST(p.toQPoint().y() == 3.1);
}

// Intersections, unions, and containment functions are impossible to test
// without drawing them on the screen because they use QPainterPath.

BOOST_AUTO_TEST_CASE(Z_QLine)
{
    z_qtshapes::ZQLine a;
    BOOST_TEST(a.x1() == 0);
    BOOST_TEST(a.y1() == 0);
    BOOST_TEST(a.x2() == 0);
    BOOST_TEST(a.y2() == 0);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQLine(QPoint(1,2), QPoint(3,4));
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQLine(QPoint(1,2), QPoint(3,4), 10);
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQLine::fromPolar(2, 90);
    BOOST_TEST(a.x1() == 0);
    BOOST_TEST(a.y1() == 0);
    BOOST_TEST(a.x2() == 0);
    BOOST_TEST(a.y2() == -2);
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQLine h(0, 0, 0, 0, 10);
    h.rotate(10);
    BOOST_TEST(h.angle() == 20);
    h = z_qtshapes::ZQLine(0, 0, 0, 0, 20);
    h.rotateRadians(M_PI_2);
    BOOST_TEST(h.angle() == 110);
    z_qtshapes::ZQLine i = h.rotated(10);
    BOOST_TEST(i.x1() == 0);
    BOOST_TEST(i.y1() == 0);
    BOOST_TEST(i.x2() == 0);
    BOOST_TEST(i.y2() == 0);
    BOOST_TEST(i.angle() == 120);
    z_qtshapes::ZQLine j = h.rotatedRadians(M_PI_2);
    BOOST_TEST(j.x1() == 0);
    BOOST_TEST(j.y1() == 0);
    BOOST_TEST(j.x2() == 0);
    BOOST_TEST(j.y2() == 0);
    BOOST_TEST(j.angle() == 200);

    h = z_qtshapes::ZQLine(0, 0, 0, 0, 110);
    h.setAngle(10);
    BOOST_TEST(h.angle() == 10);

    h = z_qtshapes::ZQLine(0, 0, 0, 0, 10);
    h.setPoints(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLine(1, 2, 3, 4, 30);
    h.setPointsRadians(QPoint(5, 6), QPoint(7, 8), M_PI_2);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLine(5, 6, 7, 8, 90);
    h.setCoords(1, 2, 3, 4);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLine(1, 2, 3, 4, 90);
    h.setCoords(5, 6, 7, 8, 30);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLine(5, 6, 7, 8, 30);
    h.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLine(1, 2, 3, 4, 90);
    int a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0;
    qreal f2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(f2 == M_PI_2);


    BOOST_TEST(h.toString() == QString("ZQLine(1,2 to 3,4 90 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    h.toPath();
    h.toPath(world3, QPointF(1,1));
    h.contains(i);
    h.contains(QPoint(1,1));
    h.intersects(i);
    h.united(i);
    h.intersected(i);

    z_qtshapes::ZQLine k(1, 2, 3, 4, 30);
    z_qtshapes::ZQLine l(1, 2, 3, 4, 20);
    if (h == k) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (h != l) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }


    k.translate(1, 1);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);

    k = z_qtshapes::ZQLine(2, 3, 4, 5, 30);
    k.translate(QPoint(-1, -1));
    BOOST_TEST(k.x1() == 1);
    BOOST_TEST(k.y1() == 2);
    BOOST_TEST(k.x2() == 3);
    BOOST_TEST(k.y2() == 4);

    k = z_qtshapes::ZQLine(1, 2, 3, 4, 30);
    k.translate(1, 1, 2);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);
    BOOST_TEST(k.angle() == 32);

    k = z_qtshapes::ZQLine(2, 3, 4, 5, 32);
    k.translate(QPoint(1, 1), 2);
    BOOST_TEST(k.x1() == 3);
    BOOST_TEST(k.y1() == 4);
    BOOST_TEST(k.x2() == 5);
    BOOST_TEST(k.y2() == 6);
    BOOST_TEST(k.angle() == 34);

    k = z_qtshapes::ZQLine(3, 4, 5, 6, 34);
    k.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(k.x1() == 4);
    BOOST_TEST(k.y1() == 5);
    BOOST_TEST(k.x2() == 6);
    BOOST_TEST(k.y2() == 7);
    BOOST_TEST(k.angle() == 124);

    k = z_qtshapes::ZQLine(4, 5, 6, 7, 124);
    k.translateRadians(QPoint(1, 1), M_PI/2);
    BOOST_TEST(k.x1() == 5);
    BOOST_TEST(k.y1() == 6);
    BOOST_TEST(k.x2() == 7);
    BOOST_TEST(k.y2() == 8);
    BOOST_TEST(k.angle() == 214);

    k = z_qtshapes::ZQLine(5, 6, 7, 8, 214);
    z_qtshapes::ZQLine m = l.translated(1, 1);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    m = l.translated(QPoint(-1, -1));
    BOOST_TEST(k.x1() == 0);
    BOOST_TEST(k.y1() == 1);
    BOOST_TEST(k.x2() == 2);
    BOOST_TEST(k.y2() == 3);
    m = l.translated(10,10,2);
    BOOST_TEST(m.x1() == 11);
    BOOST_TEST(m.y1() == 12);
    BOOST_TEST(m.x2() == 13);
    BOOST_TEST(m.y2() == 14);
    BOOST_TEST(m.angle() = 22);
    m = l.translated(QPoint(1, 1), 4);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.angle() = 24);
    m = l.translatedRadians(QPoint(10, 10), M_PI/2);
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

    z_qtshapes::ZQLine o = k;
    o.adjust(1, 1, 1, 1);
    BOOST_TEST(o.x1() == 2);
    BOOST_TEST(o.y1() == 3);
    BOOST_TEST(o.x2() == 4);
    BOOST_TEST(o.y2() == 5);

    o = z_qtshapes::ZQLine(2, 3, 4, 5, 30);
    o.adjust(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(o.x1() == 1);
    BOOST_TEST(o.y1() == 2);
    BOOST_TEST(o.x2() == 3);
    BOOST_TEST(o.y2() == 4);

    o = z_qtshapes::ZQLine(1, 2, 3, 4, 30);
    o.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(o.x1() == 2);
    BOOST_TEST(o.y1() == 3);
    BOOST_TEST(o.x2() == 4);
    BOOST_TEST(o.y2() == 5);
    BOOST_TEST(o.angle() == 32);

    o = z_qtshapes::ZQLine(2, 3, 4, 5, 32);
    o.adjust(QPoint(1, 1), QPoint(1, 1), 2);
    BOOST_TEST(o.x1() == 3);
    BOOST_TEST(o.y1() == 4);
    BOOST_TEST(o.x2() == 5);
    BOOST_TEST(o.y2() == 6);
    BOOST_TEST(o.angle() == 34);

    o = z_qtshapes::ZQLine(3, 4, 5, 6, 34);
    o.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(o.x1() == 4);
    BOOST_TEST(o.y1() == 5);
    BOOST_TEST(o.x2() == 6);
    BOOST_TEST(o.y2() == 7);
    BOOST_TEST(o.angle() == 124);

    o = z_qtshapes::ZQLine(4, 5, 6, 7, 124);
    o.adjustRadians(QPoint(1, 1), QPoint(1, 1), M_PI/2);
    BOOST_TEST(o.x1() == 5);
    BOOST_TEST(o.y1() == 6);
    BOOST_TEST(o.x2() == 7);
    BOOST_TEST(o.y2() == 8);
    BOOST_TEST(o.angle() == 214);

    z_qtshapes::ZQLine p = l.adjusted(1, 1, 1, 1);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    p = l.adjusted(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(p.x1() == 0);
    BOOST_TEST(p.y1() == 1);
    BOOST_TEST(p.x2() == 2);
    BOOST_TEST(p.y2() == 3);
    p = l.adjusted(10, 10, 10, 10, 2);
    BOOST_TEST(p.x1() == 11);
    BOOST_TEST(p.y1() == 12);
    BOOST_TEST(p.x2() == 13);
    BOOST_TEST(m.y2() == 14);
    BOOST_TEST(p.angle() = 22);
    p = l.adjusted(QPoint(1, 1), QPoint(1, 1), 4);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.angle() = 24);
    p = l.adjustedRadians(QPoint(10, 10), QPoint(10, 10), M_PI/2);
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

BOOST_AUTO_TEST_CASE(Z_QLineF)
{
    z_qtshapes::ZQLineF a;
    BOOST_TEST(a.x1() == 0);
    BOOST_TEST(a.y1() == 0);
    BOOST_TEST(a.x2() == 0);
    BOOST_TEST(a.y2() == 0);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQLineF(QPointF(1,2), QPointF(3,4));
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQLineF(QPointF(1,2), QPointF(3,4), 10);
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQLineF::fromPolar(2, 90);
    BOOST_TEST(a.x1() == 0);
    BOOST_TEST(a.y1() == 0);
    BOOST_TEST(a.x2() == 0);
    BOOST_TEST(a.y2() == -2);
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQLineF h(0, 0, 0, 0, 10);
    h.rotate(10);
    BOOST_TEST(h.angle() == 20);
    h = z_qtshapes::ZQLineF(0, 0, 0, 0, 20);
    h.rotateRadians(M_PI_2);
    BOOST_TEST(h.angle() == 110);
    z_qtshapes::ZQLineF i = h.rotated(10);
    BOOST_TEST(i.x1() == 0);
    BOOST_TEST(i.y1() == 0);
    BOOST_TEST(i.x2() == 0);
    BOOST_TEST(i.y2() == 0);
    BOOST_TEST(i.angle() == 120);
    z_qtshapes::ZQLineF j = h.rotatedRadians(M_PI_2);
    BOOST_TEST(j.x1() == 0);
    BOOST_TEST(j.y1() == 0);
    BOOST_TEST(j.x2() == 0);
    BOOST_TEST(j.y2() == 0);
    BOOST_TEST(j.angle() == 200);

    h = z_qtshapes::ZQLineF(0, 0, 0, 0, 110);
    h.setAngle(10);
    BOOST_TEST(h.angle() == 10);

    h = z_qtshapes::ZQLineF(0, 0, 0, 0, 10);
    h.setPoints(QPointF(1, 2), QPointF(3, 4), 30);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLineF(1, 2, 3, 4, 30);
    h.setPointsRadians(QPointF(5, 6), QPointF(7, 8), M_PI_2);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLineF(5, 6, 7, 8, 90);
    h.setCoords(1, 2, 3, 4);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLineF(1, 2, 3, 4, 90);
    h.setCoords(5, 6, 7, 8, 30);
    BOOST_TEST(h.x1() == 5);
    BOOST_TEST(h.y1() == 6);
    BOOST_TEST(h.x2() == 7);
    BOOST_TEST(h.y2() == 8);
    BOOST_TEST(h.angle() == 30);

    h = z_qtshapes::ZQLineF(5, 6, 7, 8, 30);
    h.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(h.x1() == 1);
    BOOST_TEST(h.y1() == 2);
    BOOST_TEST(h.x2() == 3);
    BOOST_TEST(h.y2() == 4);
    BOOST_TEST(h.angle() == 90);

    h = z_qtshapes::ZQLineF(1, 2, 3, 4, 90);
    qreal a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(f2 == M_PI_2);


    BOOST_TEST(h.toString() == QString("ZQLineF(1,2 to 3,4 90 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    h.toPath();
    h.toPath(world3, QPointF(1,1));
    h.contains(i);
    h.contains(QPointF(1,1));
    h.intersects(i);
    h.united(i);
    h.intersected(i);

    z_qtshapes::ZQLineF k(1, 2, 3, 4, 30);
    z_qtshapes::ZQLineF l(1, 2, 3, 4, 20);
    if (h == k) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (h != l) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    k.translate(1, 1);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);

    k = z_qtshapes::ZQLineF(2, 3, 4, 5, 30);
    k.translate(QPointF(-1, -1));
    BOOST_TEST(k.x1() == 1);
    BOOST_TEST(k.y1() == 2);
    BOOST_TEST(k.x2() == 3);
    BOOST_TEST(k.y2() == 4);

    k = z_qtshapes::ZQLineF(1, 2, 3, 4, 30);
    k.translate(1, 1, 2);
    BOOST_TEST(k.x1() == 2);
    BOOST_TEST(k.y1() == 3);
    BOOST_TEST(k.x2() == 4);
    BOOST_TEST(k.y2() == 5);
    BOOST_TEST(k.angle() == 32);

    k = z_qtshapes::ZQLineF(2, 3, 4, 5, 32);
    k.translate(QPointF(1, 1), 2);
    BOOST_TEST(k.x1() == 3);
    BOOST_TEST(k.y1() == 4);
    BOOST_TEST(k.x2() == 5);
    BOOST_TEST(k.y2() == 6);
    BOOST_TEST(k.angle() == 34);

    k = z_qtshapes::ZQLineF(3, 4, 5, 6, 34);
    k.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(k.x1() == 4);
    BOOST_TEST(k.y1() == 5);
    BOOST_TEST(k.x2() == 6);
    BOOST_TEST(k.y2() == 7);
    BOOST_TEST(k.angle() == 124);

    k = z_qtshapes::ZQLineF(4, 5, 6, 7, 124);
    k.translateRadians(QPointF(1, 1), M_PI/2);
    BOOST_TEST(k.x1() == 5);
    BOOST_TEST(k.y1() == 6);
    BOOST_TEST(k.x2() == 7);
    BOOST_TEST(k.y2() == 8);
    BOOST_TEST(k.angle() == 214);

    l = z_qtshapes::ZQLineF(1, 2, 3, 4, 20);
    z_qtshapes::ZQLineF m = l.translated(1, 1);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    m = l.translated(QPointF(-1, -1));
    BOOST_TEST(k.x1() == 0);
    BOOST_TEST(k.y1() == 1);
    BOOST_TEST(k.x2() == 2);
    BOOST_TEST(k.y2() == 3);
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

    z_qtshapes::ZQLineF o = k;
    o.adjust(1, 1, 1, 1);
    BOOST_TEST(o.x1() == 2);
    BOOST_TEST(o.y1() == 3);
    BOOST_TEST(o.x2() == 4);
    BOOST_TEST(o.y2() == 5);

    o = z_qtshapes::ZQLineF(2, 3, 4, 5, 30);
    o.adjust(QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(o.x1() == 1);
    BOOST_TEST(o.y1() == 2);
    BOOST_TEST(o.x2() == 3);
    BOOST_TEST(o.y2() == 4);

    o = z_qtshapes::ZQLineF(1, 2, 3, 4, 30);
    o.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(o.x1() == 2);
    BOOST_TEST(o.y1() == 3);
    BOOST_TEST(o.x2() == 4);
    BOOST_TEST(o.y2() == 5);
    BOOST_TEST(o.angle() == 32);

    o = z_qtshapes::ZQLineF(2, 3, 4, 5, 32);
    o.adjust(QPointF(1, 1), QPointF(1, 1), 2);
    BOOST_TEST(o.x1() == 3);
    BOOST_TEST(o.y1() == 4);
    BOOST_TEST(o.x2() == 5);
    BOOST_TEST(o.y2() == 6);
    BOOST_TEST(o.angle() == 34);

    o = z_qtshapes::ZQLineF(3, 4, 5, 6, 34);
    o.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(o.x1() == 4);
    BOOST_TEST(o.y1() == 5);
    BOOST_TEST(o.x2() == 6);
    BOOST_TEST(o.y2() == 7);
    BOOST_TEST(o.angle() == 124);

    o = z_qtshapes::ZQLineF(4, 5, 6, 7, 124);
    o.adjustRadians(QPointF(1, 1), QPointF(1, 1), M_PI/2);
    BOOST_TEST(o.x1() == 5);
    BOOST_TEST(o.y1() == 6);
    BOOST_TEST(o.x2() == 7);
    BOOST_TEST(o.y2() == 8);
    BOOST_TEST(o.angle() == 214);

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
    BOOST_TEST(m.y2() == 14);
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

BOOST_AUTO_TEST_CASE(Z_QTri)
{
    z_qtshapes::ZQTri a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTri(QPoint(1,2), QPoint(3,4), QPoint(5,6));
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.x3() == 5);
    BOOST_TEST(a.y3() == 6);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTri(QPoint(10,20), QPoint(30,40), QPoint(50,60), 10);
    BOOST_TEST(a.x1() == 10);
    BOOST_TEST(a.y1() == 20);
    BOOST_TEST(a.x2() == 30);
    BOOST_TEST(a.y2() == 40);
    BOOST_TEST(a.x3() == 50);
    BOOST_TEST(a.y3() == 60);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQTri(1, 2, 3, 4, 5, 6);
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.x3() == 5);
    BOOST_TEST(a.y3() == 6);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTri(10, 20, 30, 40, 50, 60, 90);
    BOOST_TEST(a.x1() == 10);
    BOOST_TEST(a.y1() == 20);
    BOOST_TEST(a.x2() == 30);
    BOOST_TEST(a.y2() == 40);
    BOOST_TEST(a.x3() == 50);
    BOOST_TEST(a.y3() == 60);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQTri g(-1, -2, -3, -4, -5, -6, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQTri(-1, -2, -3, -4, -5, -6, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQTri h = g.rotated(10);
    BOOST_TEST(h.x1() == -1);
    BOOST_TEST(h.y1() == -2);
    BOOST_TEST(h.x2() == -3);
    BOOST_TEST(h.y2() == -4);
    BOOST_TEST(h.x3() == -5);
    BOOST_TEST(h.y3() == -6);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQTri i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x1() == -1);
    BOOST_TEST(i.y1() == -2);
    BOOST_TEST(i.x2() == -3);
    BOOST_TEST(i.y2() == -4);
    BOOST_TEST(i.x3() == -5);
    BOOST_TEST(i.y3() == -6);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQTri(-1, -2, -3, -4, -5, -6, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQTri(-1, -2, -3, -4, -5, -6, 10);
    g.setCoords(QPoint(10, 20), QPoint(30, 40), QPoint(50, 60));
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);

    g = z_qtshapes::ZQTri(10, 20, 30, 40, 50, 60, 10);
    g.setCoords(QPoint(1, 2), QPoint(3, 4), QPoint(5, 6), 30);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQTri(1, 2, 3, 4, 5, 6, 30);
    g.setCoordsRadians(QPoint(10, 20), QPoint(30, 40), QPoint(50, 60), M_PI_2);
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);
    BOOST_TEST(g.angle() == 90);

    g = z_qtshapes::ZQTri(10, 20, 30, 40, 50, 60, 90);
    g.setCoords(1, 2, 3, 4, 5, 6);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);

    g = z_qtshapes::ZQTri(1, 2, 3, 4, 5, 6, 90);
    g.setCoords(10, 20, 30, 40, 50, 60, 30);
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQTri(10, 20, 30, 40, 50, 60, 30);
    g.setCoordsRadians(1, 2, 3, 4, 5, 6, M_PI_2);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);
    BOOST_TEST(g.angle() == 90);

    int a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0, g2 = 0;
    qreal h2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2, &e2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);

    h.getCoords(&a2, &b2, &c2, &d2, &e2, &f2, &g2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);
    BOOST_TEST(g2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &e2, &f2, &h2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);
    BOOST_TEST(h2 == M_PI_2);

    g = z_qtshapes::ZQTri(1, 2, 3, 4, 5, 6, 90);
    g.setFirst(QPoint(10, 20));
    BOOST_TEST(g.first().x() == 10);
    BOOST_TEST(g.first().y() == 20);

    g = z_qtshapes::ZQTri(10, 20, 3, 4, 5, 6, 90);
    g.setSecond(QPoint(30, 40));
    BOOST_TEST(g.second().x() == 30);
    BOOST_TEST(g.second().y() == 40);

    g = z_qtshapes::ZQTri(10, 20, 30, 40, 5, 6, 90);
    g.setThird(QPoint(50, 60));
    BOOST_TEST(g.third().x() == 50);
    BOOST_TEST(g.third().y() == 60);

    g = z_qtshapes::ZQTri(10, 20, 30, 40, 50, 60, 90);
    g.setX1(31);
    BOOST_TEST(g.x1() == 31);

    g = z_qtshapes::ZQTri(31, 20, 30, 40, 50, 60, 90);
    g.setY1(32);
    BOOST_TEST(g.y1() == 32);

    g = z_qtshapes::ZQTri(31, 32, 30, 40, 50, 60, 90);
    g.setX2(33);
    BOOST_TEST(g.x2() == 33);

    g = z_qtshapes::ZQTri(31, 32, 33, 40, 50, 60, 90);
    g.setY2(34);
    BOOST_TEST(g.y2() == 34);

    g = z_qtshapes::ZQTri(31, 32, 33, 34, 50, 60, 90);
    g.setX3(35);
    BOOST_TEST(g.x3() == 35);

    g = z_qtshapes::ZQTri(31, 32, 33, 34, 35, 60, 90);
    g.setY3(36);
    BOOST_TEST(g.y3() == 36);

    g = z_qtshapes::ZQTri(31, 32, 33, 34, 35, 36, 90);
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
    BOOST_TEST(m.x3() == 13);
    BOOST_TEST(m.y3() == 14);
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

    z_qtshapes::ZQTri n(1, 2, 3, 4, 5, 6, 30);
    n.adjust(1, 1, 1, 1, 1, 1);
    BOOST_TEST(n.x1() == 2);
    BOOST_TEST(n.y1() == 3);
    BOOST_TEST(n.x2() == 4);
    BOOST_TEST(n.y2() == 5);
    BOOST_TEST(n.x3() == 6);
    BOOST_TEST(n.y3() == 7);

    n = z_qtshapes::ZQTri(2, 3, 4, 5, 6, 7, 30);
    n.adjust(QPoint(-1, -1), QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(n.x1() == 1);
    BOOST_TEST(n.y1() == 2);
    BOOST_TEST(n.x2() == 3);
    BOOST_TEST(n.y2() == 4);
    BOOST_TEST(n.x3() == 5);
    BOOST_TEST(n.y3() == 6);

    n = z_qtshapes::ZQTri(1, 2, 3, 4, 4, 5, 30);
    n.adjust(1, 1, 1, 1, 1, 1, 2);
    BOOST_TEST(n.x1() == 2);
    BOOST_TEST(n.y1() == 3);
    BOOST_TEST(n.x2() == 4);
    BOOST_TEST(n.y2() == 5);
    BOOST_TEST(n.x3() == 6);
    BOOST_TEST(n.y3() == 7);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQTri(2, 3, 4, 5, 6, 7, 32);
    n.adjust(QPoint(1, 1), QPoint(1, 1), QPoint(1, 1), 2);
    BOOST_TEST(n.x1() == 3);
    BOOST_TEST(n.y1() == 4);
    BOOST_TEST(n.x2() == 5);
    BOOST_TEST(n.y2() == 6);
    BOOST_TEST(n.x3() == 7);
    BOOST_TEST(n.y3() == 8);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQTri(3, 4, 5, 6, 7, 8, 34);
    n.adjustRadians(1, 1, 1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.x1() == 4);
    BOOST_TEST(n.y1() == 5);
    BOOST_TEST(n.x2() == 6);
    BOOST_TEST(n.y2() == 7);
    BOOST_TEST(n.x3() == 8);
    BOOST_TEST(n.y3() == 9);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQTri(4, 5, 6, 7, 8, 9, 124);
    n.adjustRadians(QPoint(1, 1), QPoint(1, 1), QPoint(1, 1), M_PI/2);
    BOOST_TEST(n.x1() == 5);
    BOOST_TEST(n.y1() == 6);
    BOOST_TEST(n.x2() == 7);
    BOOST_TEST(n.y2() == 8);
    BOOST_TEST(n.x3() == 9);
    BOOST_TEST(n.y3() == 10);
    BOOST_TEST(n.angle() == 214);

    l = z_qtshapes::ZQTri(1, 2, 3, 4, 5, 6, 20);
    z_qtshapes::ZQTri p = l.adjusted(1, 1, 1, 1, 1, 1);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.x3() == 6);
    BOOST_TEST(p.y3() == 7);

    p = l.adjusted(QPoint(-1, -1), QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(p.x1() == 0);
    BOOST_TEST(p.y1() == 1);
    BOOST_TEST(p.x2() == 2);
    BOOST_TEST(p.y2() == 3);
    BOOST_TEST(p.x3() == 2);
    BOOST_TEST(p.y3() == 3);

    p = l.adjusted(10, 10, 10, 10, 10, 10, 2);
    BOOST_TEST(p.x1() == 11);
    BOOST_TEST(p.y1() == 12);
    BOOST_TEST(p.x2() == 13);
    BOOST_TEST(p.y2() == 14);
    BOOST_TEST(p.x3() == 15);
    BOOST_TEST(p.y3() == 16);
    BOOST_TEST(p.angle() = 22);

    p = l.adjusted(QPoint(1, 1), QPoint(1, 1), QPoint(1, 1), 4);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.x3() == 6);
    BOOST_TEST(p.y3() == 7);
    BOOST_TEST(p.angle() = 24);

    p = l.adjustedRadians(QPoint(10, 10), QPoint(10, 10), QPoint(10, 10), M_PI/2);
    BOOST_TEST(p.x1() == 11);
    BOOST_TEST(p.y1() == 12);
    BOOST_TEST(p.x2() == 13);
    BOOST_TEST(p.y2() == 14);
    BOOST_TEST(p.x3() == 15);
    BOOST_TEST(p.y3() == 16);
    BOOST_TEST(p.angle() = 112);

    p = l.adjustedRadians(1, 1, 1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.x3() == 6);
    BOOST_TEST(p.y3() == 7);
    BOOST_TEST(p.angle() = 112);

    BOOST_TEST(l.toString() == QString("ZQTri(1,2 3,4 5,6 20 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPoint(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQTri q(1, 2, 3, 4, 5, 6, 30);
    z_qtshapes::ZQTri r(1, 2, 3, 4, 5, 6, 20);
    z_qtshapes::ZQTri s(1, 2, 3, 4, 5, 6, 20);
    if (r == s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (q != s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }


    z_qtshapes::ZQTri t(0, 0, 2, 0, 0, 1, 0);
    z_qtshapes::ZQTri u(0, 0, 1, 0, 0, 1, 0);
    z_qtshapes::ZQTri v(0, 0, 1, 0, 0, 2, 0);
    z_qtshapes::ZQTri w(0, 0, 2, 0, 0, 2, 0);
    BOOST_TEST(t.isAcute());
    BOOST_TEST(u.isRight());
    BOOST_TEST(v.isObtuse());
    BOOST_TEST(t.isIso());
    BOOST_TEST(w.isEquilateral());
    BOOST_TEST(v.isScalene());
}

BOOST_AUTO_TEST_CASE(Z_QTriF)
{
    z_qtshapes::ZQTriF a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTriF(QPointF(1,2), QPointF(3,4), QPointF(5,6));
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.x3() == 5);
    BOOST_TEST(a.y3() == 6);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTriF(QPointF(10,20), QPointF(30,40), QPointF(50,60), 10);
    BOOST_TEST(a.x1() == 10);
    BOOST_TEST(a.y1() == 20);
    BOOST_TEST(a.x2() == 30);
    BOOST_TEST(a.y2() == 40);
    BOOST_TEST(a.x3() == 50);
    BOOST_TEST(a.y3() == 60);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6);
    BOOST_TEST(a.x1() == 1);
    BOOST_TEST(a.y1() == 2);
    BOOST_TEST(a.x2() == 3);
    BOOST_TEST(a.y2() == 4);
    BOOST_TEST(a.x3() == 5);
    BOOST_TEST(a.y3() == 6);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 90);
    BOOST_TEST(a.x1() == 10);
    BOOST_TEST(a.y1() == 20);
    BOOST_TEST(a.x2() == 30);
    BOOST_TEST(a.y2() == 40);
    BOOST_TEST(a.x3() == 50);
    BOOST_TEST(a.y3() == 60);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQTriF g(-1, -2, -3, -4, -5, -6, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQTriF h = g.rotated(10);
    BOOST_TEST(h.x1() == -1);
    BOOST_TEST(h.y1() == -2);
    BOOST_TEST(h.x2() == -3);
    BOOST_TEST(h.y2() == -4);
    BOOST_TEST(h.x3() == -5);
    BOOST_TEST(h.y3() == -6);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQTriF i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x1() == -1);
    BOOST_TEST(i.y1() == -2);
    BOOST_TEST(i.x2() == -3);
    BOOST_TEST(i.y2() == -4);
    BOOST_TEST(i.x3() == -5);
    BOOST_TEST(i.y3() == -6);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQTriF(-1, -2, -3, -4, -5, -6, 10);
    g.setCoords(QPointF(10, 20), QPointF(30, 40), QPointF(50, 60));
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);

    g = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 10);
    g.setCoords(QPointF(1, 2), QPointF(3, 4), QPointF(5, 6), 30);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6, 30);
    g.setCoordsRadians(QPointF(10, 20), QPointF(30, 40), QPointF(50, 60), M_PI_2);
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);
    BOOST_TEST(g.angle() == 90);

    g = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 90);
    g.setCoords(1, 2, 3, 4, 5, 6);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);

    g = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6, 90);
    g.setCoords(10, 20, 30, 40, 50, 60, 30);
    BOOST_TEST(g.x1() == 10);
    BOOST_TEST(g.y1() == 20);
    BOOST_TEST(g.x2() == 30);
    BOOST_TEST(g.y2() == 40);
    BOOST_TEST(g.x3() == 50);
    BOOST_TEST(g.y3() == 60);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 30);
    g.setCoordsRadians(1, 2, 3, 4, 5, 6, M_PI_2);
    BOOST_TEST(g.x1() == 1);
    BOOST_TEST(g.y1() == 2);
    BOOST_TEST(g.x2() == 3);
    BOOST_TEST(g.y2() == 4);
    BOOST_TEST(g.x3() == 5);
    BOOST_TEST(g.y3() == 6);
    BOOST_TEST(g.angle() == 90);

    qreal a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0, g2 = 0, h2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2, &e2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);

    h.getCoords(&a2, &b2, &c2, &d2, &e2, &f2, &g2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);
    BOOST_TEST(g2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &e2, &f2, &h2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 3);
    BOOST_TEST(d2 == 4);
    BOOST_TEST(e2 == 5);
    BOOST_TEST(f2 == 6);
    BOOST_TEST(h2 == M_PI_2);

    g = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6, 90);
    g.setFirst(QPointF(10, 20));
    BOOST_TEST(g.first().x() == 10);
    BOOST_TEST(g.first().y() == 20);

    g = z_qtshapes::ZQTriF(10, 20, 3, 4, 5, 6, 90);
    g.setSecond(QPointF(30, 40));
    BOOST_TEST(g.second().x() == 30);
    BOOST_TEST(g.second().y() == 40);

    g = z_qtshapes::ZQTriF(10, 20, 30, 40, 5, 6, 90);
    g.setThird(QPointF(50, 60));
    BOOST_TEST(g.third().x() == 50);
    BOOST_TEST(g.third().y() == 60);

    g = z_qtshapes::ZQTriF(10, 20, 30, 40, 50, 60, 90);
    g.setX1(31);
    BOOST_TEST(g.x1() == 31);

    g = z_qtshapes::ZQTriF(31, 20, 30, 40, 50, 60, 90);
    g.setY1(32);
    BOOST_TEST(g.y1() == 32);

    g = z_qtshapes::ZQTriF(31, 32, 30, 40, 50, 60, 90);
    g.setX2(33);
    BOOST_TEST(g.x2() == 33);

    g = z_qtshapes::ZQTriF(31, 32, 33, 40, 50, 60, 90);
    g.setY2(34);
    BOOST_TEST(g.y2() == 34);

    g = z_qtshapes::ZQTriF(31, 32, 33, 34, 50, 60, 90);
    g.setX3(35);
    BOOST_TEST(g.x3() == 35);

    g = z_qtshapes::ZQTriF(31, 32, 33, 34, 35, 60, 90);
    g.setY3(36);
    BOOST_TEST(g.y3() == 36);

    g = z_qtshapes::ZQTriF(31, 32, 33, 34, 35, 36, 90);
    g.translate(1, 1);
    BOOST_TEST(g.x1() == 32);
    BOOST_TEST(g.y1() == 33);
    BOOST_TEST(g.x2() == 34);
    BOOST_TEST(g.y2() == 35);
    BOOST_TEST(g.x3() == 36);
    BOOST_TEST(g.y3() == 37);

    g = z_qtshapes::ZQTriF(32, 33, 34, 35, 36, 37, 90);
    g.translate(QPoint(-1, -1));
    BOOST_TEST(g.x1() == 31);
    BOOST_TEST(g.y1() == 32);
    BOOST_TEST(g.x2() == 33);
    BOOST_TEST(g.y2() == 34);
    BOOST_TEST(g.x3() == 35);
    BOOST_TEST(g.y3() == 36);

    g = z_qtshapes::ZQTriF(31, 32, 33, 34, 35, 36, 90);
    g.translate(1, 1, 2);
    BOOST_TEST(g.x1() == 32);
    BOOST_TEST(g.y1() == 33);
    BOOST_TEST(g.x2() == 34);
    BOOST_TEST(g.y2() == 35);
    BOOST_TEST(g.x3() == 36);
    BOOST_TEST(g.y3() == 37);
    BOOST_TEST(g.angle() == 92);

    g = z_qtshapes::ZQTriF(32, 33, 34, 35, 36, 37, 92);
    g.translate(QPointF(1, 1), 2);
    BOOST_TEST(g.x1() == 33);
    BOOST_TEST(g.y1() == 34);
    BOOST_TEST(g.x2() == 35);
    BOOST_TEST(g.y2() == 36);
    BOOST_TEST(g.x3() == 37);
    BOOST_TEST(g.y3() == 38);
    BOOST_TEST(g.angle() == 94);

    g = z_qtshapes::ZQTriF(33, 34, 35, 36, 37, 38, 94);
    g.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(g.x1() == 34);
    BOOST_TEST(g.y1() == 35);
    BOOST_TEST(g.x2() == 36);
    BOOST_TEST(g.y2() == 37);
    BOOST_TEST(g.x3() == 38);
    BOOST_TEST(g.y3() == 39);
    BOOST_TEST(g.angle() == 184);

    g = z_qtshapes::ZQTriF(34, 35, 36, 37, 38, 39, 184);
    g.translateRadians(QPointF(1, 1), M_PI/2);
    BOOST_TEST(g.x1() == 35);
    BOOST_TEST(g.y1() == 36);
    BOOST_TEST(g.x2() == 37);
    BOOST_TEST(g.y2() == 38);
    BOOST_TEST(g.x3() == 39);
    BOOST_TEST(g.y3() == 40);
    BOOST_TEST(g.angle() == 274);

    z_qtshapes::ZQTriF l(1, 2, 3, 4, 5, 6, 20);
    z_qtshapes::ZQTriF m = l.translated(1, 1);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.x3() == 6);
    BOOST_TEST(m.y3() == 7);
    m = l.translated(QPointF(-1, -1));
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
    BOOST_TEST(m.x3() == 13);
    BOOST_TEST(m.y3() == 14);
    BOOST_TEST(m.angle() = 22);
    m = l.translated(QPointF(1, 1), 4);
    BOOST_TEST(m.x1() == 2);
    BOOST_TEST(m.y1() == 3);
    BOOST_TEST(m.x2() == 4);
    BOOST_TEST(m.y2() == 5);
    BOOST_TEST(m.x3() == 6);
    BOOST_TEST(m.y3() == 7);
    BOOST_TEST(m.angle() = 24);
    m = l.translatedRadians(QPointF(10, 10), M_PI/2);
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

    z_qtshapes::ZQTriF n(1, 2, 3, 4, 5, 6, 30);
    n.adjust(1, 1, 1, 1, 1, 1);
    BOOST_TEST(n.x1() == 2);
    BOOST_TEST(n.y1() == 3);
    BOOST_TEST(n.x2() == 4);
    BOOST_TEST(n.y2() == 5);
    BOOST_TEST(n.x3() == 6);
    BOOST_TEST(n.y3() == 7);

    n = z_qtshapes::ZQTriF(2, 3, 4, 5, 6, 7, 30);
    n.adjust(QPointF(-1, -1), QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(n.x1() == 1);
    BOOST_TEST(n.y1() == 2);
    BOOST_TEST(n.x2() == 3);
    BOOST_TEST(n.y2() == 4);
    BOOST_TEST(n.x3() == 5);
    BOOST_TEST(n.y3() == 6);

    n = z_qtshapes::ZQTriF(1, 2, 3, 4, 4, 5, 30);
    n.adjust(1, 1, 1, 1, 1, 1, 2);
    BOOST_TEST(n.x1() == 2);
    BOOST_TEST(n.y1() == 3);
    BOOST_TEST(n.x2() == 4);
    BOOST_TEST(n.y2() == 5);
    BOOST_TEST(n.x3() == 6);
    BOOST_TEST(n.y3() == 7);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQTriF(2, 3, 4, 5, 6, 7, 32);
    n.adjust(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1), 2);
    BOOST_TEST(n.x1() == 3);
    BOOST_TEST(n.y1() == 4);
    BOOST_TEST(n.x2() == 5);
    BOOST_TEST(n.y2() == 6);
    BOOST_TEST(n.x3() == 7);
    BOOST_TEST(n.y3() == 8);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQTriF(3, 4, 5, 6, 7, 8, 34);
    n.adjustRadians(1, 1, 1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.x1() == 4);
    BOOST_TEST(n.y1() == 5);
    BOOST_TEST(n.x2() == 6);
    BOOST_TEST(n.y2() == 7);
    BOOST_TEST(n.x3() == 8);
    BOOST_TEST(n.y3() == 9);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQTriF(4, 5, 6, 7, 8, 9, 124);
    n.adjustRadians(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1), M_PI/2);
    BOOST_TEST(n.x1() == 5);
    BOOST_TEST(n.y1() == 6);
    BOOST_TEST(n.x2() == 7);
    BOOST_TEST(n.y2() == 8);
    BOOST_TEST(n.x3() == 9);
    BOOST_TEST(n.y3() == 10);
    BOOST_TEST(n.angle() == 214);

    l = z_qtshapes::ZQTriF(1, 2, 3, 4, 5, 6, 20);
    z_qtshapes::ZQTriF p = l.adjusted(1, 1, 1, 1, 1, 1);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.x3() == 6);
    BOOST_TEST(p.y3() == 7);

    p = l.adjusted(QPointF(-1, -1), QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(p.x1() == 0);
    BOOST_TEST(p.y1() == 1);
    BOOST_TEST(p.x2() == 2);
    BOOST_TEST(p.y2() == 3);
    BOOST_TEST(p.x3() == 2);
    BOOST_TEST(p.y3() == 3);

    p = l.adjusted(10, 10, 10, 10, 10, 10, 2);
    BOOST_TEST(p.x1() == 11);
    BOOST_TEST(p.y1() == 12);
    BOOST_TEST(p.x2() == 13);
    BOOST_TEST(p.y2() == 14);
    BOOST_TEST(p.x3() == 15);
    BOOST_TEST(p.y3() == 16);
    BOOST_TEST(p.angle() = 22);

    p = l.adjusted(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1), 4);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.x3() == 6);
    BOOST_TEST(p.y3() == 7);
    BOOST_TEST(p.angle() = 24);

    p = l.adjustedRadians(QPointF(10, 10), QPointF(10, 10), QPointF(10, 10), M_PI/2);
    BOOST_TEST(p.x1() == 11);
    BOOST_TEST(p.y1() == 12);
    BOOST_TEST(p.x2() == 13);
    BOOST_TEST(p.y2() == 14);
    BOOST_TEST(p.x3() == 15);
    BOOST_TEST(p.y3() == 16);
    BOOST_TEST(p.angle() = 112);

    p = l.adjustedRadians(1, 1, 1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.x1() == 2);
    BOOST_TEST(p.y1() == 3);
    BOOST_TEST(p.x2() == 4);
    BOOST_TEST(p.y2() == 5);
    BOOST_TEST(p.x3() == 6);
    BOOST_TEST(p.y3() == 7);
    BOOST_TEST(p.angle() = 112);

    BOOST_TEST(l.toString() == QString("ZQTriF(1,2 3,4 5,6 20 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPoint(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQTriF q(1, 2, 3, 4, 5, 6, 30);
    z_qtshapes::ZQTriF r(1, 2, 3, 4, 5, 6, 20);
    z_qtshapes::ZQTriF s(1, 2, 3, 4, 5, 6, 20);
    if (r == s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (q != s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }


    z_qtshapes::ZQTriF t(0, 0, 2, 0, 0, 1, 0);
    z_qtshapes::ZQTriF u(0, 0, 1, 0, 0, 1, 0);
    z_qtshapes::ZQTriF v(0, 0, 1, 0, 0, 2, 0);
    z_qtshapes::ZQTriF w(0, 0, 2, 0, 0, 2, 0);
    BOOST_TEST(t.isAcute());
    BOOST_TEST(u.isRight());
    BOOST_TEST(v.isObtuse());
    BOOST_TEST(t.isIso());
    BOOST_TEST(w.isEquilateral());
    BOOST_TEST(v.isScalene());
}

BOOST_AUTO_TEST_CASE(Z_QRect)
{
    z_qtshapes::ZQRect a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQRect(QPoint(1,2), QPoint(3,4));
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQRect(QPoint(10,20), QPoint(30,40), 10);
    BOOST_TEST(a.x() == 10);
    BOOST_TEST(a.y() == 20);
    BOOST_TEST(a.width() == 30);
    BOOST_TEST(a.height() == 40);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQRect(1, 2, 3, 4);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQRect(10, 20, 30, 40, 90);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQRect g(-1, -2, -3, -4, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQRect(-1, -2, -3, -4, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQRect h = g.rotated(10);
    BOOST_TEST(h.x() == -1);
    BOOST_TEST(h.y() == -2);
    BOOST_TEST(h.width() == -3);
    BOOST_TEST(h.height() == -4);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQRect i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x() == -1);
    BOOST_TEST(i.y() == -2);
    BOOST_TEST(i.width() == -3);
    BOOST_TEST(i.height() == -4);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQRect(-1, -2, -3, -4, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQRect(-1, -2, -3, -4, 10);
    g.setCoords(QPoint(10, 20), QPoint(30, 40));
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);

    g = z_qtshapes::ZQRect(10, 20, 30, 40, 10);
    g.setCoords(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQRect(1, 2, 3, 4, 30);
    g.setCoordsRadians(QPoint(10, 20), QPoint(30, 40), M_PI_2);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 90);

    g = z_qtshapes::ZQRect(10, 20, 30, 40, 90);
    g.setCoords(1, 2, 3, 4);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);

    g = z_qtshapes::ZQRect(1, 2, 3, 4, 90);
    g.setCoords(10, 20, 30, 40, 30);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQRect(10, 20, 30, 40, 30);
    g.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 90);

    int a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0;
    qreal f2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(f2 == M_PI_2);

    g = z_qtshapes::ZQRect(31, 32, 33, 34, 90);
    g.translate(1, 1);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);

    g = z_qtshapes::ZQRect(32, 33, 34, 35, 90);
    g.translate(QPoint(-1, -1));
    BOOST_TEST(g.px1() == 31);
    BOOST_TEST(g.py1() == 32);

    g = z_qtshapes::ZQRect(31, 32, 33, 34, 90);
    g.translate(1, 1, 2);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);
    BOOST_TEST(g.angle() == 92);

    g = z_qtshapes::ZQRect(32, 33, 34, 35, 92);
    g.translate(QPoint(1, 1), 2);
    BOOST_TEST(g.px1() == 33);
    BOOST_TEST(g.py1() == 34);
    BOOST_TEST(g.angle() == 94);

    g = z_qtshapes::ZQRect(33, 34, 35, 36, 94);
    g.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(g.px1() == 34);
    BOOST_TEST(g.py1() == 35);
    BOOST_TEST(g.angle() == 184);

    g = z_qtshapes::ZQRect(34, 35, 36, 37, 184);
    g.translateRadians(QPoint(1, 1), M_PI/2);
    BOOST_TEST(g.px1() == 35);
    BOOST_TEST(g.py1() == 36);
    BOOST_TEST(g.angle() == 274);

    z_qtshapes::ZQRect l(1, 2, 3, 4, 20);
    z_qtshapes::ZQRect m = l.translated(1, 1);
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

    z_qtshapes::ZQRect n(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);

    n = z_qtshapes::ZQRect(2, 3, 4, 5, 30);
    n.adjust(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(n.px1() == 1);
    BOOST_TEST(n.py1() == 2);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);

    n = z_qtshapes::ZQRect(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQRect(2, 3, 4, 5, 32);
    n.adjust(QPoint(1, 1), QPoint(1, 1), 2);
    BOOST_TEST(n.px1() == 3);
    BOOST_TEST(n.py1() == 4);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQRect(3, 4, 5, 6, 34);
    n.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.px1() == 4);
    BOOST_TEST(n.py1() == 5);
    BOOST_TEST(n.px2() == 5);
    BOOST_TEST(n.py2() == 6);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQRect(4, 5, 6, 7, 124);
    n.adjustRadians(QPoint(1, 1), QPoint(1, 1), M_PI/2);
    BOOST_TEST(n.px1() == 5);
    BOOST_TEST(n.py1() == 6);
    BOOST_TEST(n.px2() == 6);
    BOOST_TEST(n.py2() == 7);
    BOOST_TEST(n.angle() == 214);

    l = z_qtshapes::ZQRect(1, 2, 3, 4, 20);
    z_qtshapes::ZQRect p = l.adjusted(1, 1, 1, 1);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(p.px1() == 0);
    BOOST_TEST(p.py1() == 1);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(10, 10, 10, 10, 2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 22);

    p = l.adjusted(QPoint(1, 1), QPoint(1, 1), 4);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 24);

    p = l.adjustedRadians(QPoint(10, 10), QPoint(10, 10), M_PI/2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);

    p = l.adjustedRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);
    

    BOOST_TEST(g.toString() == QString("ZQRect(1,2 size 3x4 20 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPoint(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQRect q(1, 2, 3, 4, 30);
    z_qtshapes::ZQRect r(1, 2, 3, 4, 20);
    z_qtshapes::ZQRect s(1, 2, 3, 4, 20);
    if (r == s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (q != s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }


    QMargins ma(1,1,1,1);
    z_qtshapes::ZQRect ra;
    ra = l + ma;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = ma + l;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l - ma;
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsAdded(ma);
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsRemoved(ma);
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
}

BOOST_AUTO_TEST_CASE(Z_QRectF)
{
    z_qtshapes::ZQRectF a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQRectF(QPointF(1,2), QPointF(3,4));
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQRectF(QPointF(10,20), QPointF(30,40), 10);
    BOOST_TEST(a.x() == 10);
    BOOST_TEST(a.y() == 20);
    BOOST_TEST(a.width() == 30);
    BOOST_TEST(a.height() == 40);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQRectF(1, 2, 3, 4);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQRectF(10, 20, 30, 40, 90);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQRectF g(-1, -2, -3, -4, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQRectF(-1, -2, -3, -4, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQRectF h = g.rotated(10);
    BOOST_TEST(h.x() == -1);
    BOOST_TEST(h.y() == -2);
    BOOST_TEST(h.width() == -3);
    BOOST_TEST(h.height() == -4);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQRectF i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x() == -1);
    BOOST_TEST(i.y() == -2);
    BOOST_TEST(i.width() == -3);
    BOOST_TEST(i.height() == -4);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQRect(-1, -2, -3, -4, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQRectF(-1, -2, -3, -4, 10);
    g.setCoords(QPointF(10, 20), QPointF(30, 40));
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);

    g = z_qtshapes::ZQRectF(10, 20, 30, 40, 10);
    g.setCoords(QPointF(1, 2), QPointF(3, 4), 30);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQRectF(1, 2, 3, 4, 30);
    g.setCoordsRadians(QPointF(10, 20), QPointF(30, 40), M_PI_2);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 90);

    g = z_qtshapes::ZQRectF(10, 20, 30, 40, 90);
    g.setCoords(1, 2, 3, 4);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);

    g = z_qtshapes::ZQRectF(1, 2, 3, 4, 90);
    g.setCoords(10, 20, 30, 40, 30);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQRectF(10, 20, 30, 40, 30);
    g.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 90);

    qreal a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(f2 == M_PI_2);

    g = z_qtshapes::ZQRectF(31, 32, 33, 34, 90);
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

    z_qtshapes::ZQRectF l(1, 2, 3, 4, 20);
    z_qtshapes::ZQRectF m = l.translated(1, 1);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    m = l.translated(QPointF(-1, -1));
    BOOST_TEST(m.px1() == 0);
    BOOST_TEST(m.py1() == 1);
    m = l.translated(10,10,2);
    BOOST_TEST(m.px1() == 11);
    BOOST_TEST(m.py1() == 12);
    BOOST_TEST(m.angle() = 22);
    m = l.translated(QPointF(1, 1), 4);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    BOOST_TEST(m.angle() = 24);
    m = l.translatedRadians(QPointF(10, 10), M_PI/2);
    BOOST_TEST(m.px1() == 11);
    BOOST_TEST(m.py1() == 12);
    BOOST_TEST(m.angle() = 112);
    m = l.translatedRadians(1, 1, M_PI/2);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    BOOST_TEST(m.angle() = 112);

    z_qtshapes::ZQRectF n(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);

    n = z_qtshapes::ZQRectF(2, 3, 4, 5, 30);
    n.adjust(QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(n.px1() == 1);
    BOOST_TEST(n.py1() == 2);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);

    n = z_qtshapes::ZQRectF(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQRectF(2, 3, 4, 5, 32);
    n.adjust(QPointF(1, 1), QPointF(1, 1), 2);
    BOOST_TEST(n.px1() == 3);
    BOOST_TEST(n.py1() == 4);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQRectF(3, 4, 5, 6, 34);
    n.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.px1() == 4);
    BOOST_TEST(n.py1() == 5);
    BOOST_TEST(n.px2() == 5);
    BOOST_TEST(n.py2() == 6);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQRectF(4, 5, 6, 7, 124);
    n.adjustRadians(QPointF(1, 1), QPointF(1, 1), M_PI/2);
    BOOST_TEST(n.px1() == 5);
    BOOST_TEST(n.py1() == 6);
    BOOST_TEST(n.px2() == 6);
    BOOST_TEST(n.py2() == 7);
    BOOST_TEST(n.angle() == 214);

    l = z_qtshapes::ZQRectF(1, 2, 3, 4, 20);
    z_qtshapes::ZQRectF p = l.adjusted(1, 1, 1, 1);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(p.px1() == 0);
    BOOST_TEST(p.py1() == 1);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(10, 10, 10, 10, 2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 22);

    p = l.adjusted(QPointF(1, 1), QPointF(1, 1), 4);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 24);

    p = l.adjustedRadians(QPointF(10, 10), QPointF(10, 10), M_PI/2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);

    p = l.adjustedRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);

    BOOST_TEST(g.toString() == QString("ZQRectF(1,2 size 3x4 20 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPointF(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQRectF q(1, 2, 3, 4, 30);
    z_qtshapes::ZQRectF r(1, 2, 3, 4, 20);
    z_qtshapes::ZQRectF s(1, 2, 3, 4, 20);
    if (r == s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (q != s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    QMarginsF ma(1,1,1,1);
    z_qtshapes::ZQRectF ra;
    ra = l + ma;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = ma + l;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l - ma;
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsAdded(ma);
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsRemoved(ma);
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
}



BOOST_AUTO_TEST_CASE(Z_QEllipse)
{
    z_qtshapes::ZQEllipse a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipse(QPoint(1,2), QPoint(3,4));
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipse(QPoint(10,20), QPoint(30,40), 10);
    BOOST_TEST(a.x() == 10);
    BOOST_TEST(a.y() == 20);
    BOOST_TEST(a.width() == 30);
    BOOST_TEST(a.height() == 40);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQEllipse(1, 2, 3, 4);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipse(10, 20, 30, 40, 90);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQEllipse g(-1, -2, -3, -4, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQEllipse(-1, -2, -3, -4, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQEllipse h = g.rotated(10);
    BOOST_TEST(h.x() == -1);
    BOOST_TEST(h.y() == -2);
    BOOST_TEST(h.width() == -3);
    BOOST_TEST(h.height() == -4);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQEllipse i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x() == -1);
    BOOST_TEST(i.y() == -2);
    BOOST_TEST(i.width() == -3);
    BOOST_TEST(i.height() == -4);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQEllipse(-1, -2, -3, -4, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQEllipse(-1, -2, -3, -4, 10);
    g.setCoords(QPoint(10, 20), QPoint(30, 40));
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);

    g = z_qtshapes::ZQEllipse(10, 20, 30, 40, 10);
    g.setCoords(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQEllipse(1, 2, 3, 4, 30);
    g.setCoordsRadians(QPoint(10, 20), QPoint(30, 40), M_PI_2);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 90);

    g = z_qtshapes::ZQEllipse(10, 20, 30, 40, 90);
    g.setCoords(1, 2, 3, 4);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);

    g = z_qtshapes::ZQEllipse(1, 2, 3, 4, 90);
    g.setCoords(10, 20, 30, 40, 30);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQEllipse(10, 20, 30, 40, 30);
    g.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 90);

    int a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0;
    qreal f2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(f2 == M_PI_2);

    g = z_qtshapes::ZQEllipse(31, 32, 33, 34, 90);
    g.translate(1, 1);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);

    g = z_qtshapes::ZQEllipse(32, 33, 34, 35, 90);
    g.translate(QPoint(-1, -1));
    BOOST_TEST(g.px1() == 31);
    BOOST_TEST(g.py1() == 32);

    g = z_qtshapes::ZQEllipse(31, 32, 33, 34, 90);
    g.translate(1, 1, 2);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);
    BOOST_TEST(g.angle() == 92);

    g = z_qtshapes::ZQEllipse(32, 33, 34, 35, 92);
    g.translate(QPoint(1, 1), 2);
    BOOST_TEST(g.px1() == 33);
    BOOST_TEST(g.py1() == 34);
    BOOST_TEST(g.angle() == 94);

    g = z_qtshapes::ZQEllipse(33, 34, 35, 36, 94);
    g.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(g.px1() == 34);
    BOOST_TEST(g.py1() == 35);
    BOOST_TEST(g.angle() == 184);

    g = z_qtshapes::ZQEllipse(34, 35, 36, 37, 184);
    g.translateRadians(QPoint(1, 1), M_PI/2);
    BOOST_TEST(g.px1() == 35);
    BOOST_TEST(g.py1() == 36);
    BOOST_TEST(g.angle() == 274);

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

    z_qtshapes::ZQEllipse n(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);

    n = z_qtshapes::ZQEllipse(2, 3, 4, 5, 30);
    n.adjust(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(n.px1() == 1);
    BOOST_TEST(n.py1() == 2);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);

    n = z_qtshapes::ZQEllipse(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQEllipse(2, 3, 4, 5, 32);
    n.adjust(QPoint(1, 1), QPoint(1, 1), 2);
    BOOST_TEST(n.px1() == 3);
    BOOST_TEST(n.py1() == 4);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQEllipse(3, 4, 5, 6, 34);
    n.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.px1() == 4);
    BOOST_TEST(n.py1() == 5);
    BOOST_TEST(n.px2() == 5);
    BOOST_TEST(n.py2() == 6);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQEllipse(4, 5, 6, 7, 124);
    n.adjustRadians(QPoint(1, 1), QPoint(1, 1), M_PI/2);
    BOOST_TEST(n.px1() == 5);
    BOOST_TEST(n.py1() == 6);
    BOOST_TEST(n.px2() == 6);
    BOOST_TEST(n.py2() == 7);
    BOOST_TEST(n.angle() == 214);

    l = z_qtshapes::ZQEllipse(1, 2, 3, 4, 20);
    z_qtshapes::ZQEllipse p = l.adjusted(1, 1, 1, 1);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(QPoint(-1, -1), QPoint(-1, -1));
    BOOST_TEST(p.px1() == 0);
    BOOST_TEST(p.py1() == 1);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(10, 10, 10, 10, 2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 22);

    p = l.adjusted(QPoint(1, 1), QPoint(1, 1), 4);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 24);

    p = l.adjustedRadians(QPoint(10, 10), QPoint(10, 10), M_PI/2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);

    p = l.adjustedRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);

    BOOST_TEST(g.toString() == QString("ZQEllipse(1,2 size 3x4 20 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPoint(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQEllipse q(1, 2, 3, 4, 30);
    z_qtshapes::ZQEllipse r(1, 2, 3, 4, 20);
    z_qtshapes::ZQEllipse s(1, 2, 3, 4, 20);
    if (r == s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (q != s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    QMargins ma(1,1,1,1);
    z_qtshapes::ZQEllipse ra;
    ra = l + ma;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = ma + l;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l - ma;
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsAdded(ma);
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsRemoved(ma);
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
}

BOOST_AUTO_TEST_CASE(Z_QEllipseF)
{
    z_qtshapes::ZQEllipseF a;
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipseF(QPointF(1,2), QPointF(3,4));
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipseF(QPointF(10,20), QPointF(30,40), 10);
    BOOST_TEST(a.x() == 10);
    BOOST_TEST(a.y() == 20);
    BOOST_TEST(a.width() == 30);
    BOOST_TEST(a.height() == 40);
    BOOST_TEST(a.angle() == 10);

    a = z_qtshapes::ZQEllipseF(1, 2, 3, 4);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 0);

    a = z_qtshapes::ZQEllipseF(10, 20, 30, 40, 90);
    BOOST_TEST(a.x() == 1);
    BOOST_TEST(a.y() == 2);
    BOOST_TEST(a.width() == 3);
    BOOST_TEST(a.height() == 4);
    BOOST_TEST(a.angle() == 90);
    BOOST_TEST(a.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQEllipseF g(-1, -2, -3, -4, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);

    g = z_qtshapes::ZQEllipseF(-1, -2, -3, -4, 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQEllipseF h = g.rotated(10);
    BOOST_TEST(h.x() == -1);
    BOOST_TEST(h.y() == -2);
    BOOST_TEST(h.width() == -3);
    BOOST_TEST(h.height() == -4);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQEllipseF i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.x() == -1);
    BOOST_TEST(i.y() == -2);
    BOOST_TEST(i.width() == -3);
    BOOST_TEST(i.height() == -4);
    BOOST_TEST(i.angle() == 200);

    g = z_qtshapes::ZQEllipseF(-1, -2, -3, -4, 200);
    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);

    g = z_qtshapes::ZQEllipseF(-1, -2, -3, -4, 10);
    g.setCoords(QPointF(10, 20), QPointF(30, 40));
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);

    g = z_qtshapes::ZQEllipseF(10, 20, 30, 40, 10);
    g.setCoords(QPointF(1, 2), QPointF(3, 4), 30);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQEllipseF(1, 2, 3, 4, 30);
    g.setCoordsRadians(QPointF(10, 20), QPointF(30, 40), M_PI_2);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 90);

    g = z_qtshapes::ZQEllipseF(10, 20, 30, 40, 90);
    g.setCoords(1, 2, 3, 4);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);

    g = z_qtshapes::ZQEllipseF(1, 2, 3, 4, 90);
    g.setCoords(10, 20, 30, 40, 30);
    BOOST_TEST(g.px1() == 10);
    BOOST_TEST(g.py1() == 20);
    BOOST_TEST(g.px2() == 10+30);
    BOOST_TEST(g.py2() == 20+40);
    BOOST_TEST(g.angle() == 30);

    g = z_qtshapes::ZQEllipseF(10, 20, 30, 40, 30);
    g.setCoordsRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(g.px1() == 1);
    BOOST_TEST(g.py1() == 2);
    BOOST_TEST(g.px2() == 1+3);
    BOOST_TEST(g.py2() == 2+4);
    BOOST_TEST(g.angle() == 90);

    qreal a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

    h.getCoords(&a2, &b2, &c2, &d2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);

    h.getCoords(&a2, &b2, &c2, &d2, &e2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(e2 == 90);

    h.getCoordsRadians(&a2, &b2, &c2, &d2, &f2);
    BOOST_TEST(a2 == 1);
    BOOST_TEST(b2 == 2);
    BOOST_TEST(c2 == 1+3);
    BOOST_TEST(d2 == 2+4);
    BOOST_TEST(f2 == M_PI_2);

    g = z_qtshapes::ZQEllipseF(31, 32, 33, 34, 90);
    g.translate(1, 1);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);

    g = z_qtshapes::ZQEllipseF(32, 33, 34, 35, 90);
    g.translate(QPoint(-1, -1));
    BOOST_TEST(g.px1() == 31);
    BOOST_TEST(g.py1() == 32);

    g = z_qtshapes::ZQEllipseF(31, 32, 33, 34, 90);
    g.translate(1, 1, 2);
    BOOST_TEST(g.px1() == 32);
    BOOST_TEST(g.py1() == 33);
    BOOST_TEST(g.angle() == 92);

    g = z_qtshapes::ZQEllipseF(32, 33, 34, 35, 92);
    g.translate(QPoint(1, 1), 2);
    BOOST_TEST(g.px1() == 33);
    BOOST_TEST(g.py1() == 34);
    BOOST_TEST(g.angle() == 94);

    g = z_qtshapes::ZQEllipseF(33, 34, 35, 36, 94);
    g.translateRadians(1, 1, M_PI/2);
    BOOST_TEST(g.px1() == 34);
    BOOST_TEST(g.py1() == 35);
    BOOST_TEST(g.angle() == 184);

    g = z_qtshapes::ZQEllipseF(34, 35, 36, 37, 184);
    g.translateRadians(QPointF(1, 1), M_PI/2);
    BOOST_TEST(g.px1() == 35);
    BOOST_TEST(g.py1() == 36);
    BOOST_TEST(g.angle() == 274);

    z_qtshapes::ZQEllipseF l(1, 2, 3, 4, 20);
    z_qtshapes::ZQEllipseF m = l.translated(1, 1);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    m = l.translated(QPointF(-1, -1));
    BOOST_TEST(m.px1() == 0);
    BOOST_TEST(m.py1() == 1);
    m = l.translated(10,10,2);
    BOOST_TEST(m.px1() == 11);
    BOOST_TEST(m.py1() == 12);
    BOOST_TEST(m.angle() = 22);
    m = l.translated(QPointF(1, 1), 4);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    BOOST_TEST(m.angle() = 24);
    m = l.translatedRadians(QPointF(10, 10), M_PI/2);
    BOOST_TEST(m.px1() == 11);
    BOOST_TEST(m.py1() == 12);
    BOOST_TEST(m.angle() = 112);
    m = l.translatedRadians(1, 1, M_PI/2);
    BOOST_TEST(m.px1() == 2);
    BOOST_TEST(m.py1() == 3);
    BOOST_TEST(m.angle() = 112);

    z_qtshapes::ZQEllipseF n(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);

    n = z_qtshapes::ZQEllipseF(2, 3, 4, 5, 30);
    n.adjust(QPoint(-1, -1), QPointF(-1, -1));
    BOOST_TEST(n.px1() == 1);
    BOOST_TEST(n.py1() == 2);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);

    n = z_qtshapes::ZQEllipseF(1, 2, 3, 4, 30);
    n.adjust(1, 1, 1, 1, 2);
    BOOST_TEST(n.px1() == 2);
    BOOST_TEST(n.py1() == 3);
    BOOST_TEST(n.px2() == 3);
    BOOST_TEST(n.py2() == 4);
    BOOST_TEST(n.angle() == 32);

    n = z_qtshapes::ZQEllipseF(2, 3, 4, 5, 32);
    n.adjust(QPoint(1, 1), QPointF(1, 1), 2);
    BOOST_TEST(n.px1() == 3);
    BOOST_TEST(n.py1() == 4);
    BOOST_TEST(n.px2() == 4);
    BOOST_TEST(n.py2() == 5);
    BOOST_TEST(n.angle() == 34);

    n = z_qtshapes::ZQEllipseF(3, 4, 5, 6, 34);
    n.adjustRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(n.px1() == 4);
    BOOST_TEST(n.py1() == 5);
    BOOST_TEST(n.px2() == 5);
    BOOST_TEST(n.py2() == 6);
    BOOST_TEST(n.angle() == 124);

    n = z_qtshapes::ZQEllipseF(4, 5, 6, 7, 124);
    n.adjustRadians(QPointF(1, 1), QPointF(1, 1), M_PI/2);
    BOOST_TEST(n.px1() == 5);
    BOOST_TEST(n.py1() == 6);
    BOOST_TEST(n.px2() == 6);
    BOOST_TEST(n.py2() == 7);
    BOOST_TEST(n.angle() == 214);

    l = z_qtshapes::ZQEllipseF(1, 2, 3, 4, 20);
    z_qtshapes::ZQEllipseF p = l.adjusted(1, 1, 1, 1);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(QPointF(-1, -1), QPointF(-1, -1));
    BOOST_TEST(p.px1() == 0);
    BOOST_TEST(p.py1() == 1);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);

    p = l.adjusted(10, 10, 10, 10, 2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 22);

    p = l.adjusted(QPointF(1, 1), QPointF(1, 1), 4);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 24);

    p = l.adjustedRadians(QPointF(10, 10), QPointF(10, 10), M_PI/2);
    BOOST_TEST(p.px1() == 11);
    BOOST_TEST(p.py1() == 12);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);

    p = l.adjustedRadians(1, 1, 1, 1, M_PI/2);
    BOOST_TEST(p.px1() == 2);
    BOOST_TEST(p.py1() == 3);
    BOOST_TEST(p.px2() == 3);
    BOOST_TEST(p.py2() == 4);
    BOOST_TEST(p.angle() = 112);

    BOOST_TEST(g.toString() == QString("ZQEllipseF(1,2 size 3x4 20 degrees)"));
    
    QMatrix4x4 world4;
    world4.setToIdentity();
    world4.rotate(45, 1, 0, 0);
    world4.rotate(45, 0, 1, 0);
    world4.rotate(45, 0, 0, 1);
    QMatrix3x3 world3 = world4.normalMatrix();
    g.toPath();
    g.toPath(world3, QPointF(1,1));
    g.contains(h);
    g.contains(QPointF(1,1));
    g.intersects(h);
    g.united(h);
    g.intersected(h);

    z_qtshapes::ZQEllipseF q(1, 2, 3, 4, 30);
    z_qtshapes::ZQEllipseF r(1, 2, 3, 4, 20);
    z_qtshapes::ZQEllipseF s(1, 2, 3, 4, 20);
    if (r == s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    if (q != s) {
        BOOST_TEST(true);
    }
    else {
        BOOST_TEST(false);
    }

    QMarginsF ma(1,1,1,1);
    z_qtshapes::ZQEllipseF ra;
    ra = l + ma;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = ma + l;
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l - ma;
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsAdded(ma);
    BOOST_TEST(ra.px1() == 2);
    BOOST_TEST(ra.py1() == 3);
    BOOST_TEST(ra.px2() == 4);
    BOOST_TEST(ra.py2() == 5);
    BOOST_TEST(ra.angle() == 20);
    ra = l.marginsRemoved(ma);
    BOOST_TEST(ra.px1() == 0);
    BOOST_TEST(ra.py1() == 1);
    BOOST_TEST(ra.px2() == 2);
    BOOST_TEST(ra.py2() == 3);
    BOOST_TEST(ra.angle() == 20);
}
