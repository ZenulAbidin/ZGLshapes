/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef Z_QRECT_H
#define Z_QRECT_H

#define _USE_MATH_DEFINES
#include <tgmath.h>

#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include "z_base.h"

namespace z_qtshapes {


    class ZQRect {
    public:
        constexpr ZQRect() noexcept : x1(0), y1(0), x2(-1), y2(-1), a(0) {}
        constexpr ZQRect(const QPoint &topleft, const QPoint &bottomright) noexcept;
        constexpr ZQRect(const QPoint &topleft, const QPoint &bottomright, int angle) noexcept;
        constexpr ZQRect(const QPoint &topleft, const QPoint &size) noexcept;
        constexpr ZQRect(const QPoint &topleft, const QPoint &size, int angle) noexcept;
        constexpr ZQRect(int left, int top, int width, int height) noexcept;
        constexpr ZQRect(int left, int top, int width, int height, int angle) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        constexpr inline bool isValid() const noexcept;

        constexpr inline int left() const noexcept;
        constexpr inline int top() const noexcept;
        constexpr inline int right() const noexcept;
        constexpr inline int bottom() const noexcept;
        void normalize() const noexcept;
        ZQRect normalized() const noexcept;

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
        constexpr inline ZQRect translated(int dx, int dy) const noexcept;
        constexpr inline ZQRect translated(const QPoint &p) const noexcept;
        constexpr inline ZQRect transposed() const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQRect rotated(int da) noexcept;
        constexpr inline ZQRect rotatedRadians(qreal da) noexcept;

        inline int normalizedAngle(int a) noexcept;

        inline void moveTo(int x, int t) noexcept;
        inline void moveTo(const QPoint &p) noexcept;

        inline void getRect(int x, int y, int w, int h) noexcept;
        inline void getRect(int *x, int *y, int *w, int *h) const;

        inline void setCoords(int x1, int y1, int x2, int y2) noexcept;
        inline void setCoords(int xp1, int yp1, int xp2, int yp2, int angle) noexcept;
        inline void setCoordsRadians(int xp1, int yp1, int xp2, int yp2, qreal *angle) const;
        inline void getCoords(int *x1, int *y1, int *x2, qreal *y2) const;
        inline void getCoords(int *xp1, int *yp1, int *xp2, int *yp2, int *angle) const;
        inline void getCoordsRadians(int *xp1, int *yp1, int *xp2, int *yp2, qreal *angle) const;

        inline void adjust(int x1, int y1, int x2, int y2) noexcept;
        inline void adjust(int dx1, int dy1, int dx2, int dy2, int angle) noexcept;
        inline void adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) noexcept;
        constexpr inline ZQRect adjusted(int x1, int y1, int x2, int y2) const noexcept;
        constexpr inline ZQRect adjusted(int xp1, int yp1, int xp2, int yp2, int angle) const noexcept;
        constexpr inline ZQRect adjustedRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) const noexcept;

        constexpr inline QSize size() const noexcept;
        constexpr inline int width() const noexcept;
        constexpr inline int height() const noexcept;
        inline void setWidth(int w) noexcept;
        inline void setHeight(int h) noexcept;
        inline void setSize(const QSize &s) noexcept;

        QPainterPath operator|(const ZQRect &r) const noexcept;
        QPainterPath operator&(const ZQRect &r) const noexcept;

        bool contains(const ZQRect &r, bool proper=false) const noexcept;
        bool contains(const QPoint &p, bool proper=false) const noexcept;
        inline bool contains(int x, int y) const noexcept;
        inline bool contains(int x, int y, bool proper) const noexcept;
        inline QPainterPath united(const ZQRect &other) const noexcept;
        inline QPainterPath intersected(const ZQRect &other) const noexcept;
        bool intersects(const ZQRect &r) const noexcept;

        constexpr inline ZQRect marginsAdded(const QMargins &margins) const noexcept;
        constexpr inline ZQRect marginsRemoved(const QMargins &margins) const noexcept;
        inline ZQRect &operator+=(const QMargins &margins) noexcept;
        inline ZQRect &operator-=(const QMargins &margins) noexcept;

        constexpr inline ZQRect toRect() const noexcept;
        ZQRect toAlignedRect() const noexcept;

        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 &mat, const QPoint &ref) const noexcept;
        constexpr inline QString toString() const noexcept;

        friend constexpr inline bool operator==(const ZQRect &, const ZQRect &) noexcept;
        friend constexpr inline bool operator!=(const ZQRect &, const ZQRect &) noexcept;


    private:
        qreal x1;
        qreal y1;
        qreal x2;
        qreal y2;
        qreal a;
    };


    constexpr inline bool operator==(const ZQRect &, const ZQRect &) noexcept;
    constexpr inline bool operator!=(const ZQRect &, const ZQRect &) noexcept;

    /*****************************************************************************
      ZQRect stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQRect &);
    QDataStream &operator>>(QDataStream &, ZQRect &);
    #endif

    /*****************************************************************************
      ZQRect inline member functions
     *****************************************************************************/

    constexpr inline ZQRect::ZQRect(int aleft, int atop, int awidth, int aheight) noexcept
        : x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1), a(0) {}

    constexpr inline ZQRect::ZQRect(int aleft, int atop, int awidth, int aheight, int angle) noexcept
        : x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1), a(normalizedAngle(angle)) {}

    constexpr inline ZQRect::ZQRect(const QPoint &atopLeft, const QPoint &abottomRight) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()), y2(abottomRight.y()), a(0) {}

    constexpr inline ZQRect::ZQRect(const QPoint &atopLeft, const QPoint &abottomRight, int angle) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()), y2(abottomRight.y()), a(normalizedAngle(angle)) {}

    constexpr inline ZQRect::ZQRect(const QPoint &atopLeft, const QSize &asize) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x()+asize.width() - 1), y2(atopLeft.y()+asize.height() - 1) {}

    constexpr inline ZQRect::ZQRect(const QPoint &atopLeft, const QSize &asize, int angle) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x()+asize.width() - 1), y2(atopLeft.y()+asize.height() - 1), a(normalizedAngle(angle)) {}

    constexpr inline bool ZQRect::isNull() const noexcept
    { return x2 == x1 - 1 && y2 == y1 - 1 && a == 0; }

    constexpr inline bool ZQRect::isEmpty() const noexcept
    { return x1 > x2 || y1 > y2; }

    constexpr inline bool ZQRect::isValid() const noexcept
    { return x1 <= x2 && y1 <= y2; }

    constexpr inline int ZQRect::left() const noexcept
    { return x1; }

    constexpr inline int ZQRect::top() const noexcept
    { return y1; }

    constexpr inline int ZQRect::right() const noexcept
    { return x2; }

    constexpr inline int ZQRect::bottom() const noexcept
    { return y2; }

    constexpr inline int ZQRect::x() const noexcept
    { return x1; }

    constexpr inline int ZQRect::y() const noexcept
    { return y1; }

    constexpr inline int ZQRect::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQRect::angleRadians() const noexcept
    { return M_PI/180 * a; }

    inline void ZQRect::setLeft(int pos) noexcept
    { x1 = pos; }

    inline void ZQRect::setTop(int pos) noexcept
    { y1 = pos; }

    inline void ZQRect::setRight(int pos) noexcept
    { x2 = pos; }

    inline void ZQRect::setBottom(int pos) noexcept
    { y2 = pos; }

    inline void ZQRect::setTopLeft(const QPoint &p) noexcept
    { x1 = p.x(); y1 = p.y(); }

    inline void ZQRect::setBottomRight(const QPoint &p) noexcept
    { x2 = p.x(); y2 = p.y(); }

    inline void ZQRect::setTopRight(const QPoint &p) noexcept
    { x2 = p.x(); y1 = p.y(); }

    inline void ZQRect::setBottomLeft(const QPoint &p) noexcept
    { x1 = p.x(); y2 = p.y(); }

    inline void ZQRect::setX(int ax) noexcept
    { x1 = ax; }

    inline void ZQRect::setY(int ay) noexcept
    { y1 = ay; }

    inline void ZQRect::setAngle(int aangle) noexcept
    { a = normalizedAngle(aangle); }

    inline void ZQRect::setAngleRadians(qreal aangle) noexcept
    { a = normalizedAngle((int) (180/M_PI * aangle)); }

    constexpr inline QPoint ZQRect::topLeft() const noexcept
    { return QPoint(x1, y1); }

    constexpr inline QPoint ZQRect::bottomRight() const noexcept
    { return QPoint(x2, y2); }

    constexpr inline QPoint ZQRect::topRight() const noexcept
    { return QPoint(x2, y1); }

    constexpr inline QPoint ZQRect::bottomLeft() const noexcept
    { return QPoint(x1, y2); }

    constexpr inline QPoint ZQRect::center() const noexcept
    { return QPoint(int((qint64(x1)+x2)/2), int((qint64(y1)+y2)/2)); } // cast avoids overflow on addition

    constexpr inline int ZQRect::width() const noexcept
    { return  x2 - x1 + 1; }

    constexpr inline int ZQRect::height() const noexcept
    { return  y2 - y1 + 1; }

    constexpr inline QSize ZQRect::size() const noexcept
    { return QSize(width(), height()); }

    inline void ZQRect::translate(int dx, int dy) noexcept
    {
        x1 += dx;
        y1 += dy;
        x2 += dx;
        y2 += dy;
    }

    inline void ZQRect::translate(const QPoint &p) noexcept
    {
        x1 += p.x();
        y1 += p.y();
        x2 += p.x();
        y2 += p.y();
    }

    constexpr inline ZQRect ZQRect::translated(int dx, int dy) const noexcept
    { return ZQRect(QPoint(x1 + dx, y1 + dy), QPoint(x2 + dx, y2 + dy)); }

    constexpr inline ZQRect ZQRect::translated(const QPoint &p) const noexcept
    { return ZQRect(QPoint(x1 + p.x(), y1 + p.y()), QPoint(x2 + p.x(), y2 + p.y())); }

    constexpr inline ZQRect ZQRect::transposed() const noexcept
    { return ZQRect(topLeft(), size().transposed()); }

    inline void ZQRect::rotate(int angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQRect::rotateRadians(qreal angle) const noexcept
    { a += normalizedAngle((int) (180/M_PI * angle)); }

    constexpr inline ZQRect ZQRect::rotate(int angle) const noexcept
    { return ZQRect(x1, y1, x2, y2, a + normalizedAngle(angle)); }

    constexpr inline ZQRect ZQRect::rotateRadians(qreal angle) const noexcept
    { return ZQRect(x1, y1, x2, y2, a + normalizedAngle((int) (180/M_PI * angle))); }


    inline int ZQRect::normalizedAngle(int a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle >= 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQRect::moveTo(int ax, int ay) noexcept
    {
        x2 += ax - x1;
        y2 += ay - y1;
        x1 = ax;
        y1 = ay;
    }

    inline void ZQRect::moveTo(const QPoint &p) noexcept
    {
        x2 += p.x() - x1;
        y2 += p.y() - y1;
        x1 = p.x();
        y1 = p.y();
    }

    inline void ZQRect::moveLeft(int pos) noexcept
    { x2 += (pos - x1); x1 = pos; }

    inline void ZQRect::moveTop(int pos) noexcept
    { y2 += (pos - y1); y1 = pos; }

    inline void ZQRect::moveRight(int pos) noexcept
    {
        x1 += (pos - x2);
        x2 = pos;
    }

    inline void ZQRect::moveBottom(int pos) noexcept
    {
        y1 += (pos - y2);
        y2 = pos;
    }

    inline void ZQRect::moveTopLeft(const QPoint &p) noexcept
    {
        moveLeft(p.x());
        moveTop(p.y());
    }

    inline void ZQRect::moveBottomRight(const QPoint &p) noexcept
    {
        moveRight(p.x());
        moveBottom(p.y());
    }

    inline void ZQRect::moveTopRight(const QPoint &p) noexcept
    {
        moveRight(p.x());
        moveTop(p.y());
    }

    inline void ZQRect::moveBottomLeft(const QPoint &p) noexcept
    {
        moveLeft(p.x());
        moveBottom(p.y());
    }

    inline void ZQRect::moveCenter(const QPoint &p) noexcept
    {
        int w = x2 - x1;
        int h = y2 - y1;
        x1 = p.x() - w/2;
        y1 = p.y() - h/2;
        x2 = x1 + w;
        y2 = y1 + h;
    }

    inline void ZQRect::getRect(int *ax, int *ay, int *aw, int *ah) const
    {
        *ax = x1;
        *ay = y1;
        *aw = x2 - x1 + 1;
        *ah = y2 - y1 + 1;
    }

    inline void ZQRect::setRect(int ax, int ay, int aw, int ah) noexcept
    {
        x1 = ax;
        y1 = ay;
        x2 = (ax + aw - 1);
        y2 = (ay + ah - 1);
    }

    inline void ZQRect::getCoords(int *xp1, int *yp1, int *xp2, int *yp2) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
    }

    inline void ZQRect::getCoords(int *xp1, int *yp1, int *xp2, int *yp2, int *angle) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
        *angle = a;
    }

    inline void ZQRect::getCoordsRadians(int *xp1, int *yp1, int *xp2, int *yp2, qreal *angle) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
        *angle = M_PI/180 * a;
    }

    inline void ZQRect::setCoords(int xp1, int yp1, int xp2, int yp2) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
    }

    inline void ZQRect::setCoords(int xp1, int yp1, int xp2, int yp2, int angle) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
        a = normalizedAngle(angle);
    }

    inline void ZQRect::setCoordsRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
        a = normalizedAngle((int) (180/M_PI * angle));
    }


    constexpr inline ZQRect ZQRect::adjusted(int xp1, int yp1, int xp2, int yp2) const noexcept
    { return ZQRect(QPoint(x1 + xp1, y1 + yp1), QPoint(x2 + xp2, y2 + yp2)); }

    constexpr inline ZQRect ZQRect::adjusted(int xp1, int yp1, int xp2, int yp2, int angle) const noexcept
    { return ZQRect(QPoint(x1 + xp1, y1 + yp1), QPoint(x2 + xp2, y2 + yp2), angle); }

    constexpr inline ZQRect ZQRect::adjustedRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) const noexcept
    { return ZQRect(QPoint(x1 + xp1, y1 + yp1), QPoint(x2 + xp2, y2 + yp2), normalizedAngle((int) (180/M_PI * angle))); }


    inline void ZQRect::adjust(int dx1, int dy1, int dx2, int dy2) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2;
        y2 += dy2;
    }

    inline void ZQRect::adjust(int dx1, int dy1, int dx2, int dy2, int angle) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2;
        y2 += dy2;
        a += normalizedAngle(angle);
    }

    inline void ZQRect::adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2;
        y2 += dy2;
        a += normalizedAngle((int) (180/M_PI * angle));
    }

    inline void ZQRect::setWidth(int w) noexcept
    { x2 = (x1 + w - 1); }

    inline void ZQRect::setHeight(int h) noexcept
    { y2 = (y1 + h - 1); }

    inline void ZQRect::setSize(const QSize &s) noexcept
    {
        x2 = (s.width()  + x1 - 1);
        y2 = (s.height() + y1 - 1);
    }

    inline bool ZQRect::contains(int ax, int ay, bool aproper) const noexcept
    {
        return contains(QPoint(ax, ay), aproper);
    }

    inline bool ZQRect::contains(int ax, int ay) const noexcept
    {
        return contains(QPoint(ax, ay), false);
    }

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQRect(%1,%2 size %3x%4 %5 degrees)").arg(x1, y1, width(), height(), a));
    }

    inline QPainterPath ZQRect::intersected(const ZQRect &other) const noexcept
    {
        return *this & other;
    }

    inline QPainterPath ZQRect::united(const ZQRect &r) const noexcept
    {
        return *this | r;
    }

    constexpr inline bool operator==(const ZQRect &r1, const ZQRect &r2) noexcept
    {
        return r1.x1==r2.x1 && r1.x2==r2.x2 && r1.y1==r2.y1 && r1.y2==r2.y2
               && r1.a == r2.a;
    }

    constexpr inline bool operator!=(const ZQRect &r1, const ZQRect &r2) noexcept
    {
        return r1.x1!=r2.x1 || r1.x2!=r2.x2 || r1.y1!=r2.y1 || r1.y2!=r2.y2;
    }

    constexpr inline ZQRect operator+(const ZQRect &rectangle, const QMargins &margins) noexcept
    {
        return ZQRect(QPoint(rectangle.left() - margins.left(), rectangle.top() - margins.top()),
                     QPoint(rectangle.right() + margins.right(), rectangle.bottom() + margins.bottom()));
    }

    constexpr inline ZQRect operator+(const QMargins &margins, const ZQRect &rectangle) noexcept
    {
        return ZQRect(QPoint(rectangle.left() - margins.left(), rectangle.top() - margins.top()),
                     QPoint(rectangle.right() + margins.right(), rectangle.bottom() + margins.bottom()));
    }

    constexpr inline ZQRect operator-(const ZQRect &lhs, const QMargins &rhs) noexcept
    {
        return ZQRect(QPoint(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                     QPoint(lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom()));
    }

    constexpr inline ZQRect ZQRect::marginsAdded(const QMargins &margins) const noexcept
    {
        return ZQRect(QPoint(x1 - margins.left(), y1 - margins.top()),
                     QPoint(x2 + margins.right(), y2 + margins.bottom()));
    }

    constexpr inline ZQRect ZQRect::marginsRemoved(const QMargins &margins) const noexcept
    {
        return ZQRect(QPoint(x1 + margins.left(), y1 + margins.top()),
                     QPoint(x2 - margins.right(), y2 - margins.bottom()));
    }

    inline ZQRect &ZQRect::operator+=(const QMargins &margins) noexcept
    {
        *this = marginsAdded(margins);
        return *this;
    }

    inline ZQRect &ZQRect::operator-=(const QMargins &margins) noexcept
    {
        *this = marginsRemoved(margins);
        return *this;
    }

    #ifndef QT_NO_DEBUG_STREAM
    Q_CORE_EXPORT QDebug operator<<(QDebug, const ZQRect &);
    #endif




    class ZQRectF {
    public:
        constexpr ZQRectF() noexcept : xp(0.), yp(0.), w(0.), h(0.) a(0.) {}
        constexpr ZQRectF(const QPointF &topleft, const QSizeF &size) noexcept;
        constexpr ZQRectF(const QPointF &topleft, const QSizeF &size, qreal angle) noexcept;
        constexpr ZQRectF(const QPointF &topleft, const QPointF &bottomRight) noexcept;
        constexpr ZQRectF(const QPointF &topleft, const QPointF &bottomRight, qreal angle) noexcept;
        constexpr ZQRectF(qreal left, qreal top, qreal width, qreal height) noexcept;
        constexpr ZQRectF(qreal left, qreal top, qreal width, qreal height, qreal angle) noexcept;
        constexpr ZQRectF(const ZQRect &rect) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        constexpr inline bool isValid() const noexcept;
        void normalize() const noexcept;
        ZQRectF normalized() const noexcept;

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
        inline void setAngle(qreal angle) noexcept { a = normalizedAngle(angle); }
        inline void setAngleRadians(qreal angle) noexcept { a = normalizedAngle(180/M_PI * angle); }

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

        constexpr inline ZQRectF translated(qreal dx, qreal dy) const noexcept;
        constexpr inline ZQRectF translated(const QPointF &p) const noexcept;

        constexpr inline ZQRectF transposed() const noexcept;


        inline void rotate(qreal da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQRectF rotated(qreal da) noexcept;
        constexpr inline ZQRectF rotatedRadians(qreal da) noexcept;

        inline qreal normalizedAngle(qreal a) noexcept;

        inline void moveTo(qreal x, qreal y) noexcept;
        inline void moveTo(const QPointF &p) noexcept;

        inline void setRect(qreal x, qreal y, qreal w, qreal h) noexcept;
        inline void getRect(qreal *x, qreal *y, qreal *w, qreal *h) const;

        inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void setCoordsRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const;
        inline void getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const;
        inline void getCoordsRadians(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const;

        inline void adjust(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void adjustRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        constexpr inline ZQRectF adjusted(qreal x1, qreal y1, qreal x2, qreal y2) const noexcept;
        constexpr inline ZQRectF adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept;
        constexpr inline ZQRectF adjustedRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept;

        constexpr inline QSizeF size() const noexcept;
        constexpr inline qreal width() const noexcept;
        constexpr inline qreal height() const noexcept;
        inline void setWidth(qreal w) noexcept;
        inline void setHeight(qreal h) noexcept;
        inline void setSize(const QSizeF &s) noexcept;

        QPainterPath operator|(const ZQRectF &r) const noexcept;
        QPainterPath operator&(const ZQRectF &r) const noexcept;

        bool contains(const ZQRectF &r, bool proper=false) const noexcept;
        bool contains(const QPointF &p, bool proper=false) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQRectF &other) const noexcept;
        inline QPainterPath intersected(const ZQRectF &other) const noexcept;
        bool intersects(const ZQRectF &r) const noexcept;

        constexpr inline ZQRectF marginsAdded(const QMarginsF &margins) const noexcept;
        constexpr inline ZQRectF marginsRemoved(const QMarginsF &margins) const noexcept;
        inline ZQRectF &operator+=(const QMarginsF &margins) noexcept;
        inline ZQRectF &operator-=(const QMarginsF &margins) noexcept;


        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        constexpr inline QString toString() const noexcept;

        friend constexpr inline bool operator==(const ZQRectF &, const ZQRectF &) noexcept;
        friend constexpr inline bool operator!=(const ZQRectF &, const ZQRectF &) noexcept;

    private:
        qreal xp;
        qreal yp;
        qreal w;
        qreal h;
        qreal a;
    };



    constexpr inline bool operator==(const ZQRectF &, const ZQRectF &) noexcept;
    constexpr inline bool operator!=(const ZQRectF &, const ZQRectF &) noexcept;


    /*****************************************************************************
      ZQRectF stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQRectF &);
    QDataStream &operator>>(QDataStream &, ZQRectF &);
    #endif

    /*****************************************************************************
      ZQRectF inline member functions
     *****************************************************************************/

    constexpr inline ZQRectF::ZQRectF(qreal aleft, qreal atop, qreal awidth, qreal aheight) noexcept
        : xp(aleft), yp(atop), w(awidth), h(aheight)
    {
    }

    constexpr inline ZQRectF::ZQRectF(qreal aleft, qreal atop, qreal awidth, qreal aheight, qreal angle) noexcept
        : xp(aleft), yp(atop), w(awidth), h(aheight), a(normalizedAngle(angle))
    {
    }

    constexpr inline ZQRectF::ZQRectF(const QPointF &atopLeft, const QSizeF &asize) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.width()), h(asize.height())
    {
    }

    constexpr inline ZQRectF::ZQRectF(const QPointF &atopLeft, const QSizeF &asize, qreal angle) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.width()), h(asize.height(), a(normalizedAngle(angle))
    {
    }



    constexpr inline ZQRectF::ZQRectF(const QPointF &atopLeft, const QPointF &abottomRight) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()), h(abottomRight.y() - atopLeft.y())
    {
    }


    constexpr inline ZQRectF::ZQRectF(const QPointF &atopLeft, const QPointF &abottomRight, qreal angle) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()), h(abottomRight.y() - atopLeft.y()),
            a(normalizedAngle(angle))
    {
    }


    constexpr inline ZQRectF::ZQRectF(const ZQRect &r) noexcept
        : xp(r.x()), yp(r.y()), w(r.width()), h(r.height()), a(r.angle())
    {
    }

    //QT_WARNING_PUSH
    //QT_WARNING_DISABLE_GCC("-Wfloat-equal")
    // just compile with -Wno-float-equal

    constexpr inline bool ZQRectF::isNull() const noexcept
    { return w == 0. && h == 0.; }

    constexpr inline bool ZQRectF::isEmpty() const noexcept
    { return w <= 0. || h <= 0.; }

    //QT_WARNING_POP

    constexpr inline bool ZQRectF::isValid() const noexcept
    { return w > 0. && h > 0.; }

    constexpr inline qreal ZQRectF::x() const noexcept
    { return xp; }

    constexpr inline qreal ZQRectF::y() const noexcept
    { return yp; }

    constexpr inline qreal ZQRectF::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQRectF::angleRadians() const noexcept
    { return M_PI/180 * a; }

    inline void ZQRectF::setLeft(qreal pos) noexcept
    { qreal diff = pos - xp; xp += diff; w -= diff; }

    inline void ZQRectF::setRight(qreal pos) noexcept
    { w = pos - xp; }

    inline void ZQRectF::setTop(qreal pos) noexcept
    { qreal diff = pos - yp; yp += diff; h -= diff; }

    inline void ZQRectF::setBottom(qreal pos) noexcept
    { h = pos - yp; }

    inline void ZQRectF::setTopLeft(const QPointF &p) noexcept
    { setLeft(p.x()); setTop(p.y()); }

    inline void ZQRectF::setTopRight(const QPointF &p) noexcept
    { setRight(p.x()); setTop(p.y()); }

    inline void ZQRectF::setBottomLeft(const QPointF &p) noexcept
    { setLeft(p.x()); setBottom(p.y()); }

    inline void ZQRectF::setBottomRight(const QPointF &p) noexcept
    { setRight(p.x()); setBottom(p.y()); }

    constexpr inline QPointF ZQRectF::center() const noexcept
    { return QPointF(xp + w/2, yp + h/2); }

    inline void ZQRectF::moveLeft(qreal pos) noexcept
    { xp = pos; }

    inline void ZQRectF::moveTop(qreal pos) noexcept
    { yp = pos; }

    inline void ZQRectF::moveRight(qreal pos) noexcept
    { xp = pos - w; }

    inline void ZQRectF::moveBottom(qreal pos) noexcept
    { yp = pos - h; }

    inline void ZQRectF::moveTopLeft(const QPointF &p) noexcept
    { moveLeft(p.x()); moveTop(p.y()); }

    inline void ZQRectF::moveTopRight(const QPointF &p) noexcept
    { moveRight(p.x()); moveTop(p.y()); }

    inline void ZQRectF::moveBottomLeft(const QPointF &p) noexcept
    { moveLeft(p.x()); moveBottom(p.y()); }

    inline void ZQRectF::moveBottomRight(const QPointF &p) noexcept
    { moveRight(p.x()); moveBottom(p.y()); }

    inline void ZQRectF::moveCenter(const QPointF &p) noexcept
    { xp = p.x() - w/2; yp = p.y() - h/2; }

    constexpr inline qreal ZQRectF::width() const noexcept
    { return w; }

    constexpr inline qreal ZQRectF::height() const noexcept
    { return h; }

    constexpr inline QSizeF ZQRectF::size() const noexcept
    { return QSizeF(w, h); }

    inline void ZQRectF::translate(qreal dx, qreal dy) noexcept
    {
        xp += dx;
        yp += dy;
    }

    inline void ZQRectF::translate(const QPointF &p) noexcept
    {
        xp += p.x();
        yp += p.y();
    }

    inline void ZQRectF::rotate(qreal angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQRectF::rotateRadians(qreal angle) const noexcept
    { a += normalizedAngle(180/M_PI * (angle)); }

    constexpr inline ZQRectF ZQRectF::rotate(qreal angle) const noexcept
    { return ZQRect(x1, y1, x2, y2, a + normalizedAngle(angle)); }

    constexpr inline ZQRectF ZQRectF::rotateRadians(qreal angle) const noexcept
    { return ZQRect(x1, y1, x2, y2, a + normalizedAngle(180/M_PI * angle)); }

    inline qreal ZQRectF::normalizedAngle(qreal a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle >= 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQRectF::moveTo(qreal ax, qreal ay) noexcept
    {
        xp = ax;
        yp = ay;
    }

    inline void ZQRectF::moveTo(const QPointF &p) noexcept
    {
        xp = p.x();
        yp = p.y();
    }

    constexpr inline ZQRectF ZQRectF::translated(qreal dx, qreal dy) const noexcept
    { return ZQRectF(xp + dx, yp + dy, w, h); }

    constexpr inline ZQRectF ZQRectF::translated(const QPointF &p) const noexcept
    { return ZQRectF(xp + p.x(), yp + p.y(), w, h); }

    constexpr inline ZQRectF ZQRectF::transposed() const noexcept
    { return ZQRectF(topLeft(), size().transposed()); }

    inline void ZQRectF::getRect(qreal *ax, qreal *ay, qreal *aaw, qreal *aah) const
    {
        *ax = this->xp;
        *ay = this->yp;
        *aaw = this->w;
        *aah = this->h;
    }

    inline void ZQRectF::getRect(qreal *ax, qreal *ay, qreal *aaw, qreal *aah, qreal *aaa) const
    {
        *ax = this->xp;
        *ay = this->yp;
        *aaw = this->w;
        *aah = this->h;
        *aaa = this->a;
    }

    inline void ZQRectF::setRect(qreal ax, qreal ay, qreal aaw, qreal aah) noexcept
    {
        this->xp = ax;
        this->yp = ay;
        this->w = aaw;
        this->h = aah;
    }

    inline void ZQRectF::setRect(qreal ax, qreal ay, qreal aaw, qreal aah, qreal aaa) noexcept
    {
        this->xp = ax;
        this->yp = ay;
        this->w = aaw;
        this->h = aah;
        this->a = normalizedAngle(aaa);
    }


    inline void ZQRectF::getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
    }

    inline void ZQRectF::getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
        *angle = a;
    }

    inline void ZQRectF::getCoordsRadians(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
        *angle = M_PI/180 * a;
    }

    inline void ZQRectF::setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
    }

    inline void ZQRectF::setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
        a = normalizedAngle(angle);
    }

    inline void ZQRectF::setCoordsRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
        a = normalizedAngle(180/M_PI * angle);
    }

    inline void ZQRectF::adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
    { xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1; }

    inline void ZQRectF::adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    { xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1; angle = normalizedAngle(a + angle); }

    inline void ZQRectF::adjustRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept
    { xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1; angle = normalizedAngle(a + 180/M_PI * angle); }

    constexpr inline ZQRectF ZQRectF::adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2) const noexcept
    { return ZQRectF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1); }

    constexpr inline ZQRectF ZQRectF::adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept
    { return ZQRectF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1, normalizedAngle(a + angle)); }

    constexpr inline ZQRectF ZQRectF::adjustedRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept
    { return ZQRectF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1, normalizedAngle(a + 180/M_PI * angle)); }

    inline void ZQRectF::setWidth(qreal aw) noexcept
    { this->w = aw; }

    inline void ZQRectF::setHeight(qreal ah) noexcept
    { this->h = ah; }

    inline void ZQRectF::setSize(const QSizeF &s) noexcept
    {
        w = s.width();
        h = s.height();
    }

    inline bool ZQRectF::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPointF(ax, ay));
    }

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQRectF(%1,%2 size %3x%4 %5 degrees)").arg(xp, yp, w, h, a));
    }

    inline QPainterPath ZQRectF::intersected(const ZQRectF &r) const noexcept
    {
        return *this & r;
    }

    inline QPainterPath ZQRectF::united(const ZQRectF &r) const noexcept
    {
        return *this | r;
    }

    constexpr inline bool operator==(const ZQRectF &r1, const ZQRectF &r2) noexcept
    {
        return qFuzzyCompare(r1.xp, r2.xp) && qFuzzyCompare(r1.yp, r2.yp)
               && qFuzzyCompare(r1.w, r2.w) && qFuzzyCompare(r1.h, r2.h)
               && qFuzzyCompare(r1.a, r2.a);
    }

    constexpr inline bool operator!=(const ZQRectF &r1, const ZQRectF &r2) noexcept
    {
        return !qFuzzyCompare(r1.xp, r2.xp) || !qFuzzyCompare(r1.yp, r2.yp)
               || !qFuzzyCompare(r1.w, r2.w) || !qFuzzyCompare(r1.h, r2.h);
    }

    constexpr inline ZQRect ZQRectF::toRect() const noexcept
    {
        return ZQRect(QPoint(qRound(xp), qRound(yp)), QPoint(qRound(xp + w) - 1, qRound(yp + h) - 1));
    }

    constexpr inline ZQRectF operator+(const ZQRectF &lhs, const QMarginsF &rhs) noexcept
    {
        return ZQRectF(QPointF(lhs.left() - rhs.left(), lhs.top() - rhs.top()),
                      QSizeF(lhs.width() + rhs.left() + rhs.right(), lhs.height() + rhs.top() + rhs.bottom()));
    }

    constexpr inline ZQRectF operator+(const QMarginsF &lhs, const ZQRectF &rhs) noexcept
    {
        return ZQRectF(QPointF(rhs.left() - lhs.left(), rhs.top() - lhs.top()),
                      QSizeF(rhs.width() + lhs.left() + lhs.right(), rhs.height() + lhs.top() + lhs.bottom()));
    }

    constexpr inline ZQRectF operator-(const ZQRectF &lhs, const QMarginsF &rhs) noexcept
    {
        return ZQRectF(QPointF(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                      QSizeF(lhs.width() - rhs.left() - rhs.right(), lhs.height() - rhs.top() - rhs.bottom()));
    }

    constexpr inline ZQRectF ZQRectF::marginsAdded(const QMarginsF &margins) const noexcept
    {
        return ZQRectF(QPointF(xp - margins.left(), yp - margins.top()),
                      QSizeF(w + margins.left() + margins.right(), h + margins.top() + margins.bottom()));
    }

    constexpr inline ZQRectF ZQRectF::marginsRemoved(const QMarginsF &margins) const noexcept
    {
        return ZQRectF(QPointF(xp + margins.left(), yp + margins.top()),
                      QSizeF(w - margins.left() - margins.right(), h - margins.top() - margins.bottom()));
    }

    inline ZQRectF &ZQRectF::operator+=(const QMarginsF &margins) noexcept
    {
        *this = marginsAdded(margins);
        return *this;
    }

    inline ZQRectF &ZQRectF::operator-=(const QMarginsF &margins) noexcept
    {
        *this = marginsRemoved(margins);
        return *this;
    }

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug, const ZQRectF &);
    #endif

}

#endif
