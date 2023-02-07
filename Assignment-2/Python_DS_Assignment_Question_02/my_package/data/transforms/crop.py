#Imports
from PIL import Image
import random

class CropImage(object):
    '''
        Performs either random cropping or center cropping.
    '''

    def __init__(self, shape, crop_type='center'):
        '''
            Arguments:
            shape: output shape of the crop (h, w)
            crop_type: center crop or random crop. Default: center
        '''
        self.height , self.width = shape
        self.crop_type = crop_type

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)
        '''
        try:
            image = Image.fromarray(image)
        except:
            pass
        if(self.crop_type == "center"):
            self.x = (image.size[0] - self.width)//2
            self.y = (image.size[1] - self.height)//2
            self.w = (image.size[0] + self.width)//2
            self.h = (image.size[1] + self.height)//2
        else:
            if(image.size[0]-self.width<0 and image.size[1]-self.height<0):
                self.x = random.randint(image.size[0]-self.width,0)
                self.y = random.randint(image.size[1]-self.height,0)
            else:
                if(image.size[1]-self.height<0):
                    self.x = random.randint(0,image.size[0]-self.width)
                    self.y = random.randint(image.size[1]-self.height,0)
                else:
                    self.x = random.randint(image.size[0]-self.width,0)
                    self.y = random.randint(0,image.size[1]-self.height)
            self.w = self.x + self.width
            self.h = self.y + self.height
        return image.crop(box = (self.x,self.y,self.w,self.h))
 