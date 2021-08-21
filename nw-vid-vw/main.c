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

#include "dwc.h"
#include "dwp.h"
void extapp_main(void) {

  /*raw_rectangle(0, 0, LCD_WIDTH_PX, LCD_HEIGHT_PX, _W);
  draw_string_small(110, 120, _B, _W, "Click Ok");*/


	
    
    /*int key = extapp_getKey(true, NULL);
    if(key == KEY_CTRL_EXIT || key == KEY_CTRL_MENU) {
      return;
      }

    extapp_msleep(20);*/
    
 	an();

  return;
      
}



