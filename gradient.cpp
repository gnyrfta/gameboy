#include <stdint.h>
#include "colourconversions.h"
#include "GUI_Paint.h"
uint16_t * rgb;
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
             
              rgb = convertHSVtoRGB(H); 
              //Serial.print(rgb[0]);
              //Serial.print(rgb[1]);
              //Serial.print(rgb[2]);
							Paint_SetPixel(x,y,convertToUWORD(rgb[0],rgb[1],rgb[2]));

						}
          H++;
				}

		}
}