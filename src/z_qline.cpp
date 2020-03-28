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

#include "z_line.h"
#include <QMath>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/segment.hpp>
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(QPointF, qreal, boost::geometry::cs::cartesian, x, y, setX, setY);
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(QPoint, int, boost::geometry::cs::cartesian, x, y, setX, setY);
BOOST_GEOMETRY_REGISTER_SEGMENT(QLineF, QPointF, p1, p2);


namespace z_qtshapes {

    /*!
        \class ZQLine
        \inmodule QtCore
        \ingroup painting
        \brief The ZQLine class provides a two-dimensional vector using
        integer precision.
        A ZQLine describes a finite length line (or a line segment) on a
        two-dimensional surface. The start and end points of the line are
        specified using integer point accuracy for coordinates. Use the
        ZQLineF constructor to retrieve a floating point copy.
        \table
        \row
            \li \inlineimage qline-point.png
            \li \inlineimage qline-coordinates.png
        \endtable
        The positions of the line's start and end points can be retrieved
        using the p1(), x1(), y1(), p2(), x2(), and y2() functions. The
        dx() and dy() functions return the horizontal and vertical
        components of the line. Use isNull() to determine whether the
        ZQLine represents a valid line or a null line.
        Finally, the line can be translated a given offset using the
        translate() function.
        \sa ZQLineF, QPolygon, QRect
    */

    /*!
        \fn ZQLine::ZQLine()
        Constructs a null line.
    */

    /*!
        \fn ZQLine::ZQLine(const QPoint &p1, const QPoint &p2)
        Constructs a line object that represents the line between \a p1 and
        \a p2.
    */

    /*!
        \fn ZQLine::ZQLine(const QPoint &p1, const QPoint &p2, int angle)
        Constructs a line object that represents the line between \a p1 and
        \a p2, with an \a angle in degrees.
    */

    /*!
        \fn ZQLine::ZQLine(int x1, int y1, int x2, int y2)
        Constructs a line object that represents the line between (\a x1, \a y1) and
        (\a x2, \a y2).
    */

    /*!
        \fn ZQLine::ZQLine(int x1, int y1, int x2, int y2, int angle)
        Constructs a line object that represents the line between (\a x1, \a y1) and
        (\a x2, \a y2), with an \a angle in degrees.
    */

    /*!
        \fn bool ZQLine::isNull() const
        Returns \c true if the line is not set up with valid start and end point;
        otherwise returns \c false.
    */

    /*!
        \fn QString ZQLine::toString()

        Returns a printable string of the line.
    */

    /*!
        \fn QPainterPath ZQLine::toPath()

        Converts the line into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQLine::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the line about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    constexpr QPainterPath ZQLine::toPath() const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(p1());
        QPointF c2 = QPointF(p2());
        QPointF cn = QPointF(center());

        QPointF c1a, c2a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(first.angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        c1a += cn;
        c2a += cn;

        path.moveTo(c1a);
        path.lineTo(c2a);
        path.closeSubpath();
        return path;
    }

    constexpr QPainterPath ZQLine::toPath(const QMatrix3x3 &mat, const QPoint& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(p1());
        QPointF c2 = QPointF(p2());
        QPointF cn = QPointF(center());

        QPointF c1a, c2a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(first.angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        c1a += cn;
        c2a += cn;

        QPointF c1r, c2r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        c1r += ref;
        c2r += ref;

        path.moveTo(c1r);
        path.lineTo(c2r);
        path.closeSubpath();
        return path;
    }

    /*!
        \fn QPoint ZQLine::p1() const
        Returns the line's start point.
        \sa x1(), y1(), p2()
    */

    /*!
        \fn QPoint ZQLine::p2() const
        Returns the line's end point.
        \sa x2(), y2(), p1()
    */

    /*!
        \fn int ZQLine::x1() const
        Returns the x-coordinate of the line's start point.
        \sa p1()
    */

    /*!
        \fn int ZQLine::y1() const
        Returns the y-coordinate of the line's start point.
        \sa p1()
    */

    /*!
        \fn int ZQLine::x2() const
        Returns the x-coordinate of the line's end point.
        \sa p2()
    */

    /*!
        \fn int ZQLine::y2() const
        Returns the y-coordinate of the line's end point.
        \sa p2()
    */

    /*!
        \fn int ZQLine::dx() const
        Returns the horizontal component of the line's vector.
        \sa dy()
    */

    /*!
        \fn int ZQLine::dy() const
        Returns the vertical component of the line's vector.
        \sa dx()
    */

    /*!
        \fn int ZQLine::angle() const

        Returns the angle of the line in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQLine::angleRadians() const

        Returns the angle of the line in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */


    /*!
        \since 4.4
        Returns a ZQLine with the given \a length and \a angle.
        The first point of the line will be on the origin.
        Positive values for the angles mean counter-clockwise while negative values
        mean the clockwise direction. Zero degrees is at the 3 o'clock position.
    */
    static ZQLine ZQLine::fromPolar(int length, int angle) const noexcept
    {
        const qreal angleR = angle * M_2PI / 360.0;
        return ZQLine(0, 0, (int) (qCos(angleR) * length), int(-qSin(angleR) * length));
    }


    /*!
        \fn bool ZQLine::operator!=(const ZQLine &line) const
        Returns \c true if the given \a line is not the same as \e this line.
        A line is different from another line if any of their start or
        end points differ, or the internal order of the points is different.
    */

    /*!
        \fn bool ZQLine::operator==(const ZQLine &line) const
        Returns \c true if the given \a line is the same as \e this line.
        A line is identical to another line if the start and end points
        are identical, and the internal order of the points is the same.
    */

    /*!
        \fn void ZQLine::translate(const QPoint &offset)
        Translates this line by the given \a offset.
    */

    /*!
        \fn void ZQLine::translate(int dx, int dy)
        \overload
        Translates this line the distance specified by \a dx and \a dy.
    */

    /*!
        \fn ZQLine ZQLine::translated(const QPoint &offset) const
        \since 4.4
        Returns this line translated by the given \a offset.
    */

    /*!
        \fn ZQLine ZQLine::translated(int dx, int dy) const
        \overload
        \since 4.4
        Returns this line translated the distance specified by \a dx and \a dy.
    */

    /*!
        \fn QPoint ZQLine::center() const
        \since 5.8
        Returns the center point of this line. This is equivalent to
        (p1() + p2()) / 2, except it will never overflow.
    */

    /*!
        \fn void ZQLine::setP1(const QPoint &p1)
        \since 4.4
        Sets the starting point of this line to \a p1.
        \sa setP2(), p1()
    */


    /*!
        \fn void ZQLine::setP2(const QPoint &p2)
        \since 4.4
        Sets the end point of this line to \a p2.
        \sa setP1(), p2()
    */

    /*!
        \fn void ZQLine::setAngle(int angle)

        Sets the angle of the line to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQLine::setAngleRadians(qreal angle)

        Sets the angle of the line to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */


    /*!
        \fn void ZQLine::setPoints(const QPoint &p1, const QPoint &p2)
        \since 4.4
        Sets the start point of this line to \a p1 and the end point of this line to \a p2.
        \sa setP1(), setP2(), p1(), p2()
    */

    /*!
        \fn void ZQLine::setPoints(const QPoint &p1, const QPoint &p2, int angle)
        \since 4.4
        Sets the start point of this line to \a p1, the end point of this line to \a p2,
        and the angle of this line to \a angle in degrees.
        \sa setP1(), setP2(), setAngle(), p1(), p2(), angle()
    */

    /*!
        \fn void ZQLine::setPointsRadians(const QPoint &p1, const QPoint &p2, qreal angle)
        \since 4.4
        Sets the start point of this line to \a p1, the end point of this line to \a p2,
        and the angle of this line to \a angle in radians.
        \sa setP1(), setP2(), setAngleRadians(), p1(), p2(), angleRadians()
    */


    /*!
        \fn void ZQLine::setLine(int x1, int y1, int x2, int y2)
        \since 4.4
        Sets this line to the start in \a x1, \a y1 and end in \a x2, \a y2.
        \sa setP1(), setP2(), p1(), p2()
    */

    /*!
        \fn void ZQLine::setLine(int x1, int y1, int x2, int y2, int angle)
        \since 4.4
        Sets this line to the start in \a x1, \a y1, end in \a x2, \a y2,
        and have an angle \a angle in degrees.
        \sa setP1(), setP2(), setAngle(), p1(), p2(), angle()
    */

    /*!
        \fn void ZQLine::setLineRadians(int x1, int y1, int x2, int y2, qreal angle)
        \since 4.4
        Sets this line to the start in \a x1, \a y1, end in \a x2, \a y2,
        and have an angle \a angle in radians.
        \sa setP1(), setP2(), setAngleRadians(), p1(), p2(), angleRadians()
    */


    /*!
        \fn bool ZQLine::contains(const QPoint &point, bool proper) const

        Returns \c true if the given \a point is inside or on the edge of
        the line, otherwise returns \c false.

        \sa intersects()
    */

    bool ZQLine::contains(const QPoint &p, bool proper=false) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const QPainterPath path1 = toPath();

        // FIXME proper=false is not honored because there isn't a way
        // to test if a point is on the edge.
        return path1.contains(p);

    }


    /*!
        \fn bool ZQLine::contains(int x, int y, bool proper) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the line, otherwise returns \c false.
    */

    /*!
        \fn bool ZQLine::contains(int x, int y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside this line,
        otherwise returns \c false.
    */

    /*!
        \fn bool ZQLine::contains(const ZQLine &line, bool proper) const
        \overload

        Returns \c true if the given \a line is inside this line.
        otherwise returns \c false. If \a proper is true, this function only
        returns \c true if the \a line is entirely inside this
        line (not on the edge).
    */

    bool ZQLine::contains(const ZQLine &r, bool proper=false) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        if (proper && path1 == path2) {
            return false;
        }
        return path1.contains(path2);
   
    }

    /*!
        \fn ZQLine ZQLine::operator|(const ZQLine &ine) const

        Returns the bounding line of this line and the given \a
        line. The result will always have an angle of 0 degrees.

        \sa united()
    */

    ZQLine ZQLine::operator|(const ZQLine &r) const noexcept
    {
        if (isNull())
            return r;
        if (r.isNull())
            return *this;

        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.united(path2);

    }


    /*!
        \fn ZQLine ZQLine::united(const ZQLine &line) const
        \since 4.2

        Returns the bounding line of this line and the given \a line.
        The result will always have an angle of 0 degrees.

        \image qrect-unite.png

        \sa intersected()
    */


    /*!
        \fn ZQLine ZQLine::operator&(const ZQLine &line) const

        Returns the intersection of this line and the given \a
        line. Returns an empty line if there is no intersection.
        The angle of the intersected line will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQLine::operator&(const ZQLine &r) const noexcept
    {
        if (isNull())
            return r;
        if (r.isNull())
            return *this;

        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersected(path2);
    }


    /*!
        \fn ZQLine ZQLine::intersected(const ZQLine &line) const
        \since 4.2

        Returns the intersection of this line and the given \a
        line. Note that \c{r.intersected(s)} is equivalent to \c{r & s}.

        \image qrect-intersect.png

        \sa intersects(), united()
    */

    /*!
        \fn bool ZQLine::intersects(const ZQLine &line) const

        Returns \c true if this line intersects with the given \a
        line (i.e., there is at least one pixel that is within both
        lines), otherwise returns \c false.

        The intersection line can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQLine::intersects(const ZQLine &r) const noexcept
    {
        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersects(path2);
    }


    /*!
        \fn void ZQLine::rotate(int da) const
        \since 5.7

        Rotates the line by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQLine::rotateRadians(qreal da) const
        \since 5.7

        Rotates the line by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQLine ZQLine::rotated(int da) const
        \since 5.7

        Returns a copy of the line rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQLine ZQLine::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the line rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */


    /*!
        \fn int ZQLine::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa angle()
    */



    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQLine &p)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }
    #endif

    #ifndef QT_NO_DATASTREAM
    /*!
        \relates ZQLine
        Writes the given \a line to the given \a stream and returns a
        reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &stream, const ZQLine &line)
    {
        stream << line.p1() << line.p2();
        return stream;
    }

    /*!
        \relates ZQLine
        Reads a line from the given \a stream into the given \a line and
        returns a reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &stream, ZQLine &line)
    {
        QPoint p1, p2;
        stream >> p1;
        stream >> p2;
        line = ZQLine(p1, p2);

        return stream;
    }

    #endif // QT_NO_DATASTREAM




    /*!
        \class ZQLineF
        \inmodule QtCore
        \ingroup painting
        \brief The ZQLineF class provides a two-dimensional vector using
        floating point precision.
        A ZQLineF describes a finite length line (or line segment) on a
        two-dimensional surface. ZQLineF defines the start and end points
        of the line using floating point accuracy for coordinates.  Use
        the toLine() function to retrieve an integer based copy of this
        line.
        \table
        \row
            \li \inlineimage qline-point.png
            \li \inlineimage qline-coordinates.png
        \endtable
        The positions of the line's start and end points can be retrieved
        using the p1(), x1(), y1(), p2(), x2(), and y2() functions. The
        dx() and dy() functions return the horizontal and vertical
        components of the line, respectively.
        The line's length can be retrieved using the length() function,
        and altered using the setLength() function.  Similarly, angle()
        and setAngle() are respectively used for retrieving and altering
        the angle of the line. Use the isNull()
        function to determine whether the ZQLineF represents a valid line
        or a null line.
        The intersects() function determines the IntersectionType for this
        line and a given line, while the angleTo() function returns the
        angle between the lines. In addition, the unitVector() function
        returns a line that has the same starting point as this line, but
        with a length of only 1, while the normalVector() function returns
        a line that is perpendicular to this line with the same starting
        point and length.
        Finally, the line can be translated a given offset using the
        translate() function, and can be traversed using the pointAt()
        function.
        \section1 Constraints
        ZQLine is limited to the minimum and maximum values for the
        \c int type. Operations on a ZQLine that could potentially result
        in values outside this range will result in undefined behavior.
        \sa ZQLine, QPolygonF, QRectF
    */

    /*!
        \enum ZQLineF::IntersectType
        \obsolete Use ZQLineF::IntersectionType instead
    */

    /*!
        \enum ZQLineF::IntersectionType
        Describes the intersection between two lines.
        \table
        \row
        \li \inlineimage qlinef-unbounded.png
        \li \inlineimage qlinef-bounded.png
        \row
        \li ZQLineF::UnboundedIntersection
        \li ZQLineF::BoundedIntersection
        \endtable
        \value NoIntersection Indicates that the lines do not intersect;
        i.e. they are parallel.
        \value UnboundedIntersection The two lines intersect, but not
        within the range defined by their lengths. This will be the case
        if the lines are not parallel. intersect() will also return this
        value if the intersect point is within the start and end point of
        only one of the lines.
        \value BoundedIntersection The two lines intersect with each other
        within the start and end points of each line.
        \sa intersect()
    */

    /*!
        \fn ZQLineF::ZQLineF()
        Constructs a null line.
    */

    /*!
        \fn ZQLineF::ZQLineF(const QPointF &p1, const QPointF &p2)
        Constructs a line object that represents the line between \a p1 and
        \a p2.
    */

    /*!
        \fn ZQLineF::ZQLineF(qreal x1, qreal y1, qreal x2, qreal y2)
        Constructs a line object that represents the line between (\a x1, \a y1) and
        (\a x2, \a y2).
    */

    /*!
        \fn ZQLineF::ZQLineF(const ZQLine &line)
        Construct a ZQLineF object from the given integer-based \a line.
        \sa toLine()
    */

    /*!
        \fn bool ZQLineF::isNull() const
        Returns \c true if the line is not set up with valid start and end point;
        otherwise returns \c false.
    */

    /*!
        \fn QPointF ZQLineF::p1() const
        Returns the line's start point.
        \sa x1(), y1(), p2()
    */

    /*!
        \fn QPointF ZQLineF::p2() const
        Returns the line's end point.
        \sa x2(), y2(), p1()
    */

    /*!
        \fn QString ZQLineF::toString()

        Returns a printable string of the line.
    */

    /*!
        \fn QPainterPath ZQLineF::toPath()

        Converts the line into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQLineF::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the line about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    constexpr QPainterPath ZQLineF::toPath() const noexcept
    {
        QPainterPath path;
        QPointF c1 = p1();
        QPointF c2 = p2();
        QPointF cn = center();

        QPointF c1a, c2a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(first.angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        c1a += cn;
        c2a += cn;

        path.moveTo(c1a);
        path.lineTo(c2a);
        path.closeSubpath();
        return path;
    }

    constexpr QPainterPath ZQLineF::toPath(const QMatrix3x3 &mat, const QPointF& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = p1();
        QPointF c2 = p2();
        QPointF cn = center();

        QPointF c1a, c2a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(first.angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        c1a += cn;
        c2a += cn;

        QPointF c1r, c2r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        c1r += ref;
        c2r += ref;

        path.moveTo(c1r);
        path.lineTo(c2r);
        path.closeSubpath();
        return path;
    }


    /*!
        \fn ZQLine ZQLineF::toLine() const
        Returns an integer based copy of this line.
        Note that the returned line's start and end points are rounded to
        the nearest integer.
        \sa ZQLineF()
    */
    /*!
        \fn qreal ZQLineF::x1() const
        Returns the x-coordinate of the line's start point.
        \sa p1()
    */

    /*!
        \fn qreal ZQLineF::y1() const
        Returns the y-coordinate of the line's start point.
        \sa p1()
    */

    /*!
        \fn qreal ZQLineF::x2() const
        Returns the x-coordinate of the line's end point.
        \sa p2()
    */

    /*!
        \fn qreal ZQLineF::y2() const
        Returns the y-coordinate of the line's end point.
        \sa p2()
    */

    /*!
        \fn qreal ZQLineF::dx() const
        Returns the horizontal component of the line's vector.
        \sa dy(), pointAt()
    */

    /*!
        \fn qreal ZQLineF::dy() const
        Returns the vertical component of the line's vector.
        \sa dx(), pointAt()
    */

    /*!
        \fn int ZQLine::angle() const

        Returns the angle of the line in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQLine::angleRadians() const

        Returns the angle of the line in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */

    /*!
        \fn void ZQLineF::setLength(qreal length)
        Sets the length of the line to the given \a length. ZQLineF will
        move the end point - p2() - of the line to give the line its new length.
        If the line is a null line, the length will remain zero regardless
        of the length specified.
        \sa length(), isNull()
    */

    /*!
        \fn ZQLineF ZQLineF::normalVector() const
        Returns a line that is perpendicular to this line with the same starting
        point and length.
        \image qlinef-normalvector.png
        \sa unitVector()
    */

    /*!
        \fn bool ZQLineF::operator!=(const ZQLineF &line) const
        Returns \c true if the given \a line is not the same as \e this line.
        A line is different from another line if their start or end points
        differ, or the internal order of the points is different.
    */

    /*!
        \fn bool ZQLineF::operator==(const ZQLineF &line) const
        Returns \c true if the given \a line is the same as this line.
        A line is identical to another line if the start and end points
        are identical, and the internal order of the points is the same.
    */

    /*!
      \fn qreal ZQLineF::pointAt(qreal t) const
      Returns the point at the parameterized position specified by \a
      t. The function returns the line's start point if t = 0, and its end
      point if t = 1.
      \sa dx(), dy()
    */

    /*!
        Returns the length of the line.
        \sa setLength()
    */
    qreal ZQLineF::length() const
    {
        qreal x = pt2.x() - pt1.x();
        qreal y = pt2.y() - pt1.y();
        return qSqrt(x*x + y*y);
    }

    /*!
        \since 4.4
        Returns a ZQLineF with the given \a length and \a angle.
        The first point of the line will be on the origin.
        Positive values for the angles mean counter-clockwise while negative values
        mean the clockwise direction. Zero degrees is at the 3 o'clock position.
    */
    static fZQLineF ZQLineF::fromPolar(qreal length, qreal angle) const noexcept
    {
        const qreal angleR = angle * M_2PI / 360.0;
        return ZQLineF(0, 0, qCos(angleR) * length, -qSin(angleR) * length);
    }

    /*!
        Returns the unit vector for this line, i.e a line starting at the
        same point as \e this line with a length of 1.0.
        \sa normalVector()
    */
    ZQLineF ZQLineF::unitVector() const
    {
        qreal x = pt2.x() - pt1.x();
        qreal y = pt2.y() - pt1.y();

        qreal len = qSqrt(x*x + y*y);
        ZQLineF f(p1(), QPointF(pt1.x() + x/len, pt1.y() + y/len));

    #ifndef QT_NO_DEBUG
        if (qAbs(f.length() - 1) >= 0.001)
            qWarning("ZQLine::unitVector: New line does not have unit length");
    #endif

        return f;
    }


    /*!
        \fn void ZQLineF::translate(const QPointF &offset)
        Translates this line by the given \a offset.
    */

    /*!
        \fn void ZQLineF::translate(qreal dx, qreal dy)
        \overload
        Translates this line the distance specified by \a dx and \a dy.
    */

    /*!
        \fn ZQLineF ZQLineF::translated(const QPointF &offset) const
        \since 4.4
        Returns this line translated by the given \a offset.
    */

    /*!
        \fn ZQLineF ZQLineF::translated(qreal dx, qreal dy) const
        \overload
        \since 4.4
        Returns this line translated the distance specified by \a dx and \a dy.
    */

    /*!
        \fn QPointF ZQLineF::center() const
        \since 5.8
        Returns the center point of this line. This is equivalent to
        0.5 * p1() + 0.5 * p2().
    */

    /*!
        \fn void ZQLineF::setP1(const QPointF &p1)
        \since 4.4
        Sets the starting point of this line to \a p1.
        \sa setP2(), p1()
    */


    /*!
        \fn void ZQLineF::setP2(const QPointF &p2)
        \since 4.4
        Sets the end point of this line to \a p2.
        \sa setP1(), p2()
    */


    /*!
        \fn void ZQLineF::setAngle(int angle)

        Sets the angle of the line to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQLineF::setAngleRadians(int angle)

        Sets the angle of the line to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */


    /*!
        \fn void ZQLineF::setPoints(const QPointF &p1, const QPointF &p2)
        \since 4.4
        Sets the start point of this line to \a p1 and the end point of this line to \a p2.
        \sa setP1(), setP2(), p1(), p2()
    */

    /*!
        \fn void ZQLineF::setPoints(const QPointF &p1, const QPointF &p2, qreal angle)
        \since 4.4
        Sets the start point of this line to \a p1, the end point of this line to \a p2,
        and the angle of this line to \a angle in degrees.
        \sa setP1(), setP2(), setAngle(), p1(), p2(), angle()
    */

    /*!
        \fn void ZQLine::setPointsRadians(const QPointF &p1, const QPointF &p2, qreal angle)
        \since 4.4
        Sets the start point of this line to \a p1, the end point of this line to \a p2,
        and the angle of this line to \a angle in radians.
        \sa setP1(), setP2(), setAngleRadians(), p1(), p2(), angleRadians()
    */


    /*!
        \fn void ZQLineF::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
        \since 4.4
        Sets this line to the start in \a x1, \a y1 and end in \a x2, \a y2.
        \sa setP1(), setP2(), p1(), p2()
    */

    /*!
        \fn void ZQLineF::setLine(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle)
        \since 4.4
        Sets this line to the start in \a x1, \a y1, end in \a x2, \a y2,
        and have an angle \a angle in degrees.
        \sa setP1(), setP2(), setAngle(), p1(), p2(), angle()
    */

    /*!
        \fn void ZQLineF::setLineRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal angle)
        \since 4.4
        Sets this line to the start in \a x1, \a y1, end in \a x2, \a y2,
        and have an angle \a angle in radians.
        \sa setP1(), setP2(), setAngleRadians(), p1(), p2(), angleRadians()
    */

    /*!
        \fn bool ZQLineF::contains(const QPoint &point, bool proper) const

        Returns \c true if the given \a point is inside or on the edge of
        the line, otherwise returns \c false.

        \sa intersects()
    */

    bool ZQLineF::contains(const QPoint &p, bool proper=false) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const QPainterPath path1 = toPath();

        // FIXME proper=false is not honored because there isn't a way
        // to test if a point is on the edge.
        return path1.contains(p);

    }


    /*!
        \fn bool ZQLineF::contains(int x, int y, bool proper) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the line, otherwise returns \c false.
    */

    /*!
        \fn bool ZQLine::contains(int x, int y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside this line,
        otherwise returns \c false.
    */

    /*!
        \fn bool ZQLine::contains(const ZQLine &line, bool proper) const
        \overload

        Returns \c true if the given \a line is inside this line.
        otherwise returns \c false. If \a proper is true, this function only
        returns \c true if the \a line is entirely inside this
        line (not on the edge).
    */

    bool ZQLineF::contains(const ZQLineF &r, bool proper=false) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        if (proper && path1 == path2) {
            return false;
        }
        return path1.contains(path2);
   
    }

    /*!
        \fn ZQLineF ZQLineF::operator|(const ZQLine &ine) const

        Returns the bounding line of this line and the given \a
        line. The result will always have an angle of 0 degrees.

        \sa united()
    */

    ZQLine ZQLine::operator|(const ZQLine &r) const noexcept
    {
        if (isNull())
            return r;
        if (r.isNull())
            return *this;

        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.united(path2);

    }


    /*!
        \fn ZQLineF ZQLineF::united(const ZQLineF &line) const
        \since 4.2

        Returns the bounding line of this line and the given \a line.
        The result will always have an angle of 0 degrees.

        \image qrect-unite.png

        \sa intersected()
    */


    /*!
        \fn ZQLineF ZQLine::operator&(const ZQLineF &line) const

        Returns the intersection of this line and the given \a
        line. Returns an empty line if there is no intersection.
        The angle of the intersected line will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQLineF::operator&(const ZQLineF &r) const noexcept
    {
        if (isNull())
            return r;
        if (r.isNull())
            return *this;

        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersected(path2);
    }


    /*!
        \fn ZQLineF ZQLineF::intersected(const ZQLineF &line) const
        \since 4.2

        Returns the intersection of this line and the given \a
        line. Note that \c{r.intersected(s)} is equivalent to \c{r & s}.

        \image qrect-intersect.png

        \sa intersects(), united()
    */

    /*!
        \fn bool ZQLineF::intersects(const ZQLineF &line) const

        Returns \c true if this line intersects with the given \a
        line (i.e., there is at least one pixel that is within both
        lines), otherwise returns \c false.

        The intersection line can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQLineF::intersects(const ZQLineF &r) const noexcept
    {
        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersects(path2);
    }


    /*!
        \fn void ZQLineF::rotate(qreal da) const
        \since 5.7

        Rotates the line by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQLineF::rotateRadians(qreal da) const
        \since 5.7

        Rotates the line by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQLineF ZQLineF::rotated(qreal da) const
        \since 5.7

        Returns a copy of the line rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQLineF ZQLineF::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the line rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */


    /*!
        \fn qreal ZQLineF::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa angle()
    */

    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQLineF &p)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }
    #endif

    #ifndef QT_NO_DATASTREAM
    /*!
        \relates ZQLineF
        Writes the given \a line to the given \a stream and returns a
        reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &stream, const ZQLineF &line)
    {
        stream << line.p1() << line.p2();
        return stream;
    }

    /*!
        \relates ZQLineF
        Reads a line from the given \a stream into the given \a line and
        returns a reference to the stream.
        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &stream, ZQLineF &line)
    {
        QPointF start, end;
        stream >> start;
        stream >> end;
        line = ZQLineF(start, end);

        return stream;
    }

    #endif // QT_NO_DATASTREAM

}

