#ifndef UTILS_H
#define UTILS_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define TIMER_PERIOD  30  // milisekunde
#define TIMER_ON      1   // 0: disable timer, 1: enable timer

#define D2R 0.0174532
#define PI 3.1415

typedef struct {
    float x, y;
} point_t;

typedef struct {
    point_t a, b, c, d;
    int angle;
} rect_t;
enum class TextType { Bitmap, Stroke };

void drawText(int x, int y, float size, TextType type, void* font, const char* text);
void DrawCircleSpeedometer(float x, float y, float r);
void DrawSpeedLines(float x, float y, float r);
void DrawSpeedValues(float x, float y, float r);
void CalculateNeedle(float x, float y, float r);
void DrawNeeedle(float x, float y, float r);
void DrawSpeedLabels(float x, float y);

#endif
