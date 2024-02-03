import cv2 
from pathlib import Path
import numpy as np

path = Path().absolute().parent.parent.parent

chip1 = cv2.imread(f"{path}/Images/Segmentação/cap_ficha1.jpeg")
chip2 = cv2.imread(f"{path}/Images/Segmentação/cap_ficha2.jpeg")

min = np.array([0,120,120])
max = np.array([180, 255,255])

sub = cv2.subtract(chip2, chip1)
cv2.imshow("Sub", sub)

sub = cv2.cvtColor(sub, cv2.COLOR_BGR2HSV)
mask = cv2.inRange(sub, min, max)
mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, 
                        cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (10,10)))
cv2.imshow("Binary", mask)

cv2.waitKey()
cv2.destroyAllWindows()