#include <GL/glew.h>
#include <GL/freeglut.h>
#include "init.h"
#include "drawing.h"
#include "events.h"
#include "utils.h"

bool running = true;
needleStruct needle = { 0 };
int winWidth = WIDTH, winHeight = HEIGHT;
bool up = false;
void RenderDisplay();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Digital Speedometer");
    glewInit();
    // callback functions
    glutReshapeFunc(onResize);
    glutMouseFunc(onClick); 
    glutSpecialFunc(OnKeyPressed);
    glutSpecialUpFunc(OnKeyDepressed);
    glutDisplayFunc(RenderDisplay);

#if IS_TIMER_ENABLED == 1
    glutTimerFunc(PERIOD, onTimer, 0);
#endif
    Init();
    glutMainLoop();
    return 0;
}
