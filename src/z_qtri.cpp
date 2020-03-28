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

#include "z_qtri.h"
//#include <boost/numeric/ublas/matrix.hpp>


namespace z_qtshapes {

    /*!
        \class ZQTri
        \inmodule Zgeometry
        \ingroup painting
        \reentrant

        \brief The ZQTri class defines a triangle in the plane using
        integer precision.

        A triangle is normally expressed as a top-left corner and a
        size.  The size (width and height) of a ZQTri is always equivalent
        to the mathematical triangle that forms the basis for its
        rendering.

        A ZQTri can be constructed with a set of left, top, width and
        height integers, or from a QPoint and a QSize.  The following code
        creates two identical triangles.

        \snippet code/src_corelib_tools_qtri.cpp 0

        There is a third constructor that creates a ZQTri using the
        top-left and bottom-right coordinates, but we recommend that you
        avoid using it. The rationale is that for historical reasons the
        values returned by the bottom() and right() functions deviate from
        the true bottom-right corner of the triangle.

        The ZQTri class provides a collection of functions that return the
        various triangle coordinates, and enable manipulation of
        these. ZQTri also provides functions to move the triangle relative
        to the various coordinates. In addition there is a moveTo()
        function that moves the triangle, leaving its top left corner at
        the given coordinates. Alternatively, the translate() function
        moves the triangle the given offset relative to the current
        position, and the translated() function returns a translated copy
        of this triangle.

        The size() function returns the triange's dimensions as a
        QSize. The dimensions can also be retrieved separately using the
        width() and height() functions. To manipulate the dimensions use
        the setSize(), setWidth() or setHeight() functions. Alternatively,
        the size can be changed by applying either of the functions
        setting the triangle coordinates, for example, setBottom() or
        setRight().

        The contains() function tells whether a given point is inside the
        triangle or not, and the intersects() function returns \c true if
        this triangle intersects with a give triangle. The ZQTri class
        also provides the intersected() function which returns the
        intersectio triangle, and the united() function which returns the
        triangle that encloses the give triangle and this:

        \table
        \row
        \li \inlineimage qtri-intersect.png
        \li \inlineimage qtri-unite.png
        \row
        \li intersected()
        \li united()
        \endtable

        The isEmpty() function returns \c true if left() > right() or top() >
        bottom(). Note that an empty triangle is not valid: The isValid()
        function returns \c true if left() <= right() \e and top() <=
        bottom(). A null triangle (isNull() == true) on the other hand,
        has both width and height set to 0.

        Note that due to the way ZQTri and ZQTriF are defined, an
        empty ZQTri is defined in essentially the same way as ZQTriF.

        Finally, ZQTri objects can be streamed as well as compared.

        \tableofcontents

        \section1 Rendering

        When using an \l {QPainter::Antialiasing}{anti-aliased} painter,
        the boundary line of a ZQTri will be rendered symmetrically on
        both sides of the mathematical triangle's boundary line. But when
        using an aliased painter (the default) other rules apply.

        Then, when rendering with a one pixel wide pen the ZQTri's boundary
        line will be rendered to the right and below the mathematical
        triangle's boundary line.

        When rendering with a two pixels wide pen the boundary line will
        be split in the middle by the mathematical triangle. This will be
        the case whenever the pen is set to an even number of pixels,
        while rendering with a pen with an odd number of pixels, the spare
        pixel will be rendered to the right and below the mathematical
        triangle as in the one pixel case.

        \table
        \row
            \li \inlineimage qtri-diagram-zero.png
            \li \inlineimage qtri-diagram-one.png
        \row
            \li Logical representation
            \li One pixel wide pen
        \row
            \li \inlineimage qtri-diagram-two.png
            \li \inlineimage qtri-diagram-three.png
        \row
            \li Two pixel wide pen
            \li Three pixel wide pen
        \endtable

        \section1 Coordinates

        The ZQTri class provides a collection of functions that return the
        various triangle coordinates, and enable manipulation of
        these. ZQTri also provides functions to move the triangle relative
        to the various coordinates.

        For example the left(), setLeft() and moveLeft() functions as an
        example: left() returns the x-coordinate of the triangle's left
        edge, setLeft() sets the left edge of the triangle to the given x
        coordinate (it may change the width, but will never change the
        triangle's right edge) and moveLeft() moves the entire triangle
        horizontally, leaving the triangle's left edge at the given x
        coordinate and its size unchanged.

        \image qtri-coordinates.png

        Note that for historical reasons the values returned by the
        bottom() and right() functions deviate from the true bottom-right
        corner of the triangle: The right() function returns \e { left()
        + width() - 1} and the bottom() function returns \e {top() +
        height() - 1}. The same is the case for the point returned by the
        bottomRight() convenience function. In addition, the x and y
        coordinate of the topRight() and bottomLeft() functions,
        respectively, contain the same deviation from the true right and
        bottom edges.

        We recommend that you use x() + width() and y() + height() to find
        the true bottom-right corner, and avoid right() and
        bottom(). Another solution is to use ZQTriF: The ZQTriF class
        defines a triangle in the plane using floating point accuracy for
        coordinates, and the ZQTriF::right() and ZQTriF::bottom()
        functions \e do return the right and bottom coordinates.

        It is also possible to add offsets to this triangle's coordinates
        using the adjust() function, as well as retrieve a new triangle
        based on adjustments of the original one using the adjusted()
        function. If either of the width and height is negative, use the
        normalized() function to retrieve a triangle where the corners
        are swapped.

        In addition, ZQTri provides the getCoords() function which extracts
        the position of the triangle's top-left and bottom-right corner,
        and the getTri() function which extracts the triangle's top-left
        corner, width and height. Use the setCoords() and setTri()
        function to manipulate the triangle's coordinates and dimensions
        in one go.

        \section1 Constraints

        ZQTri is limited to the minimum and maximum values for the \c int type.
        Operations on a ZQTri that could potentially result in values outside this
        range will result in undefined behavior.

        \sa ZQTriF, QRegion
    */

    /*****************************************************************************
      ZQTri member functions
     *****************************************************************************/

    /*!
        \fn ZQTri::ZQTri()

        Constructs a null triangle.

        \sa isNull()
    */

    /*!
        \fn ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third)

        Constructs a triangle with the given \a first, \a second and \a third corners.

        \sa setFirst(), setSecond(), setThird()
    */

    /*!
        \fn ZQTri::ZQTri(const QPoint &first, const QPoint &second, const QPoint &third, int angle)

        Constructs a triangle with the given \a first, \a second and \a third corners
        and an \a angle.

        \sa setFirst(), setSecond(), setThird()
    */


    /*!
        \fn ZQTri::ZQTri(int x1, int y1, int x2, int y2, int x3, int y3)

        Constructs a triangle with the coordinates (\a x1, \a y1), (\a x2, \a y2),
        (\a x3, \a y3).

        \sa setFirst(), setSecond(), setThird()
    */

    /*!
        \fn ZQTri::ZQTri(int x1, int y1, int x2, int y2, int x3, int y3, int angle)

        Constructs a triangle with the coordinates (\a x1, \a y1), (\a x2, \a y2),
        (\a x3, \a y3) and angle \a angle.

        \sa setFirst(), setSecond(), setThird()
    */


    /*!
        \fn bool ZQTri::isNull() const

        Returns \c true if the triangle is a null triangle, otherwise
        returns \c false.

        A null triangle has all coordinates set to 0. A null triangle
        is also empty, and hence is not valid.

        \sa isEmpty()
    */

    /*!
        \fn bool ZQTri::isEmpty() const

        Returns \c true if the triangle is empty, otherwise returns \c false.

        An empty triangle has all coordinates the same. An
        empty triangle is not valid (i.e., isEmpty() == !isValid()).

        Use the normalized() function to retrieve a triangle where the
        corners are swapped.

        \sa isNull(), isValid()
    */

    /*!
        \fn bool ZQTri::isValid() const

        Returns \c true if the triangle is valid, otherwise returns \c false.

        A valid triangle has points which are not on a straight line.
        A valid rectangle is not empty (i.e., isValid() == !isEmpty()).

        \sa isNull(), isEmpty()
    */


    /*!
        \fn QPoint ZQTri::first() const

        Returns the first point in the triangle.

        \sa second(), third(), setFirst(), setSecond(), setThird()
    */

    /*!
        \fn QPoint ZQTri::second() const

        Returns the second point in the triangle.

        \sa first(), third(), setFirst(), setSecond(), setThird()
    */


    /*!
        \fn QPoint ZQTri::third() const

        Returns the second point in the triangle.

        \sa second(), third(), setFirst(), setSecond(), setThird()
    */

    /*!
        \fn QPoint ZQTri::center() const

        Returns the center point of the triangle.

        \sa first(), second(), third()
    */

    /*!
        \fn int ZQTri::x1() const

        Returns the x-coordinate of the first point.

        \sa x2(), x3(), y1(), y2(), y3()
    */

    /*!
        \fn int ZQTri::x1() const

        Returns the x-coordinate of the first point.

        \sa x2(), x3(), y1(), y2(), y3()
    */

    /*!
        \fn int ZQTri::y1() const

        Returns the y-coordinate of the first point.

        \sa x1(), x2(), x3(), y2(), y3()
    */

    /*!
        \fn int ZQTri::x2() const

        Returns the x-coordinate of the second point.

        \sa x1(), x3(), y1(), y2(), y3()
    */

    /*!
        \fn int ZQTri::y2() const

        Returns the y-coordinate of the second point.

        \sa x1(), x2(), x3(), y1(), y3()
    */

    /*!
        \fn int ZQTri::x3() const

        Returns the x-coordinate of the third point.

        \sa x1(), x2(), y1(), y2(), y3()
    */

    /*!
        \fn int ZQTri::y3() const

        Returns the y-coordinate of the third point.

        \sa x1(), x2(), x3(), y1(), y2()
    */

    /*!
        \fn int ZQTri::angle() const

        Returns the angle of the triangle in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQTri::angleRadians() const

        Returns the angle of the triangle in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */

    /*!
        \fn void ZQTri::setX1(int pos)

        Sets the x-coordinate of the first point to \a pos.

        \sa setX2(), setX3(), setY1(), setY2(), setY3()
    */

    /*!
        \fn void ZQTri::setY1(int pos)

        Sets the y-coordinate of the first point to \a pos.

        \sa setX1(), setX2(), setX3(), setY2(), setY3()
    */

    /*!
        \fn void ZQTri::setX2(int pos)

        Sets the x-coordinate of the second point to \a pos.

        \sa setX1(), setX3(), setY1(), setY2(), setY3()
    */

    /*!
        \fn void ZQTri::setY2(int pos)

        Sets the y-coordinate of the second point to \a pos.

        \sa setX1(), setX2(), setX3(), setY1(), setY3()
    */

    /*!
        \fn void ZQTri::setX3(int pos)

        Sets the x-coordinate of the third point to \a pos.

        \sa setX1(), setX2(), setY1(), setY2(), setY3()
    */

    /*!
        \fn void ZQTri::setY3(int pos)

        Sets the y-coordinate of the third point to \a pos.

        \sa setX1(), setX2(), setX3(), setY1(), setY2()
    */

    /*!
        \fn void ZQTri::setFirst(QPoint p)

        Sets the first point to \a p.

        \sa first(), second(), third(), setSecond(), setThird()
    */

    /*!
        \fn void ZQTri::setSecond(QPoint p)

        Sets the second point to \a p.

        \sa first(), second(), third(), setFirst(), setThird()
    */


    /*!
        \fn void ZQTri::setThird(QPoint p)

        Sets the third point to \a p.

        \sa first(), second(), third(), setFirst(), setSecond()
    */

    /*!
        \fn void ZQTri::setAngle(int angle)

        Sets the angle of the triangle to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQTri::setAngleRadians(qreal angle)

        Sets the angle of the triangle to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */

    /*!
        \fn void ZQTri::setAngleRadians(qreal angle)

        Sets the angle of the triangle to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */

    /*!
        \fn qreal ZQTri::length12()

        Returns the length between the first and second points.

        \sa length13(), length23(), area()
    */

    /*!
        \fn qreal ZQTri::length13()

        Returns the length between the first and third points.

        \sa length12(), length23(), area()
    */

    /*!
        \fn qreal ZQTri::length23()

        Returns the length between the second and third points.

        \sa length13(), length23(), area()
    */

    /*!
        \fn qreal ZQTri::area()

        Returns the area of the triangle.

        \sa length12(), length13(), length23()
    */

    /*!
        \fn void ZQTri::moveX1(int pos)

        Moves the x-coordinate of the first point by an offset of \a pos.

        \sa moveX2(), moveX3(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTri::moveY1(int pos)

        Moves the y-coordinate of the first point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveX3(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTri::moveX2(int pos)

        Moves the x-coordinate of the second point by an offset of \a pos.

        \sa moveX2(), moveX3(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTri::moveY2(int pos)

        Moves the y-coordinate of the second point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveX3(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTri::moveX3(int pos)

        Moves the x-coordinate of the second point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTri::moveY3(int pos)

        Moves the y-coordinate of the second point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveX3(), moveY1(), moveY2()
    */

    /*!
        \fn void ZQTri::moveFirst(QPoint p)

        Moves the x- and y-coordinates of the first point by an offset of the
        x- and y- coordinates in \a p.

        \sa moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTri::moveSecond(QPoint p)

        Moves the x- and y-coordinates of the second point by an offset of the
        x- and y- coordinates in \a p.

        \sa moveFirst(), moveThird(), moveBy()
    */

    /*!
        \fn void ZQTri::moveThird(QPoint p)

        Moves the x- and y-coordinates of the third point by an offset of the
        x- and y- coordinates in \a p.

        \sa moveFirst(), moveSecond(), moveBy()
    */

    /*!
        \fn void ZQTri::moveCenter(QPoint p)

        Moves the x- and y-coordinates of the center point by an offset of the
        x- and y- coordinates in \a p. This has the consequence of moving all three
        control points of the triangle by that distance.

        \sa moveFirst(), moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTri::moveBy(QPoint p1, QPoint p2, QPoint p3)

        Moves the x- and y-coordinates of the first point by \a p1, the
        x- and y-coordinates of the second point by \a p2, and the
        x- and y-coordinates of the third point by \a p3.

        \sa moveFirst(), moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTri::movedX1(int pos)

        Returns a triangle with the x-coordinate of the first point moved
        by an offset of \a pos.

        \sa movedX2(), movedX3(), movedY1(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTri::movedY1(int pos)

        Returns a triangle with the y-coordinate of the first point moved
        by an offset of \a pos.

        \sa movedX1(), movedX2(), movedX3(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTri::movedX2(int pos)

        Returns a triangle with the x-coordinate of the second point moved
        by an offset of \a pos.

        \sa movedX2(), movedX3(), movedY1(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTri::movedY2(int pos)

        Returns a triangle with the y-coordinate of the second point moved
        by an offset of \a pos.

        \sa movedX1(), movedX2(), movedX3(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTri::movedX3(int pos)

        Returns a triangle with the x-coordinate of the second point moved
        by an offset of \a pos.

        \sa moveX1(), moveX2(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTri::movedY3(int pos)

        Returns a triangle with the y-coordinate of the second point moved
        by an offset of \a pos.

        \sa movedX1(), movedX2(), movedX3(), movedY1(), movedY2()
    */

    /*!
        \fn void ZQTri::movedFirst(QPoint p)

        Returns a triangle with the x- and y-coordinates of the first point moved
        by an offset of the x- and y- coordinates in \a p.

        \sa moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTri::movedSecond(QPoint p)

        Returns a triangle with the x- and y-coordinates of the second point moved
        by an offset of the x- and y- coordinates in \a p.

        \sa moveFirst(), moveThird(), moveBy()
    */

    /*!
        \fn void ZQTri::movedThird(QPoint p)

        Returns a triangle with the x- and y-coordinates of the third point moved
        by an offset of the x- and y- coordinates in \a p.

        \sa moveFirst(), moveSecond(), moveBy()
    */

    /*!
        \fn void ZQTri::movedCenter(QPoint p)

        Returns a triangle with  the x- and y-coordinates of the center point moved
        by an offset of the x- and y- coordinates in \a p. This has the
        consequence of moving all three control points of the triangle by that distance.

        \sa moveFirst(), moveSecond(), moveThird()
    */


    /*!
        \fn void ZQTri::movedBy(QPoint p1, QPoint p2, QPoint p3)

        Returns a triangle with the x- and y-coordinates of the first point
        moved by \a p1, the x- and y-coordinates of the second point moved
        by \a p2, and the x- and y-coordinates of the third point moved by \a p3.

        \sa moveFirst(), moveSecond(), moveThird()
    */


    /*!
        \fn ZQTri ZQTri::translated(int dx, int dy) const

        Returns a copy of the triangle that is translated \a dx along the
        x axis and \a dy along the y axis, relative to the current
        position. Positive values move the triangle to the right and
        down.

        \sa translate()

    */


    /*!
        \fn ZQTri ZQTri::translated(const QPoint &offset) const

        \overload

        Returns a copy of the triangle that is translated
        \a{offset}.\l{QPoint::x()}{x()} along the x axis and
        \a{offset}.\l{QPoint::y()}{y()} along the y axis, relative to the
        current position.
    */

    /*!
        \fn void ZQTri::translate(int dx, int dy)

        Moves the triangle \a dx along the x axis and \a dy along the y
        axis, relative to the current position. Positive values move the
        triangle to the right and down.

        \sa moveTopLeft(), moveTo(), translated()
    */


    /*!
        \fn void ZQTri::translate(const QPoint &offset)
        \overload

        Moves the triangle \a{offset}.\l{QPoint::x()}{x()} along the x
        axis and \a{offset}.\l{QPoint::y()}{y()} along the y axis,
        relative to the current position.
    */


    /*!
        \fn void ZQTri::rotate(int da) const
        \since 5.7

        Rotates the triangle by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQTri::rotateRadians(qreal da) const
        \since 5.7

        Rotates the triangle by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQTri ZQTri::rotated(int da) const
        \since 5.7

        Returns a copy of the triangle rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQTri ZQTri::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the triangle rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */

    /*!
        \fn int ZQTri::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa angle()
    */


    /*!
        \fn void ZQTri::getTri(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3) const

        Extracts the position of the triangle's first point to *\a x1
        and *\a y1, its second point to *\a x2 and *\a y2, and its third point
        to *\a x3 and *\a y3.

        \sa setTri()
    */

    /*!
        \fn void ZQTri::getTri(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *angle) const

        Extracts the position of the triangle's first point to *\a x1
        and *\a y1, its second point to *\a x2 and *\a y2, and its third point
        to *\a x3 and *\a y3, and its angle to *\a angle in degrees.

        \sa setTri()
    */

    /*!
        \fn void ZQTri::getTriRadians(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, qreal *angle) const

        Extracts the position of the triangle's first point to *\a x1
        and *\a y1, its second point to *\a x2 and *\a y2, and its third point
        to *\a x3 and *\a y3, and its angle to *\a angle in radians.

        \sa setTriRadians()
    */



    /*!
        \fn void ZQTri::setTri(int x1, int y1, int x2, int y2, int x3, int y3)

        Sets the coordinates of the triangle's first point to (\a{x1},
        \a{y1}), its second point to (\a{x2}, \a{y2}), and its third
        point to (\a{x3}, \a{y3}).

        \sa getTri()
    */

    /*!
        \fn void ZQTri::setTri(int x1, int y1, int x2, int y2, int x3, int y3, int angle)

        Sets the coordinates of the triangle's first point to (\a{x1},
        \a{y1}), its second point to (\a{x2}, \a{y2}), and its third
        point to (\a{x3}, \a{y3}), and its angle to \a angle in degrees.

        \sa getTri()
    */

    /*!
        \fn void ZQTri::setTriRadians(int x1, int y1, int x2, int y2, int x3, int y3, qreal angle)

        Sets the coordinates of the triangle's first point to (\a{x1},
        \a{y1}), its second point to (\a{x2}, \a{y2}), and its third
        point to (\a{x3}, \a{y3}), and its angle to \a angle in radians.

        \sa getTriRadians()
    */



    /*!
        \fn bool ZQTri::contains(const QPoint &point, bool proper) const

        Returns \c true if the given \a point is inside or on the edge of
        the triangle, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the given \a point is \e inside the
        triangle (i.e., not on the edge).

        \sa intersects()
    */

    bool ZQTri::contains(const QPoint &p, bool proper) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const QPainterPath path1 = toPath();

        // FIXME proper=false is not honored because there isn't a way
        // to test if a point is on the edge.
        return path1.contains(p);

    }


    /*!
        \fn bool ZQTri::contains(int x, int y, bool proper) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the triangle, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the point is entirely inside the
        triangle(not on the edge).
    */

    /*!
        \fn bool ZQTri::contains(int x, int y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside this triangle,
        otherwise returns \c false.
    */

    /*!
        \fn bool ZQTri::contains(const ZQTri &triangle, bool proper) const
        \overload

        Returns \c true if the given \a triangle is inside this triangle.
        otherwise returns \c false. If \a proper is true, this function only
        returns \c true if the \a triangle is entirely inside this
        triangle (not on the edge).
    */

    bool ZQTri::contains(const ZQTri &r, bool proper) const noexcept
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
        \fn QPainterPath ZQTri::operator|(const ZQTri &triangle) const

        Returns the bounding triangle of this triangle and the given \a
        triangle. The result will always have an angle of 0 degrees.

        \sa united()
    */

    QPainterPath ZQTri::operator|(const ZQTri &r) const noexcept
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
        \fn QPainterPath ZQTri::united(const ZQTri &triangle) const
        \since 4.2

        Returns the bounding triangle of this triangle and the given \a triangle.
        The result will always have an angle of 0 degrees.

        \image qtri-unite.png

        \sa intersected()
    */


    /*!
        \fn QPainterPath ZQTri::operator&(const ZQTri &triangle) const

        Returns the intersection of this triangle and the given \a
        triangle. Returns an empty triangle if there is no intersection.
        The angle of the intersected triangle will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQTri::operator&(const ZQTriF &r) const noexcept
    {
        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersected(path2);

    }


    /*!
        \fn QPainterPath ZQTri::intersected(const ZQTri &triangle) const
        \since 4.2

        Returns the intersection of this triangle and the given \a
        triangle. Note that \c{r.intersected(s)} is equivalent to \c{r & s}.

        \image qtri-intersect.png

        \sa intersects(), united()()
    */

    /*!
        \fn bool ZQTri::intersects(const ZQTri &triangle) const

        Returns \c true if this triangle intersects with the given \a
        triangle (i.e., there is at least one pixel that is within both
        triangles), otherwise returns \c false.

        The intersectio triangle can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQTri::intersects(const ZQTri &r) const noexcept
    {
        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersects(path2);
    }

    /*!
        \fn bool operator==(const ZQTri &r1, const ZQTri &r2)
        \relates ZQTri

        Returns \c true if the triangles \a r1 and \a r2 are equal,
        otherwise returns \c false.
    */


    /*!
        \fn bool operator!=(const ZQTri &r1, const ZQTri &r2)
        \relates ZQTri

        Returns \c true if the triangles \a r1 and \a r2 are different, otherwise
        returns \c false.
    */


    /*!
        \fn QPainterPath ZQTri::toPath()

        Converts the triangle into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQTri::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the triangle about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    /*!
        \fn QString ZQTri::toString()

        Returns a printable string of the triangle.
    */


    constexpr QPainterPath ZQTri::toPath() const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(first());
        QPointF c2 = QPointF(second());
        QPointF c3 = QPointF(third());
        QPointF cn = QPointF(center());

        QPointF c1a, c2a, c3a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;

        path.moveTo(c1);
        path.lineTo(c2);
        path.lineTo(c3);
        path.lineTo(c1);
        path.closeSubpath();
        return path;
    }

    constexpr QPainterPath ZQTri::toPath(const QMatrix3x3 &mat, const QPointF& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(first());
        QPointF c2 = QPointF(second());
        QPointF c3 = QPointF(third());
        QPointF cn = QPointF(center());

        QPointF c1a, c2a, c3a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;

        QPoint c1r, c2r, c3r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        boost::geometry::transform(c3a - ref, c3r, project2D);

        path.moveTo(c1 + ref);
        path.lineTo(c2 + ref);
        path.lineTo(c3 + ref);
        path.lineTo(c1 + ref);
        path.closeSubpath();
        return path;
    }

    /*****************************************************************************
      ZQTri stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQTri &triangle)
        \relates ZQTri

        Writes the given \a triangle to the given \a stream, and returns
        a reference to the stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQTri &r)
    {
        if (s.version() == 1)
            s << (qint16)r.left() << (qint16)r.top()
              << (qint16)r.right() << (qint16)r.bottom() << (qint16)r.angle();
        else
            s << (qint32)r.left() << (qint32)r.top()
              << (qint32)r.right() << (qint32)r.bottom() << (qint32)r.angle();
        return s;
    }

    /*!
        \fn QDataStream &operator>>(QDataStream &stream, ZQTri &triangle)
        \relates ZQTri

        Reads a triangle from the given \a stream into the given \a
        triangle, and returns a reference to the stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQTri &r)
    {
        if (s.version() == 1) {
            qint16 x1, y1, x2, y2, a;
            s >> x1; s >> y1; s >> x2; s >> y2; s >> a
            r.setCoords(x1, y1, x2, y2);
            r.setAngle(a);
        }
        else {
            qint32 x1, y1, x2, y2, a;
            s >> x1; s >> y1; s >> x2; s >> y2; s >> a;
            r.setCoords(x1, y1, x2, y2);
            r.setAngle(a);
        }
        return s;
    }

    #endif // QT_NO_DATASTREAM


    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQTri &r)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }
    #endif

    /*!
        \class ZQTriF
        \inmodule Zgeometry
        \ingroup painting
        \reentrant

        \brief The ZQTriF class defines a triangle in the plane using floating
        point precision.

        A triangle is normally expressed as a top-left corner and a
        size.  The size (width and height) of a ZQTriF is always equivalent
        to the mathematical triangle that forms the basis for its
        rendering.

        A ZQTriF can be constructed with a set of left, top, width and
        height coordinates, or from a QPointF and a QSizeF.  The following
        code creates two identical triangles.

        \snippet code/src_corelib_tools_qtri.cpp 1

        There is also a third constructor creating a ZQTriF from a ZQTri,
        and a corresponding toEllipse() function that returns a ZQTri object
        based on the values of this triangle (note that the coordinates
        in the returned triangle are rounded to the nearest integer).

        The ZQTriF class provides a collection of functions that return
        the various triangle coordinates, and enable manipulation of
        these. ZQTriF also provides functions to move the triangle
        relative to the various coordinates. In addition there is a
        moveTo() function that moves the triangle, leaving its top left
        corner at the given coordinates. Alternatively, the translate()
        function moves the triangle the given offset relative to the
        current position, and the translated() function returns a
        translated copy of this triangle.

        The size() function returns the triange's dimensions as a
        QSizeF. The dimensions can also be retrieved separately using the
        width() and height() functions. To manipulate the dimensions use
        the setSize(), setWidth() or setHeight() functions. Alternatively,
        the size can be changed by applying either of the functions
        setting the triangle coordinates, for example, setBottom() or
        setRight().

        The contains() function tells whether a given point is inside the
        triangle or not, and the intersects() function returns \c true if
        this triangle intersects with a give triangle (otherwise
        false). The ZQTriF class also provides the intersected() function
        which returns the intersectio triangle, and the united() function
        which returns the triangle that encloses the give triangle and
        this:

        \table
        \row
        \li \inlineimage qtri-intersect.png
        \li \inlineimage qtri-unite.png
        \row
        \li intersected()
        \li united()
        \endtable

        The isEmpty() function returns \c true if the triangle's width or
        height is less than, or equal to, 0. Note that an empty triangle
        is not valid: The isValid() function returns \c true if both width
        and height is larger than 0. A null triangle (isNull() == true)
        on the other hand, has both width and height set to 0.

        Note that due to the way ZQTri and ZQTriF are defined, an
        empty ZQTriF is defined in essentially the same way as ZQTri.

        Finally, ZQTriF objects can be streamed as well as compared.

        \tableofcontents

        \section1 Rendering

        When using an \l {QPainter::Antialiasing}{anti-aliased} painter,
        the boundary line of a ZQTriF will be rendered symmetrically on both
        sides of the mathematical triangle's boundary line. But when
        using an aliased painter (the default) other rules apply.

        Then, when rendering with a one pixel wide pen the ZQTriF's boundary
        line will be rendered to the right and below the mathematical
        triangle's boundary line.

        When rendering with a two pixels wide pen the boundary line will
        be split in the middle by the mathematical triangle. This will be
        the case whenever the pen is set to an even number of pixels,
        while rendering with a pen with an odd number of pixels, the spare
        pixel will be rendered to the right and below the mathematical
        triangle as in the one pixel case.

        \table
        \row
            \li \inlineimage qtri-diagram-zero.png
            \li \inlineimage qtrif-diagram-one.png
        \row
            \li Logical representation
            \li One pixel wide pen
        \row
            \li \inlineimage qtrif-diagram-two.png
            \li \inlineimage qtrif-diagram-three.png
        \row
            \li Two pixel wide pen
            \li Three pixel wide pen
        \endtable

        \section1 Coordinates

        The ZQTriF class provides a collection of functions that return
        the various triangle coordinates, and enable manipulation of
        these. ZQTriF also provides functions to move the triangle
        relative to the various coordinates.

        For example: the bottom(), setBottom() and moveBottom() functions:
        bottom() returns the y-coordinate of the triangle's bottom edge,
        setBottom() sets the bottom edge of the triangle to the given y
        coordinate (it may change the height, but will never change the
        triangle's top edge) and moveBottom() moves the entire triangle
        vertically, leaving the triangle's bottom edge at the given y
        coordinate and its size unchanged.

        \image qtrif-coordinates.png

        It is also possible to add offsets to this triangle's coordinates
        using the adjust() function, as well as retrieve a new triangle
        based on adjustments of the original one using the adjusted()
        function. If either of the width and height is negative, use the
        normalized() function to retrieve a triangle where the corners
        are swapped.

        In addition, ZQTriF provides the getCoords() function which extracts
        the position of the triangle's top-left and bottom-right corner,
        and the getTri() function which extracts the triangle's top-left
        corner, width and height. Use the setCoords() and setTri()
        function to manipulate the triangle's coordinates and dimensions
        in one go.

        \sa ZQTri, QRegion
    */

    /*****************************************************************************
      ZQTriF member functions
     *****************************************************************************/

    /*!
        \fn ZQTriF::ZQTriF()

        Constructs a null triangle.

        \sa isNull()
    */


    /*!
        \fn ZQTriF::ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third)

        Constructs a triangle with the given \a first, \a second and \a third corners.

        \sa setFirst(), setSecond(), setThird()
    */

    /*!
        \fn ZQTriF::ZQTriF(const QPointF &first, const QPointF &second, const QPointF &third, qreal angle)

        Constructs a triangle with the given \a first, \a second and \a third corners
        and an \a angle.

        \sa setFirst(), setSecond(), setThird()
    */


    /*!
        \fn ZQTriF::ZQTriF(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3)

        Constructs a triangle with the coordinates (\a x1, \a y1), (\a x2, \a y2),
        (\a x3, \a y3).

        \sa setFirst(), setSecond(), setThird()
    */

    /*!
        \fn ZQTriF::ZQTriF(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal angle)

        Constructs a triangle with the coordinates (\a x1, \a y1), (\a x2, \a y2),
        (\a x3, \a y3) and angle \a angle.

        \sa setFirst(), setSecond(), setThird()
    */


    /*!
        \fn bool ZQTriF::isNull() const

        Returns \c true if the triangle is a null triangle, otherwise
        returns \c false.

        A null triangle has all coordinates set to 0. A null triangle
        is also empty, and hence is not valid.

        \sa isEmpty()
    */

    /*!
        \fn bool ZQTriF::isEmpty() const

        Returns \c true if the triangle is empty, otherwise returns \c false.

        An empty triangle has all coordinates the same. An
        empty triangle is not valid (i.e., isEmpty() == !isValid()).

        Use the normalized() function to retrieve a triangle where the
        corners are swapped.

        \sa isNull(), isValid()
    */

    /*!
        \fn bool ZQTriF::isValid() const

        Returns \c true if the triangle is valid, otherwise returns \c false.

        A valid triangle has points which are not on a straight line.
        A valid rectangle is not empty (i.e., isValid() == !isEmpty()).

        \sa isNull(), isEmpty()
    */

/*
    constexpr inline bool ZQTriF::isValid() const noexcept
    {
        boost::numeric::ublas::matrix<qreal> triangle(3,2);
        triangle(0,0) = x1();
        triangle(0,1) = y1();
        triangle(1,0) = x2();
        triangle(1,1) = y2();
        triangle(2,0) = x3();
        triangle(2,1) = y3();
    }
*/

    /*!
        \fn QPointF ZQTriF::first() const

        Returns the first point in the triangle.

        \sa second(), third(), setFirst(), setSecond(), setThird()
    */

    /*!
        \fn QPointF ZQTriF::second() const

        Returns the second point in the triangle.

        \sa first(), third(), setFirst(), setSecond(), setThird()
    */


    /*!
        \fn QPointF ZQTriF::third() const

        Returns the second point in the triangle.

        \sa second(), third(), setFirst(), setSecond(), setThird()
    */

    /*!
        \fn QPointF ZQTriF::center() const

        Returns the center point of the triangle.

        \sa first(), second(), third()
    */

    /*!
        \fn qreal ZQTriF::x1() const

        Returns the x-coordinate of the first point.

        \sa x2(), x3(), y1(), y2(), y3()
    */

    /*!
        \fn qreal ZQTriF::x1() const

        Returns the x-coordinate of the first point.

        \sa x2(), x3(), y1(), y2(), y3()
    */

    /*!
        \fn qreal ZQTriF::y1() const

        Returns the y-coordinate of the first point.

        \sa x1(), x2(), x3(), y2(), y3()
    */

    /*!
        \fn qreal ZQTriF::x2() const

        Returns the x-coordinate of the second point.

        \sa x1(), x3(), y1(), y2(), y3()
    */

    /*!
        \fn qreal ZQTriF::y2() const

        Returns the y-coordinate of the second point.

        \sa x1(), x2(), x3(), y1(), y3()
    */

    /*!
        \fn qreal ZQTriF::x3() const

        Returns the x-coordinate of the third point.

        \sa x1(), x2(), y1(), y2(), y3()
    */

    /*!
        \fn qreal ZQTriF::y3() const

        Returns the y-coordinate of the third point.

        \sa x1(), x2(), x3(), y1(), y2()
    */

    /*!
        \fn qreal ZQTriF::angle() const

        Returns the angle of the triangle in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQTriF::angleRadians() const

        Returns the angle of the triangle in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */

    /*!
        \fn void ZQTriF::setX1(qreal pos)

        Sets the x-coordinate of the first point to \a pos.

        \sa setX2(), setX3(), setY1(), setY2(), setY3()
    */

    /*!
        \fn void ZQTriF::setY1(qreal pos)

        Sets the y-coordinate of the first point to \a pos.

        \sa setX1(), setX2(), setX3(), setY2(), setY3()
    */

    /*!
        \fn void ZQTriF::setX2(qreal pos)

        Sets the x-coordinate of the second point to \a pos.

        \sa setX1(), setX3(), setY1(), setY2(), setY3()
    */

    /*!
        \fn void ZQTriF::setY2(qreal pos)

        Sets the y-coordinate of the second point to \a pos.

        \sa setX1(), setX2(), setX3(), setY1(), setY3()
    */

    /*!
        \fn void ZQTriF::setX3(qreal pos)

        Sets the x-coordinate of the third point to \a pos.

        \sa setX1(), setX2(), setY1(), setY2(), setY3()
    */

    /*!
        \fn void ZQTriF::setY3(qreal pos)

        Sets the y-coordinate of the third point to \a pos.

        \sa setX1(), setX2(), setX3(), setY1(), setY2()
    */

    /*!
        \fn void ZQTriF::setFirst(QPointF p)

        Sets the first point to \a p.

        \sa first(), second(), third(), setSecond(), setThird()
    */

    /*!
        \fn void ZQTriF::setSecond(QPointF p)

        Sets the second point to \a p.

        \sa first(), second(), third(), setFirst(), setThird()
    */


    /*!
        \fn void ZQTriF::setThird(QPointF p)

        Sets the third point to \a p.

        \sa first(), second(), third(), setFirst(), setSecond()
    */

    /*!
        \fn void ZQTriF::setAngle(qreal angle)

        Sets the angle of the triangle to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQTriF::setAngleRadians(qreal angle)

        Sets the angle of the triangle to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */

    /*!
        \fn void ZQTriF::setAngleRadians(qreal angle)

        Sets the angle of the triangle to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */

    /*!
        \fn qreal ZQTriF::length12()

        Returns the length between the first and second points.

        \sa length13(), length23(), area()
    */

    /*!
        \fn qreal ZQTriF::length13()

        Returns the length between the first and third points.

        \sa length12(), length23(), area()
    */

    /*!
        \fn qreal ZQTriF::length23()

        Returns the length between the second and third points.

        \sa length13(), length23(), area()
    */

    /*!
        \fn qreal ZQTriF::area()

        Returns the area of the triangle.

        \sa length12(), length13(), length23()
    */

    /*!
        \fn void ZQTriF::moveX1(qreal pos)

        Moves the x-coordinate of the first point by an offset of \a pos.

        \sa moveX2(), moveX3(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTriF::moveY1(qreal pos)

        Moves the y-coordinate of the first point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveX3(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTriF::moveX2(qreal pos)

        Moves the x-coordinate of the second point by an offset of \a pos.

        \sa moveX2(), moveX3(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTriF::moveY2(qreal pos)

        Moves the y-coordinate of the second point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveX3(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTriF::moveX3(qreal pos)

        Moves the x-coordinate of the second point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTriF::moveY3(qreal pos)

        Moves the y-coordinate of the second point by an offset of \a pos.

        \sa moveX1(), moveX2(), moveX3(), moveY1(), moveY2()
    */

    /*!
        \fn void ZQTriF::moveFirst(QPointF p)

        Moves the x- and y-coordinates of the first point by an offset of the
        x- and y- coordinates in \a p.

        \sa moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTriF::moveSecond(QPointF p)

        Moves the x- and y-coordinates of the second point by an offset of the
        x- and y- coordinates in \a p.

        \sa moveFirst(), moveThird(), moveBy()
    */

    /*!
        \fn void ZQTriF::moveThird(QPointF p)

        Moves the x- and y-coordinates of the third point by an offset of the
        x- and y- coordinates in \a p.

        \sa moveFirst(), moveSecond(), moveBy()
    */

    /*!
        \fn void ZQTriF::moveCenter(QPointF p)

        Moves the x- and y-coordinates of the center point by an offset of the
        x- and y- coordinates in \a p. This has the consequence of moving all three
        control points of the triangle by that distance.

        \sa moveFirst(), moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTriF::moveBy(QPointF p1, QPointF p2, QPointF p3)

        Moves the x- and y-coordinates of the first point by \a p1, the
        x- and y-coordinates of the second point by \a p2, and the
        x- and y-coordinates of the third point by \a p3.

        \sa moveFirst(), moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTriF::movedX1(qreal pos)

        Returns a triangle with the x-coordinate of the first point moved
        by an offset of \a pos.

        \sa movedX2(), movedX3(), movedY1(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTriF::movedY1(qreal pos)

        Returns a triangle with the y-coordinate of the first point moved
        by an offset of \a pos.

        \sa movedX1(), movedX2(), movedX3(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTriF::movedX2(qreal pos)

        Returns a triangle with the x-coordinate of the second point moved
        by an offset of \a pos.

        \sa movedX2(), movedX3(), movedY1(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTriF::movedY2(qreal pos)

        Returns a triangle with the y-coordinate of the second point moved
        by an offset of \a pos.

        \sa movedX1(), movedX2(), movedX3(), movedY2(), movedY3()
    */

    /*!
        \fn void ZQTriF::movedX3(qreal pos)

        Returns a triangle with the x-coordinate of the second point moved
        by an offset of \a pos.

        \sa moveX1(), moveX2(), moveY1(), moveY2(), moveY3()
    */

    /*!
        \fn void ZQTriF::movedY3(qreal pos)

        Returns a triangle with the y-coordinate of the second point moved
        by an offset of \a pos.

        \sa movedX1(), movedX2(), movedX3(), movedY1(), movedY2()
    */

    /*!
        \fn void ZQTriF::movedFirst(QPointF p)

        Returns a triangle with the x- and y-coordinates of the first point moved
        by an offset of the x- and y- coordinates in \a p.

        \sa moveSecond(), moveThird()
    */

    /*!
        \fn void ZQTriF::movedSecond(QPointF p)

        Returns a triangle with the x- and y-coordinates of the second point moved
        by an offset of the x- and y- coordinates in \a p.

        \sa moveFirst(), moveThird(), moveBy()
    */

    /*!
        \fn void ZQTriF::movedThird(QPointF p)

        Returns a triangle with the x- and y-coordinates of the third point moved
        by an offset of the x- and y- coordinates in \a p.

        \sa moveFirst(), moveSecond(), moveBy()
    */

    /*!
        \fn void ZQTriF::movedCenter(QPointF p)

        Returns a triangle with  the x- and y-coordinates of the center point moved
        by an offset of the x- and y- coordinates in \a p. This has the
        consequence of moving all three control points of the triangle by that distance.

        \sa moveFirst(), moveSecond(), moveThird()
    */


    /*!
        \fn void ZQTriF::movedBy(QPointF p1, QPointF p2, QPointF p3)

        Returns a triangle with the x- and y-coordinates of the first point
        moved by \a p1, the x- and y-coordinates of the second point moved
        by \a p2, and the x- and y-coordinates of the third point moved by \a p3.

        \sa moveFirst(), moveSecond(), moveThird()
    */


    /*!
        \fn ZQTriF ZQTriF::translated(qreal dx, qreal dy) const

        Returns a copy of the triangle that is translated \a dx along the
        x axis and \a dy along the y axis, relative to the current
        position. Positive values move the triangle to the right and
        down.

        \sa translate()

    */


    /*!
        \fn ZQTriF ZQTriF::translated(const QPointF &offset) const

        \overload

        Returns a copy of the triangle that is translated
        \a{offset}.\l{QPoint::x()}{x()} along the x axis and
        \a{offset}.\l{QPoint::y()}{y()} along the y axis, relative to the
        current position.
    */

    /*!
        \fn void ZQTriF::translate(qreal dx, qreal dy)

        Moves the triangle \a dx along the x axis and \a dy along the y
        axis, relative to the current position. Positive values move the
        triangle to the right and down.

        \sa moveTopLeft(), moveTo(), translated()
    */


    /*!
        \fn void ZQTriF::translate(const QPointF &offset)
        \overload

        Moves the triangle \a{offset}.\l{QPoint::x()}{x()} along the x
        axis and \a{offset}.\l{QPoint::y()}{y()} along the y axis,
        relative to the current position.
    */


    /*!
        \fn void ZQTriF::rotate(qreal da) const
        \since 5.7

        Rotates the triangle by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQTriF::rotateRadians(qreal da) const
        \since 5.7

        Rotates the triangle by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQTriF ZQTriF::rotated(qreal da) const
        \since 5.7

        Returns a copy of the triangle rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQTriF ZQTriF::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the triangle rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */

    /*!
        \fn qreal ZQTriF::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa angle()
    */


    /*!
        \fn void ZQTriF::getTri(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3) const

        Extracts the position of the triangle's first point to *\a x1
        and *\a y1, its second point to *\a x2 and *\a y2, and its third point
        to *\a x3 and *\a y3.

        \sa setTri()
    */

    /*!
        \fn void ZQTriF::getTri(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, qreal *angle) const

        Extracts the position of the triangle's first point to *\a x1
        and *\a y1, its second point to *\a x2 and *\a y2, and its third point
        to *\a x3 and *\a y3, and its angle to *\a angle in degrees.

        \sa setTri()
    */

    /*!
        \fn void ZQTriF::getTriRadians(qreal *x1, qreal *y1, qreal *x2, qreal *y2, qreal *x3, qreal *y3, qreal *angle) const

        Extracts the position of the triangle's first point to *\a x1
        and *\a y1, its second point to *\a x2 and *\a y2, and its third point
        to *\a x3 and *\a y3, and its angle to *\a angle in radians.

        \sa setTriRadians()
    */



    /*!
        \fn void ZQTriF::setTri(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3)

        Sets the coordinates of the triangle's first point to (\a{x1},
        \a{y1}), its second point to (\a{x2}, \a{y2}), and its third
        point to (\a{x3}, \a{y3}).

        \sa getTri()
    */

    /*!
        \fn void ZQTriF::setTri(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal angle)

        Sets the coordinates of the triangle's first point to (\a{x1},
        \a{y1}), its second point to (\a{x2}, \a{y2}), and its third
        point to (\a{x3}, \a{y3}), and its angle to \a angle in degrees.

        \sa getTri()
    */

    /*!
        \fn void ZQTriF::setTriRadians(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal angle)

        Sets the coordinates of the triangle's first point to (\a{x1},
        \a{y1}), its second point to (\a{x2}, \a{y2}), and its third
        point to (\a{x3}, \a{y3}), and its angle to \a angle in radians.

        \sa getTriRadians()
    */



    /*!
        \fn bool ZQTriF::contains(const QPointF &point, bool proper) const

        Returns \c true if the given \a point is inside or on the edge of
        the triangle, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the given \a point is \e inside the
        triangle (i.e., not on the edge).

        \sa intersects()
    */

    bool ZQTriF::contains(const QPointF &p, bool proper) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const QPainterPath path1 = toPath();

        // FIXME proper=false is not honored because there isn't a way
        // to test if a point is on the edge.
        return path1.contains(p);

    }


    /*!
        \fn bool ZQTriF::contains(qreal x, qreal y, bool proper) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the triangle, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the point is entirely inside the
        triangle(not on the edge).
    */

    /*!
        \fn bool ZQTriF::contains(qreal x, qreal y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside this triangle,
        otherwise returns \c false.
    */

    /*!
        \fn bool ZQTriF::contains(const ZQTriF &triangle, bool proper) const
        \overload

        Returns \c true if the given \a triangle is inside this triangle.
        otherwise returns \c false. If \a proper is true, this function only
        returns \c true if the \a triangle is entirely inside this
        triangle (not on the edge).
    */

    bool ZQTri::contains(const ZQTri &r, bool proper) const noexcept
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
        \fn QPainterPath ZQTriF::operator|(const ZQTriF &triangle) const

        Returns the bounding triangle of this triangle and the given \a
        triangle. The result will always have an angle of 0 degrees.

        \sa united()
    */

    QPainterPath ZQTriF::operator|(const ZQTriF &r) const noexcept
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
        \fn QPainterPath ZQTriF::united(const ZQTriF &triangle) const
        \since 4.2

        Returns the bounding triangle of this triangle and the given \a triangle.
        The result will always have an angle of 0 degrees.

        \image qtri-unite.png

        \sa intersected()
    */


    /*!
        \fn ZQTri ZQTri::operator&(const ZQTri &triangle) const

        Returns the intersection of this triangle and the given \a
        triangle. Returns an empty triangle if there is no intersection.
        The angle of the intersected triangle will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQTri::operator&(const ZQTriF &r) const noexcept
    {
        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersected(path2);

    }


    /*!
        \fn QPainterPath ZQTriF::intersected(const ZQTriF &triangle) const
        \since 4.2

        Returns the intersection of this triangle and the given \a
        triangle. Note that \c{r.intersected(s)} is equivalent to \c{r & s}.

        \image qtri-intersect.png

        \sa intersects(), united()()
    */

    /*!
        \fn bool ZQTriF::intersects(const ZQTriF &triangle) const

        Returns \c true if this triangle intersects with the given \a
        triangle (i.e., there is at least one pixel that is within both
        triangles), otherwise returns \c false.

        The intersectio triangle can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQTriF::intersects(const ZQTriF &r) const noexcept
    {
        const QPainterPath path1 = toPath();
        const QPainterPath path2 = r.toPath();

        return path1.intersects(path2);
    }

    /*!
        \fn bool operator==(const ZQTriF &r1, const ZQTriF &r2)
        \relates ZQTri

        Returns \c true if the triangles \a r1 and \a r2 are equal,
        otherwise returns \c false.
    */


    /*!
        \fn bool operator!=(const ZQTriF &r1, const ZQTriF &r2)
        \relates ZQTri

        Returns \c true if the triangles \a r1 and \a r2 are different, otherwise
        returns \c false.
    */


    /*!
        \fn QPainterPath ZQTriF::toPath()

        Converts the triangle into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQTriF::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the triangle about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    /*!
        \fn QString ZQTriF::toString()

        Returns a printable string of the triangle.
    */


    constexpr QPainterPath ZQTri::toPath() const noexcept
    {
        QPainterPath path;
        QPointF c1 = first();
        QPointF c2 = second();
        QPointF c3 = third();
        QPointF cn = center();

        QPointF c1a, c2a, c3a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;

        path.moveTo(c1);
        path.lineTo(c2);
        path.lineTo(c3);
        path.lineTo(c1);
        path.closeSubpath();
        return path;
    }

    constexpr QPainterPath ZQTri::toPath(const QMatrix3x3 &mat, const QPointF& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = first();
        QPointF c2 = second();
        QPointF c3 = third();
        QPointF cn = center();

        QPointF c1a, c2a, c3a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;

        QPoint c1r, c2r, c3r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        boost::geometry::transform(c3a - ref, c3r, project2D);

        path.moveTo(c1 + ref);
        path.lineTo(c2 + ref);
        path.lineTo(c3 + ref);
        path.lineTo(c1 + ref);
        path.closeSubpath();
        return path;
    }

    /*!
        \fn ZQTri ZQTriF::toTri() const

        Returns a ZQTri based on the values of this triangle.  Note that the
        coordinates in the returned triangle are rounded to the nearest integer.

        \sa ZQTriF(), toAlignedTri()
    */

    /*!
        \fn ZQTri ZQTriF::toAlignedTri() const
        \since 4.3

        Returns a ZQTri based on the values of this triangle that is the
        smallest possible integer triangle that completely contains this
        triangle.

        \sa toTri()
    */

    ZQTri ZQTriF::toAlignedTri() const noexcept
    {
        int xmin = int(qFloor(xp));
        int xmax = int(qCeil(xp + w));
        int ymin = int(qFloor(yp));
        int ymax = int(qCeil(yp + h));
        return ZQTri(xmin, ymin, xmax - xmin, ymax - ymin);
    }


    /*****************************************************************************
      ZQTriF stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQTriF &triangle)

        \relates ZQTriF

        Writes the \a triangle to the \a stream, and returns a reference to the
        stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQTriF &r)
    {
        s << double(r.x()) << double(r.y()) << double(r.width()) << double(r.height());
        return s;
    }

    /*!
        \fn QDataStream &operator>>(QDataStream &stream, ZQTriF &triangle)

        \relates ZQTriF

        Reads a \a triangle from the \a stream, and returns a reference to the
        stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQTriF &r)
    {
        double x, y, w, h, a;
        s >> x;
        s >> y;
        s >> w;
        s >> h;
        s >> a;
        r.setTri(qreal(x), qreal(y), qreal(w), qreal(h));
        return s;
    }

    #endif // QT_NO_DATASTREAM


    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQTriF &r)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }
    #endif

}
