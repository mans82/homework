#pragma once

namespace containers {
    struct Point {
        int x;
        int y;
    };

    bool operator==(const Point& ,const Point&);
    bool operator!=(const Point& ,const Point&);

    struct Rectangle {
        Point topLeft;
        Point bottomRight;
    };

    struct Circle {
        Point center;
        int radius;
    };

}