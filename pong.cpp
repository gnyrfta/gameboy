#include "GUI_Paint.h"
#include "LCD_Driver.h"
#include "joystick.h"

// Ball values
int x_center = 120;
int y_center = 160;
int radius = 1;
int ball_colour = BLACK;

//Used for all shapes:
int line_width = DOT_PIXEL_DFT;
int draw_fill = DOT_FILL_AROUND;

//Padel values
int padelOneXstart = 0;
int padelOneXend = 8;
int padelOneYstart = 140;
int padelOneYend = 180;

int padelTwoXstart = 232;
int padelTwoXend = 240;
int padelTwoYstart = 140;
int padelTwoYend = 180;

int padelColour = BLACK;

int background = WHITE;

int yValuePong = 0;//reads the potentiometer value from the joystick in the y-direction.
int xValuePong = 0; //reads the potentiometer value from the joystick in the x-direction. Only used because joystick function wants both x and y values.
int cursorYPong = 0; //Position of cursor in the y-direction.
int cursorYOldPong = 0;//Previous position of cursor in the y-direction.

bool travellingRight{true};
bool travellingLeft{false};

bool runProgramPong = true;

void drawPadelOne(int yPosition);
void drawPadelTwo(int yPosition);

void runPong()
{
  int x_center_old = x_center;
  int storeValueRightPadel=padelTwoYstart;
  int storeValueLeftPadel=padelTwoXstart;

  while(runProgramPong){
    if((x_center >= 232) && (y_center >= cursorYPong) && (y_center <=cursorYPong + 20))
    {
      travellingRight = false;
      travellingLeft = true;
      storeValueRightPadel = cursorYPong;
      cursorYPong = storeValueLeftPadel;
    }
    else if((x_center <=2) && (travellingLeft))
    {
      travellingRight = true;
      travellingLeft = false;
      storeValueLeftPadel = cursorYPong;
      cursorYPong = storeValueRightPadel;
    }
    if(travellingRight)
    {
    x_center_old = x_center;
    x_center+=2;
    }
    else if(travellingLeft)
    {
    x_center_old = x_center;
    x_center-=2;      
    }
    
    Paint_DrawCircle(x_center_old,y_center, radius, background, line_width, draw_fill);
    Paint_DrawCircle(x_center,y_center, radius, ball_colour, line_width, draw_fill);

    resetCommand();//resets the joystick command variable to zero.
    yValuePong = readJoyStickY();//reads the potentiometer value from the joystick in the y-direction and gives it as an int.
    setCommand(xValuePong,yValuePong);//Sets command to left,right, up or down.
    cursorYOldPong = cursorYPong;
    cursorYPong = changeCursorYValue(cursorYPong);
    if(travellingLeft)
    {
      drawPadelOne(cursorYPong);
    } 
    if(travellingRight)
    {
      drawPadelTwo(cursorYPong);
    }
  }    
  
}
void drawPadelOne(int yPosition)
{
  if(yPosition > cursorYOldPong)
  {
    Paint_DrawRectangle(padelOneXstart, cursorYOldPong, padelOneXend, yPosition, background, line_width, draw_fill);
    Paint_DrawRectangle(padelOneXstart, yPosition, padelOneXend, yPosition + 20, padelColour, line_width, draw_fill);
    Serial.println("should have been drawn.");
  }
  else if(yPosition <= cursorYOldPong)
  {
    Paint_DrawRectangle(padelOneXstart,yPosition + 20, padelOneXend,  cursorYOldPong + 20, background, line_width, draw_fill);
    Paint_DrawRectangle(padelOneXstart, yPosition, padelOneXend, yPosition + 20, padelColour, line_width, draw_fill); 
    Serial.println("should have been drawn 2.");   
  }
}
void drawPadelTwo(int yPosition)
{
  if(yPosition > cursorYOldPong)
  {
    Paint_DrawRectangle(padelTwoXstart, cursorYOldPong, padelTwoXend, yPosition, background, line_width, draw_fill);
    Paint_DrawRectangle(padelTwoXstart, yPosition, padelTwoXend, yPosition + 20, padelColour, line_width, draw_fill);
  }
  else if(yPosition <= cursorYOldPong)
  {
    Paint_DrawRectangle(padelTwoXstart,yPosition + 20, padelTwoXend,  cursorYOldPong + 20, background, line_width, draw_fill);
    Paint_DrawRectangle(padelTwoXstart, yPosition, padelTwoXend, yPosition + 20, padelColour, line_width, draw_fill);    
  }
}