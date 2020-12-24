#ifndef GAME_MODEL_PONG
#define GAME_MODEL_PONG
#include "raylib.h"
#include "raymath.h"
#include "raylib_extensions.hpp"
#include "game_concepts.hpp"

namespace pong {
    class PongModel;

    class Wall: public concept::DrawableObject, public concept::GeometryColours, public concept::CollidableRectangle {
        public:
        Wall(Rectangle rect) : concept::GeometryColours(GRAY, DARKGRAY), concept::CollidableRectangle(rect) {}
        Wall() : Wall(extensions::RectangleZero()) {}
        
        virtual inline void drawObject() {
            DrawRectangleRec(rect, GRAY);
            DrawRectangleLinesEx(rect, 1, DARKGRAY);
        }
    };

    class ScoreZone: public concept::CollidableRectangle {
        public:
        ScoreZone(Rectangle rect) : concept::CollidableRectangle(rect) {};
        ScoreZone() : ScoreZone(extensions::RectangleZero()) {}

        virtual inline Rectangle getCollisionBox() const { return rect; }
    };

    class Paddle: public concept::DrawableObject, public concept::GeometryColours, public concept::CollidableRectangle {
        public:
        //xyPosition corresponds to the centre of the paddle
        Vector2 xyPosition;
        float speed;
        
        Paddle(Vector2 position, float width, float height, float speed) :
            GeometryColours(Color{255,0,0,255}, Color{255,255,0,255}),
            CollidableRectangle(Rectangle{position.x-width/2.0f, position.y-height/2.0f, width, height}),
            xyPosition(position), speed(speed) {}
        Paddle() : Paddle(Vector2Zero(), 0, 0, 0) {}

        virtual void drawObject();
        void updatePaddle(float verticalDelta, float maxYPos, float minYPos);
    };

    class Ball: public concept::DrawableObject, public concept::GeometryColours {
        public:
        Vector2 xyPosition;
        float radius;
        float speed;
        Vector2 directionVect;

        Ball(float x, float y, float r, float s, float d);
        Ball() : Ball(0, 0, 0, 0, 0) {}

        void setDirection(Vector2& directionVector);
        void setDirection(float radianAngle);

        virtual void drawObject();
        void updateBall(float frameTime, PongModel& gameModel);
    };

    class ScoreBoard: public concept::DrawableObject {
        PongModel* model_ptr;
        Rectangle P1ScoreDisplayZone, P2ScoreDisplayZone;
        float fontSize;

        public:
        ScoreBoard() : model_ptr(nullptr), P1ScoreDisplayZone(Rectangle{0}), P2ScoreDisplayZone(Rectangle{0}), fontSize(0) {}
        ScoreBoard(PongModel* model_p, Rectangle P1Zone, Rectangle P2Zone, float fontSize) :
            model_ptr(model_p), P1ScoreDisplayZone(P1Zone), P2ScoreDisplayZone(P2Zone), fontSize(fontSize) {}
        virtual void drawObject();
    };

    class PongModel: public concept::DrawableObject {
        public:
        concept::GameWorld* worldInfo;
        Wall TopWall, BottomWall;
        Paddle P1Paddle, P2Paddle;
        int P1Score, P2Score;
        ScoreZone P1ScoreZone, P2ScoreZone;
        ScoreBoard GameScore;

        Ball PongBall;
        bool canBallMove;
        float paddleWidth, paddleHeight, paddleSpeed;
        float MaxPaddleYPosition, MinPaddleYPosition;

        PongModel() {}
        PongModel(concept::GameWorld* gw);
        ~PongModel() {}

        virtual void drawObject();
    };
}
#endif