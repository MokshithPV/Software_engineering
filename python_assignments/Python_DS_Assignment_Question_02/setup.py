from setuptools import setup
setup(
    name = "21CS10050_package",
    version= "0.0.1",
    description= "Image captioning model",
    author= "Mokshith",
    author_email= "venkatsaimokshithp@gmail.com",
    packages= ["my_package","my_package.data","my_package.data.transforms"],
    install_requires = ["numpy==1.21.5","opencv-python-headless","Pillow==9.4.0","spacy","torchvision","jsonlines==3.1.0"]
)