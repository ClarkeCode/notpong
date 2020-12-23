#ifndef RAYLIB_EXTENSIONS
#define RAYLIB_EXTENSIONS

#include "raylib.h"

namespace extensions {
    //Rectangle related extensions
    enum RectangleSide { TOP, BOTTOM, LEFT, RIGHT };
    enum RectangleVertex { TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

    inline Rectangle RectangleCentreOnCoord(Vector2 const& coord, float width, float height) {
        return Rectangle{coord.x-width/2.0f, coord.y-height/2.0f, width, height};
    }
    inline Rectangle RectangleCentreOnCoord(Vector2 const& coord, Rectangle const& rect) {
        return Rectangle{coord.x-rect.width/2.0f, coord.y-rect.height/2.0f, rect.width, rect.height};
    }
    inline Rectangle RectangleExpandByAmount(Rectangle const& rect, float amount) {
        return Rectangle{rect.x-amount, rect.y-amount, rect.width+2*amount, rect.height+2*amount};
    }
    inline Vector2 RectangleGetVertexCoord(Rectangle const& rect, RectangleVertex const& desiredVertex) {
        if (desiredVertex == TOPLEFT)
            return Vector2{rect.x, rect.y};
        else if (desiredVertex == TOPRIGHT)
            return Vector2{rect.x+rect.width, rect.y};
        else if (desiredVertex == BOTTOMLEFT)
            return Vector2{rect.x, rect.y+rect.height};
        else
            return Vector2{rect.x+rect.width, rect.y+rect.height};
    }

    inline bool isValueWithinRange(float value, float min, float max) { return value >= min && value <= max; }
    inline bool isPointWithinYValues(Vector2 const& xyCoord, Rectangle const& rect) {
        return xyCoord.y >= rect.y && xyCoord.y <= rect.y + rect.height;
    }
    inline bool isPointWithinXValues(Vector2 const& xyCoord, Rectangle const& rect) {
        return xyCoord.x >= rect.x && xyCoord.x <= rect.x + rect.width;
    }
}

#endif