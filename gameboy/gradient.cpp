//Draws a gradient, uncomment to use. 
/*
#include <stdint.h>
#include "colourconversions.h"
#include "GUI_Paint.h"
#include "joystick.h"

uint16_t * rgb;
bool runGradient{true};

void HSVCycle()
{
	int H = 0;
	while(runGradient)
		{
			for(uint16_t x = 0; x<240;x++)
				{
					for(uint16_t y=0;y<320;y++)
						{
							double xd{x};
							double yd{y};
             
              rgb = convertHSVtoRGB(H); 
              //Serial.print(rgb[0]);
              //Serial.print(rgb[1]);
              //Serial.print(rgb[2]);
							Paint_SetPixel(x,y,convertToUWORD(rgb[0],rgb[1],rgb[2]));
              int bvalue = readJoyStickButton();
              if(buttonPressed())
              {
                if(x>2)
                {
                  Serial.print("button pressed");
                  x = 1000;
                  y= 1000;
                  runGradient = false;
                }
              }
						}
          H++;
				}

		}
}*/
