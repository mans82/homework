#include "shapes.h"

namespace containers {
    bool operator==(const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }

    bool operator!=(const Point& a, const Point& b) {
        return !(a == b);
    }
}