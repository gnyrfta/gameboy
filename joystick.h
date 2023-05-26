#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

void joyStickInit();
void setCommand(int xValue, int yValue);
int changeCursorXValue(int cursorX);
int changeCursorYValue(int cursorY);
int readJoyStickButton();
bool buttonPressed();
bool buttonReleased();
int readJoyStickX();
int readJoyStickY();
void resetCommand();

#endif
