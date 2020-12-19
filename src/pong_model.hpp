#ifndef __GAME_MODEL_PONG
#define __GAME_MODEL_PONG
#include "raylib.h"
namespace pong {
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

    class GeometryColours {
        public:
        Color lineColour;
        Color fillColour;

        GeometryColours(Color line, Color fill) : lineColour(line), fillColour(fill) {}
    };

    class Paddle: public DrawableObject, public GeometryColours {
        public:
        float xpos, ypos;
        float width, height;
        float speed;
        
        Paddle(float x, float y, float w, float h, float s) : 
            GeometryColours(Color{255,0,0,255}, Color{255,255,0,255}), 
            xpos(x), ypos(y), width(w), height(h), speed(s) {}
        Paddle() : Paddle(0, 0, 0, 0, 0) {}

        virtual void drawObject();
        void updatePaddle(float verticalDelta, float maxYPos, float minYPos);
    };

    class Ball: public DrawableObject, public GeometryColours {
        public:
        double xpos, ypos;
        double radius;
        double speed;
        double direction;

        Ball(double x, double y, double r, double s, double d) :
            GeometryColours(Color{0,0,230,255}, Color{60,60,60,255}),
            xpos(x), ypos(y), radius(r), speed(s), direction(d) {}
        Ball() : Ball(0, 0, 0, 0, 0) {}

        virtual void drawObject();
    };

    class PongModel: public DrawableObject {
        public:
        GameWorld* worldInfo;
        Paddle P1Paddle, P2Paddle;
        Ball PongBall;
        int topBottomWallThickness;
        double paddleWidth, paddleHeight, paddleSpeed;
        double MaxPaddleYPosition, MinPaddleYPosition;

        PongModel() {}
        PongModel(GameWorld* gw);
        ~PongModel() {}

        virtual void drawObject();
    };
}
#endif