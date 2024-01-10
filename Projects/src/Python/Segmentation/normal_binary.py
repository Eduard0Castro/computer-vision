import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent
print(path)

coffee = cv2.imread(f"{path}/Images/Segmentação/coffee.jpeg")
gray = cv2.cvtColor(coffee, cv2.COLOR_BGR2GRAY)
_, binary = cv2.threshold(gray, 135, 255, cv2.THRESH_BINARY_INV)
binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, 
                          cv2.getStructuringElement(cv2.MORPH_RECT, (3,3)))

cv2.imshow("Coffee", coffee)
cv2.imshow("Binary", binary)

cv2.waitKey()
cv2.destroyAllWindows()