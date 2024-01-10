import cv2
from pathlib import Path 
import numpy as np

path = Path().resolve().parent.parent.parent

cube = cv2.imread(f"{path}/Images/Segmentação/cube.jpeg")
cv2.imshow("Cube", cube)

cube = cv2.cvtColor(cube, cv2.COLOR_BGR2HSV)
min = np.array([160,100,100])
max = np.array([200,255,255])

mask  = cv2.inRange(cube, min, max)
mask  = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, 
                 cv2.getStructuringElement(cv2.MORPH_RECT, (5,5)))

cv2.imshow("Mascara", mask)
cv2.waitKey()
cv2.destroyAllWindows()