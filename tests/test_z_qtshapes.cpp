#define BOOST_TEST_MODULE Z_QTShapes
#include <boost/test/included/unit_test.hpp>

#include "z_qpoint.h"
#include "z_qline.h"
#include "z_qtri.h"
#include "z_qrect.h"
#include "z_qellipse.h"

// Some test cases may be removed on the assumption that the corresponding classes
// and methods are "grandfathered", not changed after they are published.

// ZQPoint/ZQPointF were hardly modified from the original
BOOST_AUTO_TEST_CASE(Z_QPoint)
{
    z_qtshapes::ZQPoint p(2,3);
    BOOST_TEST(p.toString() == QString("ZQPoint(2,3)");
    BOOST_TEST(p.toQPoint() == QPoint(2,3));
}

BOOST_AUTO_TEST_CASE(Z_QPointF)
{
    z_qtshapes::ZQPointF p(2.1,3.1);
    BOOST_TEST(p.toString() == QString("ZQPointF(2.1,3.1)");
    BOOST_TEST(p.toQPoint() == QPointF(2.1,3.1));
}

// Intersections, unions, and containment functions are impossible to test
// without drawing them on the screen because they use QPainterPath.

BOOST_AUTO_TEST_CASE(Z_QLine)
{
    z_qtshapes::ZQLine a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQLine b(QPoint(1,2), QPoint(3,4));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQLine c(QPoint(1,2), QPoint(3,4), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQLine d(QPoint(1,2), QPoint(3,4), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQLine e(1, 2, 3, 4);
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQLine f(1, 2, 3, 4, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQLine g = z_qtshapes::ZQLine::fromPolar(2, 90);
    BOOST_TEST(g.x2() == 0);
    BOOST_TEST(g.y2() == -2);

    z_qtshapes::ZQLine h(0, 0, 0, 0, 10);
    h.rotate(10);
    BOOST_TEST(h.angle() == 20);
    h.rotateRadians(M_PI_2);
    BOOST_TEST(h.angle() == 110);
    z_qtshapes::ZQLine i = h.rotated(10);
    BOOST_TEST(i.angle() == 120);
    z_qtshapes::ZQLine j = h.rotatedRadians(M_PI_2);
    BOOST_TEST(j.angle() == 200);

    h.setAngle(10);
    BOOST_TEST(h.angle() == 10);
    h.setAngle(5760);
    BOOST_TEST(h.angle() == 0);

    h.setPoints(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(h.angle() == 30);

    h.setPointsRadians(QPoint(1, 2), QPoint(3, 4), M_PI_2);
    BOOST_TEST(h.angle() == 90);

    h.setLine(1, 2, 3, 4, 30);
    BOOST_TEST(h.angle() == 30);

    h.setLineRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(h.angle() == 90);

    BOOST_TEST(h.toString() == QString("ZQLine(1,2 to 3,4 90 degrees)");
    
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
    BOOST_TEST(h == k);
    BOOST_TEST(h != l);

}

BOOST_AUTO_TEST_CASE(Z_QLineF)
{
    z_qtshapes::ZQLineF a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQLineF b(QPointF(1,2), QPointF(3,4));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQLineF c(QPoint(1,2), QPointF(3,4), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQLineF d(QPoint(1,2), QPointF(3,4), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQLineF e(1, 2, 3, 4);
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQLineF f(1, 2, 3, 4, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQLine g = z_qtshapes::ZQLine::fromPolar(2, 90);
    BOOST_TEST(g.x2() == 0);
    BOOST_TEST(g.y2() == -2);

    z_qtshapes::ZQLineF h(0, 0, 0, 0, 10);
    h.rotate(10);
    BOOST_TEST(h.angle() == 20);
    h.rotateRadians(M_PI_2);
    BOOST_TEST(h.angle() == 110);
    z_qtshapes::ZQLineF i = h.rotated(10);
    BOOST_TEST(i.angle() == 120);
    z_qtshapes::ZQLineF j = h.rotatedRadians(M_PI_2);
    BOOST_TEST(j.angle() == 200);

    h.setAngle(10);
    BOOST_TEST(h.angle() == 10);
    h.setAngle(5760);
    BOOST_TEST(h.angle() == 0);

    h.setPoints(QPointF(1, 2), QPointF(3, 4), 30);
    BOOST_TEST(h.angle() == 30);

    h.setPointsRadians(QPointF(1, 2), QPointF(3, 4), M_PI_2);
    BOOST_TEST(h.angle() == 90);

    h.setLine(1, 2, 3, 4, 30);
    BOOST_TEST(h.angle() == 30);

    h.setLineRadians(1, 2, 3, 4, M_PI_2);
    BOOST_TEST(h.angle() == 90);

    BOOST_TEST(h.toString() == QString("ZQLine(1,2 to 3,4 90 degrees)");
    
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
    BOOST_TEST(h == k);
    BOOST_TEST(h != l);

}

BOOST_AUTO_TEST_CASE(Z_QTri)
{
    z_qtshapes::ZQTri a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQTri b(QPoint(1,2), QPoint(3,4), QPoint(5,6));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQTri c(QPoint(1,2), QPoint(3,4), QPoint(5,6), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQTri d(QPoint(1,2), QPoint(3,4), QPoint(5,6), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQTri e(1, 2, 3, 4, 5, 6);
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQTri f(1, 2, 3, 4, 5, 6, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQTri g(0, 0, 0, 0, 0, 0, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQTri h = g.rotated(10);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQTri i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.angle() == 200);

    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);
    g.setAngle(5760);
    BOOST_TEST(g.angle() == 0);

    g.setPoints(QPoint(1, 2), QPoint(3, 4), QPoint(5, 6), 30);
    BOOST_TEST(g.angle() == 30);

    g.setPointsRadians(QPoint(1, 2), QPoint(3, 4), QPoint(5, 6), M_PI_2);
    BOOST_TEST(g.angle() == 90);

    g.setFirst(QPoint(10, 20));
    BOOST_TEST(g.first() == QPoint(10, 20));
    g.setSecond(QPoint(10, 20));
    BOOST_TEST(g.second() == QPoint(10, 20));
    g.setThird(QPoint(10, 20));
    BOOST_TEST(g.third() == QPoint(10, 20));
    g.setX1(30);
    BOOST_TEST(g.x1() == 30);
    g.setY1(30);
    BOOST_TEST(g.y1() == 30);
    g.setX2(30);
    BOOST_TEST(g.x2() == 30);
    g.setY2(30);
    BOOST_TEST(g.y2() == 30);
    g.setX3(30);
    BOOST_TEST(g.x3() == 30);
    g.setY3(30);
    BOOST_TEST(g.y3() == 30);

    g.setTri(1, 2, 3, 4, 5, 6, 30);
    BOOST_TEST(g.angle() == 30);

    g.setTriRadians(1, 2, 3, 4, 5, 6, M_PI_2);
    BOOST_TEST(g.angle() == 90);

    int a_a, a_b, a_c, a_d, a_e, a_f, a_g;
    g.getTri(&a_a, &a_b, &a_c, &a_d, &a_e, &a_f, &a_g);
    BOOST_TEST(a_g == 90);

    qreal a_h;
    g.getTri(&a_a, &a_b, &a_c, &a_d, &a_e, &a_f, &a_h);
    BOOST_TEST(a_h == M_PI_2);

    z_qtshapes::ZQTri g2 = g.adjusted(a_a, a_b, a_c, a_d, a_e, a_f, a_g);
    BOOST_TEST(g2.x1() == 2 && g2.y1() == 4 && g2.x2() == 6 && g2.y2() == 8
        && g2.x3() == 10 && g2.y3() 12 && g2.angle() == 180);

    BOOST_TEST(g.toString() == QString("ZQTri(1,2 3,4 5,6 90 degrees)");
    
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

    z_qtshapes::ZQTri j(1, 2, 3, 4, 5, 6, 30);
    z_qtshapes::ZQTri k(1, 2, 3, 4, 5, 6, 20);
    BOOST_TEST(g == j);
    BOOST_TEST(g != k);

    z_qtshapes::ZQTri l(0, 0, 2, 0, 0, 1, 0);
    z_qtshapes::ZQTri m(0, 0, 1, 0, 0, 1, 0);
    z_qtshapes::ZQTri n(0, 0, 1, 0, 0, 2, 0);
    z_qtshapes::ZQTri o(0, 0, 2, 0, 0, 2, 0);
    BOOST_TEST(l.isAcute());
    BOOST_TEST(m.isRight());
    BOOST_TEST(n.isObtuse());
    BOOST_TEST(l.isIso());
    BOOST_TEST(o.isEquilateral());
    BOOST_TEST(n.isScalene());
}

BOOST_AUTO_TEST_CASE(Z_QTriF)
{
    z_qtshapes::ZQTriF a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQTriF b(QPointF(1,2), QPointF(3,4), QPointF(5,6));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQTriF c(QPointF(1,2), QPointF(3,4), QPointF(5,6), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQTriF d(QPointF(1,2), QPointF(3,4), QPointF(5,6), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQTriF e(1, 2, 3, 4, 5, 6);
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQTriF f(1, 2, 3, 4, 5, 6, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQTriF g(0, 0, 0, 0, 0, 0, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQTriF h = g.rotated(10);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQTriF i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.angle() == 200);

    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);
    g.setAngle(5760);
    BOOST_TEST(g.angle() == 0);

    g.setPoints(QPointF(1, 2), QPointF(3, 4), QPointF(5, 6), 30);
    BOOST_TEST(g.angle() == 30);

    g.setPointsRadians(QPointF(1, 2), QPointF(3, 4), QPointF(5, 6), M_PI_2);
    BOOST_TEST(g.angle() == 90);

    g.setFirst(QPointF(10, 20));
    BOOST_TEST(g.first() == QPointF(10, 20));
    g.setSecond(QPointF(10, 20));
    BOOST_TEST(g.second() == QPointF(10, 20));
    g.setThird(QPointF(10, 20));
    BOOST_TEST(g.third() == QPointF(10, 20));
    g.setX1(30);
    BOOST_TEST(g.x1() == 30);
    g.setY1(30);
    BOOST_TEST(g.y1() == 30);
    g.setX2(30);
    BOOST_TEST(g.x2() == 30);
    g.setY2(30);
    BOOST_TEST(g.y2() == 30);
    g.setX3(30);
    BOOST_TEST(g.x3() == 30);
    g.setY3(30);
    BOOST_TEST(g.y3() == 30);

    g.setTri(1, 2, 3, 4, 5, 6, 30);
    BOOST_TEST(g.angle() == 30);

    g.setTriRadians(1, 2, 3, 4, 5, 6, M_PI_2);
    BOOST_TEST(g.angle() == 90);

    qreal a_a, a_b, a_c, a_d, a_e, a_f, a_g;
    g.getTri(&a_a, &a_b, &a_c, &a_d, &a_e, &a_f, &a_g);
    BOOST_TEST(a_g == 90);

    qreal a_h;
    g.getTri(&a_a, &a_b, &a_c, &a_d, &a_e, &a_f, &a_h);
    BOOST_TEST(a_h == M_PI_2);

    z_qtshapes::ZQTriF g2 = g.adjusted(a_a, a_b, a_c, a_d, a_e, a_f, a_g);
    BOOST_TEST(g2.x1() == 2 && g2.y1() == 4 && g2.x2() == 6 && g2.y2() == 8
        && g2.x3() == 10 && g2.y3() 12 && g2.angle() == 180);

    BOOST_TEST(g.toString() == QString("ZQTriF(1,2 3,4 5,6 90 degrees)");
    
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

    z_qtshapes::ZQTriF j(1, 2, 3, 4, 5, 6, 30);
    z_qtshapes::ZQTriF k(1, 2, 3, 4, 5, 6, 20);
    BOOST_TEST(g == j);
    BOOST_TEST(g != k);

    z_qtshapes::ZQTriF l(0, 0, 2, 0, 0, 1, 0);
    z_qtshapes::ZQTriF m(0, 0, 1, 0, 0, 1, 0);
    z_qtshapes::ZQTriF n(0, 0, 1, 0, 0, 2, 0);
    z_qtshapes::ZQTriF o(0, 0, 2, 0, 0, 2, 0);
    BOOST_TEST(l.isAcute());
    BOOST_TEST(m.isRight());
    BOOST_TEST(n.isObtuse());
    BOOST_TEST(l.isIso());
    BOOST_TEST(o.isEquilateral());
    BOOST_TEST(n.isScalene());
}

BOOST_AUTO_TEST_CASE(Z_QRect)
{
    z_qtshapes::ZQRect a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQRect b(QPoint(1,2), QPoint(3,4));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQRect c(QPoint(1,2), QPoint(3,4), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQRect d(QPoint(1,2), QPoint(3,4), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQRect e(1, 2, 3, 4;
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQRect f(1, 2, 3, 4, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQRect g(0, 0, 0, 0, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQRect h = g.rotated(10);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQRect i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.angle() == 200);

    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);
    g.setAngle(5760);
    BOOST_TEST(g.angle() == 0);

    g.setPoints(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(g.angle() == 30);

    g.setPointsRadians(QPoint(1, 2), QPoint(3, 4), M_PI_2);
    BOOST_TEST(g.angle() == 90);

    g.setTopLeft(QPoint(10, 20));
    BOOST_TEST(g.topLeft() == QPoint(10, 20));
    g.setTopRight(QPoint(10, 20));
    BOOST_TEST(g.topRight() == QPoint(10, 20));
    g.setBottomLeft(QPoint(10, 20));
    BOOST_TEST(g.bottomLeft() == QPoint(10, 20));
    g.setBottomRight(QPoint(10, 20));
    BOOST_TEST(g.bottomRight() == QPoint(10, 20));
    g.setLeft(30);
    BOOST_TEST(g.left() == 30);
    g.setTop(30);
    BOOST_TEST(g.top() == 30);
    g.setRight(30);
    BOOST_TEST(g.right() == 30);
    g.setBottom(30);
    BOOST_TEST(g.bottom() == 30);
    g.setX(40);
    BOOST_TEST(g.x() == 40);
    g.setY(40);
    BOOST_TEST(g.y() == 40);
    g.setWidth(40);
    BOOST_TEST(g.width() == 40);
    g.setHeight(40);
    BOOST_TEST(g.height() == 40);

    g.setRect(1, 2, 3, 4, 30);
    BOOST_TEST(g.angle() == 30);

    g.setRectRadians(1, 2, 3, 4 M_PI_2);
    BOOST_TEST(g.angle() == 90);

    int a_a, a_b, a_c, a_d, a_g;
    g.getRect(&a_a, &a_b, &a_c, &a_d, &a_g);
    BOOST_TEST(a_g == 90);

    qreal a_h;
    g.getRectRadians(&a_a, &a_b, &a_c, &a_d, &a_h);
    BOOST_TEST(a_h == M_PI_2);

    z_qtshapes::ZQRect g2 = g.adjusted(a_a, a_b, a_c, a_d, a_g);
    BOOST_TEST(g2.angle() == 180);

    BOOST_TEST(g.toString() == QString("ZQRect(1,2 size 3x4 90 degrees)");
    
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

    z_qtshapes::ZQRect j(1, 2, 3, 4, 30);
    z_qtshapes::ZQRect k(1, 2, 3, 4, 20);
    BOOST_TEST(g == j);
    BOOST_TEST(g != k);
}

BOOST_AUTO_TEST_CASE(Z_QRectF)
{
    z_qtshapes::ZQRectF a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQRectF b(QPointF(1,2), QPointF(3,4));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQRectF c(QPointF(1,2), QPointF(3,4), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQRectF d(QPointF(1,2), QPointF(3,4), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQRectF e(1, 2, 3, 4;
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQRectF f(1, 2, 3, 4, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQRectF g(0, 0, 0, 0, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQRectF h = g.rotated(10);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQRectF i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.angle() == 200);

    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);
    g.setAngle(5760);
    BOOST_TEST(g.angle() == 0);

    g.setPoints(QPointF(1, 2), QPointF(3, 4), 30);
    BOOST_TEST(g.angle() == 30);

    g.setPointsRadians(QPointF(1, 2), QPointF(3, 4), M_PI_2);
    BOOST_TEST(g.angle() == 90);

    g.setTopLeft(QPointF(10, 20));
    BOOST_TEST(g.topLeft() == QPointF(10, 20));
    g.setTopRight(QPointF(10, 20));
    BOOST_TEST(g.topRight() == QPointF(10, 20));
    g.setBottomLeft(QPointF(10, 20));
    BOOST_TEST(g.bottomLeft() == QPointF(10, 20));
    g.setBottomRight(QPointF(10, 20));
    BOOST_TEST(g.bottomRight() == QPointF(10, 20));
    g.setLeft(30);
    BOOST_TEST(g.left() == 30);
    g.setTop(30);
    BOOST_TEST(g.top() == 30);
    g.setRight(30);
    BOOST_TEST(g.right() == 30);
    g.setBottom(30);
    BOOST_TEST(g.bottom() == 30);
    g.setX(40);
    BOOST_TEST(g.x() == 40);
    g.setY(40);
    BOOST_TEST(g.y() == 40);
    g.setWidth(40);
    BOOST_TEST(g.width() == 40);
    g.setHeight(40);
    BOOST_TEST(g.height() == 40);

    g.setRect(1, 2, 3, 4, 30);
    BOOST_TEST(g.angle() == 30);

    g.setRectRadians(1, 2, 3, 4 M_PI_2);
    BOOST_TEST(g.angle() == 90);

    qreal a_a, a_b, a_c, a_d, a_g;
    g.getRect(&a_a, &a_b, &a_c, &a_d, &a_g);
    BOOST_TEST(a_g == 90);

    qreal a_h;
    g.getRectRadians(&a_a, &a_b, &a_c, &a_d, &a_h);
    BOOST_TEST(a_h == M_PI_2);

    z_qtshapes::ZQRectF g2 = g.adjusted(a_a, a_b, a_c, a_d, a_g);
    BOOST_TEST(g2.angle() == 180);

    BOOST_TEST(g.toString() == QString("ZQRectF(1,2 size 3x4 90 degrees)");
    
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

    z_qtshapes::ZQRectF j(1, 2, 3, 4, 30);
    z_qtshapes::ZQRectF k(1, 2, 3, 4, 20);
    BOOST_TEST(g == j);
    BOOST_TEST(g != k);
}



BOOST_AUTO_TEST_CASE(Z_QEllipse)
{
    z_qtshapes::ZQEllipse a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQEllipse b(QPoint(1,2), QPoint(3,4));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQEllipse c(QPoint(1,2), QPoint(3,4), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQEllipse d(QPoint(1,2), QPoint(3,4), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQEllipse e(1, 2, 3, 4;
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQEllipse f(1, 2, 3, 4, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQEllipse g(0, 0, 0, 0, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQEllipse h = g.rotated(10);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQEllipse i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.angle() == 200);

    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);
    g.setAngle(5760);
    BOOST_TEST(g.angle() == 0);

    g.setPoints(QPoint(1, 2), QPoint(3, 4), 30);
    BOOST_TEST(g.angle() == 30);

    g.setPointsRadians(QPoint(1, 2), QPoint(3, 4), M_PI_2);
    BOOST_TEST(g.angle() == 90);

    g.setTopLeft(QPoint(10, 20));
    BOOST_TEST(g.topLeft() == QPoint(10, 20));
    g.setTopRight(QPoint(10, 20));
    BOOST_TEST(g.topRight() == QPoint(10, 20));
    g.setBottomLeft(QPoint(10, 20));
    BOOST_TEST(g.bottomLeft() == QPoint(10, 20));
    g.setBottomRight(QPoint(10, 20));
    BOOST_TEST(g.bottomRight() == QPoint(10, 20));
    g.setLeft(30);
    BOOST_TEST(g.left() == 30);
    g.setTop(30);
    BOOST_TEST(g.top() == 30);
    g.setRight(30);
    BOOST_TEST(g.right() == 30);
    g.setBottom(30);
    BOOST_TEST(g.bottom() == 30);
    g.setX(40);
    BOOST_TEST(g.x() == 40);
    g.setY(40);
    BOOST_TEST(g.y() == 40);
    g.setWidth(40);
    BOOST_TEST(g.width() == 40);
    g.setHeight(40);
    BOOST_TEST(g.height() == 40);

    g.setEllipse(1, 2, 3, 4, 30);
    BOOST_TEST(g.angle() == 30);

    g.setEllipseRadians(1, 2, 3, 4 M_PI_2);
    BOOST_TEST(g.angle() == 90);

    int a_a, a_b, a_c, a_d, a_g;
    g.getEllipse(&a_a, &a_b, &a_c, &a_d, &a_g);
    BOOST_TEST(a_g == 90);

    qreal a_h;
    g.getEllipseRadians(&a_a, &a_b, &a_c, &a_d, &a_h);
    BOOST_TEST(a_h == M_PI_2);

    z_qtshapes::ZQEllipse g2 = g.adjusted(a_a, a_b, a_c, a_d, a_g);
    BOOST_TEST(g2.angle() == 180);

    BOOST_TEST(g.toString() == QString("ZQEllipse(1,2 size 3x4 90 degrees)");
    
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

    z_qtshapes::ZQEllipse j(1, 2, 3, 4, 30);
    z_qtshapes::ZQEllipse k(1, 2, 3, 4, 20);
    BOOST_TEST(g == j);
    BOOST_TEST(g != k);
}

BOOST_AUTO_TEST_CASE(Z_QEllipseF)
{
    z_qtshapes::ZQEllipseF a;
    BOOST_TEST(a.angle() == 0);

    z_qtshapes::ZQEllipseF b(QPointF(1,2), QPointF(3,4));
    BOOST_TEST(b.angle() == 0);

    z_qtshapes::ZQEllipseF c(QPointF(1,2), QPointF(3,4), 10);
    BOOST_TEST(c.angle() == 10);

    z_qtshapes::ZQEllipseF d(QPointF(1,2), QPointF(3,4), 5760);
    BOOST_TEST(d.angle() == 0);

    z_qtshapes::ZQEllipseF e(1, 2, 3, 4;
    BOOST_TEST(e.angle() == 0);

    z_qtshapes::ZQEllipseF f(1, 2, 3, 4, 5850);
    BOOST_TEST(f.angle() == 90);
    BOOST_TEST(f.angleRadians() == M_PI_2);
    
    z_qtshapes::ZQEllipseF g(0, 0, 0, 0, 10);
    g.rotate(10);
    BOOST_TEST(g.angle() == 20);
    g.rotateRadians(M_PI_2);
    BOOST_TEST(g.angle() == 110);
    z_qtshapes::ZQEllipseF h = g.rotated(10);
    BOOST_TEST(h.angle() == 120);
    z_qtshapes::ZQEllipseF i = g.rotatedRadians(M_PI_2);
    BOOST_TEST(i.angle() == 200);

    g.setAngle(10);
    BOOST_TEST(g.angle() == 10);
    g.setAngle(5760);
    BOOST_TEST(g.angle() == 0);

    g.setPoints(QPointF(1, 2), QPointF(3, 4), 30);
    BOOST_TEST(g.angle() == 30);

    g.setPointsRadians(QPointF(1, 2), QPointF(3, 4), M_PI_2);
    BOOST_TEST(g.angle() == 90);

    g.setTopLeft(QPointF(10, 20));
    BOOST_TEST(g.topLeft() == QPointF(10, 20));
    g.setTopRight(QPointF(10, 20));
    BOOST_TEST(g.topRight() == QPointF(10, 20));
    g.setBottomLeft(QPointF(10, 20));
    BOOST_TEST(g.bottomLeft() == QPointF(10, 20));
    g.setBottomRight(QPointF(10, 20));
    BOOST_TEST(g.bottomRight() == QPointF(10, 20));
    g.setLeft(30);
    BOOST_TEST(g.left() == 30);
    g.setTop(30);
    BOOST_TEST(g.top() == 30);
    g.setRight(30);
    BOOST_TEST(g.right() == 30);
    g.setBottom(30);
    BOOST_TEST(g.bottom() == 30);
    g.setX(40);
    BOOST_TEST(g.x() == 40);
    g.setY(40);
    BOOST_TEST(g.y() == 40);
    g.setWidth(40);
    BOOST_TEST(g.width() == 40);
    g.setHeight(40);
    BOOST_TEST(g.height() == 40);

    g.setEllipse(1, 2, 3, 4, 30);
    BOOST_TEST(g.angle() == 30);

    g.setEllipseRadians(1, 2, 3, 4 M_PI_2);
    BOOST_TEST(g.angle() == 90);

    qreal a_a, a_b, a_c, a_d, a_g;
    g.getEllipse(&a_a, &a_b, &a_c, &a_d, &a_g);
    BOOST_TEST(a_g == 90);

    qreal a_h;
    g.getEllipse(&a_a, &a_b, &a_c, &a_d, &a_h);
    BOOST_TEST(a_h == M_PI_2);

    z_qtshapes::ZQEllipseF g2 = g.adjusted(a_a, a_b, a_c, a_d, a_g);
    BOOST_TEST(g2.angle() == 180);

    BOOST_TEST(g.toString() == QString("ZQEllipseF(1,2 size 3x4 90 degrees)");
    
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

    z_qtshapes::ZQEllipseF j(1, 2, 3, 4, 30);
    z_qtshapes::ZQEllipseF k(1, 2, 3, 4, 20);
    BOOST_TEST(g == j);
    BOOST_TEST(g != k);
}
