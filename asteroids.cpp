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
//Ship specs:
static int xOrigin{120};
static int yOrigin{160};
static int speedShip{0};

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

//Stores value from joystick in x-direction and y-directions.
static int xValueShip;
static int yValueShip;



//Asteroid specs: 
static int asteroidXOrigins[8];
static int asteroidYOrigins[8];
static int asteroidXVelocity[8];
static int asteroidYVelocity[8]; 
static int asteroidXOriginsOld[8];
static int asteroidYOriginsOld[8];

//Shot specs:
static int shotXCoordinates[8] = {0,0,0,0,0,0,0,0};//0 - no active shot.
static int shotYCoordinates[8] = {0,0,0,0,0,0,0,0};//
static int shotXCoordinatesOld[8] = {0,0,0,0,0,0,0,0};//0 - no active shot.
static int shotYCoordinatesOld[8] = {0,0,0,0,0,0,0,0};//
static int shotAngles[8] = {0,0,0,0,0,0,0,0};
static int activeShots = 0;

//Input function:
void readJoyStickAsteroids(); //Asteroids here refers to the game, not to the asteroids.

//Ship functions: 
void setShipStartPos();
void rotateShip();//Sets ship to current rotation angle. If joystick 'left' or 'right' increments angle.
void translationMotion();//Updates the unfortunately named xOrigin and yOrigin according to current ship speed and angle.
void shiftOrigin();//Updates position of points A,B and C in the ships triangle using the new values of xOrigin and yOrigin. The 'logic' behind calling them xOrigin and yOrigin is that they are the origin in the reference 
//in which the points A,B and C always would have the same x and y-values, i.e. the ref. frame travelling with the ship. 
void drawShip();
void eraseShip();

//Asteroid functions:
void positionAsteroids();
void setVelocityAsteroids();
void moveAsteroids();
void drawAsteroids();

//Shot functions: 
void shoot();
void translationMotionShots(int angle, int shotnumber);//increments position of shot #shotnumber according to angle
void drawShots();
void eraseShot(int shotnumber);

void runAsteroids()
{
  delay(4000); //to avoid buttonpress being registered immediately. 
  setShipStartPos();
  drawShip();
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
      shoot();
    }
    if(activeShots!=0)
    {
      for (int i = 0;i<activeShots;i++)
      {
        translationMotionShots(shotAngles[i],i);
      }
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
  //All angles are measured clockwise from the y-axis. Should some time change this to conterclockwise from the x-axis since thats what's used in the unit circle. 
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
  //As the 'origin' of the triangle moves the ship the points need to be repositioned, since they are first always calculated as if the origin was zero.
  Ax += xOrigin;
  Ay += yOrigin;
  Bx += xOrigin;
  By += yOrigin;
  Cx += xOrigin;
  Cy += yOrigin;
}
void translationMotion() //Calculates how far the ship should move each loop. 
{
  int L = speedShip;
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
  int i = shotnumber;
  Serial.println("shotnumber");
  Serial.println(shotnumber);
  //int temp2 = shotnumber-1;
  Serial.println("Tr");
  for(int temp=0;temp<8;temp++)
  {
  Serial.println(shotXCoordinates[temp]);
  Serial.println(shotYCoordinates[temp]);
  }
  double degree = (double)angle;
  double radian = (degree/180.0)*PI;
  int xBoost = (int)L*sin(radian);
  int yBoost = (int)L*cos(radian);
  shotXCoordinatesOld[i] = shotXCoordinates[i];
  shotYCoordinatesOld[i] = shotYCoordinates[i];
  shotXCoordinates[i] += xBoost;
  shotYCoordinates[i] += yBoost;

  if(shotXCoordinates[i] > 236)
  {
    eraseShot(i);
    Serial.print("Active shots:");
    Serial.println(activeShots);
    Serial.println("one");
  }
  else if(shotYCoordinates[i] > 316)
  {
    eraseShot(i);
    Serial.print("Active shots:");
    Serial.println(activeShots);
    Serial.println("two");
  }
  else if(shotXCoordinates[i] < 8)
  {
    eraseShot(i);
    Serial.print("Active shots:");
    Serial.println(activeShots);
    Serial.println("three");
  }    
  else if(shotYCoordinates[i] < 8)
  {
    eraseShot(i);
    Serial.print("Active shots:");
    Serial.println(activeShots);
    Serial.println("four");
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
  //Serial.println("in drawShots");
  //Serial.print("Active shots: ");
  //Serial.print(activeShots);
  if(activeShots != 0)
  {
    for(int i = 0;i<activeShots;i++)
    {
      Paint_DrawPoint(shotXCoordinatesOld[i-1], shotYCoordinatesOld[i-1], BLACK,1,DOT_FILL_AROUND); 
      Paint_DrawPoint(shotXCoordinates[i-1], shotYCoordinates[i-1], WHITE,1,DOT_FILL_AROUND);
    // Serial.println("Have drawn shots");    
    }
  }
 // Serial.println("Exiting drawShots");
}
void eraseShot(int i)
{
    Paint_DrawPoint(shotXCoordinatesOld[i], shotYCoordinatesOld[i], BLACK,1,DOT_FILL_AROUND);
    Paint_DrawPoint(shotXCoordinates[i], shotYCoordinates[i], BLACK,1,DOT_FILL_AROUND); 
    activeShots--;
    shotXCoordinates[i]=0;
    shotYCoordinates[i]=0;
    shotXCoordinatesOld[i]=0;
    shotYCoordinatesOld[i]=0;
    shotAngles[i] = 0;   
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
  speedShip = changeOriginSpeed();
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

  if(activeShots < 8)
  {
  activeShots++;
  //Serial.println(activeShots);
  int i = activeShots;  
  shotAngles[i-1] = R;
  shotXCoordinates[i-1]=Ax;
  shotYCoordinates[i-1]=Ay;
  Serial.println("sh");
  for(int temp=0;temp<8;temp++)
  {
  Serial.println(shotXCoordinates[temp]);
  Serial.println(shotYCoordinates[temp]);
  }
 /* Serial.print("This is i: ");
  Serial.println(i);
  Serial.println(shotAngles[i-1]);
  Serial.println(shotXCoordinates[i-1]);
  Serial.println(shotYCoordinates[i-1]);
*/  }

  //Serial.println("Exiting shoot");    
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
    //Serial.println(asteroidXOrigins[i]);
  }
}
void setVelocityAsteroids()
{ 
    randomSeed(analogRead(2));
  for(int i=0;i<8;i++)
  { 
    asteroidXVelocity[i] = random(4);
    asteroidYVelocity[i] = random(4);
  }
}