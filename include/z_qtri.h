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
        constexpr inline ZQTri() noexcept : x1p(0), y1p(0), x2p(0), y2p(0), x3p(0), y3p(0), a(0) {}
        constexpr inline ZQTri(const QPoint &first, const QPoint &second, const QPoint &third) noexcept;
        inline ZQTri(const QPoint &first, const QPoint &second, const QPoint &third, int angle) noexcept;
        constexpr inline ZQTri(int x1, int y1, int x2, int y2, int x3, int y3) noexcept;
        inline ZQTri(int x1, int y1, int x2, int y2, int x3, int y3, int angle) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        //constexpr inline bool isValid() const noexcept;

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
        inline void setFirst(const QPoint &p) noexcept;
        inline void setSecond(const QPoint &p) noexcept;
        inline void setThird(const QPoint &p) noexcept;
        inline void setAngle(int a) noexcept;
        inline void setAngleRadians(qreal a) noexcept;

        inline int length12() const noexcept;
        inline int length13() const noexcept;
        inline int length23() const noexcept;
        inline int area() const noexcept;

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
        inline void moveBy(const QPoint &p1, const QPoint &p2, const QPoint &p3) noexcept;

        inline ZQTri movedX1(int x) const noexcept;
        inline ZQTri movedY1(int y) const noexcept;
        inline ZQTri movedX2(int x) const noexcept;
        inline ZQTri movedY2(int y) const noexcept;
        inline ZQTri movedX3(int x) const noexcept;
        inline ZQTri movedY3(int y) const noexcept;
        inline ZQTri movedFirst(const QPoint &p) const noexcept;
        inline ZQTri movedSecond(const QPoint &p) const noexcept;
        inline ZQTri movedThird(const QPoint &p) const noexcept;
        inline ZQTri movedCenter(const QPoint &p) const noexcept;
        inline ZQTri movedBy(const QPoint &p1, const QPoint &p2, const QPoint &p3) const noexcept;

        inline void translate(int dx, int dy) noexcept;
        inline void translate(int dx, int dy, int angle) noexcept;
        inline void translateRadians(int dx, int dy, qreal angle) noexcept;
        inline void translate(const QPoint &p) noexcept;
        inline void translate(const QPoint &p, int angle) noexcept;
        inline void translateRadians(const QPoint &p, qreal angle) noexcept;

        inline ZQTri translated(int dx, int dy) const noexcept;
        inline ZQTri translated(int dx, int dy, int angle) const noexcept;
        inline ZQTri translatedRadians(int dx, int dy, qreal angle) const noexcept;
        inline ZQTri translated(const QPoint &p) const noexcept;
        inline ZQTri translated(const QPoint &p, int angle) const noexcept;
        inline ZQTri translatedRadians(const QPoint &p, qreal angle) const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        inline ZQTri rotated(int da) const noexcept;
        inline ZQTri rotatedRadians(qreal da) const noexcept;

        inline void setCoords(int x1, int y1, int x2, int y2, int x3, int y3) noexcept;
        inline void setCoords(int x1, int y1, int x2, int y2, int x3, int y3, int a_) noexcept;
        inline void setCoordsRadians(int x1, int y1, int x2, int y2, int x3, int y3, qreal a_) noexcept;
        inline void setCoords(const QPoint &p1, const QPoint &p2, const QPoint &p3) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y()); };
        inline void setCoords(const QPoint &p1, const QPoint &p2, const QPoint &p3, int a_) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), a_); };
        inline void setCoordsRadians(const QPoint &p1, const QPoint &p2, const QPoint &p3, qreal a_) noexcept {return setCoordsRadians(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), a_); };
        inline void getCoords(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3) const;
        inline void getCoords(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *a_) const;
        inline void getCoordsRadians(int *xp1, int *y1, int *x2, int *y2, int *x3, int *y3, qreal *a_) const;

        inline void adjust(const QPoint &p1, const QPoint &p2, const QPoint &p3) noexcept;
        inline void adjust(const QPoint &p1, const QPoint &p2, const QPoint &p3, int a_) noexcept;
        inline void adjustRadians(const QPoint &p1, const QPoint &p2, const QPoint &p3, qreal angle) noexcept;
        inline ZQTri adjusted(const QPoint &p1, const QPoint &p2, const QPoint &p3) const noexcept;
        inline ZQTri adjusted(const QPoint &p1, const QPoint &p2, const QPoint &p3, int a_) const noexcept;
        inline ZQTri adjustedRadians(const QPoint &p1, const QPoint &p2, const QPoint &p3, qreal a_) const noexcept;

        inline void adjust(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3) noexcept;
        inline void adjust(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int a_) noexcept;
        inline void adjustRadians(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, qreal angle) noexcept;
        inline ZQTri adjusted(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3) const noexcept;
        inline ZQTri adjusted(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int a_) const noexcept;
        inline ZQTri adjustedRadians(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, qreal a_) const noexcept;

        QPainterPath operator|(const ZQTri &r) const noexcept;
        QPainterPath operator&(const ZQTri &r) const noexcept;

        bool contains(const ZQTri &r, bool proper = false) const noexcept;
        bool contains(const QPoint &p) const noexcept;
        inline bool contains(int x, int y) const noexcept;
        inline QPainterPath united(const ZQTri &other) const noexcept;
        inline QPainterPath intersected(const ZQTri &other) const noexcept;
        bool intersects(const ZQTri &r) const noexcept;

        inline bool isAcute() const noexcept;
        inline bool isRight() const noexcept;
        inline bool isObtuse() const noexcept;
        inline bool isIso() const noexcept;
        inline bool isEquilateral() const noexcept;
        inline bool isScalene() const noexcept { return !isIso(); }

        QPainterPath toPath() const noexcept;
        QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        QString toString() const noexcept;

        friend constexpr inline bool operator==(const ZQTri &, const ZQTri &) noexcept;
        friend constexpr inline bool operator!=(const ZQTri &, const ZQTri &) noexcept;


    private:
        int x1p;
        int y1p;
        int x2p;
        int y2p;
        int x3p;
        int y3p;
        int a;
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
        : x1p(x1_), y1p(y1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_), a(0) {}

    inline ZQTri::ZQTri(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_, int a_) noexcept
        : x1p(x1_), y1p(y1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_)
    {
        a = normalizedAngle(a_);
    }

    constexpr inline ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y()), a(0) {}

    inline ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third, int a_) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y())
    {
        a = normalizedAngle(a_);
    }

    constexpr inline bool ZQTri::isNull() const noexcept
    { return x1p == 0 && x2p == 0 && x3p == 0 && y1p == 0 && y2p == 0 && y3p == 0 && a == 0; }

    constexpr inline bool ZQTri::isEmpty() const noexcept
    { return x2p == x1p && x3p == x1p && y1p == x1p && y2p == x1p && y3p == x1p; }

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

    inline void ZQTri::setAngle(int a_) noexcept
    { a = normalizedAngle(a_); }

    inline void ZQTri::setAngleRadians(qreal a_) noexcept
    { a = normalizedAngle((int) (180/M_PI * a_)); }

    constexpr inline QPoint ZQTri::first() const noexcept
    { return QPoint(x1p, y1p); }

    constexpr inline QPoint ZQTri::second() const noexcept
    { return QPoint(x2p, y2p); }

    constexpr inline QPoint ZQTri::third() const noexcept
    { return QPoint(x3p, y3p); }

    constexpr inline QPoint ZQTri::center() const noexcept
    { return QPoint(int((qint64(x1p)+x2p+x3p)/3), int((qint64(y1p)+y2p+y3p)/3)); } // cast avoids overflow on addition

    inline int ZQTri::length12() const noexcept
    {
        int x = x2p - x1p;
        int y = y2p - y1p;
        return (int) sqrt(x*x + y*y);
    }

    inline int ZQTri::length13() const noexcept
    {
        int x = x3p - x1p;
        int y = y3p - y1p;
        return (int) sqrt(x*x + y*y);
    }

    inline int ZQTri::length23() const noexcept
    {
        int x = x3p - x2p;
        int y = y3p - y2p;
        return (int) sqrt(x*x + y*y);
    }

    inline int ZQTri::area() const noexcept
    {
        return abs((x1p - x3p)*(y2p - y1p) - (x1p - x2p)*(y3p - y1p))/2;
    }

    inline void ZQTri::translate(int dx, int dy) noexcept
    {
        x1p += dx;
        y1p += dy;
        x2p += dx;
        y2p += dy;
        x3p += dx;
        y3p += dy;
    }

    inline void ZQTri::translate(int dx, int dy, int a_) noexcept
    {
        x1p += dx;
        y1p += dy;
        x2p += dx;
        y2p += dy;
        x3p += dx;
        y3p += dy;
        a = normalizedAngle(a + a_);
    }

    inline void ZQTri::translateRadians(int dx, int dy, qreal a_) noexcept
    {
        x1p += dx;
        y1p += dy;
        x2p += dx;
        y2p += dy;
        x3p += dx;
        y3p += dy;
        a = normalizedAngle(a + (int) 180/M_PI * a_);
    }

    inline void ZQTri::translate(const QPoint &p) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
    }

    inline void ZQTri::translate(const QPoint &p, int a_) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
        a = normalizedAngle(a + a_);
    }

    inline void ZQTri::translateRadians(const QPoint &p, qreal a_) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
        a = normalizedAngle(a + (int) 180/M_PI * a_);
    }

    inline ZQTri ZQTri::translated(int dx, int dy) const noexcept
    { return ZQTri(QPoint(x1p + dx, y1p + dy), QPoint(x2p + dx, y2p + dy), QPoint(x3p + dx, y3p + dy)); }

    inline ZQTri ZQTri::translated(int dx, int dy, int a_) const noexcept
    { return ZQTri(QPoint(x1p + dx, y1p + dy), QPoint(x2p + dx, y2p + dy), QPoint(x3p + dx, y3p + dy), a_); }

    inline ZQTri ZQTri::translatedRadians(int dx, int dy, qreal a_) const noexcept
    { return ZQTri(QPoint(x1p + dx, y1p + dy), QPoint(x2p + dx, y2p + dy), QPoint(x3p + dx, y3p + dy), a_); }

    inline ZQTri ZQTri::translated(const QPoint &p) const noexcept
    { return ZQTri(QPoint(x1p + p.x(), y1p + p.y()), QPoint(x2p + p.x(), y2p + p.y()), QPoint(x3p + p.x(), y3p + p.y())); }

    inline ZQTri ZQTri::translated(const QPoint &p, int a_) const noexcept
    { return ZQTri(QPoint(x1p + p.x(), y1p + p.y()), QPoint(x2p + p.x(), y2p + p.y()), QPoint(x3p + p.x(), y3p + p.y()), a_); }

    inline ZQTri ZQTri::translatedRadians(const QPoint &p, qreal a_) const noexcept
    { return ZQTri(QPoint(x1p + p.x(), y1p + p.y()), QPoint(x2p + p.x(), y2p + p.y()), QPoint(x3p + p.x(), y3p + p.y()), a_); }

    inline void ZQTri::rotate(int a_) noexcept
    { a = normalizedAngle(a + a_); }

    inline void ZQTri::rotateRadians(qreal a_) noexcept
    { a = normalizedAngle(a + (int) (180/M_PI * a_)); }

    inline ZQTri ZQTri::rotated(int a_) const noexcept
    { return ZQTri(x1p, y1p, x2p, y2p, x3p, y3p, normalizedAngle(a + a_)); }

    inline ZQTri ZQTri::rotatedRadians(qreal a_) const noexcept
    { return ZQTri(x1p, y1p, x2p, y2p, x3p, y3p, normalizedAngle(a + (int) (180/M_PI * a_))); }


    inline void ZQTri::setX1(int x) noexcept
    {
        x1p = x;
    }

    inline void ZQTri::setY1(int y) noexcept
    {
        y1p += y;
    }

    inline void ZQTri::setX2(int x) noexcept
    {
        x2p = x;
    }

    inline void ZQTri::setY2(int y) noexcept
    {
        y2p = y;
    }

    inline void ZQTri::setX3(int x) noexcept
    {
        x3p = x;
    }

    inline void ZQTri::setY3(int y) noexcept
    {
        y3p = y;
    }

    inline void ZQTri::setFirst(const QPoint &p) noexcept
    {
        x1p = p.x();
        y1p = p.y();
    }

    inline void ZQTri::setSecond(const QPoint &p) noexcept
    {
        x2p = p.x();
        y2p = p.y();
    }

    inline void ZQTri::setThird(const QPoint &p) noexcept
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

    inline void ZQTri::moveBy(const QPoint &p1, const QPoint &p2, const QPoint &p3) noexcept
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
    }

    inline ZQTri ZQTri::movedX1(int x) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveX1(x);
        return tmp;
    }

    inline ZQTri ZQTri::movedY1(int y) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveY1(y);
        return tmp;
    }

    inline ZQTri ZQTri::movedX2(int x) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveX2(x);
        return tmp;
    }

    inline ZQTri ZQTri::movedY2(int y) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveY2(y);
        return tmp;
    }

    inline ZQTri ZQTri::movedX3(int x) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveX3(x);
        return tmp;
    }

    inline ZQTri ZQTri::movedY3(int y) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveY3(y);
        return tmp;
    }

    inline ZQTri ZQTri::movedFirst(const QPoint &p) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveFirst(p);
        return tmp;
    }

    inline ZQTri ZQTri::movedSecond(const QPoint &p) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveSecond(p);
        return tmp;
    }

    inline ZQTri ZQTri::movedThird(const QPoint &p) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveThird(p);
        return tmp;
    }

    inline ZQTri ZQTri::movedCenter(const QPoint &p) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveCenter(p);
        return tmp;
    }

    inline ZQTri ZQTri::movedBy(const QPoint &p1, const QPoint &p2, const QPoint &p3) const noexcept
    {
        ZQTri tmp = *this;
        tmp.moveFirst(p1);
        tmp.moveSecond(p2);
        tmp.moveThird(p3);
        return tmp;
    }

    inline void ZQTri::getCoords(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
    }

    inline void ZQTri::getCoords(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *a_) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a_ = this->a;
    }

    inline void ZQTri::getCoordsRadians(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, qreal *a_) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a_ = M_PI/180 * a;
    }


    inline void ZQTri::setCoords(int x1, int y1, int x2, int y2, int x3, int y3) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
    }

    inline void ZQTri::setCoords(int x1, int y1, int x2, int y2, int x3, int y3, int a) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = normalizedAngle(a);
    }

    inline void ZQTri::setCoordsRadians(int x1, int y1, int x2, int y2, int x3, int y3, qreal angle) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = normalizedAngle((int) (180/M_PI * angle));
    }


    inline void ZQTri::adjust(const QPoint &p1, const QPoint &p2, const QPoint &p3) noexcept
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
    }

    inline void ZQTri::adjust(const QPoint &p1, const QPoint &p2, const QPoint &p3, int a_) noexcept
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
        a = normalizedAngle(a + a_);
    }

    inline void ZQTri::adjustRadians(const QPoint &p1, const QPoint &p2, const QPoint &p3, qreal a_) noexcept
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
        a = normalizedAngle(a + 180/M_PI * a_);
    }

    inline ZQTri ZQTri::adjusted(const QPoint &p1, const QPoint &p2, const QPoint &p3) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjust(p1, p2, p3);
        return tmp;
    }

    inline ZQTri ZQTri::adjusted(const QPoint &p1, const QPoint &p2, const QPoint &p3, int angle) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjust(p1, p2, p3, angle);
        return tmp;
    }

    inline ZQTri ZQTri::adjustedRadians(const QPoint &p1, const QPoint &p2, const QPoint &p3, qreal angle) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjustRadians(p1, p2, p3, angle);
        return tmp;
    }



    inline void ZQTri::adjust(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
    }

    inline void ZQTri::adjust(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int a_) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
        a = normalizedAngle(a + a_);
    }

    inline void ZQTri::adjustRadians(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, qreal a_) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
        a = normalizedAngle(a + 180/M_PI * a_);
    }

    inline ZQTri ZQTri::adjusted(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3);
        return tmp;
    }

    inline ZQTri ZQTri::adjusted(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int angle) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3, angle);
        return tmp;
    }

    inline ZQTri ZQTri::adjustedRadians(int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, qreal angle) const noexcept
    {
        ZQTri tmp = *this;
        tmp.adjustRadians(dx1, dy1, dx2, dy2, dx3, dy3, angle);
        return tmp;
    }


    inline bool ZQTri::contains(int ax, int ay) const noexcept
    {
        return contains(QPoint(ax, ay));
    }


    inline QPainterPath ZQTri::intersected(const ZQTri &other) const noexcept
    {
        return *this & other;
    }

    inline QPainterPath ZQTri::united(const ZQTri &r) const noexcept
    {
        return *this | r;
    }

    inline bool ZQTri::isAcute() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 < 90 && a2 < 90 && a3 < 90) {
            return true;
        }
        return false;
    }

    inline bool ZQTri::isRight() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 == 90 || a2 == 90 || a3 == 90) {
            return true;
        }
        return false;
    }

    inline bool ZQTri::isObtuse() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 > 90 || a2 > 90 || a3 > 90) {
            return true;
        }
        return false;
    }

    inline bool ZQTri::isIso() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 == a2 || a2 == a3 || a3 == a1) {
            return true;
        }
        return false;
    }

    inline bool ZQTri::isEquilateral() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 == 60 && a2 == 60 && a3 == 60) {
            return true;
        }
        return false;
    }

    constexpr inline bool operator==(const ZQTri &r1, const ZQTri &r2) noexcept
    {
        return r1.x1p==r2.x1p && r1.x2p==r2.x2p && r1.y1p==r2.y1p && r1.y2p==r2.y2p && r1.x3p==r2.x3p && r1.y3p==r2.y3p && r1.a == r2.a;
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
        constexpr ZQTriF() noexcept : x1p(0), y1p(0), x2p(0), y2p(0), x3p(0), y3p(0), a(0) {}
        constexpr ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third) noexcept;
        ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third, qreal a_) noexcept;
        constexpr ZQTriF(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) noexcept;
        ZQTriF(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal a_) noexcept;
        constexpr ZQTriF(const ZQTri &tri) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        //constexpr inline bool isValid() const noexcept;

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
        inline void setAngle(qreal a_) noexcept { a = normalizedAngle(a_); }
        inline void setAngleRadians(qreal a_) noexcept { a = normalizedAngle(180/M_PI * a_); }

        inline qreal length12() const noexcept;
        inline qreal length13() const noexcept;
        inline qreal length23() const noexcept;
        inline qreal area() const noexcept;

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

        inline ZQTriF movedX1(qreal x) noexcept;
        inline ZQTriF movedY1(qreal y) noexcept;
        inline ZQTriF movedX2(qreal x) noexcept;
        inline ZQTriF movedY2(qreal y) noexcept;
        inline ZQTriF movedX3(qreal x) noexcept;
        inline ZQTriF movedY3(qreal y) noexcept;
        inline ZQTriF movedFirst(const QPointF &p) noexcept;
        inline ZQTriF movedSecond(const QPointF &p) noexcept;
        inline ZQTriF movedThird(const QPointF &p) noexcept;
        inline ZQTriF movedCenter(const QPointF &p) noexcept;
        inline ZQTriF movedBy(const QPointF &p1, const QPointF &p2, const QPointF &p3);

        inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) noexcept;
        inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal a) noexcept;
        inline void setCoordsRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal angle) noexcept;
        inline void setCoords(const QPointF &p1, const QPointF &p2, const QPointF &p3) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y()); };
        inline void setCoords(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal a_) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), a_); };
        inline void setCoordsRadians(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal a_) noexcept {return setCoordsRadians(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), a_); };
        inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3) const;
        inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, qreal *a) const;
        inline void getCoordsRadians(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, qreal *angle) const;

        inline void translate(qreal dx, qreal dy) noexcept;
        inline void translate(qreal dx, qreal dy, qreal a_) noexcept;
        inline void translateRadians(qreal dx, qreal dy, qreal a_) noexcept;
        inline void translate(const QPointF &p) noexcept;
        inline void translate(const QPointF &p, qreal a_) noexcept;
        inline void translateRadians(const QPointF &p, qreal a_) noexcept;

        inline ZQTriF translated(qreal dx, qreal dy) const noexcept;
        inline ZQTriF translated(qreal dx, qreal dy, qreal a_) const noexcept;
        inline ZQTriF translatedRadians(qreal dx, qreal dy, qreal a_) const noexcept;
        inline ZQTriF translated(const QPointF &p) const noexcept;
        inline ZQTriF translated(const QPointF &p, qreal a_) const noexcept;
        inline ZQTriF translatedRadians(const QPointF &p, qreal a_) const noexcept;

        inline void rotate(qreal da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        inline ZQTriF rotated(qreal da) const noexcept;
        inline ZQTriF rotatedRadians(qreal da) const noexcept;

        inline void adjust(const QPointF &p1, const QPointF &p2, const QPointF &p3) noexcept;
        inline void adjust(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal angle) noexcept;
        inline void adjustRadians(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal angle) noexcept;
        inline ZQTriF adjusted(const QPointF &p1, const QPointF &p2, const QPointF &p3) const noexcept;
        inline ZQTriF adjusted(const QPointF &p1, const QPointF &p2, const QPointF &p3, const qreal angle) const noexcept;
        inline ZQTriF adjustedRadians(const QPointF &p1, const QPointF &p2, const QPointF &p3, const qreal angle) const noexcept;

        inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) noexcept;
        inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) noexcept;
        inline void adjustRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) noexcept;
        inline ZQTriF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) const noexcept;
        inline ZQTriF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) const noexcept;
        inline ZQTriF adjustedRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal angle) const noexcept;

        QPainterPath operator|(const ZQTriF &r) const noexcept;
        QPainterPath operator&(const ZQTriF &r) const noexcept;

        bool contains(const ZQTriF &r, bool proper = false) const noexcept;
        bool contains(const QPointF &p) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQTriF &other) const noexcept;
        inline QPainterPath intersected(const ZQTriF &other) const noexcept;
        bool intersects(const ZQTriF &r) const noexcept;

        bool isAcute() const noexcept;
        bool isRight() const noexcept;
        bool isObtuse() const noexcept;
        bool isIso() const noexcept;
        bool isEquilateral() const noexcept;
        bool isScalene() const noexcept { return !isIso(); }

        QPainterPath toPath() const noexcept;
        QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        QString toString() const noexcept;

        inline ZQTri toTri() const noexcept;

        friend constexpr inline bool operator==(const ZQTriF &, const ZQTriF &) noexcept;
        friend constexpr inline bool operator!=(const ZQTriF &, const ZQTriF &) noexcept;

    private:
        qreal x1p;
        qreal y1p;
        qreal x2p;
        qreal y2p;
        qreal x3p;
        qreal y3p;
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
    constexpr inline ZQTriF::ZQTriF(qreal x1_, qreal y1_, qreal x2_, qreal y2_, qreal x3_, qreal y3_) noexcept
        : x1p(x1_), y1p(y1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_), a(0) {}

    inline ZQTriF::ZQTriF(qreal x1_, qreal y1_, qreal x2_, qreal y2_, qreal x3_, qreal y3_, qreal a_) noexcept
        : x1p(x1_), y1p(y1_), x2p(x2_), y2p(y2_), x3p(x3_), y3p(y3_)
    {
        a = normalizedAngle(a_);
    }

    constexpr inline ZQTriF::ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y()), a(0) {}

    inline ZQTriF::ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third, qreal a_) noexcept
        : x1p(first.x()), y1p(first.y()), x2p(second.x()), y2p(second.y()), x3p(third.x()), y3p(third.y())
    {
        a = normalizedAngle(a_);
    }

    constexpr inline ZQTriF::ZQTriF(const ZQTri &tri) noexcept
        : x1p(tri.x1()), y1p(tri.y1()), x2p(tri.x2()), y2p(tri.y2()), x3p(tri.x3()), y3p(tri.y3()), a(0) {}


    //QT_WARNING_PUSH
    //QT_WARNING_DISABLE_GCC("-Wfloat-equal")
    // just compile with -Wno-float-equal

    constexpr inline bool ZQTriF::isNull() const noexcept
    { return x1p == 0. && x2p == 0. && x3p == 0. && y1p == 0. && y2p == 0. && y3p == 0. && a == 0.; }

    //QT_WARNING_POP

    constexpr inline bool ZQTriF::isEmpty() const noexcept
    { return x2p == x1p && x3p == x1p && y1p == x1p && y2p == x1p && y3p == x1p; }

    constexpr inline qreal ZQTriF::x1() const noexcept
    { return x1p; }

    constexpr inline qreal ZQTriF::y1() const noexcept
    { return y1p; }

    constexpr inline qreal ZQTriF::x2() const noexcept
    { return x2p; }

    constexpr inline qreal ZQTriF::y2() const noexcept
    { return y2p; }

    constexpr inline qreal ZQTriF::x3() const noexcept
    { return x3p; }

    constexpr inline qreal ZQTriF::y3() const noexcept
    { return y3p; }


    constexpr inline qreal ZQTriF::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQTriF::angleRadians() const noexcept
    { return M_PI/180 * a; }

    constexpr inline QPointF ZQTriF::first() const noexcept
    { return QPoint(x1p, y1p); }

    constexpr inline QPointF ZQTriF::second() const noexcept
    { return QPointF(x2p, y2p); }

    constexpr inline QPointF ZQTriF::third() const noexcept
    { return QPointF(x3p, y3p); }

    constexpr inline QPointF ZQTriF::center() const noexcept
    { return QPointF((y1p + y2p + y3p)/3, (y1p + y2p + y3p)/3); }

    inline qreal ZQTriF::length12() const noexcept
    {
        qreal x = x2p - x1p;
        qreal y = y2p - y1p;
        return qSqrt(x*x + y*y);
    }

    inline qreal ZQTriF::length13() const noexcept
    {
        qreal x = x3p - x1p;
        qreal y = y3p - y1p;
        return qSqrt(x*x + y*y);
    }

    inline qreal ZQTriF::length23() const noexcept
    {
        qreal x = x3p - x2p;
        qreal y = y3p - y2p;
        return qSqrt(x*x + y*y);
    }

    inline qreal ZQTriF::area() const noexcept
    {
        return abs((x1p - x3p)*(y2p - y1p) - (x1p - x2p)*(y3p - y1p))/2;
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

    inline void ZQTriF::setThird(const QPointF &p) noexcept
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


    inline ZQTriF ZQTriF::movedX1(qreal x) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveX1(x);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedY1(qreal y) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveY1(y);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedX2(qreal x) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveX2(x);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedY2(qreal y) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveY2(y);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedX3(qreal x) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveX3(x);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedY3(qreal y) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveY3(y);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedFirst(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveFirst(p);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedSecond(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveSecond(p);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedThird(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveThird(p);
        return tmp;
    }

    inline ZQTriF ZQTriF::movedCenter(const QPointF &p) noexcept
    {
        ZQTriF tmp = *this;
        tmp.moveCenter(p);
        return tmp;
    }

    inline void ZQTriF::getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
    }

    inline void ZQTriF::getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, qreal *a_) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a_ = this->a;
    }

    inline void ZQTriF::getCoordsRadians(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, qreal *a_) const
    {
        *x1 = x1p;
        *y1 = y1p;
        *x2 = x2p;
        *y2 = y2p;
        *x3 = x3p;
        *y3 = y3p;
        *a_ = M_PI/180 * this->a;
    }


    inline void ZQTriF::setCoords(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
    }

    inline void ZQTriF::setCoords(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal a_) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = normalizedAngle(a_);
    }


    inline void ZQTriF::setCoordsRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal a_) noexcept
    {
        x1p = x1;
        y1p = y1;
        x2p = x2;
        y2p = y2;
        x3p = x3;
        y3p = y3;
        this->a = normalizedAngle((int) (180/M_PI * a_));
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

    inline void ZQTriF::translate(qreal dx, qreal dy, qreal a_) noexcept
    {
        x1p += dx;
        y1p += dy;
        x2p += dx;
        y2p += dy;
        x3p += dx;
        y3p += dy;
        a = normalizedAngle(a + a_);
    }

    inline void ZQTriF::translateRadians(qreal dx, qreal dy, qreal a_) noexcept
    {
        x1p += dx;
        y1p += dy;
        x2p += dx;
        y2p += dy;
        x3p += dx;
        y3p += dy;
        a = normalizedAngle(a + 180/M_PI * a_);
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

    inline void ZQTriF::translate(const QPointF &p, qreal a_) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
        a = normalizedAngle(a + a_);
    }

    inline void ZQTriF::translateRadians(const QPointF &p, qreal a_) noexcept
    {
        x1p += p.x();
        y1p += p.y();
        x2p += p.x();
        y2p += p.y();
        x3p += p.x();
        y3p += p.y();
        a = normalizedAngle(a + 180/M_PI * a_);
    }

    inline void ZQTriF::rotate(qreal a_) noexcept
    { a = normalizedAngle(a + a_); }

    inline void ZQTriF::rotateRadians(qreal a_) noexcept
    { a = (180/M_PI * normalizedAngle(a + a_)); }

    inline ZQTriF ZQTriF::rotated(qreal a_) const noexcept
    { return ZQTri(x1p, y1p, x2p, y2p, x3p, y3p, normalizedAngle(a + a_)); }

    inline ZQTriF ZQTriF::rotatedRadians(qreal a_) const noexcept
    { return ZQTri(x1p, y1p, x2p, y2p, x3p, y3p, normalizedAngle(a + (180/M_PI * a_))); }


    inline ZQTriF ZQTriF::translated(qreal dx, qreal dy) const noexcept
    { return ZQTriF(QPointF(x1p + dx, y1p + dy), QPointF(x2p + dx, y2p + dy), QPointF(x3p + dx, y3p + dy)); }

    inline ZQTriF ZQTriF::translated(qreal dx, qreal dy, qreal a_) const noexcept
    { return ZQTriF(QPointF(x1p + dx, y1p + dy), QPointF(x2p + dx, y2p + dy), QPointF(x3p + dx, y3p + dy), a_); }

    inline ZQTriF ZQTriF::translatedRadians(qreal dx, qreal dy, qreal a_) const noexcept
    { return ZQTriF(QPointF(x1p + dx, y1p + dy), QPointF(x2p + dx, y2p + dy), QPointF(x3p + dx, y3p + dy), a_); }

    inline ZQTriF ZQTriF::translated(const QPointF &p) const noexcept
    { return ZQTriF(QPointF(x1p + p.x(), y1p + p.y()), QPointF(x2p + p.x(), y2p + p.y()), QPointF(x3p + p.x(), y3p + p.y())); }

    inline ZQTriF ZQTriF::translated(const QPointF &p, qreal a_) const noexcept
    { return ZQTriF(QPointF(x1p + p.x(), y1p + p.y()), QPointF(x2p + p.x(), y2p + p.y()), QPointF(x3p + p.x(), y3p + p.y()), a_); }

    inline ZQTriF ZQTriF::translatedRadians(const QPointF &p, qreal a_) const noexcept
    { return ZQTriF(QPointF(x1p + p.x(), y1p + p.y()), QPointF(x2p + p.x(), y2p + p.y()), QPointF(x3p + p.x(), y3p + p.y()), a_); }


    inline void ZQTriF::adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
    }

    inline void ZQTriF::adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal a_) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
        a = normalizedAngle(a + a_);
    }

    inline void ZQTriF::adjustRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal a_) noexcept
    {
        x1p += dx1;
        y1p += dy1;
        x2p += dx2;
        y2p += dy2;
        x3p += dx3;
        y3p += dy3;
        a = normalizedAngle(a + 180/M_PI * a_);
    }

    inline ZQTriF ZQTriF::adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3);
        return tmp;
    }

    inline ZQTriF ZQTriF::adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal a_) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjust(dx1, dy1, dx2, dy2, dx3, dy3, a_);
        return tmp;
    }

    inline ZQTriF ZQTriF::adjustedRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal dx3, qreal dy3, qreal a_) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjustRadians(dx1, dy1, dx2, dy2, dx3, dy3, a_);
        return tmp;
    }


    inline void ZQTriF::adjust(const QPointF &p1, const QPointF &p2, const QPointF &p3) noexcept
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
    }

    inline void ZQTriF::adjust(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal a_) noexcept
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
        a = normalizedAngle(a + a_);
    }

    inline void ZQTriF::adjustRadians(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal a_) noexcept
    {
        x1p += p1.x();
        y1p += p1.y();
        x2p += p2.x();
        y2p += p2.y();
        x3p += p3.x();
        y3p += p3.y();
        a = normalizedAngle(a + 180/M_PI * a_);
    }

    inline ZQTriF ZQTriF::adjusted(const QPointF &p1, const QPointF &p2, const QPointF &p3) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjust(p1, p2, p3);
        return tmp;
    }

    inline ZQTriF ZQTriF::adjusted(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal a_) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjust(p1, p2, p3, a_);
        return tmp;
    }

    inline ZQTriF ZQTriF::adjustedRadians(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal a_) const noexcept
    {
        ZQTriF tmp = *this;
        tmp.adjustRadians(p1, p2, p3, a_);
        return tmp;
    }


    inline bool ZQTriF::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPointF(ax, ay));
    }

    inline QPainterPath ZQTriF::intersected(const ZQTriF &r) const noexcept
    {
        return *this & r;
    }

    inline QPainterPath ZQTriF::united(const ZQTriF &r) const noexcept
    {
        return *this | r;
    }

    inline bool ZQTriF::isAcute() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 < 90 && a2 < 90 && a3 < 90) {
            return true;
        }
        return false;
    }

    inline bool ZQTriF::isRight() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 == 90 || a2 == 90 || a3 == 90) {
            return true;
        }
        return false;
    }

    inline bool ZQTriF::isObtuse() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 > 90 || a2 > 90 || a3 > 90) {
            return true;
        }
        return false;
    }

    inline bool ZQTriF::isIso() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 == a2 || a2 == a3 || a3 == a1) {
            return true;
        }
        return false;
    }

    inline bool ZQTriF::isEquilateral() const noexcept
    {
        qreal l12 = length12(), l13 = length13(), l23 = length23();

        qreal a1 = 180/M_PI * qAcos(qPow(l23, 2) - qPow(l12, 2) - qPow(l13, 2) + 2 * l12 * l13);
        qreal a2 = 180/M_PI * qAcos(qPow(l13, 2) - qPow(l12, 2) - qPow(l23, 2) + 2 * l12 * l23);        
        qreal a3 = 180/M_PI * qAcos(qPow(l12, 2) - qPow(l13, 2) - qPow(l23, 2) + 2 * l13 * l23);
        if (a1 == 60 && a2 == 60 && a3 == 60) {
            return true;
        }
        return false;
    }

    constexpr inline bool operator==(const ZQTriF &r1, const ZQTriF &r2) noexcept
    {
        return qFuzzyCompare(r1.x1p, r2.x1p) && qFuzzyCompare(r1.x2p, r2.x2p) &&
                qFuzzyCompare(r1.y1p, r2.y1p) && qFuzzyCompare(r1.y2p, r2.y2p) &&
                qFuzzyCompare(r1.x3p, r2.x3p) && qFuzzyCompare(r1.y3p, r2.y3p) && qFuzzyCompare(r1.a, r2.a);
    }

    constexpr inline bool operator!=(const ZQTriF &r1, const ZQTriF &r2) noexcept
    {
        return !(r1 == r2);
    }

    inline ZQTri ZQTriF::toTri() const noexcept
    {
        return ZQTri(QPoint(qRound(x1p), qRound(y1p)), QPoint(qRound(x2p), qRound(y2p)), QPoint(qRound(x3p), qRound(y3p)), qRound(a));
    }

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug, const ZQTriF &);
    #endif

}

#endif
