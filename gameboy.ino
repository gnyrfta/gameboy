/*This code is based off the example LCD code that waveshare distributes with its 2.4 inch lcd-screen:
https://www.waveshare.com/wiki/2.4inch_LCD_Module#Arduino_hardware_connection
https://www.waveshare.com/wiki/2.4inch_LCD_Module#Arduino_software_description

The mandelbrot code and the functions for colouring the graph are based on Filips program:
https://github.com/FilipBerglund/Fractals
Filips program is for c++ and some of the libraries didn't work on arduino, so that makes some parts of the programs 
kind of different.

Complex is an arduino library for Complex math. 
In DEV_Config the baud rate is set to 115200 bit/second, so the serial monitor needs to be set to the same. 
*/

#ifndef FUN 
#define FUN

#include <Complex.h>
#include <ezButton.h>//necessary for reading pushdown on the button.
#include "GUI_Paint.h"
#include "LCD_Driver.h"
#include <math.h>        // std::abs

//#include "image.h
//#include <SPI.h>

using namespace std;
double nextOriginX{0};//Used to find a starting place for next mandelbrot drawing that is along one of the borders.
double tempNextOriginX{0};
double nextOriginY{0};
double tempNextOriginY{0};
double scale{1};//Used to scale inwards in the fractal. 

//For joystick
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

int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int bValue = 0; // To store value of the button

int command = COMMAND_NO;

//end for Joystick
  int cursorX{0};
  int cursorY{0};
  // put your setup code here, to run once:

   bool tryLoop{false};
   bool tryLoop2{false};

uint16_t changeThisLater[3];

void setup() 
{
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  button.setDebounceTime(50);
  Serial.println("Hello");
}

void loop() //Presents the menu and if 'Mandelbrot' is clicked it starts drawing the Mandelbrot set. 
{
  button.loop(); // MUST call the loop() function first
  bValue = button.getState();
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  command = COMMAND_NO; //resets commands

  readJoyStickOne(); //Sets command to left,right, up or down.

  // print command to serial and process command
  int cursorXOld = cursorX; //Used to overwrite former cursor position. 
  int cursorYOld = cursorY;

  changeCursorValue();//Increments x or y-value of cursor according to 'command'. 

  if (button.isPressed()) {
    Serial.println("The button is pressed");//If the button is pressed on the 'mandelbrot' text, launch the mandelbrot program. 
    Serial.print(cursorY);
    if(30>cursorY>10)
    {
    Paint_DrawString_EN(30, 10, "Mandelbrot", &Font24, BLUE, WHITE);//Show that the button has been pressed. 
    delay(200);
    } 
    else if(cursorY>30)
    {
      tryLoop2=true;
      Serial.println("tryLoop2 set to true");
    }
  }
  if (button.isReleased()) {
    Serial.println("The button is released");
    if(30>cursorY>10)
    {
    Paint_DrawString_EN(30, 10, "Mandelbrot", &Font24, WHITE, BLACK);
    tryLoop=true; //Launch Mandelbrot program. 
    }
    else if(60>cursorY>30)
    {
      tryLoop2=true;
      Serial.println("tryLoop2 set to true");
    }

  }
 // Paint_DrawRectangle(cursorXOld, cursorYOld, 17, 17, WHITE,  DOT_PIXEL_2X2,DRAW_FILL_FULL);
  Paint_DrawString_EN(30, 10, "Mandelbrot", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30, "Gradient", &Font24, WHITE, BLACK);

  if(!(cursorX==cursorXOld && cursorY==cursorYOld))
  {
  Paint_DrawString_EN(cursorXOld, cursorYOld, "+", &Font24, WHITE, WHITE);//Take away this and you have an etch-a-sketch. : ) 
  Paint_DrawString_EN(cursorX, cursorY, "+", &Font24, WHITE, RED);
  }
 
  if(tryLoop)
  {
  mandelbrot(nextOriginX,nextOriginY,scale);
  nextOriginX=tempNextOriginX;
  nextOriginY=tempNextOriginY;
  scale+=1.5;
  }
  if(tryLoop2)
  {
    HSVCycle();
  }
}

int iterations(Complex c) //Counts iterations until absolute value (modulus) of z is larger than 2. The more iterations, the brighter colour.
{
  int maxIter{100}; 
  Complex z(0,0);
  int iter{0};
  while (iter < maxIter && z.modulus() < 2)
  { 
    z = z*z+c;
    iter++;
  }
  if (iter == maxIter) return(0);
  else return(iter);
}

uint16_t fun(Complex c, double xd, double yd) //Sets a color based on amount of iterations before z is larger than 2. Stores a starting point for next draw.
{
  uint16_t arr[3];
  int iter{};
  iter = iterations(c);
  if(80<iter<90)
  {
    tempNextOriginX = xd; //Store a starting point for next draw that is part of the border region. 
    tempNextOriginY = yd;    
  }
  //Serial.println("hello");
  arr[0] = (uint16_t)iter*53;
  arr[1] = (uint16_t)iter*53;
  arr[2] = 0;
  convertHSVtoRGB(iter*3);
  return convertToUWORD(changeThisLater[0],changeThisLater[1],changeThisLater[2]);
}

uint16_t convertToUWORD(uint16_t red_value,uint16_t green_value,uint16_t blue_value) //Converts to a color format that Paint_setPixel understands.
{
uint16_t red_565 = map(red_value, 0, 255, 0, 31);

uint16_t green_565 = map(green_value, 0, 255, 0, 63);

uint16_t blue_565 = map(blue_value, 0, 255, 0, 31);
uint16_t rgb_565 = (red_565<<11)|(green_565<<5)|blue_565;
return rgb_565;
}
/*Loops through all pixels in the 240x320 screen. The first loop every pixel is projected onto a (-2:2, -2:2) coord syst.
After that the coord. syst is scaled and centered on an area where iterations were between 80 and 90 (close to not diverging - border region).
*/
void mandelbrot(double nextOriginX, double nextOriginY,double scale) 
{
  for(uint16_t x = 0; x<240;x++)
  {
    for(uint16_t y=0;y<320;y++)
    {
      double xd{x};
      double yd{y};
      xd = (4*xd / 240) -2;
      yd = (4*yd / 320) -2;
      xd = xd + nextOriginX;
      xd = xd/scale;
      yd = yd + nextOriginY;
      yd = yd/scale;
      Complex c(xd,yd);
      //Serial.print(c);
      Paint_SetPixel(x,y,fun(c,xd,yd));//This function works and 'convertToUWORD' works.
    }

  }
}

void readJoyStickOne() //Checks up, down, right, left.
{
if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (yValue < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS
}
void changeCursorValue()
{
    if (command & COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    if(cursorX > 0 )
    {
    cursorX-=3;
    }
  }

  if (command & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    if(cursorX < 240)
    {
    cursorX+=3;
    }
  }

  if (command & COMMAND_UP) {
    Serial.println("COMMAND UP");
    if(cursorY > 0)
    {https://www.rapidtables.com/convert/color/hsv-to-rgb.html
    cursorY-=3; 
    }   
  }

  if (command & COMMAND_DOWN) {
    Serial.println("COMMAND DOWN");
    if(cursorY < 320)
    {
    cursorY+=3;
    }
  }
}
 
 void convertHSVtoRGB(int H)
  {
    double h = (double)H;
    double s = h/60;
    //Serial.println(s);
    double X = 1-fabs(fmod(s,2)-1);
    //Serial.println(X);
    H = fmod(H,360);
    uint16_t x = (int)(X*255);
    Serial.println(x);
    if(H<60)
    {
      changeThisLater[0]= 255;
      changeThisLater[1]=x;
      changeThisLater[2]=0;
    }
    else if((60<=H)&&(H<120))
    {
      changeThisLater[0]=x;
      changeThisLater[1]=255;
      changeThisLater[2]=0;
    }
    else if((120<=H)&&(H<180))
    {
      changeThisLater[0]=0;
      changeThisLater[1]=255;
      changeThisLater[2]=x;
    }
    else if((180<=H)&&(H<240))
    {
      changeThisLater[0]=0;
      changeThisLater[1]=x;
      changeThisLater[2]=255;
    }
    else if((240<=H)&&(H<300))
    {
      changeThisLater[0]=x;
      changeThisLater[1]=0;
      changeThisLater[2]=255;
    }
    else if((300<=H)&&(H<360))
    {
      changeThisLater[0]=255;
      changeThisLater[1]=0;
      changeThisLater[2]=x;
    }
    Serial.print(changeThisLater[0]);
    Serial.print(changeThisLater[1]);
    Serial.print(changeThisLater[2]);
  }
  



 
void HSVCycle()
{
	int H = 0;
	while(true)
		{
			for(uint16_t x = 0; x<240;x++)
				{
					for(uint16_t y=0;y<320;y++)
						{
							double xd{x};
							double yd{y};
							Serial.print("should be drawing colours");
							convertHSVtoRGB(H);
							Paint_SetPixel(x,y,convertToUWORD(changeThisLater[0],changeThisLater[1],changeThisLater[2]));//This function works and 'convertToUWORD' works.

						}
          H++;
				}

		}
}
#endif
