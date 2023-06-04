#include "GUI_Paint.h"
#include "LCD_Driver.h"
#include "joystick.h"
#include <math.h>

using namespace std;
// Ball values
int x_center = 120;
int y_center = 160;
int radius = 2;
int ball_colour = BLACK;

//Used for all shapes:
int line_width = DOT_PIXEL_DFT;
int draw_fill = DOT_FILL_AROUND;

//Padel values
int padelOneXstart = 0;
int padelOneXend = 4;
int padelOneYstart = 140;
int padelOneYend = 180;

int padelTwoXstart = 236;
int padelTwoXend = 240;
int padelTwoYstart = 140;
int padelTwoYend = 180;

int padelColour = BLACK;

int background = WHITE;

int yValuePong = 0;//reads the potentiometer value from the joystick in the y-direction.
int xValuePong = 0; //reads the potentiometer value from the joystick in the x-direction. Only used because joystick function wants both x and y values.
int cursorYPong = 0; //Position of cursor in the y-direction.
int cursorYOldPong = 0;//Previous position of cursor in the y-direction.
//int cursorSpeed = 3;

bool travellingRight{true};
bool travellingLeft{false};

bool runProgramPong = true;

void drawPadelOne(int yPosition);
void drawPadelTwo(int yPosition);
void drawStartPosition(int yStart);
int determineAngle(int yBall, int yPadel);
void moveBallLeft(int angle);
void moveBallRight(int angle);

char* toString(int number);
char numeralsToString(int numeral);

void runPong()
{
  runProgramPong=true;
  travellingRight=true;
  travellingLeft=false;
  y_center=160;
  x_center=0;
  int x_center_old = x_center;
  int y_center_old = y_center;
  int storeValueRightPadel=padelTwoYstart;
  int storeValueLeftPadel=padelTwoXstart;
  int angle{0};

  int score =0;
  const char * dude = toString(39);
  Serial.print("this is ");
  Serial.print(dude);




  drawStartPosition(padelOneYstart);
  while(runProgramPong){
    if(x_center >= 232 ) //collision right padel
    {
      if((y_center >= cursorYPong) && (y_center <=cursorYPong + 20))
      {
      Serial.println("Collision!");
      Serial.println(y_center);
      Serial.println(cursorYPong);
      travellingRight = false;
      travellingLeft = true;
      storeValueRightPadel = cursorYPong;
      cursorYPong = storeValueLeftPadel;
      angle = determineAngle(y_center, cursorYPong);
      score++;
      }
      else if(travellingRight)
      {
        Paint_DrawString_EN(30, 10, "Game Over", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(30, 30, "Score: ", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(140, 30, toString(score), &Font24, WHITE, BLACK);

        delay(3000);
        runProgramPong = false;
      }
    }
    else if(x_center <=4)//collision left padel
    {
      if((y_center >= cursorYPong) && (y_center <=cursorYPong + 20))
      {
      travellingRight = true;
      travellingLeft = false;
      storeValueLeftPadel = cursorYPong;
      cursorYPong = storeValueRightPadel;
      Serial.println("Collision!");
      Serial.println(y_center);
      Serial.println(cursorYPong);
      score++;
      }
      else if(travellingLeft)
      {
        
        Paint_DrawString_EN(30, 10, "Game Over", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(30, 30, "Score: ", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(140, 30, toString(score), &Font24, WHITE, BLACK);
        delay(3000);
        runProgramPong = false;
      }
    }
    else
    {
      //Serial.println("There should not have been a collision.");
    }
    if((y_center<=2)||(y_center>=318))
    {
      angle = angle*-1;      
    }
    if(travellingRight)
    {
    x_center_old = x_center;
    y_center_old = y_center;
    moveBallRight(angle);
    }
    else if(travellingLeft)
    {
      x_center_old = x_center;
      y_center_old = y_center;
      moveBallLeft(angle);
    }
    
    Paint_DrawCircle(x_center_old,y_center_old, radius, background, line_width, draw_fill);
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
  }
  else if(yPosition <= cursorYOldPong)
  {
    Paint_DrawRectangle(padelOneXstart,yPosition + 20, padelOneXend,  cursorYOldPong + 20, background, line_width, draw_fill);
    Paint_DrawRectangle(padelOneXstart, yPosition, padelOneXend, yPosition + 20, padelColour, line_width, draw_fill); 
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
void drawStartPosition(int yPosition)
{
  Paint_DrawRectangle(padelOneXstart, yPosition, padelOneXend, yPosition + 20, padelColour, line_width, draw_fill);
  Paint_DrawRectangle(padelTwoXstart, yPosition, padelTwoXend, yPosition + 20, padelColour, line_width, draw_fill);
}
int determineAngle(int yBall, int yPadel)
{
  int centerPadel = yPadel + 10;
  bool upperSection{false};
  bool lowerSection{false};
  int returnAngle{0};

  if((yBall - centerPadel)>0)
  {
    lowerSection = true;
  }
  else if((yBall - centerPadel) <=0 )
  {
    upperSection = true;
  }

  int distanceFromCenter = abs(yBall-centerPadel);  
  if(distanceFromCenter <=3)
  {
    returnAngle = 0;
    //horizontal speed.
  }
  else if((distanceFromCenter > 3) && (distanceFromCenter <= 5))
  {
      returnAngle = 27;
    //x + 2, y + 1
  }
  else if((distanceFromCenter > 5) && (distanceFromCenter <=8))
  {
      returnAngle = 45;  
    //x + 2 y + 2
  }
  else if(distanceFromCenter > 8)
  {
     returnAngle = 63;
  }   
    //y + 2, x + 1

  if(lowerSection)
  {
    returnAngle = returnAngle*(-1);
  } 
  return returnAngle;
}
void moveBallLeft(int angle)
{
  if(angle == 0)
  {
    x_center -=2;
  }
  else if(angle == 27)
  {
    x_center -=2;
    y_center-=1;    
  }
  else if(angle == -27)
  {
    x_center-=2;
    y_center+=1;
  }
  else if(angle == 45)
  {
    x_center-=2;
    y_center-=2;
  }
  else if(angle == -45)
  {
    x_center -=2;
    y_center+=2;
  }
  else if(angle == 63)
  {
    x_center-=1;
    y_center-=2;
  }
  else if(angle == -63)
  {
    x_center -=1;
    y_center+=2;
  }
}
void moveBallRight(int angle)
{
  if(angle == 0)
  {
    x_center +=2;
  }
  else if(angle == 27)
  {
    x_center +=2;
    y_center-=1;    
  }
  else if(angle == -27)
  {
    x_center+=2;
    y_center+=1;
  }
  else if(angle == 45)
  {
    x_center+=2;
    y_center-=2;
  }
  else if(angle == -45)
  {
    x_center +=2;
    y_center+=2;
  }
  else if(angle == 63)
  {
    x_center+=1;
    y_center-=2;
  }
  else if(angle == -63)
  {
    x_center +=1;
    y_center+=2;
  }
}
char* toString(int number)
{
  /*Handles numbers up to 999*/
  int hundred = number/100;
  Serial.println("Should be 0.");
  Serial.println(hundred);
  int temp = number - hundred*100;
  Serial.println("temp:");
  Serial.println(temp);
  int ten = temp/10;
  int one = temp - ten*10;
  Serial.println("hundred: ");
  Serial.println(hundred);
  Serial.println("ten: ");
  Serial.println(ten);
  Serial.println("one: ");
  Serial.println(one);

  static char returnValue[4];

  returnValue[0]=numeralsToString(hundred);
  returnValue[1]=numeralsToString(ten);
  returnValue[2]=numeralsToString(one);
  returnValue[3]='\0';//char arrays in c++ need to be null-terminated. Which is something I don't understand, but oh well. Without it there is a square rectangle outputed. 
  return returnValue;
}
char numeralsToString(int numeral)
{

  char returnChar;
  if(numeral == 0)
  {
    returnChar = '0';
  } 
  else if(numeral == 1)
  {
    returnChar = '1';
  }
  else if(numeral == 2)
  {
    returnChar = '2';
  }
  else if(numeral == 3)
  { 
    returnChar = '3';
  } 
  else if(numeral == 4)
  {
    returnChar = '4';
  }
  else if(numeral == 5)
  {
    returnChar = '5';
  }
  else if(numeral == 6)
  {
    returnChar = '6';
  }
  else if(numeral == 7)
  {
    returnChar = '7';
  } 
  else if(numeral == 8)
  {
    returnChar = '8';
  }
  else if(numeral == 9)
  {
    returnChar = '9';
  }
  else
  {
    returnChar = ' ';
  }
  return returnChar;
} 