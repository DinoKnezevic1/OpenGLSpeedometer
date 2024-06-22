#include <GL/glew.h>
#include <GL/freeglut.h>
#include "utils.h"
#include <stdarg.h> // for va_list, va_start, va_end
#include <stdio.h>  // for vsprintf_s
#include <corecrt_math.h>

extern rect_t rectangle;

void circle(int x, int y, int r) {
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font) {
    int len = (int)strlen(string);
    glRasterPos2f(x, y);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

void vprint(int x, int y, void* font, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    glRasterPos2f(x, y);
    int len = (int)strlen(str);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, str[i]);
    }
}

void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len = (int)strlen(str);
    for (int i = 0; i < len; i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

float easeInOut(float t) {
    return t * t * (3.0f - 2.0f * t);
}

void DrawCircleSpeedometer(float x, float y, float r) {
    glColor3f(1, 1, 1);
    glLineWidth(1);
    glBegin(GL_LINE_STRIP);
    glVertex2f((r + 2) * cos(-70 * D2R) + x, (r + 2) * sin(-70 * D2R) + y);
    glVertex2f((r + 24) * cos(-70 * D2R) + x, (r + 24) * sin(-70 * D2R) + y);
    for (float angle = 0 - 70; angle <= 320 - 70; angle += 5) {
        glVertex2f(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y);
    }
    glVertex2f((r + 2) * cos(250 * D2R) + x, (r + 2) * sin(250 * D2R) + y);
    glVertex2f((r + 24) * cos(250 * D2R) + x, (r + 24) * sin(250 * D2R) + y);
    glEnd();
}

void DrawSpeedLines(float x, float y, float r) {
    glColor3f(1, 1, 1);
    glLineWidth(1);
    glBegin(GL_LINES);
    for (float angle = 10 - 70; angle <= 310 - 70; angle += 10) {
        float lineLength = (static_cast<int>((angle + 70) / 10) % 2 == 0) ? 25 : 7.5; // Alternate line lengths
        glVertex2f(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y);
        glVertex2f((r - lineLength) * cos(angle * D2R) + x, (r - lineLength) * sin(angle * D2R) + y);
    }
    glEnd();
}

void DrawSpeedValues(float x, float y, float r) {
    glLineWidth(10);
    glColor3f(1, 1, 1);
    for (float angle = 0 - 70; angle <= 320 - 70; angle += 10) {
        vprint((r+0) * cos(angle * D2R) + x, r * sin(angle * D2R) + y, GLUT_BITMAP_HELVETICA_18, "%d", -1 * ((int)angle - 250));
    }
}

void CalculateNeedle(float x, float y, float r) {
    rectangle.a.x = r * cos((250 + -rectangle.angle) * D2R) + x;
    rectangle.a.y = r * sin((250 + -rectangle.angle) * D2R) + y;

    rectangle.b.x = 15 * cos((150 + -rectangle.angle) * D2R) + x;
    rectangle.b.y = 15 * sin((150 + -rectangle.angle) * D2R) + y;

    rectangle.c.x = 20 * cos((70 + -rectangle.angle) * D2R) + x;
    rectangle.c.y = 20 * sin((70 + -rectangle.angle) * D2R) + y;

    rectangle.d.x = 15 * cos((-10 + -rectangle.angle) * D2R) + x;
    rectangle.d.y = 15 * sin((-10 + -rectangle.angle) * D2R) + y;
}

void DrawNeeedle(float x, float y, float r) {
    glLineWidth(3); 
    glColor3f(1, 0, 0); // Red color 
    glBegin(GL_LINES);
    glVertex2f(x, y);
    float angle = (250 - rectangle.angle) * D2R;
    glVertex2f((r - 20) * cos(angle) + x, (r - 20) * sin(angle) + y); 
    glEnd();
}

void DrawSpeedLabels(float x, float y) {
    glColor3f(0, 0.5f, 1);
    glLineWidth(3);
    vprint2(x, y, 0.2f, "%d", rectangle.angle);
    vprint2(x, y - 30, 0.15f, "KM/h");
}


