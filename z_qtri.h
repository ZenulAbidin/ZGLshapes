/****************************************************************************
**
** Copyright (C) 2020 Ali Sherief
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file was adapted from the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef Z_QTRI_H
#define Z_QTRI_H

#define _USE_MATH_DEFINES
#include <tgmath.h>

#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include "z_base.h"

namespace z_qtshapes {

    class ZQTri {
    public:
        constexpr ZQTri() noexcept : x1(0), y1(0), x2(0), y2(0), x3(0), y3(0), a(0) {}
        constexpr ZQTri(const QPoint &first, const QPoint &second, const QPoint &third) noexcept;
        constexpr ZQTri(const QPoint &first, const QPoint &second, const QPoint &third, int angle) noexcept;
        constexpr ZQTri(int x1, int y1, int x2, int y2, int x3, int y3) noexcept;
        constexpr ZQTri(int x1, int y1, int x2, int y2, int x3, int y3, int angle) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;

        constexpr inline QPoint first() const noexcept;
        constexpr inline QPoint second() const noexcept;
        constexpr inline QPoint third() const noexcept;
        constexpr inline QPoint center() const noexcept;

        constexpr inline int x1() const noexcept;
        constexpr inline int y1() const noexcept;
        constexpr inline int x2() const noexcept;
        constexpr inline int y2() const noexcept;
        constexpr inline int x3() const noexcept;
        constexpr inline int y3() const noexcept;
        constexpr inline int angle() const noexcept;
        constexpr inline qreal angleRadians() const noexcept;

        inline void setX1(int x) noexcept;
        inline void setY1(int y) noexcept;
        inline void setX2(int x) noexcept;
        inline void setY2(int y) noexcept;
        inline void setX3(int x) noexcept;
        inline void setY3(int y) noexcept;
        inline void setFirst(const QPointF &p) noexcept;
        inline void setSecond(const QPointF &p) noexcept;
        inline void setThird(const QPointF &p) noexcept;
        inline void setAngle(int a) noexcept;
        inline void setAngleRadians(qreal a) noexcept;

        constexpr inline int length12() const noexcept;
        constexpr inline int length13() const noexcept;
        constexpr inline int length23() const noexcept;
        constexpr inline int area() const noexcept;

        inline void moveX1(int x) noexcept;
        inline void moveY1(int y) noexcept;
        inline void moveX2(int x) noexcept;
        inline void moveY2(int y) noexcept;
        inline void moveX3(int x) noexcept;
        inline void moveY3(int y) noexcept;
        inline void moveFirst(const QPoint &p) noexcept;
        inline void moveSecond(const QPoint &p) noexcept;
        inline void moveThird(const QPoint &p) noexcept;
        inline void moveCenter(const QPoint &p) noexcept;
        inline void moveBy(const QPoint &p1, const QPoint &p2, const QPoint &p3);

        constexpr inline ZQTri movedX1(int x) noexcept;
        constexpr inline ZQTri movedY1(int y) noexcept;
        constexpr inline ZQTri movedX2(int x) noexcept;
        constexpr inline ZQTri movedY2(int y) noexcept;
        constexpr inline ZQTri movedX3(int x) noexcept;
        constexpr inline ZQTri movedY3(int y) noexcept;
        constexpr inline ZQTri movedFirst(const QPoint &p) noexcept;
        constexpr inline ZQTri movedSecond(const QPoint &p) noexcept;
        constexpr inline ZQTri movedThird(const QPoint &p) noexcept;
        constexpr inline ZQTri movedCenter(const QPoint &p) noexcept;
        constexpr inline ZQTri movedBy(const QPoint &p1, const QPoint &p2, const QPoint &p3);

        inline void translate(int dx, int dy) noexcept;
        inline void translate(const QPoint &p) noexcept;
        constexpr inline ZQTri translated(int dx, int dy) const noexcept;
        constexpr inline ZQTri translated(const QPoint &p) const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQTri rotated(int da) noexcept;
        constexpr inline ZQTri rotatedRadians(qreal da) noexcept;

        inline void normalizeAngle() noexcept;
        inline int normalizedAngle() noexcept;

        inline void setTri(int x1, int y1, int x2, int y2, int x3, int y3) noexcept;
        inline void setTri(int x1, int y1, int x2, int y2, int x3, int y3, int a) noexcept;
        inline void setTriRadians(int x1, int y1, int x2, int y2, qreal angle) const;
        inline void getTri(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3) const;
        inline void getTri(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *a) const;
        inline void getTriRadians(int *xp1, int *y1, int *x2, int *y2, qreal *angle) const;

        inline void adjust(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3) noexcept;
        inline void adjust(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int angle) noexcept;
        inline void adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) noexcept;
        constexpr inline ZQTri adjusted(int dx1, int dy1, int dx2, dint y2, int dx3, int dy3) const noexcept;
        constexpr inline ZQTri adjusted(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int angle) const noexcept;
        constexpr inline ZQTri adjustedRadians(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, qreal angle) const noexcept;

        QPainterPath operator|(const ZQTri &r) const noexcept;
        QPainterPath operator&(const ZQTri &r) const noexcept;

        bool contains(const ZQTri &r, bool proper = false) const noexcept;
        bool contains(const QPoint &p, bool proper=false) const noexcept;
        inline bool contains(int x, int y) const noexcept;
        inline bool contains(int x, int y, bool proper) const noexcept;
        inline QPainterPath united(const ZQTri &other) const noexcept;
        inline QPainterPath intersected(const ZQTri &other) const noexcept;
        bool intersects(const ZQTri &r) const noexcept;

        bool isRight() const noexcept;
        bool isIso() const noexcept;
        bool isEquilateral() const noexcept;

        constexpr inline ZQTri toTri() const noexcept;
        ZQTri toAlignedTri() const noexcept;

        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        constexpr inline QString toString() const noexcept;

        friend constexpr inline bool operator==(const ZQTri &, const ZQTri &) noexcept;
        friend constexpr inline bool operator!=(const ZQTri &, const ZQTri &) noexcept;


    private:
        qreal x1p;
        qreal y1p;
        qreal x2p;
        qreal y2p;
        qreal x3p;
        qreal y3p;
        qreal a;
    };


    constexpr inline bool operator==(const ZQTri &, const ZQTri &) noexcept;
    constexpr inline bool operator!=(const ZQTri &, const ZQTri &) noexcept;

    /*****************************************************************************
      ZQTri stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQTri &);
    QDataStream &operator>>(QDataStream &, ZQTri &);
    #endif

    /*****************************************************************************
      ZQTri inline member functions
     *****************************************************************************/

    constexpr inline ZQTri::ZQTri(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_) noexcept
        : x1p(x1_), y1p(x1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_), a(0) {}

    constexpr inline ZQTri::ZQTri(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_, int angle) noexcept
        : x1p(x1_), y1p(x1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_), a(normalizedAngle(angle)) {}

    constexpr inline ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y()), a(0) {}

    constexpr inline ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third, int angle) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y()), a(normalizedAngle(angle)) {}

    constexpr inline bool ZQTri::isNull() const noexcept
    { return x1p == 0 && x2p == 0 && x3p == 0 && y1p == 0 && y2p == 0 && y3p == 0 && a == 0; }

    constexpr inline bool ZQTri::isEmpty() const noexcept
    { return x2p == x1p && x3p == x1p && y1p == x1p && y2p == x1p && y3p == x1p }

    constexpr inline int ZQTri::x1() const noexcept
    { return x1p; }

    constexpr inline int ZQTri::y1() const noexcept
    { return y1p; }

    constexpr inline int ZQTri::x2() const noexcept
    { return x2p; }

    constexpr inline int ZQTri::y2() const noexcept
    { return y2p; }

    constexpr inline int ZQTri::x3() const noexcept
    { return x3p; }

    constexpr inline int ZQTri::y3() const noexcept
    { return y3p; }

    constexpr inline int ZQTri::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQTri::angleRadians() const noexcept
    { return M_PI/180 * a; }

    inline void ZQTri::setX1(int pos) noexcept
    { x1p = pos; }

    inline void ZQTri::setY1(int pos) noexcept
    { y1p = pos; }

    inline void ZQTri::setX2(int pos) noexcept
    { x2p = pos; }

    inline void ZQTri::setY2(int pos) noexcept
    { y2p = pos; }

    inline void ZQTri::setX3(int pos) noexcept
    { x3p = pos; }

    inline void ZQTri::setY3(int pos) noexcept
    { y3p = pos; }

    inline void ZQTri::setAngle(int aangle) noexcept
    { a = normalizedAngle(aangle); }

    inline void ZQTri::setAngleRadians(qreal aangle) noexcept
    { a = normalizedAngle((int) (180/M_PI * aangle)); }

    constexpr inline QPoint ZQTri::first() const noexcept
    { return QPoint(x1p, y1p); }

    constexpr inline QPoint ZQTri::second() const noexcept
    { return QPoint(x2p, y2p); }

    constexpr inline QPoint ZQTri::third() const noexcept
    { return QPoint(x3p, y3p); }

    constexpr inline QPoint ZQTri::center() const noexcept
    { return QPoint(int((qint64(x1p)+x2p+x3p)/3), int((qint64(y1p)+y2p+y3p)/3)); } // cast avoids overflow on addition

    constexpr inline int length12() const noexcept
    {
        int x = x2p - x1p;
        int y = y2p - y1p;
        return (int) sqrt(x*x + y*y);
    }

    constexpr inline int length13() const noexcept
    {
        int x = x3p - x1p;
        int y = y3p - y1p;
        return (int) sqrt(x*x + y*y);
    }

    constexpr inline int length23() const noexcept
    {
        int x = x3p - x2p;
        int y = y3p - y2p;
        return (int) sqrt(x*x + y*y);
    }

    constexpr inline int area() const noexcept
    {
        return abs(x1p - x3p)*(y2p - y1p) - (x1p - x2p)*(y3p - y1p))/2;
    }

    inline void ZQTri::translate(int dx, int dy) noexcept
    {
        x1 += dx;
        y1 += dy;
        x2 += dx;
        y2 += dy;
    }

    inline void ZQTri::translate(const QPoint &p) noexcept
    {
        x1 += p.x();
        y1 += p.y();
        x2 += p.x();
        y2 += p.y();
    }

    constexpr inline ZQTri ZQTri::translated(int dx, int dy) const noexcept
    { return ZQTri(QPoint(x1 + dx, y1 + dy), QPoint(x2 + dx, y2 + dy)); }

    constexpr inline ZQTri ZQTri::translated(const QPoint &p) const noexcept
    { return ZQTri(QPoint(x1 + p.x(), y1 + p.y()), QPoint(x2 + p.x(), y2 + p.y())); }

    inline void ZQTri::rotate(int angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQTri::rotateRadians(qreal angle) const noexcept
    { a += normalizedAngle((int) (180/M_PI * angle)); }

    constexpr inline ZQTri ZQTri::rotate(int angle) const noexcept
    { return ZQTri(x1, y1, x2, y2, a + normalizedAngle(angle)); }

    constexpr inline ZQTri ZQTri::rotateRadians(qreal angle) const noexcept
    { return ZQTri(x1, y1, x2, y2, a + normalizedAngle((int) (180/M_PI * angle))); }


    inline void ZQTri::normalizeAngle() noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle > 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
    }

    inline int ZQTri::normalizedAngle(int a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle > 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQTriF::setX1(qreal x) noexcept
    {
        x1p = x;
    }

    inline void ZQTriF::setY1(qreal y) noexcept
    {
        y1p += y;
    }

    inline void ZQTriF::setX2(qreal x) noexcept
    {
        x2p = x;
    }

    inline void ZQTriF::setY2(qreal y) noexcept
    {
        y2p = y;
    }

    inline void ZQTriF::setX3(qreal x) noexcept
    {
        x3p = x;
    }

    inline void ZQTriF::setY3(qreal y) noexcept
    {
        y3p = y;
    }

    inline void ZQTriF::setFirst(const QPointF &p) noexcept
    {
        x1p = p.x();
        y1p = p.y();
    }

    inline void ZQTriF::setSecond(const QPointF &p) noexcept
    {
        x2p = p.x();
        y2p = p.y();
    }

    inline void ZQTriF::moveThird(const QPointF &p) noexcept
    {
        x3p = p.x();
        y3p = p.y();
    }


    inline void ZQTri::moveX1(int x) noexcept
    {
        x1p += x;
    }

    inline void ZQTri::moveY1(int y) noexcept
    {
        y1p += y;
    }

    inline void ZQTri::moveX2(int x) noexcept
    {
        x2p += x;
    }

    inline void ZQTri::moveY2(int y) noexcept
    {
        y2p += y;
    }

    inline void ZQTri::moveX3(int x) noexcept
    {
        x3p += x;
    }

    inline void ZQTri::moveY3(int y) noexcept
    {
        y3p += y;
    }

    inline void ZQTri::moveFirst(const QPoint &p) noexcept
    {
        x1p += p.x();
        y1p += p.y();
    }

    inline void ZQTri::moveSecond(const QPoint &p) noexcept
    {
        x2p += p.x();
        y2p += p.y();
    }

    inline void ZQTri::moveThird(const QPoint &p) noexcept
    {
        x3p += p.x();
        y3p += p.y();
    }

    inline void ZQTri::moveCenter(const QPoint &p) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
    }

    inline void ZQTri::moveBy(const QPoint &p1, const QPoint &p2, const QPoint &p3)
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
    }

    constexpr inline ZQTri ZQTri::movedX1(int x) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveX1(x);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedY1(int y) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveY1(y);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedX2(int x) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveX2(x);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedY2(int y) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveY2(y);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedX3(int x) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveX3(x);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedY3(int y) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveY3(x);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedFirst(const QPoint &p) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveFirst(p);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedSecond(const QPoint &p) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveSecond(p);
        return tmp;
    }

    constexpr inline ZQTri ZQTri::movedThird(const QPoint &p) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveThird(p);
        return tmp;
    }

    constexpr inline void movedCenter(const QPoint &p) noexcept
    {
        ZQTri tmp = *this;
        tmp.moveCenter(p);
        return tmp;
    }

    constexpr inline ZQTri movedBy(const QPoint &p1, const QPoint &p2, const QPoint &p3)
    {
        ZQTri tmp = *this;
        tmp.moveFirst(p1);
        tmp.moveSecond(p2);
        tmp.moveThird(p3);
        return tmp;
    }

    inline void ZQTri::setTri(int x1, int y1, int x2, int y2, int x3, int y3) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
    }

    inline void ZQTri::setTri(int x1, int y1, int x2, int y2, int x3, int y3, int a) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = normalizedAngle(a);
    }

    inline void ZQTri::getTri(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
    }

    inline void ZQTri::getTri(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *a) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a = this->a;
    }

    inline void ZQTri::setTriRadians(int x1, int y1, int x2, int y2, qreal angle) const
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = normalizedAngle((int) (180/M_PI * angle));
    }

    inline void ZQTri::getTriRadians(int *xp1, int *y1, int *x2, int *y2, qreal *angle) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a = normalizedAngle(M_PI/180 * this->a);
    }

    constexpr inline ZQTri adjusted(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3);
        return tmp;
    }

    constexpr inline ZQTri adjusted(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int angle) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3, angle);
        return tmp;
    }

    constexpr inline ZQTri adjustedRadians(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int angle) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjustRadians(dx1, dy1, dx2, dy2, dx3, dy3, angle);
        return tmp;
    }


    inline bool ZQTri::contains(int ax, int ay, bool aproper) const noexcept
    {
        return contains(QPoint(ax, ay), aproper);
    }

    inline bool ZQTri::contains(int ax, int ay) const noexcept
    {
        return contains(QPoint(ax, ay), false);
    }

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQTri(%1,%2 %3,%4 %5,%6 %7 degrees))".arg(x1p, y1p, x2p, y2p, x3p, y3p, a));
    }


    inline ZQTri ZQTri::intersected(const ZQTri &other) const noexcept
    {
        return *this & other;
    }

    inline ZQTri ZQTri::united(const ZQTri &r) const noexcept
    {
        return *this | r;
    }

    constexpr inline bool operator==(const ZQTri &r1, const ZQTri &r2) noexcept
    {
        return r1.x1==r2.x1 && r1.x2==r2.x2 && r1.y1==r2.y1 && r1.y2==r2.y2 && r1.a == r2.a;
    }

    constexpr inline bool operator!=(const ZQTri &r1, const ZQTri &r2) noexcept
    {
        return !(r1 == r2);
    }

    #ifndef QT_NO_DEBUG_STREAM
    Q_CORE_EXPORT QDebug operator<<(QDebug, const ZQTri &);
    #endif




    class ZQTriF {
    public:
        constexpr ZQTriF() noexcept : x1(0), y1(0), x2(0), y2(0), x3(0), y3(0), a(0) {}
        constexpr ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third) noexcept;
        constexpr ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third, qreal angle) noexcept;
        constexpr ZQTriF(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) noexcept;
        constexpr ZQTriF(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal angle) noexcept;
        constexpr ZQTriF(const ZQTri &rect) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;

        constexpr inline QPointF first() const noexcept;
        constexpr inline QPointF second() const noexcept;
        constexpr inline QPointF third() const noexcept;
        constexpr inline QPointF center() const noexcept;

        constexpr inline qreal x1() const noexcept;
        constexpr inline qreal y1() const noexcept;
        constexpr inline qreal x2() const noexcept;
        constexpr inline qreal y2() const noexcept;
        constexpr inline qreal x3() const noexcept;
        constexpr inline qreal y3() const noexcept;
        constexpr inline qreal angle() const noexcept;
        constexpr inline qreal angleRadians() const noexcept;

        inline void setX1(qreal pos) noexcept;
        inline void setY1(qreal pos) noexcept;
        inline void setX2(qreal pos) noexcept;
        inline void setY2(qreal pos) noexcept;
        inline void setX3(qreal pos) noexcept;
        inline void setY3(qreal pos) noexcept;
        inline void setFirst(const QPointF &p) noexcept;
        inline void setSecond(const QPointF &p) noexcept;
        inline void setThird(const QPointF &p) noexcept;
        inline void setAngle(qreal angle) noexcept { a = noramlizedAngle(angle); }
        inline void setAngleRadians(qreal angle) noexcept { a = normalizedAngle(180/M_PI * angle); }

        constexpr inline qreal length12() const noexcept;
        constexpr inline qreal length13() const noexcept;
        constexpr inline qreal length23() const noexcept;
        constexpr inline qreal area() const noexcept;

        inline void moveX1(qreal pos) noexcept;
        inline void moveY1(qreal pos) noexcept;
        inline void moveX2(qreal pos) noexcept;
        inline void moveY2(qreal pos) noexcept;
        inline void moveX3(qreal pos) noexcept;
        inline void moveY3(qreal pos) noexcept;
        inline void moveFirst(const QPointF &p) noexcept;
        inline void moveSecond(const QPointF &p) noexcept;
        inline void moveThird(const QPointF &p) noexcept;
        inline void moveCenter(const QPointF &p) noexcept;
        inline void moveBy(const QPointF &p1, const QPointF &p2, const QPointF &p3);

        constexpr inline ZQTriF movedX1(qreal x) noexcept;
        constexpr inline ZQTriF movedY1(qreal y) noexcept;
        constexpr inline ZQTriF movedX2(qreal x) noexcept;
        constexpr inline ZQTriF movedY2(qreal y) noexcept;
        constexpr inline ZQTriF movedX3(qreal x) noexcept;
        constexpr inline ZQTriF movedY3(qreal y) noexcept;
        constexpr inline ZQTriF movedFirst(const QPointF &p) noexcept;
        constexpr inline ZQTriF movedSecond(const QPointF &p) noexcept;
        constexpr inline ZQTriF movedThird(const QPointF &p) noexcept;
        constexpr inline ZQTriF movedCenter(const QPointF &p) noexcept;
        constexpr inline ZQTriF movedBy(const QPointF &p1, const QPointF &p2, const QPointF &p3);

        inline void setTri(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) noexcept;
        inline void setTri(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal a) noexcept;
        inline void setTriRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle) const;
        inline void getTri(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3) const;
        inline void getTri(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, int *a) const;
        inline void getTriRadians(qreal *xp1, qreal *y1, qreal *x2, qreal *y2, qreal *angle) const;

        inline void translate(qreal dx, qreal dy) noexcept;
        inline void translate(const QPointF &p) noexcept;

        constexpr inline ZQTriF translated(qreal dx, qreal dy) const noexcept;
        constexpr inline ZQTriF translated(const QPointF &p) const noexcept;

        inline void rotate(qreal da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQTriF rotated(qreal da) noexcept;
        constexpr inline ZQTriF rotatedRadians(qreal da) noexcept;

        inline void normalizeAngle() noexcept;
        inline int normalizedAngle() noexcept;

        inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) noexcept;
        inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) noexcept;
        inline void adjustRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) noexcept;
        constexpr inline ZQTriF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) const noexcept;
        constexpr inline ZQTriF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) const noexcept;
        constexpr inline ZQTriF adjustedRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) const noexcept;

        QPainterPath operator|(const ZQTriF &r) const noexcept;
        QPainterPath operator&(const ZQTriF &r) const noexcept;

        bool contains(const ZQTriF &r) const noexcept;
        bool contains(const QPointF &p) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQTriF &other) const noexcept;
        inline QPainterPath intersected(const ZQTriF &other) const noexcept;
        bool intersects(const ZQTriF &r) const noexcept;

        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        constexpr inline QString toString() const noexcept;

        friend constexpr inline bool operator==(const ZQTriF &, const ZQTriF &) noexcept;
        friend constexpr inline bool operator!=(const ZQTriF &, const ZQTriF &) noexcept;

    private:
        qreal xp;
        qreal yp;
        qreal w;
        qreal h;
        qreal a;
    };



    constexpr inline bool operator==(const ZQTriF &, const ZQTriF &) noexcept;
    constexpr inline bool operator!=(const ZQTriF &, const ZQTriF &) noexcept;


    /*****************************************************************************
      ZQTriF stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQTriF &);
    QDataStream &operator>>(QDataStream &, ZQTriF &);
    #endif

    /*****************************************************************************
      ZQTriF inline member functions
     *****************************************************************************/
    constexpr inline ZQTri::ZQTri(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_) noexcept
        : x1p(x1_), y1p(x1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_), a(0) {}

    constexpr inline ZQTri::ZQTri(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_, int angle) noexcept
        : x1p(x1_), y1p(x1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_), a(normalizedAngle(angle)) {}

    constexpr inline ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y()), a(0) {}

    constexpr inline ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third, int angle) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y()), a(normalizedAngle(angle)) {}

    //QT_WARNING_PUSH
    //QT_WARNING_DISABLE_GCC("-Wfloat-equal")
    // just compile with -Wno-float-equal

    constexpr inline bool ZQTriF::isNull() const noexcept
    { return x1p == 0. && x2p == 0. && x3p == 0. && y1p == 0. && y2p == 0. && y3p == 0. && a == 0.; }

    //QT_WARNING_POP

    constexpr inline bool ZQTriF::isEmpty() const noexcept
    { return x2p == x1p && x3p == x1p && y1p == x1p && y2p == x1p && y3p == x1p }

    constexpr inline int ZQTriF::x1() const noexcept
    { return x1p; }

    constexpr inline int ZQTriF::y1() const noexcept
    { return y1p; }

    constexpr inline int ZQTriF::x2() const noexcept
    { return x2p; }

    constexpr inline int ZQTriF::y2() const noexcept
    { return y2p; }

    constexpr inline int ZQTriF::x3() const noexcept
    { return x3p; }

    constexpr inline int ZQTriF::y3() const noexcept
    { return y3p; }


    constexpr inline qreal ZQTriF::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQTriF::angleRadians() const noexcept
    { return M_PI/180 * a; }

    inline void ZQTriF::setX1(qreal pos) noexcept
    { x1p = pos; }

    inline void ZQTriF::setY1(qreal pos) noexcept
    { y1p = pos; }

    inline void ZQTriF::setX2(qreal pos) noexcept
    { x2p = pos; }

    inline void ZQTriF::setY2(qreal pos) noexcept
    { y2p = pos; }

    inline void ZQTriF::setX3(qreal pos) noexcept
    { x3p = pos; }

    inline void ZQTriF::setY3(qreal pos) noexcept
    { y3p = pos; }

    constexpr inline QPointF ZQTriF::first() const noexcept
    { return QPoint(x1p, y1p); }

    constexpr inline QPointF ZQTriF::second() const noexcept
    { return QPointF(x2p, y2p); }

    constexpr inline QPointF ZQTriF::third() const noexcept
    { return QPointF(x3p, y3p); }

    constexpr inline QPointF ZQTriF::center() const noexcept
    { return QPointF((y1p + y2p + y3p)/3, (y1p + y2p + y3p)/3); }

    constexpr inline qreal length12() const noexcept
    {
        qreal x = x2p - x1p;
        qreal y = y2p - y1p;
        return qSqrt(x*x + y*y);
    }

    constexpr inline qreal length13() const noexcept
    {
        qreal x = x3p - x1p;
        qreal y = y3p - y1p;
        return qSqrt(x*x + y*y);
    }

    constexpr inline qreal length23() const noexcept
    {
        qreal x = x3p - x2p;
        qreal y = y3p - y2p;
        return qSqrt(x*x + y*y);
    }

    constexpr inline qreal area() const noexcept
    {
        return abs(x1p - x3p)*(y2p - y1p) - (x1p - x2p)*(y3p - y1p))/2;
    }

    inline void ZQTriF::setX1(qreal x) noexcept
    {
        x1p = x;
    }

    inline void ZQTriF::setY1(qreal y) noexcept
    {
        y1p += y;
    }

    inline void ZQTriF::setX2(qreal x) noexcept
    {
        x2p = x;
    }

    inline void ZQTriF::setY2(qreal y) noexcept
    {
        y2p = y;
    }

    inline void ZQTriF::setX3(qreal x) noexcept
    {
        x3p = x;
    }

    inline void ZQTriF::setY3(qreal y) noexcept
    {
        y3p = y;
    }

    inline void ZQTriF::setFirst(const QPointF &p) noexcept
    {
        x1p = p.x();
        y1p = p.y();
    }

    inline void ZQTriF::setSecond(const QPointF &p) noexcept
    {
        x2p = p.x();
        y2p = p.y();
    }

    inline void ZQTriF::moveThird(const QPointF &p) noexcept
    {
        x3p = p.x();
        y3p = p.y();
    }

    inline void ZQTriF::moveX1(qreal x) noexcept
    {
        x1p += x;
    }

    inline void ZQTriF::moveY1(qreal y) noexcept
    {
        y1p += y;
    }

    inline void ZQTriF::moveX2(qreal x) noexcept
    {
        x2p += x;
    }

    inline void ZQTriF::moveY2(qreal y) noexcept
    {
        y2p += y;
    }

    inline void ZQTriF::moveX3(qreal x) noexcept
    {
        x3p += x;
    }

    inline void ZQTriF::moveY3(qreal y) noexcept
    {
        y3p += y;
    }

    inline void ZQTriF::moveFirst(const QPointF &p) noexcept
    {
        x1p += p.x();
        y1p += p.y();
    }

    inline void ZQTriF::moveSecond(const QPointF &p) noexcept
    {
        x2p += p.x();
        y2p += p.y();
    }

    inline void ZQTriF::moveThird(const QPointF &p) noexcept
    {
        x3p += p.x();
        y3p += p.y();
    }

    inline void ZQTriF::moveCenter(const QPointF &p) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
    }

    inline void ZQTriF::moveBy(const QPointF &p1, const QPointF &p2, const QPointF &p3)
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
    }


    constexpr inline ZQTriF ZQTriF::movedX1(qreal x) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveX1(x);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedY1(qreal y) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveY1(y);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedX2(qreal x) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveX2(x);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedY2(qreal y) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveY2(y);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedX3(qreal x) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveX3(x);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedY3(qreal y) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveY3(x);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedFirst(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveFirst(p);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedSecond(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveSecond(p);
        return tmp;
    }

    constexpr inline ZQTriF ZQTriF::movedThird(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveThird(p);
        return tmp;
    }

    constexpr inline void movedCenter(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveCenter(p);
        return tmp;
    }

    inline void ZQTriF::getTri(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
    }

    inline void ZQTriF::getTri(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, qreal *a) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a = this->a;
    }

    inline void ZQTriF::getTriRadians(qreal *xp1, qreal *y1, qreal *x2, qreal *y2, qreal *angle) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a = M_PI/180 * this->a;
    }


    inline void ZQTriF::setTri(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
    }

    inline void ZQTriF::setTri(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal a) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = a;
    }


    inline void ZQTriF::setTriRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle) const
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = normalizedAngle((int) (180/M_PI * angle));
    }

    inline void ZQTriF::translate(qreal dx, qreal dy) noexcept
    {
        x1p += dx;
        y1p += dy;
        x2p += dx;
        y2p += dy;
        x3p += dx;
        y3p += dy;
    }

    inline void ZQTriF::translate(const QPointF &p) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
    }

    inline void ZQTriF::rotate(qreal angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQTriF::rotateRadians(qreal angle) const noexcept
    { a += (180/M_PI * normalizedAngle(angle)); }

    constexpr inline ZQTriF ZQTriF::rotate(qreal angle) const noexcept
    { return ZQTri(x1, y1, x2, y2, a + normalizedAngle(angle)); }

    constexpr inline ZQTriF ZQTriF::rotateRadians(qreal angle) const noexcept
    { return ZQTri(x1, y1, x2, y2, a + (180/M_PI * normalizedAngle(angle))); }

    inline void ZQTriF::normalizeAngle() noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle > 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
    }

    inline qreal ZQTriF::normalizedAngle(qreal a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle > 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQTriF::moveBy(qreal ax, qreal ay) noexcept
    {
        xp = ax;
        yp = ay;
    }

    inline void ZQTriF::moveBy(const QPointF &p) noexcept
    {
        xp = p.x();
        yp = p.y();
    }

    constexpr inline ZQTriF ZQTriF::translated(qreal dx, qreal dy) const noexcept
    { return ZQTriF(xp + dx, yp + dy, w, h); }

    constexpr inline ZQTriF ZQTriF::translated(const QPointF &p) const noexcept
    { return ZQTriF(xp + p.x(), yp + p.y(), w, h); }


    inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
    }

    inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
        a += normalizedAngle(angle);
    }

    inline void adjustRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
        a += normalizedAngle(180/M_PI * angle);
    }

    constexpr inline ZQTriF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3);
        return tmp;
    }

    constexpr inline ZQTriF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3, angle);
        return tmp;
    }

    constexpr inline ZQTriF adjustedRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjustRadians(dx1, dy1, dx2, dy2, dx3, dy3, angle);
        return tmp;
    }

    inline bool ZQTriF::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPointF(ax, ay));
    }

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQTriF(%1,%2 %3,%4 %5,%6 %7 degrees))".arg(x1p, y1p, x2p, y2p, x3p, y3p, a));
    }


    inline ZQTriF ZQTriF::intersected(const ZQTriF &r) const noexcept
    {
        return *this & r;
    }

    inline ZQTriF ZQTriF::united(const ZQTriF &r) const noexcept
    {
        return *this | r;
    }

    constexpr inline bool operator==(const ZQTriF &r1, const ZQTriF &r2) noexcept
    {
        return qFuzzyCompare(r1.xp, r2.xp) && qFuzzyCompare(r1.yp, r2.yp)
               && qFuzzyCompare(r1.w, r2.w) && qFuzzyCompare(r1.h, r2.h) && qFuzzyCompare(r1.a, r2.a);
    }

    constexpr inline bool operator!=(const ZQTriF &r1, const ZQTriF &r2) noexcept
    {
        return !(r1 == r2);
    }

    constexpr inline ZQTri ZQTriF::toTri() const noexcept
    {
        return ZQTri(QPoint(qRound(xp), qRound(yp)), QPoint(qRound(xp + w) - 1, qRound(yp + h) - 1));
    }

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug, const ZQTriF &);
    #endif

}

#endif
