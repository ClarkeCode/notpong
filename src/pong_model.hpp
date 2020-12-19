#ifndef __GAME_MODEL_PONG
#define __GAME_MODEL_PONG
namespace pong {
    class GameWorld {
        public:
        int width, height;
        GameWorld(int horizontalWidth, int verticalHeight) : width(horizontalWidth), height(verticalHeight) {}
    };

    class GameObject {
        public:
        virtual void drawObject() = delete;
        virtual ~GameObject() {}
    };

    class Paddle {
        public:
        double xpos, ypos;
        double width, length;
        double speed;
        
        Paddle(double x, double y, double w, double l, double s) : xpos(x), ypos(y), width(w), length(l), speed(s) {}
        Paddle() : Paddle(0, 0, 0, 0, 0) {}
    };

    class Ball {
        public:
        double xpos, ypos;
        double radius;
        double speed;
        double direction;

        Ball(double x, double y, double r, double s, double d) : xpos(x), ypos(y), radius(r), speed(s), direction(d) {}
        Ball() : Ball(0, 0, 0, 0, 0) {}
    };

    class PongModel {
        public:
        Paddle P1Paddle, P2Paddle;
        Ball PongBall;
        int topBottomWallThickness;
        double paddleWidth, paddleHeight, paddleSpeed;
        double MaxPaddleYPosition, MinPaddleYPosition;

        PongModel() {}
        PongModel(GameWorld& gw);
        ~PongModel() {}
    };
}
#endif