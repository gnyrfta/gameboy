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
#include "GUI_Paint.h"
#include "LCD_Driver.h"
#include <math.h>        // std::abs
//#include "mandelbrot.h"
#include "colourconversions.h"
#include "joystick.h"
#include "etchasketch.h"
#include "pong.h"
#include "asteroids.h"
//Neopixel stuffs
#include <Adafruit_NeoPixel.h>
#include "pixelmenu.h"
#define LED_PIN 4
#define LED_COUNT 74
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

using namespace std;

int xValue = 0 ; // To store value of the X axis - it would make sense to keep these in joystick.cpp
int yValue = 0 ; // To store value of the Y axis
int bValue = 0; // To store value of the button

int cursorX{0};
int cursorY{0};
int cursorXOld{0};
int cursorYOld{0};

//bool drawMandelbrot{false};
bool playAsteroids{false};
bool etchASketch{false};
bool playPong{false};
bool drawGradient{false};
bool pixelsOn{false};


void setup() 
{
  Config_Init();
  LCD_Init();
  joyStickInit();
  drawStartMenu();
  //Neopixel stuffs:
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() //Presents the menu and if 'Mandelbrot' is clicked it starts drawing the Mandelbrot set. 
{
  resetCommand();//resets the joystick command variable to zero.
  xValue = readJoyStickX();//reads the potentiometer value from the joystick in the x-direction and gives it as an int.
  yValue = readJoyStickY();//reads the potentiometer value from the joystick in the y-direction and gives it as an int.
  setCommand(xValue,yValue);//Sets command to left,right, up or down.

  cursorXOld = cursorX; //Used to overwrite former cursor position. 
  cursorYOld = cursorY;
  cursorX = changeCursorXValue(cursorX);//Increments x or y-value of cursor according to 'command'. 
  cursorY = changeCursorYValue(cursorY);
  bValue = readJoyStickButton();  //bvalue not used currently.

  if (buttonPressed()) 
  {
    if(30>cursorY)
    {
      Paint_DrawString_EN(10, 10, "Etch a Sketch", &Font24, BLUE, WHITE);//Show that the button has been pressed. 
      delay(200);
      etchASketch=true;
    } 
    else if((cursorY>30) && (cursorY<50))
    {
      Paint_DrawString_EN(30,30, "Pong", &Font24, BLUE, WHITE);
      delay(200);
      playPong=true;
    }
    else if((cursorY>50) && (cursorY<70))
    {
      Paint_DrawString_EN(30,50, "Asteroids", &Font24, BLUE, WHITE);
      delay(500);
      playAsteroids=true;
    }
    /*else if((cursorY>70) && (cursorY<90))
    {
      Paint_DrawString_EN(30, 70, "Mandelbrot", &Font24, BLUE, WHITE);
      delay(200);
      drawMandelbrot=true;
    }*/
    else if((cursorY>90) && (cursorY<110))
    {
      Paint_DrawString_EN(30,90, "Neopixels", &Font24, BLUE, WHITE);
      delay(200);
      if(!pixelsOn)
      {
      pixelsOn=true;
      strip.setBrightness(50);
      delay(200);
      }
      else if(pixelsOn)
      {
        pixelsOn=false;
        Paint_DrawString_EN(30,90, "Neopixels", &Font24, WHITE, BLACK);
        colorWipe(strip.Color(  0,   0, 0), 0); // Black
        delay(500);
      }
    }
  }
  if(!(cursorX==cursorXOld && cursorY==cursorYOld)) // If the cursor has moved.
  {
     if((30>cursorY) && (cursorY>10))
     {
       if(!((30>cursorYOld) && (cursorYOld>10)))
        {
         // Paint_DrawString_EN(30, 10, "Mandelbrot", &Font24, WHITE, BLUE);
         // Paint_DrawString_EN(30,30, "Gradient", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(10,10,"Etch a sketch", &Font24, WHITE, BLUE);
          Paint_DrawString_EN(30,30,"Pong", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,50,"Asteroids", &Font24, WHITE, BLACK);
         // Paint_DrawString_EN(30, 70, "Mandelbrot", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,90, "Neopixels", &Font24, WHITE, BLACK);



        }
     }
     else if((50>cursorY) && (cursorY>30))
     {
      if(!((50>cursorYOld) && (cursorYOld>30)))
      {
          Paint_DrawString_EN(10,10,"Etch a sketch", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,30,"Pong", &Font24, WHITE, BLUE);
          Paint_DrawString_EN(30,50,"Asteroids", &Font24, WHITE, BLACK);
        //  Paint_DrawString_EN(30, 70, "Mandelbrot", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,90, "Neopixels", &Font24, WHITE, BLACK);
      }
     }
      else if((70>cursorY) && (cursorY>50))
     {
      if(!((70>cursorYOld) && (cursorYOld>50)))
      {
          Paint_DrawString_EN(10,10,"Etch a sketch", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,30,"Pong", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,50,"Asteroids", &Font24, WHITE, BLUE);
        //  Paint_DrawString_EN(30, 70, "Mandelbrot", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,90, "Neopixels", &Font24, WHITE, BLACK);
      }
     }
     else if((90>cursorY) && (cursorY>70))
     {
      if(!((90>cursorYOld) && (cursorYOld>70)))
      {
          Paint_DrawString_EN(10,10,"Etch a sketch", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,30,"Pong", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,50,"Asteroids", &Font24, WHITE, BLACK);
        //  Paint_DrawString_EN(30, 70, "Mandelbrot", &Font24, WHITE, BLUE);
          Paint_DrawString_EN(30,90, "Neopixels", &Font24, WHITE, BLACK);
      }
     }
     else if((110>cursorY) && (cursorY>90))
     {
      if(!((110>cursorYOld) && (cursorYOld>90)))
      {
          Paint_DrawString_EN(10,10,"Etch a sketch", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,30,"Pong", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,50,"Asteroids", &Font24, WHITE, BLACK);
      //  Paint_DrawString_EN(30, 70, "Mandelbrot", &Font24, WHITE, BLACK);
          Paint_DrawString_EN(30,90, "Neopixels", &Font24, WHITE, BLUE);
      }
     }
  }
  /*if(drawMandelbrot)
  {
    LCD_Clear(0xffff);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    Paint_Clear(WHITE);
    delay(500);
    runMandelbrot();
    drawMandelbrot = false;// When exiting program it is set to false.
    delay(500);//Delay to allow button state to return to not pressed.
    readJoyStickButton();
    drawStartMenu();
  }*/
  /*if(drawGradient)
  {
    LCD_Clear(0xffff);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    Paint_Clear(WHITE);
    delay(500);
    HSVCycle();
    drawGradient = false;
    delay(500);
    readJoyStickButton();
    drawStartMenu();
  }*/
  if(etchASketch)
  {
    //bool runEtchASketch{true};
    LCD_Clear(0xffff);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    Paint_Clear(WHITE);
    delay(1000);
    runEtchASketchProgram();
    etchASketch = false;
    delay(500);
    readJoyStickButton();
    drawStartMenu();
  }
  if(playPong)
  {
    //bool runEtchASketch{true};
    LCD_Clear(0xffff);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    Paint_Clear(WHITE);
    delay(1000);
    runPong();
    playPong = false;
    delay(500);
    readJoyStickButton();
    drawStartMenu();
  }
  if(playAsteroids)
  {
    //bool runEtchASketch{true};
    LCD_Clear(0xffff);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, BLACK);
    Paint_Clear(BLACK);
    delay(1000);
    runAsteroids();
    playAsteroids = false;
    delay(500);
    readJoyStickButton();
    drawStartMenu();
  }  
  if(pixelsOn) {
    runPixels();
    colorWipe(strip.Color(  0,   0, 255), 50); // Blue
    pixelsOn=false;
    delay(500);//For some reason the menu is drawn twice.
    drawStartMenu();
    //rainbow(10);
  }
}
void drawStartMenu()
{
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_DrawString_EN(10,10,"Etch a sketch", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30,"Pong", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,50,"Asteroids", &Font24, WHITE, BLACK);
 // Paint_DrawString_EN(30, 70, "Mandelbrot", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,90, "Neopixels", &Font24, WHITE, BLACK);

}
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
#endif
