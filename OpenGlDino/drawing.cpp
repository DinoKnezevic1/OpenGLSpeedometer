#include <GL/glew.h>
#include <GL/freeglut.h>
#include "utils.h"
#include "drawing.h"
#include <corecrt_math.h>

extern int winWidth, winHeight;
extern bool running;

void DrawBackground() {
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.3f);
    glVertex2f(-winWidth / 2, winHeight / 2);
    glVertex2f(winWidth / 2, winHeight / 2);

    glColor3f(0.2f, 0.0f, 0.4f);
    glVertex2f(winWidth / 2, -winHeight / 2);
    glVertex2f(-winWidth / 2, -winHeight / 2);

    glEnd();
}

void DisplayAuthorInformation() {
    glColor3f(1, 1, 1);
    vprint(-390, 360, GLUT_BITMAP_8_BY_13, "Dino Knezevic");
    vprint(-390, 340, GLUT_BITMAP_8_BY_13, "#pre-alpha v1");
    vprint(100, -340, GLUT_BITMAP_8_BY_13, "UP arrow key to accelerate");
}

void DisplaySpeedometerOutline() {
    DrawCircleSpeedometer(0, 0, 248);
}

void DisplayDangerZone() {
    glColor3f(1, 0, 0);
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    for (float angle = 320 - 30; angle <= 320 + 30; angle += 5) {
        glVertex2f(240 * cos(angle * D2R) + 0, 240 * sin(angle * D2R) + 0);
    }
    glEnd();
}

void DisplaySpeedometerSpeedLabels() {
    DrawSpeedLines(0, 0, 248);
    DrawSpeedValues(-10, 0, 200);
}

void DisplaySpeedNeedle() {
    CalculateNeedle(0, 0, 248);
    DrawNeeedle(0, 0, 248);
    DrawSpeedLabels(-50, -300);
}

void DisplayStartStop() {
    // Coordinates for upper right corner
    int buttonX = winWidth / 2 - 110;
    int buttonY = winHeight / 2 - 60;

    // Draw the start/stop button
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(buttonX, buttonY);
    glVertex2f(buttonX + 100, buttonY);
    glVertex2f(buttonX + 100, buttonY + 50);
    glVertex2f(buttonX, buttonY + 50);
    glEnd();

    glColor3f(1, 1, 1);
    vprint(buttonX + 20, buttonY + 20, GLUT_BITMAP_HELVETICA_18, running ? "Stop" : "Start");
}


void RenderDisplay() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawBackground();
    DisplayAuthorInformation();
    DisplaySpeedometerOutline();
    DisplaySpeedometerSpeedLabels();
    DisplaySpeedNeedle();
    DisplayStartStop(); 

    glutSwapBuffers();
}
