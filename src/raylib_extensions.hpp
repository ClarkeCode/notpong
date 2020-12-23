#ifndef RAYLIB_EXTENSIONS
#define RAYLIB_EXTENSIONS

#include "raylib.h"

namespace extensions {
    //Rectangle related extensions
    enum RectangleSide { TOP, BOTTOM, LEFT, RIGHT };
    enum RectangleVertex { TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
    
    Rectangle RectangleExpandByAmount(Rectangle const& rect, float amount) {
        return Rectangle{rect.x-amount, rect.y-amount, rect.width+2*amount, rect.height+2*amount};
    }
    Vector2 RectangleGetVertexCoord(Rectangle const& rect, RectangleVertex const& desiredVertex) {
        if (desiredVertex == TOPLEFT)
            return Vector2{rect.x, rect.y};
        else if (desiredVertex == TOPRIGHT)
            return Vector2{rect.x+rect.width, rect.y};
        else if (desiredVertex == BOTTOMLEFT)
            return Vector2{rect.x, rect.y+rect.height};
        else
            return Vector2{rect.x+rect.width, rect.y+rect.height};
    }

    bool isValueWithinRange(float value, float min, float max) { return value >= min && value <= max; }
    bool isPointWithinYValues(Vector2 const& xyCoord, Rectangle const& rect) {
        return xyCoord.y >= rect.y && xyCoord.y <= rect.y + rect.height;
    }
    bool isPointWithinXValues(Vector2 const& xyCoord, Rectangle const& rect) {
        return xyCoord.x >= rect.x && xyCoord.x <= rect.x + rect.width;
    }
}

#endif