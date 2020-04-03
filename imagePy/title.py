#!/usr/bin/env python

from PIL import Image, ImageDraw, ImageFont


original = Image.open("image.JPG") # load an image from the hard drive

print(original.size)

(ox,oy)=original.size

xAlign = ox//20

ySpace = oy//8

xy = [ (xAlign,5*ySpace), (xAlign,6*ySpace), (xAlign,7*ySpace) ]

letterHeight = (oy//9)

print(letterHeight)

font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSansBold.ttf", size=letterHeight)
#font = ImageFont.load_default()

color = 'rgb(255, 255, 255)' 

message = ['Morning', 'Synth',  '  ' ]
message2 = 'Episode #{}'

for ep in range (0,10):
    image = original.copy()
    draw = ImageDraw.Draw(image)
    message[2] = message2.format(ep)

    for te in range (0,3):
        draw.text( xy[te], message[te], fill=color, font=font)
    

    
    image.save('./out/ep{}.png'.format(ep), optimize=True, quality=20)    
    
    newsize = (ox//4, oy//4) 
    image = image.resize(newsize)
    #image.show()
    
