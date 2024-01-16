import cv2 
from pathlib import Path

path = Path().absolute().parent.parent.parent

hole_1 = cv2.imread(f"{path}/Images/Extração/hole_1.bmp", 0)
hole_2 = cv2.imread(f"{path}/Images/Extração/hole_2.bmp", 0)
hole_3 = cv2.imread(f"{path}/Images/Extração/hole_3.bmp", 0)

_, binary = cv2.threshold(hole_3, 127, 255, cv2.THRESH_BINARY)
contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

holes = len(contours) - 1

print(holes)

cv2.imshow("Holes", binary)

cv2.waitKey()
cv2.destroyAllWindows()


