import cv2
import pathlib
from matplotlib import pyplot as grafico

img_path = pathlib.Path(__file__)
print(img_path)
img = cv2.imread("/home/eduardocastro/Computer_Vision/Projects/Images/fruits.jpg")
  
cv2.imshow("Fruits", img)

cv2.waitKey(0)
cv2.destroyAllWindows()
