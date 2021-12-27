from PIL import Image
from colormap import *
import os


def image_read(img_s):
	img = Image.open(img_s)
	largeur,hauteur = img.size
	l=[]
	cou=largeur*hauteur
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
			if color == "0000" : color = "0020"
			l.append(color)

	return l

def RLE_compresse(l):
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
				
		except:pass
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


def main():
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
			imc=RLE_compresse(imnc)
			dat.append(imc)
			c=c+1
		except :
			print("error img ",i)
			c=c+1
			pass

	#dat_f=dat_f+"{B}"
	#c=c+1
	return dat,c


def ar2bin(d,q):
	mes=""
	for i in range(len(d)):
		fl=str(i)+".bin"
		file = open("img/"+fl,"wb")
		for j in range(len(d[i])):
			hex_string = d[i][j]
			#print(hex_string)

			try :
				a=bytearray.fromhex(hex_string)
			except:
				#print(hex_string)
				pass

			if j==0:
				if q==0:
					zer=bytearray.fromhex("49424d505f70000000")
				elif q==1 : zer=bytearray.fromhex("49424d505f70000001")
				
				file.write(zer)
			file.write(a)
		file.close()
	file.close()
	return None



def ar2bin_v(d,q,v):
	mes=""
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
				#print(hex_string)
				pass

			if j==0 and i==0 and nnn==0:
				nnn=1
				zer=bytearray.fromhex("49424d505f76")
				file.write(zer)
				ba=hex(len(d))
				ba=ba[2:]
				if len(ba)==1:ba="0"+ba
				bb=hex(v)
				bb=bb[2:]
				if len(bb)==1:bb="0"+bb
				file.write(bytearray.fromhex(ba))
				file.write(bytearray.fromhex(bb))
				if q==0:
					zer=bytearray.fromhex("00")
				elif q==1 : 
					zer=bytearray.fromhex("01")
				
				file.write(zer)
			file.write(a)
	file.close()
	return None





data,n_img=main()
issec=0
vid=0
b=input("secur ? [y/n]\n")
if b == "y":
	issec=1
	print("secur : on\n")
	mpd = input("password ? use digit ['0123456789'] (8 pin max) \n")
	try : 
		if len(mpd)>8:
			print("error\n")
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
		print("error\n")
		os.wait(2)
		exit()



a=input("video : y/n\n")
if a == "y" :
	b=input("frame delay (ms)\n")
	try : 
		vid = int(b)
		if vid > 255:
			vid=255
			print(" >> 255  (val max)\n")
		print("ok\n")
	except : 
		print("error\n")
		os.wait(2)
		exit()
	ar2bin_v(data,issec,vid)


else : 
	print("\npicture\n")
	ar2bin(data,issec)


print("\nend \t DONE\n")
os.system("pause")


