#include <math.h>        // std::abs
#include <stdint.h>


#include <Complex.h> //Necessary for map.

using namespace std;

uint16_t convertToUWORD(uint16_t red_value,uint16_t green_value,uint16_t blue_value) //Converts to a color format that Paint_setPixel understands.
{
uint16_t red_565 = map(red_value, 0, 255, 0, 31);
uint16_t green_565 = map(green_value, 0, 255, 0, 63);
uint16_t blue_565 = map(blue_value, 0, 255, 0, 31);
uint16_t rgb_565 = (red_565<<11)|(green_565<<5)|blue_565;
return rgb_565;
}

uint16_t* arrayReturnTest()
{
  static uint16_t dude[3] = {1,2,3};

  return dude;
  }
 uint16_t* convertHSVtoRGB(int H)
  {
    static uint16_t changeThisLater[3]; 
    double h = (double)H;
    double s = h/60;
    //Serial.println(s);
    double X = 1-fabs(fmod(s,2)-1);
    //Serial.println(X);
    H = fmod(H,360);
    uint16_t x = (int)(X*255);
   // Serial.println("This is H: ");
    //Serial.println(H);
    if(H<60)
    {
      //Serial.println("In correct for-loop");
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
    return changeThisLater;
    //Serial.print(changeThisLater[1]);
    //Serial.print(changeThisLater[2]);
  }
  
