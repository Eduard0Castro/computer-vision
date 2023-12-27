import cv2
import pathlib
from matplotlib import pyplot as grafico

img_path = pathlib.Path().absolute().parent.parent
img = cv2.imread(f"{img_path}/Images/folha.bmp")
  


blue, green, red = cv2.split(img)

grafico.hist(blue.ravel(), 256, (0, 256))
grafico.figure()

grafico.hist(green.ravel(), 256, (0, 256))
grafico.figure()

grafico.hist(red.ravel(), 256, (0, 256))
grafico.show()

