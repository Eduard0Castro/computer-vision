import cv2 
from pathlib import Path

path = Path().absolute().parent.parent.parent

coffee = cv2.imread(f"{path}/Images/Segmentação/coffee.jpeg")
gray = cv2.cvtColor(coffee, cv2.COLOR_BGR2GRAY)

# Só para mostrar que é possível:
binary = gray.copy()
cv2.threshold(gray, 135, 255, cv2.THRESH_BINARY_INV, binary)
cv2.morphologyEx(binary, cv2.MORPH_CLOSE, cv2.getStructuringElement(cv2.MORPH_RECT, (3,3)), binary)
canny = cv2.Canny(binary, 100, 200)

cv2.imshow("Coffee", coffee)
cv2.imshow("Binary", binary)
cv2.imshow("Canny", canny)

cv2.waitKey()
cv2.destroyAllWindows()