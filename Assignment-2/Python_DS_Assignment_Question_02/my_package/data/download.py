from PIL import Image
import requests
from io import BytesIO

class Download(object):
    '''
        A class for helping in dowloading the required images from the given url to the specified path
    '''

    def __call__(self, path, url):
        '''
            Arguments:
            path: download path with the file name
            url: required image URL
        '''
        file = open(path,"wb")
        image_request = requests.get(url)
        binary_class = BytesIO(image_request.content)
        binary_data = binary_class.getvalue()
        file.write(binary_data)
        file.close()
