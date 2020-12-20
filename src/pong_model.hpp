#ifndef GAME_MODEL_PONG
#define GAME_MODEL_PONG
#include "raylib.h"
#include "game_concepts.hpp"

namespace pong {
    class PongModel;

    class Wall: public concept::DrawableObject, public concept::GeometryColours, public concept::CollidableRectangle {
        Rectangle rect;
        public:
        Wall(Rectangle rect) : concept::GeometryColours(GRAY, DARKGRAY), rect(rect) {}
        Wall() : Wall(Rectangle{0,0,0,0}) {}
        
        virtual void drawObject() {
            DrawRectangleRec(rect, GRAY);
            DrawRectangleLinesEx(rect, 1, DARKGRAY);
        }
        virtual Rectangle getCollisionBox() { return rect; }
    };

    class Paddle: public concept::DrawableObject, public concept::GeometryColours, public concept::CollidableRectangle {
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
        virtual Rectangle getCollisionBox();
    };

    class Ball: public concept::DrawableObject, public concept::GeometryColours {
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

    class PongModel: public concept::DrawableObject {
        public:
        concept::GameWorld* worldInfo;
        Wall TopWall, BottomWall;
        Paddle P1Paddle, P2Paddle;
        Ball PongBall;
        bool canBallMove;
        int topBottomWallThickness;
        float paddleWidth, paddleHeight, paddleSpeed;
        float MaxPaddleYPosition, MinPaddleYPosition;

        PongModel() {}
        PongModel(concept::GameWorld* gw);
        ~PongModel() {}

        virtual void drawObject();
    };
}
#endif