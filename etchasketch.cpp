//Fyll with monocolour black.
//Create cursor logic, but with prefix sketch
//Don't refill after cursor has passed.
#include "joystick.h"
#include "GUI_Paint.h"

bool runEtchASketch{true};
int xValueEtch{0};
int yValueEtch{0};
int cursorXEtch{0};
int cursorYEtch{0};
int cursorXOldEtch{0};
int cursorYOldEtch{0};
int bValueEtch{0};

void drawMenu();

void runEtchASketchProgram()
{
  drawMenu();
  setCursorSpeed(1);
  while(runEtchASketch)
    {
      delay(10);//cursor is fast and hard to control otherwise.
      resetCommand();//resets the joystick command variable to zero.
      xValueEtch = readJoyStickX();//reads the potentiometer value from the joystick in the x-direction and gives it as an int.
      yValueEtch = readJoyStickY();//reads the potentiometer value from the joystick in the y-direction and gives it as an int.
      setCommand(xValueEtch,yValueEtch);//Sets command to left,right, up or down.

      cursorXOldEtch = cursorXEtch; //Used to overwrite former cursor position. Not used in etchaSketch, but necessary if you would want the cursor to be a cursor sometime.
      cursorYOldEtch = cursorYEtch;
      cursorXEtch = changeCursorXValue(cursorXEtch);//Increments x or y-value of cursor according to 'command'. 
      cursorYEtch = changeCursorYValue(cursorYEtch);
      if(cursorXEtch < 0)
      {
        cursorXEtch = 0;
      }
      else if(cursorXEtch > 240)
      {
        cursorXEtch = 240;
      }
      else if(cursorYEtch < 0)
      {
        cursorYEtch = 0;
      }
      else if(cursorYEtch > 320)
      {
        cursorYEtch = 320;
      }
      bValueEtch = readJoyStickButton();  //bvalue not used currently.
      if(cursorYEtch < 280)
      {
        Paint_DrawPoint(cursorXEtch,cursorYEtch, BLACK,3,DOT_FILL_RIGHTUP);
      }     
      if((cursorYEtch > 282))
      {
        Paint_DrawString_EN(10, 290, "Quit", &Font24, WHITE, BLUE);     
        if(buttonPressed())
        {
        runEtchASketch = false;
        }
      }
      if((cursorYEtch < 282) && (cursorYOldEtch >= 282))
      {
        Paint_DrawString_EN(10, 290, "Quit", &Font24, WHITE, BLACK); 
      }      
    }
}

void drawMenu()
{
  Paint_DrawLine(0, 280, 240, 280, BLACK, 2, LINE_STYLE_SOLID);
  Paint_DrawString_EN(10, 290, "Quit", &Font24, WHITE, BLACK); 
}