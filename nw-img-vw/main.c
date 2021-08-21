#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "extapp_api.h"




#define LCD_WIDTH_PX 320
#define LCD_HEIGHT_PX 240

#define _W 0xffff
#define _B 0x0000





void draw_string(int16_t x, int16_t y, const char *text) {
  extapp_drawTextLarge(text, x, y, _B, _W, false);
}

void draw_string_small(int16_t x, int16_t y, uint16_t fg, uint16_t bg, const char *text) {
  extapp_drawTextSmall(text, x, y, fg, bg, false);
}

void draw_rectangle(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color) {
  extapp_pushRectUniform(x, y, w, h, color);
}
void dw(int16_t x, int16_t y, uint16_t * color){
  extapp_pushRectUniform(x, y, 1, 1, color);
}
  int et0 = 0;
  int et1 = 0;
  int nc = 0;
#include "dwc.h"
#include "dwp.h"
void extapp_main(void) {

  draw_rectangle(0, 0, LCD_WIDTH_PX, LCD_HEIGHT_PX, _W);
    dp(0);

 
    int key = extapp_getKey(true, NULL);
    if(key == KEY_CTRL_EXIT || key == KEY_CTRL_MENU) {
      return;
      }
	
    while (key != KEY_CTRL_EXIT || key != KEY_CTRL_MENU)
    {
    int key = extapp_getKey(true, NULL);
    	 
 	 if (key == KEY_CHAR_0)
 	 {
 	 	 nc = 0;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
 	     extapp_msleep(40);
 	     }
     else if (key == KEY_CHAR_1)
     {
         nc = 1;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_2)
     {
         nc = 2;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_3)
     {
         nc = 3;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_4)
     {
         nc = 4;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_5)
     {
         nc = 5;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_6)
     {
         nc = 6;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_7)
     {
         nc = 7;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_8)
     {
         nc = 8;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key == KEY_CHAR_9)
     {
         nc = 9;
 	 	 if (et1==1){nc=nc+10;}
 	     key = 8008;
 	     dp(nc);
         extapp_msleep(40);
         }
     else if (key==KEY_CHAR_RPAR)
     {
     	et1=1;
     }
     else if (key==KEY_CHAR_LPAR)
     {
     	et1=0;
     }

 	  else if (key != KEY_CTRL_EXIT && key != KEY_CTRL_MENU){
 	  	
 	  	int key = 8008;
 	  	return;
 	  }
 	  if(key == KEY_CTRL_EXIT || key == KEY_CTRL_MENU) {
 	  break;
     	 return;
      }

  	  
    }
    if(key == KEY_CTRL_EXIT || key == KEY_CTRL_MENU) {
      return;
      }

      return;
      
}



