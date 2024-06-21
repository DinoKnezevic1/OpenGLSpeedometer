#include <GL/glew.h>
#include <GL/freeglut.h>
#include "utils.h"
#include <stdarg.h> // for va_list, va_start, va_end
#include <stdio.h>  // for vsprintf_s

#include <corecrt_math.h>
extern rect_t rectangle; // Add this line

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

void draw_circle_wire(float x, float y, float r) {
    glColor3f(1, 1, 1);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    for (float angle = 0; angle < 360; angle += 5) {
        glVertex2f(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y);
    }
    glEnd();
}

void draw_inner_circle_wire(float x, float y, float r) {
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

void draw_lines(float x, float y, float r) {
    glColor3f(1, 1, 1);
    glLineWidth(1);
    glBegin(GL_LINES);
    for (float angle = 0 - 70; angle <= 320 - 70; angle += 20) {
        glVertex2f(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y);
        glVertex2f((r - 15) * cos(angle * D2R) + x, (r - 15) * sin(angle * D2R) + y);
    }
    glEnd();
}

void draw_nums(float x, float y, float r) {
    glLineWidth(10);
    glColor3f(1, 1, 1);
    for (float angle = 0 - 70; angle <= 320 - 70; angle += 20) {
        vprint(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y, GLUT_BITMAP_HELVETICA_18, "%d", -1 * ((int)angle - 250));
    }
}

void calculate_indicator(float x, float y, float r) {
    rectangle.a.x = r * cos((250 + -rectangle.angle) * D2R) + x;
    rectangle.a.y = r * sin((250 + -rectangle.angle) * D2R) + y;

    rectangle.b.x = 15 * cos((150 + -rectangle.angle) * D2R) + x;
    rectangle.b.y = 15 * sin((150 + -rectangle.angle) * D2R) + y;

    rectangle.c.x = 20 * cos((70 + -rectangle.angle) * D2R) + x;
    rectangle.c.y = 20 * sin((70 + -rectangle.angle) * D2R) + y;

    rectangle.d.x = 15 * cos((-10 + -rectangle.angle) * D2R) + x;
    rectangle.d.y = 15 * sin((-10 + -rectangle.angle) * D2R) + y;
}

void draw_indicator(float x, float y, float r) {
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(rectangle.a.x, rectangle.a.y);
    glVertex2f(rectangle.b.x, rectangle.b.y);
    glVertex2f(rectangle.c.x, rectangle.c.y);
    glVertex2f(rectangle.d.x, rectangle.d.y);
    glEnd();

    glLineWidth(3);
    glColor3f(0.5, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(rectangle.a.x, rectangle.a.y);
    glVertex2f(rectangle.b.x, rectangle.b.y);
    glVertex2f(rectangle.c.x, rectangle.c.y);
    glVertex2f(rectangle.d.x, rectangle.d.y);
    glEnd();

    glColor3f(0, 0, 0);
    circle(x, y, 8);
}

void draw_speed_info(float x, float y) {
    glColor3f(1, 1, 0);
    glLineWidth(3);
    vprint2(x, y, 0.2f, "%d", rectangle.angle);
    vprint2(x, y - 70, 0.1f, "KM/h");
}

void draw_speed_arc(float x, float y, float r) {
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    for (float a = 0; a <= rectangle.angle; a += 1) {
        float t = a / 320.0f;

        float red = (t < 0.5f) ? 2.0f * t : 1.0f;
        float green = (t < 0.5f) ? 1.0f : 1.0f - 2.0f * (t - 0.5f);
        float blue = 0.0f;

        glColor3f(red, green, blue);
        float angle = (250 + -a) * D2R;
        glVertex2f((r + 4) * cos(angle) + x, (r + 4) * sin(angle) + y);
    }
    glEnd();
}
