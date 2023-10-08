/**
  ******************************************************************************
  * @file    Font12.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text Font12 for STM32xx-EVAL's LCD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/


#include "fonts.h"


// 
//  Font data for Courier New 12pt
// 

const CH_CN Font12CN_Table[] = 
{
/*--  文字:  你  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"你",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1D,0xC0,0x1D,0x80,0x3B,0xFF,0x3B,0x07,
0x3F,0x77,0x7E,0x76,0xF8,0x70,0xFB,0xFE,0xFB,0xFE,0x3F,0x77,0x3F,0x77,0x3E,0x73,
0x38,0x70,0x38,0x70,0x3B,0xE0,0x00,0x00,0x00,0x00},

/*--  文字:  好  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"好",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x73,0xFF,0x70,0x0F,0xFE,0x1E,
0x7E,0x3C,0x6E,0x38,0xEE,0x30,0xEF,0xFF,0xFC,0x30,0x7C,0x30,0x38,0x30,0x3E,0x30,
0x7E,0x30,0xE0,0x30,0xC1,0xF0,0x00,0x00,0x00,0x00},

/*--  文字:  树  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"树",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0E,0x30,0x0E,0x3F,0xEE,0x30,0xEE,
0xFC,0xFF,0x76,0xCE,0x77,0xFE,0x7B,0xFE,0xFF,0xFE,0xF3,0xDE,0xF3,0xCE,0x37,0xEE,
0x3E,0x6E,0x3C,0x0E,0x30,0x3E,0x00,0x00,0x00,0x00},

/*--  文字:  莓  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"莓",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x70,0xFF,0xFF,0x3E,0x70,0x38,0x00,
0x7F,0xFF,0xE0,0x00,0xFF,0xFC,0x3B,0x8C,0x39,0xCC,0xFF,0xFF,0x73,0x9C,0x71,0xDC,
0x7F,0xFF,0x00,0x1C,0x01,0xF8,0x00,0x00,0x00,0x00},

/*--  文字:  派  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"派",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x1F,0xFF,0xF0,0x3E,0x00,0x0E,0x1F,
0xCF,0xFB,0xFF,0xF8,0x3F,0xFF,0x0F,0xFF,0x7F,0xD8,0x7F,0xDC,0x6F,0xCE,0xED,0xFF,
0xFD,0xF7,0xF9,0xC0,0x00,0x00,0x00,0x00,0x00,0x00},

/*--  文字:  a  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"a",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x3E,0x00,0x67,0x00,0x07,0x80,0x0F,0x80,0x7F,0x80,0xE3,0x80,0xE7,0x80,0xE7,0x80,
0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

/*--  文字:  b  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"b",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,
0x7F,0x00,0x7B,0x80,0x71,0xC0,0x71,0xC0,0x71,0xC0,0x71,0xC0,0x71,0xC0,0x7B,0x80,
0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

/*--  文字:  c  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"c",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x3F,0x00,0x73,0x00,0xF0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xF0,0x00,0x73,0x00,
0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

/*--  文字:  A  --*/
/*--  微软雅黑12;  此字体下对应的点阵为：宽x高=16x21   --*/
{"A",
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x1F,0x00,0x1F,0x00,
0x1F,0x00,0x3B,0x80,0x3B,0x80,0x71,0x80,0x7F,0xC0,0x71,0xC0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
};

cFONT Font12CN = {
  Font12CN_Table,
  sizeof(Font12CN_Table)/sizeof(CH_CN),  /*size of table*/
  11, /* ASCII Width */
  16, /* Width */
  21, /* Height */
};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/