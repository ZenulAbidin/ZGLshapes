/****************************************************************************
**
** Copyright (C) 2020 Ali Sherief
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


#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include "z_base.h"

namespace z_qtshapes {


    class ZQRect {
    public:
        constexpr inline ZQRect() noexcept : x1(0), y1(0), x2(-1), y2(-1), a(0) {};
        constexpr inline ZQRect(const QPoint &topleft, const QPoint &size) noexcept;
        inline ZQRect(const QPoint &topleft, const QPoint &size, int angle) noexcept;
        constexpr inline ZQRect(int left, int top, int width, int height) noexcept;
        inline ZQRect(int left, int top, int width, int height, int angle) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        constexpr inline bool isValid() const noexcept;

        constexpr inline int left() const noexcept;
        constexpr inline int top() const noexcept;
        constexpr inline int right() const noexcept;
        constexpr inline int bottom() const noexcept;
        void normalize() noexcept;
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

        inline void setTopLeft(const QPoint &p) noexcept;
        inline void setBottomRight(const QPoint &p) noexcept;
        inline void setTopRight(const QPoint &p) noexcept;
        inline void setBottomLeft(const QPoint &p) noexcept;

        constexpr inline QPoint topLeft() const noexcept;
        constexpr inline QPoint bottomRight() const noexcept;
        constexpr inline QPoint topRight() const noexcept;
        constexpr inline QPoint bottomLeft() const noexcept;
        constexpr inline QPoint center() const noexcept;

        inline void moveLeft(int pos) noexcept;
        inline void moveTop(int pos) noexcept;
        inline void moveRight(int pos) noexcept;
        inline void moveBottom(int pos) noexcept;
        inline void moveTopLeft(const QPoint &p) noexcept;
        inline void moveBottomRight(const QPoint &p) noexcept;
        inline void moveTopRight(const QPoint &p) noexcept;
        inline void moveBottomLeft(const QPoint &p) noexcept;
        inline void moveCenter(const QPoint &p) noexcept;

        inline void translate(int dx, int dy) noexcept;
        inline void translate(int dx, int dy, int a_) noexcept;
        inline void translateRadians(int dx, int dy, qreal a_) noexcept;
        inline void translate(const QPoint &p) noexcept;
        inline void translate(const QPoint &p, int a_) noexcept;
        inline void translateRadians(const QPoint &p, qreal a_) noexcept;

        inline ZQRect translated(int dx, int dy) const noexcept;
        inline ZQRect translated(int dx, int dy, int a_) const noexcept;
        inline ZQRect translatedRadians(int dx, int dy, qreal a_) const noexcept;
        inline ZQRect translated(const QPoint &p) const noexcept;
        inline ZQRect translated(const QPoint &p, int a_) const noexcept;
        inline ZQRect translatedRadians(const QPoint &p, qreal a_) const noexcept;

        constexpr inline ZQRect transposed() const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        inline ZQRect rotated(int da) const noexcept;
        inline ZQRect rotatedRadians(qreal da) const noexcept;

        inline void moveTo(int x, int t) noexcept;
        inline void moveTo(const QPoint &p) noexcept;

        inline void setRect(int x, int y, int w, int h) noexcept;
        inline void setRect(int x, int y, int w, int h, int aa) noexcept;
        inline void setRectRadians(int x, int y, int w, int h, qreal aa) noexcept;
        inline void getRect(int *x, int *y, int *w, int *h) const;
        inline void getRect(int *x, int *y, int *w, int *h, int *aa) const;
        inline void getRectRadians(int *x, int *y, int *w, int *h, qreal *aa) const;

        inline void setCoords(int x1, int y1, int x2, int y2) noexcept;
        inline void setCoords(int xp1, int yp1, int xp2, int yp2, int angle) noexcept;
        inline void setCoordsRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) noexcept;
        inline void setCoords(const QPoint &p1, const QPoint &p2) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y()); };
        inline void setCoords(const QPoint &p1, const QPoint &p2, int a_) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline void setCoordsRadians(const QPoint &p1, const QPoint &p2, qreal a_) noexcept {return setCoordsRadians(p1.x(), p1.y(), p2.x(), p2.y(), a_); };

        inline void getCoords(int *x1, int *y1, int *x2, int *y2) const;
        inline void getCoords(int *xp1, int *yp1, int *xp2, int *yp2, int *angle) const;
        inline void getCoordsRadians(int *xp1, int *yp1, int *xp2, int *yp2, qreal *angle) const;

        inline void adjust(int x1, int y1, int x2, int y2) noexcept;
        inline void adjust(int dx1, int dy1, int dx2, int dy2, int angle) noexcept;
        inline void adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) noexcept;
        inline ZQRect adjusted(int x1, int y1, int x2, int y2) const noexcept;
        inline ZQRect adjusted(int xp1, int yp1, int xp2, int yp2, int angle) const noexcept;
        inline ZQRect adjustedRadians(int xp1, int yp1, int xp2, int yp2, qreal angle) const noexcept;
        inline void adjust(const QPoint &p1, const QPoint &p2) noexcept {return adjust(p1.x(), p1.y(), p2.x(), p2.y()); };
        inline void adjust(const QPoint &p1, const QPoint &p2, int a_) noexcept {return adjust(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline void adjustRadians(const QPoint &p1, const QPoint &p2, qreal a_) noexcept {return adjustRadians(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline ZQRect adjusted(const QPoint &p1, const QPoint &p2) noexcept {return adjusted(p1.x(), p1.y(), p2.x(), p2.y()); };
        inline ZQRect adjusted(const QPoint &p1, const QPoint &p2, int a_) noexcept {return adjusted(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline ZQRect adjustedRadians(const QPoint &p1, const QPoint &p2, qreal a_) noexcept {return adjustedRadians(p1.x(), p1.y(), p2.x(), p2.y(), a_); };


        constexpr inline QSize size() const noexcept;
        constexpr inline int width() const noexcept;
        constexpr inline int height() const noexcept;
        constexpr inline int px1() const noexcept {return x(); };
        constexpr inline int py1() const noexcept {return y(); };
        constexpr inline int px2() const noexcept {return x() + width(); };
        constexpr inline int py2() const noexcept {return y() + height(); };
        inline void setWidth(int w) noexcept;
        inline void setHeight(int h) noexcept;
        inline void setSize(const QSize &s) noexcept;

        QPainterPath operator|(const ZQRect &r) const noexcept;
        QPainterPath operator&(const ZQRect &r) const noexcept;

        bool contains(const ZQRect &r, bool proper=false) const noexcept;
        bool contains(const QPoint &p) const noexcept;
        inline bool contains(int x, int y) const noexcept;
        inline QPainterPath united(const ZQRect &other) const noexcept;
        inline QPainterPath intersected(const ZQRect &other) const noexcept;
        bool intersects(const ZQRect &r) const noexcept;

        inline ZQRect marginsAdded(const QMargins &margins) const noexcept;
        inline ZQRect marginsRemoved(const QMargins &margins) const noexcept;
        inline ZQRect &operator+=(const QMargins &margins) noexcept;
        inline ZQRect &operator-=(const QMargins &margins) noexcept;

        QPainterPath toPath() const noexcept;
        QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        QString toString() const noexcept;

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
        : x1(aleft), y1(atop), x2(aleft + awidth), y2(atop + aheight), a(0) {}

    inline ZQRect::ZQRect(int aleft, int atop, int awidth, int aheight, int a_) noexcept
        : x1(aleft), y1(atop), x2(aleft + awidth), y2(atop + aheight)
    {
        a = normalizedAngle(a_);
    }

    constexpr inline ZQRect::ZQRect(const QPoint &atopLeft, const QPoint &asize) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x()+asize.x()), y2(atopLeft.y()+asize.y()), a(0) {}

    inline ZQRect::ZQRect(const QPoint &atopLeft, const QPoint &asize, int a_) noexcept
        : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x()+asize.x()), y2(atopLeft.y()+asize.y())
    {
        a = normalizedAngle(a_);
    }


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
    { return  x2 - x1; }

    constexpr inline int ZQRect::height() const noexcept
    { return  y2 - y1; }

    constexpr inline QSize ZQRect::size() const noexcept
    { return QSize(width(), height()); }

    inline void ZQRect::translate(int dx, int dy) noexcept
    {
        x1 += dx;
        y1 += dy;
        x2 += dx;
        y2 += dy;
    }

    inline void ZQRect::translate(int dx, int dy, int a_) noexcept
    {
        x1 += dx;
        y1 += dy;
        x2 += dx;
        y2 += dy;
        a = normalizedAngle(a + a_);
    }

    inline void ZQRect::translateRadians(int dx, int dy, qreal a_) noexcept
    {
        x1 += dx;
        y1 += dy;
        x2 += dx;
        y2 += dy;
        a = normalizedAngle(a + (int) (180/M_PI * a_));
    }

    inline void ZQRect::translate(const QPoint &p) noexcept
    {
        x1 += p.x();
        y1 += p.y();
        x2 += p.x();
        y2 += p.y();
    }

    inline void ZQRect::translate(const QPoint &p, int a_) noexcept
    {
        x1 += p.x();
        y1 += p.y();
        x2 += p.x();
        y2 += p.y();
        a = normalizedAngle(a + a_);
    }

    inline void ZQRect::translateRadians(const QPoint &p, qreal a_) noexcept
    {
        x1 += p.x();
        y1 += p.y();
        x2 += p.x();
        y2 += p.y();
        a = normalizedAngle(a + (int) (180/M_PI * a_));
    }

    inline ZQRect ZQRect::translated(int dx, int dy) const noexcept
    { return ZQRect(QPoint(x1 + dx, y1 + dy), QPoint(width() + dx, height() + dy), a); }

    inline ZQRect ZQRect::translated(int dx, int dy, int a_) const noexcept
    { return ZQRect(QPoint(x1 + dx, y1 + dy), QPoint(width() + dx, height() + dy), normalizedAngle(a + a_)); }

    inline ZQRect ZQRect::translatedRadians(int dx, int dy, qreal a_) const noexcept
    { return ZQRect(QPoint(x1 + dx, y1 + dy), QPoint(width() + dx, height() + dy), normalizedAngle(a + (int) (180/M_PI * a_))); }

    inline ZQRect ZQRect::translated(const QPoint &p) const noexcept
    { return ZQRect(QPoint(x1 + p.x(), y1 + p.y()), QPoint(width() + p.x(), height() + p.y()), a); }

    inline ZQRect ZQRect::translated(const QPoint &p, int a_) const noexcept
    { return ZQRect(QPoint(x1 + p.x(), y1 + p.y()), QPoint(width() + p.x(), height() + p.y()), normalizedAngle(a + a_)); }

    inline ZQRect ZQRect::translatedRadians(const QPoint &p, qreal a_) const noexcept
    { return ZQRect(QPoint(x1 + p.x(), y1 + p.y()), QPoint(width() + p.x(), height() + p.y()), normalizedAngle(a + (int) (180/M_PI * a_))); }

    constexpr inline ZQRect ZQRect::transposed() const noexcept
    { return ZQRect(topLeft(), QPoint(bottomRight().y(), bottomRight().x())); }

    inline void ZQRect::rotate(int a_) noexcept
    { a = normalizedAngle(a + a_); }

    inline void ZQRect::rotateRadians(qreal a_) noexcept
    { a = normalizedAngle(a + (int) (180/M_PI * a_)); }

    inline ZQRect ZQRect::rotated(int a_) const noexcept
    { return ZQRect(x1, y1, width(), height(), a + normalizedAngle(a_)); }

    inline ZQRect ZQRect::rotatedRadians(qreal a_) const noexcept
    { return ZQRect(x1, y1, width(), height(), a + normalizedAngle((int) (180/M_PI * a_))); }

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
        *aw = x2 - x1;
        *ah = y2 - y1;
    }

    inline void ZQRect::getRect(int *ax, int *ay, int *aw, int *ah, int *aa) const
    {
        *ax = x1;
        *ay = y1;
        *aw = x2 - x1;
        *ah = y2 - y1;
        *aa = a;
    }

    inline void ZQRect::getRectRadians(int *ax, int *ay, int *aw, int *ah, qreal *aa) const
    {
        *ax = x1;
        *ay = y1;
        *aw = x2 - x1;
        *ah = y2 - y1;
        *aa = M_PI/180 * a;
    }

    inline void ZQRect::setRect(int ax, int ay, int aw, int ah) noexcept
    {
        x1 = ax;
        y1 = ay;
        x2 = (ax + aw);
        y2 = (ay + ah);
    }

    inline void ZQRect::setRect(int ax, int ay, int aw, int ah, int aa) noexcept
    {
        x1 = ax;
        y1 = ay;
        x2 = (ax + aw);
        y2 = (ay + ah);
        a = normalizedAngle(aa);
    }

    inline void ZQRect::setRectRadians(int ax, int ay, int aw, int ah, qreal aa) noexcept
    {
        x1 = ax;
        y1 = ay;
        x2 = (ax + aw);
        y2 = (ay + ah);
        a = normalizedAngle((int) (180/M_PI * aa));
    }

    inline void ZQRect::getCoords(int *xp1, int *yp1, int *xp2, int *yp2) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
    }

    inline void ZQRect::getCoords(int *xp1, int *yp1, int *xp2, int *yp2, int *a_) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
        *a_ = a;
    }

    inline void ZQRect::getCoordsRadians(int *xp1, int *yp1, int *xp2, int *yp2, qreal *a_) const
    {
        *xp1 = x1;
        *yp1 = y1;
        *xp2 = x2;
        *yp2 = y2;
        *a_ = M_PI/180 * a;
    }

    inline void ZQRect::setCoords(int xp1, int yp1, int xp2, int yp2) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
    }

    inline void ZQRect::setCoords(int xp1, int yp1, int xp2, int yp2, int a_) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
        a = normalizedAngle(a_);
    }

    inline void ZQRect::setCoordsRadians(int xp1, int yp1, int xp2, int yp2, qreal a_) noexcept
    {
        x1 = xp1;
        y1 = yp1;
        x2 = xp2;
        y2 = yp2;
        a = normalizedAngle((int) (180/M_PI * a_));
    }


    inline ZQRect ZQRect::adjusted(int xp1, int yp1, int xp2, int yp2) const noexcept
    { return ZQRect(QPoint(x1 + xp1, y1 + yp1), QPoint(width() + xp2, height() + yp2), a); }

    inline ZQRect ZQRect::adjusted(int xp1, int yp1, int xp2, int yp2, int a_) const noexcept
    { return ZQRect(QPoint(x1 + xp1, y1 + yp1), QPoint(width() + xp2, height() + yp2), normalizedAngle(a + a_)); }

    inline ZQRect ZQRect::adjustedRadians(int xp1, int yp1, int xp2, int yp2, qreal a_) const noexcept
    { return ZQRect(QPoint(x1 + xp1, y1 + yp1), QPoint(width() + xp2, height() + yp2), normalizedAngle((int) (180/M_PI * a_))); }


    inline void ZQRect::adjust(int dx1, int dy1, int dx2, int dy2) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2 + dx1;
        y2 += dy2 + dy1;
    }

    inline void ZQRect::adjust(int dx1, int dy1, int dx2, int dy2, int a_) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2 + dx1;
        y2 += dy2 + dy1;
        a = normalizedAngle(a + a_);
    }

    inline void ZQRect::adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal a_) noexcept
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2 + dx1;
        y2 += dy2 + dy1;
        a = normalizedAngle(a + (int) (180/M_PI * a_));
    }

    inline void ZQRect::setWidth(int w) noexcept
    { x2 = (x1 + w); }

    inline void ZQRect::setHeight(int h) noexcept
    { y2 = (y1 + h); }

    inline void ZQRect::setSize(const QSize &s) noexcept
    {
        x2 = (s.width()  + x1);
        y2 = (s.height() + y1);
    }

    inline bool ZQRect::contains(int ax, int ay) const noexcept
    {
        return contains(QPoint(ax, ay));
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
        return r1.x1!=r2.x1 || r1.x2!=r2.x2 || r1.y1!=r2.y1 || r1.y2!=r2.y2 || r1.a!=r2.a;
    }

    inline ZQRect operator+(const ZQRect &lhs, const QMargins &rhs) noexcept
    {
        return lhs.adjusted(rhs.left(), rhs.top(), rhs.right(), rhs.bottom());
    }

    inline ZQRect operator+(const QMarginsF &lhs, const ZQRect &rhs) noexcept
    {
        return rhs.adjusted(lhs.left(), lhs.top(), lhs.right(), lhs.bottom());
    }

    inline ZQRect operator-(const ZQRect &lhs, const QMargins &rhs) noexcept
    {
        return lhs.adjusted(-rhs.left(), -rhs.top(), -rhs.right(), -rhs.bottom());
    }

    inline ZQRect ZQRect::marginsAdded(const QMargins &margins) const noexcept
    {
        return *this + margins;
    }

    inline ZQRect ZQRect::marginsRemoved(const QMargins &margins) const noexcept
    {
        return *this - margins;
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
        constexpr ZQRectF() noexcept : xp(0.), yp(0.), w(0.), h(0.), a(0.) {}
        constexpr ZQRectF(const QPointF &topleft, const QPointF &size) noexcept;
        ZQRectF(const QPointF &topleft, const QPointF &size, qreal angle) noexcept;
        constexpr ZQRectF(qreal left, qreal top, qreal width, qreal height) noexcept;
        ZQRectF(qreal left, qreal top, qreal width, qreal height, qreal angle) noexcept;
        constexpr ZQRectF(const ZQRect &rect) noexcept;

        constexpr inline bool isNull() const noexcept;
        constexpr inline bool isEmpty() const noexcept;
        constexpr inline bool isValid() const noexcept;
        void normalize() noexcept;
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
        inline void translate(qreal dx, qreal dy, qreal a_) noexcept;
        inline void translateRadians(qreal dx, qreal dy, qreal a_) noexcept;
        inline void translate(const QPointF &p) noexcept;
        inline void translate(const QPointF &p, qreal a_) noexcept;
        inline void translateRadians(const QPointF &p, qreal a_) noexcept;

        inline ZQRectF translated(qreal dx, qreal dy) const noexcept;
        inline ZQRectF translated(qreal dx, qreal dy, qreal a_) const noexcept;
        inline ZQRectF translatedRadians(qreal dx, qreal dy, qreal a_) const noexcept;
        inline ZQRectF translated(const QPointF &p) const noexcept;
        inline ZQRectF translated(const QPointF &p, qreal a_) const noexcept;
        inline ZQRectF translatedRadians(const QPointF &p, qreal a_) const noexcept;

        constexpr inline ZQRectF transposed() const noexcept;


        inline void rotate(qreal da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        inline ZQRectF rotated(qreal da) const noexcept;
        inline ZQRectF rotatedRadians(qreal da) const noexcept;

        inline void moveTo(qreal x, qreal y) noexcept;
        inline void moveTo(const QPointF &p) noexcept;

        inline void setRect(qreal x, qreal y, qreal w, qreal h) noexcept;
        inline void setRect(qreal x, qreal y, qreal w, qreal h, qreal a) noexcept;
        inline void setRectRadians(qreal x, qreal y, qreal w, qreal h, qreal a) noexcept;
        inline void getRect(qreal *x, qreal *y, qreal *w, qreal *h) const;
        inline void getRect(qreal *x, qreal *y, qreal *w, qreal *h, qreal *a) const;
        inline void getRectRadians(qreal *x, qreal *y, qreal *w, qreal *h, qreal *a) const;

        inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void setCoordsRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void setCoords(const QPointF &p1, const QPointF &p2) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y()); };
        inline void setCoords(const QPointF &p1, const QPointF &p2, qreal a_) noexcept {return setCoords(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline void setCoordsRadians(const QPointF &p1, const QPointF &p2, qreal a_) noexcept {return setCoordsRadians(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const;
        inline void getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const;
        inline void getCoordsRadians(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *angle) const;

        inline void adjust(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline void adjustRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) noexcept;
        inline ZQRectF adjusted(qreal x1, qreal y1, qreal x2, qreal y2) const noexcept;
        inline ZQRectF adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept;
        inline ZQRectF adjustedRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal angle) const noexcept;
        inline void adjust(const QPointF &p1, const QPointF &p2) noexcept {return adjust(p1.x(), p1.y(), p2.x(), p2.y()); };
        inline void adjust(const QPointF &p1, const QPointF &p2, qreal a_) noexcept {return adjust(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline void adjustRadians(const QPointF &p1, const QPointF &p2, qreal a_) noexcept {return adjustRadians(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline ZQRectF adjusted(const QPointF &p1, const QPointF &p2) noexcept {return adjusted(p1.x(), p1.y(), p2.x(), p2.y()); };
        inline ZQRectF adjusted(const QPointF &p1, const QPointF &p2, qreal a_) noexcept {return adjusted(p1.x(), p1.y(), p2.x(), p2.y(), a_); };
        inline ZQRectF adjustedRadians(const QPointF &p1, const QPointF &p2, qreal a_) noexcept {return adjustedRadians(p1.x(), p1.y(), p2.x(), p2.y(), a_); };


        constexpr inline QSizeF size() const noexcept;
        constexpr inline qreal width() const noexcept;
        constexpr inline qreal height() const noexcept;
        constexpr inline qreal px1() const noexcept {return x(); };
        constexpr inline qreal py1() const noexcept {return y(); };
        constexpr inline qreal px2() const noexcept {return x() + width(); };
        constexpr inline qreal py2() const noexcept {return y() + height(); };
        inline void setWidth(qreal w) noexcept;
        inline void setHeight(qreal h) noexcept;
        inline void setSize(const QSizeF &s) noexcept;

        QPainterPath operator|(const ZQRectF &r) const noexcept;
        QPainterPath operator&(const ZQRectF &r) const noexcept;

        bool contains(const ZQRectF &r, bool proper=false) const noexcept;
        bool contains(const QPointF &p) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQRectF &other) const noexcept;
        inline QPainterPath intersected(const ZQRectF &other) const noexcept;
        bool intersects(const ZQRectF &r) const noexcept;

        inline ZQRectF marginsAdded(const QMarginsF &margins) const noexcept;
        inline ZQRectF marginsRemoved(const QMarginsF &margins) const noexcept;
        inline ZQRectF &operator+=(const QMarginsF &margins) noexcept;
        inline ZQRectF &operator-=(const QMarginsF &margins) noexcept;

        inline ZQRect toRect() const noexcept;
        ZQRect toAlignedRect() const noexcept;

        QPainterPath toPath() const noexcept;
        QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;
        QString toString() const noexcept;

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
        : xp(aleft), yp(atop), w(awidth), h(aheight), a(0)
    {
    }

    inline ZQRectF::ZQRectF(qreal aleft, qreal atop, qreal awidth, qreal aheight, qreal angle) noexcept
        : xp(aleft), yp(atop), w(awidth), h(aheight)
    {
        a = normalizedAngle(angle);
    }

    constexpr inline ZQRectF::ZQRectF(const QPointF &atopLeft, const QPointF &asize) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.x()), h(asize.y()), a(0)
    {
    }

    inline ZQRectF::ZQRectF(const QPointF &atopLeft, const QPointF &asize, qreal angle) noexcept
        : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.x()), h(asize.y())
    {
        a = normalizedAngle(angle);
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

    inline void ZQRectF::rotate(qreal a_) noexcept
    { a += normalizedAngle(a_); }

    inline void ZQRectF::rotateRadians(qreal a_) noexcept
    { a += normalizedAngle(180/M_PI * (a_)); }

    inline ZQRectF ZQRectF::rotated(qreal a_) const noexcept
    { return ZQRect(xp, yp, width(), height(), a + normalizedAngle(a_)); }

    inline ZQRectF ZQRectF::rotatedRadians(qreal a_) const noexcept
    { return ZQRect(xp, yp, width(), height(), a + normalizedAngle(180/M_PI * a_)); }

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

    inline void ZQRectF::translate(qreal dx, qreal dy) noexcept
    {
        xp += dx;
        yp += dy;
    }

    inline void ZQRectF::translate(qreal dx, qreal dy, qreal a_) noexcept
    {
        xp += dx;
        yp += dy;
        a = normalizedAngle(a + a_);
    }

    inline void ZQRectF::translateRadians(qreal dx, qreal dy, qreal a_) noexcept
    {
        xp += dx;
        yp += dy;
        a = normalizedAngle(a + 180/M_PI * a_);
    }

    inline void ZQRectF::translate(const QPointF &p) noexcept
    {
        xp += p.x();
        yp += p.y();
    }

    inline void ZQRectF::translate(const QPointF &p, qreal a_) noexcept
    {
        xp += p.x();
        yp += p.y();
        a = normalizedAngle(a + a_);
    }

    inline void ZQRectF::translateRadians(const QPointF &p, qreal a_) noexcept
    {
        xp += p.x();
        yp += p.y();
        a = normalizedAngle(a + 180/M_PI * a_);
    }

    inline ZQRectF ZQRectF::translated(qreal dx, qreal dy) const noexcept
    { return ZQRectF(xp + dx, yp + dy, w, h, a); }

    inline ZQRectF ZQRectF::translated(qreal dx, qreal dy, qreal a_) const noexcept
    { return ZQRectF(xp + dx, yp + dy, w, h, normalizedAngle(a + a_)); }

    inline ZQRectF ZQRectF::translatedRadians(qreal dx, qreal dy, qreal a_) const noexcept
    { return ZQRectF(xp + dx, yp + dy, w, h, normalizedAngle(a + 180/M_PI * a_)); }

    inline ZQRectF ZQRectF::translated(const QPointF &p) const noexcept
    { return ZQRectF(xp + p.x(), yp + p.y(), w, h, a); }

    inline ZQRectF ZQRectF::translated(const QPointF &p, qreal a_) const noexcept
    { return ZQRectF(xp + p.x(), yp + p.y(), w, h, normalizedAngle(a + a_)); }

    inline ZQRectF ZQRectF::translatedRadians(const QPointF &p, qreal a_) const noexcept
    { return ZQRectF(xp + p.x(), yp + p.y(), w, h, normalizedAngle(a + 180/M_PI * a_)); }

    constexpr inline ZQRectF ZQRectF::transposed() const noexcept
    { return ZQRectF(topLeft(), QPoint(bottomRight().y(), bottomRight().x())); }

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

    inline void ZQRectF::getRectRadians(qreal *ax, qreal *ay, qreal *aaw, qreal *aah, qreal *aaa) const
    {
        *ax = this->xp;
        *ay = this->yp;
        *aaw = this->w;
        *aah = this->h;
        *aaa = M_PI/180 * this->a;
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

    inline void ZQRectF::setRectRadians(qreal ax, qreal ay, qreal aaw, qreal aah, qreal aaa) noexcept
    {
        this->xp = ax;
        this->yp = ay;
        this->w = aaw;
        this->h = aah;
        this->a = normalizedAngle(180/M_PI * aaa);
    }

    inline void ZQRectF::getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
    }

    inline void ZQRectF::getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *a_) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
        *a_ = a;
    }

    inline void ZQRectF::getCoordsRadians(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2, qreal *a_) const
    {
        *xp1 = xp;
        *yp1 = yp;
        *xp2 = xp + w;
        *yp2 = yp + h;
        *a_ = M_PI/180 * a;
    }

    inline void ZQRectF::setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
    }

    inline void ZQRectF::setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal a_) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
        a = normalizedAngle(a_);
    }

    inline void ZQRectF::setCoordsRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal a_) noexcept
    {
        xp = xp1;
        yp = yp1;
        w = xp2 - xp1;
        h = yp2 - yp1;
        a = normalizedAngle(180/M_PI * a_);
    }

    inline void ZQRectF::adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
    { xp += xp1; yp += yp1; w += xp2; h += yp2; }

    inline void ZQRectF::adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal a_) noexcept
    { xp += xp1; yp += yp1; w += xp2; h += yp2; a = normalizedAngle(a + a_); }

    inline void ZQRectF::adjustRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal a_) noexcept
    { xp += xp1; yp += yp1; w += xp2; h += yp2; a = normalizedAngle(a + 180/M_PI * a_); }

    inline ZQRectF ZQRectF::adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2) const noexcept
    { return ZQRectF(xp + xp1, yp + yp1, w + xp2, h + yp2, a); }

    inline ZQRectF ZQRectF::adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal a_) const noexcept
    { return ZQRectF(xp + xp1, yp + yp1, w + xp2, h + yp2, normalizedAngle(a + a_)); }

    inline ZQRectF ZQRectF::adjustedRadians(qreal xp1, qreal yp1, qreal xp2, qreal yp2, qreal a_) const noexcept
    { return ZQRectF(xp + xp1, yp + yp1, w + xp2, h + yp2, normalizedAngle(a + 180/M_PI * a_)); }

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
               || !qFuzzyCompare(r1.w, r2.w) || !qFuzzyCompare(r1.h, r2.h)
               || !qFuzzyCompare(r1.a, r2.a);
    }

    inline ZQRect ZQRectF::toRect() const noexcept
    {
        return ZQRect(QPoint(qRound(xp), qRound(yp)), QPoint(qRound(xp + w) - 1, qRound(yp + h) - 1), a);
    }

    inline ZQRectF operator+(const ZQRectF &lhs, const QMarginsF &rhs) noexcept
    {
        return lhs.adjusted(rhs.left(), rhs.top(), rhs.right(), rhs.bottom());
    }

    inline ZQRectF operator+(const QMarginsF &lhs, const ZQRectF &rhs) noexcept
    {
        return rhs.adjusted(lhs.left(), lhs.top(), lhs.right(), lhs.bottom());
    }

    inline ZQRectF operator-(const ZQRectF &lhs, const QMarginsF &rhs) noexcept
    {
        return lhs.adjusted(-rhs.left(), -rhs.top(), -rhs.right(), -rhs.bottom());
    }

    inline ZQRectF ZQRectF::marginsAdded(const QMarginsF &margins) const noexcept
    {
        return *this + margins;
    }

    inline ZQRectF ZQRectF::marginsRemoved(const QMarginsF &margins) const noexcept
    {
        return *this - margins;
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
