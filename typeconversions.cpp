#include <math.h>

char numeralsToString(int numeral);
char* toString(int number)
{
  /*Handles numbers up to 999*/
  int hundreds = number/100;
  int temp = number - hundreds*100;
  int tens = temp/10;
  int ones = temp - tens*10;
  static char returnValue[4];
  returnValue[0]=numeralsToString(hundreds);
  returnValue[1]=numeralsToString(tens);
  returnValue[2]=numeralsToString(ones);
  returnValue[3]='\0';//char arrays in c++ need to be null-terminated. Which is something I don't understand, but oh well. Without it there is a square rectangle outputed. 
  return returnValue;
}
char numeralsToString(int numeral)
{

  char returnChar;
  if(numeral == 0)
  {
    returnChar = '0';
  } 
  else if(numeral == 1)
  {
    returnChar = '1';
  }
  else if(numeral == 2)
  {
    returnChar = '2';
  }
  else if(numeral == 3)
  { 
    returnChar = '3';
  } 
  else if(numeral == 4)
  {
    returnChar = '4';
  }
  else if(numeral == 5)
  {
    returnChar = '5';
  }
  else if(numeral == 6)
  {
    returnChar = '6';
  }
  else if(numeral == 7)
  {
    returnChar = '7';
  } 
  else if(numeral == 8)
  {
    returnChar = '8';
  }
  else if(numeral == 9)
  {
    returnChar = '9';
  }
  else
  {
    returnChar = ' ';
  }
  return returnChar;
} 