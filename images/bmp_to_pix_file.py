import os
from PIL import Image

filename = None
pixels_file = None
while True:
	filename = input("Enter bmp file:")
	pixels_file = input("Enter output file (must exist already):")
	if os.path.isfile(filename) and os.path.isfile(pixels_file):
		break
	else:
		print("output file/bmp file not found")

im = Image.open(filename)
pixels = list(im.getdata())
width, height = im.size
pixels = [pixels[i * width:(i + 1) * width] for i in range(height)]

output = open(pixels_file, "w")
output.write(str(width))
output.write(",")
output.write(str(height))
output.write(",\n")
for pixel in pixels:
	for p in pixel:
		output.write(",".join(str(i) for i in p))
		output.write(",")
	output.write("\n")
	
output.close()
im.close()
