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

#ifndef Z_QPOINT_H
#define Z_QPOINT_H

#define _USE_MATH_DEFINES
#include <tgmath.h>

#include <QtWidgets>
#include <QDataStream>
#include <QDebug>
#include "z_base.h"

namespace z_qtshapes {


    class ZQPoint
    {
    public:
        constexpr ZQPoint();
        constexpr ZQPoint(int xpos, int ypos);

        constexpr inline bool isNull() const;

        constexpr inline int x() const;
        constexpr inline int y() const;

        inline void setX(int x);
        inline void setY(int y);

        constexpr inline int manhattanLength() const;

        constexpr ZQPoint transposed() const noexcept { return {yp, xp}; }

        inline int &rx();
        inline int &ry();

        inline ZQPoint &operator+=(const ZQPoint &p);
        inline ZQPoint &operator-=(const ZQPoint &p);

        inline ZQPoint &operator*=(float factor);
        inline ZQPoint &operator*=(double factor);
        inline ZQPoint &operator*=(int factor);

        inline ZQPoint &operator/=(qreal divisor);

        constexpr static inline int dotProduct(const ZQPoint &p1, const ZQPoint &p2)
        { return p1.xp * p2.xp + p1.yp * p2.yp; }

        friend constexpr inline bool operator==(const ZQPoint &, const ZQPoint &);
        friend constexpr inline bool operator!=(const ZQPoint &, const ZQPoint &);
        friend constexpr inline const ZQPoint operator+(const ZQPoint &, const ZQPoint &);
        friend constexpr inline const ZQPoint operator-(const ZQPoint &, const ZQPoint &);
        friend constexpr inline const ZQPoint operator*(const ZQPoint &, float);
        friend constexpr inline const ZQPoint operator*(float, const ZQPoint &);
        friend constexpr inline const ZQPoint operator*(const ZQPoint &, double);
        friend constexpr inline const ZQPoint operator*(double, const ZQPoint &);
        friend constexpr inline const ZQPoint operator*(const ZQPoint &, int);
        friend constexpr inline const ZQPoint operator*(int, const ZQPoint &);
        friend constexpr inline const ZQPoint operator+(const ZQPoint &);
        friend constexpr inline const ZQPoint operator-(const ZQPoint &);
        friend constexpr inline const ZQPoint operator/(const ZQPoint &, qreal);

        constexpr inline QString toString() const noexcept;
        constexpr inline QPoint toQPoint() const noexcept;

    private:
        friend class QTransform;
        int xp;
        int yp;
    };


    /*****************************************************************************
      ZQPoint stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQPoint &);
    QDataStream &operator>>(QDataStream &, ZQPoint &);
    #endif

    /*****************************************************************************
      ZQPoint inline functions
     *****************************************************************************/

    constexpr inline ZQPoint::ZQPoint() : xp(0), yp(0) {}

    constexpr inline ZQPoint::ZQPoint(int xpos, int ypos) : xp(xpos), yp(ypos) {}

    constexpr inline bool ZQPoint::isNull() const
    { return xp == 0 && yp == 0; }

    constexpr inline int ZQPoint::x() const
    { return xp; }

    constexpr inline int ZQPoint::y() const
    { return yp; }

    inline void ZQPoint::setX(int xpos)
    { xp = xpos; }

    inline void ZQPoint::setY(int ypos)
    { yp = ypos; }

    inline int constexpr ZQPoint::manhattanLength() const
    { return qAbs(x())+qAbs(y()); }

    inline int &ZQPoint::rx()
    { return xp; }

    inline int &ZQPoint::ry()
    { return yp; }

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQPointF(%1,%2))".arg(x1, y1));
    }
    
    constexpr inline QPoint toQPoint() const noexcept
    {
        return QPoint(tmpxp, tmp.yp);
    }

    inline ZQPoint &ZQPoint::operator+=(const ZQPoint &p)
    { xp+=p.xp; yp+=p.yp; return *this; }

    inline ZQPoint &ZQPoint::operator-=(const ZQPoint &p)
    { xp-=p.xp; yp-=p.yp; return *this; }

    inline ZQPoint &ZQPoint::operator*=(float factor)
    { xp = qRound(xp*factor); yp = qRound(yp*factor); return *this; }

    inline ZQPoint &ZQPoint::operator*=(double factor)
    { xp = qRound(xp*factor); yp = qRound(yp*factor); return *this; }

    inline ZQPoint &ZQPoint::operator*=(int factor)
    { xp = xp*factor; yp = yp*factor; return *this; }

    constexpr inline bool operator==(const ZQPoint &p1, const ZQPoint &p2)
    { return p1.xp == p2.xp && p1.yp == p2.yp && p1.a == p2.a; }

    constexpr inline bool operator!=(const ZQPoint &p1, const ZQPoint &p2)
    { return p1.xp != p2.xp || p1.yp != p2.yp; }

    constexpr inline const ZQPoint operator+(const ZQPoint &p1, const ZQPoint &p2)
    { return ZQPoint(p1.xp+p2.xp, p1.yp+p2.yp); }

    constexpr inline const ZQPoint operator-(const ZQPoint &p1, const ZQPoint &p2)
    { return ZQPoint(p1.xp-p2.xp, p1.yp-p2.yp); }

    constexpr inline const ZQPoint operator*(const ZQPoint &p, float factor)
    { return ZQPoint(qRound(p.xp*factor), qRound(p.yp*factor)); }

    constexpr inline const ZQPoint operator*(const ZQPoint &p, double factor)
    { return ZQPoint(qRound(p.xp*factor), qRound(p.yp*factor)); }

    constexpr inline const ZQPoint operator*(const ZQPoint &p, int factor)
    { return ZQPoint(p.xp*factor, p.yp*factor); }

    constexpr inline const ZQPoint operator*(float factor, const ZQPoint &p)
    { return ZQPoint(qRound(p.xp*factor), qRound(p.yp*factor)); }

    constexpr inline const ZQPoint operator*(double factor, const ZQPoint &p)
    { return ZQPoint(qRound(p.xp*factor), qRound(p.yp*factor)); }

    constexpr inline const ZQPoint operator*(int factor, const ZQPoint &p)
    { return ZQPoint(p.xp*factor, p.yp*factor); }

    constexpr inline const ZQPoint operator+(const ZQPoint &p)
    { return p; }

    constexpr inline const ZQPoint operator-(const ZQPoint &p)
    { return ZQPoint(-p.xp, -p.yp); }

    inline ZQPoint &ZQPoint::operator/=(qreal c)
    {
        xp = qRound(xp/c);
        yp = qRound(yp/c);
        return *this;
    }

    constexpr inline const ZQPoint operator/(const ZQPoint &p, qreal c)
    {
        return ZQPoint(qRound(p.xp/c), qRound(p.yp/c));
    }

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug, const ZQPoint &);
    #endif



    class ZQPointF
    {
    public:
        constexpr ZQPointF();
        constexpr ZQPointF(const ZQPoint &p);
        constexpr ZQPointF(const ZQPoint &p, qreal angle);
        constexpr ZQPointF(qreal xpos, qreal ypos);
        constexpr ZQPointF(qreal xpos, qreal ypos, qreal angle);

        constexpr inline qreal manhattanLength() const;

        inline bool isNull() const;

        constexpr inline qreal x() const noexcept;
        constexpr inline qreal y() const noexcept;
        inline void setX(qreal x) noexcept;
        inline void setY(qreal y) noexcept;

        constexpr ZQPointF transposed() const noexcept { return {yp, xp}; }

        inline qreal &rx();
        inline qreal &ry();

        inline ZQPointF &operator+=(const ZQPointF &p);
        inline ZQPointF &operator-=(const ZQPointF &p);
        inline ZQPointF &operator*=(qreal c);
        inline ZQPointF &operator/=(qreal c);

        constexpr static inline qreal dotProduct(const ZQPointF &p1, const ZQPointF &p2)
        { return p1.xp * p2.xp + p1.yp * p2.yp; }

        friend constexpr inline bool operator==(const ZQPointF &, const ZQPointF &);
        friend constexpr inline bool operator!=(const ZQPointF &, const ZQPointF &);
        friend constexpr inline const ZQPointF operator+(const ZQPointF &, const ZQPointF &);
        friend constexpr inline const ZQPointF operator-(const ZQPointF &, const ZQPointF &);
        friend constexpr inline const ZQPointF operator*(qreal, const ZQPointF &);
        friend constexpr inline const ZQPointF operator*(const ZQPointF &, qreal);
        friend constexpr inline const ZQPointF operator+(const ZQPointF &);
        friend constexpr inline const ZQPointF operator-(const ZQPointF &);
        friend constexpr inline const ZQPointF operator/(const ZQPointF &, qreal);

        constexpr QString toString() const noexcept;
        constexpr ZQPoint toPoint() const noexcept;
        constexpr QPointF toQPointF() const noexcept;


    private:
        friend class QMatrix;
        friend class QTransform;

        qreal xp;
        qreal yp;
    };


    /*****************************************************************************
      ZQPointF stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    QDataStream &operator<<(QDataStream &, const ZQPointF &);
    QDataStream &operator>>(QDataStream &, ZQPointF &);
    #endif

    /*****************************************************************************
      ZQPointF inline functions
     *****************************************************************************/

    constexpr inline ZQPointF::ZQPointF() : xp(0), yp(0) { }

    constexpr inline ZQPointF::ZQPointF(qreal xpos, qreal ypos) : xp(xpos), yp(ypos) { }

    constexpr inline ZQPointF::ZQPointF(const ZQPoint &p) : xp(p.x()), yp(p.y()) { }

    constexpr inline qreal ZQPointF::manhattanLength() const
    {
        return qAbs(x())+qAbs(y());
    }

    inline bool ZQPointF::isNull() const
    {
        return qIsNull(xp) && qIsNull(yp);
    }

    constexpr inline qreal ZQPointF::x() const
    {
        return xp;
    }

    constexpr inline qreal ZQPointF::y() const
    {
        return yp;
    }

    inline void ZQPointF::setX(qreal xpos)
    {
        xp = xpos;
    }

    inline void ZQPointF::setY(qreal ypos)
    {
        yp = ypos;
    }

    inline qreal &ZQPointF::rx()
    {
        return xp;
    }

    inline qreal &ZQPointF::ry()
    {
        return yp;
    }

    inline ZQPointF &ZQPointF::operator+=(const ZQPointF &p)
    {
        xp+=p.xp;
        yp+=p.yp;
        return *this;
    }

    inline ZQPointF &ZQPointF::operator-=(const ZQPointF &p)
    {
        xp-=p.xp; yp-=p.yp; return *this;
    }

    inline ZQPointF &ZQPointF::operator*=(qreal c)
    {
        xp*=c; yp*=c; return *this;
    }

    //QT_WARNING_PUSH
    //QT_WARNING_DISABLE_CLANG("-Wfloat-equal")


    constexpr inline bool operator==(const ZQPointF &p1, const ZQPointF &p2)
    {
        return ((!p1.xp || !p2.xp) ? qFuzzyIsNull(p1.xp - p2.xp) : qFuzzyCompare(p1.xp, p2.xp))
            && ((!p1.yp || !p2.yp) ? qFuzzyIsNull(p1.yp - p2.yp) : qFuzzyCompare(p1.yp, p2.yp))
            && p1.a == p2.a;
    }

    constexpr inline bool operator!=(const ZQPointF &p1, const ZQPointF &p2)
    {
        return !(p1 == p2);
    }

    //QT_WARNING_POP

    constexpr inline QString toString() const noexcept
    {
        return QString("ZQPointF(%1,%2))".arg(x1, y1));
    }
    
    constexpr inline QPoint toQPointF() const noexcept
    {
        return QPointF(tmpxp, tmp.yp);
    }

    constexpr inline const ZQPointF operator+(const ZQPointF &p1, const ZQPointF &p2)
    {
        return ZQPointF(p1.xp+p2.xp, p1.yp+p2.yp);
    }

    constexpr inline const ZQPointF operator-(const ZQPointF &p1, const ZQPointF &p2)
    {
        return ZQPointF(p1.xp-p2.xp, p1.yp-p2.yp);
    }

    constexpr inline const ZQPointF operator*(const ZQPointF &p, qreal c)
    {
        return ZQPointF(p.xp*c, p.yp*c);
    }

    constexpr inline const ZQPointF operator*(qreal c, const ZQPointF &p)
    {
        return ZQPointF(p.xp*c, p.yp*c);
    }

    constexpr inline const ZQPointF operator+(const ZQPointF &p)
    {
        return p;
    }

    constexpr inline const ZQPointF operator-(const ZQPointF &p)
    {
        return ZQPointF(-p.xp, -p.yp);
    }

    inline ZQPointF &ZQPointF::operator/=(qreal divisor)
    {
        xp/=divisor;
        yp/=divisor;
        return *this;
    }

    constexpr inline const ZQPointF operator/(const ZQPointF &p, qreal divisor)
    {
        return ZQPointF(p.xp/divisor, p.yp/divisor);
    }

    constexpr inline ZQPoint ZQPointF::toPoint() const
    {
        return ZQPoint(qRound(xp), qRound(yp));
    }

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug d, const ZQPointF &p);
    #endif

}

#endif
