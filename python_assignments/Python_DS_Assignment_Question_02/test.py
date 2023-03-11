from my_package.model import ImageCaptioningModel
from my_package.data import Dataset, Download
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
import numpy as np
from PIL import Image , ImageDraw

captioner = ImageCaptioningModel()
#z = Download()
#z("C:\\Users\\venka\\Downloads\\1.jpg","https://scontent-sin6-3.xx.fbcdn.net/v/t39.30808-1/273883598_132156142637614_7720801435020966075_n.jpg?stp=c0.0.160.160a_dst-jpg_p160x160&_nc_cat=110&ccb=1-7&_nc_sid=7206a8&_nc_ohc=YjHedsIA6p4AX9XZe9a&tn=48sTEmN7vkJTgm4G&_nc_ht=scontent-sin6-3.xx&oh=00_AfCoGLnY_ojn8r08bWfo8NL1t8cUtWDyiU9XIieOcnTxBQ&oe=63E4BC6E")
im1 = Image.open("C:\\Users\\venka\\Downloads\\2.jpg")
im = Image.new("RGB",size=(im1.size[0] , im1.size[1]),color=(255,255,255))
imd = ImageDraw.Draw(im)
imd.rectangle((25,25,im1.size[0]-25,im1.size[1]-25),outline=(0,0,0))
a = captioner("C:\\Users\\venka\\Downloads\\2.jpg",3)
st = "Generated captions:\n\n"
for k in range(len(a)):
    st = st + str(k+1) + ")" + a[k] + "\n\n"
imd.text((30,30),st,fill=(0,0,0))
im2 = Image.new("RGB",size=(im1.size[0]*2 , im1.size[1]),color=(255,255,255))
im2.paste(im1 , (0,0))
im2.paste(im , (im1.size[0],0))
im2.show()
