#ifndef dwp
#define dwp

#define HEADER 12+1
uint32_t buff2=0;

void dp(char* dat , uint zi){
    int i;
    int kx = 0;
    int ky = 0;
    const uint16_t W = 0xffff;
    const uint16_t B = 0x0000;
    uint16_t rxd;
    uint16_t rxd2;
    uint16_t rxd3;
    uint32_t buff=0;
    int ss = 0;
    if (zi==0){buff2 = 0;}
// ugly function
    for (i = 0; i < 76800+76800*zi; i++)
    {
        //rxd = ((uint16_t)dat[2*i+9+(zi*76800*2)] << 8) | dat[2*i+1+9+(zi*76800*2)];
        rxd = ((uint16_t)dat[2 * i + HEADER+buff+buff2] << 8) | dat[2 * i + 1 + HEADER+buff+buff2];
        if (rxd ==0x0000){
            rxd2 = dat[2 * i + HEADER+2+buff+buff2];
            rxd3 = ((uint16_t)dat[2 * i + HEADER+3+buff+buff2] << 8) | dat[2 * i + 1 + HEADER+3+buff+buff2];
            for (rxd2; rxd2 > 0 ; rxd2=rxd2-1)
            {
                dw(kx,ky,rxd3);
                kx++;
                
                if (kx !=320 ){}
                else { kx = 0; ky++; }
            }
            buff = buff + 3; //buff +3 and in+on rxd3
            if(ky>239){ky=0;buff2=2*i+buff+buff2;break;}

        } else{
            dw(kx,ky,rxd);
                kx++;
                if (kx !=320 ){}
                else { kx = 0; ky++; }
                if(ky>239){ky=0;buff2=2*i+buff+buff2;break;}
        }
        
    }


}


void vdp(char * dat){
    /*int c = 0;*/
    uint16_t o = 0;
    uint16_t nbimg = ((uint16_t)dat[6] << 8) | dat[7];
    buff2 = 0;
    while(true){
    dp(dat,o);
    extapp_msleep(dat[8]);
    o++;
    if (o == nbimg){o=0;buff2 = 0;}
    
    /*if (c >= 3){
        if (extapp_getKey(true, NULL)== KEY_CTRL_EXIT){break; return; return;}
        c=0;

    }*/

    uint64_t k = extapp_scanKeyboard();
        if (k & (SCANCODE_Home | SCANCODE_Back)) {
            return;
        }
    
    }
    return;
}

//video black & white decoder (from nw-badapple by M4xi1m3)
void vdp_2c(char * dat){
    uint32_t vdo_len = ((uint32_t)dat[9] << 24) | ((uint32_t)dat[10] << 16) | ((uint32_t)dat[11] << 8) | dat[3];
    for(unsigned int len = 0; len < vdo_len;) {
        uint64_t start = extapp_millis();
        extapp_waitForVBlank();
        uint8_t frame_type = dat[HEADER+len++];
        switch (frame_type) {
            case 1:
            case 2: {
                unsigned int i = 0, j = 0, k = 0;
                bool color = frame_type == 2;
                while (i < 320*240) {
                    uint8_t num = dat[HEADER+len++];
                    i += num;
                    j += num;
                    if (j >= 320) {
                        extapp_pushRectUniform(j-num, k, (num - (j - 320)), 1, color ? 0xFFFF : 0);
                        k++;
                        if (j-320 != 0) {
                            extapp_pushRectUniform(0, k, (j - 320), 1, color ? 0xFFFF : 0);
                            j = j - 320;
                        } else {
                            j = 0;
                        }
                    } else {
                        extapp_pushRectUniform(j-num, k, num, 1, color ? 0xFFFF : 0);
                    }
                    color = !color;
                }
                break;
            }
            case 3:
                extapp_pushRectUniform(0, 0, LCD_WIDTH, LCD_HEIGHT, 0);
                break;
            case 4:
                extapp_pushRectUniform(0, 0, LCD_WIDTH, LCD_HEIGHT, 0xFFFF);
                break;
            default:
                break;
        }
        while (extapp_millis() - start < (len%3 == 0 ? 66 : 67));
        
        uint64_t k = extapp_scanKeyboard();
        if (k & SCANCODE_Home) {
            return;
        }
    }
}



void hlock(char* lpin){
    
    int key = 8008;
    int pint=0;
    
   
    draw_rectangle(0, 0, LCD_WIDTH_PX, LCD_HEIGHT_PX, 0xfffd);
    extapp_drawTextLarge("           nw-img-vw4           ", 0, 0, 65535, 0x18c3, false);
    draw_string(0, 30,"   picture locked (security)    ");
    /*draw_string(60,10,lpin);*/
    char*  code = "\x49\x42\x4d\x50\x5f\x73\x20\x20";
    char*  code2;
    code2=malloc(strlen(lpin));
    strcpy(code2, code); 
    /*strcat(code2, "1514");*/
    
    /*draw_string(60,45,code2);*/
    
    /*
    if(lpin[0]=='I'){draw_string(120,170,"go");}
    if(code2[0]=='I'){draw_string(120,190,"go");}
    */




while (key != KEY_CTRL_MENU)
        {
            key = extapp_getKey(true, NULL);
            
            if (key == KEY_CHAR_0){strcat(code2, "0");}
            if (key == KEY_CHAR_1){strcat(code2, "1");}
            if (key == KEY_CHAR_2){strcat(code2, "2");}
            if (key == KEY_CHAR_3){strcat(code2, "3");}
            if (key == KEY_CHAR_4){strcat(code2, "4");}
            if (key == KEY_CHAR_5){strcat(code2, "5");}
            if (key == KEY_CHAR_6){strcat(code2, "6");}
            if (key == KEY_CHAR_7){strcat(code2, "7");}
            if (key == KEY_CHAR_8){strcat(code2, "8");}
            if (key == KEY_CHAR_9){strcat(code2, "9");}
            if (key == KEY_CTRL_MENU){free(code2);return;}
            
            draw_rectangle(25+25*pint, 140, 6, 6, _B);
            extapp_drawTextLarge("           nw-img-vw3           ", 0, 0, 65535, 0x18c3, false);
            pint+=1;
            if (pint>8){break;}
            if (key == KEY_CTRL_OK){break;}


        }


    for(int i = 0; i < 24; i++) {
        if(lpin[i]==NULL){draw_string(120,100,"end");break;}
        if (lpin[i]==code2[i]){draw_string(10+i*15,150,"x");lck=1;}
        else{lck=0;break;}

    }
    if(lck==1){draw_string(120,80,"UNLOCKED");}
    else if(lck==0){draw_string(120,80,"WRONG");free(code2);}



    
}


#endif

