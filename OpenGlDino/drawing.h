#ifndef DRAWING_H
#define DRAWING_H

void draw_background();
void display_label();
void display_outline();
void display_speed_text();
void display_danger_zone();
void display_indicator();
void display_speed_arc();
void display_button();
void display(); // Add this line


void draw_speed_history();
void draw_speedometer(float x, float y, float r);
void draw_rpm_gauge(float x, float y, float r);
#endif // DRAWING_H
