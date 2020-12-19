#ifndef __GAME_MODEL_PONG
#define __GAME_MODEL_PONG
namespace pong {
    class Paddle {
        double xpos, ypos;
        double width;
        double speed;
        
        public:
        Paddle(double x, double y, double w, double s) : xpos(x), ypos(y), width(w), speed(s) {}
        Paddle() : Paddle(0, 0, 0, 0) {}
    };

    class Ball {
        double xpos, ypos;
        double radius;
        double speed;
        double direction;

        public:
        Ball(double x, double y, double r, double s, double d) : xpos(x), ypos(y), radius(r), speed(s), direction(d) {}
        Ball() : Ball(0, 0, 0, 0, 0) {}
    };

    class PongModel {
        Paddle P1Paddle, P2Paddle;
        Ball PongBall;
        double MaxPaddleLocation, MinPaddleLocation;

        public:
        PongModel() {}
        ~PongModel() {}
    };
}
#endif