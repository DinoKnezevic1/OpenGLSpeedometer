#include <GL/glew.h>
#include <GL/freeglut.h>
#include "init.h"
#include "drawing.h"
#include "events.h"
#include "utils.h"

bool running = true;
needleStruct needle = { 0 };
int winWidth = WINDOW_WIDTH, winHeight = WINDOW_HEIGHT;
bool up = false, down = false, left = false, right = false;
void RenderDisplay();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Digital Speedometer");
    glewInit();
    // callback functions
    glutReshapeFunc(onResize);
    glutMouseFunc(onClick); 
    glutSpecialFunc(OnKeyPressed);
    glutSpecialUpFunc(OnKeyDepressed);
    glutDisplayFunc(RenderDisplay);

#if TIMER_ON == 1
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif
    Init();
    glutMainLoop();
    return 0;
}
