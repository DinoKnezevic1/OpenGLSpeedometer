#ifndef UTILS_H
#define UTILS_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define TIMER_PERIOD  30  // milisekunde
#define TIMER_ON      1   // 0: disable timer, 1: enable timer

#define DegToRadian 0.0174532
#define PI 3.1415

typedef struct {
    float x, y;
} needlePoint;

typedef struct {
    needlePoint a, b, c, d;
    int speed;
} needleStruct;
enum class TextType { Bitmap, Stroke };

void drawText(int x, int y, float size, TextType type, void* font, const char* text);
void DrawCircleSpeedometer(float r);
void DrawSpeedLines(float r);
void DrawSpeedValues(float x, float y, float r);
void DrawNeeedle(float r);
void DrawSpeed(float x, float y);

#endif
