#Imports
from my_package.model import ImageCaptioningModel
from my_package.data import Dataset, Download
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
import numpy as np
from PIL import Image


def experiment(annotation_file, captioner, transforms, outputs):
    '''
        Function to perform the desired experiments

        Arguments:
        annotation_file: Path to annotation file
        captioner: The image captioner
        transforms: List of transformation classes
        outputs: Path of the output folder to store the images
    '''

    #Create the instances of the dataset, download

    download_i = Download()
    dataset_i = Dataset(annotation_file,transforms=transforms)

    #Print image names and their captions from annotation file using dataset object

    for i in range(len(dataset_i)):
        a = dataset_i.__getann__(i)
        print("Image name: ",a["file_name"])
        print("Image captions:")
        k=1
        for j in a["captions"]:
            print(str(k)+")",j["caption"])
            k+=1
        print("\n")

    #Download images to ./data/imgs/ folder using download object

    for i in range(len(dataset_i)):
        a = dataset_i.__getann__(i)
        download_i("./data/imgs/10050img_0"+str(i)+".jpg",a["url"])
    download_i("C:\\Users\\venka\\Pictures\\Camera Roll\\venky.jpg","https://scontent-bom1-2.xx.fbcdn.net/v/t39.30808-1/319563728_700360105103496_1862849083292076259_n.jpg?stp=dst-jpg_p320x320&_nc_cat=111&ccb=1-7&_nc_sid=7206a8&_nc_ohc=4o2ZZ6Asso8AX9XdFir&_nc_ht=scontent-bom1-2.xx&oh=00_AfAcRrVgHqh_1ay2J0Be-4DcrYWqHYJMyE_nzwp4V3lqeA&oe=63E58D28")

    #Transform the required image (roll number mod 10) and save it seperately

    dataset_i.__transformitem__("./data/imgs/10050img_00.jpg").save(outputs+"10050_0_g.jpg")

    #Get the predictions from the captioner for the above saved transformed image

    a = captioner(outputs+"10050_0_g.jpg",3)
    print("captions:")
    k=1
    for j in a:
        print(str(k)+")",j)
        k+=1

def main():
    captioner = ImageCaptioningModel()
    experiment('./data/annotations.jsonl', captioner, [RotateImage(45)], ".\\output\\imgs\\") # Sample arguments to call experiment()


if __name__ == '__main__':
    main()