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

static const char HELP[] = 
"usage: ./maze [args] | java -jar ./drawapp-5.0.jar\n"
"\n"
"--gen [algorithm]\n"
"    Choose a maze generation algorithm. One of:\n"
"        prim: Randomised Prim's algorithm\n"
"        dfs: Randomised Depth First Search\n"
"--solve [algorithm]\n"
"    Choose a maze solving algorithm. One of:\n"
"        hug: simple left wall hug (DFS)\n"
"        hugright: ditto, but right wall\n"
"        random: random mouse algorithm\n"
"--pov  \n"
"    Run the program in a 3D view from the perspective of the robot.\n"
"--seed [int]  \n"
"    Set a seed for maze generation.\n"
"--speed [float]  \n"
"    Set a speed multiplier for animation.\n"
"--width [int]  \n"
"    Set the width of the maze. Must be odd.\n"
"--height [int]  \n"
"    Set the height of the maze. Must be odd.\n"
"--help  \n"
"    Display this help information.\n";

