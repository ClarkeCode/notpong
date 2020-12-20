#ifndef GAME_CONCEPTS
#define GAME_CONCEPTS
#include "raylib.h"

namespace concept {
    class GameWorld {
        public:
        int width, height;
        GameWorld(int horizontalWidth, int verticalHeight) : width(horizontalWidth), height(verticalHeight) {}
    };

    class DrawableObject {
        public:
        virtual void drawObject() = 0;
        virtual ~DrawableObject() {}
    };

    class CollidableRectangle {
        public:
        virtual Rectangle getCollisionBox() = 0;
        virtual ~CollidableRectangle() {}
    };

    class GeometryColours {
        public:
        Color lineColour;
        Color fillColour;

        GeometryColours(Color line, Color fill) : lineColour(line), fillColour(fill) {}
    };
}

#endif