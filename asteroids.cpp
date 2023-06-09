#include "GUI_Paint.h";
#include <math.h>;
#include "joystick.h";

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

static int xValueShip;
static int yValueShip;
static int cursorXShip;
static int cursorYShip;
static int cursorXOldShip;
static int cursorYOldShip;

static int xOrigin = 120;
static int yOrigin = 160;
static int originSpeedAsteroids = 0;

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
void moveShip();
void rotateShip();
void moveAsteroids();
void readJoyStickAsteroids();
void translationMotion();

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
    readJoyStickAsteroids();
    translationMotion();
    rotateShip(); //Function only rotates if R has changed. 
    shiftOrigin();
    if(buttonPressed())
    {
      Serial.println("button pressed");
     // We want to shoot here.
    }
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
  //Serial.println(sin(bStartingAngle));
  By = (int)b*cos(bStartingAngle);
  //Serial.println(cos(bStartingAngle));
  double cStartingAngle = bStartingAngle*(-1);
  Cx = (int)b*sin(cStartingAngle);
  Cy = (int)b*cos(cStartingAngle);
  shiftOrigin();
}
void drawShip()
{
  //Serial.println("In drawShip");
  //From C to A:
  Paint_DrawLine(Cx, Cy, Ax, Ay, WHITE, line_width, draw_fill);
  //From A to B: 
  Paint_DrawLine(Ax, Ay, Bx, By, WHITE, line_width, draw_fill);
  // From B to C: 
  Paint_DrawLine(Bx, By, Cx, Cy, WHITE, line_width, draw_fill);
 // Serial.println(Bx);
 // Serial.println(By);
 // Serial.println(Cx);
 // Serial.println(Cy);
}
void eraseShip()
{
 // Serial.println("In eraseShip");
  //From C to A:
  Paint_DrawLine(CxOld, CyOld, AxOld, AyOld, BLACK, line_width, 0);
  //From A to B: 
  Paint_DrawLine(AxOld, AyOld, BxOld, ByOld, BLACK, line_width, 0);
  // From B to C: 
  Paint_DrawLine(BxOld, ByOld, CxOld, CyOld, BLACK, line_width, 0);
}
void shiftOrigin()
{
  Ax += xOrigin;
  Ay += yOrigin;
  Bx += xOrigin;
  By += yOrigin;
  Cx += xOrigin;
  Cy += yOrigin;
}
void translationMotion() 
{
  int L = originSpeedAsteroids;
  double degree = (double)R;
  double radian = (degree/180.0)*PI;
  int xBoost = (int)L*sin(radian);
  int yBoost = (int)L*cos(radian);
  xOrigin += xBoost;
  yOrigin += yBoost;
 
  Serial.println("xBoost: ");
  Serial.println(xBoost);
  Serial.println("yBoost: ");
  Serial.println(yBoost);
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
  //Serial.println("In drawAsteroids");
  //Paint_DrawCircle()
}
void readJoyStickAsteroids()
{
  //The ship has a constant drift velocity until boosted.
  //Checking for command to turn or to boost.
  resetCommand();//resets the joystick command variable to zero.
  xValueShip = readJoyStickX();//reads the potentiometer value from the joystick in the x-direction and gives it as an int.
  yValueShip = readJoyStickY();//reads the potentiometer value from the joystick in the y-direction and gives it as an int.
  setCommand(xValueShip,yValueShip);//Sets command to left,right, up or down.
  R = changeAngle();
  originSpeedAsteroids = changeOriginSpeed();
  readJoyStickButton();

  //cursorXOldShip = cursorXShip; //Used to overwrite former cursor position. Not used in etchaSketch, but necessary if you would want the cursor to be a cursor sometime.
  //cursorYOldShip = cursorYShip;
  //cursorXShip = changeCursorXValue(cursorXShip);//Increments x or y-value of cursor according to 'command'. 
  //cursorYShip = changeCursorYValue(cursorYShip);
} 
void rotateShip()
{ 
  double degree = (double)R;
  double radian = (degree/180.0)*PI;
  Ax = a*sin(radian);
  Ay = a*cos(radian);
  double bStartingAngle = -(150.0/180.0)*PI;
  Bx = b*sin(radian-bStartingAngle);
  By = (int)b*cos(radian-bStartingAngle);
  Cx = (int)b*sin(radian + bStartingAngle);
  Cy = (int)b*cos(radian + bStartingAngle);
}
void shoot()
{
//Ax Ay, use translation motion code. 
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
 // Serial.println("In moveAsteroids");
}