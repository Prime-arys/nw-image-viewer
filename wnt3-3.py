from PIL import Image
from colormap import *
import cv2
import struct
import os
from encode import *

##FX
def image_read(img_s):
    img = Image.open(img_s)
    largeur,hauteur = img.size
    l=[]
    for y in range(hauteur):
        for x in range(largeur):
            r,v,b = img.getpixel((x,y))
            rgb565 = (((r & 248)<<8)+((v & 252)<<3)+((b & 248)>>3))
            #print(hex(rgb565))
            #color=rgb2hex(r,v,b)
            color=hex(rgb565)
            color = color[2:]
            while len(color)!=4:
                color="0"+color
            if len(color)!=4:print('error')
            if color == "0000" : color = "0020" #this is for RLE compress
            l.append(color)

    return l

def RLE_compress(l):
    lf=[]
    i=0
    c=1
    p=0
    while i <= len(l)-1:
        try:
            while l[i]==l[i+1] :
                if l[i]==l[i+1]==l[i+2] or p==1:
                    p=1
                    i+=1
                    c+=1
                    col=l[i]
                    if c==255 : break
                else:break
            p=0
                
        except:
            #print("error : out of map // end of file")
            #print("done")
            pass
        if c!=1 :
            lf.append("0000")
            ar = hex(c)
            ar = ar[2:]
            while len(ar)!=2:
                ar="0"+ar
            lf.append(ar)
            lf.append(col)
            c=1
            i+=1

        else :
            lf.append(l[i])
            i+=1

    return lf




def main_img():
    dat=[]
    c=0
    onlyfiles = next(os.walk("d_img/"))[2]
    print(len(onlyfiles)," files\n")
    for i in range(len(onlyfiles)):
        select_img="d_img/"+str(i)+".png"
        try :
            msd5=str(c)+".png"
            print(msd5)
            imnc=image_read(select_img)
            imc=RLE_compress(imnc)
            dat.append(imc)
            c=c+1
        except :
            print("error img ",i," Make sure your image is encoded in RGB 8bpc.")
            c=c+1
            pass

    #dat_f=dat_f+"{B}"
    #c=c+1
    return dat,c

def header_manager(ftype:str, nbimg:int, lag:int, off:int, sec:str):
    '''
    offset 00   KEY : {49424d505f} : [IBMP_]
    offset 05   TYPE : {73} : [s] -> pass file
    offset 05   TYPE : {76} : [v] -> video file
    offset 05   TYPE : {77} : [w] -> video file (black & white)
    offset 05   TYPE : {70} : [p] -> image file
    offset 06   NBIMG : {XXXX} -> 0-65536 #number of image for video
    offset 08   LAG : {XX} -> 0-255 #latency betwen image
    offset 09   OFF : {XXXXXX} -> len of DATA on 24bits (0x000000=undef)
    offset 0C   SEC : {00}/{01} -> is the file secure ?
    offset 0D   DATA
    '''
    KEY = "49424d505f"
    
    NBIMG=hex(nbimg)[2:]
    while len(NBIMG)<4:NBIMG="0"+NBIMG
    
    LAG=hex(lag)[2:]
    if len(LAG)==1:LAG="0"+LAG
    
    OFF=hex(off)[2:]
    while len(OFF)<6:OFF="0"+OFF
    
    OUT = KEY+ftype+NBIMG+LAG+OFF+sec
    return OUT
    


def ar2bin(d,q):
    '''
    generates a binary image data
    '''
    for i in range(len(d)):
        fl=str(i)+".bin"
        file = open("img/"+fl,"wb")
        for j in range(len(d[i])):
            hex_string = d[i][j]
            #print(hex_string)

            try :
                a=bytearray.fromhex(hex_string)
            except:
                print("fails to format : ",hex_string)
                pass

            if j==0:
                
                zer=bytearray.fromhex(header_manager("70",0,0,0,str(q)))
            
                file.write(zer)
            file.write(a)
        file.close()
    file.close()
    return None



def ar2bin_v(d,q,v:int):
    '''
    generates a binary video data (clone of 'ar2bin')
    '''
    nnn=0
    fl=str("v0-"+str(len(d)))+".bin"
    file = open("img/"+fl,"wb")
    print(len(d))
    for i in range(len(d)):
        
        for j in range(len(d[i])):
            hex_string = d[i][j]
            #print(hex_string)

            try :
                a=bytearray.fromhex(hex_string)
            except:
                print("fails to format : ",hex_string)
                pass

            if j==0 and i==0 and nnn==0:
                nnn=1
                zer=header_manager("76",len(d),v,0,q)

                file.write(bytearray.fromhex(zer))
            file.write(a)
    file.close()
    return None


def rawify(fname:str):
    '''
    adapt from nw-badapple by M4xi1m3
    '''
    vid = cv2.VideoCapture(fname)
    fps = vid.get(cv2.CAP_PROP_FPS)
    print(fps)
    
    f = open("raw", "wb")
    i = 0
    o=0
    while True:
        success, image = vid.read()
        
        if (not success):
            break
        for line in image:
            for col in line:
                #wide.append(1 if col[0] > 128 else 0)
                f.write(struct.pack(">B", col[0]))
                o+=1
                 
        i += 1
        print(str(i) + " : " + str(i/fps), end="\r")

    print()
    f.close()
    return i,o


def SEC():
    global issec
    b=input("secur ? [y/n]\n")
    if b == "y":
        issec="01"
        print("secur : on\n")
        mpd = input("password ? use digits ['0123456789'] (8 pin max) \n")
        try : 
            if len(mpd)>8:
                print("error\n(8 pin max)")
                os.wait(2)
                exit()
                
            f_mpd=int(mpd)
            print(f_mpd)
            file2 = open("img/pass.bin","w")
            zer="IBMP_s\x20\x20"
            file2.write(zer)
            file2.write(str(f_mpd))
            file2.close()
            print("\nok\n")

        except : 
            print("error\nplease use digits ['0123456789']")
            os.wait(2)
            exit()

def LAG():
    b=input("frame delay (ms)\n")
    try : 
        latency = int(b)
        if latency > 255:
            latency=255
            print(" >> 255  (val max)\n")
        print("ok\n")
    except : 
        print("error\nplease use digits ['0123456789']")
        os.wait(2)
        exit()
    return latency
  
def main():
    global issec
    mode = input("mode ? : \n 1) image (d_img)\n 2) video (d_img)\n 3) video Black & White (<file>.mp4)\n q) exit\n")
    if mode!="q" and mode != "Q" and mode != "":
        SEC()
    
    if mode=="1":
        data,n_img=main_img()
        print("\npicture\n")
        ar2bin(data,issec)
        
        
    elif mode == "2":
        data,n_img=main_img()
        latency = LAG()
        ar2bin_v(data,issec,latency)

        
    elif mode == "3":
        #TODO
        fname=input("file name ? :\n")
        latency=LAG()
        nbi,lno=rawify(fname)
        main_ENC()
        file_size = os.path.getsize("tmp")
        print(file_size)
        vid = open("tmp","rb")
        Big_data=vid.read()
        vid.close()
        
        fl="v1-"+fname[0:-4]+".bin"
        
        zer=header_manager("77",nbi,latency,file_size,issec)
        finalf=open("img/"+fl,"wb")
        finalf.write(bytearray.fromhex(zer))
        #for ij in range(len(Big_data)):
            #fff=[]
            #fff.append(Big_data[ij])
            #finalf.write(fff[ij]) #ERROR
        finalf.write(Big_data)
        finalf.close()
        
        
        
    
    elif mode == "q" or mode == "Q":
        exit()
    
    
    else:
        print("\n")
        main()



##VAR

issec="00"
vid=0



##MAIN

main()
print("\nend \t DONE\n")
os.system("pause")




