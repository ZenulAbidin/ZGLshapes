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
        inline ZQLine(const QPoint &pt1, const QPoint &pt2, int angle) noexcept;
        constexpr inline ZQLine(int x1, int y1, int x2, int y2) noexcept;
        inline ZQLine(int x1, int y1, int x2, int y2, int angle) noexcept;

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

        static ZQLine fromPolar(int length, int angle) noexcept;

        inline void translate(const QPoint &p) noexcept;
        inline void translate(const QPoint &p, int a_) noexcept;
        inline void translateRadians(const QPoint &p, qreal a_) noexcept;
        inline void translate(int dx, int dy) noexcept;
        inline void translate(int dx, int dy, int a_) noexcept;
        inline void translateRadians(int dx, int dy, qreal a_) noexcept;


        constexpr inline ZQLine translated(const QPoint &p) const noexcept;
        inline ZQLine translated(const QPoint &p, int a_) const noexcept;
        inline ZQLine translatedRadians(const QPoint &p, qreal a_) const noexcept;
        constexpr inline ZQLine translated(int dx, int dy) const noexcept;
        inline ZQLine translated(int dx, int dy, int a_) const noexcept;
        inline ZQLine translatedRadians(int dx, int dy, qreal a_) const noexcept;


        inline void adjust(const QPoint &p1, const QPoint &p2) noexcept;
        inline void adjust(const QPoint &p1, const QPoint &p2, int a_) noexcept;
        inline void adjustRadians(const QPoint &p1, const QPoint &p2, qreal a_) noexcept;
        inline void adjust(int dx1, int dy1, int dx2, int dy2) noexcept;
        inline void adjust(int dx1, int dy1, int dx2, int dy2, int a_) noexcept;
        inline void adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal a_) noexcept;

        inline ZQLine adjusted(const QPoint &p1, const QPoint &p2) const noexcept;
        inline ZQLine adjusted(const QPoint &p1, const QPoint &p2, int a_) const noexcept;
        inline ZQLine adjustedRadians(const QPoint &p1, const QPoint &p2, qreal a_) const noexcept;
        inline ZQLine adjusted(int dx1, int dy1, int dx2, int dy2) const noexcept;
        inline ZQLine adjusted(int dx1, int dy1, int dx2, int dy2, int a_) const noexcept;
        inline ZQLine adjustedRadians(int dx1, int dy1, int dx2, int dy2, qreal a_) const noexcept;

        constexpr inline QPoint center() const noexcept;

        inline void rotate(int da) noexcept;
        inline void rotateRadians(qreal da) noexcept;
        inline ZQLine rotated(int da) const noexcept;
        inline ZQLine rotatedRadians(qreal da) const noexcept;

        constexpr ZQLine normalVector() const noexcept;

        inline void setP1(const QPoint &p1) noexcept;
        inline void setP2(const QPoint &p2) noexcept;
        inline void setAngle(int a_) noexcept;
        inline void setAngleRadians(qreal a_) noexcept;
        inline void setPoints(const QPoint &p1, const QPoint &p2) noexcept;
        inline void setPoints(const QPoint &p1, const QPoint &p2, int angle) noexcept;
        inline void setPointsRadians(const QPoint &p1, const QPoint &p2, qreal angle) noexcept;
        inline void setCoords(int x1, int y1, int x2, int y2) noexcept;
        inline void setCoords(int x1, int y1, int x2, int y2, int angle) noexcept;
        inline void setCoordsRadians(int x1, int y1, int x2, int y2, qreal angle) noexcept;
        inline void getCoords(int *x1, int *y1, int *x2, int *y2) const;
        inline void getCoords(int *x1, int *y1, int *x2, int *y2, int *a) const;
        inline void getCoordsRadians(int *x1, int *y1, int *x2, int *y2, qreal *angle) const;

        QString toString() const noexcept;
        QPainterPath toPath() const noexcept;
        QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;

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

    constexpr inline ZQLine::ZQLine() noexcept: a(0) { }

    constexpr inline ZQLine::ZQLine(const QPoint &pt1_, const QPoint &pt2_) noexcept: pt1(pt1_), pt2(pt2_), a(0) { }

    inline ZQLine::ZQLine(const QPoint &pt1_, const QPoint &pt2_, int a_) noexcept: pt1(pt1_), pt2(pt2_)
    {
        a = normalizedAngle(a_);
    }

    constexpr inline ZQLine::ZQLine(int x1pos, int y1pos, int x2pos, int y2pos) noexcept: pt1(QPoint(x1pos, y1pos)), pt2(QPoint(x2pos, y2pos)), a(0) { }

    inline ZQLine::ZQLine(int x1pos, int y1pos, int x2pos, int y2pos, int a_) noexcept: pt1(QPoint(x1pos, y1pos)), pt2(QPoint(x2pos, y2pos))
    {
        a = normalizedAngle(a_);
    }

    constexpr inline bool ZQLine::isNull() const noexcept
    {
        return pt1 == pt2;
    }

    constexpr inline int ZQLine::x1() const noexcept
    {
        return pt1.x();
    }

    constexpr inline int ZQLine::y1() const noexcept
    {
        return pt1.y();
    }

    constexpr inline int ZQLine::x2() const noexcept
    {
        return pt2.x();
    }

    constexpr inline int ZQLine::y2() const noexcept
    {
        return pt2.y();
    }

    constexpr inline QPoint ZQLine::p1() const noexcept
    {
        return pt1;
    }

    constexpr inline QPoint ZQLine::p2() const noexcept
    {
        return pt2;
    }

    constexpr inline int ZQLine::dx() const noexcept
    {
        return pt2.x() - pt1.x();
    }

    constexpr inline int ZQLine::dy() const noexcept
    {
        return pt2.y() - pt1.y();
    }

    constexpr inline int ZQLine::angle() const noexcept
    { return a; }

    constexpr inline qreal ZQLine::angleRadians() const noexcept
    { return M_PI/180 * a; }

    constexpr inline ZQLine ZQLine::normalVector() const noexcept
    {
        return ZQLine(p1(), p1() + QPoint((int) dy(), (int) -dx()));
    }


    inline void ZQLine::translate(const QPoint &point) noexcept
    {
        pt1 += point;
        pt2 += point;
    }

    inline void ZQLine::translate(const QPoint &point, int a_) noexcept
    {
        pt1 += point;
        pt2 += point;
        a += normalizedAngle(a_);
    }

    inline void ZQLine::translateRadians(const QPoint &point, qreal a_) noexcept
    {
        pt1 += point;
        pt2 += point;
        a += normalizedAngle((int) (180/M_PI * a_));
    }

    inline void ZQLine::translate(int adx, int ady) noexcept
    {
        this->translate(QPoint(adx, ady));
    }

    inline void ZQLine::translate(int adx, int ady, int a_) noexcept
    {
        this->translate(QPoint(adx, ady), a_);
    }

    inline void ZQLine::translateRadians(int adx, int ady, qreal a_) noexcept
    {
        this->translateRadians(QPoint(adx, ady), a_);
    }

    constexpr inline ZQLine ZQLine::translated(const QPoint &p) const noexcept
    {
        return ZQLine(pt1 + p, pt2 + p);
    }

    inline ZQLine ZQLine::translated(const QPoint &p, int a_) const noexcept
    {
        return ZQLine(pt1 + p, pt2 + p, a + normalizedAngle(a_));
    }

    inline ZQLine ZQLine::translatedRadians(const QPoint &p, qreal a_) const noexcept
    {
        return ZQLine(pt1 + p, pt2 + p, a + normalizedAngle(a_));
    }

    constexpr inline ZQLine ZQLine::translated(int adx, int ady) const noexcept
    {
        return translated(QPoint(adx, ady));
    }

    inline ZQLine ZQLine::translated(int adx, int ady, int a_) const noexcept
    {
        return translated(QPoint(adx, ady), a_);
    }
    inline ZQLine ZQLine::translatedRadians(int adx, int ady, qreal a_) const noexcept
    {
        return translatedRadians(QPoint(adx, ady), a_);
    }



    inline void ZQLine::adjust(const QPoint &point, const QPoint &point2) noexcept
    {
        pt1 += point;
        pt2 += point2;
    }

    inline void ZQLine::adjust(const QPoint &point, const QPoint &point2, int a_) noexcept
    {
        pt1 += point;
        pt2 += point2;
        a += normalizedAngle(a_);
    }

    inline void ZQLine::adjustRadians(const QPoint &point, const QPoint &point2, qreal a_) noexcept
    {
        pt1 += point;
        pt2 += point2;
        a += normalizedAngle((int) (180/M_PI * a_));
    }

    inline void ZQLine::adjust(int adx1, int ady1, int adx2, int ady2) noexcept
    {
        this->adjust(QPoint(adx1, ady1), QPoint(adx2, ady2));
    }

    inline void ZQLine::adjust(int adx1, int ady1, int adx2, int ady2, int a_) noexcept
    {
        this->adjust(QPoint(adx1, ady1), QPoint(adx2, ady2), a_);
    }

    inline void ZQLine::adjustRadians(int adx1, int ady1, int adx2, int ady2, qreal a_) noexcept
    {
        this->adjustRadians(QPoint(adx1, ady1), QPoint(adx2, ady2), a_);
    }

    inline ZQLine ZQLine::adjusted(const QPoint &p, const QPoint &p2) const noexcept
    {
        return ZQLine(pt1 + p, pt2 + p2, a);
    }

    inline ZQLine ZQLine::adjusted(const QPoint &p, const QPoint &p2, int a_) const noexcept
    {
        return ZQLine(pt1 + p, pt2 + p2, a + normalizedAngle(a_));
    }

    inline ZQLine ZQLine::adjustedRadians(const QPoint &p, const QPoint &p2, qreal a_) const noexcept
    {
        return ZQLine(pt1 + p, pt2 + p2, a + normalizedAngle(a_));
    }

    inline ZQLine ZQLine::adjusted(int adx1, int ady1, int adx2, int ady2) const noexcept
    {
        return adjusted(QPoint(adx1, ady1), QPoint(adx2, ady2), a);
    }

    inline ZQLine ZQLine::adjusted(int adx1, int ady1, int adx2, int ady2, int a_) const noexcept
    {
        return adjusted(QPoint(adx1, ady1), QPoint(adx2, ady2), a_);
    }
    inline ZQLine ZQLine::adjustedRadians(int adx1, int ady1, int adx2, int ady2, qreal a_) const noexcept
    {
        return adjustedRadians(QPoint(adx1, ady1), QPoint(adx2, ady2), a_);
    }


    constexpr inline QPoint ZQLine::center() const noexcept
    {
        return QPoint(int((qint64(pt1.x()) + pt2.x()) / 2), int((qint64(pt1.y()) + pt2.y()) / 2));
    }

    inline void ZQLine::rotate(int a_) noexcept
    { a += normalizedAngle(a_); }

    inline void ZQLine::rotateRadians(qreal a_) noexcept
    { a += normalizedAngle((int) (180/M_PI * a_)); }

    inline ZQLine ZQLine::rotated(int a_) const noexcept
    { return ZQLine(pt1, pt2, a + normalizedAngle(a_)); }

    inline ZQLine ZQLine::rotatedRadians(qreal a_) const noexcept
    { return ZQLine(pt1, pt2, a + normalizedAngle((int) (180/M_PI * a_))); }

    inline void ZQLine::setP1(const QPoint &aP1) noexcept
    {
        pt1 = aP1;
    }

    inline void ZQLine::setP2(const QPoint &aP2) noexcept
    {
        pt2 = aP2;
    }

    inline void ZQLine::setAngle(int aangle) noexcept
    { a = normalizedAngle(aangle); }

    inline void ZQLine::setAngleRadians(qreal aangle) noexcept
    { a = normalizedAngle((int) (180/M_PI * aangle)); }

    inline void ZQLine::setPoints(const QPoint &aP1, const QPoint &aP2) noexcept
    {
        pt1 = aP1;
        pt2 = aP2;
    }

    inline void ZQLine::setPoints(const QPoint &aP1, const QPoint &aP2, int angle) noexcept
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle(angle);
    }

    inline void ZQLine::setPointsRadians(const QPoint &aP1, const QPoint &aP2, qreal angle) noexcept
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle((int) (180/M_PI * angle));
    }

    inline void ZQLine::setCoords(int aX1, int aY1, int aX2, int aY2) noexcept
    {
        pt1 = QPoint(aX1, aY1);
        pt2 = QPoint(aX2, aY2);
    }

    inline void ZQLine::setCoords(int aX1, int aY1, int aX2, int aY2, int angle) noexcept
    {
        pt1 = QPoint(aX1, aY1);
        pt2 = QPoint(aX2, aY2);
        a = normalizedAngle(angle);
    }

    inline void ZQLine::setCoordsRadians(int aX1, int aY1, int aX2, int aY2, qreal angle) noexcept
    {
        pt1 = QPoint(aX1, aY1);
        pt2 = QPoint(aX2, aY2);
        a = normalizedAngle((int) (180/M_PI * angle));
    }


    inline void ZQLine::getCoords(int *x1, int *y1, int *x2, int *y2) const
    {
        *x1 = pt1.x();
        *y1 = pt1.y();
        *x2 = pt2.x();
        *y2 = pt2.y();
    }

    inline void ZQLine::getCoords(int *x1, int *y1, int *x2, int *y2, int *a_) const
    {
        *x1 = pt1.x();
        *y1 = pt1.y();
        *x2 = pt2.x();
        *y2 = pt2.y();
        *a_ = this->a;
    }

    inline void ZQLine::getCoordsRadians(int *x1, int *y1, int *x2, int *y2, qreal *a_) const
    {
        *x1 = pt1.x();
        *y1 = pt1.y();
        *x2 = pt2.x();
        *y2 = pt2.y();
        *a_ = M_PI/180 * a;
    }


    inline QPainterPath ZQLine::intersected(const ZQLine &r) const noexcept
    {
        return *this & r;
    }

    inline QPainterPath ZQLine::united(const ZQLine &r) const noexcept
    {
        return *this | r;
    }


    constexpr inline bool ZQLine::operator==(const ZQLine &d) const noexcept
    {
        return pt1 == d.pt1 && pt2 == d.pt2 && a == d.a;
    }

    inline bool ZQLine::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPoint(ax, ay));
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
        inline ZQLineF(const QPointF &pt1, const QPointF &pt2, qreal a_) noexcept;
        constexpr inline ZQLineF(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline ZQLineF(qreal x1, qreal y1, qreal x2, qreal y2, qreal a_) noexcept;
        constexpr inline ZQLineF(const ZQLine &line) noexcept: pt1(line.p1()), pt2(line.p2()), a(line.angle()) { };

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
        inline ZQLineF rotated(int da) const noexcept;
        inline ZQLineF rotatedRadians(qreal da) const noexcept;


        qreal length() const noexcept;
        inline void setLength(qreal len) noexcept;

        inline void setAngle(qreal a_) noexcept { a = normalizedAngle(a_); };
        inline void setAngleRadians(qreal a_) noexcept { a = normalizedAngle(180/M_PI * a_); };

        ZQLineF unitVector() const noexcept;
        constexpr ZQLineF normalVector() const noexcept;
        constexpr inline QPointF pointAt(qreal t) const noexcept;

        inline void translate(const QPointF &p) noexcept;
        inline void translate(const QPointF &p, qreal a_) noexcept;
        inline void translateRadians(const QPointF &p, qreal a_) noexcept;
        inline void translate(qreal dx, qreal dy) noexcept;
        inline void translate(qreal dx, qreal dy, qreal a_) noexcept;
        inline void translateRadians(qreal dx, qreal dy, qreal a_) noexcept;

        constexpr inline ZQLineF translated(const QPointF &p) const noexcept;
        inline ZQLineF translated(const QPointF &p, qreal a_) const noexcept;
        inline ZQLineF translatedRadians(const QPointF &p, qreal a_) const noexcept;
        constexpr inline ZQLineF translated(qreal dx, qreal dy) const noexcept;
        inline ZQLineF translated(qreal dx, qreal dy, qreal a_) const noexcept;
        inline ZQLineF translatedRadians(qreal dx, qreal dy, qreal a_) const noexcept;

        inline void adjust(const QPointF &p1, const QPointF &p2) noexcept;
        inline void adjust(const QPointF &p1, const QPointF &p2, qreal a_) noexcept;
        inline void adjustRadians(const QPointF &p1, const QPointF &p2, qreal a_) noexcept;
        inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2) noexcept;
        inline void adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal a_) noexcept;
        inline void adjustRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal a_) noexcept;

        inline ZQLineF adjusted(const QPointF &p1, const QPointF &p2) const noexcept;
        inline ZQLineF adjusted(const QPointF &p1, const QPointF &p2, qreal a_) const noexcept;
        inline ZQLineF adjustedRadians(const QPointF &p1, const QPointF &p2, qreal a_) const noexcept;
        inline ZQLineF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2) const noexcept;
        inline ZQLineF adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal a_) const noexcept;
        inline ZQLineF adjustedRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal a_) const noexcept;

        constexpr inline QPointF center() const noexcept;

        inline void setP1(const QPointF &p1) noexcept;
        inline void setP2(const QPointF &p2) noexcept;
        inline void setPoints(const QPointF &p1, const QPointF &p2) noexcept;
        inline void setPoints(const QPointF &p1, const QPointF &p2, qreal angle) noexcept;
        inline void setPointsRadians(const QPointF &p1, const QPointF &p2, qreal angle) noexcept;
        inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
        inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle) noexcept;
        inline void setCoordsRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle) noexcept;
        inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const;
        inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *a) const;
        inline void getCoordsRadians(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *angle) const;

        QPainterPath operator|(const ZQLineF &r) const noexcept;
        QPainterPath operator&(const ZQLineF &r) const noexcept;

        bool contains(const ZQLineF &r) const noexcept;
        bool contains(const QPointF &p) const noexcept;
        inline bool contains(qreal x, qreal y) const noexcept;
        inline QPainterPath united(const ZQLineF &other) const noexcept;
        inline QPainterPath intersected(const ZQLineF &other) const noexcept;
        bool intersects(const ZQLineF &r) const noexcept;


        constexpr inline bool operator==(const ZQLineF &d) const noexcept;
        constexpr inline bool operator!=(const ZQLineF &d) const noexcept { return !(*this == d); }

        constexpr ZQLine toLine() const noexcept;

        QString toString() const noexcept;
        QPainterPath toPath() const noexcept;
        QPainterPath toPath(const QMatrix3x3 &mat, const QPointF &ref) const noexcept;

    private:
        QPointF pt1, pt2;
        qreal a;
    };

    /*******************************************************************************
     * class ZQLineF inline members
     *******************************************************************************/

    constexpr inline ZQLineF::ZQLineF() noexcept: a(0)
    {
    }

    constexpr inline ZQLineF::ZQLineF(const QPointF &apt1, const QPointF &apt2) noexcept
        : pt1(apt1), pt2(apt2), a(0)
    {
    }

    inline ZQLineF::ZQLineF(const QPointF &apt1, const QPointF &apt2, qreal a_) noexcept
        : pt1(apt1), pt2(apt2)
    {
        a = normalizedAngle(a_);
    }

    constexpr inline ZQLineF::ZQLineF(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos) noexcept
        : pt1(x1pos, y1pos), pt2(x2pos, y2pos), a(0)
    {
    }

    inline ZQLineF::ZQLineF(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos, qreal a_) noexcept
        : pt1(x1pos, y1pos), pt2(x2pos, y2pos)
    {
        a = normalizedAngle(a_);
    }

    constexpr inline qreal ZQLineF::x1() const noexcept
    {
        return pt1.x();
    }

    constexpr inline qreal ZQLineF::y1() const noexcept
    {
        return pt1.y();
    }

    constexpr inline qreal ZQLineF::x2() const noexcept
    {
        return pt2.x();
    }

    constexpr inline qreal ZQLineF::y2() const noexcept
    {
        return pt2.y();
    }

    constexpr inline bool ZQLineF::isNull() const noexcept
    {
        return qFuzzyCompare(pt1.x(), pt2.x()) && qFuzzyCompare(pt1.y(), pt2.y());
    }

    constexpr inline QPointF ZQLineF::p1() const noexcept
    {
        return pt1;
    }

    constexpr inline QPointF ZQLineF::p2() const noexcept
    {
        return pt2;
    }

    constexpr inline qreal ZQLineF::dx() const noexcept
    {
        return pt2.x() - pt1.x();
    }

    constexpr inline qreal ZQLineF::dy() const noexcept
    {
        return pt2.y() - pt1.y();
    }

    constexpr inline qreal ZQLineF::angle() const noexcept
    {
        return a;
    }

    constexpr inline qreal ZQLineF::angleRadians() const noexcept
    {
        return M_PI/180 * a;
    }

    constexpr inline ZQLineF ZQLineF::normalVector() const noexcept
    {
        return ZQLineF(p1(), p1() + QPointF(dy(), -dx()));
    }


    inline void ZQLineF::translate(const QPointF &point) noexcept
    {
        pt1 += point;
        pt2 += point;
    }

    inline void ZQLineF::translate(const QPointF &point, qreal a_) noexcept
    {
        pt1 += point;
        pt2 += point;
        a = normalizedAngle(a + a_);
    }

    inline void ZQLineF::translateRadians(const QPointF &point, qreal a_) noexcept
    {
        pt1 += point;
        pt2 += point;
        a = normalizedAngle(a + (int) (180/M_PI * a_));
    }

    inline void ZQLineF::translate(qreal adx, qreal ady) noexcept
    {
        this->translate(QPointF(adx, ady));
    }

    inline void ZQLineF::translate(qreal adx, qreal ady, qreal a_) noexcept
    {
        this->translate(QPointF(adx, ady), a_);
    }

    inline void ZQLineF::translateRadians(qreal adx, qreal ady, qreal a_) noexcept
    {
        this->translateRadians(QPointF(adx, ady), a_);
    }

    constexpr inline ZQLineF ZQLineF::translated(const QPointF &p) const noexcept
    {
        return ZQLineF(pt1 + p, pt2 + p);
    }

    inline ZQLineF ZQLineF::translated(const QPointF &p, qreal a_) const noexcept
    {
        return ZQLineF(pt1 + p, pt2 + p, normalizedAngle(a + a_));
    }

    inline ZQLineF ZQLineF::translatedRadians(const QPointF &p, qreal a_) const noexcept
    {
        return ZQLineF(pt1 + p, pt2 + p, normalizedAngle(a + a_));
    }

    constexpr inline ZQLineF ZQLineF::translated(qreal adx, qreal ady) const noexcept
    {
        return translated(QPointF(adx, ady));
    }

    inline ZQLineF ZQLineF::translated(qreal adx, qreal ady, qreal a_) const noexcept
    {
        return translated(QPointF(adx, ady), a_);
    }
    inline ZQLineF ZQLineF::translatedRadians(qreal adx, qreal ady, qreal a_) const noexcept
    {
        return translatedRadians(QPointF(adx, ady), a_);
    }


    inline void ZQLineF::adjust(const QPointF &point, const QPointF &point2) noexcept
    {
        pt1 += point;
        pt2 += point2;
    }

    inline void ZQLineF::adjust(const QPointF &point, const QPointF &point2, qreal a_) noexcept
    {
        pt1 += point;
        pt2 += point2;
        a = normalizedAngle(a + a_);
    }

    inline void ZQLineF::adjustRadians(const QPointF &point, const QPointF &point2, qreal a_) noexcept
    {
        pt1 += point;
        pt2 += point2;
        a = normalizedAngle(a + (int) (180/M_PI * a_));
    }

    inline void ZQLineF::adjust(qreal adx1, qreal ady1, qreal adx2, qreal ady2) noexcept
    {
        this->adjust(QPointF(adx1, ady1), QPointF(adx2, ady2));
    }

    inline void ZQLineF::adjust(qreal adx1, qreal ady1, qreal adx2, qreal ady2, qreal a_) noexcept
    {
        this->adjust(QPointF(adx1, ady1), QPointF(adx2, ady2), a_);
    }

    inline void ZQLineF::adjustRadians(qreal adx1, qreal ady1, qreal adx2, qreal ady2, qreal a_) noexcept
    {
        this->adjustRadians(QPointF(adx1, ady1), QPointF(adx2, ady2), a_);
    }

    inline ZQLineF ZQLineF::adjusted(const QPointF &p, const QPointF &p2) const noexcept
    {
        return ZQLineF(pt1 + p, pt2 + p2, a);
    }

    inline ZQLineF ZQLineF::adjusted(const QPointF &p, const QPointF &p2, qreal a_) const noexcept
    {
        return ZQLineF(pt1 + p, pt2 + p2, normalizedAngle(a + a_));
    }

    inline ZQLineF ZQLineF::adjustedRadians(const QPointF &p, const QPointF &p2, qreal a_) const noexcept
    {
        return ZQLineF(pt1 + p, pt2 + p2, normalizedAngle(a + a_));
    }

    inline ZQLineF ZQLineF::adjusted(qreal adx1, qreal ady1, qreal adx2, qreal ady2) const noexcept
    {
        return adjusted(QPointF(adx1, ady1), QPointF(adx2, ady2), a);
    }

    inline ZQLineF ZQLineF::adjusted(qreal adx1, qreal ady1, qreal adx2, qreal ady2, qreal a_) const noexcept
    {
        return adjusted(QPointF(adx1, ady1), QPointF(adx2, ady2), a_);
    }
    inline ZQLineF ZQLineF::adjustedRadians(qreal adx1, qreal ady1, qreal adx2, qreal ady2, qreal a_) const noexcept
    {
        return adjustedRadians(QPointF(adx1, ady1), QPointF(adx2, ady2), a_);
    }


    constexpr inline QPointF ZQLineF::center() const noexcept
    {
        return QPointF(0.5 * pt1.x() + 0.5 * pt2.x(), 0.5 * pt1.y() + 0.5 * pt2.y());
    }

    inline void ZQLineF::rotate(int a_) noexcept
    { a = normalizedAngle(a + a_); }

    inline void ZQLineF::rotateRadians(qreal a_) noexcept
    { a = normalizedAngle(a + 180/M_PI * a_); }

    inline ZQLineF ZQLineF::rotated(int a_) const noexcept
    { return ZQLineF(pt1, pt2, normalizedAngle(a + a_)); }

    inline ZQLineF ZQLineF::rotatedRadians(qreal a_) const noexcept
    { return ZQLineF(pt1, pt2, normalizedAngle(a + 180/M_PI * a_)); }


    inline void ZQLineF::setLength(qreal len) noexcept
    {
        if (isNull())
            return;
        ZQLineF v = unitVector();
        pt2 = QPointF(pt1.x() + v.dx() * len, pt1.y() + v.dy() * len);
    }

    constexpr inline QPointF ZQLineF::pointAt(qreal t) const noexcept
    {
        return QPointF(pt1.x() + (pt2.x() - pt1.x()) * t, pt1.y() + (pt2.y() - pt1.y()) * t);
    }

    constexpr inline ZQLine ZQLineF::toLine() const noexcept
    {
        return ZQLine(pt1.toPoint(), pt2.toPoint());
    }


    inline void ZQLineF::setP1(const QPointF &aP1) noexcept
    {
        pt1 = aP1;
    }

    inline void ZQLineF::setP2(const QPointF &aP2) noexcept
    {
        pt2 = aP2;
    }

    inline void ZQLineF::setPoints(const QPointF &aP1, const QPointF &aP2) noexcept
    {
        pt1 = aP1;
        pt2 = aP2;
    }

    inline void ZQLineF::setPoints(const QPointF &aP1, const QPointF &aP2, qreal angle) noexcept
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle(angle);
    }

    inline void ZQLineF::setPointsRadians(const QPointF &aP1, const QPointF &aP2, qreal angle) noexcept
    {
        pt1 = aP1;
        pt2 = aP2;
        a = normalizedAngle(180/M_PI * angle);
    }

    inline void ZQLineF::setCoords(qreal aX1, qreal aY1, qreal aX2, qreal aY2) noexcept
    {
        pt1 = QPointF(aX1, aY1);
        pt2 = QPointF(aX2, aY2);
    }

    inline void ZQLineF::setCoords(qreal aX1, qreal aY1, qreal aX2, qreal aY2, qreal a_) noexcept
    {
        pt1 = QPointF(aX1, aY1);
        pt2 = QPointF(aX2, aY2);
        a = normalizedAngle(a_);
    }

    inline void ZQLineF::setCoordsRadians(qreal aX1, qreal aY1, qreal aX2, qreal aY2, qreal a_) noexcept
    {
        pt1 = QPointF(aX1, aY1);
        pt2 = QPointF(aX2, aY2);
        a = normalizedAngle(180/M_PI * a_);
    }

    inline void ZQLineF::getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const
    {
        *x1 = pt1.x();
        *y1 = pt1.y();
        *x2 = pt2.x();
        *y2 = pt2.y();
    }

    inline void ZQLineF::getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *a_) const
    {
        *x1 = pt1.x();
        *y1 = pt1.y();
        *x2 = pt2.x();
        *y2 = pt2.y();
        *a_ = this->a;
    }

    inline void ZQLineF::getCoordsRadians(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *a_) const
    {
        *x1 = pt1.x();
        *y1 = pt1.y();
        *x2 = pt2.x();
        *y2 = pt2.y();
        *a_ = M_PI/180 * a;
    }



    inline QPainterPath ZQLineF::intersected(const ZQLineF &r) const noexcept
    {
        return *this & r;
    }

    inline QPainterPath ZQLineF::united(const ZQLineF &r) const noexcept
    {
        return *this | r;
    }


    constexpr inline bool ZQLineF::operator==(const ZQLineF &d) const noexcept
    {
        return pt1 == d.pt1 && pt2 == d.pt2 && a == d.a;
    }

    inline bool ZQLineF::contains(qreal ax, qreal ay) const noexcept
    {
        return contains(QPointF(ax, ay));
    }



    #ifndef QT_NO_DEBUG_STREAM
    Q_CORE_EXPORT QDebug operator<<(QDebug d, const ZQLineF &p);
    #endif

    #ifndef QT_NO_DATASTREAM
    Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const ZQLineF &);
    Q_CORE_EXPORT QDataStream &operator>>(QDataStream &, ZQLineF &);
    #endif

}

#endif
