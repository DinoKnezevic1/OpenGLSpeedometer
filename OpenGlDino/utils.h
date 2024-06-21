#ifndef UTILS_H
#define UTILS_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define TIMER_PERIOD  30 // Period for the timer
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

void circle(int x, int y, int r);
void print(int x, int y, const char* string, void* font);
void vprint(int x, int y, void* font, const char* string, ...);
void vprint2(int x, int y, float size, const char* string, ...);
void draw_circle_wire(float x, float y, float r);
void draw_inner_circle_wire(float x, float y, float r);
void draw_lines(float x, float y, float r);
void draw_nums(float x, float y, float r);
void calculate_indicator(float x, float y, float r);
void draw_indicator(float x, float y, float r);
void draw_speed_info(float x, float y);
void draw_speed_arc(float x, float y, float r);

#endif // UTILS_H
