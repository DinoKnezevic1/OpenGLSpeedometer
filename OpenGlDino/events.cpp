#include <GL/glew.h>
#include <GL/freeglut.h>
#include "events.h"
#include "drawing.h"
#include "utils.h"
#include "constants.h"
#include <algorithm>
extern bool running;
extern needleStruct needle;
extern int winWidth, winHeight;
extern bool up;

void OnKeyPressed(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    }
    glutPostRedisplay();
}

void OnKeyDepressed(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
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


float calculateIncrement(bool accelerating, float currentAngle) {
    if (accelerating) {
        // simulate acceleration
        return std::min(8.0f, (180.0f - currentAngle) / 20.0f); 
    }
    else {
        //  simulate deceleration
        return std::max(-4.0f, -currentAngle / 80.0f); 
    }
}


#if TIMER_ON == 1
void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

    if (running) {
        float increment = calculateIncrement(up, needle.speed);
        needle.speed += increment;

        if (needle.speed < 0) needle.speed = 0;
        if (needle.speed > 180) needle.speed = 180;
    }

    glutPostRedisplay();
}
#endif

void toggleRunning() {
    running = !running;
}
