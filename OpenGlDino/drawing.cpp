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
    drawText(-390, 360, 1.0f, TextType::Bitmap, GLUT_BITMAP_8_BY_13, "Dino Knezevic");
}

void DisplaySpeedometerOutline() {
    DrawCircleSpeedometer(300);
}

void DisplaySpeedometerSpeedLabels() {
    DrawSpeedLines(300);
    DrawSpeedValues(-15, 0, 255);
}

void DisplaySpeedNeedle() {
    DrawNeeedle(300);
    DrawSpeed(-50, -100);
}

void DisplayStartStop() {
    int buttonX = winWidth / 2 - 110;
    int buttonY = winHeight / 2 - 60;

    // Draw the button background
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(buttonX, buttonY);
    glVertex2f(buttonX + 100, buttonY);
    glVertex2f(buttonX + 100, buttonY + 50);
    glVertex2f(buttonX, buttonY + 50);
    glEnd();

    // Draw the button text
    glColor3f(1, 1, 1);
    drawText(buttonX + 20, buttonY + 20, 1.0f, TextType::Bitmap, GLUT_BITMAP_HELVETICA_18, running ? "Stop" : "Start");
}



void RenderDisplay() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawBackground();
    DisplayAuthorInformation();
    DisplayStartStop(); 
    DisplaySpeedNeedle();
    DisplaySpeedometerSpeedLabels();
    DisplaySpeedometerOutline();

    glutSwapBuffers();
}
