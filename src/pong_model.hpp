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

    class PongModel;

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
        Rectangle getCollisionBox();
    };

    class Ball: public DrawableObject, public GeometryColours {
        public:
        Vector2 xyPosition;
        float radius;
        float speed;
        float direction;

        Ball(float x, float y, float r, float s, float d) :
            GeometryColours(Color{0,0,230,255}, Color{60,60,60,255}),
            xyPosition(Vector2{x,y}), radius(r), speed(s), direction(d) {}
        Ball() : Ball(0, 0, 0, 0, 0) {}

        virtual void drawObject();
        void updateBall(float frameTime, PongModel& gameModel);
    };

    class PongModel: public DrawableObject {
        public:
        GameWorld* worldInfo;
        Paddle P1Paddle, P2Paddle;
        Ball PongBall;
        bool canBallMove;
        int topBottomWallThickness;
        float paddleWidth, paddleHeight, paddleSpeed;
        float MaxPaddleYPosition, MinPaddleYPosition;

        PongModel() {}
        PongModel(GameWorld* gw);
        ~PongModel() {}

        virtual void drawObject();
    };
}
#endif