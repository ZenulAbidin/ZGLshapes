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

#ifndef Z_QLINE_H
#define Z_QLINE_H

#define _USE_MATH_DEFINES
#include <tgmath.h>

#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include "z_base.h"

namespace z_qtshapes {


    /*******************************************************************************
     * class ZQLine
     *******************************************************************************/

    class ZQLine
    {
    public:
        constexpr inline ZQLine() noexcept;
        constexpr inline ZQLine(const QPoint &pt1, const QPoint &pt2) noexcept;
        constexpr inline ZQLine(const QPoint &pt1, const QPoint &pt2, int angle) noexcept;
        constexpr inline ZQLine(int x1, int y1, int x2, int y2) noexcept;
        constexpr inline ZQLine(int x1, int y1, int x2, int y2, angle) noexcept;

        constexpr inline bool isNull() const noexcept;

        constexpr inline QPoint p1() const noexcept;
        constexpr inline QPoint p2() const noexcept;

        constexpr inline int x1() const noexcept;
        constexpr inline int y1() const noexcept;

        constexpr inline int x2() const noexcept;
        constexpr inline int y2() const noexcept;

        constexpr inline int dx() const noexcept;
        constexpr inline int dy() const noexcept;

        constexpr inline int angle() const noexcept;
        constexpr inline qreal angleRadians() const noexcept;

        static ZQLineF fromPolar(qreal length, qreal angle) noexcept;

        inline void translate(const QPoint &p) noexcept;
        inline void translate(int dx, int dy) noexcept;

        constexpr inline ZQLine translated(const QPoint &p) const noexcept;
        constexpr inline ZQLine translated(int dx, int dy) const noexcept;

        constexpr inline QPoint center() const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQLine rotated(int da) noexcept;
        constexpr inline ZQLine rotatedRadians(qreal da) noexcept;

        inline int normalizedAngle() noexcept;

        ZQLine normalVector() const noexcept;

        inline void setP1(const QPoint &p1) noexcept;
        inline void setP2(const QPoint &p2) noexcept;
        inline void setAngle(int angle) noexcept;
        inline void setAngleRadians(qreal angle) noexcept;
        inline void setPoints(const QPoint &p1, const QPoint &p2) noexcept;
        inline void setPoints(const QPoint &p1, const QPoint &p2, int angle) noexcept;
        inline void setPointsRadians(const QPoint &p1, const QPoint &p2, qreal angle) noexcept;
        inline void setLine(int x1, int y1, int x2, int y2) noexcept;
        inline void setLine(int x1, int y1, int x2, int y2, int angle) noexcept;
        inline void setLineRadians(int x1, int y1, int x2, int y2, qreal angle) noexcept;

        constexpr inline QString toString() const noexcept;
        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 mat, const QPointF &ref) const noexcept;

        QPainterPath operator|(const ZQLine &r) const noexcept;
        QPainterPath operator&(const ZQLine &r) const noexcept;

        bool contains(const ZQLine &r) const noexcept;
        bool contains(const QPoint &p) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQLine &other) const noexcept;
        inline QPainterPath intersected(const ZQLine &other) const noexcept;
        bool intersects(const ZQLine &r) const noexcept;

        constexpr inline bool operator==(const ZQLine &d) const noexcept;
        constexpr inline bool operator!=(const ZQLine &d) const noexcept { return !(*this == d); }

    private:
        QPoint pt1, pt2;
        int a;
    };

    /*******************************************************************************
     * class ZQLine inline members
     *******************************************************************************/

    constexpr inline ZQLine::ZQLine(): a(0) { }

    constexpr inline ZQLine::ZQLine(const QPoint &pt1_, const QPoint &pt2_) : pt1(pt1_), pt2(pt2_), a(0) { }

    constexpr inline ZQLine::ZQLine(const QPoint &pt1_, const QPoint &pt2_, int a_) : pt1(pt1_), pt2(pt2_), a(normalizedAngle(a_)) { }

    constexpr inline ZQLine::ZQLine(int x1pos, int y1pos, int x2pos, int y2pos) : pt1(QPoint(x1pos, y1pos)), pt2(QPoint(x2pos, y2pos)), a(0) { }

    constexpr inline ZQLine::ZQLine(int x1pos, int y1pos, int x2pos, int y2pos, int a_) : pt1(QPoint(x1pos, y1pos)), pt2(QPoint(x2pos, y2pos)),
        a(normalizedAngle(a_)) { }

    constexpr inline bool ZQLine::isNull() const
    {
        return pt1 == pt2;
    }

    constexpr inline int ZQLine::x1() const
    {
        return pt1.x();
    }

    constexpr inline int ZQLine::y1() const
    {
        return pt1.y();
    }

    constexpr inline int ZQLine::x2() const
    {
        return pt2.x();
    }

    constexpr inline int ZQLine::y2() const
    {
        return pt2.y();
    }

    constexpr inline QPoint ZQLine::p1() const
    {
        return pt1;
    }

    constexpr inline QPoint ZQLine::p2() const
    {
        return pt2;
    }

    constexpr inline int ZQLine::dx() const
    {
        return pt2.x() - pt1.x();
    }

    constexpr inline int ZQLine::dy() const
    {
        return pt2.y() - pt1.y();
    }

    constexpr inline int ZQLine::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQLine::angleRadians() const noexcept
    { return M_PI/180 * a; }

    constexpr inline ZQLine ZQLine::normalVector() const
    {
        return ZQLine(p1(), p1() + QPoint((int) dy(), (int) -dx()));
    }


    inline void ZQLine::translate(const QPoint &point)
    {
        pt1 += point;
        pt2 += point;
    }

    inline void ZQLine::translate(int adx, int ady)
    {
        this->translate(QPoint(adx, ady));
    }

    constexpr inline ZQLine ZQLine::translated(const QPoint &p) const
    {
        return ZQLine(pt1 + p, pt2 + p);
    }

    constexpr inline ZQLine ZQLine::translated(int adx, int ady) const
    {
        return translated(QPoint(adx, ady));
    }

    constexpr inline QPoint ZQLine::center() const
    {
        return QPoint(int((qint64(pt1.x()) + pt2.x()) / 2), int((qint64(pt1.y()) + pt2.y()) / 2));
    }

    inline void ZQLine::rotate(int angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQLine::rotateRadians(qreal angle) const noexcept
    { a += normalizedAngle((int) (180/M_PI * angle)); }

    constexpr inline ZQLine ZQLine::rotate(int angle) const noexcept
    { return ZQLine(p1, p2, a + normalizedAngle(angle)); }

    constexpr inline ZQLine ZQLine::rotateRadians(qreal angle) const noexcept
    { return ZQLine(p1, p2, a + normalizedAngle((int) (180/M_PI * angle))); }

    inline int ZQLine::normalizedAngle(int a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle >= 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQLine::setP1(const QPoint &aP1)
    {
        pt1 = aP1;
    }

    inline void ZQLine::setP2(const QPoint &aP2)
    {
        pt2 = aP2;
    }

    inline void ZQLine::setAngle(int aangle) noexcept
    { a = normalizedAngle(aangle); }

    inline void ZQLine::setAngleRadians(qreal aangle) noexcept
    { a = normalizedAngle((int) (180/M_PI * aangle)); }

    inline void ZQLine::setPoints(const QPoint &aP1, const QPoint &aP2)
    {
        pt1 = aP1;
        pt2 = aP2;
    }

    inline void ZQLine::setPoints(const QPoint &aP1, const QPoint &aP2, int angle)
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle(angle);
    }

    inline void ZQLine::setPointsRadians(const QPoint &aP1, const QPoint &aP2, qreal angle)
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle((int) (180/M_PI * angle));
    }

    inline void ZQLine::setLine(int aX1, int aY1, int aX2, int aY2)
    {
        pt1 = QPoint(aX1, aY1);
        pt2 = QPoint(aX2, aY2);
    }

    inline void ZQLine::setLine(int aX1, int aY1, int aX2, int aY2, int angle)
    {
        pt1 = QPoint(aX1, aY1);
        pt2 = QPoint(aX2, aY2);
        a = normalizedAngle(angle);
    }

    inline void ZQLine::setLineRadians(int aX1, int aY1, int aX2, int aY2, qreal angle)
    {
        pt1 = QPoint(aX1, aY1);
        pt2 = QPoint(aX2, aY2);
        a = normalizedAngle((int) (180/M_PI * angle));
    }

    inline QPainterPath ZQLine::intersected(const ZQLine &r) const noexcept
    {
        return *this & r;
    }

    inline QPainterPath ZQLine::united(const ZQLine &r) const noexcept
    {
        return *this | r;
    }


    constexpr inline bool ZQLine::operator==(const ZQLine &d) const
    {
        return pt1 == d.pt1 && pt2 == d.pt2 && a == d.a;
    }


    inline bool ZQLine::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPointF(ax, ay));
    }


    constexpr inline QString toString() const noexcept
    {
        return QString("ZQLineF(%1,%2 to %3,%4 %5 degrees)").arg(x1, y1, x2, y2, a));
    }


    #ifndef QT_NO_DEBUG_STREAM
    Q_CORE_EXPORT QDebug operator<<(QDebug d, const ZQLine &p);
    #endif

    #ifndef QT_NO_DATASTREAM
    Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const ZQLine &);
    Q_CORE_EXPORT QDataStream &operator>>(QDataStream &, ZQLine &);
    #endif

    /*******************************************************************************
     * class ZQLineF
     *******************************************************************************/
    class ZQLineF {
    public:

        constexpr inline ZQLineF() noexcept;
        constexpr inline ZQLineF(const QPointF &pt1, const QPointF &pt2) noexcept;
        constexpr inline ZQLineF(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        constexpr inline ZQLineF(const ZQLine &line) : pt1(line.p1()), pt2(line.p2()) noexcept { }

        static ZQLineF fromPolar(qreal length, qreal angle) noexcept;

        constexpr inline bool isNull() const noexcept;

        constexpr inline QPointF p1() const noexcept;
        constexpr inline QPointF p2() const noexcept;

        constexpr inline qreal x1() const noexcept;
        constexpr inline qreal y1() const noexcept;

        constexpr inline qreal x2() const noexcept;
        constexpr inline qreal y2() const noexcept;

        constexpr inline qreal dx() const noexcept;
        constexpr inline qreal dy() const noexcept;

        constexpr inline qreal angle() const noexcept;
        constexpr inline qreal angleRadians() const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        constexpr inline ZQLine rotated(int da) noexcept;
        constexpr inline ZQLine rotatedRadians(qreal da) noexcept;

        inline int normalizedAngle() noexcept;

        constexpr qreal length() const noexcept;
        inline void setLength(qreal len) noexcept;

        inline void setAngle(qreal angle) noexcept { a = angle; };
        inline void setAngleRadians(qreal angle) noexcept { a = 180/M_PI * angle; };

        ZQLineF unitVector() const noexcept;
        ZQLineF normalVector() const noexcept;

        constexpr inline QPointF pointAt(qreal t) const noexcept;
        inline void translate(const QPointF &p) noexcept;
        inline void translate(qreal dx, qreal dy) noexcept;

        constexpr inline ZQLineF translated(const QPointF &p) const;
        constexpr inline ZQLineF translated(qreal dx, qreal dy) const;

        constexpr inline QPointF center() const;

        inline void setP1(const QPointF &p1);
        inline void setP2(const QPointF &p2);
        inline void setPoints(const QPointF &p1, const QPointF &p2) noexcept;
        inline void setPoints(const QPointF &p1, const QPointF &p2, qreal angle) noexcept;
        inline void setPointsRadians(const QPointF &p1, const QPointF &p2, qreal angle) noexcept;
        inline void setLine(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void setLine(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle) noexcept;
        inline void setLineRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle) noexcept;

        QPainterPath operator|(const ZQLineF &r) const noexcept;
        QPainterPath operator&(const ZQLineF &r) const noexcept;

        bool contains(const ZQLineF &r) const noexcept;
        bool contains(const QPointF &p) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQLineF &other) const noexcept;
        inline QPainterPath intersected(const ZQLineF &other) const noexcept;
        bool intersects(const ZQLineF &r) const noexcept;


        constexpr inline bool operator==(const ZQLineF &d) const;
        constexpr inline bool operator!=(const ZQLineF &d) const { return !(*this == d); }

        constexpr ZQLine toLine() const;

        constexpr inline QString toString() const noexcept;
        constexpr QPainterPath toPath() const noexcept;
        constexpr QPainterPath toPath(const QMatrix3x3 mat, const QPointF &ref) const noexcept;

    private:
        QPointF pt1, pt2;
        qreal a;
    };

    /*******************************************************************************
     * class ZQLineF inline members
     *******************************************************************************/

    constexpr inline ZQLineF::ZQLineF(): a(0)
    {
    }

    constexpr inline ZQLineF::ZQLineF(const QPointF &apt1, const QPointF &apt2)
        : pt1(apt1), pt2(apt2)
    {
    }

    constexpr inline ZQLineF::ZQLineF(const QPointF &apt1, const QPointF &apt2, qreal angle)
        : pt1(apt1), pt2(apt2), a(normalizedAngle(angle)
    {
    }

    constexpr inline ZQLineF::ZQLineF(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos)
        : pt1(x1pos, y1pos), pt2(x2pos, y2pos)
    {
    }

    constexpr inline ZQLineF::ZQLineF(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos, qreal angle)
        : pt1(x1pos, y1pos), pt2(x2pos, y2pos), a(normalizedAngle(angle))
    {
    }

    constexpr inline qreal ZQLineF::x1() const
    {
        return pt1.x();
    }

    constexpr inline qreal ZQLineF::y1() const
    {
        return pt1.y();
    }

    constexpr inline qreal ZQLineF::x2() const
    {
        return pt2.x();
    }

    constexpr inline qreal ZQLineF::y2() const
    {
        return pt2.y();
    }

    constexpr inline bool ZQLineF::isNull() const
    {
        return qFuzzyCompare(pt1.x(), pt2.x()) && qFuzzyCompare(pt1.y(), pt2.y());
    }

    constexpr inline QPointF ZQLineF::p1() const
    {
        return pt1;
    }

    constexpr inline QPointF ZQLineF::p2() const
    {
        return pt2;
    }

    constexpr inline qreal ZQLineF::dx() const
    {
        return pt2.x() - pt1.x();
    }

    constexpr inline qreal ZQLineF::dy() const
    {
        return pt2.y() - pt1.y();
    }

    constexpr inline qreal ZQLineF::angle() const
    {
        return a;
    }

    constexpr inline qreal ZQLineF::angleRadians() const
    {
        return M_PI/180 * a;
    }

    constexpr inline ZQLineF ZQLineF::normalVector() const
    {
        return ZQLineF(p1(), p1() + QPointF(dy(), -dx()));
    }

    inline void ZQLineF::setAngle(int aangle) noexcept
    { a = normalizedAngle(aangle); }

    inline void ZQLineF::setAngleRadians(qreal aangle) noexcept
    { a = normalizedAngle(180/M_PI * aangle); }


    inline void ZQLineF::translate(const QPointF &point)
    {
        pt1 += point;
        pt2 += point;
    }

    inline void ZQLineF::translate(qreal adx, qreal ady)
    {
        this->translate(QPointF(adx, ady));
    }

    constexpr inline ZQLineF ZQLineF::translated(const QPointF &p) const
    {
        return ZQLineF(pt1 + p, pt2 + p);
    }

    constexpr inline ZQLineF ZQLineF::translated(qreal adx, qreal ady) const
    {
        return translated(QPointF(adx, ady));
    }

    constexpr inline QPointF ZQLineF::center() const
    {
        return QPointF(0.5 * pt1.x() + 0.5 * pt2.x(), 0.5 * pt1.y() + 0.5 * pt2.y());
    }

    inline void ZQLineF::rotate(int angle) const noexcept
    { a += normalizedAngle(angle); }

    inline void ZQLineF::rotateRadians(qreal angle) const noexcept
    { a += normalizedAngle(180/M_PI * angle); }

    constexpr inline ZQLineF ZQLineF::rotate(int angle) const noexcept
    { return ZQLineF(p1, p2, a + normalizedAngle(angle)); }

    constexpr inline ZQLineF ZQLineF::rotateRadians(qreal angle) const noexcept
    { return ZQLineF(p1, p2, a + normalizedAngle(180/M_PI * angle)); }


    inline qreal ZQLineF::normalizedAngle(qreal a) noexcept
    {
        while (a < 0)
            a += 360 * MAX_ROTATIONS;
        while (angle >= 360 * MAX_ROTATIONS)
            a -= 360 * MAX_ROTATIONS;
        return a;
    }

    inline void ZQLineF::setLength(qreal len)
    {
        if (isNull())
            return;
        ZQLineF v = unitVector();
        pt2 = QPointF(pt1.x() + v.dx() * len, pt1.y() + v.dy() * len);
    }

    constexpr inline QPointF ZQLineF::pointAt(qreal t) const
    {
        return QPointF(pt1.x() + (pt2.x() - pt1.x()) * t, pt1.y() + (pt2.y() - pt1.y()) * t);
    }

    constexpr inline ZQLine ZQLineF::toLine() const
    {
        return ZQLine(pt1.toPoint(), pt2.toPoint());
    }


    inline void ZQLineF::setP1(const QPointF &aP1)
    {
        pt1 = aP1;
    }

    inline void ZQLineF::setP2(const QPointF &aP2)
    {
        pt2 = aP2;
    }

    inline void ZQLineF::setPoints(const QPointF &aP1, const QPointF &aP2)
    {
        pt1 = aP1;
        pt2 = aP2;
    }

    inline void ZQLineF::setPoints(const QPointF &aP1, const QPointF &aP2, qreal angle)
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle(angle);
    }

    inline void ZQLineF::setPointsRadians(const QPointF &aP1, const QPointF &aP2, qreal angle)
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle(180/M_PI * angle);
    }

    inline void ZQLineF::setLine(qreal aX1, qreal aY1, qreal aX2, qreal aY2)
    {
        pt1 = QPointF(aX1, aY1);
        pt2 = QPointF(aX2, aY2);
    }

    inline void ZQLineF::setLine(qreal aX1, qreal aY1, qreal aX2, qreal aY2, qreal angle)
    {
        pt1 = QPointF(aX1, aY1);
        pt2 = QPointF(aX2, aY2);
        a = normalizedAngle(angle);
    }

    inline void ZQLineF::setLineRadians(qreal aX1, qreal aY1, qreal aX2, qreal aY2, qreal angle)
    {
        pt1 = QPointF(aX1, aY1);
        pt2 = QPointF(aX2, aY2);
        a = normalizedAngle(180/M_PI * angle);
    }


    inline QPainterPath ZQLineF::intersected(const ZQLineF &r) const noexcept
    {
        return *this & r;
    }

    inline QPainterPath ZQLineF::united(const ZQLineF &r) const noexcept
    {
        return *this | r;
    }


    constexpr inline bool ZQLineF::operator==(const ZQLineF &d) const
    {
        return pt1 == d.pt1 && pt2 == d.pt2 && a == d.a;
    }


    inline bool ZQLineF::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPointF(ax, ay));
    }


    constexpr inline QString toString() const noexcept
    {
        return QString("ZQLineF(%1,%2 to %3,%4 %5 degrees)").arg(x1, y1, x2, y2, a));
    }

    #ifndef QT_NO_DEBUG_STREAM
    Q_CORE_EXPORT QDebug operator<<(QDebug d, const ZQLineF &p);
    #endif

    #ifndef QT_NO_DATASTREAM
    Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const ZQLineF &);
    Q_CORE_EXPORT QDataStream &operator>>(QDataStream &, ZQLineF &);
    #endif

}
