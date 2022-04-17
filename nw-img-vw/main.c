#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "extapp_api.h"



#define LCD_WIDTH_PX 320
#define LCD_HEIGHT_PX 240
#define LCD_WIDTH 320
#define LCD_HEIGHT 240

#define _W 0xffff
#define _B 0x0000
#define FILENAME_LENGHT_MAX 512
int lck=0;
int page = 0;

#include "dwp.h"



static void waitForKeyReleasedTimeout(int timeout) {
	while(extapp_scanKeyboard() && timeout > 0) {
		extapp_msleep(10);
		timeout -= 10;
	}
}

static void waitForKeyReleased() {
	while(extapp_scanKeyboard()) {
		extapp_msleep(10);
	}
}

static void waitForKeyPressed() {
	while(!extapp_scanKeyboard()) {
		extapp_msleep(10);
	}
}


char ** removes(char ** first, char ** last) {
  char ** result = first;
  while (first != last) {
    if (!(*first == NULL)) {
      *result = *first;
      ++result;
    }
    ++first;
  }
  return result;
}



void drawRomList(char **filenames, int nb, int selected_rom) {
	char name_buffer[FILENAME_LENGHT_MAX];

  extapp_drawTextLarge("           nw-img-vw4           ", 0, 0, 65535, 0x18c3, false);
  int t=0;
  int i=0;
  if (selected_rom>10 && selected_rom <21){t=nb-(nb-10);if(page!=1){draw_rectangle(0, 20, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);page=1;} }
  if (selected_rom>20 && selected_rom <31){t=nb-(nb-20);if(page!=2){draw_rectangle(0, 20, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);page=2;} }
  if (selected_rom>30 && selected_rom <41){t=nb-(nb-30);if(page!=3){draw_rectangle(0, 20, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);page=3;} }
  if (selected_rom>40 && selected_rom <51){t=nb-(nb-40);if(page!=4){draw_rectangle(0, 20, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);page=4;} }
  
  if (selected_rom<=10){t=0;if(page!=0){draw_rectangle(0, 20, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);page=0;}}
	for(i; i < nb-t; i++) {
		strncpy(name_buffer, filenames[i+t], FILENAME_LENGHT_MAX);
		name_buffer[32] = '\0';

		extapp_drawTextLarge(name_buffer, 5, (i+1)*20, selected_rom == i+t ? 0b1111100000000000 : 65535 , 8452, false);
		
	if(t!=0 && i==0){extapp_drawTextLarge(name_buffer, 5, (i+1)*20, 0xff34 , 8452, false);}
		strncpy(name_buffer, filenames[i+t], FILENAME_LENGHT_MAX);
		
	}
}




void draw_string(int16_t x, int16_t y, char *text) {
  extapp_drawTextLarge(text, x, y, _B, 0xfffd, false);
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


void extapp_main(void) {

  draw_rectangle(0, 0, LCD_WIDTH_PX, LCD_HEIGHT_PX, _W);


  /*char* mes;*/
  const int max_roms = 50;
	char * filenames[max_roms];
	int selected_rom = 0;
	char name_buffer[FILENAME_LENGHT_MAX];

  int nb = extapp_fileListWithExtension(filenames, max_roms, "", EXTAPP_FLASH_FILE_SYSTEM);

char* lpin;
  size_t len;
	for(int i = 0; i < nb; i++) {
		const char * data = extapp_fileRead(filenames[i], &len, EXTAPP_FLASH_FILE_SYSTEM);
		if(len < 5 || data[0] != 'I' || data[1] != 'B' || data[2] != 'M' || data[3] != 'P' || data[4] != 0x5f) {
			filenames[i] = NULL;
		}
		if(data[4] == 0x5f && data[5] == 0x73) {
			/*draw_string(150,150,data);*/
			lpin=data;
			/*draw_string(150,170,lpin);*/
			/*if(lpin[0]=='I'){draw_string(60,130,"go");}
			extapp_msleep(1800);*/
			filenames[i] = NULL;
		}
		
		
	}
	

	nb = removes(filenames, filenames + nb) - filenames;




if(nb == 0) {
		extapp_drawTextLarge("          No IMG found          ", 0, 110, 65535, 0x18c3, false);
		extapp_msleep(150);
		waitForKeyReleasedTimeout(150);
		waitForKeyPressed();
		return NULL;
	} else {
		draw_rectangle(0, 0, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);
		drawRomList(filenames, nb, selected_rom);
    waitForKeyReleased();
	int aff=0;
	for (;;)
	{
		extapp_msleep(10);
		uint64_t scancode = extapp_scanKeyboard();
		if (scancode && aff == 1){ draw_rectangle(0, 0, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);aff = 0;}

			if(scancode & SCANCODE_Down) {
				selected_rom = (selected_rom + 1) % nb;
				drawRomList(filenames, nb, selected_rom);
				waitForKeyReleasedTimeout(200);
			} else if(scancode & SCANCODE_Up) {
				selected_rom = (selected_rom - 1) % nb;
				if(selected_rom < 0) {
					selected_rom = nb + selected_rom;
				}
				
				drawRomList(filenames, nb, selected_rom);
				waitForKeyReleasedTimeout(200);
			} else if(scancode & (SCANCODE_OK | SCANCODE_EXE))  {
				aff = 1;
				char *dat = extapp_fileRead(filenames[selected_rom], &len, EXTAPP_FLASH_FILE_SYSTEM);
				if(dat[4] == 0x5f && dat[5] == 0x70) {
					
					if (dat[8] == 0x01 && lck ==0){hlock(lpin);}
					else {dp(dat,0);}
					
				}
				else if (dat[4] == 0x5f && dat[5] == 0x76){
					extapp_drawTextLarge("           in progress          ", 0, 120, 65535, 0x18c3, false);
					waitForKeyReleasedTimeout(200);
					if (dat[8] == 0x01 && lck ==0){hlock(lpin);}
					else {vdp(dat);}
				}
				else if (dat[4] == 0x5f && dat[5] == 0x77){
					extapp_drawTextLarge("           in progress          ", 0, 120, 65535, 0x18c3, false);
					waitForKeyReleasedTimeout(200);
					if (dat[12] == 0x01 && lck ==0){hlock(lpin);}
					else {vdp_2c(dat);}
				}
        		
        		waitForKeyReleased();
        
        


			} else if(scancode & (SCANCODE_Back |SCANCODE_Backspace)) {
				strncpy(name_buffer, filenames[selected_rom], FILENAME_LENGHT_MAX);
				drawRomList(filenames, nb, selected_rom);
				waitForKeyReleased();
			} else if(scancode &  SCANCODE_Home) {
				return NULL;
			} else if(scancode &  SCANCODE_Dot) {
				extapp_drawTextLarge("         (c) Prime-arys         ", 0, 0, 65535, 0x18c3, false);
				waitForKeyReleased();
				extapp_drawTextLarge("           nw-img-vw4           ", 0, 0, 65535, 0x18c3, false);
			}
	}
	}





 
    int key = extapp_getKey(true, NULL);
    if(key == KEY_CTRL_EXIT || key == KEY_CTRL_MENU) {
      return;
      }
	
    while (key != KEY_CTRL_EXIT || key != KEY_CTRL_MENU)
    {
    int key = extapp_getKey(true, NULL);
    	if(key == KEY_CTRL_EXIT || key == KEY_CTRL_MENU) {
      return;
      }
 	 
      
}
}



