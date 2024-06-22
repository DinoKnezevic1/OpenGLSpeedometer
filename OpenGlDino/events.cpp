#include <GL/glew.h>
#include <GL/freeglut.h>
#include "events.h"
#include "drawing.h"
#include "utils.h"
#include "constants.h"

extern bool running;
extern rect_t rectangle;
extern int winWidth, winHeight;
extern bool up, down, left, right;

void onKeyDown(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
    glutPostRedisplay();
}

void onSpecialKeyDown(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }
    glutPostRedisplay();
}

void onSpecialKeyUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }
    glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y) {
    // Convert window coordinates to OpenGL coordinates
    int oglX = x - winWidth / 2;
    int oglY = winHeight / 2 - y;

    // Coordinates for upper right corner
    int buttonX = winWidth / 2 - 110;
    int buttonY = winHeight / 2 - 60;

    // Check if the click is within the start/stop button area
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        if (oglX > buttonX && oglX < buttonX + 100 && oglY > buttonY && oglY < buttonY + 50) {
            toggleRunning();
        }
    }
    glutPostRedisplay();
}


void onResize(int w, int h) {
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    RenderDisplay();
}

void onMoveDown(int x, int y) {
    glutPostRedisplay();
}

void onMove(int x, int y) {
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

    if (running) {
        if (up && rectangle.angle <= 316) {
            rectangle.angle = (rectangle.angle == 316) ? rectangle.angle + 4 : rectangle.angle + 8;
        }
        else if (!up && rectangle.angle >= 4) {
            rectangle.angle -= 4;
        }
    }

    glutPostRedisplay();
}
#endif

void toggleRunning() {
    running = !running;
}
