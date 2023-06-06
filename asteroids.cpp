#include "GUI_Paint.h";
#include <math.h>
//Used for all shapes:
static int line_width = DOT_PIXEL_DFT;    
static int draw_fill = DOT_FILL_AROUND;

static double a;
static double b;
static int Ax;
static int Ay;
static int Bx;
static int By;
static int Cx;
static int Cy;
static int R;

void setShipStartPos();
void shiftOrigin();
void drawShip();
void rotateShip();

void runAsteroids()
{
  setShipStartPos();
  drawShip();
  delay(3000);
  while(true)
  {
    rotateShip();
    drawShip();
  }
}
void setShipStartPos()
{
  Serial.println("in setShipStartPos()");
  //first test - a = b = c, determines ship shape.
  R = 0;
  a = 15;
  b = 15;
  Ax = 0;
  Ay = a;
  double bStartingAngle = -(150.0/180.0)*PI;
  Bx = b*sin(bStartingAngle);
  Serial.println(sin(bStartingAngle));
  By = (int)b*cos(bStartingAngle);
  Serial.println(cos(bStartingAngle));
  double cStartingAngle = bStartingAngle*(-1);
  Cx = (int)b*sin(cStartingAngle);
  Cy = (int)b*cos(cStartingAngle);
  shiftOrigin();
}
void drawShip()
{
  Serial.println("In drawShip");
  //From C to A:
  Paint_DrawLine(Cx, Cy, Ax, Ay, BLACK, line_width, draw_fill);
  //From A to B: 
  Paint_DrawLine(Ax, Ay, Bx, By, BLACK, line_width, draw_fill);
  // From B to C: 
  Paint_DrawLine(Bx, By, Cx, Cy, BLACK, line_width, draw_fill);
  Serial.println(Bx);
  Serial.println(By);
  Serial.println(Cx);
  Serial.println(Cy);
}
void shiftOrigin()
{
  Ax += 120;
  Ay += 160;
  Bx += 120;
  By += 160;
  Cx += 120;
  Cy += 160;
}
void drawAsteroid(int origin)
{

}
void moveShip()
{

}
void rotateShip()
{ 
  R+=2;
  double degree = (double)R;
  double radian = (degree/180.0)*PI;
  Ax = a*sin(radian);
  Ay = a*cos(radian);
  double bStartingAngle = -(150.0/180.0)*PI;
  Bx = b*sin(radian-bStartingAngle);
  By = (int)b*cos(radian-bStartingAngle);
  Cx = (int)b*sin(radian + bStartingAngle);
  Cy = (int)b*cos(radian + bStartingAngle);
  shiftOrigin();
}
void shoot()
{

}
void boost()
{

}

