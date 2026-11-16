// casually use 1 kb of ram
#define STACK 256*2*2

static const int SIZE = 25;
static const int WIDTH = 25;
static const int HEIGHT = 19;

static const float STEP = 100;
static const float FPS = 12;   // frames per step :)
static const int SLEEP = (int)(STEP / FPS);

static const float POV_WIDTH = 600.0;
static const float POV_HEIGHT = 400.0;
static const float WALL_HEIGHT = 0.45;
static const float FOV = 1.0;

