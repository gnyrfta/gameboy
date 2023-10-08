#ifndef _COLOURCONVERSIONS_H_
#define _COLOURCONVERSIONS_H_

uint16_t convertToUWORD(uint16_t red_value,uint16_t green_value,uint16_t blue_value);
uint16_t* convertHSVtoRGB(int H);
uint16_t* arrayReturnTest();
#endif