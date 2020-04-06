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

#include "z_qellipse.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/segment.hpp>
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(QPointF, qreal, boost::geometry::cs::cartesian, x, y, setX, setY);
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(QPoint, int, boost::geometry::cs::cartesian, x, y, setX, setY);
BOOST_GEOMETRY_REGISTER_SEGMENT(QLineF, QPointF, p1, p2);


namespace z_qtshapes {

    /*!
        \class ZQEllipse
        \inmodule Zgeometry
        \ingroup painting
        \reentrant

        \brief The ZQEllipse class defines an ellipse in the plane using
        integer precision.

        An ellipse is normally expressed as a top-left corner and a
        size.  The size (width and height) of a ZQEllipse is always equivalent
        to the mathematical ellipse that forms the basis for its
        rendering.

        A ZQEllipse can be constructed with a set of left, top, width and
        height integers, or from a QPoint and a QSize.  The following code
        creates two identical ellipses.

        \snippet code/src_corelib_tools_qEllipse.cpp 0

        There is a third constructor that creates a ZQEllipse using the
        top-left and bottom-right coordinates, but we recommend that you
        avoid using it. The rationale is that for historical reasons the
        values returned by the bottom() and right() functions deviate from
        the true bottom-right corner of the ellipse.

        The ZQEllipse class provides a collection of functions that return the
        various ellipse coordinates, and enable manipulation of
        these. ZQEllipse also provides functions to move the ellipse relative
        to the various coordinates. In addition there is a moveTo()
        function that moves the ellipse, leaving its top left corner at
        the given coordinates. Alternatively, the translate() function
        moves the ellipse the given offset relative to the current
        position, and the translated() function returns a translated copy
        of this ellipse.

        The size() function returns the Ellipseange's dimensions as a
        QSize. The dimensions can also be retrieved separately using the
        width() and height() functions. To manipulate the dimensions use
        the setSize(), setWidth() or setHeight() functions. Alternatively,
        the size can be changed by applying either of the functions
        setting the ellipse coordinates, for example, setBottom() or
        setRight().

        The contains() function tells whether a given point is inside the
        ellipse or not, and the intersects() function returns \c true if
        this ellipse intersects with a given ellipse. The ZQEllipse class
        also provides the intersected() function which returns the
        intersection ellipse, and the united() function which returns the
        ellipse that encloses the given ellipse and this:

        \table
        \row
        \li \inlineimage qEllipse-intersect.png
        \li \inlineimage qEllipse-unite.png
        \row
        \li intersected()
        \li united()
        \endtable

        The isEmpty() function returns \c true if left() > right() or top() >
        bottom(). Note that an empty ellipse is not valid: The isValid()
        function returns \c true if left() <= right() \e and top() <=
        bottom(). A null ellipse (isNull() == true) on the other hand,
        has both width and height set to 0.

        Note that due to the way ZQEllipse and ZQEllipseF are defined, an
        empty ZQEllipse is defined in essentially the same way as ZQEllipseF.

        Finally, ZQEllipse objects can be streamed as well as compared.

        \tableofcontents

        \section1 Rendering

        When using an \l {QPainter::Antialiasing}{anti-aliased} painter,
        the boundary line of a ZQEllipse will be rendered symmetrically on
        both sides of the mathematical ellipse's boundary line. But when
        using an aliased painter (the default) other rules apply.

        Then, when rendering with a one pixel wide pen the ZQEllipse's boundary
        line will be rendered to the right and below the mathematical
        ellipse's boundary line.

        When rendering with a two pixels wide pen the boundary line will
        be split in the middle by the mathematical ellipse. This will be
        the case whenever the pen is set to an even number of pixels,
        while rendering with a pen with an odd number of pixels, the spare
        pixel will be rendered to the right and below the mathematical
        ellipse as in the one pixel case.

        \table
        \row
            \li \inlineimage qEllipse-diagram-zero.png
            \li \inlineimage qEllipse-diagram-one.png
        \row
            \li Logical representation
            \li One pixel wide pen
        \row
            \li \inlineimage qEllipse-diagram-two.png
            \li \inlineimage qEllipse-diagram-three.png
        \row
            \li Two pixel wide pen
            \li Three pixel wide pen
        \endtable

        \section1 Coordinates

        The ZQEllipse class provides a collection of functions that return the
        various ellipse coordinates, and enable manipulation of
        these. ZQEllipse also provides functions to move the ellipse relative
        to the various coordinates.

        For example the left(), setLeft() and moveLeft() functions as an
        example: left() returns the x-coordinate of the ellipse's left
        edge, setLeft() sets the left edge of the ellipse to the given x
        coordinate (it may change the width, but will never change the
        ellipse's right edge) and moveLeft() moves the entire ellipse
        horizontally, leaving the ellipse's left edge at the given x
        coordinate and its size unchanged.

        \image qEllipse-coordinates.png

        Note that for historical reasons the values returned by the
        bottom() and right() functions deviate from the true bottom-right
        corner of the ellipse: The right() function returns \e { left()
        + width() - 1} and the bottom() function returns \e {top() +
        height() - 1}. The same is the case for the point returned by the
        bottomRight() convenience function. In addition, the x and y
        coordinate of the topRight() and bottomLeft() functions,
        respectively, contain the same deviation from the true right and
        bottom edges.

        We recommend that you use x() + width() and y() + height() to find
        the true bottom-right corner, and avoid right() and
        bottom(). Another solution is to use ZQEllipseF: The ZQEllipseF class
        defines an ellipse in the plane using floating point accuracy for
        coordinates, and the ZQEllipseF::right() and ZQEllipseF::bottom()
        functions \e do return the right and bottom coordinates.

        It is also possible to add offsets to this ellipse's coordinates
        using the adjust() function, as well as retrieve a new ellipse
        based on adjustments of the original one using the adjusted()
        function. If either of the width and height is negative, use the
        normalized() function to retrieve an ellipse where the corners
        are swapped.

        In addition, ZQEllipse provides the getCoords() function which extracts
        the position of the ellipse's top-left and bottom-right corner,
        and the getEllipse() function which extracts the ellipse's top-left
        corner, width and height. Use the setCoords() and setEllipse()
        function to manipulate the ellipse's coordinates and dimensions
        in one go.

        \section1 Constraints

        ZQEllipse is limited to the minimum and maximum values for the \c int type.
        Operations on a ZQEllipse that could potentially result in values outside this
        range will result in undefined behavior.

        \sa ZQEllipseF, QRegion
    */

    /*****************************************************************************
      ZQEllipse member functions
     *****************************************************************************/

    /*!
        \fn ZQEllipse::ZQEllipse()

        Constructs a null ellipse.

        \sa isNull()
    */

    /*!
        \fn ZQEllipse::ZQEllipse(const QPoint &topLeft, const QPoint &bottomRight)

        Constructs an ellipse with the given \a topLeft and \a bottomRight corners.

        \sa setTopLeft(), setBottomRight()
    */

    /*!
        \fn ZQEllipse::ZQEllipse(const QPoint &topleft, const QPoint &bottomright, int angle)

        Constructs an ellipse with the given \a topLeft and \a bottomRight corners,
        with an \a angle in degrees.

        \sa setTopLeft(), setBottomRight()
    */

    /*!
        \fn ZQEllipse::ZQEllipse(const QPoint &topLeft, const QSize &size)

        Constructs an ellipse with the given \a topLeft corner and the
        given \a size.

        \sa setTopLeft(), setSize()
    */

    /*!
        \fn ZQEllipse::ZQEllipse(const QPoint &topLeft, const QSize &size, int angle)

        Constructs an ellipse with the given \a topLeft corner and the
        given \a size, with an \a angle in degrees.

        \sa setTopLeft(), setSize()
    */

    /*!
        \fn ZQEllipse::ZQEllipse(int x, int y, int width, int height)

        Constructs an ellipse with (\a x, \a y) as its top-left corner
        and the given \a width and \a height.

        \sa setEllipse()
    */

    /*!
        \fn ZQEllipse::ZQEllipse(int left, int top, int width, int height, int angle)

        Constructs an ellipse with (\a x, \a y) as its top-left corner
        and the given \a width and \a height, with an \a angle in degrees.

        \sa setEllipse()
    */

    /*!
        \fn bool ZQEllipse::isNull() const

        Returns \c true if the ellipse is a null ellipse, otherwise
        returns \c false.

        A null ellipse has both the width and the height set to 0 (i.e.,
        right() == left() - 1 and bottom() == top() - 1). A null ellipse
        is also empty, and hence is not valid.

        \sa isEmpty(), isValid()
    */

    /*!
        \fn bool ZQEllipse::isEmpty() const

        Returns \c true if the ellipse is empty, otherwise returns \c false.

        An empty ellipse has a left() > right() or top() > bottom(). An
        empty ellipse is not valid (i.e., isEmpty() == !isValid()).

        Use the normalized() function to retrieve an ellipse where the
        corners are swapped.

        \sa isNull(), isValid(), normalized()
    */

    /*!
        \fn bool ZQEllipse::isValid() const

        Returns \c true if the ellipse is valid, otherwise returns \c false.

        A valid ellipse has a left() <= right() and top() <=
        bottom(). Note that non-trivial operations like intersections are
        not defined for invalid ellipses. A valid ellipse is not empty
        (i.e., isValid() == !isEmpty()).

        \sa isNull(), isEmpty(), normalized()
    */

    /*!
        Normalizes the ellipse; i.e., changes the ellipse to have a
        non-negative width and height.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    void ZQEllipse::normalize() noexcept
    {
        int temp;
        if (x2 < x1) {
            temp = x2;
            x2 = x1;
            x1 = temp;
        }
        if (y2 < y1) {
            temp = y2;
            y2 = y1;
            y1 = temp;
        }
    }


    /*!
        Returns a normalized ellipse; i.e., an ellipse that has a
        non-negative width and height, and an angle with an absolute size
        no greater than a predefined number of full rotations in degrees.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    ZQEllipse ZQEllipse::normalized() const noexcept
    {
        ZQEllipse r = *this;
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
        \fn int ZQEllipse::left() const

        Returns the x-coordinate of the ellipse's left edge. Equivalent
        to x().

        \sa setLeft(), topLeft(), bottomLeft()
    */

    /*!
        \fn int ZQEllipse::top() const

        Returns the y-coordinate of the ellipse's top edge.
        Equivalent to y().

        \sa setTop(), topLeft(), topRight()
    */

    /*!
        \fn int ZQEllipse::right() const

        Returns the x-coordinate of the ellipse's right edge.

        Note that for historical reasons this function returns left() +
        width() - 1; use x() + width() to retrieve the true x-coordinate.

        \sa setRight(), topRight(), bottomRight()
    */

    /*!
        \fn int ZQEllipse::bottom() const

        Returns the y-coordinate of the ellipse's bottom edge.

        Note that for historical reasons this function returns top() +
        height() - 1; use y() + height() to retrieve the true y-coordinate.

        \sa setBottom(), bottomLeft(), bottomRight()
    */

    /*!
        \fn int ZQEllipse::x() const

        Returns the x-coordinate of the ellipse's left edge. Equivalent to left().

        \sa setX(), y(), topLeft()
    */

    /*!
        \fn int ZQEllipse::y() const

        Returns the y-coordinate of the ellipse's top edge. Equivalent to top().

        \sa setY(), x(), topLeft()
    */

    /*!
        \fn int ZQEllipse::angle() const

        Returns the angle of the ellipse in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQEllipse::angleRadians() const

        Returns the angle of the ellipse in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */

    /*!
        \fn void ZQEllipse::setLeft(int x)

        Sets the left edge of the ellipse to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the ellipse.

        Equivalent to setX().

        \sa left(), moveLeft()
    */

    /*!
        \fn void ZQEllipse::setTop(int y)

        Sets the top edge of the ellipse to the given \a y
        coordinate. May change the height, but will never change the
        bottom edge of the ellipse.

        Equivalent to setY().

        \sa top(), moveTop()
    */

    /*!
        \fn void ZQEllipse::setRight(int x)

        Sets the right edge of the ellipse to the given \a x
        coordinate. May change the width, but will never change the left
        edge of the ellipse.

        \sa right(), moveRight()
    */

    /*!
        \fn void ZQEllipse::setBottom(int y)

        Sets the bottom edge of the ellipse to the given \a y
        coordinate. May change the height, but will never change the top
        edge of the ellipse.

        \sa bottom(), moveBottom(),
    */

    /*!
        \fn void ZQEllipse::setX(int x)

        Sets the left edge of the ellipse to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the ellipse.

        Equivalent to setLeft().

        \sa x(), setY(), setTopLeft()
    */

    /*!
        \fn void ZQEllipse::setY(int y)

        Sets the top edge of the ellipse to the given \a y
        coordinate. May change the height, but will never change the
        bottom edge of the ellipse.

        Equivalent to setTop().

        \sa y(), setX(), setTopLeft()
    */

    /*!
        \fn void ZQEllipse::setAngle(int angle)

        Sets the angle of the ellipse to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQEllipse::setAngleRadians(int angle)

        Sets the angle of the ellipse to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */

    /*!
        \fn void ZQEllipse::setTopLeft(const QPoint &position)

        Set the top-left corner of the ellipse to the given \a
        position. May change the size, but will never change the
        bottom-right corner of the ellipse.

        \sa topLeft(), moveTopLeft()
    */

    /*!
        \fn void ZQEllipse::setBottomRight(const QPoint &position)

        Set the bottom-right corner of the ellipse to the given \a
        position. May change the size, but will never change the
        top-left corner of the ellipse.

        \sa bottomRight(), moveBottomRight()
    */

    /*!
        \fn void ZQEllipse::setTopRight(const QPoint &position)

        Set the top-right corner of the ellipse to the given \a
        position. May change the size, but will never change the
        bottom-left corner of the ellipse.

        \sa topRight(), moveTopRight()
    */

    /*!
        \fn void ZQEllipse::setBottomLeft(const QPoint &position)

        Set the bottom-left corner of the ellipse to the given \a
        position. May change the size, but will never change the
        top-right corner of the ellipse.

        \sa bottomLeft(), moveBottomLeft()
    */

    /*!
        \fn QPoint ZQEllipse::topLeft() const

        Returns the position of the ellipse's top-left corner.

        \sa setTopLeft(), top(), left()
    */

    /*!
        \fn QPoint ZQEllipse::bottomRight() const

        Returns the position of the ellipse's bottom-right corner.

        Note that for historical reasons this function returns
        QPoint(left() + width() -1, top() + height() - 1).

        \sa setBottomRight(), bottom(), right()
    */

    /*!
        \fn QPoint ZQEllipse::topRight() const

        Returns the position of the ellipse's top-right corner.

        Note that for historical reasons this function returns
        QPoint(left() + width() -1, top()).

        \sa setTopRight(), top(), right()
    */

    /*!
        \fn QPoint ZQEllipse::bottomLeft() const

        Returns the position of the ellipse's bottom-left corner. Note
        that for historical reasons this function returns QPoint(left(),
        top() + height() - 1).

        \sa setBottomLeft(), bottom(), left()
    */

    /*!
        \fn QPoint ZQEllipse::center() const

        Returns the center point of the ellipse.

        \sa moveCenter()
    */


    /*!
        \fn void ZQEllipse::getEllipse(int *x, int *y, int *width, int *height) const

        Extracts the position of the ellipse's top-left corner to *\a x
        and *\a y, and its dimensions to *\a width and *\a height.

        \sa setEllipse(), getCoords()
    */

    /*!
        \fn void ZQEllipse::getEllipse(int *x, int *y, int *width, int *height, int *angle) const

        Extracts the position of the ellipse's top-left corner to *\a x
        and *\a y, its dimensions to *\a width and *\a height, and its angle to *\a angle in degrees.

        \sa setEllipse(), getCoords()
    */

    /*!
        \fn void ZQEllipse::getEllipseRadians(int *x, int *y, int *width, int *height, qreal *angle) const

        Extracts the position of the ellipse's top-left corner to *\a x
        and *\a y, its dimensions to *\a width and *\a height, and its angle to *\a angle in radians.

        \sa setEllipseRadians(), getCoordsRadians()
    */

    /*!
        \fn void ZQEllipse::getCoords(int *x1, int *y1, int *x2, int *y2) const

        Extracts the position of the ellipse's top-left corner to *\a x1
        and *\a y1, and the position of the bottom-right corner to *\a x2
        and *\a y2.

        \sa setCoords(), getEllipse()
    */

    /*!
        \fn void ZQEllipse::getCoords(int *x1, int *y1, int *x2, int *y2, int *angle) const

        Extracts the position of the ellipse's top-left corner to *\a x1
        and *\a y1, the position of the bottom-right corner to *\a x2
        and *\a y2 and the angle to *\a angle in degrees.

        \sa setCoords(), getEllipse()
    */

    /*!
        \fn void ZQEllipse::getCoordsRadians(int *x1, int *y1, int *x2, int *y2, qreal *angle) const

        Extracts the position of the ellipse's top-left corner to *\a x1
        and *\a y1, the position of the bottom-right corner to *\a x2
        and *\a y2 and the angle to *\a angle in radians.

        \sa setCoordsRadians(), getEllipseRadians()
    */


    /*!
        \fn void ZQEllipse::moveLeft(int x)

        Moves the ellipse horizontally, leaving the ellipse's left
        edge at the given \a x coordinate. The ellipse's size is
        unchanged.

        \sa left(), setLeft(), moveRight()
    */

    /*!
        \fn void ZQEllipse::moveTop(int y)

        Moves the ellipse vertically, leaving the ellipse's top edge
        at the given \a y coordinate. The ellipse's size is unchanged.

        \sa top(), setTop(), moveBottom()
    */


    /*!
        \fn void ZQEllipse::moveRight(int x)

        Moves the ellipse horizontally, leaving the ellipse's right
        edge at the given \a x coordinate. The ellipse's size is
        unchanged.

        \sa right(), setRight(), moveLeft()
    */


    /*!
        \fn void ZQEllipse::moveBottom(int y)

        Moves the ellipse vertically, leaving the ellipse's bottom
        edge at the given \a y coordinate. The ellipse's size is
        unchanged.

        \sa bottom(), setBottom(), moveTop()
    */


    /*!
        \fn void ZQEllipse::moveTopLeft(const QPoint &position)

        Moves the ellipse, leaving the top-left corner at the given \a
        position. The ellipse's size is unchanged.

        \sa setTopLeft(), moveTop(), moveLeft()
    */


    /*!
        \fn void ZQEllipse::moveBottomRight(const QPoint &position)

        Moves the ellipse, leaving the bottom-right corner at the given
        \a position. The ellipse's size is unchanged.

        \sa setBottomRight(), moveRight(), moveBottom()
    */


    /*!
        \fn void ZQEllipse::moveTopRight(const QPoint &position)

        Moves the ellipse, leaving the top-right corner at the given \a
        position. The ellipse's size is unchanged.

        \sa setTopRight(), moveTop(), moveRight()
    */


    /*!
        \fn void ZQEllipse::moveBottomLeft(const QPoint &position)

        Moves the ellipse, leaving the bottom-left corner at the given
        \a position. The ellipse's size is unchanged.

        \sa setBottomLeft(), moveBottom(), moveLeft()
    */


    /*!
        \fn void ZQEllipse::moveCenter(const QPoint &position)

        Moves the ellipse, leaving the center point at the given \a
        position. The ellipse's size is unchanged.

        \sa center()
    */

    /*!
        \fn void ZQEllipse::moveTo(int x, int y)

        Moves the ellipse, leaving the top-left corner at the given
        position (\a x, \a y).  The ellipse's size is unchanged.

        \sa translate(), moveTopLeft()
    */

    /*!
        \fn void ZQEllipse::moveTo(const QPoint &position)

        Moves the ellipse, leaving the top-left corner at the given \a
        position.
    */

    /*!
        \fn void ZQEllipse::translate(int dx, int dy)

        Moves the ellipse \a dx along the x axis and \a dy along the y
        axis, relative to the current position. Positive values move the
        ellipse to the right and down.

        \sa moveTopLeft(), moveTo(), translated()
    */


    /*!
        \fn void ZQEllipse::translate(const QPoint &offset)
        \overload

        Moves the ellipse \a{offset}.\l{QPoint::x()}{x()} along the x
        axis and \a{offset}.\l{QPoint::y()}{y()} along the y axis,
        relative to the current position.
    */


    /*!
        \fn ZQEllipse ZQEllipse::translated(int dx, int dy) const

        Returns a copy of the ellipse that is translated \a dx along the
        x axis and \a dy along the y axis, relative to the current
        position. Positive values move the ellipse to the right and
        down.

        \sa translate()

    */


    /*!
        \fn ZQEllipse ZQEllipse::translated(const QPoint &offset) const

        \overload

        Returns a copy of the ellipse that is translated
        \a{offset}.\l{QPoint::x()}{x()} along the x axis and
        \a{offset}.\l{QPoint::y()}{y()} along the y axis, relative to the
        current position.
    */

    /*!
        \fn ZQEllipse ZQEllipse::transposed() const
        \since 5.7

        Returns a copy of the ellipse that has its width and height
        exchanged:

        \snippet code/src_corelib_tools_qEllipse.cpp 2

        \sa QSize::transposed()
    */

    /*!
        \fn void ZQEllipse::rotate(int da) const
        \since 5.7

        Rotates the ellipse by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQEllipse::rotateRadians(qreal da) const
        \since 5.7

        Rotates the ellipse by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQEllipse ZQEllipse::rotated(int da) const
        \since 5.7

        Returns a copy of the ellipse rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQEllipse ZQEllipse::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the ellipse rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */

    /*!
        \fn int ZQEllipse::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa angle()
    */

    /*!
        \fn void ZQEllipse::setEllipse(int x, int y, int width, int height)

        Sets the coordinates of the ellipse's top-left corner to (\a{x},
        \a{y}), and its size to the given \a width and \a height.

        \sa getEllipse(), setCoords()
    */

    /*!
        \fn void ZQEllipse::setEllipse(int x, int y, int width, int height, int angle)

        Sets the coordinates of the ellipse's top-left corner to (\a{x},
        \a{y}), its size to the given \a width and \a height, and its angle to \a angle in degrees.

        \sa getEllipse(), setCoords()
    */

    /*!
        \fn void ZQEllipse::setEllipseRadians(int x, int y, int width, int height, qreal angle)

        Sets the coordinates of the ellipse's top-left corner to (\a{x},
        \a{y}), its size to the given \a width and \a height, and its angle to \a angle in radians.

        \sa getEllipseRadians(), setCoordsRadians()
    */

    /*!
        \fn void ZQEllipse::setCoords(int x1, int y1, int x2, int y2)

        Sets the coordinates of the ellipse's top-left corner to (\a x1,
        \a y1), and the coordinates of its bottom-right corner to (\a x2,
        \a y2).

        \sa getCoords(), setEllipse()
    */

    /*!
        \fn void ZQEllipse::setCoords(int x1, int y1, int x2, int y2, int angle)

        Sets the coordinates of the ellipse's top-left corner to (\a x1,
        \a y1), the coordinates of its bottom-right corner to (\a x2,
        \a y2), and the angle to \a angle in degrees.

        \sa getCoords(), setEllipse()
    */

    /*!
        \fn void ZQEllipse::setCoordsRadians(int x1, int y1, int x2, int y2, qreal angle)

        Sets the coordinates of the ellipse's top-left corner to (\a x1,
        \a y1), the coordinates of its bottom-right corner to (\a x2,
        \a y2), and the angle to \a angle in radians.

        \sa getCoordsRadians(), setEllipseRadians()
    */


    /*! \fn ZQEllipse ZQEllipse::adjusted(int dx1, int dy1, int dx2, int dy2) const

        Returns a new ellipse with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this ellipse.
        The angle of the ellipse is not affected.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQEllipse ZQEllipse::adjusted(int dx1, int dy1, int dx2, int dy2, int angle) const

        Returns a new ellipse with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this ellipse, and
        \a angle in degrees added to the ellipse's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQEllipse ZQEllipse::adjustedRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) const

        Returns a new ellipse with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this ellipse, and
        \a angle in radians added to the ellipse's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */

    /*! \fn void ZQEllipse::adjust(int dx1, int dy1, int dx2, int dy2)

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the ellipse. The angle of the ellipse
        is not affected.

        \sa adjusted(), adjustRadians(), adjustedRadians(), setEllipse()
    */

    /*! \fn void ZQEllipse::adjust(int dx1, int dy1, int dx2, int dy2, int angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing ellipse of the ellipse, and \a angle in degrees
        added to the ellipse's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn void ZQEllipse::adjustRadians(int dx1, int dy1, int dx2, int dy2, qreal angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the ellipse, and \a angle in radians
        added to the ellipse's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */


    /*!
        \fn QSize ZQEllipse::size() const

        Returns the size of the ellipse.

        \sa setSize(), width(), height()
    */

    /*!
        \fn int ZQEllipse::width() const

        Returns the width of the ellipse.

        \sa setWidth(), height(), size()
    */

    /*!
        \fn int ZQEllipse::height() const

        Returns the height of the ellipse.

        \sa setHeight(), width(), size()
    */

    /*!
        \fn void ZQEllipse::setWidth(int width)

        Sets the width of the ellipse to the given \a width. The right
        edge is changed, but not the left one.

        \sa width(), setSize()
    */


    /*!
        \fn void ZQEllipse::setHeight(int height)

        Sets the height of the ellipse to the given \a height. The bottom
        edge is changed, but not the top one.

        \sa height(), setSize()
    */


    /*!
        \fn void ZQEllipse::setSize(const QSize &size)

        Sets the size of the ellipse to the given \a size. The top-left
        corner is not moved.

        \sa size(), setWidth(), setHeight()
    */


    /*!
        \fn bool ZQEllipse::contains(const QPoint &point, bool proper) const

        Returns \c true if the given \a point is inside or on the edge of
        the ellipse, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the given \a point is \e inside the
        ellipse (i.e., not on the edge).

        \sa intersects()
    */

    bool ZQEllipse::contains(const QPoint &p) const noexcept
    {
        if (isNull())
            return false;

        const ZQEllipse first = normalized();
        const QPainterPath path1 = first.toPath();

        return path1.contains(p);

    }


    /*!
        \fn bool ZQEllipse::contains(int x, int y, bool proper) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the ellipse, otherwise returns \c false. If \a proper is true, this
        function only returns \c true if the point is entirely inside the
        ellipse(not on the edge).
    */

    /*!
        \fn bool ZQEllipse::contains(int x, int y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside this ellipse,
        otherwise returns \c false.
    */

    /*!
        \fn bool ZQEllipse::contains(const ZQEllipse &ellipse, bool proper) const
        \overload

        Returns \c true if the given \an ellipse is inside this ellipse.
        otherwise returns \c false. If \a proper is true, this function only
        returns \c true if the \an ellipse is entirely inside this
        ellipse (not on the edge).
    */

    bool ZQEllipse::contains(const ZQEllipse &r, bool proper) const noexcept
    {
        if (isNull() || r.isNull())
            return false;

        const ZQEllipse first = normalized();
        const ZQEllipse second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        if (proper && path1 == path2) {
            return false;
        }
        return path1.contains(path2);
    }

    /*!
        \fn QPainterPath ZQEllipse::operator|(const ZQEllipse &ellipse) const

        Returns the bounding ellipse of this ellipse and the given \a
        ellipse. The result will always have an angle of 0 degrees.

        \sa united()
    */

    QPainterPath ZQEllipse::operator|(const ZQEllipse &r) const noexcept
    {
        if (isNull())
            return r.toPath();
        if (r.isNull())
            return toPath();

        const ZQEllipse first = normalized();
        const ZQEllipse second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.united(path2);
    }

    /*!
        \fn QPainterPath ZQEllipse::united(const ZQEllipse &ellipse) const
        \since 4.2

        Returns the bounding ellipse of this ellipse and the given \an ellipse.
        The result will always have an angle of 0 degrees.

        \image qEllipse-unite.png

        \sa intersected()
    */


    /*!
        \fn QPainterPath ZQEllipse::operator&(const ZQEllipse &ellipse) const

        Returns the intersection of this ellipse and the given \a
        ellipse. Returns an empty ellipse if there is no intersection.
        The angle of the intersected ellipse will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQEllipse::operator&(const ZQEllipse &r) const noexcept
    {
        const ZQEllipseF first = normalized();
        const ZQEllipseF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersected(path2);
    }


    /*!
        \fn QPainterPath ZQEllipse::intersected(const ZQEllipse &ellipse) const
        \since 4.2

        Returns the intersection of this ellipse and the given \a
        ellipse. Note that \c{r.intersected(s)} is equivalent to \c{r & s}.

        \image qEllipse-intersect.png

        \sa intersects(), united()
    */

    /*!
        \fn bool ZQEllipse::intersects(const ZQEllipse &ellipse) const

        Returns \c true if this ellipse intersects with the given \a
        ellipse (i.e., there is at least one pixel that is within both
        ellipses), otherwise returns \c false.

        The intersection ellipse can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQEllipse::intersects(const ZQEllipse &r) const noexcept
    {
        const ZQEllipse first = normalized();
        const ZQEllipse second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersects(path2);
    }

    /*!
        \fn bool operator==(const ZQEllipse &r1, const ZQEllipse &r2)
        \relates ZQEllipse

        Returns \c true if the ellipses \a r1 and \a r2 are equal,
        otherwise returns \c false.
    */


    /*!
        \fn bool operator!=(const ZQEllipse &r1, const ZQEllipse &r2)
        \relates ZQEllipse

        Returns \c true if the ellipses \a r1 and \a r2 are different, otherwise
        returns \c false.
    */

    /*!
        \fn ZQEllipse operator+(const ZQEllipse &ellipse, const QMargins &margins)
        \relates ZQEllipse

        Returns the \an ellipse grown by the \a margins.

        \since 5.1
    */

    /*!
        \fn ZQEllipse operator+(const QMargins &margins, const ZQEllipse &ellipse)
        \relates ZQEllipse
        \overload

        Returns the \an ellipse grown by the \a margins.

        \since 5.1
    */

    /*!
        \fn ZQEllipse operator-(const ZQEllipse &lhs, const QMargins &rhs)
        \relates ZQEllipse

        Returns the \a lhs ellipse shrunk by the \a rhs margins.

        \since 5.3
    */

    /*!
        \fn ZQEllipse ZQEllipse::marginsAdded(const QMargins &margins) const

        Returns an ellipse grown by the \a margins.

        \sa operator+=(), marginsRemoved(), operator-=()

        \since 5.1
    */

    /*!
        \fn ZQEllipse ZQEllipse::operator+=(const QMargins &margins)

        Adds the \a margins to the ellipse, growing it.

        \sa marginsAdded(), marginsRemoved(), operator-=()

        \since 5.1
    */

    /*!
        \fn ZQEllipse ZQEllipse::marginsRemoved(const QMargins &margins) const

        Removes the \a margins from the ellipse, shrinking it.

        \sa marginsAdded(), operator+=(), operator-=()

        \since 5.1
    */

    /*!
        \fn ZQEllipse ZQEllipse::operator -=(const QMargins &margins)

        Returns an ellipse shrunk by the \a margins.

        \sa marginsRemoved(), operator+=(), marginsAdded()

        \since 5.1
    */

    /*!
        \fn QPainterPath ZQEllipse::toPath()

        Converts the ellipse into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQEllipse::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the ellipse about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    /*!
        \fn QString ZQEllipse::toString()

        Returns a printable string of the ellipse.
    */

    QString ZQEllipse::toString() const noexcept
    {
        return QString("ZQEllipse(%1,%2 size %3x%4 %5 degrees)").arg(QString::number(x1), QString::number(y1),
                QString::number(width()), QString::number(height()), QString::number(a));
    }

    QPainterPath ZQEllipse::toPath() const noexcept
    {

        QPainterPath path;
        QPointF c1 = QPointF(center().x(), top());
        QPointF c2 = QPointF(center().x() + (right()-center().x())*4/3, top());
        QPointF c3 = QPointF(center().x() + (right()-center().x())*4/3, bottom());
        QPointF c4 = QPointF(center().x(), bottom());
        QPointF c5 = QPointF(center().x() - (center().x()-left())*4/3, bottom());
        QPointF c6 = QPointF(center().x() - (center().x()-left())*4/3, top());
        QPointF cn = center();

        QPointF c1a, c2a, c3a, c4a, c5a, c6a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        boost::geometry::transform(c5 - cn, c5a, rotate);
        boost::geometry::transform(c6 - cn, c6a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;
        c5a += cn;
        c6a += cn;

        path.moveTo(c1a);
        path.cubicTo(c2a, c3a, c4a);
        path.cubicTo(c5a, c6a, c1a);
        path.closeSubpath();

        return path;
    }

    QPainterPath ZQEllipse::toPath(const QMatrix3x3 &mat, const QPointF& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(center().x(), top());
        QPointF c2 = QPointF(center().x() + (right()-center().x())*4/3, top());
        QPointF c3 = QPointF(center().x() + (right()-center().x())*4/3, bottom());
        QPointF c4 = QPointF(center().x(), bottom());
        QPointF c5 = QPointF(center().x() - (center().x()-left())*4/3, bottom());
        QPointF c6 = QPointF(center().x() - (center().x()-left())*4/3, top());
        QPointF cn = center();

        QPointF c1a, c2a, c3a, c4a, c5a, c6a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        boost::geometry::transform(c5 - cn, c5a, rotate);
        boost::geometry::transform(c6 - cn, c6a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;
        c5a += cn;
        c6a += cn;

        QPointF c1r, c2r, c3r, c4r, c5r, c6r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        boost::geometry::transform(c3a - ref, c3r, project2D);
        boost::geometry::transform(c4a - ref, c4r, project2D);
        boost::geometry::transform(c5a - ref, c5r, project2D);
        boost::geometry::transform(c6a - ref, c6r, project2D);
        c1r += ref;
        c2r += ref;
        c3r += ref;
        c4r += ref;
        c5r += ref;
        c6r += ref;

        path.moveTo(c1r);
        path.cubicTo(c2r, c3r, c4r);
        path.cubicTo(c5r, c6r, c1r);
        path.closeSubpath();
        return path;
    }


    /*****************************************************************************
      ZQEllipse stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQEllipse &ellipse)
        \relates ZQEllipse

        Writes the given \an ellipse to the given \a stream, and returns
        a reference to the stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQEllipse &r)
    {
        s << (qint32)r.left() << (qint32)r.top()
          << (qint32)r.right() << (qint32)r.bottom() << (qint32)r.angle();
        return s;
    }

    /*!
        \fn QDataStream &operator>>(QDataStream &stream, ZQEllipse &ellipse)
        \relates ZQEllipse

        Reads an ellipse from the given \a stream into the given \a
        ellipse, and returns a reference to the stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQEllipse &r)
    {

        qint32 x1, y1, x2, y2, a;
        s >> x1; s >> y1; s >> x2; s >> y2; s >> a;
        r.setCoords(x1, y1, x2, y2);
        r.setAngle(a);
        return s;
    }

    #endif // QT_NO_DATASTREAM


    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQEllipse &r)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << r.toString();
        return dbg;
    }
    #endif

    /*!
        \class ZQEllipseF
        \inmodule Zgeometry
        \ingroup painting
        \reentrant

        \brief The ZQEllipseF class defines an ellipse in the plane using floating
        point precision.

        An ellipse is normally expressed as a top-left corner and a
        size.  The size (width and height) of a ZQEllipseF is always equivalent
        to the mathematical ellipse that forms the basis for its
        rendering.

        A ZQEllipseF can be constructed with a set of left, top, width and
        height coordinates, or from a QPointF and a QSizeF.  The following
        code creates two identical ellipses.

        \snippet code/src_corelib_tools_qEllipse.cpp 1

        There is also a third constructor creating a ZQEllipseF from a ZQEllipse,
        and a corresponding toEllipse() function that returns a ZQEllipse object
        based on the values of this ellipse (note that the coordinates
        in the returned ellipse are rounded to the nearest integer).

        The ZQEllipseF class provides a collection of functions that return
        the various ellipse coordinates, and enable manipulation of
        these. ZQEllipseF also provides functions to move the ellipse
        relative to the various coordinates. In addition there is a
        moveTo() function that moves the ellipse, leaving its top left
        corner at the given coordinates. Alternatively, the translate()
        function moves the ellipse the given offset relative to the
        current position, and the translated() function returns a
        translated copy of this ellipse.

        The size() function returns the Ellipseange's dimensions as a
        QSizeF. The dimensions can also be retrieved separately using the
        width() and height() functions. To manipulate the dimensions use
        the setSize(), setWidth() or setHeight() functions. Alternatively,
        the size can be changed by applying either of the functions
        setting the ellipse coordinates, for example, setBottom() or
        setRight().

        The contains() function tells whether a given point is inside the
        ellipse or not, and the intersects() function returns \c true if
        this ellipse intersects with a given ellipse (otherwise
        false). The ZQEllipseF class also provides the intersected() function
        which returns the intersection ellipse, and the united() function
        which returns the ellipse that encloses the given ellipse and
        this:

        \table
        \row
        \li \inlineimage qEllipse-intersect.png
        \li \inlineimage qEllipse-unite.png
        \row
        \li intersected()
        \li united()
        \endtable

        The isEmpty() function returns \c true if the ellipse's width or
        height is less than, or equal to, 0. Note that an empty ellipse
        is not valid: The isValid() function returns \c true if both width
        and height is larger than 0. A null ellipse (isNull() == true)
        on the other hand, has both width and height set to 0.

        Note that due to the way ZQEllipse and ZQEllipseF are defined, an
        empty ZQEllipseF is defined in essentially the same way as ZQEllipse.

        Finally, ZQEllipseF objects can be streamed as well as compared.

        \tableofcontents

        \section1 Rendering

        When using an \l {QPainter::Antialiasing}{anti-aliased} painter,
        the boundary line of a ZQEllipseF will be rendered symmetrically on both
        sides of the mathematical ellipse's boundary line. But when
        using an aliased painter (the default) other rules apply.

        Then, when rendering with a one pixel wide pen the ZQEllipseF's boundary
        line will be rendered to the right and below the mathematical
        ellipse's boundary line.

        When rendering with a two pixels wide pen the boundary line will
        be split in the middle by the mathematical ellipse. This will be
        the case whenever the pen is set to an even number of pixels,
        while rendering with a pen with an odd number of pixels, the spare
        pixel will be rendered to the right and below the mathematical
        ellipse as in the one pixel case.

        \table
        \row
            \li \inlineimage qEllipse-diagram-zero.png
            \li \inlineimage qEllipsef-diagram-one.png
        \row
            \li Logical representation
            \li One pixel wide pen
        \row
            \li \inlineimage qEllipsef-diagram-two.png
            \li \inlineimage qEllipsef-diagram-three.png
        \row
            \li Two pixel wide pen
            \li Three pixel wide pen
        \endtable

        \section1 Coordinates

        The ZQEllipseF class provides a collection of functions that return
        the various ellipse coordinates, and enable manipulation of
        these. ZQEllipseF also provides functions to move the ellipse
        relative to the various coordinates.

        For example: the bottom(), setBottom() and moveBottom() functions:
        bottom() returns the y-coordinate of the ellipse's bottom edge,
        setBottom() sets the bottom edge of the ellipse to the given y
        coordinate (it may change the height, but will never change the
        ellipse's top edge) and moveBottom() moves the entire ellipse
        vertically, leaving the ellipse's bottom edge at the given y
        coordinate and its size unchanged.

        \image qEllipsef-coordinates.png

        It is also possible to add offsets to this ellipse's coordinates
        using the adjust() function, as well as retrieve a new ellipse
        based on adjustments of the original one using the adjusted()
        function. If either of the width and height is negative, use the
        normalized() function to retrieve an ellipse where the corners
        are swapped.

        In addition, ZQEllipseF provides the getCoords() function which extracts
        the position of the ellipse's top-left and bottom-right corner,
        and the getEllipse() function which extracts the ellipse's top-left
        corner, width and height. Use the setCoords() and setEllipse()
        function to manipulate the ellipse's coordinates and dimensions
        in one go.

        \sa ZQEllipse, QRegion
    */

    /*****************************************************************************
      ZQEllipseF member functions
     *****************************************************************************/

    /*!
        \fn ZQEllipseF::ZQEllipseF()

        Constructs a null ellipse.

        \sa isNull()
    */

    /*!
        \fn ZQEllipseF::ZQEllipseF(const QPointF &topLeft, const QSizeF &size)

        Constructs an ellipse with the given \a topLeft corner and the given \a size.

        \sa setTopLeft(), setSize()
    */

    /*!
        \fn ZQEllipseF::ZQEllipseF(const QPointF &topLeft, const QPointF &bottomRight)
        \since 4.3

        Constructs an ellipse with the given \a topLeft and \a bottomRight corners.

        \sa setTopLeft(), setBottomRight()
    */

    /*!
        \fn ZQEllipseF::ZQEllipseF(qreal x, qreal y, qreal width, qreal height)

        Constructs an ellipse with (\a x, \a y) as its top-left corner
        and the given \a width and \a height.

        \sa setEllipse()
    */

    /*!
        \fn ZQEllipseF::ZQEllipseF(const ZQEllipse &ellipse)

        Constructs a ZQEllipseF ellipse from the given ZQEllipse \an ellipse.

        \sa toEllipse()
    */

    /*!
        \fn bool ZQEllipseF::isNull() const

        Returns \c true if the ellipse is a null ellipse, otherwise returns \c false.

        A null ellipse has both the width and the height set to 0. A
        null ellipse is also empty, and hence not valid.

        \sa isEmpty(), isValid()
    */

    /*!
        \fn bool ZQEllipseF::isEmpty() const

        Returns \c true if the ellipse is empty, otherwise returns \c false.

        An empty ellipse has width() <= 0 or height() <= 0.  An empty
        ellipse is not valid (i.e., isEmpty() == !isValid()).

        Use the normalized() function to retrieve an ellipse where the
        corners are swapped.

        \sa isNull(), isValid(), normalized()
    */

    /*!
        \fn bool ZQEllipseF::isValid() const

        Returns \c true if the ellipse is valid, otherwise returns \c false.

        A valid ellipse has a width() > 0 and height() > 0. Note that
        non-trivial operations like intersections are not defined for
        invalid ellipses. A valid ellipse is not empty (i.e., isValid()
        == !isEmpty()).

        \sa isNull(), isEmpty(), normalized()
    */


    /*!
        Normalizes the ellipse; i.e., changes the ellipse to have a
        non-negative width and height.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    void ZQEllipseF::normalize() noexcept
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
        Returns a normalized ellipse; i.e., an ellipse that has a
        non-negative width and height.

        If width() < 0 the function swaps the left and right corners, and
        it swaps the top and bottom corners if height() < 0.

        \sa isValid(), isEmpty()
    */

    ZQEllipseF ZQEllipseF::normalized() const noexcept
    {
        ZQEllipseF r = *this;
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
        \fn qreal ZQEllipseF::x() const

        Returns the x-coordinate of the ellipse's left edge. Equivalent
        to left().


        \sa setX(), y(), topLeft()
    */

    /*!
        \fn qreal ZQEllipseF::y() const

        Returns the y-coordinate of the ellipse's top edge. Equivalent
        to top().

        \sa setY(), x(), topLeft()
    */

    /*!
        \fn qreal ZQEllipseF::angle() const

        Returns the angle of the ellipse in degrees. The angle is normalized
        between a predefined number of full rotations in degrees.

        \sa angleRadians(), setAngle(), setAngleRadians()
    */

    /*!
        \fn qreal ZQEllipseF::angleRadians() const

        Returns the angle of the ellipse in radians. The angle is normalized
        between a predefined number of full rotations in radians.

        \sa angle(), setAngle(), setAngleRadians()
    */

    /*!
        \fn void ZQEllipseF::setLeft(qreal x)

        Sets the left edge of the ellipse to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the ellipse.

        Equivalent to setX().

        \sa left(), moveLeft()
    */

    /*!
        \fn void ZQEllipseF::setTop(qreal y)

        Sets the top edge of the ellipse to the given \a y coordinate. May
        change the height, but will never change the bottom edge of the
        ellipse.

        Equivalent to setY().

        \sa top(), moveTop()
    */

    /*!
        \fn void ZQEllipseF::setRight(qreal x)

        Sets the right edge of the ellipse to the given \a x
        coordinate. May change the width, but will never change the left
        edge of the ellipse.

        \sa right(), moveRight()
    */

    /*!
        \fn void ZQEllipseF::setBottom(qreal y)

        Sets the bottom edge of the ellipse to the given \a y
        coordinate. May change the height, but will never change the top
        edge of the ellipse.

        \sa bottom(), moveBottom()
    */

    /*!
        \fn void ZQEllipseF::setX(qreal x)

        Sets the left edge of the ellipse to the given \a x
        coordinate. May change the width, but will never change the right
        edge of the ellipse.

        Equivalent to setLeft().

        \sa x(), setY(), setTopLeft()
    */

    /*!
        \fn void ZQEllipseF::setY(qreal y)

        Sets the top edge of the ellipse to the given \a y
        coordinate. May change the height, but will never change the
        bottom edge of the ellipse.

        Equivalent to setTop().

        \sa y(), setX(), setTopLeft()
    */

    /*!
        \fn void ZQEllipseF::setAngle(int angle)

        Sets the angle of the ellipse to the given angle \a angle in degrees.

        \sa angle(), angleRadians(), setAngleRadians()
    */

    /*!
        \fn void ZQEllipseF::setAngleRadians(qreal angle)

        Sets the angle of the ellipse to the given angle \a angle in radians.

        \sa angle(), angleRadians(), setAngle()
    */


    /*!
        \fn void ZQEllipseF::setTopLeft(const QPointF &position)

        Set the top-left corner of the ellipse to the given \a
        position. May change the size, but will never change the
        bottom-right corner of the ellipse.

        \sa topLeft(), moveTopLeft()
    */

    /*!
        \fn void ZQEllipseF::setBottomRight(const QPointF &position)

        Set the bottom-right corner of the ellipse to the given \a
        position. May change the size, but will never change the
        top-left corner of the ellipse.

        \sa bottomRight(), moveBottomRight()
    */

    /*!
        \fn void ZQEllipseF::setTopRight(const QPointF &position)

        Set the top-right corner of the ellipse to the given \a
        position. May change the size, but will never change the
        bottom-left corner of the ellipse.

        \sa topRight(), moveTopRight()
    */

    /*!
        \fn void ZQEllipseF::setBottomLeft(const QPointF &position)

        Set the bottom-left corner of the ellipse to the given \a
        position. May change the size, but will never change the
        top-right corner of the ellipse.

        \sa bottomLeft(), moveBottomLeft()
    */

    /*!
        \fn QPointF ZQEllipseF::center() const

        Returns the center point of the ellipse.

        \sa moveCenter()
    */


    /*!
        \fn void ZQEllipseF::getEllipse(qreal *x, qreal *y, qreal *width, qreal *height) const

        Extracts the position of the ellipse's top-left corner to *\a x and
        *\a y, and its dimensions to *\a width and *\a height.

        \sa setEllipse(), getCoords()
    */


    /*!
        \fn void ZQEllipseF::getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const

        Extracts the position of the ellipse's top-left corner to *\a x1
        and *\a y1, and the position of the bottom-right corner to *\a x2 and
        *\a y2.

        \sa setCoords(), getEllipse()
    */

    /*!
        \fn void ZQEllipseF::moveLeft(qreal x)

        Moves the ellipse horizontally, leaving the ellipse's left
        edge at the given \a x coordinate. The ellipse's size is
        unchanged.

        \sa left(), setLeft(), moveRight()
    */

    /*!
        \fn void ZQEllipseF::moveTop(qreal y)

        Moves the ellipse vertically, leaving the ellipse's top line
        at the given \a y coordinate. The ellipse's size is unchanged.

        \sa top(), setTop(), moveBottom()
    */


    /*!
        \fn void ZQEllipseF::moveRight(qreal x)

        Moves the ellipse horizontally, leaving the ellipse's right
        edge at the given \a x coordinate. The ellipse's size is
        unchanged.

        \sa right(), setRight(), moveLeft()
    */


    /*!
        \fn void ZQEllipseF::moveBottom(qreal y)

        Moves the ellipse vertically, leaving the ellipse's bottom
        edge at the given \a y coordinate. The ellipse's size is
        unchanged.

        \sa bottom(), setBottom(), moveTop()
    */


    /*!
        \fn void ZQEllipseF::moveTopLeft(const QPointF &position)

        Moves the ellipse, leaving the top-left corner at the given \a
        position. The ellipse's size is unchanged.

        \sa setTopLeft(), moveTop(), moveLeft()
    */


    /*!
        \fn void ZQEllipseF::moveBottomRight(const QPointF &position)

        Moves the ellipse, leaving the bottom-right corner at the given
        \a position. The ellipse's size is unchanged.

        \sa setBottomRight(), moveBottom(), moveRight()
    */


    /*!
        \fn void ZQEllipseF::moveTopRight(const QPointF &position)

        Moves the ellipse, leaving the top-right corner at the given
        \a position. The ellipse's size is unchanged.

        \sa setTopRight(), moveTop(), moveRight()
    */


    /*!
        \fn void ZQEllipseF::moveBottomLeft(const QPointF &position)

        Moves the ellipse, leaving the bottom-left corner at the given
        \a position. The ellipse's size is unchanged.

        \sa setBottomLeft(), moveBottom(), moveLeft()
    */


    /*!
        \fn void ZQEllipseF::moveTo(qreal x, qreal y)

        Moves the ellipse, leaving the top-left corner at the given
        position (\a x, \a y). The ellipse's size is unchanged.

        \sa translate(), moveTopLeft()
    */

    /*!
        \fn void ZQEllipseF::moveTo(const QPointF &position)
        \overload

        Moves the ellipse, leaving the top-left corner at the given \a
        position.
    */

    /*!
        \fn void ZQEllipseF::translate(qreal dx, qreal dy)

        Moves the ellipse \a dx along the x-axis and \a dy along the y-axis,
        relative to the current position. Positive values move the ellipse to the
        right and downwards.

        \sa moveTopLeft(), moveTo(), translated()
    */


    /*!
        \fn void ZQEllipseF::translate(const QPointF &offset)
        \overload

        Moves the ellipse \a{offset}.\l{QPointF::x()}{x()} along the x
        axis and \a{offset}.\l{QPointF::y()}{y()} along the y axis,
        relative to the current position.
    */


    /*!
        \fn ZQEllipseF ZQEllipseF::translated(qreal dx, qreal dy) const

        Returns a copy of the ellipse that is translated \a dx along the
        x axis and \a dy along the y axis, relative to the current
        position. Positive values move the ellipse to the right and
        down.

        \sa translate()
    */


    /*!
        \fn ZQEllipseF ZQEllipseF::translated(const QPointF &offset) const
        \overload

        Returns a copy of the ellipse that is translated
        \a{offset}.\l{QPointF::x()}{x()} along the x axis and
        \a{offset}.\l{QPointF::y()}{y()} along the y axis, relative to the
        current position.
    */

    /*!
        \fn ZQEllipseF ZQEllipseF::transposed() const
        \since 5.7

        Returns a copy of the ellipse that has its width and height
        exchanged:

        \snippet code/src_corelib_tools_qEllipse.cpp 3

        \sa QSizeF::transposed()
    */

    /*!
        \fn void ZQEllipseF::rotate(int da) const
        \since 5.7

        Rotates the ellipse by \a da degrees clockwise.


        \sa rotateRadians(), rotated(), rotatedRadians()
    */

    /*!
        \fn void ZQEllipseF::rotateRadians(qreal da) const
        \since 5.7

        Rotates the ellipse by \a da radians clockwise.


        \sa rotate(), rotated(), rotatedRadians()
    */

    /*!
        \fn ZQEllipseF ZQEllipseF::rotated(int da) const
        \since 5.7

        Returns a copy of the ellipse rotated by \a da degrees clockwise.


        \sa rotate(), rotateRadians(), rotatedRadians()
    */

    /*!
        \fn ZQEllipseF ZQEllipseF::rotatedRadians(qreal da) const
        \since 5.7

        Returns a copy of the ellipse rotated by \a da radians clockwise.


        \sa rotate(), rotateRadians(), rotated()
    */

    /*!
        \fn qreal ZQEllipseF::normalizedAngle() const

        Returns a normalized angle i.e. changes the angle to have a value
        between 0 and 360 times a fixed number of rotations.

        \sa angle()
    */


    /*!
        \fn void ZQEllipseF::setEllipse(qreal x, qreal y, qreal width, qreal height)

        Sets the coordinates of the ellipse's top-left corner to (\a x,
        \a y), and its size to the given \a width and \a height.

        \sa getEllipse(), setCoords()
    */


    /*!
        \fn void ZQEllipseF::setCoords(qreal x1, qreal y1, qreal x2, qreal y2)

        Sets the coordinates of the ellipse's top-left corner to (\a x1,
        \a y1), and the coordinates of its bottom-right corner to (\a x2,
        \a y2).

        \sa getCoords(), setEllipse()
    */

    /*! \fn ZQEllipseF ZQEllipseF::adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2) const

        Returns a new ellipse with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this ellipse.
        The angle of the ellipse is not affected.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQEllipseF ZQEllipseF::adjusted(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Returns a new ellipse with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this ellipse, and
        \a angle in degrees added to the ellipse's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn ZQEllipseF ZQEllipseF::adjustedRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Returns a new ellipse with \a dx1, \a dy1, \a dx2 and \a dy2
        added respectively to the existing coordinates of this ellipse, and
        \a angle in radians added to the ellipse's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */

    /*! \fn void ZQEllipseF::adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2)

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the ellipse. The angle of the ellipse
        is not affected.

        \sa adjusted(), adjustRadians(), adjustedRadians(), setEllipse()
    */

    /*! \fn void ZQEllipseF::adjust(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing ellipse of the ellipse, and \a angle in degrees
        added to the ellipse's angle.

        \sa adjust(), adjustRadians(), adjustedRadians()
    */

    /*! \fn void ZQEllipseF::adjustRadians(qreal dx1, qreal dy1, qreal dx2, qreal dy2, qreal angle) const

        Adds \a dx1, \a dy1, \a dx2 and \a dy2 respectively to the
        existing coordinates of the ellipse, and \a angle in radians
        added to the ellipse's angle.

        \sa adjust(), adjusted(), adjustedRadians()
    */


    /*!
        \fn QSizeF ZQEllipseF::size() const

        Returns the size of the ellipse.

        \sa setSize(), width(), height()
    */

    /*!
        \fn qreal ZQEllipseF::width() const

        Returns the width of the ellipse.

        \sa setWidth(), height(), size()
    */

    /*!
        \fn qreal ZQEllipseF::height() const

        Returns the height of the ellipse.

        \sa setHeight(), width(), size()
    */

    /*!
        \fn void ZQEllipseF::setWidth(qreal width)

        Sets the width of the ellipse to the given \a width. The right
        edge is changed, but not the left one.

        \sa width(), setSize()
    */


    /*!
        \fn void ZQEllipseF::setHeight(qreal height)

        Sets the height of the ellipse to the given \a height. The bottom
        edge is changed, but not the top one.

        \sa height(), setSize()
    */


    /*!
        \fn void ZQEllipseF::setSize(const QSizeF &size)

        Sets the size of the ellipse to the given \a size. The top-left
        corner is not moved.

        \sa size(), setWidth(), setHeight()
    */


    /*!
        \fn bool ZQEllipseF::contains(const QPointF &point) const

        Returns \c true if the given \a point is inside or on the edge of the
        ellipse; otherwise returns \c false.

        \sa intersects()
    */

    bool ZQEllipseF::contains(const QPointF &p) const noexcept
    {
        if (isNull())
            return false;

        const ZQEllipseF first = normalized();
        const QPainterPath path1 = first.toPath();

        return path1.contains(p);

    }


    /*!
        \fn bool ZQEllipseF::contains(qreal x, qreal y) const
        \overload

        Returns \c true if the point (\a x, \a y) is inside or on the edge of
        the ellipse; otherwise returns \c false.
    */

    /*!
        \fn bool ZQEllipseF::contains(const ZQEllipseF &ellipse) const
        \overload

        Returns \c true if the given \an ellipse is inside this ellipse;
        otherwise returns \c false.
    */

    bool ZQEllipseF::contains(const ZQEllipseF &r, bool proper) const noexcept
    {
        const ZQEllipseF first = normalized();
        const ZQEllipseF second = r.normalized();
        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        if (proper && path1 == path2) {
            return false;
        }
        return path1.contains(path2);
    }

    /*!
        \fn qreal ZQEllipseF::left() const

        Returns the x-coordinate of the ellipse's left edge. Equivalent
        to x().

        \sa setLeft(), topLeft(), bottomLeft()
    */

    /*!
        \fn qreal ZQEllipseF::top() const

        Returns the y-coordinate of the ellipse's top edge. Equivalent
        to y().

        \sa setTop(), topLeft(), topRight()
    */

    /*!
        \fn qreal ZQEllipseF::right() const

        Returns the x-coordinate of the ellipse's right edge.

        \sa setRight(), topRight(), bottomRight()
    */

    /*!
        \fn qreal ZQEllipseF::bottom() const

        Returns the y-coordinate of the ellipse's bottom edge.

        \sa setBottom(), bottomLeft(), bottomRight()
    */

    /*!
        \fn QPointF ZQEllipseF::topLeft() const

        Returns the position of the ellipse's top-left corner.

        \sa setTopLeft(), top(), left()
    */

    /*!
        \fn QPointF ZQEllipseF::bottomRight() const

        Returns the position of the ellipse's  bottom-right corner.

        \sa setBottomRight(), bottom(), right()
    */

    /*!
        \fn QPointF ZQEllipseF::topRight() const

        Returns the position of the ellipse's top-right corner.

        \sa setTopRight(), top(), right()
    */

    /*!
        \fn QPointF ZQEllipseF::bottomLeft() const

        Returns the position of the ellipse's  bottom-left corner.

        \sa setBottomLeft(), bottom(), left()
    */

    /*!
        \fn QPainterPath ZQEllipseF::operator|(const ZQEllipseF &ellipse) const

        Returns the bounding ellipse of this ellipse and the given \an ellipse.
        The result will always have an angle of 0 degrees.

        \sa united()
    */

    QPainterPath ZQEllipseF::operator|(const ZQEllipseF &r) const noexcept
    {
        if (isNull())
            return r.toPath();
        if (r.isNull())
            return toPath();

        const ZQEllipseF first = normalized();
        const ZQEllipseF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.united(path2);
    }

    /*!
        \fn QPainterPath ZQEllipseF::united(const ZQEllipseF &ellipse) const
        \since 4.2

        Returns the bounding ellipse of this ellipse and the given \a
        ellipse. The result will always have an angle of 0 degrees.

        \image qEllipse-unite.png

        \sa intersected()
    */


    /*!
        \fn QPainterPath ZQEllipseF::operator&(const ZQEllipseF &ellipse) const

        Returns the intersection of this ellipse and the given \a
        ellipse. Returns an empty ellipse if there is no intersection.
        The angle of the intersected ellipse will always be 0 degrees.

        \sa intersected()
    */

    QPainterPath ZQEllipseF::operator&(const ZQEllipseF &r) const noexcept
    {
        if (isNull())
            return r.toPath();
        if (r.isNull())
            return toPath();

        const ZQEllipseF first = normalized();
        const ZQEllipseF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersected(path2);
    }

    /*!
        \fn QPainterPath ZQEllipseF::intersected(const ZQEllipseF &ellipse) const
        \since 4.2

        Returns the intersection of this ellipse and the given \a
        ellipse. Note that \c {r.intersected(s)} is equivalent to \c
        {r & s}.

        \image qEllipse-intersect.png

        \sa intersects(), united()
    */

    /*!
        \fn bool ZQEllipseF::intersects(const ZQEllipseF &ellipse) const

        Returns \c true if this ellipse intersects with the given \a
        ellipse (i.e. there is a non-empty area of overlap between
        them), otherwise returns \c false.

        The intersection ellipse can be retrieved using the intersected()
        function.

        \sa contains()
    */

    bool ZQEllipseF::intersects(const ZQEllipseF &r) const noexcept
    {
        const ZQEllipseF first = normalized();
        const ZQEllipseF second = r.normalized();

        const QPainterPath path1 = first.toPath();
        const QPainterPath path2 = second.toPath();

        return path1.intersects(path2);
    }

    /*!
        \fn ZQEllipse ZQEllipseF::toEllipse() const

        Returns a ZQEllipse based on the values of this ellipse.  Note that the
        coordinates in the returned ellipse are rounded to the nearest integer.

        \sa ZQEllipseF(), toAlignedEllipse()
    */

    /*!
        \fn ZQEllipse ZQEllipseF::toAlignedEllipse() const
        \since 4.3

        Returns a ZQEllipse based on the values of this ellipse that is the
        smallest possible integer ellipse that completely contains this
        ellipse.

        \sa toEllipse()
    */

    ZQEllipse ZQEllipseF::toAlignedEllipse() const noexcept
    {
        int xmin = int(qFloor(xp));
        int xmax = int(qCeil(xp + w));
        int ymin = int(qFloor(yp));
        int ymax = int(qCeil(yp + h));
        return ZQEllipse(xmin, ymin, xmax - xmin, ymax - ymin, a);
    }


    /*!
        \fn void ZQEllipseF::moveCenter(const QPointF &position)

        Moves the ellipse, leaving the center point at the given \a
        position. The ellipse's size is unchanged.

        \sa center()
    */

    /*!
        \fn bool operator==(const ZQEllipseF &r1, const ZQEllipseF &r2)
        \relates ZQEllipseF

        Returns \c true if the ellipses \a r1 and \a r2 are equal,
        otherwise returns \c false.
    */


    /*!
        \fn bool operator!=(const ZQEllipseF &r1, const ZQEllipseF &r2)
        \relates ZQEllipseF

        Returns \c true if the ellipses \a r1 and \a r2 are different, otherwise
        returns \c false.
    */

    /*!
        \fn ZQEllipseF operator+(const ZQEllipseF &lhs, const QMarginsF &rhs)
        \relates ZQEllipseF
        \since 5.3

        Returns the \a lhs ellipse grown by the \a rhs margins.
    */

    /*!
        \fn ZQEllipseF operator-(const ZQEllipseF &lhs, const QMarginsF &rhs)
        \relates ZQEllipseF
        \since 5.3

        Returns the \a lhs ellipse shrunk by the \a rhs margins.
    */

    /*!
        \fn ZQEllipseF operator+(const QMarginsF &lhs, const ZQEllipseF &rhs)
        \relates ZQEllipseF
        \overload
        \since 5.3

        Returns the \a lhs ellipse grown by the \a rhs margins.
    */

    /*!
        \fn ZQEllipseF ZQEllipseF::marginsAdded(const QMarginsF &margins) const
        \since 5.3

        Returns an ellipse grown by the \a margins.

        \sa operator+=(), marginsRemoved(), operator-=()
    */

    /*!
        \fn ZQEllipseF ZQEllipseF::marginsRemoved(const QMarginsF &margins) const
        \since 5.3

        Removes the \a margins from the ellipse, shrinking it.

        \sa marginsAdded(), operator+=(), operator-=()
    */

    /*!
        \fn ZQEllipseF ZQEllipseF::operator+=(const QMarginsF &margins)
        \since 5.3

        Adds the \a margins to the ellipse, growing it.

        \sa marginsAdded(), marginsRemoved(), operator-=()
    */

    /*!
        \fn ZQEllipseF ZQEllipseF::operator-=(const QMarginsF &margins)
        \since 5.3

        Returns an ellipse shrunk by the \a margins.

        \sa marginsRemoved(), operator+=(), marginsAdded()
    */

    /*!
        \fn QPainterPath ZQEllipseF::toPath()

        Converts the ellipse into a QPainterPath which can then be drawn on
        the screen.
    */

    /*!
        \fn QPainterPath ZQEllipseF::toPath(const QMatrix3x3 &mat, const QPointF &ref)

        Transforms the ellipse about the point \a ref using the transformation
        matrix \mat and then converts it into a QPainterPath which can then be
        drawn on the screen.
    */

    /*!
        \fn QString ZQEllipseF::toString()

        Returns a printable string of the ellipse.
    */

    QString ZQEllipseF::toString() const noexcept
    {
        return QString("ZQEllipseF(%1,%2 size %3x%4 %5 degrees)").arg(QString::number(xp), QString::number(yp),
                QString::number(w), QString::number(h), QString::number(a));
    }

    QPainterPath ZQEllipseF::toPath() const noexcept
    {

        QPainterPath path;
        QPointF c1 = QPointF(center().x(), top());
        QPointF c2 = QPointF(center().x() + (right()-center().x())*4/3, top());
        QPointF c3 = QPointF(center().x() + (right()-center().x())*4/3, bottom());
        QPointF c4 = QPointF(center().x(), bottom());
        QPointF c5 = QPointF(center().x() - (center().x()-left())*4/3, bottom());
        QPointF c6 = QPointF(center().x() - (center().x()-left())*4/3, top());
        QPointF cn = center();

        QPointF c1a, c2a, c3a, c4a, c5a, c6a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, int, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        boost::geometry::transform(c5 - cn, c5a, rotate);
        boost::geometry::transform(c6 - cn, c6a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;
        c5a += cn;
        c6a += cn;

        path.moveTo(c1a);
        path.cubicTo(c2a, c3a, c4a);
        path.cubicTo(c5a, c6a, c1a);
        path.closeSubpath();

        return path;
    }

    QPainterPath ZQEllipseF::toPath(const QMatrix3x3 &mat, const QPointF& ref) const noexcept
    {
        QPainterPath path;
        QPointF c1 = QPointF(center().x(), top());
        QPointF c2 = QPointF(center().x() + (right()-center().x())*4/3, top());
        QPointF c3 = QPointF(center().x() + (right()-center().x())*4/3, bottom());
        QPointF c4 = QPointF(center().x(), bottom());
        QPointF c5 = QPointF(center().x() - (center().x()-left())*4/3, bottom());
        QPointF c6 = QPointF(center().x() - (center().x()-left())*4/3, top());
        QPointF cn = center();

        QPointF c1a, c2a, c3a, c4a, c5a, c6a;
        boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, qreal, 2, 2> rotate(angle());
        boost::geometry::transform(c1 - cn, c1a, rotate);
        boost::geometry::transform(c2 - cn, c2a, rotate);
        boost::geometry::transform(c3 - cn, c3a, rotate);
        boost::geometry::transform(c4 - cn, c4a, rotate);
        boost::geometry::transform(c5 - cn, c5a, rotate);
        boost::geometry::transform(c6 - cn, c6a, rotate);
        c1a += cn;
        c2a += cn;
        c3a += cn;
        c4a += cn;
        c5a += cn;
        c6a += cn;

        QPointF c1r, c2r, c3r, c4r, c5r, c6r;
        boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>project2D(mat(0,0), mat(0,1), mat(0,2), mat(1,0), mat(1,1), mat(1,2), mat(2,0), mat(2,1), mat(2,2));
        boost::geometry::transform(c1a - ref, c1r, project2D);
        boost::geometry::transform(c2a - ref, c2r, project2D);
        boost::geometry::transform(c3a - ref, c3r, project2D);
        boost::geometry::transform(c4a - ref, c4r, project2D);
        boost::geometry::transform(c5a - ref, c5r, project2D);
        boost::geometry::transform(c6a - ref, c6r, project2D);
        c1r += ref;
        c2r += ref;
        c3r += ref;
        c4r += ref;
        c5r += ref;
        c6r += ref;

        path.moveTo(c1r);
        path.cubicTo(c2r, c3r, c4r);
        path.cubicTo(c5r, c6r, c1r);
        path.closeSubpath();
        return path;
    }

    /*****************************************************************************
      ZQEllipseF stream functions
     *****************************************************************************/
    #ifndef QT_NO_DATASTREAM
    /*!
        \fn QDataStream &operator<<(QDataStream &stream, const ZQEllipseF &ellipse)

        \relates ZQEllipseF

        Writes the \an ellipse to the \a stream, and returns a reference to the
        stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator<<(QDataStream &s, const ZQEllipseF &r)
    {
        s << double(r.x()) << double(r.y()) << double(r.width()) << double(r.height());
        return s;
    }

    /*!
        \fn QDataStream &operator>>(QDataStream &stream, ZQEllipseF &ellipse)

        \relates ZQEllipseF

        Reads a \an ellipse from the \a stream, and returns a reference to the
        stream.

        \sa {Serializing Qt Data Types}
    */

    QDataStream &operator>>(QDataStream &s, ZQEllipseF &r)
    {
        double x, y, w, h, a;
        s >> x;
        s >> y;
        s >> w;
        s >> h;
        s >> a;
        r.setEllipse(qreal(x), qreal(y), qreal(w), qreal(h), qreal(a));
        return s;
    }


    #endif // QT_NO_DATASTREAM


    #ifndef QT_NO_DEBUG_STREAM
    QDebug operator<<(QDebug dbg, const ZQEllipseF &r)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << r.toString();
        return dbg;
    }
    #endif

}
