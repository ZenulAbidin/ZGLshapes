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

#include "z_qpoint.h"

namespace z_qtshapes {

    /*!
        \class ZQPoint
        \inmodule QtCore
        \ingroup painting
        \reentrant
        \brief The ZQPoint class defines a point in the plane using integer
        precision.
        A point is specified by a x coordinate and an y coordinate which
        can be accessed using the x() and y() functions. The isNull()
        function returns \c true if both x and y are set to 0. The
        coordinates can be set (or altered) using the setX() and setY()
        functions, or alternatively the rx() and ry() functions which
        return references to the coordinates (allowing direct
        manipulation).
        Given a point \e p, the following statements are all equivalent:
        \snippet code/src_corelib_tools_qpoint.cpp 0
        A ZQPoint object can also be used as a vector: Addition and
        subtraction are defined as for vectors (each component is added
        separately). A ZQPoint object can also be divided or multiplied by
        an \c int or a \c qreal.
        In addition, the ZQPoint class provides the manhattanLength()
        function which gives an inexpensive approximation of the length of
        the ZQPoint object interpreted as a vector. Finally, ZQPoint objects
        can be streamed as well as compared.
        \sa ZQPointF, QPolygon
    */


    /*****************************************************************************
      ZQPoint member functions
     *****************************************************************************/

    /*!
        \fn ZQPoint::ZQPoint()
        Constructs a null point, i.e. with coordinates (0, 0)
        \sa isNull()
    */

    /*!
        \fn ZQPoint::ZQPoint(int xpos, int ypos)
        Constructs a point with the given coordinates (\a xpos, \a ypos).
        \sa setX(), setY()
    */

    /*!
        \fn bool ZQPoint::isNull() const
        Returns \c true if both the x and y coordinates are set to 0,
        otherwise returns \c false.
    */

    /*!
        \fn int ZQPoint::x() const
        Returns the x coordinate of this point.
        \sa setX(), rx()
    */

    /*!
        \fn int ZQPoint::y() const
        Returns the y coordinate of this point.
        \sa setY(), ry()
    */


    /*!
        \fn void ZQPoint::setX(int x)
        Sets the x coordinate of this point to the given \a x coordinate.
        \sa x(), setY()
    */

    /*!
        \fn void ZQPoint::setY(int y)
        Sets the y coordinate of this point to the given \a y coordinate.
        \sa y(), setX()
    */

    /*!
        \fn ZQPoint::transposed() const
        \since 5.14
        Returns a point with x and y coordinates exchanged:
        \code
        ZQPoint{1, 2}.transposed() // {2, 1}
        \endcode
        \sa x(), y(), setX(), setY()
    */


    /*!
        \fn int &ZQPoint::rx()
        Returns a reference to the x coordinate of this point.
        Using a reference makes it possible to directly manipulate x. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 1
        \sa x(), setX()
    */

    /*!
        \fn int &ZQPoint::ry()
        Returns a reference to the y coordinate of this point.
        Using a reference makes it possible to directly manipulate y. For
        example:
        \snippet code/src_corelib_tools_qpoint.cpp 2
        \sa y(), setY()
    */


    /*!
        \fn ZQPoint &ZQPoint::operator+=(const ZQPoint &point)
        Adds the given \a point to this point and returns a reference to
        this point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 3
        \sa operator-=()
    */

    /*!
        \fn ZQPoint &ZQPoint::operator-=(const ZQPoint &point)
        Subtracts the given \a point from this point and returns a
        reference to this point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 4
        \sa operator+=()
    */

    /*!
        \fn ZQPoint &ZQPoint::operator*=(float factor)
        Multiplies this point's coordinates by the given \a factor, and
        returns a reference to this point.
        Note that the result is rounded to the nearest integer as points are held as
        integers. Use ZQPointF for floating point accuracy.
        \sa operator/=()
    */

    /*!
        \fn ZQPoint &ZQPoint::operator*=(double factor)
        Multiplies this point's coordinates by the given \a factor, and
        returns a reference to this point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 5
        Note that the result is rounded to the nearest integer as points are held as
        integers. Use ZQPointF for floating point accuracy.
        \sa operator/=()
    */

    /*!
        \fn ZQPoint &ZQPoint::operator*=(int factor)
        Multiplies this point's coordinates by the given \a factor, and
        returns a reference to this point.
        \sa operator/=()
    */

    /*!
        \fn QString ZQPoint::toString()

        Returns a printable string of the point.
    */

    /*!
        \fn QPoint ZQPoint::toQPoint() const
        Returns a QPoint object with the point's coordinates and angle.
    */

    /*!
        \fn static int ZQPoint::dotProduct(const ZQPoint &p1, const ZQPoint &p2)
        \since 5.1
        \snippet code/src_corelib_tools_qpoint.cpp 16
        Returns the dot product of \a p1 and \a p2.
    */

    /*!
        \fn bool operator==(const ZQPoint &p1, const ZQPoint &p2)
        \relates ZQPoint
        Returns \c true if \a p1 and \a p2 are equal; otherwise returns
        false.
    */

    /*!
        \fn bool operator!=(const ZQPoint &p1, const ZQPoint &p2)
        \relates ZQPoint
        Returns \c true if \a p1 and \a p2 are not equal; otherwise returns \c false.
    */

    /*!
        \fn const ZQPoint operator+(const ZQPoint &p1, const ZQPoint &p2)
        \relates ZQPoint
        Returns a ZQPoint object that is the sum of the given points, \a p1
        and \a p2; each component is added separately.
        \sa ZQPoint::operator+=()
    */

    /*!
        \fn const ZQPoint operator-(const ZQPoint &p1, const ZQPoint &p2)
        \relates ZQPoint
        Returns a ZQPoint object that is formed by subtracting \a p2 from
        \a p1; each component is subtracted separately.
        \sa ZQPoint::operator-=()
    */

    /*!
        \fn const ZQPoint operator*(const ZQPoint &point, float factor)
        \relates ZQPoint
        Returns a copy of the given \a point multiplied by the given \a factor.
        Note that the result is rounded to the nearest integer as points
        are held as integers. Use ZQPointF for floating point accuracy.
        \sa ZQPoint::operator*=()
    */

    /*!
        \fn const ZQPoint operator*(const ZQPoint &point, double factor)
        \relates ZQPoint
        Returns a copy of the given \a point multiplied by the given \a factor.
        Note that the result is rounded to the nearest integer as points
        are held as integers. Use ZQPointF for floating point accuracy.
        \sa ZQPoint::operator*=()
    */

    /*!
        \fn const ZQPoint operator*(const ZQPoint &point, int factor)
        \relates ZQPoint
        Returns a copy of the given \a point multiplied by the given \a factor.
        \sa ZQPoint::operator*=()
    */

    /*!
        \fn const ZQPoint operator*(float factor, const ZQPoint &point)
        \overload
        \relates ZQPoint
        Returns a copy of the given \a point multiplied by the given \a factor.
        Note that the result is rounded to the nearest integer as points
        are held as integers. Use ZQPointF for floating point accuracy.
        \sa ZQPoint::operator*=()
    */

    /*!
        \fn const ZQPoint operator*(double factor, const ZQPoint &point)
        \overload
        \relates ZQPoint
        Returns a copy of the given \a point multiplied by the given \a factor.
        Note that the result is rounded to the nearest integer as points
        are held as integers. Use ZQPointF for floating point accuracy.
        \sa ZQPoint::operator*=()
    */

    /*!
        \fn const ZQPoint operator*(int factor, const ZQPoint &point)
        \overload
        \relates ZQPoint
        Returns a copy of the given \a point multiplied by the given \a factor.
        \sa ZQPoint::operator*=()
    */

    /*!
        \fn const ZQPoint operator+(const ZQPoint &point)
        \relates ZQPoint
        \since 5.0
        Returns \a point unmodified.
    */

    /*!
        \fn const ZQPoint operator-(const ZQPoint &point)
        \overload
        \relates ZQPoint
        Returns a ZQPoint object that is formed by changing the sign of
        both components of the given \a point.
        Equivalent to \c{QPoint(0,0) - point}.
    */

    /*!
        \fn ZQPoint &ZQPoint::operator/=(qreal divisor)
        \overload
        Divides both x and y by the given \a divisor, and returns a reference to this
        point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 6
        Note that the result is rounded to the nearest integer as points are held as
        integers. Use ZQPointF for floating point accuracy.
        \sa operator*=()
    */

    /*!
        \fn const ZQPoint operator/(const ZQPoint &point, qreal divisor)
        \relates ZQPoint
        Returns the ZQPoint formed by dividing both components of the given \a point
        by the given \a divisor.
        Note that the result is rounded to the nearest integer as points are held as
        integers. Use ZQPointF for floating point accuracy.
        \sa ZQPoint::operator/=()
    */

    /*****************************************************************************
      ZQPoint stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQPoint &point)
        \relates ZQPoint
        Writes the given \a point to the given \a stream and returns a
        reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQPoint &p)
    {
        if (s.version() == 1)
            s << (qint16)p.x() << (qint16)p.y();
        else
            s << (qint32)p.x() << (qint32)p.y();
        return s;
    }

    /*!
        \fn QDataStream &operator>>(QDataStream &stream, ZQPoint &point)
        \relates ZQPoint
        Reads a point from the given \a stream into the given \a point
        and returns a reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQPoint &p)
    {
        if (s.version() == 1) {
            qint16 x, y;
            s >> x;  p.rx() = x;
            s >> y;  p.ry() = y;
        }
        else {
            qint32 x, y;
            s >> x;  p.rx() = x;
            s >> y;  p.ry() = y;
        }
        return s;
    }

    #endif // QT_NO_DATASTREAM
    /*!
        \fn int ZQPoint::manhattanLength() const
        Returns the sum of the absolute values of x() and y(),
        traditionally known as the "Manhattan length" of the vector from
        the origin to the point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 7
        This is a useful, and quick to calculate, approximation to the
        true length:
        \snippet code/src_corelib_tools_qpoint.cpp 8
        The tradition of "Manhattan length" arises because such distances
        apply to travelers who can only travel on a rectangular grid, like
        the streets of Manhattan.
    */

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQPoint &p)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }

    QDebug operator<<(QDebug dbg, const ZQPointF &p)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }
    #endif

    /*!
        \class ZQPointF
        \inmodule QtCore
        \ingroup painting
        \reentrant
        \brief The ZQPointF class defines a point in the plane using
        floating point precision.
        A point is specified by a x coordinate and an y coordinate which
        can be accessed using the x() and y() functions. The coordinates
        of the point are specified using floating point numbers for
        accuracy. The isNull() function returns \c true if both x and y are
        set to 0.0. The coordinates can be set (or altered) using the setX()
        and setY() functions, or alternatively the rx() and ry() functions which
        return references to the coordinates (allowing direct
        manipulation).
        Given a point \e p, the following statements are all equivalent:
        \snippet code/src_corelib_tools_qpoint.cpp 9
        A ZQPointF object can also be used as a vector: Addition and
        subtraction are defined as for vectors (each component is added
        separately). A ZQPointF object can also be divided or multiplied by
        an \c int or a \c qreal.
        In addition, the ZQPointF class provides a constructor converting a
        ZQPoint object into a ZQPointF object, and a corresponding toPoint()
        function which returns a ZQPoint copy of \e this point. Finally,
        ZQPointF objects can be streamed as well as compared.
        \sa ZQPoint, QPolygonF
    */

    /*!
        \fn ZQPointF::ZQPointF()
        Constructs a null point, i.e. with coordinates (0.0, 0.0)
        \sa isNull()
    */

    /*!
        \fn ZQPointF::ZQPointF(const ZQPoint &point)
        Constructs a copy of the given \a point.
        \sa toPoint()
    */

    /*!
        \fn ZQPointF::ZQPointF(qreal xpos, qreal ypos)
        Constructs a point with the given coordinates (\a xpos, \a ypos).
        \sa setX(), setY()
    */

    /*!
        \fn bool ZQPointF::isNull() const
        Returns \c true if both the x and y coordinates are set to 0.0 (ignoring
        the sign); otherwise returns \c false.
    */


    /*!
        \fn qreal ZQPointF::manhattanLength() const
        \since 4.6
        Returns the sum of the absolute values of x() and y(),
        traditionally known as the "Manhattan length" of the vector from
        the origin to the point.
        \sa ZQPoint::manhattanLength()
    */

    /*!
        \fn qreal ZQPointF::x() const
        Returns the x coordinate of this point.
        \sa setX(), rx()
    */

    /*!
        \fn qreal ZQPointF::y() const
        Returns the y coordinate of this point.
        \sa setY(), ry()
    */

    /*!
        \fn void ZQPointF::setX(qreal x)
        Sets the x coordinate of this point to the given \a x coordinate.
        \sa x(), setY()
    */

    /*!
        \fn void ZQPointF::setY(qreal y)
        Sets the y coordinate of this point to the given \a y coordinate.
        \sa y(), setX()
    */

    /*!
        \fn ZQPointF::transposed() const
        \since 5.14
        Returns a point with x and y coordinates exchanged:
        \code
        ZQPointF{1.0, 2.0}.transposed() // {2.0, 1.0}
        \endcode
        \sa x(), y(), setX(), setY()
    */


    /*!
        \fn qreal& ZQPointF::rx()
        Returns a reference to the x coordinate of this point.
        Using a reference makes it possible to directly manipulate x. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 10
        \sa x(), setX()
    */

    /*!
        \fn qreal& ZQPointF::ry()
        Returns a reference to the y coordinate of this point.
        Using a reference makes it possible to directly manipulate y. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 11
        \sa y(), setY()
    */

    /*!
        \fn ZQPointF& ZQPointF::operator+=(const ZQPointF &point)
        Adds the given \a point to this point and returns a reference to
        this point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 12
        \sa operator-=()
    */

    /*!
        \fn ZQPointF& ZQPointF::operator-=(const ZQPointF &point)
        Subtracts the given \a point from this point and returns a reference
        to this point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 13
        \sa operator+=()
    */

    /*!
        \fn ZQPointF& ZQPointF::operator*=(qreal factor)
        Multiplies this point's coordinates by the given \a factor, and
        returns a reference to this point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 14
        \sa operator/=()
    */

    /*!
        \fn ZQPointF& ZQPointF::operator/=(qreal divisor)
        Divides both x and y by the given \a divisor, and returns a reference
        to this point. For example:
        \snippet code/src_corelib_tools_qpoint.cpp 15
        \sa operator*=()
    */

    /*!
        \fn const ZQPointF operator+(const ZQPointF &p1, const ZQPointF &p2)
        \relates ZQPointF
        Returns a ZQPointF object that is the sum of the given points, \a p1
        and \a p2; each component is added separately.
        \sa ZQPointF::operator+=()
    */

    /*!
        \fn const ZQPointF operator-(const ZQPointF &p1, const ZQPointF &p2)
        \relates ZQPointF
        Returns a ZQPointF object that is formed by subtracting \a p2 from \a p1;
        each component is subtracted separately.
        \sa ZQPointF::operator-=()
    */

    /*!
        \fn const ZQPointF operator*(const ZQPointF &point, qreal factor)
        \relates ZQPointF
        Returns a copy of the given \a point,  multiplied by the given \a factor.
        \sa ZQPointF::operator*=()
    */

    /*!
        \fn const ZQPointF operator*(qreal factor, const ZQPointF &point)
        \relates ZQPointF
        \overload
        Returns a copy of the given \a point, multiplied by the given \a factor.
    */

    /*!
        \fn const ZQPointF operator+(const ZQPointF &point)
        \relates ZQPointF
        \since 5.0
        Returns \a point unmodified.
    */

    /*!
        \fn const ZQPointF operator-(const ZQPointF &point)
        \relates ZQPointF
        \overload
        Returns a ZQPointF object that is formed by changing the sign of
        both components of the given \a point.
        Equivalent to \c {QPointF(0,0) - point}.
    */

    /*!
        \fn const ZQPointF operator/(const ZQPointF &point, qreal divisor)
        \relates ZQPointF
        Returns the ZQPointF object formed by dividing both components of
        the given \a point by the given \a divisor.
        \sa ZQPointF::operator/=()
    */

    /*!
        \fn ZQPoint ZQPointF::toPoint() const
        Rounds the coordinates and angle of this point to the nearest integer,
        and returns a ZQPoint object with the rounded coordinates and angle.
        \sa ZQPointF()
    */

    /*!
        \fn QString ZQPointF::toString()

        Returns a printable string of the point.
    */

    /*!
        \fn QPointF ZQPointF::toQPoint() const
        Returns a QPointF object with the point's coordinates and angle.
    */

    /*!
        \fn static qreal ZQPointF::dotProduct(const ZQPointF &p1, const ZQPointF &p2)
        \since 5.1
        \snippet code/src_corelib_tools_qpoint.cpp 17
        Returns the dot product of \a p1 and \a p2.
    */

    /*!
        \fn bool operator==(const ZQPointF &p1, const ZQPointF &p2)
        \relates ZQPointF
        Returns \c true if \a p1 is equal to \a p2; otherwise returns \c false.
    */

    /*!
        \fn bool operator!=(const ZQPointF &p1, const ZQPointF &p2);
        \relates ZQPointF
        Returns \c true if \a p1 is not equal to \a p2; otherwise returns \c false.
    */

    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQPointF &point)
        \relates ZQPointF
        Writes the given \a point to the given \a stream and returns a
        reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQPointF &p)
    {
        s << double(p.x()) << double(p.y());
        return s;
    }

    /*!
        \fn QDataStream &operator>>(QDataStream &stream, ZQPointF &point)
        \relates ZQPointF
        Reads a point from the given \a stream into the given \a point
        and returns a reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQPointF &p)
    {
        double x, y;
        s >> x;
        s >> y;
        p.setX(qreal(x));
        p.setY(qreal(y));
        return s;
    }
    #endif // QT_NO_DATASTREAM

}
