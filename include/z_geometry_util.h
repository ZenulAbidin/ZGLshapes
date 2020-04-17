#ifndef Z_GEOMETRY_UTIL_H
#define Z_GEOMETRY_UTIL_H

#include <array>
#include <initializer_list>
#include "z_matrix.h"
#include "z_linalg.h"

namespace z_geometry_util {

    bool isCollinear(const QPointF &a, const QPointF &b, const QPointF &c) {
        z_linalg::ZQMatrix<2, 3, qreal> m( &std::array<qreal, 6>({ a.x(), a.y(), b.x(), b.y(), c.x(), c.y() })[0] );
        if (z_linalg::rank(m) <= 1) {
            return true;
        }
        else {
            return false;
        }

    }

    // It's not taking QPoint() constructors for some reason
    bool isCollinear(const QPoint &a, const QPoint &b, const QPoint &c) {
        return isCollinear(QPointF(a), QPointF(b), QPointF(c));
    }
}

#endif
