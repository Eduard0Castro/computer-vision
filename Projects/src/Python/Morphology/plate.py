import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

plate = cv2.imread(f"{path}/Images/Morfologia/plate.bmp")


plate = cv2.cvtColor(plate, cv2.COLOR_BGR2GRAY)
_, binary = cv2.threshold(plate, 60, 255, cv2.THRESH_BINARY_INV)
dilate = cv2.dilate(binary, cv2.getStructuringElement(cv2.MORPH_RECT, (5,5)), 5)

# Testando operação de fechamento, que corrige os danos da binarização:
close = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, 
                         cv2.getStructuringElement(cv2.MORPH_RECT, (7,7)))

cv2.imshow("Plate", plate)
cv2.imshow("Binary", binary)
cv2.imshow("Dilated", dilate)
cv2.imshow("Close", close)

cv2.waitKey()
cv2.destroyAllWindows()