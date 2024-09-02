#ifndef EVENTS_H
#define EVENTS_H

void OnKeyPressed(int key, int x, int y);
void OnKeyDepressed(int key, int x, int y);
void onClick(int button, int stat, int x, int y); 
void onResize(int w, int h);
void onTimer(int v);

void toggleRunning(); 

#endif 
