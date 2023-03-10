from my_package.model import ImageCaptioningModel
from my_package.model import ImageClassificationModel
from tkinter import *
from functools import partial
from PIL import ImageTk, Image
from tkinter import filedialog , messagebox , font


def fileClick(clicked):
	# Define the function you want to call when the filebrowser button (Open) is clicked.
	# This function should pop-up a dialog for the user to select an input image file.
	# To have a better clarity, please check out the sample video. 
	global filename
	a = filedialog.askopenfilename(initialdir = "./data/imgs",title = "Select file",filetypes = (("jpeg files","*.jpg"),("all files","*.*")))
	if(a != ""):
		filename = a
	if(filename != ""):
		imageframe = LabelFrame(root, text="Image" , padx=5, pady=5)
		imageframe.grid(row=1, column=0, columnspan=8 , padx=5, pady=5 , rowspan=2 , sticky=W+E+N+S)
		clicked.delete(0 , END)
		clicked.insert(0, "image-"+filename.split("/")[-1])
		global selected_image
		global label
		selected_image = ImageTk.PhotoImage(Image.open(filename))
		label = Label(imageframe, image=selected_image)
		label.pack()


def process(clicked, captioner, classifier):
	# This function will produce the required output when 'Process' button is clicked.
	# Note: This should handle the case if the user clicks on the `Process` button without selecting any image file.
	if(filename == ""):
		messagebox.showerror("Error", "Please select an image file")
	else:
		if(clicked[0].get() == "" and clicked[1].get() == ""):
			messagebox.showerror("Error", "Please select an option")
		else:
			f = clicked[2]
			fon = font.Font(family=f['family'], size=f['size'], weight=f['weight'], slant=f['slant'], underline=f['underline'], overstrike=f['overstrike'])
			top = Toplevel(root)
			top.title("Processing")
			top.geometry("100x100")
			topframe = LabelFrame(top, text="Processing" , padx=5, pady=5)
			topframe.grid(row=0, column=0 , padx=5, pady=5 , rowspan=1 , sticky=W+E+N+S)
			toplabel = Label(topframe, text="Processing...")
			toplabel.pack()
			top.update()
			global captframe
			global classframe
			global captions
			global classes
			global caplabel
			global classlabel
			if(clicked[0].get() == "classification" and clicked[1].get() == "captioning"):
				captframe = LabelFrame(root, text="Captions of " + filename.split("/")[-1] , padx=5, pady=5 )
				classframe = LabelFrame(root, text="Classifications of " + filename.split("/")[-1] , padx=5, pady=5 )
				captframe.grid(row=1, column=8 , padx=5, pady=5 , rowspan=1 , sticky=W+E+N+S , columnspan=6)
				classframe.grid(row=2, column=8 , padx=5, pady=5 , rowspan=1 , sticky=W+E+N+S , columnspan=6)
				caption = captioner(filename)
				classe = classifier(filename)
				top.destroy()
				captions = "Top 3 captions are:\n"
				classes = "Top 3 classes are:\n"
				for i in range(3):
					captions += str(i+1) + ") " + (caption[i] + "\n").capitalize()
					classes += str(i+1) + ") " + str(round(float(classe[i][0])*100,2)) + " percent of " + classe[i][1] + "\n"
				caplabel = Label(captframe, text=captions , font=fon )
				classlabel = Label(classframe, text=classes , font=fon)
				caplabel.pack()
				classlabel.pack()
			elif(clicked[0].get() == "classification"):
				classframe = LabelFrame(root, text="Classifications of " + filename.split("/")[-1] , padx=5, pady=5)
				classframe.grid(row=1, column=8 , padx=5, pady=5 , rowspan=2 , sticky=W+E+N+S , columnspan=6)
				classe = classifier(filename)
				top.destroy()
				classes = "Top 3 classes are:\n"
				for i in range(3):
					classes += str(i+1) + ") " + str(round(float(classe[i][0])*100,2)) + " percent of " + classe[i][1] + "\n"
				classlabel = Label(classframe, text=classes , font=fon , foreground=f['color'])
				classlabel.pack()
			elif(clicked[1].get() == "captioning"):
				captframe = LabelFrame(root, text="Captions of " + filename.split("/")[-1] , padx=5, pady=5)
				captframe.grid(row=1, column=8 , padx=5, pady=5 , rowspan=2 , sticky=W+E+N+S , columnspan=6)
				caption = captioner(filename)
				top.destroy()
				captions = "Top 3 captions are:\n"
				for i in range(3):
					captions += str(i+1) + ") " + (caption[i] + "\n").capitalize()
				caplabel = Label(captframe, text=captions , font=fon , foreground=f['color'])
				caplabel.pack()




if __name__ == '__main__':
	# Complete the main function preferably in this order:
	# Instantiate the root window.
	# Provide a title to the root window.
	# Instantiate the captioner, classifier models.
	# Declare the file browsing button.
	# Declare the drop-down button.
	# Declare the process button.
	# Declare the output label.
	root = Tk()
	root.title("Image captioner and classification Viewer")
	captioner = ImageCaptioningModel()
	classifier = ImageClassificationModel()
	filename = ""
	entry = Entry(root)
	entry.grid(row=0, column=0)
	browsebutton = Button(root, text="Browse", command=lambda: fileClick(entry))
	browsebutton.grid(row=0, column=1)
	clasvar = StringVar()
	capvar = StringVar()
	clascheckbox = Checkbutton(root, text="Classification", variable=clasvar, onvalue="classification", offvalue="")
	capcheckbox = Checkbutton(root, text="Captioning", variable=capvar, onvalue="captioning", offvalue="")
	clascheckbox.grid(row=0, column=2)
	capcheckbox.grid(row=0, column=3)
	fonttype = Label(root, text="Font type:")
	fonttype.grid(row=0, column=4)
	fontcolor = Label(root, text="Font color:")
	fontcolor.grid(row=0, column=6)
	colorvar = StringVar()
	colorvar.set("black")
	colordropdown = OptionMenu(root, colorvar, "black", "white", "red", "green", "blue", "yellow", "cyan", "magenta")
	colordropdown.grid(row=0, column=7)
	fontsize = Label(root, text="Font size:")
	fontsize.grid(row=0, column=8)
	sizevar = IntVar()
	sizecheck = Spinbox(root, from_=1, to=100 , textvariable=sizevar , width=3)
	sizecheck.grid(row=0, column=9)
	sizevar.set(9)
	fontvar = StringVar()
	fontvar.set("Segoe UI")
	fontdropdown = OptionMenu(root, fontvar, "Segoe UI", "Arial", "Times New Roman", "Courier New", "Verdana", "Tahoma", "Calibri", "Comic Sans MS", "Impact", "Lucida Console", "Lucida Sans Unicode", "MS Sans Serif", "MS Serif", "Symbol", "System", "Wingdings")
	fontdropdown.grid(row=0, column=5)
	boldvar = StringVar()
	boldcheck = Checkbutton(root, text="Bold", variable=boldvar, onvalue="bold", offvalue="normal")
	boldcheck.deselect()
	boldcheck.grid(row=0, column=10)
	italicvar = StringVar()
	italiccheck = Checkbutton(root, text="Italic", variable=italicvar, onvalue="italic", offvalue="roman")
	italiccheck.deselect()
	italiccheck.grid(row=0, column=11)
	underlinevar = IntVar()
	underlinecheck = Checkbutton(root, text="Underline", variable=underlinevar, onvalue=1, offvalue=0)
	underlinecheck.deselect()
	underlinecheck.grid(row=0, column=12)
	processbutton = Button(root, text="Process", command=lambda: process([clasvar , capvar , {'family': fontvar.get() , 'weight': boldvar.get() , 'slant': italicvar.get() , 'underline': underlinevar.get() , 'overstrike': 0 , 'size': sizevar.get() , 'color': colorvar.get()}], captioner, classifier), font=font.Font(family = "Impact" , size = 10 , weight = "bold" , slant = "italic" , underline = 0 , overstrike = 0 ), foreground="black" , background="red" , activeforeground="white" , activebackground="blue")
	processbutton.grid(row=0, column=13)
	root.mainloop()

