/*This file should contain joystick code.*/
#include <ezButton.h>//necessary for reading pushdown on the button.
using namespace std;

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define SW_PIN   2  // Arduino pin connected to SW  pin

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

ezButton button(SW_PIN);//Necessary for registering pushdown-state. 
int cursorSpeed{3};

int angle{0};
int rotationSpeed = 10;
int originSpeed = 0;

int command = COMMAND_NO;
void joyStickInit()
{
  button.setDebounceTime(50);
}
void setCommand(int xValue, int yValue) //Checks up, down, right, left.
{
  if (xValue < LEFT_THRESHOLD)
      command = command | COMMAND_LEFT;
    else if (xValue > RIGHT_THRESHOLD)
      command = command | COMMAND_RIGHT;
  if (yValue < UP_THRESHOLD)
      command = command | COMMAND_UP;
    else if (yValue > DOWN_THRESHOLD)
      command = command | COMMAND_DOWN;
    // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS
}
int changeCursorXValue(int cursorX)
{
  if (command & COMMAND_LEFT) {
   // Serial.println("COMMAND LEFT");
    if(cursorX > 0 )
    {
    cursorX-=cursorSpeed;
    }
  }

  if (command & COMMAND_RIGHT) {
    //Serial.println("COMMAND RIGHT");
    if(cursorX < 240)
    {
    cursorX+=cursorSpeed;
    }
  }
  return cursorX;
}
int changeCumulativeCursorXValue(int cursorX)
{
  if (command & COMMAND_LEFT) {
   // Serial.println("COMMAND LEFT");
    if(cursorX > 0 )
    {
    cursorX-=cursorSpeed;
    }
  }

  if (command & COMMAND_RIGHT) {
    //Serial.println("COMMAND RIGHT");
    if(cursorX < 240*3)
    {
    cursorX+=cursorSpeed;
    }
  }
  return cursorX;
}
int changeCursorYValue(int cursorY)
{
  if (command & COMMAND_UP) {
    //Serial.println("COMMAND UP");
    if(cursorY > 0)
    {        
    cursorY-=cursorSpeed; 
    }   
  }

  if (command & COMMAND_DOWN) {
    //Serial.println("COMMAND DOWN");
    if(cursorY < 320)
    {
    cursorY+=cursorSpeed;
    }
  }
  return cursorY;
}
int changeAngle()
{
  if (command & COMMAND_LEFT) 
  {
   // Serial.println("COMMAND LEFT");
      angle+=rotationSpeed;
  }
  else if (command & COMMAND_RIGHT) 
  {
    //Serial.println("COMMAND RIGHT");
      angle-=rotationSpeed;
  }
  return angle;
}
int changeOriginSpeed()
{
  if (command & COMMAND_UP) 
  {
   // Serial.println("COMMAND LEFT");
    originSpeed +=1;
  }
  else if (command & COMMAND_DOWN) 
  {
    //Serial.println("COMMAND RIGHT");
    originSpeed-=1;
  }
  return originSpeed;
}

int readJoyStickButton()
{
  button.loop(); // MUST call the loop() function first
  int bValue = button.getState();
  return bValue;
}
bool buttonPressed(){
  return button.isPressed();
}
bool buttonReleased(){
  return button.isReleased();
}
int readJoyStickX()
{
  int xValue = analogRead(VRX_PIN);
  return xValue;
}
int readJoyStickY()
{
  int yValue = analogRead(VRY_PIN);
  return yValue;
}
void resetCommand()
{
  command = COMMAND_NO; //resets commands
}
void setCursorSpeed(int speed)
{
  cursorSpeed = speed;
}
void runLoop()
{
  button.loop();
}