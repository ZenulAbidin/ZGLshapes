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

#ifndef Z_QELLIPSE_H
#define Z_QELLIPSE_H

#define _USE_MATH_DEFINES
#include <tgmath.h>

#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include "z_base.h"

namespace z_qtshapes {

    /*
     * It has been found that an ellipse can be made from the same dimension parameters
     * as rectangles. They can be fully described by coordinates of a rectangle.
     */
    class ZQEllipse {
    public:
        constexpr ZQEllipse() noexcept : x1(0), y1(0), x2(-1), y2(-1), a(0) {}
        constexpr ZQEllipse(const ZQEllipse &topleft, const ZQEllipse &bottomright) noexcept;
        constexpr ZQEllipse(const ZQEllipse &topleft, const ZQEllipse &bottomright, int angle) noexcept;
        constexpr ZQEllipse(const ZQEllipse &topleft, const ZQEllipse &size) noexcept;
        constexpr ZQEllipse(const ZQEllipse &topleft, const ZQEllipse &size, int angle) noexcept;
        constexpr ZQEllipse(int left, int top, int width, int height) noexcept;
        constexpr ZQEllipse(int left, int top, int width, int height, int angle) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        constexpr inline bool isValid() const noexcept;

        constexpr inline int left() const noexcept;
        constexpr inline int top() const noexcept;
        constexpr inline int right() const noexcept;
        constexpr inline int bottom() const noexcept;
        void normalize() const noexcept;
        ZQEllipse normalized() const noexcept;

        constexpr inline int x() const noexcept;
        constexpr inline int y() const noexcept;
        constexpr inline int angle() const noexcept;
        constexpr inline qreal angleRadians() const noexcept;
        inline void setLeft(int pos) noexcept;
        inline void setTop(int pos) noexcept;
        inline void setRight(int pos) noexcept;
        inline void setBottom(int pos) noexcept;
        inline void setX(int x) noexcept;
        inline void setY(int y) noexcept;
        inline void setAngle(int a) noexcept;
        inline void setAngleRadians(qreal a) noexcept;

        inline void setTopLeft(const QPointF &p) noexcept;
        inline void setBottomRight(const QPointF &p) noexcept;
        inline void setTopRight(const QPointF &p) noexcept;
        inline void setBottomLeft(const QPointF &p) noexcept;

        constexpr inline QPoint topLeft() const noexcept;
        constexpr inline QPoint bottomRight() const noexcept;
        constexpr inline QPoint topRight() const noexcept;
        constexpr inline QPoint bottomLeft() const noexcept;
        constexpr inline QPoint center() const noexcept;

        inline void moveLeft(qreal pos) noexcept;
        inline void moveTop(qreal pos) noexcept;
        inline void moveRight(qreal pos) noexcept;
        inline void moveBottom(qreal pos) noexcept;
        inline void moveTopLeft(const QPoint &p) noexcept;
        inline void moveBottomRight(const QPoint &p) noexcept;
        inline void moveTopRight(const QPoint &p) noexcept;
        inline void moveBottomLeft(const QPoint &p) noexcept;
        inline void moveCenter(const QPoint &p) noexcept;

        inline void translate(int dx, int dy) noexcept;
        inline void translate(const QPoint &p) noexcept;
        constexpr inline ZQEllipse translated(int dx, int dy) const noexcept;
        constexpr inline ZQEllipse translated(const QPoint &p) const noexcept;
        constexpr inline ZQEllipse transposed() const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQEllipse rotated(int da) noexcept;
        constexpr inline ZQEllipse rotatedRadians(qreal da) noexcept;

        inline int normalizedAngle(int a) noexcept;

        inline void moveTo(int x, int t) noexcept;
        inline void moveTo(const QPoint &p) noexcept;

        inline void getEllipse(int x, int y, int w, int h) noexcept;
        inline void getEllipse(int *x, int *y, int *w, int *h) const;

        inline void setCoords(int x1, int y1, int x2, int y2) noexcept;
        inline void setCoords(int xp1, int yp1, int xp2, int yp2, int angle) noexcept;
        inline void getCoords(int *x1, int *y1, int *x2, qreal *y2) const;
        inline void getCoords(int *xp1, int *yp1, int *xp2, int *yp2, int *angle) const;
        inline void getCoordsRadians(int *xp1, int *yp1, int *xp2, int *yp2, qreal *angle) const;

        inline void adjust(int x1, int y1, int x2, int y2) noexcept;
        inline void adjust(int dx1, int dy1, int dx2, int dy2, int angle) noexcept;
        inline void adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) noexcept;
        constexpr inline ZQEllipse adjusted(int x1, int y1, int x2, int y2) const noexcept;
        constexpr inline ZQEllipse adjusted(int xp1, int yp1, int xp2, int yp2, int angle) const noexcept;
        constexpr inline ZQEllipse adjustedRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) const noexcept;

        constexpr inline QSize size() const noexcept;
        constexpr inline int width() const noexcept;
        constexpr inline int height() const noexcept;
        inline void setWidth(int w) noexcept;
        inline void setHeight(int h) noexcept;
        inline void setSize(const QSize &s) noexcept;

        QPainterPath operator|(const ZQEllipse &r) const noexcept;
        QPainterPath operator&(const ZQEllipse &r) const noexcept;

        bool contains(const ZQEllipse &r, bool proper = false) const noexcept;
        bool contains(const QPoint &p, bool proper=false) const noexcept;
        inline bool contains(int x, int y) const noexcept;
        inline bool contains(int x, int y, bool proper) const noexcept;
        inline QPainterPath united(const ZQEllipse &other) const noexcept;
        inline QPainterPath intersected(const ZQEllipse &other) const noexcept;
        bool intersects(const ZQEllipse &r) const noexcept;

        constexpr inline ZQEllipse marginsAdded(const QMargins &margins) const noexcept;
        constexpr inline ZQEllipse marginsRemoved(const QMargins &margins) const noexcept;
        inline ZQEllipse &operator+=(const QMargins &margins) noexcept;
        inline ZQEllipse &operator-=(const QMargins &margins) noexcept;

        constexpr inline ZQEllipse toEllipse() const noexcept;
        ZQEllipse toAlignedEllipse() const noexcept;

        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 mat, const QPointF &ref) const noexcept;
        constexpr inline QString toString() const noexcept;

        friend constexpr inline bool operator==(const ZQEllipse &, const ZQEllipse &) noexcept;
        friend constexpr inline bool operator!=(const ZQEllipse &, const ZQEllipse &) noexcept;


    private:
        qreal x1;
        qreal y1;
        qreal x2;
        qreal y2;
        qreal a;
    };


    constexpr inline bool operator==(const ZQEllipse &, const ZQEllipse &) noexcept;
    constexpr inline bool operator!=(const ZQEllipse &, const ZQEllipse &) noexcept;

    /*****************************************************************************
      ZQEllipse stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQEllipse &);
    QDataStream &operator>>(QDataStream &, ZQEllipse &);
    #endif

    /*****************************************************************************
      ZQEllipse inline member functions
     *****************************************************************************/

    constexpr inline ZQEllipse::ZQEllipse(int aleft, int atop, int awidth, int aheight) noexcept
        : x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1), a(0) {}

    constexpr inline ZQEllipse::ZQEllipse(int aleft, int atop, int awidth, int aheight, int angle) noexcept
        : x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1), a(normalizedAngle(angle)) {}

    constexpr inline ZQEllipse::ZQEllipse(const QPoint &atopLeft, const QPoint &abottomRight) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()), y2(abottomRight.y()), a(0) {}

    constexpr inline ZQEllipse::ZQEllipse(const QPoint &atopLeft, const QPoint &abottomRight, int angle) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()), y2(abottomRight.y()), a(normalizedAngle(angle)) {}

    constexpr inline ZQEllipse::ZQEllipse(const QPoint &atopLeft, const QSize &asize) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x()+asize.width() - 1), y2(atopLeft.y()+asize.height() - 1) {}

    constexpr inline ZQEllipse::ZQEllipse(const QPoint &atopLeft, const QSize &asize, int angle) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x()+asize.width() - 1), y2(atopLeft.y()+asize.height() - 1), a(normalizedAngle(angle)) {}

    constexpr inline bool ZQEllipse::isNull() const noexcept
    { return x2 == x1 - 1 && y2 == y1 - 1 && a == 0; }

    constexpr inline bool ZQEllipse::isEmpty() const noexcept
    { return x1 > x2 || y1 > y2; }

    constexpr inline bool ZQEllipse::isValid() const noexcept
    { return x1 <= x2 && y1 <= y2; }

    constexpr inline int ZQEllipse::left() const noexcept
    { return x1; }

    constexpr inline int ZQEllipse::top() const noexcept
    { return y1; }

    constexpr inline int ZQEllipse::right() const noexcept
    { return x2; }

    constexpr inline int ZQEllipse::bottom() const noexcept
    { return y2; }

    constexpr inline int ZQEllipse::x() const noexcept
    { return x1; }

    constexpr inline int ZQEllipse::y() const noexcept
    { return y1; }

    constexpr inline int ZQEllipse::angle() const noexcept
    { return angle; }

    constexpr inline qreal ZQEllipse::angleRadians() const noexcept
    { return M_PI/180 * angle; }

    inline void ZQEllipse::setLeft(int pos) noexcept
    { x1 = pos; }

    inline void ZQEllipse::setTop(int pos) noexcept
    { y1 = pos; }

    inline void ZQEllipse::setRight(int pos) noexcept
    { x2 = pos; }

    inline void ZQEllipse::setBottom(int pos) noexcept
    { y2 = pos; }

    inline void ZQEllipse::setTopLeft(const QPoint &p) noexcept
    { x1 = p.x(); y1 = p.y(); }

    inline void ZQEllipse::setBottomRight(const QPoint &p) noexcept
    { x2 = p.x(); y2 = p.y(); }

    inline void ZQEllipse::setTopRight(const QPoint &p) noexcept
    { x2 = p.x(); y1 = p.y(); }

    inline void ZQEllipse::setBottomLeft(const QPoint &p) noexcept
    { x1 = p.x(); y2 = p.y(); }

    inline void ZQEllipse::setX(int ax) noexcept
    { x1 = ax; }

    inline void ZQEllipse::setY(int ay) noexcept
    { y1 = ay; }

    inline void ZQEllipse::setAngle(int aangle) noexcept
    { a = normalizedAngle(aangle); }

    inline void ZQEllipse::setAngleRadians(qreal aangle) noexcept
    { a = normalizedAngle((int) (180/M_PI * aangle)); }

    constexpr inline QPoint ZQEllipse::topLeft() const noexcept
    { return QPoint(x1, y1); }

    constexpr inline QPoint ZQEllipse::bottomRight() const noexcept
    { return QPoint(x2, y2); }

    constexpr inline QPoint ZQEllipse::topRight() const noexcept
    { return QPoint(x2, y1); }

    constexpr inline QPoint ZQEllipse::bottomLeft() const noexcept
    { return QPoint(x1, y2); }

    constexpr inline QPoint ZQEllipse::center() const noexcept
    { return QPoint(int((qint64(x1)+x2)/2), int((qint64(y1)+y2)/2)); } // cast avoids overflow on addition

    constexpr inline int ZQEllipse::width() const noexcept
    { return  x2 - x1 + 1; }

    constexpr inline int ZQEllipse::height() const noexcept
    { return  y2 - y1 + 1; }

    constexpr inline QSize ZQEllipse::size() const noexcept
    { return QSize(width(), height()); }

    inline void ZQEllipse::translate(int dx, int dy) noexcept
    {
        x1 += dx;
        y1 += dy;
        x2 += dx;
        y2 += dy;
    }

    inline void ZQEllipse::translate(const QPoint &p) noexcept
    {
        x1 += p.x();
        y1 += p.y();
        x2 += p.x();
        y2 += p.y();
    }

    constexpr inline ZQEllipse ZQEllipse::translated(int dx, int dy) const noexcept
    { return ZQEllipse(QPoint(x1 + dx, y1 + dy), QPoint(x2 + dx, y2 + dy)); }

    constexpr inline ZQEllipse ZQEllipse::translated(const QPoint &p) const noexcept
    { return ZQEllipse(QPoint(x1 + p.x(), y1 + p.y()), QPoint(x2 + p.x(), y2 + p.y())); }

    constexpr inline ZQEllipse ZQEllipse::transposed() const noexcept
    { return ZQEllipse(topLeft(), size().transposed()); }

    inline void ZQEllipse::rotate(int angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQEllipse::rotateRadians(qreal angle) const noexcept
    { a += (int) (180/M_PI * normalizedAngle(angle)); }

    constexpr inline ZQEllipse ZQEllipse::rotate(int angle) const noexcept
    { return ZQEllipse(x1, y1, x2, y2, a + normalizedAngle(angle)); }

    constexpr inline ZQEllipse ZQEllipse::rotateRadians(qreal angle) const noexcept
    { return ZQEllipse(x1, y1, x2, y2, a + (int) (180/M_PI * normalizedAngle(angle))); }


    inline int ZQEllipse::normalizedAngle(int a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle >= 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQEllipse::moveTo(int ax, int ay) noexcept
    {
        x2 += ax - x1;
        y2 += ay - y1;
        x1 = ax;
        y1 = ay;
    }

    inline void ZQEllipse::moveTo(const QPoint &p) noexcept
    {
        x2 += p.x() - x1;
        y2 += p.y() - y1;
        x1 = p.x();
        y1 = p.y();
    }

    inline void ZQEllipse::moveLeft(int pos) noexcept
    { x2 += (pos - x1); x1 = pos; }

    inline void ZQEllipse::moveTop(int pos) noexcept
    { y2 += (pos - y1); y1 = pos; }

    inline void ZQEllipse::moveRight(int pos) noexcept
    {
        x1 += (pos - x2);
        x2 = pos;
    }

    inline void ZQEllipse::moveBottom(int pos) noexcept
    {
        y1 += (pos - y2);
        y2 = pos;
    }

    inline void ZQEllipse::moveTopLeft(const QPoint &p) noexcept
    {
        moveLeft(p.x());
        moveTop(p.y());
    }

    inline void ZQEllipse::moveBottomRight(const QPoint &p) noexcept
    {
        moveRight(p.x());
        moveBottom(p.y());
    }

    inline void ZQEllipse::moveTopRight(const QPoint &p) noexcept
    {
        moveRight(p.x());
        moveTop(p.y());
    }

    inline void ZQEllipse::moveBottomLeft(const QPoint &p) noexcept
    {
        moveLeft(p.x());
        moveBottom(p.y());
    }

    inline void ZQEllipse::moveCenter(const QPoint &p) noexcept
    {
        int w = x2 - x1;
        int h = y2 - y1;
        x1 = p.x() - w/2;
        y1 = p.y() - h/2;
        x2 = x1 + w;
        y2 = y1 + h;
    }

    inline void ZQEllipse::getEllipse(int *ax, int *ay, int *aw, int *ah) const
    {
        *ax = x1;
        *ay = y1;
        *aw = x2 - x1 + 1;
        *ah = y2 - y1 + 1;
    }

    inline void ZQEllipse::setEllipse(int ax, int ay, int aw, int ah) noexcept
    {
        x1 = ax;
        y1 = ay;
        x2 = (ax + aw - 1);
        y2 = (ay + ah - 1);
    }

    inline void ZQEllipse::getCoords(int *xp1, int *yp1, int *xp2, int *yp2) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
    }

    inline void ZQEllipse::getCoords(int *xp1, int *yp1, int *xp2, int *yp2, int *angle) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
        *angle = a;
    }

    inline void ZQEllipse::getCoordsRadians(int *xp1, int *yp1, int *xp2, int *yp2, qreal *angle) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
        *angle = M_PI/180 * a;
    }

    inline void ZQEllipse::setCoords(int xp1, int yp1, int xp2, int yp2) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
    }

    inline void ZQEllipse::setCoords(int xp1, int yp1, int xp2, int yp2, int angle) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
        a = angle;
    }

    inline void ZQEllipse::setCoordsRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
        a = normalizedAngle((int) (180/M_PI * angle));
    }


    constexpr inline ZQEllipse ZQEllipse::adjusted(int xp1, int yp1, int xp2, int yp2) const noexcept
    { return ZQEllipse(QPoint(x1 + xp1, y1 + yp1), QPoint(x2 + xp2, y2 + yp2)); }

    constexpr inline ZQEllipse ZQEllipse::adjusted(int xp1, int yp1, int xp2, int yp2, int angle) const noexcept
    { return ZQEllipse(QPoint(x1 + xp1, y1 + yp1), QPoint(x2 + xp2, y2 + yp2), normalizedAngle(angle)); }

    constexpr inline ZQEllipse ZQEllipse::adjustedRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) const noexcept
    { return ZQEllipse(QPoint(x1 + xp1, y1 + yp1), QPoint(x2 + xp2, y2 + yp2), normalizedAngle((int) (180/M_PI * angle))); }


    inline void ZQEllipse::adjust(int dx1, int dy1, int dx2, int dy2) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2;
        y2 += dy2;
    }

    inline void ZQEllipse::adjust(int dx1, int dy1, int dx2, int dy2, int angle) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2;
        y2 += dy2;
        a += normalizedAngle(angle);
    }

    inline void ZQEllipse::adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2;
        y2 += dy2;
        a += normalizedAngle((int) (180/M_PI * angle));
    }

    inline void ZQEllipse::setWidth(int w) noexcept
    { x2 = (x1 + w - 1); }

    inline void ZQEllipse::setHeight(int h) noexcept
    { y2 = (y1 + h - 1); }

    inline void ZQEllipse::setSize(const QSize &s) noexcept
    {
        x2 = (s.width()  + x1 - 1);
        y2 = (s.height() + y1 - 1);
    }

    inline bool ZQEllipse::contains(int ax, int ay, bool aproper) const noexcept
    {
        return contains(QPoint(ax, ay), aproper);
    }

    inline bool ZQEllipse::contains(int ax, int ay) const noexcept
    {
        return contains(QPoint(ax, ay), false);
    }

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQEllipse(%1,%2 size %3x%4 %5 degrees)").arg(x1, y1, width(), height(), a));
    }

    inline QPainterPath ZQEllipse::intersected(const ZQEllipse &other) const noexcept
    {
        return *this & other;
    }

    inline QPainterPath ZQEllipse::united(const ZQEllipse &r) const noexcept
    {
        return *this | r;
    }

    constexpr inline bool operator==(const ZQEllipse &r1, const ZQEllipse &r2) noexcept
    {
        return r1.x1==r2.x1 && r1.x2==r2.x2 && r1.y1==r2.y1 && r1.y2==r2.y2
               && r1.a == r2.a;
    }

    constexpr inline bool operator!=(const ZQEllipse &r1, const ZQEllipse &r2) noexcept
    {
        return r1.x1!=r2.x1 || r1.x2!=r2.x2 || r1.y1!=r2.y1 || r1.y2!=r2.y2;
    }

    constexpr inline ZQEllipse operator+(const ZQEllipse &rectangle, const QMargins &margins) noexcept
    {
        return ZQEllipse(QPoint(rectangle.left() - margins.left(), rectangle.top() - margins.top()),
                     QPoint(rectangle.right() + margins.right(), rectangle.bottom() + margins.bottom()));
    }

    constexpr inline ZQEllipse operator+(const QMargins &margins, const ZQEllipse &rectangle) noexcept
    {
        return ZQEllipse(QPoint(rectangle.left() - margins.left(), rectangle.top() - margins.top()),
                     QPoint(rectangle.right() + margins.right(), rectangle.bottom() + margins.bottom()));
    }

    constexpr inline ZQEllipse operator-(const ZQEllipse &lhs, const QMargins &rhs) noexcept
    {
        return ZQEllipse(QPoint(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                     QPoint(lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom()));
    }

    constexpr inline ZQEllipse ZQEllipse::marginsAdded(const QMargins &margins) const noexcept
    {
        return ZQEllipse(QPoint(x1 - margins.left(), y1 - margins.top()),
                     QPoint(x2 + margins.right(), y2 + margins.bottom()));
    }

    constexpr inline ZQEllipse ZQEllipse::marginsRemoved(const QMargins &margins) const noexcept
    {
        return ZQEllipse(QPoint(x1 + margins.left(), y1 + margins.top()),
                     QPoint(x2 - margins.right(), y2 - margins.bottom()));
    }

    inline ZQEllipse &ZQEllipse::operator+=(const QMargins &margins) noexcept
    {
        *this = marginsAdded(margins);
        return *this;
    }

    inline ZQEllipse &ZQEllipse::operator-=(const QMargins &margins) noexcept
    {
        *this = marginsRemoved(margins);
        return *this;
    }

    #ifndef QT_NO_DEBUG_STREAM
    Q_CORE_EXPORT QDebug operator<<(QDebug, const ZQEllipse &);
    #endif




    class ZQEllipseF {
    public:
        constexpr ZQEllipseF() noexcept : xp(0.), yp(0.), w(0.), h(0.) a(0.) {}
        constexpr ZQEllipseF(const QPointF &topleft, const QSizeF &size) noexcept;
        constexpr ZQEllipseF(const QPointF &topleft, const QSizeF &size, qreal angle) noexcept;
        constexpr ZQEllipseF(const QPointF &topleft, const QPointF &bottomRight) noexcept;
        constexpr ZQEllipseF(const QPointF &topleft, const QPointF &bottomRight, qreal angle) noexcept;
        constexpr ZQEllipseF(qreal left, qreal top, qreal width, qreal height) noexcept;
        constexpr ZQEllipseF(qreal left, qreal top, qreal width, qreal height, qreal angle) noexcept;
        constexpr ZQEllipseF(const ZQEllipse &rect) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        constexpr inline bool isValid() const noexcept;
        void normalize() const noexcept;
        ZQEllipseF normalized() const noexcept;

        constexpr inline qreal left() const noexcept { return xp; }
        constexpr inline qreal top() const noexcept { return yp; }
        constexpr inline qreal right() const noexcept { return xp + w; }
        constexpr inline qreal bottom() const noexcept { return yp + h; }

        constexpr inline qreal x() const noexcept;
        constexpr inline qreal y() const noexcept;
        constexpr inline qreal angle() const noexcept;
        constexpr inline qreal angleRadians() const noexcept;
        inline void setLeft(qreal pos) noexcept;
        inline void setTop(qreal pos) noexcept;
        inline void setRight(qreal pos) noexcept;
        inline void setBottom(qreal pos) noexcept;
        inline void setX(qreal pos) noexcept { setLeft(pos); }
        inline void setY(qreal pos) noexcept { setTop(pos); }
        inline void setAngle(qreal angle) noexcept { a = angle; }
        inline void setAngleRadians(qreal angle) noexcept { a = 180/M_PI * angle; }

        constexpr inline QPointF topLeft() const noexcept { return QPointF(xp, yp); }
        constexpr inline QPointF bottomRight() const noexcept { return QPointF(xp+w, yp+h); }
        constexpr inline QPointF topRight() const noexcept { return QPointF(xp+w, yp); }
        constexpr inline QPointF bottomLeft() const noexcept { return QPointF(xp, yp+h); }
        constexpr inline QPointF center() const noexcept;

        inline void setTopLeft(const QPointF &p) noexcept;
        inline void setBottomRight(const QPointF &p) noexcept;
        inline void setTopRight(const QPointF &p) noexcept;
        inline void setBottomLeft(const QPointF &p) noexcept;

        inline void moveLeft(qreal pos) noexcept;
        inline void moveTop(qreal pos) noexcept;
        inline void moveRight(qreal pos) noexcept;
        inline void moveBottom(qreal pos) noexcept;
        inline void moveTopLeft(const QPointF &p) noexcept;
        inline void moveBottomRight(const QPointF &p) noexcept;
        inline void moveTopRight(const QPointF &p) noexcept;
        inline void moveBottomLeft(const QPointF &p) noexcept;
        inline void moveCenter(const QPointF &p) noexcept;

        inline void translate(qreal dx, qreal dy) noexcept;
        inline void translate(const QPointF &p) noexcept;

        constexpr inline ZQEllipseF translated(qreal dx, qreal dy) const noexcept;
        constexpr inline ZQEllipseF translated(const QPointF &p) const noexcept;

        constexpr inline ZQEllipseF transposed() const noexcept;


        inline void rotate(qreal da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQEllipseF rotated(qreal da) noexcept;
        constexpr inline ZQEllipseF rotatedRadians(qreal da) noexcept;

        inline qreal normalizedAngle(qreal a) noexcept;

        inline void moveTo(qreal x, qreal y) noexcept;
        inline void moveTo(const QPointF &p) noexcept;

        inline void setEllipse(qreal x, qreal y, qreal w, qreal h) noexcept;
        inline void getEllipse(qreal *x, qreal *y, qreal *w, qreal *h) const;

        inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void setCoordsRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const;
        inline void getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const;
        inline void getCoordsRadians(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const;

        inline void adjust(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void adjustRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        constexpr inline ZQEllipseF adjusted(qreal x1, qreal y1, qreal x2, qreal y2) const noexcept;
        constexpr inline ZQEllipseF adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept;
        constexpr inline ZQEllipseF adjustedRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept;

        constexpr inline QSizeF size() const noexcept;
        constexpr inline qreal width() const noexcept;
        constexpr inline qreal height() const noexcept;
        inline void setWidth(qreal w) noexcept;
        inline void setHeight(qreal h) noexcept;
        inline void setSize(const QSizeF &s) noexcept;

        QPainterPath operator|(const ZQEllipseF &r) const noexcept;
        QPainterPath operator&(const ZQEllipseF &r) const noexcept;

        bool contains(const ZQEllipseF &r) const noexcept;
        bool contains(const QPointF &p) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQEllipseF &other) const noexcept;
        inline QPainterPath intersected(const ZQEllipseF &other) const noexcept;
        bool intersects(const ZQEllipseF &r) const noexcept;

        constexpr inline ZQEllipseF marginsAdded(const QMarginsF &margins) const noexcept;
        constexpr inline ZQEllipseF marginsRemoved(const QMarginsF &margins) const noexcept;
        inline ZQEllipseF &operator+=(const QMarginsF &margins) noexcept;
        inline ZQEllipseF &operator-=(const QMarginsF &margins) noexcept;

        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        constexpr inline QString toString() const noexcept;

        friend constexpr inline bool operator==(const ZQEllipseF &, const ZQEllipseF &) noexcept;
        friend constexpr inline bool operator!=(const ZQEllipseF &, const ZQEllipseF &) noexcept;

    private:
        qreal xp;
        qreal yp;
        qreal w;
        qreal h;
        qreal a;
    };



    constexpr inline bool operator==(const ZQEllipseF &, const ZQEllipseF &) noexcept;
    constexpr inline bool operator!=(const ZQEllipseF &, const ZQEllipseF &) noexcept;


    /*****************************************************************************
      ZQEllipseF stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQEllipseF &);
    QDataStream &operator>>(QDataStream &, ZQEllipseF &);
    #endif

    /*****************************************************************************
      ZQEllipseF inline member functions
     *****************************************************************************/

    constexpr inline ZQEllipseF::ZQEllipseF(qreal aleft, qreal atop, qreal awidth, qreal aheight) noexcept
        : xp(aleft), yp(atop), w(awidth), h(aheight)
    {
    }


    constexpr inline ZQEllipseF::ZQEllipseF(qreal aleft, qreal atop, qreal awidth, qreal aheight, qreal angle) noexcept
        : xp(aleft), yp(atop), w(awidth), h(aheight), a(normalizedAngle(angle))
    {
    }


    constexpr inline ZQEllipseF::ZQEllipseF(const QPointF &atopLeft, const QSizeF &asize) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.width()), h(asize.height())
    {
    }

    constexpr inline ZQEllipseF::ZQEllipseF(const QPointF &atopLeft, const QSizeF &asize, qreal angle) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.width()), h(asize.height()), a(normalizedAngle(angle))
    {
    }


    constexpr inline ZQEllipseF::ZQEllipseF(const QPointF &atopLeft, const QPointF &abottomRight) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()), h(abottomRight.y() - atopLeft.y())
    {
    }


    constexpr inline ZQEllipseF::ZQEllipseF(const QPointF &atopLeft, const QPointF &abottomRight, qreal angle) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()), h(abottomRight.y() - atopLeft.y()),
            a(normalizedAngle(angle))
    {
    }

    constexpr inline ZQEllipseF::ZQEllipseF(const ZQEllipse &r) noexcept
        : xp(r.x()), yp(r.y()), w(r.width()), h(r.height())
    {
    }

    //QT_WARNING_PUSH
    //QT_WARNING_DISABLE_GCC("-Wfloat-equal")
    // just compile with -Wno-float-equal

    constexpr inline bool ZQEllipseF::isNull() const noexcept
    { return w == 0. && h == 0.; }

    constexpr inline bool ZQEllipseF::isEmpty() const noexcept
    { return w <= 0. || h <= 0.; }

    //QT_WARNING_POP

    constexpr inline bool ZQEllipseF::isValid() const noexcept
    { return w > 0. && h > 0.; }

    constexpr inline qreal ZQEllipseF::x() const noexcept
    { return xp; }

    constexpr inline qreal ZQEllipseF::y() const noexcept
    { return yp; }

    constexpr inline qreal ZQEllipseF::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQEllipseF::angleRadians() const noexcept
    { return M_PI/180 * a; }

    inline void ZQEllipseF::setLeft(qreal pos) noexcept
    { qreal diff = pos - xp; xp += diff; w -= diff; }

    inline void ZQEllipseF::setRight(qreal pos) noexcept
    { w = pos - xp; }

    inline void ZQEllipseF::setTop(qreal pos) noexcept
    { qreal diff = pos - yp; yp += diff; h -= diff; }

    inline void ZQEllipseF::setBottom(qreal pos) noexcept
    { h = pos - yp; }

    inline void ZQEllipseF::setTopLeft(const QPointF &p) noexcept
    { setLeft(p.x()); setTop(p.y()); }

    inline void ZQEllipseF::setTopRight(const QPointF &p) noexcept
    { setRight(p.x()); setTop(p.y()); }

    inline void ZQEllipseF::setBottomLeft(const QPointF &p) noexcept
    { setLeft(p.x()); setBottom(p.y()); }

    inline void ZQEllipseF::setBottomRight(const QPointF &p) noexcept
    { setRight(p.x()); setBottom(p.y()); }

    constexpr inline QPointF ZQEllipseF::center() const noexcept
    { return QPointF(xp + w/2, yp + h/2); }

    inline void ZQEllipseF::moveLeft(qreal pos) noexcept
    { xp = pos; }

    inline void ZQEllipseF::moveTop(qreal pos) noexcept
    { yp = pos; }

    inline void ZQEllipseF::moveRight(qreal pos) noexcept
    { xp = pos - w; }

    inline void ZQEllipseF::moveBottom(qreal pos) noexcept
    { yp = pos - h; }

    inline void ZQEllipseF::moveTopLeft(const QPointF &p) noexcept
    { moveLeft(p.x()); moveTop(p.y()); }

    inline void ZQEllipseF::moveTopRight(const QPointF &p) noexcept
    { moveRight(p.x()); moveTop(p.y()); }

    inline void ZQEllipseF::moveBottomLeft(const QPointF &p) noexcept
    { moveLeft(p.x()); moveBottom(p.y()); }

    inline void ZQEllipseF::moveBottomRight(const QPointF &p) noexcept
    { moveRight(p.x()); moveBottom(p.y()); }

    inline void ZQEllipseF::moveCenter(const QPointF &p) noexcept
    { xp = p.x() - w/2; yp = p.y() - h/2; }

    constexpr inline qreal ZQEllipseF::width() const noexcept
    { return w; }

    constexpr inline qreal ZQEllipseF::height() const noexcept
    { return h; }

    constexpr inline QSizeF ZQEllipseF::size() const noexcept
    { return QSizeF(w, h); }

    inline void ZQEllipseF::translate(qreal dx, qreal dy) noexcept
    {
        xp += dx;
        yp += dy;
    }

    inline void ZQEllipseF::translate(const QPointF &p) noexcept
    {
        xp += p.x();
        yp += p.y();
    }

    inline void ZQEllipseF::rotate(qreal angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQEllipseF::rotateRadians(qreal angle) const noexcept
    { a += (normalizedAngle(180/M_PI * angle)); }

    constexpr inline ZQEllipseF ZQEllipseF::rotate(qreal angle) const noexcept
    { return ZQEllipse(x1, y1, x2, y2, a + normalizedAngle(angle)); }

    constexpr inline ZQEllipseF ZQEllipseF::rotateRadians(qreal angle) const noexcept
    { return ZQEllipse(x1, y1, x2, y2, a + normalizedAngle((180/M_PI * angle))); }

    inline qreal ZQEllipseF::normalizedAngle(qreal a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle >= 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQEllipseF::moveTo(qreal ax, qreal ay) noexcept
    {
        xp = ax;
        yp = ay;
    }

    inline void ZQEllipseF::moveTo(const QPointF &p) noexcept
    {
        xp = p.x();
        yp = p.y();
    }

    constexpr inline ZQEllipseF ZQEllipseF::translated(qreal dx, qreal dy) const noexcept
    { return ZQEllipseF(xp + dx, yp + dy, w, h); }

    constexpr inline ZQEllipseF ZQEllipseF::translated(const QPointF &p) const noexcept
    { return ZQEllipseF(xp + p.x(), yp + p.y(), w, h); }

    constexpr inline ZQEllipseF ZQEllipseF::transposed() const noexcept
    { return ZQEllipseF(topLeft(), size().transposed()); }

    inline void ZQEllipseF::getEllipse(qreal *ax, qreal *ay, qreal *aaw, qreal *aah) const
    {
        *ax = this->xp;
        *ay = this->yp;
        *aaw = this->w;
        *aah = this->h;
    }

    inline void ZQEllipseF::getEllipse(qreal *ax, qreal *ay, qreal *aaw, qreal *aah, qreal *aaa) const
    {
        *ax = this->xp;
        *ay = this->yp;
        *aaw = this->w;
        *aah = this->h;
        *aaa = this->a;
    }

    inline void ZQEllipseF::setEllipse(qreal ax, qreal ay, qreal aaw, qreal aah) noexcept
    {
        this->xp = ax;
        this->yp = ay;
        this->w = aaw;
        this->h = aah;
    }

    inline void ZQEllipseF::setEllipse(qreal ax, qreal ay, qreal aaw, qreal aah, qreal aaa) noexcept
    {
        this->xp = ax;
        this->yp = ay;
        this->w = aaw;
        this->h = aah;
        this->a = aaa;
    }


    inline void ZQEllipseF::getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
    }

    inline void ZQEllipseF::getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
        *angle = a;
    }

    inline void ZQEllipseF::getCoordsRadians(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
        *angle = M_PI/180 * a;
    }

    inline void ZQEllipseF::setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
    }

    inline void ZQEllipseF::setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
        a = normalizedAngle(angle);
    }

    inline void ZQEllipseF::setCoordsRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
        a = normalizedAngle(180/M_PI * angle);
    }

    inline void ZQEllipseF::adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
    { xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1; }

    inline void ZQEllipseF::adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    { xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1; angle = normalizedAngle(a + angle); }

    inline void ZQEllipseF::adjustRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    { xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1; angle = normalizedAngle(a + 180/M_PI * angle); }

    constexpr inline ZQEllipseF ZQEllipseF::adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2) const noexcept
    { return ZQEllipseF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1); }

    constexpr inline ZQEllipseF ZQEllipseF::adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept
    { return ZQEllipseF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1, normalizedAngle(a + angle)); }

    constexpr inline ZQEllipseF ZQEllipseF::adjustedRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept
    { return ZQEllipseF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1, normalizedAngle(a + 180/M_PI * angle)); }

    inline void ZQEllipseF::setWidth(qreal aw) noexcept
    { this->w = aw; }

    inline void ZQEllipseF::setHeight(qreal ah) noexcept
    { this->h = ah; }

    inline void ZQEllipseF::setSize(const QSizeF &s) noexcept
    {
        w = s.width();
        h = s.height();
    }

    inline bool ZQEllipseF::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPointF(ax, ay));
    }

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQEllipseF(%1,%2 size %3x%4 %5 degrees)").arg(xp, yp, w, h, a));
    }

    inline QPainterPath ZQEllipseF::intersected(const ZQEllipseF &r) const noexcept
    {
        return *this & r;
    }

    inline QPainterPath ZQEllipseF::united(const ZQEllipseF &r) const noexcept
    {
        return *this | r;
    }

    constexpr inline bool operator==(const ZQEllipseF &r1, const ZQEllipseF &r2) noexcept
    {
        return qFuzzyCompare(r1.xp, r2.xp) && qFuzzyCompare(r1.yp, r2.yp)
               && qFuzzyCompare(r1.w, r2.w) && qFuzzyCompare(r1.h, r2.h) 
               && qFuzzyCompare(r1.a, r2.a);
    }

    constexpr inline bool operator!=(const ZQEllipseF &r1, const ZQEllipseF &r2) noexcept
    {
        return !qFuzzyCompare(r1.xp, r2.xp) || !qFuzzyCompare(r1.yp, r2.yp)
               || !qFuzzyCompare(r1.w, r2.w) || !qFuzzyCompare(r1.h, r2.h);
    }

    constexpr inline ZQEllipse ZQEllipseF::toEllipse() const noexcept
    {
        return ZQEllipse(QPoint(qRound(xp), qRound(yp)), QPoint(qRound(xp + w) - 1, qRound(yp + h) - 1));
    }

    constexpr inline ZQEllipseF operator+(const ZQEllipseF &lhs, const QMarginsF &rhs) noexcept
    {
        return ZQEllipseF(QPointF(lhs.left() - rhs.left(), lhs.top() - rhs.top()),
                      QSizeF(lhs.width() + rhs.left() + rhs.right(), lhs.height() + rhs.top() + rhs.bottom()));
    }

    constexpr inline ZQEllipseF operator+(const QMarginsF &lhs, const ZQEllipseF &rhs) noexcept
    {
        return ZQEllipseF(QPointF(rhs.left() - lhs.left(), rhs.top() - lhs.top()),
                      QSizeF(rhs.width() + lhs.left() + lhs.right(), rhs.height() + lhs.top() + lhs.bottom()));
    }

    constexpr inline ZQEllipseF operator-(const ZQEllipseF &lhs, const QMarginsF &rhs) noexcept
    {
        return ZQEllipseF(QPointF(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                      QSizeF(lhs.width() - rhs.left() - rhs.right(), lhs.height() - rhs.top() - rhs.bottom()));
    }

    constexpr inline ZQEllipseF ZQEllipseF::marginsAdded(const QMarginsF &margins) const noexcept
    {
        return ZQEllipseF(QPointF(xp - margins.left(), yp - margins.top()),
                      QSizeF(w + margins.left() + margins.right(), h + margins.top() + margins.bottom()));
    }

    constexpr inline ZQEllipseF ZQEllipseF::marginsRemoved(const QMarginsF &margins) const noexcept
    {
        return ZQEllipseF(QPointF(xp + margins.left(), yp + margins.top()),
                      QSizeF(w - margins.left() - margins.right(), h - margins.top() - margins.bottom()));
    }

    inline ZQEllipseF &ZQEllipseF::operator+=(const QMarginsF &margins) noexcept
    {
        *this = marginsAdded(margins);
        return *this;
    }

    inline ZQEllipseF &ZQEllipseF::operator-=(const QMarginsF &margins) noexcept
    {
        *this = marginsRemoved(margins);
        return *this;
    }

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug, const ZQEllipseF &);
    #endif

}

#endif
