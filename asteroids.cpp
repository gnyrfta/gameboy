#include "GUI_Paint.h";
#include <math.h>;
#include "joystick.h";

//Used for all shapes:
static int line_width = DOT_PIXEL_DFT;    
static int draw_fill = DOT_FILL_AROUND;

//a and b are sides in the triangle that makes up the ship.
//A, B, C are the points in the triangle.
//R is the angle of the ship. Currently the angle is the angle from the y-axis, counted clockwise. 
//The orientation of the screen means that a starting angle of zero points straight downwards. 

static double a;
static double b;
static int Ax;
static int Ay;
static int Bx;
static int By;
static int Cx;
static int Cy;
static int R;

//To store previous position:
static int AxOld;
static int AyOld;
static int BxOld;
static int ByOld;
static int CxOld;
static int CyOld;

//Stores value from joystick in x-direction and y-directions.
static int xValueShip;
static int yValueShip;

//
static int xOrigin = 120;
static int yOrigin = 160;
static int originSpeedAsteroids = 0;

static int asteroidXOrigins[8];
static int asteroidYOrigins[8];
static int asteroidXVelocity[8];
static int asteroidYVelocity[8]; 

static int shotXCoordinates[8] = {0,0,0,0,0,0,0,0};//0 - no active shot.
static int shotYCoordinates[8] = {0,0,0,0,0,0,0,0};//
static int shotXCoordinatesOld[8] = {0,0,0,0,0,0,0,0};//0 - no active shot.
static int shotYCoordinatesOld[8] = {0,0,0,0,0,0,0,0};//
static int shotAngles[8] = {0,0,0,0,0,0,0,0};
static int activeShots = 0;

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

void positionAsteroids();
void setVelocityAsteroids();
void drawAsteroids();

void shoot();
void translationMotionShots(int angle, int shotnumber);
void drawShots();


void runAsteroids()
{
  setShipStartPos();
  drawShip();
  delay(3000);
  activeShots = 0;
  positionAsteroids();
  setVelocityAsteroids();
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
      shoot();
    }
    for (int i = 0;i<activeShots;i++)
    {
      translationMotionShots(shotAngles[i],i);
    }
    eraseShip();
    drawShip();
    drawShots();
    moveAsteroids();
    drawAsteroids();
  }
}
void setShipStartPos()
{
  //first test - a = b = c, determines ship shape.
  R = 0;
  a = 8;
  b = 8;
  Ax = 0;
  Ay = a;
  double bStartingAngle = -(150.0/180.0)*PI;
  Bx = b*sin(bStartingAngle);
  By = (int)b*cos(bStartingAngle);
  double cStartingAngle = bStartingAngle*(-1);
  Cx = (int)b*sin(cStartingAngle);
  Cy = (int)b*cos(cStartingAngle);
  shiftOrigin();
}
void drawShip()
{
  //From C to A:
  Paint_DrawLine(Cx, Cy, Ax, Ay, WHITE, line_width, draw_fill);
  //From A to B: 
  Paint_DrawLine(Ax, Ay, Bx, By, WHITE, line_width, draw_fill);
  // From B to C: 
  Paint_DrawLine(Bx, By, Cx, Cy, WHITE, line_width, draw_fill);
}
void eraseShip()
{
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
  if(xOrigin > 230)
  {
    xOrigin = 8;
  }
  if(yOrigin > 310)
  {
    yOrigin = 8;
  }
  if(xOrigin < 8)
  {
    xOrigin = 230;
  }    
  if(yOrigin < 8)
  {
    yOrigin = 310;
  }
}
void translationMotionShots(int angle, int shotnumber)
{
  int shotSpeed = 10;
  int L = shotSpeed;
  double degree = (double)angle;
  double radian = (degree/180.0)*PI;
  int xBoost = (int)L*sin(radian);
  int yBoost = (int)L*cos(radian);
  shotXCoordinatesOld[shotnumber] = shotXCoordinates[shotnumber];
  shotYCoordinatesOld[shotnumber] = shotYCoordinates[shotnumber];
  shotXCoordinates[shotnumber] += xBoost;
  shotYCoordinates[shotnumber] += yBoost;
  int i = shotnumber;
  if(shotXCoordinates[i] > 236)
  {
    activeShots--;
    shotXCoordinates[i]=0;
    shotYCoordinates[i]=0;
    shotXCoordinatesOld[i]=0;
    shotYCoordinatesOld[i]=0;
    shotAngles[i] = 0;
  }
  if(shotYCoordinates[i] > 316)
  {
    activeShots--;
    shotXCoordinates[i]=0;
    shotYCoordinates[i]=0;
    shotXCoordinatesOld[i]=0;
    shotYCoordinatesOld[i]=0;
    shotAngles[i] = 0;
  }
  if(shotXCoordinates[i] < 8)
  {
    activeShots--;
    shotXCoordinates[i]=0;
    shotYCoordinates[i]=0;
    shotXCoordinatesOld[i]=0;
    shotYCoordinatesOld[i]=0;
    shotAngles[i] = 0;
  }    
  if(shotYCoordinates[i] < 8)
  {
    activeShots--;
    shotXCoordinates[i]=0;
    shotYCoordinates[i]=0;
    shotXCoordinatesOld[i]=0;
    shotYCoordinatesOld[i]=0;
    shotAngles[i] = 0;
  }

}
void drawAsteroids()
{ 
  for(int i = 0;i<8;i++)
  {
    Paint_DrawPoint(asteroidXOriginsOld[i], asteroidYOriginsOld[i], BLACK,3,DOT_FILL_AROUND); 
    Paint_DrawPoint(asteroidXOrigins[i], asteroidYOrigins[i], WHITE,3,DOT_FILL_AROUND);    
  }
}
void drawShots()
{ 
  for(int i = 0;i<activeShots;i++)
  {
    Paint_DrawPoint(shotXCoordinatesOld[i], shotYCoordinatesOld[i], BLACK,1,DOT_FILL_AROUND); 
    Paint_DrawPoint(shotXCoordinates[i], shotYCoordinates[i], WHITE,1,DOT_FILL_AROUND);    
  }

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
      //Store angle.
  activeShots++;
  int i = activeShots;  
  shotAngles[i] = R;
  shotXCoordinates[i]=Ax;
  shotYCoordinates[i]=Ay;
  /*Serial.println("in shoot");
  Serial.println("active shots");
  Serial.println(activeShots);*/
    //translationMotionShots(angle)
//Ax Ay, use translation motion code. 
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
}
void positionAsteroids()
{
    randomSeed(analogRead(2));
  for(int i=0;i<8;i++)
  { 
    asteroidXOrigins[i] = random(10, 230);
    asteroidYOrigins[i] = random(10, 310);
    //Make sure asteroids don't start too close to the ship:
    while((asteroidXOrigins[i] > (xOrigin - 10)) && (asteroidXOrigins[i] < (xOrigin + 10)))
    {
      randomSeed(analogRead(2));
      asteroidXOrigins[i] = random(10,230);
    }
    while((asteroidYOrigins[i] > (yOrigin - 10)) && (asteroidYOrigins[i] < (yOrigin + 10)))
    {
      randomSeed(analogRead(2));
      asteroidYOrigins[i] = random(10,310);
    }
    Serial.println(asteroidXOrigins[i]);
  }
}
void setVelocityAsteroids()
{ 
    randomSeed(analogRead(2));
  for(int i=0;i<8;i++)
  { 
    asteroidXVelocity[i] = random(4);
    asteroidYVelocity[i] = random(4);
    //Make sure asteroids don't start too close to the ship: 
  }
}