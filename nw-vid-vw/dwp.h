#ifndef dwp
#define dwp

void dp(int8_t a){
    int i = 0;
    int kx = 0;
    int ky = 0;
    const uint16_t W = 0xffff;
    const uint16_t B = 0x0000;
    

    for (i = 0; i < 76800; i++)
    {
        dw(kx,ky,DAT[a][i]);
        kx++;
        if (kx !=320 ){}
        else { kx = 0; ky++; }
    }

}
void an(){
    /*int c = 0;*/
    int o = 0;
    while(true){
    dp(o);
    extapp_msleep(msDT);
    o++;
    if (o == nDAT){o=0;}
    
    /*if (c >= 3){
        if (extapp_getKey(true, NULL)== KEY_CTRL_EXIT){break; return; return;}
        c=0;

    }*/

    uint64_t k = extapp_scanKeyboard();
        if (k & SCANCODE_Home) {
            return;
        }
    
    }
    return;
}


#endif
