#ifndef EVENTS_H
#define EVENTS_H

void onKeyDown(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);
void onSpecialKeyDown(int key, int x, int y);
void onSpecialKeyUp(int key, int x, int y);
void onClick(int button, int stat, int x, int y); // Ensure this is declared
void onResize(int w, int h);
void onMoveDown(int x, int y);
void onMove(int x, int y);
void onTimer(int v);

void toggleRunning(); // Add this line

#endif // EVENTS_H
