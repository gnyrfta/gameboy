#include "GUI_Paint.h"
#include "LCD_Driver.h"
#include "joystick.h"
#include <Adafruit_NeoPixel.h>
#include "pixelmenu.h"
#define LED_PIN 4
#define LED_COUNT 74
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


bool selectingPixels{true};
void drawPixelMenu();
void rainbow(int wait);
void colorWipe(uint32_t color, int wait);
bool gradient{false};

int red{0};
  int green{0};
  int blue{0};
  int positionRed{0};
  int positionGreen{0};
  int positionBlue{0};
  int cursorXPixelRed{10};
  int cursorXOldPixelRed{10};
  int cursorXPixelGreen{10};
  int cursorXOldPixelGreen{10};
  int cursorXPixelBlue{10};
  int cursorXOldPixelBlue{10};
 // int cursorXPixelBrightness{10};
 // int cursorXOldPixelBrightness{10};
  

void runPixels(){
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to max.  (max = 255)
    colorWipe(strip.Color(0,0,0), 0);

  drawPixelMenu();
  delay(5000);
  int xValuePixel{0};
  int yValuePixel{0};
  int cursorXPixel{0};
  int cursorYPixel{0};
  int cursorXOldPixel{0};
  int cursorYOldPixel{0};
  selectingPixels=true;

  

  while(selectingPixels){
   // Serial.println("Entering eternal loop.");
    resetCommand();//resets the joystick command variable to zero.
    xValuePixel = readJoyStickX();//reads the potentiometer value from the joystick in the x-direction and gives it as an int.
    yValuePixel = readJoyStickY();//reads the potentiometer value from the joystick in the y-direction and gives it as an int.
    setCommand(xValuePixel,yValuePixel);//Sets command to left,right, up or down.

    cursorXOldPixel = cursorXPixel; //Used to overwrite former cursor position. 
    cursorYOldPixel = cursorYPixel;
    cursorXPixel = changeCursorXValue(cursorXPixel);//Increments x or y-value of cursor according to 'command'. 
    cursorYPixel = changeCursorYValue(cursorYPixel);
    readJoyStickButton();  //bvalue not used currently.
    // Check for button press
     if (buttonPressed()) 
  {
    Serial.println("Button press registered");
    if((170>cursorYPixel) && (cursorYPixel>150))
    {
      selectingPixels=false;
      Serial.println("should have exited loop");
    }
  }
    if(!(cursorXPixel==cursorXOldPixel && cursorYPixel==cursorYOldPixel))
    {
     if((30>cursorYPixel) && (cursorYPixel>10))
     {
        cursorXOldPixelRed = cursorXPixelRed;
        cursorXPixelRed = changeCursorXValue(cursorXPixelRed);
       if(!((30>cursorYOldPixel) && (cursorYOldPixel>10)))
        {
          Paint_DrawLine(cursorXPixelRed,10,cursorXPixelRed,30,RED,2, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelGreen,30,cursorXPixelGreen,50,GREEN,1, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelBlue,50,cursorXPixelBlue,70,BLUE,1, LINE_STYLE_SOLID);

      }
            Paint_DrawLine(cursorXOldPixelRed,10,cursorXOldPixelRed,30,WHITE,2, LINE_STYLE_SOLID);
            Paint_DrawLine(cursorXPixelRed,10,cursorXPixelRed,30,RED,2, LINE_STYLE_SOLID);
     }
     //
      if((50>cursorYPixel) && (cursorYPixel>30))
     {
        cursorXOldPixelGreen = cursorXPixelGreen;
        cursorXPixelGreen = changeCursorXValue(cursorXPixelGreen);
       if(!((50>cursorYOldPixel) && (cursorYOldPixel>30)))
        {
          Paint_DrawLine(cursorXPixelRed,10,cursorXPixelRed,30,WHITE,2, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelRed,10,cursorXPixelRed,30,RED,1, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelGreen,30,cursorXPixelGreen,50,GREEN,2, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelBlue,50,cursorXPixelBlue,70,BLUE,1, LINE_STYLE_SOLID);

      }
            Paint_DrawLine(cursorXOldPixelGreen,30,cursorXOldPixelGreen,50,WHITE,2, LINE_STYLE_SOLID);
            Paint_DrawLine(cursorXPixelGreen,30,cursorXPixelGreen,50,GREEN,2, LINE_STYLE_SOLID);
     }
     //
  if((70>cursorYPixel) && (cursorYPixel>50))
     {
        cursorXOldPixelBlue = cursorXPixelBlue;
        cursorXPixelBlue = changeCursorXValue(cursorXPixelBlue);
       if(!((70>cursorYOldPixel) && (cursorYOldPixel>50)))
        {
          Paint_DrawLine(cursorXPixelRed,10,cursorXPixelRed,30,RED,1, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelGreen,30,cursorXPixelGreen,50,WHITE,2, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelGreen,30,cursorXPixelGreen,50,GREEN,1, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelBlue,50,cursorXPixelBlue,70,BLUE,2, LINE_STYLE_SOLID);
         // Paint_DrawLine(cursorXPixelBrightness,70,cursorXPixelBrightness,90,WHITE,2, LINE_STYLE_SOLID);
         // Paint_DrawLine(cursorXPixelBrightness,70,cursorXPixelBrightness,90,BLACK,1, LINE_STYLE_SOLID);

      }
            Paint_DrawLine(cursorXOldPixelBlue,50,cursorXOldPixelBlue,70,WHITE,2, LINE_STYLE_SOLID);
            Paint_DrawLine(cursorXPixelBlue,50,cursorXPixelBlue,70,BLUE,2, LINE_STYLE_SOLID);
     }
    if((90>cursorYPixel) && (cursorYPixel>70))
     {
       // cursorXOldPixelBrightness = cursorXPixelBrightness;
       // cursorXPixelBrightness = changeCursorXValue(cursorXPixelBrightness);
       if(!((90>cursorYOldPixel) && (cursorYOldPixel>70)))
        {
          Paint_DrawLine(cursorXPixelRed,10,cursorXPixelRed,30,RED,1, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelGreen,30,cursorXPixelGreen,50,GREEN,1, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelBlue,50,cursorXPixelBlue,70,WHITE,2, LINE_STYLE_SOLID);
          Paint_DrawLine(cursorXPixelBlue,50,cursorXPixelBlue,70,BLUE,1, LINE_STYLE_SOLID);
          Paint_DrawString_EN(30,90, "Gradient", &Font24, WHITE, BLACK);


      }
            //Paint_DrawLine(cursorXOldPixelBrightness,70,cursorXOldPixelBrightness,90,WHITE,2, LINE_STYLE_SOLID);
            //Paint_DrawLine(cursorXPixelBrightness,70,cursorXPixelBrightness,90,BLACK,2, LINE_STYLE_SOLID);
     }
     else if((110>cursorYPixel) && (cursorYPixel>90))
     {
      if(!((110>cursorYOldPixel) && (cursorYOldPixel>90)))
      {
        Paint_DrawString_EN(30,90, "Gradient", &Font24, WHITE, BLUE);
       // Paint_DrawLine(cursorXPixelBrightness,70,cursorXPixelBrightness,90,WHITE,2, LINE_STYLE_SOLID);
        //Paint_DrawLine(cursorXPixelBrightness,70,cursorXPixelBrightness,90,BLACK,1, LINE_STYLE_SOLID);
        Paint_DrawString_EN(30,110,"On", &Font24, WHITE, BLACK);

     }
     }
    else if((130>cursorYPixel) && (cursorYPixel>110))
     {
      if(!((130>cursorYOldPixel) && (cursorYOldPixel>110)))
      {
        Paint_DrawString_EN(30,90, "Gradient", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(30,110,"On", &Font24, WHITE, BLUE);
        Paint_DrawString_EN(30,130,"Off", &Font24, WHITE, BLACK);
     }
     }
    else if((150>cursorYPixel) && (cursorYPixel>130))
     {
      if(!((150>cursorYOldPixel) && (cursorYOldPixel>130)))
      {
        Paint_DrawString_EN(30,110,"On", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(30,130,"Off", &Font24, WHITE, BLUE);
        Paint_DrawString_EN(30,150,"Back", &Font24, WHITE, BLACK);

     }
     }
    else if((170>cursorYPixel) && (cursorYPixel>150))
     {
      if(!((170>cursorYOldPixel) && (cursorYOldPixel>150)))
      {
        Paint_DrawString_EN(30,110,"On", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(30,130,"Off", &Font24, WHITE, BLACK);
        Paint_DrawString_EN(30,150,"Back", &Font24, WHITE, BLUE);

     }
     }
     red = cursorXPixelRed;
     green = cursorXPixelGreen;
     blue = cursorXPixelBlue;

   // strip.setBrightness(255);
    colorWipe(strip.Color(red,green,blue), 0);
    }
    else {
     // Serial.println(xValuePixel);
/*Serial.println(cursorXPixel);
    Serial.println(cursorXOldPixel);
    Serial.println(cursorYPixel);
    Serial.println(cursorYOldPixel);*/
    }
    
   // colorWipe(strip.Color(  red,   green, blue), 0);



   // Serial.println("Last line in eternal loop.");
  }

}
void drawPixelMenu() {
    LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_DrawLine(cursorXPixelRed,10,cursorXPixelRed,30,RED,1, LINE_STYLE_SOLID);
  Paint_DrawLine(cursorXPixelGreen,30,cursorXPixelGreen,50,GREEN,1, LINE_STYLE_SOLID);
  Paint_DrawLine(cursorXPixelBlue,50,cursorXPixelBlue,70,BLUE,1, LINE_STYLE_SOLID);
 // Paint_DrawLine(cursorXPixelBrightness,70,cursorXPixelBrightness,90,BLACK,1,LINE_STYLE_SOLID);
  Paint_DrawString_EN(30,90,"Gradient", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,110,"On", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,130,"Off", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,150,"Back", &Font24, WHITE, BLACK);

 /* Paint_DrawString_EN(10,10,"RED", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30,"GREEN", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,50,"BLUE", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30, 70, "Brightness", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,90, "GRADIENT", &Font24, WHITE, BLACK);*/
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
    if(!gradient)
    {
      break;
    }
  }
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}