import os
import sys
import numpy as np
from PIL import Image

def read_png(file):
    img = Image.open(file)
    img = img.convert('RGBA')
    img = np.array(img)
    return img

def convert_to_code(img):
    code = ""
    y = 0
    for row in img:
        x = 0
        for pixel in row:
            r = pixel[0]
            g = pixel[1]
            b = pixel[2]
            hex_string = f"0x{r:02x}{g:02x}{b:02x}"
            if pixel[3] == 0:
                code += "0x0f0f0f, "
            else:
                code += f"{hex_string}, "
            x += 1
        y += 1
    return code

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 png_to_code.py <file>")
        sys.exit(1)

    file = sys.argv[1]
    if not os.path.exists(file):
        print(f"File {file} not found")
        sys.exit(1)

    img = read_png(file)
    code = convert_to_code(img)
    print(code)

if __name__ == "__main__":
    main()