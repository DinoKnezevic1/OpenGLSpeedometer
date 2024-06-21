#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "utils.h"
#include "drawing.h"
#include "constants.h" 

extern int winWidth, winHeight;
extern bool running;
extern rect_t rectangle;
std::vector<int> speedHistory;


void draw_background() {
    glBegin(GL_QUADS);

    // Top color (e.g., dark blue)
    glColor3f(0.0f, 0.0f, 0.3f);
    glVertex2f(-winWidth / 2, winHeight / 2);
    glVertex2f(winWidth / 2, winHeight / 2);

    // Bottom color (e.g., dark purple)
    glColor3f(0.2f, 0.0f, 0.4f);
    glVertex2f(winWidth / 2, -winHeight / 2);
    glVertex2f(-winWidth / 2, -winHeight / 2);

    glEnd();
}

void display_label() {
    glColor3f(1, 1, 1);
    vprint(-390, 360, GLUT_BITMAP_8_BY_13, "Dino Knezevic");
    vprint(-390, 340, GLUT_BITMAP_8_BY_13, "#pre-alpha v1");
    vprint(-100, -340, GLUT_BITMAP_8_BY_13, "UP arrow key to accelerate");
}


// Function to draw the speed history graph
void draw_speed_history() {
    glColor3f(0, 1, 0);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < speedHistory.size(); ++i) {
        glVertex2f(-winWidth / 2 + i * (winWidth / maxHistorySize), -winHeight / 2 + speedHistory[i]);
    }
    glEnd();
}

// Function to draw the enhanced speedometer
void draw_speedometer(float x, float y, float r) {
    // Draw the outer circle
    glColor3f(0.8, 0.8, 0.8);
    draw_circle_wire(x, y, r);

    // Draw the needle
    glColor3f(1, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + r * cos((250 + -rectangle.angle) * D2R), y + r * sin((250 + -rectangle.angle) * D2R));
    glEnd();

    // Draw the markings
    draw_lines(x, y, r - 10);

    // Draw the speed text
    draw_speed_info(x - 30, y - r - 20);
}

// Function to draw the RPM gauge
void draw_rpm_gauge(float x, float y, float r) {
    // Draw the outer circle
    glColor3f(0.8, 0.8, 0.8);
    draw_circle_wire(x, y, r);

    // Draw the needle (for RPM, you might want to use a different variable)
    int rpmAngle = (rectangle.angle % 100) * 3.6; // Example conversion
    glColor3f(0, 0, 1);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + r * cos((250 + -rpmAngle) * D2R), y + r * sin((250 + -rpmAngle) * D2R));
    glEnd();

    // Draw the markings
    draw_lines(x, y, r - 10);

    // Draw the RPM text
    draw_speed_info(x - 30, y - r - 20); // Change this to show RPM value
}

void display_button() {
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

void display() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_background();

    // Draw the speedometer and RPM gauge
    draw_speedometer(-150, 0, 200); // Position and radius of the speedometer
    draw_rpm_gauge(150, 0, 200);    // Position and radius of the RPM gauge

    // Draw the speed history graph
    draw_speed_history();

    display_label();
    display_button();

    glutSwapBuffers();
}
