#include <GL/glew.h>
#include <GL/freeglut.h>
#include "init.h"
#include "drawing.h"
#include "events.h"
#include "utils.h"

// Global Variables
bool running = true;
rect_t rectangle = { 0 };
int winWidth = WINDOW_WIDTH, winHeight = WINDOW_HEIGHT;
bool up = false, down = false, left = false, right = false;

void RenderDisplay();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Digital Speedometer");

    glewInit();

    // Register callback functions
    glutDisplayFunc(RenderDisplay);
    glutReshapeFunc(onResize);
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);
    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);
    glutMouseFunc(onClick); 
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if TIMER_ON == 1
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();
    glutMainLoop();
    return 0;
}
