#ifndef UTILS_H
#define UTILS_H

#define WIDTH  800
#define HEIGHT 800
#define PERIOD  30  // milisekunde
#define IS_TIMER_ENABLED      1   // 0: disable timer, 1: enable timer

#define DegToRadian 0.0174532
#define PI 3.1415

typedef struct {
    int speed;
} needleStruct;
enum class TextType { Bitmap, Stroke };

void drawText(int x, int y, float size, TextType type, void* font, const char* text);
void DrawCircleSpeedometer(float radius);
void DrawSpeedLines(float radius);
void DrawSpeedValues(float x, float y, float radius);
void DrawNeeedle(float radius);
void DrawSpeed(float x, float y);

#endif
