#include <GL/glew.h>
#include <GL/freeglut.h>
#include "utils.h"
#include <stdio.h>  //  vsprintf_s
#include <corecrt_math.h>
extern needleStruct needle;

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

void DrawCircleSpeedometer(float r) {
    glColor3f(1, 1, 1);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);

    for (float angle = 0; angle <= 180; angle += 5) {
        glVertex2f(r * cos(angle * DegToRadian), r * sin(angle * DegToRadian));
    }

    glEnd();
}

void DrawSpeedLines(float r) {
    glColor3f(1, 1, 1);
    glLineWidth(1);
    glBegin(GL_LINES);
    for (float angle = 0; angle <= 180; angle += 10) {
        float lineLength = (static_cast<int>((angle +10) / 10) % 2 == 0) ? 25 : 7.5; // Alternate line lengths
        glVertex2f(r * cos(angle * DegToRadian), r * sin(angle * DegToRadian));
        glVertex2f((r - lineLength) * cos(angle * DegToRadian), (r - lineLength) * sin(angle * DegToRadian));
    }
    glEnd();
}

void DrawSpeedValues(float x, float y, float r) {
    glColor3f(1, 1, 1);
    char buffer[1024];

    for (float angle = 0 ; angle <= 180; angle += 10) {
        int speedValue = -1 * ((int)angle - 180);
        snprintf(buffer, sizeof(buffer), "%d", speedValue);

        float posX = r * cos(angle * DegToRadian) + x;
        float posY = r * sin(angle * DegToRadian) + y;

        drawText(posX, posY, 1.0f, TextType::Bitmap, GLUT_BITMAP_HELVETICA_18, buffer);
    }
}

void DrawNeeedle( float r) {
    glLineWidth(5);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    float angle = (180 - needle.speed) * DegToRadian;
    glVertex2f(r * cos(angle), r * sin(angle));
    glEnd();
}

void DrawSpeed(float x, float y) {
    glColor3f(0, 0.5f, 1);
    glLineWidth(3);
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Speed: %d km/h", needle.speed);
    drawText(x, y, 1.0f, TextType::Bitmap, GLUT_BITMAP_HELVETICA_18, buffer);
}



