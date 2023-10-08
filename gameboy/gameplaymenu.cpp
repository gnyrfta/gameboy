#include "GUI_Paint.h"

void drawMenu()
{
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_DrawLine(0, 280, 240, 280, BLACK, 2, LINE_STYLE_SOLID);
  Paint_DrawString_EN(10, 290, "Quit", &Font24, WHITE, BLACK); 
  Paint_DrawString_EN(100, 290, "Replay", &Font24, WHITE, BLACK); 

}
void highlightQuit(bool active)
{
  if(active)
  {
    Paint_DrawString_EN(10, 290, "Quit", &Font24, WHITE, BLUE);   
  }
  else
  {
    Paint_DrawString_EN(10, 290, "Quit", &Font24, WHITE, BLACK);   
  }
}
void highlightReplay(bool active)
{
  if(active)
  {
    Paint_DrawString_EN(100, 290, "Replay", &Font24, WHITE, BLUE); 
  }
  else
  {
    Paint_DrawString_EN(100, 290, "Replay", &Font24, WHITE, BLACK); 
  }
}

