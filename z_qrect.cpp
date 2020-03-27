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

#include "z_qrect.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/segment.hpp>
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(QPointF, qreal, boost::geometry::cs::cartesian, x, y, setX, setY);
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(QPoint, int, boost::geometry::cs::cartesian, x, y, setX, setY);
BOOST_GEOMETRY_REGISTER_SEGMENT(QLineF, QPointF, p1, p2);


namespace z_qtshapes {

    /*!
        \class ZQRect
        \inmodule Zgeometry
        \ingroup painting
        \reentrant

        \brief The ZQRect class defines a rectangle in the plane using
        integer precision.

        A rectangle is normally expressed as a top-left corner and a
        size.  The size (width and height) of a ZQRect is always equivalent
        to the mathematical rectangle that forms the basis for its
        rendering.

        A ZQRect can be constructed with a set of left, top, width and
        height integers, or from a QPoint and a QSize.  The following code
        creates two identical rectangles.

        \snippet code/src_corelib_tools_qrect.cpp 0

        There is a third constructor that creates a ZQRect using the
        top-left and bottom-right coordinates, but we recommend that you
        avoid using it. The rationale is that for historical reasons the
        values returned by the bottom() and right() functions deviate from
        the true bottom-right corner of the rectangle.

        The ZQRect class provides a collection of functions that return the
        various rectangle coordinates, and enable manipulation of
        these. ZQRect also provides functions to move the rectangle relative
        to the various coordinates. In addition there is a moveTo()
        function that moves the rectangle, leaving its top left corner at
        the given coordinates. Alternatively, the translate() function
        moves the rectangle the given offset relative to the current
        position, and the translated() function returns a translated copy
        of this rectangle.

        The size() function returns the rectange's dimensions as a
        QSize. The dimensions can also be retrieved separately using the
        width() and height() functions. To manipulate the dimensions use
        the setSize(), setWidth() or setHeight() functions. Alternatively,
        the size can be changed by applying either of the functions
        setting the rectangle coordinates, for example, setBottom() or
        setRight().

        The contains() function tells whether a given point is inside the
        rectangle or not, and the intersects() function returns \c true if
        this rectangle intersects with a give rectangle. The ZQRect class
        also provides the intersected() function which returns the
        intersectio rectangle, and the united() function which returns the
        rectangle that encloses the give rectangle and this:

        \table
        \row
        \li \inlineimage qrect-intersect.png
        \li \inlineimage qrect-unite.png
        \row
        \li intersected()
        \li united()
        \endtable

        The isEmpty() function returns \c true if left() > right() or top() >
        bottom(). Note that an empty rectangle is not valid: The isValid()
        function returns \c true if left() <= right() \e and top() <=
        bottom(). A null rectangle (isNull() == true) on the other hand,
        has both width and height set to 0.

        Note that due to the way ZQRect and ZQRectF are defined, an
        empty ZQRect is defined in essentially the same way as ZQRectF.

        Finally, ZQRect objects can be streamed as well as compared.

        \tableofcontents

        \section1 Rendering

        When using an \l {QPainter::Antialiasing}{anti-aliased} painter,
        the boundary line of a ZQRect will be rendered symmetrically on
        both sides of the mathematical rectangle's boundary line. But when
        using an aliased painter (the default) other rules apply.

        Then, when rendering with a one pixel wide pen the ZQRect's boundary
        line will be rendered to the right and below the mathematical
        rectangle's boundary line.

        When rendering with a two pixels wide pen the boundary line will
        be split in the middle by the mathematical rectangle. This will be
        the case whenever the pen is set to an even number of pixels,
        while rendering with a pen with an odd number of pixels, the spare
        pixel will be rendered to the right and below the mathematical
        rectangle as in the one pixel case.

        \table
        \row
            \li \inlineimage qrect-diagram-zero.png
            \li \inlineimage qrect-diagram-one.png
        \row
            \li Logical representation
            \li One pixel wide pen
        \row
            \li \inlineimage qrect-diagram-two.png
            \li \inlineimage qrect-diagram-three.png
        \row
            \li Two pixel wide pen
            \li Three pixel wide pen
        \endtable

        \section1 Coordinates

        The ZQRect class provides a collection of functions that return the
        various rectangle coordinates, and enable manipulation of
        these. ZQRect also provides functions to move the rectangle relative
        to the various coordinates.

        For example the left(), setLeft() and moveLeft() functions as an
        example: left() returns the x-coordinate of the rectangle's left
        edge, setLeft() sets the left edge of the rectangle to the given x
        coordinate (it may change the width, but will never change the
        rectangle's right edge) and moveLeft() moves the entire rectangle
        horizontally, leaving the rectangle's left edge at the given x
        coordinate and its size unchanged.

        \image qrect-coordinates.png

        Note that for historical reasons the values returned by the
        bottom() and right() functions deviate from the true bottom-right
        corner of the rectangle: The right() function returns \e { left()
        + width() - 1} and the bottom() function returns \e {top() +
        height() - 1}. The same is the case for the point returned by the
        bottomRight() convenience function. In addition, the x and y
        coordinate of the topRight() and bottomLeft() functions,
        respectively, contain the same deviation from the true right and
        bottom edges.

        We recommend that you use x() + width() and y() + height() to find
        the true bottom-right corner, and avoid right() and
        bottom(). Another solution is to use ZQRectF: The ZQRectF class
        defines a rectangle in the plane using floating point accuracy for
        coordinates, and the ZQRectF::right() and ZQRectF::bottom()
        functions \e do return the right and bottom coordinates.

        It is also possible to add offsets to this rectangle's coordinates
        using the adjust() function, as well as retrieve a new rectangle
        based on adjustments of the original one using the adjusted()
        function. If either of the width and height is negative, use the
        normalized() function to retrieve a rectangle where the corners
        are swapped.

        In addition, ZQRect provides the getCoords() function which extracts
        the position of the rectangle's top-left and bottom-right corner,
        and the getRect() function which extracts the rectangle's top-left
        corner, width and height. Use the setCoords() and setRect()
        function to manipulate the rectangle's coordinates and dimensions
        in one go.

        \section1 Constraints

        ZQRect is limited to the minimum and maximum values for the \c int type.
        Operations on a ZQRect that could potentially result in values outside this
        range will result in undefined behavior.

        \sa ZQRectF, QRegion
    */

    /*****************************************************************************
      ZQRect member functions
     *****************************************************************************/

    /*!
        \fn ZQRect::ZQRect()

        Constructs a null rectangle.

        \sa isNull()
    */

    /*!
        \fn ZQRect::ZQRect(const QPoint &topLeft, const QPoint &bottomRight)

        Constructs a rectangle with the given \a topLeft and \a bottomRight corners.

        \sa setTopLeft(), setBottomRight()
    */

    /*!
        \fn ZQRect::ZQRect(const QPoint &topleft, const QPoint &bottomright, int angle)

        Constructs a rectangle with the given \a topLeft and \a bottomRight corners,
        with an \a angle in degrees.

        \sa setTopLeft(), setBottomRight()
    */

    /*!
        \fn ZQRect::ZQRect(const QPoint &topLeft, const QSize &size)

        Constructs a rectangle with the given \a topLeft corner and the
        given \a size.

        \sa setTopLeft(), setSize()
    */

    /*!
        \fn ZQRect::ZQRect(const QPoint &topLeft, const QSize &size, int angle)

        Constructs a rectangle with the given \a topLeft corner and the
        given \a size, with an \a angle in degrees.

        \sa setTopLeft(), setSize()
    */

    /*!
        \fn ZQRect::ZQRect(int x, int y, int width, int height)

        Constructs a rectangle with (\a x, \a y) as its top-left corner
        and the given \a width and \a height.

        \sa setRect()
    */

    /*!
        \fn ZQRect::ZQRect(int left, int top, int width, int height, int angle)

        Constructs a rectangle with (\a x, \a y) as its top-left corner
        and the given \a width and \a height, with an \a angle in degrees.

        \sa setRect()
    */


    /*!
        \fn bool ZQRect::isNull() const

        Returns \c true if the rectangle is a null rectangle, otherwise
        returns \c false.

        A null rectangle has both the width and the height set to 0 (i.e.,
        right() == left() - 1 and bottom() == top() - 1). A null rectangle
        is also empty, and hence is not valid.

        \sa isEmpty(), isValid()
    */

    /*!
        \fn bool ZQRect::isEmpty() const

        Returns \c true if the rectangle is empty, otherwise returns \c false.

        An empty rectangle has a left() > right() or top() > bottom(). An
        empty rectangle is not valid (i.e., isEmpty() == !isValid()).

        Use the normalized() function to retrieve a rectangle where the
        corners are swapped.

        \sa isNull(), isValid(), normalized()
    */

    /*!
        \fn bool ZQRect::isValid() const

        Returns \c true if the rectangle is valid, otherwise returns \c false.

        A valid rectangle has a left() <= right() and top() <=
        bottom(). Note that non-trivial operations like intersections are
        not defined for invalid rectangles. A valid rectangle is not empty
        (i.e., isValid() == !isEmpty()).

        \sa isNull(), isEmpty(), normalized()
    */

    /*!
        Normalizes the rectangle; i.e., changes the rectangle to have a
        non-negative width and height.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    void ZQRect::normalize() const noexcept
    {
        if (w < 0) {
            xp += w;
            w = -w;
        }
        if (h < 0) {
            yp += h;
            h = -h;
        }
    }

    /*!
        Returns a normalized rectangle; i.e., a rectangle that has a
        non-negative width and height, and an angle with an absolute size
        no greater than a predefined number of full rotations in degrees.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    ZQRect ZQRect::normalized() const noexcept
    {
        ZQRect r = *this;

        if (x2 < x1 - 1) {                                // swap bad x values
            r.x1 = x2;
            r.x2 = x1;
        } else {
            r.x1 = x1;
            r.x2 = x2;
        }
        if (y2 < y1 - 1) {                                // swap bad y values
            r.y1 = y2;
            r.y2 = y1;
        } else {
            r.y1 = y1;
            r.y2 = y2;
        }

        return r;
    }

    /*!
        \fn int ZQRect::left() const

        Returns the x-coordinate of the rectangle's left edge. Equivalent
        to x().

        \sa setLeft(), topLeft(), bottomLeft()
    */

    /*!
        \fn int ZQRect::top() const

        Returns the y-coordinate of the rectangle's top edge.
        Equivalent to y().

        \sa setTop(), topLeft(), topRight()
    */

    /*!
        \fn int ZQRect::right() const

        Returns the x-coordinate of the rectangle's right edge.

        Note that for historical reasons this function returns left() +
        width() - 1; use x() + width() to retrieve the true x-coordinate.

        \sa setRight(), topRight(), bottomRight()
    */

    /*!
        \fn int ZQRect::bottom() const

        Returns the y-coordinate of the rectangle's bottom edge.

        Note that for historical reasons this function returns top() +
        height() - 1; use y() + height() to retrieve the true y-coordinate.

        \sa setBottom(), bottomLeft(), bottomRight()
    */

    /*!
        \fn int ZQRect::x() const

        Returns the x-coordinate of the rectangle's left edge. Equivalent to left().

        \sa setX(), y(), topLeft()
    */

    /*!
        \fn int ZQRect::y() const

        Returns the y-coordinate of the rectangle's top edge. Equivalent to top().

        \sa setY(), x(), topLeft()
    */

    /*!
        \fn int ZQRect::angle() const

        Returns the angle of the rectangle in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQRect::angleRadians() const

        Returns the angle of the rectangle in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */

    /*!
        \fn void ZQRect::setLeft(int x)

        Sets the left edge of the rectangle to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the rectangle.

        Equivalent to setX().

        \sa left(), moveLeft()
    */

    /*!
        \fn void ZQRect::setTop(int y)

        Sets the top edge of the rectangle to the given \a y
        coordinate. May change the height, but will never change the
        bottom edge of the rectangle.

        Equivalent to setY().

        \sa top(), moveTop()
    */

    /*!
        \fn void ZQRect::setRight(int x)

        Sets the right edge of the rectangle to the given \a x
        coordinate. May change the width, but will never change the left
        edge of the rectangle.

        \sa right(), moveRight()
    */

    /*!
        \fn void ZQRect::setBottom(int y)

        Sets the bottom edge of the rectangle to the given \a y
        coordinate. May change the height, but will never change the top
        edge of the rectangle.

        \sa bottom(), moveBottom(),
    */

    /*!
        \fn void ZQRect::setX(int x)

        Sets the left edge of the rectangle to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the rectangle.

        Equivalent to setLeft().

        \sa x(), setY(), setTopLeft()
    */

    /*!
        \fn void ZQRect::setY(int y)

        Sets the top edge of the rectangle to the given \a y
        coordinate. May change the height, but will never change the
        bottom edge of the rectangle.

        Equivalent to setTop().

        \sa y(), setX(), setTopLeft()
    */

    /*!
        \fn void ZQRect::setAngle(int angle)

        Sets the angle of the rectangle to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQRect::setAngleRadians(qreal angle)

        Sets the angle of the rectangle to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */

    /*!
        \fn void ZQRect::setTopLeft(const QPoint &position)

        Set the top-left corner of the rectangle to the given \a
        position. May change the size, but will never change the
        bottom-right corner of the rectangle.

        \sa topLeft(), moveTopLeft()
    */

    /*!
        \fn void ZQRect::setBottomRight(const QPoint &position)

        Set the bottom-right corner of the rectangle to the given \a
        position. May change the size, but will never change the
        top-left corner of the rectangle.

        \sa bottomRight(), moveBottomRight()
    */

    /*!
        \fn void ZQRect::setTopRight(const QPoint &position)

        Set the top-right corner of the rectangle to the given \a
        position. May change the size, but will never change the
        bottom-left corner of the rectangle.

        \sa topRight(), moveTopRight()
    */

    /*!
        \fn void ZQRect::setBottomLeft(const QPoint &position)

        Set the bottom-left corner of the rectangle to the given \a
        position. May change the size, but will never change the
        top-right corner of the rectangle.

        \sa bottomLeft(), moveBottomLeft()
    */

    /*!
        \fn QPoint ZQRect::topLeft() const

        Returns the position of the rectangle's top-left corner.

        \sa setTopLeft(), top(), left()
    */

    /*!
        \fn QPoint ZQRect::bottomRight() const

        Returns the position of the rectangle's bottom-right corner.

        Note that for historical reasons this function returns
        QPoint(left() + width() -1, top() + height() - 1).

        \sa setBottomRight(), bottom(), right()
    */

    /*!
        \fn QPoint ZQRect::topRight() const

        Returns the position of the rectangle's top-right corner.

        Note that for historical reasons this function returns
        QPoint(left() + width() -1, top()).

        \sa setTopRight(), top(), right()
    */

    /*!
        \fn QPoint ZQRect::bottomLeft() const

        Returns the position of the rectangle's bottom-left corner. Note
        that for historical reasons this function returns QPoint(left(),
        top() + height() - 1).

        \sa setBottomLeft(), bottom(), left()
    */

    /*!
        \fn QPoint ZQRect::center() const

        Returns the center point of the rectangle.

        \sa moveCenter()
    */


    /*!
        \fn void ZQRect::getRect(int *x, int *y, int *width, int *height) const

        Extracts the position of the rectangle's top-left corner to *\a x
        and *\a y, and its dimensions to *\a width and *\a height.

        \sa setRect(), getCoords()
    */

    /*!
        \fn void ZQRect::getRect(int *x, int *y, int *width, int *height, int *angle) const

        Extracts the position of the rectangle's top-left corner to *\a x
        and *\a y, its dimensions to *\a width and *\a height, and its angle to *\a angle in degrees.

        \sa setRect(), getCoords()
    */

    /*!
        \fn void ZQRect::getRectRadians(int *x, int *y, int *width, int *height, qreal *angle) const

        Extracts the position of the rectangle's top-left corner to *\a x
        and *\a y, its dimensions to *\a width and *\a height, and its angle to *\a angle in radians.

        \sa setRectRadians(), getCoordsRadians()
    */

    /*!
        \fn void ZQRect::getCoords(int *x1, int *y1, int *x2, int *y2) const

        Extracts the position of the rectangle's top-left corner to *\a x1
        and *\a y1, and the position of the bottom-right corner to *\a x2
        and *\a y2.

        \sa setCoords(), getRect()
    */

    /*!
        \fn void ZQRect::getCoords(int *x1, int *y1, int *x2, int *y2, int *angle) const

        Extracts the position of the rectangle's top-left corner to *\a x1
        and *\a y1, the position of the bottom-right corner to *\a x2
        and *\a y2 and the angle to *\a angle in degrees.

        \sa setCoords(), getRect()
    */

    /*!
        \fn void ZQRect::getCoordsRadians(int *x1, int *y1, int *x2, int *y2, qreal *angle) const

        Extracts the position of the rectangle's top-left corner to *\a x1
        and *\a y1, the position of the bottom-right corner to *\a x2
        and *\a y2 and the angle to *\a angle in radians.

        \sa setCoordsRadians(), getRectRadians()
    */


    /*!
        \fn void ZQRect::moveLeft(int x)

        Moves the rectangle horizontally, leaving the rectangle's left
        edge at the given \a x coordinate. The rectangle's size is
        unchanged.

        \sa left(), setLeft(), moveRight()
    */

    /*!
        \fn void ZQRect::moveTop(int y)

        Moves the rectangle vertically, leaving the rectangle's top edge
        at the given \a y coordinate. The rectangle's size is unchanged.

        \sa top(), setTop(), moveBottom()
    */


    /*!
        \fn void ZQRect::moveRight(int x)

        Moves the rectangle horizontally, leaving the rectangle's right
        edge at the given \a x coordinate. The rectangle's size is
        unchanged.

        \sa right(), setRight(), moveLeft()
    */


    /*!
        \fn void ZQRect::moveBottom(int y)

        Moves the rectangle vertically, leaving the rectangle's bottom
        edge at the given \a y coordinate. The rectangle's size is
        unchanged.

        \sa bottom(), setBottom(), moveTop()
    */


    /*!
        \fn void ZQRect::moveTopLeft(const QPoint &position)

        Moves the rectangle, leaving the top-left corner at the given \a
        position. The rectangle's size is unchanged.

        \sa setTopLeft(), moveTop(), moveLeft()
    */


    /*!
        \fn void ZQRect::moveBottomRight(const QPoint &position)

        Moves the rectangle, leaving the bottom-right corner at the given
        \a position. The rectangle's size is unchanged.

        \sa setBottomRight(), moveRight(), moveBottom()
    */


    /*!
        \fn void ZQRect::moveTopRight(const QPoint &position)

        Moves the rectangle, leaving the top-right corner at the given \a
        position. The rectangle's size is unchanged.

        \sa setTopRight(), moveTop(), moveRight()
    */


    /*!
        \fn void ZQRect::moveBottomLeft(const QPoint &position)

        Moves the rectangle, leaving the bottom-left corner at the given
        \a position. The rectangle's size is unchanged.

        \sa setBottomLeft(), moveBottom(), moveLeft()
    */


    /*!
        \fn void ZQRect::moveCenter(const QPoint &position)

        Moves the rectangle, leaving the center point at the given \a
        position. The rectangle's size is unchanged.

        \sa center()
    */

    /*!
        \fn void ZQRect::moveTo(int x, int y)

        Moves the rectangle, leaving the top-left corner at the given
        position (\a x, \a y).  The rectangle's size is unchanged.

        \sa translate(), moveTopLeft()
    */

    /*!
        \fn void ZQRect::moveTo(const QPoint &position)

        Moves the rectangle, leaving the top-left corner at the given \a
        position.
    */

    /*!
        \fn void ZQRect::translate(int dx, int dy)

        Moves the rectangle \a dx along the x axis and \a dy along the y
        axis, relative to the current position. Positive values move the
        rectangle to the right and down.

        \sa moveTopLeft(), moveTo(), translated()
    */


    /*!
        \fn void ZQRect::translate(const QPoint &offset)
        \overload

        Moves the rectangle \a{offset}.\l{QPoint::x()}{x()} along the x
        axis and \a{offset}.\l{QPoint::y()}{y()} along the y axis,
        relative to the current position.
    */


    /*!
        \fn ZQRect ZQRect::translated(int dx, int dy) const

        Returns a copy of the rectangle that is translated \a dx along the
        x axis and \a dy along the y axis, relative to the current
        position. Positive values move the rectangle to the right and
        down.

        \sa translate()

    */


    /*!
        \fn ZQRect ZQRect::translated(const QPoint &offset) const

        \overload

        Returns a copy of the rectangle that is translated
        \a{offset}.\l{QPoint::x()}{x()} along the x axis and
        \a{offset}.\l{QPoint::y()}{y()} along the y axis, relative to the
        current position.
    */

    /*!
        \fn ZQRect ZQRect::transposed() const
        \since 5.7

        Returns a copy of the rectangle that has its width and height
        exchanged:

        \snippet code/src_corelib_tools_qrect.cpp 2

        \sa QSize::transposed()
    */

    /*!
        \fn void ZQRect::rotate(int da) const
        \since 5.7

        Rotates the rectangle by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQRect::rotateRadians(qreal da) const
        \since 5.7

        Rotates the rectangle by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQRect ZQRect::rotated(int da) const
        \since 5.7

        Returns a copy of the rectangle rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQRect ZQRect::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the rectangle rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */


    /*!
        \fn void ZQRect::normalizeAngle() const

        Normalizes the angle i.e. changes the angle to have a value between 0
        and 360 times a fixed number of rotations.

        \sa normalizedAngle()
    */

    /*!
        \fn int ZQRect::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa normalizedAngle()
    */


    /*!
        \fn void ZQRect::setRect(int x, int y, int width, int height)

        Sets the coordinates of the rectangle's top-left corner to (\a{x},
        \a{y}), and its size to the given \a width and \a height.

        \sa getRect(), setCoords()
    */

    /*!
        \fn void ZQRect::setRect(int x, int y, int width, int height, int angle)

        Sets the coordinates of the rectangle's top-left corner to (\a{x},
        \a{y}), its size to the given \a width and \a height, and its angle to \a angle in degrees.

        \sa getRect(), setCoords()
    */

    /*!
        \fn void ZQRect::setRectRadians(int x, int y, int width, int height, qreal angle)

        Sets the coordinates of the rectangle's top-left corner to (\a{x},
        \a{y}), its size to the given \a width and \a height, and its angle to \a angle in radians.

        \sa getRectRadians(), setCoordsRadians()
    */

    /*!
        \fn void ZQRect::setCoords(int x1, int y1, int x2, int y2)

        Sets the coordinates of the rectangle's top-left corner to (\a x1,
        \a y1), and the coordinates of its bottom-right corner to (\a x2,
        \a y2).

        \sa getCoords(), setRect()
    */

    /*!
        \fn void ZQRect::setCoords(int x1, int y1, int x2, int y2, int angle)

        Sets the coordinates of the rectangle's top-left corner to (\a x1,
        \a y1), the coordinates of its bottom-right corner to (\a x2,
        \a y2), and the angle to \a angle in degrees.

        \sa getCoords(), setRect()
    */

    /*!
        \fn void ZQRect::setCoordsRadians(int x1, int y1, int x2, int y2, qreal angle)

        Sets the coordinates of the rectangle's top-left corner to (\a x1,
        \a y1), the coordinates of its bottom-right corner to (\a x2,
        \a y2), and the angle to \a angle in radians.

        \sa getCoordsRadians(), setRectRadians()
    */


    /*! \fn ZQRect ZQRect::adjusted(int dx1, int dy1, int dx2, int dy2) const

        Returns a new rectangle with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this rectangle.
        The angle of the rectangle is not affected.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQRect ZQRect::adjusted(int dx1, int dy1, int dx2, int dy2, int angle) const

        Returns a new rectangle with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this rectangle, and
        \a angle in degrees added to the rectangle's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQRect ZQRect::adjustedRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) const

        Returns a new rectangle with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this rectangle, and
        \a angle in radians added to the rectangle's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */

    /*! \fn void ZQRect::adjust(int dx1, int dy1, int dx2, int dy2)

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the rectangle. The angle of the rectangle
        is not affected.

        \sa adjusted(), adjustRadians(), adjustedRadians(), setRect()
    */

    /*! \fn void ZQRect::adjust(int dx1, int dy1, int dx2, int dy2, int angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the rectangle, and \a angle in degrees
        added to the rectangle's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn void ZQRect::adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the rectangle, and \a angle in radians
        added to the rectangle's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */


    /*!
        \fn QSize ZQRect::size() const

        Returns the size of the rectangle.

        \sa setSize(), width(), height()
    */

    /*!
        \fn int ZQRect::width() const

        Returns the width of the rectangle.

        \sa setWidth(), height(), size()
    */

    /*!
        \fn int ZQRect::height() const

        Returns the height of the rectangle.

        \sa setHeight(), width(), size()
    */

    /*!
        \fn void ZQRect::setWidth(int width)

        Sets the width of the rectangle to the given \a width. The right
        edge is changed, but not the left one.

        \sa width(), setSize()
    */


    /*!
        \fn void ZQRect::setHeight(int height)

        Sets the height of the rectangle to the given \a height. The bottom
        edge is changed, but not the top one.

        \sa height(), setSize()
    */


    /*!
        \fn void ZQRect::setSize(const QSize &size)

        Sets the size of the rectangle to the given \a size. The top-left
        corner is not moved.

        \sa size(), setWidth(), setHeight()
    */


    /*!
        \fn bool ZQRect::contains(const QPoint &point, bool proper) const

        Returns \c true if the given \a point is inside or on the edge of
        the rectangle, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the given \a point is \e inside the
        rectangle (i.e., not on the edge).

        \sa intersects()
    */

    bool ZQRect::contains(const QPoint &p, bool proper=false) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const ZQRect first = normalized();

        const QPainterPath path1 = first.toPath();

        // FIXME proper=false is not honored because there isn't a way
        // to test if a point is on the edge.
        return path1.contains(p);

    }


    /*!
        \fn bool ZQRect::contains(int x, int y, bool proper) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the rectangle, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the point is entirely inside the
        rectangle(not on the edge).
    */

    /*!
        \fn bool ZQRect::contains(int x, int y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside this rectangle,
        otherwise returns \c false.
    */

    /*!
        \fn bool ZQRect::contains(const ZQRect &rectangle, bool proper) const
        \overload

        Returns \c true if the given \a rectangle is inside this rectangle.
        otherwise returns \c false. If \a proper is true, this function only
        returns \c true if the \a rectangle is entirely inside this
        rectangle (not on the edge).
    */

    bool ZQRect::contains(const ZQRect &r, bool proper=false) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const ZQRect first = normalized();
        const ZQRect second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        if (proper && path1 == path2) {
            return false;
        }
        return path1.contains(path2);

   
    }

    /*!
        \fn ZQRect ZQRect::operator|(const ZQRect &rectangle) const

        Returns the bounding rectangle of this rectangle and the given \a
        rectangle. The result will always have an angle of 0 degrees.

        \sa united()
    */

    ZQRect ZQRect::operator|(const ZQRect &r) const noexcept
    {
        if (isNull())
            return r;
        if (r.isNull())
            return *this;

        const ZQRect first = normalized();
        const ZQRect second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.united(path2);

    }


    /*!
        \fn ZQRect ZQRect::united(const ZQRect &rectangle) const
        \since 4.2

        Returns the bounding rectangle of this rectangle and the given \a rectangle.
        The result will always have an angle of 0 degrees.

        \image qrect-unite.png

        \sa intersected()
    */


    /*!
        \fn ZQRect ZQRect::operator&(const ZQRect &rectangle) const

        Returns the intersection of this rectangle and the given \a
        rectangle. Returns an empty rectangle if there is no intersection.
        The angle of the intersected rectangle will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQRectF::operator&(const ZQRectF &r) const noexcept
    {
        if (isNull())
            return r;
        if (r.isNull())
            return *this;

        const ZQRect first = normalized();
        const ZQRect second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersected(path2);
    }


    /*!
        \fn ZQRect ZQRect::intersected(const ZQRect &rectangle) const
        \since 4.2

        Returns the intersection of this rectangle and the given \a
        rectangle. Note that \c{r.intersected(s)} is equivalent to \c{r & s}.

        \image qrect-intersect.png

        \sa intersects(), united()
    */

    /*!
        \fn bool ZQRect::intersects(const ZQRect &rectangle) const

        Returns \c true if this rectangle intersects with the given \a
        rectangle (i.e., there is at least one pixel that is within both
        rectangles), otherwise returns \c false.

        The intersectio rectangle can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQRect::intersects(const ZQRect &r) const noexcept
    {
        const ZQRect first = normalized();
        const ZQRect second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersects(path2);
    }

    /*!
        \fn bool operator==(const ZQRect &r1, const ZQRect &r2)
        \relates ZQRect

        Returns \c true if the rectangles \a r1 and \a r2 are equal,
        otherwise returns \c false.
    */


    /*!
        \fn bool operator!=(const ZQRect &r1, const ZQRect &r2)
        \relates ZQRect

        Returns \c true if the rectangles \a r1 and \a r2 are different, otherwise
        returns \c false.
    */

    /*!
        \fn ZQRect operator+(const ZQRect &rectangle, const QMargins &margins)
        \relates ZQRect

        Returns the \a rectangle grown by the \a margins.

        \since 5.1
    */

    /*!
        \fn ZQRect operator+(const QMargins &margins, const ZQRect &rectangle)
        \relates ZQRect
        \overload

        Returns the \a rectangle grown by the \a margins.

        \since 5.1
    */

    /*!
        \fn ZQRect operator-(const ZQRect &lhs, const QMargins &rhs)
        \relates ZQRect

        Returns the \a lhs rectangle shrunk by the \a rhs margins.

        \since 5.3
    */

    /*!
        \fn ZQRect ZQRect::marginsAdded(const QMargins &margins) const

        Returns a rectangle grown by the \a margins.

        \sa operator+=(), marginsRemoved(), operator-=()

        \since 5.1
    */

    /*!
        \fn ZQRect ZQRect::operator+=(const QMargins &margins)

        Adds the \a margins to the rectangle, growing it.

        \sa marginsAdded(), marginsRemoved(), operator-=()

        \since 5.1
    */

    /*!
        \fn ZQRect ZQRect::marginsRemoved(const QMargins &margins) const

        Removes the \a margins from the rectangle, shrinking it.

        \sa marginsAdded(), operator+=(), operator-=()

        \since 5.1
    */

    /*!
        \fn ZQRect ZQRect::operator -=(const QMargins &margins)

        Returns a rectangle shrunk by the \a margins.

        \sa marginsRemoved(), operator+=(), marginsAdded()

        \since 5.1
    */

    /*!
        \fn QPainterPath ZQRect::toPath()

        Converts the rectangle into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQRect::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the rectangle about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    /*!
        \fn QString ZQRect::toString()

        Returns a printable string of the rectangle.
    */

    constexpr QPainterPath ZQRect::toPath() const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(topRight());
        QPointF c2 = QPointF(bottomRight());
        QPointF c3 = QPointF(bottomLeft());
        QPointF c4 = QPointF(topLeft());
        QPointF cn = QPointF(center());

        QPointF c1a, c2a, c3a, c4a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;

        path.moveTo(c1a);
        path.lineTo(c2a);
        path.lineTo(c3a);
        path.lineTo(c4a);
        path.lineTo(c1a);
        path.closeSubpath();
        return path;
    }

    constexpr QPainterPath ZQRect::toPath(const QMatrix3x3 &mat, const QPointF& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(topRight());
        QPointF c2 = QPointF(bottomRight());
        QPointF c3 = QPointF(bottomLeft());
        QPointF c4 = QPointF(topLeft());
        QPointF cn = QPointF(center());

        QPointF c1a, c2a, c3a, c4a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;

        QPointF c1r, c2r, c3r, c4r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        boost::geometry::transform(c3a - ref, c3r, project2D);
        boost::geometry::transform(c4a - ref, c4r, project2D);
        c1r += ref;
        c2r += ref;
        c3r += ref;
        c4r += ref;

        path.moveTo(c1r);
        path.lineTo(c2r);
        path.lineTo(c3r);
        path.lineTo(c4r);
        path.lineTo(c1r);
        path.closeSubpath();
        return path;
    }

    /*****************************************************************************
      ZQRect stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQRect &rectangle)
        \relates ZQRect

        Writes the given \a rectangle to the given \a stream, and returns
        a reference to the stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQRect &r)
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
        \fn QDataStream &operator>>(QDataStream &stream, ZQRect &rectangle)
        \relates ZQRect

        Reads a rectangle from the given \a stream into the given \a
        rectangle, and returns a reference to the stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQRect &r)
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
    QDebug operator<<(QDebug dbg, const ZQRect &r)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }
    #endif

    /*!
        \class ZQRectF
        \inmodule Zgeometry
        \ingroup painting
        \reentrant

        \brief The ZQRectF class defines a rectangle in the plane using floating
        point precision.

        A rectangle is normally expressed as a top-left corner and a
        size.  The size (width and height) of a ZQRectF is always equivalent
        to the mathematical rectangle that forms the basis for its
        rendering.

        A ZQRectF can be constructed with a set of left, top, width and
        height coordinates, or from a QPointF and a QSizeF.  The following
        code creates two identical rectangles.

        \snippet code/src_corelib_tools_qrect.cpp 1

        There is also a third constructor creating a ZQRectF from a ZQRect,
        and a corresponding toEllipse() function that returns a ZQRect object
        based on the values of this rectangle (note that the coordinates
        in the returned rectangle are rounded to the nearest integer).

        The ZQRectF class provides a collection of functions that return
        the various rectangle coordinates, and enable manipulation of
        these. ZQRectF also provides functions to move the rectangle
        relative to the various coordinates. In addition there is a
        moveTo() function that moves the rectangle, leaving its top left
        corner at the given coordinates. Alternatively, the translate()
        function moves the rectangle the given offset relative to the
        current position, and the translated() function returns a
        translated copy of this rectangle.

        The size() function returns the rectange's dimensions as a
        QSizeF. The dimensions can also be retrieved separately using the
        width() and height() functions. To manipulate the dimensions use
        the setSize(), setWidth() or setHeight() functions. Alternatively,
        the size can be changed by applying either of the functions
        setting the rectangle coordinates, for example, setBottom() or
        setRight().

        The contains() function tells whether a given point is inside the
        rectangle or not, and the intersects() function returns \c true if
        this rectangle intersects with a give rectangle (otherwise
        false). The ZQRectF class also provides the intersected() function
        which returns the intersectio rectangle, and the united() function
        which returns the rectangle that encloses the give rectangle and
        this:

        \table
        \row
        \li \inlineimage qrect-intersect.png
        \li \inlineimage qrect-unite.png
        \row
        \li intersected()
        \li united()
        \endtable

        The isEmpty() function returns \c true if the rectangle's width or
        height is less than, or equal to, 0. Note that an empty rectangle
        is not valid: The isValid() function returns \c true if both width
        and height is larger than 0. A null rectangle (isNull() == true)
        on the other hand, has both width and height set to 0.

        Note that due to the way ZQRect and ZQRectF are defined, an
        empty ZQRectF is defined in essentially the same way as ZQRect.

        Finally, ZQRectF objects can be streamed as well as compared.

        \tableofcontents

        \section1 Rendering

        When using an \l {QPainter::Antialiasing}{anti-aliased} painter,
        the boundary line of a ZQRectF will be rendered symmetrically on both
        sides of the mathematical rectangle's boundary line. But when
        using an aliased painter (the default) other rules apply.

        Then, when rendering with a one pixel wide pen the ZQRectF's boundary
        line will be rendered to the right and below the mathematical
        rectangle's boundary line.

        When rendering with a two pixels wide pen the boundary line will
        be split in the middle by the mathematical rectangle. This will be
        the case whenever the pen is set to an even number of pixels,
        while rendering with a pen with an odd number of pixels, the spare
        pixel will be rendered to the right and below the mathematical
        rectangle as in the one pixel case.

        \table
        \row
            \li \inlineimage qrect-diagram-zero.png
            \li \inlineimage qrectf-diagram-one.png
        \row
            \li Logical representation
            \li One pixel wide pen
        \row
            \li \inlineimage qrectf-diagram-two.png
            \li \inlineimage qrectf-diagram-three.png
        \row
            \li Two pixel wide pen
            \li Three pixel wide pen
        \endtable

        \section1 Coordinates

        The ZQRectF class provides a collection of functions that return
        the various rectangle coordinates, and enable manipulation of
        these. ZQRectF also provides functions to move the rectangle
        relative to the various coordinates.

        For example: the bottom(), setBottom() and moveBottom() functions:
        bottom() returns the y-coordinate of the rectangle's bottom edge,
        setBottom() sets the bottom edge of the rectangle to the given y
        coordinate (it may change the height, but will never change the
        rectangle's top edge) and moveBottom() moves the entire rectangle
        vertically, leaving the rectangle's bottom edge at the given y
        coordinate and its size unchanged.

        \image qrectf-coordinates.png

        It is also possible to add offsets to this rectangle's coordinates
        using the adjust() function, as well as retrieve a new rectangle
        based on adjustments of the original one using the adjusted()
        function. If either of the width and height is negative, use the
        normalized() function to retrieve a rectangle where the corners
        are swapped.

        In addition, ZQRectF provides the getCoords() function which extracts
        the position of the rectangle's top-left and bottom-right corner,
        and the getRect() function which extracts the rectangle's top-left
        corner, width and height. Use the setCoords() and setRect()
        function to manipulate the rectangle's coordinates and dimensions
        in one go.

        \sa ZQRect, QRegion
    */

    /*****************************************************************************
      ZQRectF member functions
     *****************************************************************************/

    /*!
        \fn ZQRectF::ZQRectF()

        Constructs a null rectangle.

        \sa isNull()
    */

    /*!
        \fn ZQRectF::ZQRectF(const QPointF &topLeft, const QSizeF &size)

        Constructs a rectangle with the given \a topLeft corner and the given \a size.

        \sa setTopLeft(), setSize()
    */

    /*!
        \fn ZQRectF::ZQRectF(const QPointF &topLeft, const QSizeF &size, qreal angle)

        Constructs a rectangle with the given \a topLeft corner and the
        given \a size, with an \a angle in degrees.

        \sa setTopLeft(), setSize()
    */


    /*!
        \fn ZQRectF::ZQRectF(const QPointF &topLeft, const QPointF &bottomRight)
        \since 4.3

        Constructs a rectangle with the given \a topLeft and \a bottomRight corners.

        \sa setTopLeft(), setBottomRight()
    */

    /*!
        \fn ZQRectF::ZQRectF(const QPointF &topleft, const QPointF &bottomright, qreal angle)

        Constructs a rectangle with the given \a topLeft and \a bottomRight corners,
        with an \a angle in degrees.

        \sa setTopLeft(), setBottomRight()
    */

    /*!
        \fn ZQRectF::ZQRectF(qreal x, qreal y, qreal width, qreal height)

        Constructs a rectangle with (\a x, \a y) as its top-left corner
        and the given \a width and \a height.

        \sa setRect()
    */

    /*!
        \fn ZQRectF::ZQRectF(qreal left, qreal top, qreal width, qreal height, qreal angle)

        Constructs a rectangle with (\a x, \a y) as its top-left corner
        and the given \a width and \a height, with an \a angle in degrees.

        \sa setRect()
    */

    /*!
        \fn ZQRectF::ZQRectF(const ZQRect &rectangle)

        Constructs a ZQRectF rectangle from the given ZQRect \a rectangle.

        \sa toEllipse()
    */

    /*!
        \fn bool ZQRectF::isNull() const

        Returns \c true if the rectangle is a null rectangle, otherwise returns \c false.

        A null rectangle has both the width and the height set to 0. A
        null rectangle is also empty, and hence not valid.

        \sa isEmpty(), isValid()
    */

    /*!
        \fn bool ZQRectF::isEmpty() const

        Returns \c true if the rectangle is empty, otherwise returns \c false.

        An empty rectangle has width() <= 0 or height() <= 0.  An empty
        rectangle is not valid (i.e., isEmpty() == !isValid()).

        Use the normalized() function to retrieve a rectangle where the
        corners are swapped.

        \sa isNull(), isValid(), normalized()
    */

    /*!
        \fn bool ZQRectF::isValid() const

        Returns \c true if the rectangle is valid, otherwise returns \c false.

        A valid rectangle has a width() > 0 and height() > 0. Note that
        non-trivial operations like intersections are not defined for
        invalid rectangles. A valid rectangle is not empty (i.e., isValid()
        == !isEmpty()).

        \sa isNull(), isEmpty(), normalized()
    */


    /*!
        Normalizes the rectangle; i.e., changes the rectangle to have a
        non-negative width and height.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    void ZQRectF::normalize() const noexcept
    {
        if (w < 0) {
            xp += w;
            w = -w;
        }
        if (h < 0) {
            yp += h;
            h = -h;
        }
    }


    /*!
        Returns a normalized rectangle; i.e., a rectangle that has a
        non-negative width and height.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    ZQRectF ZQRectF::normalized() const noexcept
    {
        ZQRectF r = *this;

        if (r.w < 0) {
            r.xp += r.w;
            r.w = -r.w;
        }
        if (r.h < 0) {
            r.yp += r.h;
            r.h = -r.h;

        }
        return r;
    }

    /*!
        \fn qreal ZQRectF::x() const

        Returns the x-coordinate of the rectangle's left edge. Equivalent
        to left().


        \sa setX(), y(), topLeft()
    */

    /*!
        \fn qreal ZQRectF::y() const

        Returns the y-coordinate of the rectangle's top edge. Equivalent
        to top().

        \sa setY(), x(), topLeft()
    */

    /*!
        \fn qreal ZQRectF::angle() const

        Returns the angle of the rectangle in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQRectF::angleRadians() const

        Returns the angle of the rectangle in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */

    /*!
        \fn void ZQRectF::setLeft(qreal x)

        Sets the left edge of the rectangle to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the rectangle.

        Equivalent to setX().

        \sa left(), moveLeft()
    */

    /*!
        \fn void ZQRectF::setTop(qreal y)

        Sets the top edge of the rectangle to the given \a y coordinate. May
        change the height, but will never change the bottom edge of the
        rectangle.

        Equivalent to setY().

        \sa top(), moveTop()
    */

    /*!
        \fn void ZQRectF::setRight(qreal x)

        Sets the right edge of the rectangle to the given \a x
        coordinate. May change the width, but will never change the left
        edge of the rectangle.

        \sa right(), moveRight()
    */

    /*!
        \fn void ZQRectF::setBottom(qreal y)

        Sets the bottom edge of the rectangle to the given \a y
        coordinate. May change the height, but will never change the top
        edge of the rectangle.

        \sa bottom(), moveBottom()
    */

    /*!
        \fn void ZQRectF::setX(qreal x)

        Sets the left edge of the rectangle to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the rectangle.

        Equivalent to setLeft().

        \sa x(), setY(), setTopLeft()
    */

    /*!
        \fn void ZQRectF::setY(qreal y)

        Sets the top edge of the rectangle to the given \a y
        coordinate. May change the height, but will never change the
        bottom edge of the rectangle.

        Equivalent to setTop().

        \sa y(), setX(), setTopLeft()
    */

    /*!
        \fn void ZQRectF::setAngle(int angle)

        Sets the angle of the rectangle to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQRectF::setAngleRadians(qreal angle)

        Sets the angle of the rectangle to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */


    /*!
        \fn void ZQRectF::setTopLeft(const QPointF &position)

        Set the top-left corner of the rectangle to the given \a
        position. May change the size, but will never change the
        bottom-right corner of the rectangle.

        \sa topLeft(), moveTopLeft()
    */

    /*!
        \fn void ZQRectF::setBottomRight(const QPointF &position)

        Set the bottom-right corner of the rectangle to the given \a
        position. May change the size, but will never change the
        top-left corner of the rectangle.

        \sa bottomRight(), moveBottomRight()
    */

    /*!
        \fn void ZQRectF::setTopRight(const QPointF &position)

        Set the top-right corner of the rectangle to the given \a
        position. May change the size, but will never change the
        bottom-left corner of the rectangle.

        \sa topRight(), moveTopRight()
    */

    /*!
        \fn void ZQRectF::setBottomLeft(const QPointF &position)

        Set the bottom-left corner of the rectangle to the given \a
        position. May change the size, but will never change the
        top-right corner of the rectangle.

        \sa bottomLeft(), moveBottomLeft()
    */

    /*!
        \fn QPointF ZQRectF::center() const

        Returns the center point of the rectangle.

        \sa moveCenter()
    */


    /*!
        \fn void ZQRectF::getRect(qreal *x, qreal *y, qreal *width, qreal *height) const

        Extracts the position of the rectangle's top-left corner to *\a x and
        *\a y, and its dimensions to *\a width and *\a height.

        \sa setRect(), getCoords()
    */


    /*!
        \fn void ZQRectF::getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const

        Extracts the position of the rectangle's top-left corner to *\a x1
        and *\a y1, and the position of the bottom-right corner to *\a x2 and
        *\a y2.

        \sa setCoords(), getRect()
    */

    /*!
        \fn void ZQRectF::moveLeft(qreal x)

        Moves the rectangle horizontally, leaving the rectangle's left
        edge at the given \a x coordinate. The rectangle's size is
        unchanged.

        \sa left(), setLeft(), moveRight()
    */

    /*!
        \fn void ZQRectF::moveTop(qreal y)

        Moves the rectangle vertically, leaving the rectangle's top line
        at the given \a y coordinate. The rectangle's size is unchanged.

        \sa top(), setTop(), moveBottom()
    */


    /*!
        \fn void ZQRectF::moveRight(qreal x)

        Moves the rectangle horizontally, leaving the rectangle's right
        edge at the given \a x coordinate. The rectangle's size is
        unchanged.

        \sa right(), setRight(), moveLeft()
    */


    /*!
        \fn void ZQRectF::moveBottom(qreal y)

        Moves the rectangle vertically, leaving the rectangle's bottom
        edge at the given \a y coordinate. The rectangle's size is
        unchanged.

        \sa bottom(), setBottom(), moveTop()
    */


    /*!
        \fn void ZQRectF::moveTopLeft(const QPointF &position)

        Moves the rectangle, leaving the top-left corner at the given \a
        position. The rectangle's size is unchanged.

        \sa setTopLeft(), moveTop(), moveLeft()
    */


    /*!
        \fn void ZQRectF::moveBottomRight(const QPointF &position)

        Moves the rectangle, leaving the bottom-right corner at the given
        \a position. The rectangle's size is unchanged.

        \sa setBottomRight(), moveBottom(), moveRight()
    */


    /*!
        \fn void ZQRectF::moveTopRight(const QPointF &position)

        Moves the rectangle, leaving the top-right corner at the given
        \a position. The rectangle's size is unchanged.

        \sa setTopRight(), moveTop(), moveRight()
    */


    /*!
        \fn void ZQRectF::moveBottomLeft(const QPointF &position)

        Moves the rectangle, leaving the bottom-left corner at the given
        \a position. The rectangle's size is unchanged.

        \sa setBottomLeft(), moveBottom(), moveLeft()
    */


    /*!
        \fn void ZQRectF::moveTo(qreal x, qreal y)

        Moves the rectangle, leaving the top-left corner at the given
        position (\a x, \a y). The rectangle's size is unchanged.

        \sa translate(), moveTopLeft()
    */

    /*!
        \fn void ZQRectF::moveTo(const QPointF &position)
        \overload

        Moves the rectangle, leaving the top-left corner at the given \a
        position.
    */

    /*!
        \fn void ZQRectF::translate(qreal dx, qreal dy)

        Moves the rectangle \a dx along the x-axis and \a dy along the y-axis,
        relative to the current position. Positive values move the rectangle to the
        right and downwards.

        \sa moveTopLeft(), moveTo(), translated()
    */


    /*!
        \fn void ZQRectF::translate(const QPointF &offset)
        \overload

        Moves the rectangle \a{offset}.\l{QPointF::x()}{x()} along the x
        axis and \a{offset}.\l{QPointF::y()}{y()} along the y axis,
        relative to the current position.
    */


    /*!
        \fn ZQRectF ZQRectF::translated(qreal dx, qreal dy) const

        Returns a copy of the rectangle that is translated \a dx along the
        x axis and \a dy along the y axis, relative to the current
        position. Positive values move the rectangle to the right and
        down.

        \sa translate()
    */


    /*!
        \fn ZQRectF ZQRectF::translated(const QPointF &offset) const
        \overload

        Returns a copy of the rectangle that is translated
        \a{offset}.\l{QPointF::x()}{x()} along the x axis and
        \a{offset}.\l{QPointF::y()}{y()} along the y axis, relative to the
        current position.
    */

    /*!
        \fn ZQRectF ZQRectF::transposed() const
        \since 5.7

        Returns a copy of the rectangle that has its width and height
        exchanged:

        \snippet code/src_corelib_tools_qrect.cpp 3

        \sa QSizeF::transposed()
    */

    /*!
        \fn void ZQRectF::rotate(int da) const
        \since 5.7

        Rotates the rectangle by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQRectF::rotateRadians(qreal da) const
        \since 5.7

        Rotates the rectangle by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQRectF ZQEllipseF::rotated(int da) const
        \since 5.7

        Returns a copy of the rectangle rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQRectF ZQRectF::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the rectangle rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */


    /*!
        \fn void ZQRectF::normalizeAngle() const

        Normalizes the angle i.e. changes the angle to have a value between 0
        and 360 times a fixed number of rotations.

        \sa normalizedAngle()
    */

    /*!
        \fn int ZQRectF::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa normalizedAngle()
    */


    /*!
        \fn void ZQRectF::setRect(qreal x, qreal y, qreal width, qreal height)

        Sets the coordinates of the rectangle's top-left corner to (\a x,
        \a y), and its size to the given \a width and \a height.

        \sa getRect(), setCoords()
    */

    /*!
        \fn void ZQRectF::setCoords(qreal x1, qreal y1, qreal x2, qreal y2)

        Sets the coordinates of the rectangle's top-left corner to (\a x1,
        \a y1), and the coordinates of its bottom-right corner to (\a x2,
        \a y2).

        \sa getCoords(), setRect()
    */


    /*! \fn ZQRectF ZQRectF::adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2) const

        Returns a new rectangle with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this rectangle.
        The angle of the rectangle is not affected.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQRectF ZQRectF::adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Returns a new rectangle with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this rectangle, and
        \a angle in degrees added to the rectangle's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQRectF ZQRectF::adjustedRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Returns a new rectangle with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this rectangle, and
        \a angle in radians added to the rectangle's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */

    /*! \fn void ZQRectF::adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2)

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the rectangle. The angle of the rectangle
        is not affected.

        \sa adjusted(), adjustRadians(), adjustedRadians(), setRect()
    */

    /*! \fn void ZQRectF::adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the rectangle, and \a angle in degrees
        added to the rectangle's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn void ZQRectF::adjustRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the rectangle, and \a angle in radians
        added to the rectangle's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */



    /*!
        \fn QSizeF ZQRectF::size() const

        Returns the size of the rectangle.

        \sa setSize(), width(), height()
    */

    /*!
        \fn qreal ZQRectF::width() const

        Returns the width of the rectangle.

        \sa setWidth(), height(), size()
    */

    /*!
        \fn qreal ZQRectF::height() const

        Returns the height of the rectangle.

        \sa setHeight(), width(), size()
    */

    /*!
        \fn void ZQRectF::setWidth(qreal width)

        Sets the width of the rectangle to the given \a width. The right
        edge is changed, but not the left one.

        \sa width(), setSize()
    */


    /*!
        \fn void ZQRectF::setHeight(qreal height)

        Sets the height of the rectangle to the given \a height. The bottom
        edge is changed, but not the top one.

        \sa height(), setSize()
    */


    /*!
        \fn void ZQRectF::setSize(const QSizeF &size)

        Sets the size of the rectangle to the given \a size. The top-left
        corner is not moved.

        \sa size(), setWidth(), setHeight()
    */


    /*!
        \fn bool ZQRectF::contains(const QPointF &point) const

        Returns \c true if the given \a point is inside or on the edge of the
        rectangle; otherwise returns \c false.

        \sa intersects()
    */

    bool ZQRectF::contains(const QPointF &p, bool proper=false) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const ZQRectF first = normalized();
        const QPainterPath path1 = first.toPath();

        // FIXME proper=false is not honored because there isn't a way
        // to test if a point is on the edge.
        return path1.contains(p);
    }


    /*!
        \fn bool ZQRectF::contains(qreal x, qreal y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the rectangle; otherwise returns \c false.
    */

    /*!
        \fn bool ZQRectF::contains(const ZQRectF &rectangle) const
        \overload

        Returns \c true if the given \a rectangle is inside this rectangle;
        otherwise returns \c false.
    */

    bool ZQRectF::contains(const ZQRectF &r, bool proper=false) const noexcept
    {
        const ZQRectF first = normalized();
        const ZQRectF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        if (proper && path1 == path2) {
            return false;
        }
        return path1.contains(path2);
    }

    /*!
        \fn qreal ZQRectF::left() const

        Returns the x-coordinate of the rectangle's left edge. Equivalent
        to x().

        \sa setLeft(), topLeft(), bottomLeft()
    */

    /*!
        \fn qreal ZQRectF::top() const

        Returns the y-coordinate of the rectangle's top edge. Equivalent
        to y().

        \sa setTop(), topLeft(), topRight()
    */

    /*!
        \fn qreal ZQRectF::right() const

        Returns the x-coordinate of the rectangle's right edge.

        \sa setRight(), topRight(), bottomRight()
    */

    /*!
        \fn qreal ZQRectF::bottom() const

        Returns the y-coordinate of the rectangle's bottom edge.

        \sa setBottom(), bottomLeft(), bottomRight()
    */

    /*!
        \fn QPointF ZQRectF::topLeft() const

        Returns the position of the rectangle's top-left corner.

        \sa setTopLeft(), top(), left()
    */

    /*!
        \fn QPointF ZQRectF::bottomRight() const

        Returns the position of the rectangle's  bottom-right corner.

        \sa setBottomRight(), bottom(), right()
    */

    /*!
        \fn QPointF ZQRectF::topRight() const

        Returns the position of the rectangle's top-right corner.

        \sa setTopRight(), top(), right()
    */

    /*!
        \fn QPointF ZQRectF::bottomLeft() const

        Returns the position of the rectangle's  bottom-left corner.

        \sa setBottomLeft(), bottom(), left()
    */


    /*!
        \fn ZQRectF ZQRectF::operator|(const ZQRectF &rectangle) const

        Returns the bounding rectangle of this rectangle and the given \a rectangle.
        The result will always have an angle of 0 degrees.

        \sa united()
    */

    QPainterPath ZQRectF::operator|(const ZQRectF &r) const noexcept
    {
        if (isNull())
            return r;
        if (r.isNull())
            return *this;

        const ZQRectF first = normalized();
        const ZQRectF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.united(path2);
    }


    /*!
        \fn ZQRectF ZQRectF::united(const ZQRectF &rectangle) const
        \since 4.2

        Returns the bounding rectangle of this rectangle and the given \a
        rectangle. The result will always have an angle of 0 degrees.

        \image qrect-unite.png

        \sa intersected()
    */


    /*!
        \fn ZQRectF ZQRectF::operator&(const ZQRectF &rectangle) const

        Returns the intersection of this rectangle and the given \a
        rectangle. Returns an empty rectangle if there is no intersection.
        The angle of the intersected rectangle will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQRectF::operator&(const ZQRectF &r) const noexcept
    {
        const ZQRectF first = normalized();
        const ZQRectF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersected(path2);
    }


    /*!
        \fn QPainterPath ZQRectF::intersected(const ZQRectF &rectangle) const
        \since 4.2

        Returns the intersection of this rectangle and the given \a
        rectangle. Note that \c {r.intersected(s)} is equivalent to \c
        {r & s}.

        \image qrect-intersect.png

        \sa intersects(), united()
    */

    /*!
        \fn bool ZQRectF::intersects(const ZQRectF &rectangle) const

        Returns \c true if this rectangle intersects with the given \a
        rectangle (i.e. there is a non-empty area of overlap between
        them), otherwise returns \c false.

        The intersectio rectangle can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQRectF::intersects(const ZQRectF &r) const noexcept
    {

        const ZQRectF first = normalized();
        const ZQRectF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersects(path2);
    }

    /*!
        \fn ZQRect ZQRectF::toEllipse() const

        Returns a ZQRect based on the values of this rectangle.  Note that the
        coordinates in the returned rectangle are rounded to the nearest integer.

        \sa ZQRectF(), toAlignedEllipse()
    */

    /*!
        \fn ZQRect ZQRectF::toAlignedEllipse() const
        \since 4.3

        Returns a ZQRect based on the values of this rectangle that is the
        smallest possible integer rectangle that completely contains this
        rectangle.

        \sa toEllipse()
    */

    ZQRect ZQRectF::toAlignedEllipse() const noexcept
    {
        int xmin = int(qFloor(xp));
        int xmax = int(qCeil(xp + w));
        int ymin = int(qFloor(yp));
        int ymax = int(qCeil(yp + h));
        return ZQRect(xmin, ymin, xmax - xmin, ymax - ymin);
    }

    /*!
        \fn void ZQRectF::moveCenter(const QPointF &position)

        Moves the rectangle, leaving the center point at the given \a
        position. The rectangle's size is unchanged.

        \sa center()
    */

    /*!
        \fn bool operator==(const ZQRectF &r1, const ZQRectF &r2)
        \relates ZQRectF

        Returns \c true if the rectangles \a r1 and \a r2 are equal,
        otherwise returns \c false.
    */


    /*!
        \fn bool operator!=(const ZQRectF &r1, const ZQRectF &r2)
        \relates ZQRectF

        Returns \c true if the rectangles \a r1 and \a r2 are different, otherwise
        returns \c false.
    */

    /*!
        \fn ZQRectF operator+(const ZQRectF &lhs, const QMarginsF &rhs)
        \relates ZQRectF
        \since 5.3

        Returns the \a lhs rectangle grown by the \a rhs margins.
    */

    /*!
        \fn ZQRectF operator-(const ZQRectF &lhs, const QMarginsF &rhs)
        \relates ZQRectF
        \since 5.3

        Returns the \a lhs rectangle shrunk by the \a rhs margins.
    */

    /*!
        \fn ZQRectF operator+(const QMarginsF &lhs, const ZQRectF &rhs)
        \relates ZQRectF
        \overload
        \since 5.3

        Returns the \a lhs rectangle grown by the \a rhs margins.
    */

    /*!
        \fn ZQRectF ZQRectF::marginsAdded(const QMarginsF &margins) const
        \since 5.3

        Returns a rectangle grown by the \a margins.

        \sa operator+=(), marginsRemoved(), operator-=()
    */

    /*!
        \fn ZQRectF ZQRectF::marginsRemoved(const QMarginsF &margins) const
        \since 5.3

        Removes the \a margins from the rectangle, shrinking it.

        \sa marginsAdded(), operator+=(), operator-=()
    */

    /*!
        \fn ZQRectF ZQRectF::operator+=(const QMarginsF &margins)
        \since 5.3

        Adds the \a margins to the rectangle, growing it.

        \sa marginsAdded(), marginsRemoved(), operator-=()
    */

    /*!
        \fn ZQRectF ZQRectF::operator-=(const QMarginsF &margins)
        \since 5.3

        Returns a rectangle shrunk by the \a margins.

        \sa marginsRemoved(), operator+=(), marginsAdded()
    */

    /*!
        \fn QPainterPath ZQRectF::toPath()

        Converts the rectangle into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQRectF::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the rectangle about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    /*!
        \fn QString ZQRectF::toString()

        Returns a printable string of the rectangle.
    */

    constexpr QPainterPath ZQRectF::toPath() const noexcept
    {
        QPainterPath path;
        QPointF c1 = topRight();
        QPointF c2 = bottomRight();
        QPointF c3 = bottomLeft();
        QPointF c4 = topLeft();
        QPointF cn = center();

        QPointF c1a, c2a, c3a, c4a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(first.angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;

        path.moveTo(c1a);
        path.lineTo(c2a);
        path.lineTo(c3a);
        path.lineTo(c4a);
        path.lineTo(c1a);
        path.closeSubpath();
        return path;
    }

    constexpr QPainterPath ZQRectF::toPath(const QMatrix3x3 &mat, const QPointF& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = topRight();
        QPointF c2 = bottomRight();
        QPointF c3 = bottomLeft();
        QPointF c4 = topLeft();
        QPointF cn = center();

        QPointF c1a, c2a, c3a, c4a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(first.angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;

        QPointF c1r, c2r, c3r, c4r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        boost::geometry::transform(c3a - ref, c3r, project2D);
        boost::geometry::transform(c4a - ref, c4r, project2D);
        c1r += ref;
        c2r += ref;
        c3r += ref;
        c4r += ref;

        path.moveTo(c1r);
        path.lineTo(c2r);
        path.lineTo(c3r);
        path.lineTo(c4r);
        path.lineTo(c1r);
        path.closeSubpath();
        return path;
    }

    /*****************************************************************************
      ZQRectF stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQRectF &rectangle)

        \relates ZQRectF

        Writes the \a rectangle to the \a stream, and returns a reference to the
        stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQRectF &r)
    {
        s << double(r.x()) << double(r.y()) << double(r.width()) << double(r.height());
        return s;
    }

    /*!
        \fn QDataStream &operator>>(QDataStream &stream, ZQRectF &rectangle)

        \relates ZQRectF

        Reads a \a rectangle from the \a stream, and returns a reference to the
        stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQRectF &r)
    {
        double x, y, w, h, a;
        s >> x;
        s >> y;
        s >> w;
        s >> h;
        s >> a;
        r.setRect(qreal(x), qreal(y), qreal(w), qreal(h));
        return s;
    }

    #endif // QT_NO_DATASTREAM


    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQRectF &r)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << toString();
        return dbg;
    }
    #endif

}
