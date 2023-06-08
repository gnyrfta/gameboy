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

static int AxOld;
static int AyOld;
static int BxOld;
static int ByOld;
static int CxOld;
static int CyOld;

static int asteroidXOrigins[8] = {0,50,100,110,10,200,228,230};
static int asteroidYOrigins[8] = {0,50,100,110,10,200,229,230};
static int asteroidXVelocity[8] = {3,2,1,0,2,1,3,2};
static int asteroidYVelocity[8] = {0,2,1,3,2,1,1,2}; 

static int asteroidXOriginsOld[8];
static int asteroidYOriginsOld[8];

void setShipStartPos();
void shiftOrigin();
void drawShip();
void eraseShip();

void rotateShip();
void moveAsteroids();

void drawAsteroids();

void runAsteroids()
{
  setShipStartPos();
  drawShip();
  delay(3000);
  while(true)
  {
    AxOld = Ax;
    AyOld = Ay;
    BxOld = Bx;
    ByOld = By;
    CxOld = Cx;
    CyOld = Cy;    
    rotateShip();
    eraseShip();
    drawShip();
    moveAsteroids();
    drawAsteroids();
  }
  Serial.println("Mysteriously escaped");
}
void setShipStartPos()
{
  Serial.println("in setShipStartPos()");
  //first test - a = b = c, determines ship shape.
  R = 0;
  a = 8;
  b = 8;
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
  Paint_DrawLine(Cx, Cy, Ax, Ay, WHITE, line_width, draw_fill);
  //From A to B: 
  Paint_DrawLine(Ax, Ay, Bx, By, WHITE, line_width, draw_fill);
  // From B to C: 
  Paint_DrawLine(Bx, By, Cx, Cy, WHITE, line_width, draw_fill);
  Serial.println(Bx);
  Serial.println(By);
  Serial.println(Cx);
  Serial.println(Cy);
}
void eraseShip()
{
  Serial.println("In eraseShip");
  //From C to A:
  Paint_DrawLine(CxOld, CyOld, AxOld, AyOld, BLACK, line_width, 0);
  //From A to B: 
  Paint_DrawLine(AxOld, AyOld, BxOld, ByOld, BLACK, line_width, 0);
  // From B to C: 
  Paint_DrawLine(BxOld, ByOld, CxOld, CyOld, BLACK, line_width, 0);
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
void drawAsteroids()
{ 
  for(int i = 0;i<8;i++)
  {
    //Paint_DrawCircle(asteroidXOrigins[i],asteroidYOrigins[i],5,WHITE,line_width,DRAW_FILL_EMPTY);
    //Paint_DrawString_EN(asteroidXOrigins[i], asteroidYOrigins[i], ".", &Font16, BLACK, WHITE); 
    Paint_DrawPoint(asteroidXOriginsOld[i], asteroidYOriginsOld[i], BLACK,3,DOT_FILL_AROUND); 
    Paint_DrawPoint(asteroidXOrigins[i], asteroidYOrigins[i], WHITE,3,DOT_FILL_AROUND);    
  }
  Serial.println("In drawAsteroids");
  //Paint_DrawCircle()
}
void moveShip()
{

}
void rotateShip()
{ 
  R+=3;
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
void moveAsteroids()
{
  
  for(int i=0;i<8;i++)
  {
    asteroidXOriginsOld[i] = asteroidXOrigins[i];
    asteroidYOriginsOld[i] = asteroidYOrigins[i];
    asteroidXOrigins[i]+=asteroidXVelocity[i];
    asteroidYOrigins[i]+=asteroidYVelocity[i];
    if(asteroidXOrigins[i]>240)
    {
      asteroidXOrigins[i]=0;
    }
    if(asteroidYOrigins[i]>320)
    {
      asteroidYOrigins[i]=0;
    }
  }
  Serial.println("In moveAsteroids");
}