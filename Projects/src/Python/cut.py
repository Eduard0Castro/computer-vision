import cv2
from pathlib import Path 

path = Path().absolute().parent.parent

fichas = cv2.imread(f"{path}/Images/Fichas/fichas_red.bmp")

x1 = 0
x2 = 303

for i in range(0,4):
    ficha = fichas[0:303,x1:x2]
    cv2.imwrite("{}/Images/Fichas/red{}.bmp" .format(path, i+1), ficha)
    x1 = x2 + 26
    x2 = x1 + 303


cv2.waitKey(0)
cv2.destroyAllWindows
