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
        
        virtual inline void drawObject() {
            DrawRectangleRec(rect, GRAY);
            DrawRectangleLinesEx(rect, 1, DARKGRAY);
        }
        virtual inline Rectangle getCollisionBox() const { return rect; }
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
        virtual Rectangle getCollisionBox() const;
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
        ScoreBoard GameScore;

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