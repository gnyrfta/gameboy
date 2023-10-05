#include "GUI_Paint.h"
#include "LCD_Driver.h"
#include "joystick.h"

bool selectingPixels{true};
void drawPixelMenu();
void runPixels(){
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
    if(!(cursorXPixel==cursorXOldPixel && cursorYPixel==cursorYOldPixel))
    {
     if((30>cursorYPixel) && (cursorYPixel>10))
     {
       if(!((30>cursorYOldPixel) && (cursorYOldPixel>10)))
        {
Paint_DrawString_EN(10,10,"RED", &Font24, WHITE, BLUE);
  Paint_DrawString_EN(30,30,"GREEN", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,50,"BLUE", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30, 70, "Placeholder", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,90, "GRADIENT", &Font24, WHITE, BLACK);
        }
     }
     else if((50>cursorYPixel) && (cursorYPixel>30))
     {
      if(!((50>cursorYOldPixel) && (cursorYOldPixel>30)))
      {
Paint_DrawString_EN(10,10,"RED", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30,"GREEN", &Font24, WHITE, BLUE);
  Paint_DrawString_EN(30,50,"BLUE", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30, 70, "Placeholder", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,90, "GRADIENT", &Font24, WHITE, BLACK);
      }
     }
      else if((70>cursorYPixel) && (cursorYPixel>50))
     {
      if(!((70>cursorYOldPixel) && (cursorYOldPixel>50)))
      {
Paint_DrawString_EN(10,10,"RED", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30,"GREEN", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,50,"BLUE", &Font24, WHITE, BLUE);
  Paint_DrawString_EN(30, 70, "Placeholder", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,90, "GRADIENT", &Font24, WHITE, BLACK);
      }
     }
     else if((90>cursorYPixel) && (cursorYPixel>70))
     {
      if(!((90>cursorYOldPixel) && (cursorYOldPixel>70)))
      {
Paint_DrawString_EN(10,10,"RED", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30,"GREEN", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,50,"BLUE", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30, 70, "Placeholder", &Font24, WHITE, BLUE);
  Paint_DrawString_EN(30,90, "GRADIENT", &Font24, WHITE, BLACK);
      }
     }
     else if((110>cursorYPixel) && (cursorYPixel>90))
     {
      if(!((110>cursorYOldPixel) && (cursorYOldPixel>90)))
      {
Paint_DrawString_EN(10,10,"RED", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30,"GREEN", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,50,"BLUE", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30, 70, "Placeholder", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,90, "GRADIENT", &Font24, WHITE, BLUE);
      }
     }
    }
    Serial.println("This is y-value");
    Serial.println(yValuePixel);

   // Serial.println("Last line in eternal loop.");
  }

}
void drawPixelMenu() {
    LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_DrawString_EN(10,10,"RED", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,30,"GREEN", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,50,"BLUE", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30, 70, "Placeholder", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(30,90, "GRADIENT", &Font24, WHITE, BLACK);
}