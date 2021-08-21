from PIL import Image
from colormap import *
import os

def code_open():
	f=open("code.h","r",encoding="utf8")
	return str(f.read());

def image_read(img_s):
	img = Image.open(img_s)
	largeur,hauteur = img.size
	message=""
	message_f=""
	xcou=0
	cou=largeur*hauteur
	for y in range(hauteur):
	    for x in range(largeur):
	        r,v,b = img.getpixel((x,y))
	        xcou=xcou+1
	        rgb565 = (((r & 248)<<8)+((v & 252)<<3)+((b & 248)>>3))
	        #print(hex(rgb565))
	        #color=rgb2hex(r,v,b)
	        color=hex(rgb565)
	        for k in color:
	            if k =="#":
	                message = message + "0x"
	            else: message = message + k
	            if message == "0xffff":
	            	message = "W"
	            if message == "0x0":
	            	message = "B"

	        #fo=("  dw("+str(x)+","+str(y)+","+str(message)+");")
	        fo=(str(message))
	        message_f=message_f+fo
	        if xcou != cou : message_f=message_f+","
	        message=""
	return message_f;

def main():
	dat_f=""
	dat=""
	c=0
	init=0
	onlyfiles = next(os.walk("d_img/"))[2]
	print(len(onlyfiles)," files\n")
	for i in range(len(onlyfiles)):
		select_img="d_img/"+str(i)+".png"
		try :
			msd5=str(c)+".png"
			print(msd5)
			dat = "{"+str(image_read(select_img))+"}"
			if i != len(onlyfiles)-1:
				dat_f=dat_f+dat+","
			else:
				dat_f=dat_f+dat
			c=c+1
			init=1
		except :
			print("error img ",i)
			dat=""
			init=0
			c=c+1
			pass

	#dat_f=dat_f+"{B}"
	#c=c+1
	return dat_f,c;


file1 = open("dwc.h","w",encoding="utf8")
file1.write(code_open())
data,n_img=main()
const_img="\nconst uint16_t DAT["+str(n_img)+"][76800] = {"
file1.write(const_img)
file1.write(data)
file1.write("};")
file1.write("\nconst int nDAT = "+str(n_img)+";")
a=input("video : y/n\n")
if a == "y" :
	b=input("frame delay (ms)\n")
	try:
		file1.write("\nconst int msDT = "+str(b)+";")
		print("\nOk.\n")
	except:
		print("error : incorect value >> (pictures mode)\n")
		pass


elif a!="y":print("Ok (pictures mode)\n")
file1.write("\n#endif")
file1.close()
print("\nend \t build : dwc.h\n")
os.system("pause")


