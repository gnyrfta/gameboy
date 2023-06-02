#include "GUI_Paint.h"
#include "LCD_Driver.h"
#include "joystick.h"


int x_center = 120;
int y_center = 160;
int radius = 1;
int ball_colour = BLACK;
int line_width = DOT_PIXEL_DFT;
int draw_fill = DOT_FILL_AROUND;

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

int yValuePong = 140;
int xValuePong = 0; 
int cursorXPong = 0;
int cursorYPong =0;
int cursorXOldPong = 0;
int cursorYOldPong = 0;


bool runProgramPong = true;

bool travellingRight{true};
bool travellingLeft{false};

void drawPadelOne(int yPosition);
void drawPadelTwo(int yPosition);

void runPong()
{
  int x_center_old = x_center;
  while(runProgramPong){
    if((x_center >= 232) && (y_center >= cursorYPong) && (y_center <=cursorYPong + 20))
    {
      travellingRight = false;
      travellingLeft = true;
    }
    else if((x_center <=2) && (travellingLeft))
    {
      travellingRight = true;
      travellingLeft = false;
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
    xValuePong = readJoyStickX();
    setCommand(xValuePong,yValuePong);//Sets command to left,right, up or down.
    cursorXOldPong = cursorXPong; //Used to overwrite former cursor position. Not used in etchaSketch, but necessary if you would want the cursor to be a cursor sometime.
    cursorYOldPong = cursorYPong;
    cursorXPong = changeCursorXValue(cursorXPong);//Increments x or y-value of cursor according to 'command'. 
    cursorYPong = changeCursorYValue(cursorYPong);
    drawPadelTwo(cursorYPong);
  }
}
void drawPadelOne(int yPosition)
{
  //first time, draw full rectangle, then only redraw pixels on bottom and top. 
  Paint_DrawRectangle(padelOneXstart, padelOneYstart, padelOneXend, padelOneYend, padelColour, line_width, draw_fill);
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