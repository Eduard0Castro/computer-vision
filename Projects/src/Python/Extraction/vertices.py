import cv2 
from pathlib import Path

path = Path().absolute().parent.parent.parent

square = cv2.imread(f"{path}/Images/Extração/square.jpeg", 0)
triangle = cv2.imread(f"{path}/Images/Extração/triangle.jpeg", 0)

_, binary = cv2.threshold(triangle, 127, 255, cv2.THRESH_BINARY)

contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
perimetro = cv2.arcLength(contours[0], True)
vertices = cv2.approxPolyDP(contours[0], 0.1*perimetro, True)

print(len(vertices))

cv2.imshow("Image", binary)

cv2.waitKey()
cv2.destroyAllWindows()