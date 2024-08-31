#include <GL/glew.h>
#include <GL/freeglut.h>
#include "utils.h"
#include <stdio.h>  //  vsprintf_s
#include <corecrt_math.h>
extern rect_t rectangle;


void drawText(int x, int y, float size, TextType type, void* font, const char* text) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    if (type == TextType::Bitmap) {
        glRasterPos2f(0, 0);
        for (const char* c = text; *c; ++c) {
            glutBitmapCharacter(font, *c);
        }
    }
    else {
        glScalef(size, size, 1);
        for (const char* c = text; *c; ++c) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
        }
    }

    glPopMatrix();
}


void DrawCircleSpeedometer(float x, float y, float r) {
    glColor3f(1, 1, 1);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);

    for (float angle = -70; angle <= 250; angle += 5) {
        glVertex2f(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y);
    }

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
    char buffer[1024];

    for (float angle = 0 - 70; angle <= 320 - 70; angle += 10) {
        int speedValue = -1 * ((int)angle - 250);
        snprintf(buffer, sizeof(buffer), "%d", speedValue);

        float posX = (r + 0) * cos(angle * D2R) + x;
        float posY = r * sin(angle * D2R) + y;

        drawText(posX, posY, 1.0f, TextType::Bitmap, GLUT_BITMAP_HELVETICA_18, buffer);
    }
}
void CalculatePoint(float& xOut, float& yOut, float radius, float angle, float x, float y) {
    xOut = radius * cos(angle * D2R) + x;
    yOut = radius * sin(angle * D2R) + y;
}

void CalculateNeedle(float x, float y, float r) {
    float adjustedAngle = -rectangle.angle;

    CalculatePoint(rectangle.a.x, rectangle.a.y, r, 250 + adjustedAngle, x, y);
    CalculatePoint(rectangle.b.x, rectangle.b.y, 15, 150 + adjustedAngle, x, y);
    CalculatePoint(rectangle.c.x, rectangle.c.y, 20, 70 + adjustedAngle, x, y);
    CalculatePoint(rectangle.d.x, rectangle.d.y, 15, -10 + adjustedAngle, x, y);
}


void DrawNeeedle(float x, float y, float r) {
    glLineWidth(3);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    float angle = (250 - rectangle.angle) * D2R;
    glVertex2f((r - 20) * cos(angle) + x, (r - 20) * sin(angle) + y);
    glEnd();
}

void DrawSpeedLabels(float x, float y) {
    glColor3f(0, 0.5f, 1);
    glLineWidth(3);
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Speed: %d km/h", rectangle.angle);
    drawText(x, y, 1.0f, TextType::Bitmap, GLUT_BITMAP_HELVETICA_18, buffer);
}



