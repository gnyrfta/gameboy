/*This file should contain code for mandelbrot program. */

#include "mandelbrot.h"
#include "colourconversions.h"
#include "joystick.h"


double nextOriginX{0};//Used to find a starting place for next mandelbrot drawing that is along one of the borders.
double tempNextOriginX{0};
double nextOriginY{0};
double tempNextOriginY{0};
double scale{1};//Used to scale inwards in the fractal. 

uint16_t fun(Complex c, double xd, double yd);
int iterations(Complex c);
void mandelbrot(double nextOriginX, double nextOriginY, double scale);
bool runProgram{true};

void runMandelbrot(){
  while(runProgram)
   {
    mandelbrot(nextOriginX,nextOriginY,scale);
    nextOriginX=tempNextOriginX;
    nextOriginY=tempNextOriginY;
    scale+=1.5;
   }
}
void mandelbrot(double nextOriginX, double nextOriginY,double scale) 
{
  Serial.println("in mandelbrot");
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
      Paint_SetPixel(x,y,fun(c,xd,yd));//This function works and 'convertToUWORD' works.
      int bvalue = readJoyStickButton();
      Serial.print("bvalue");
      Serial.print(bvalue);
      if(buttonPressed())
      {
        if(x>2)
        {
          Serial.print("button pressed");
          x = 1000;
          y= 1000;
          runProgram = false;
        }
      }
    }

  }

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
 // Serial.println("hello");
  arr[0] = (uint16_t)iter*53;
  arr[1] = (uint16_t)iter*53;
  arr[2] = 0;
  uint16_t * rgb = convertHSVtoRGB(iter*3);
  Serial.println("This is rgb:");
  Serial.println(rgb[0]);
  return convertToUWORD(rgb[0],rgb[1],rgb[2]);
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
