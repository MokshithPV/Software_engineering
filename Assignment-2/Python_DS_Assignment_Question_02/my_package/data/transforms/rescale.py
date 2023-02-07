#Imports
from PIL import Image

class RescaleImage(object):
    '''
        Rescales the image to a given size.
    '''

    def __init__(self, output_size):
        '''
            Arguments:
            output_size (tuple or int): Desired output size. If tuple, output is
            matched to output_size. If int, smaller of image edges is matched
            to output_size keeping aspect ratio the same.
        '''
        self.out = output_size

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)

            Note: You do not need to resize the bounding boxes. ONLY RESIZE THE IMAGE.
        '''
        try:
            image = Image.fromarray(image)
        except:
            pass
        if(isinstance(self.out , int)):
            w = image.size[0]
            h = image.size[1]
            if(w>h):
                self.out_w = self.out * w//h
                self.out_h = self.out
            else:
                self.out_w = self.out
                self.out_h = self.out * h//w
            return image.resize((self.out_w, self.out_h))
        else:
            return image.resize(self.out)
