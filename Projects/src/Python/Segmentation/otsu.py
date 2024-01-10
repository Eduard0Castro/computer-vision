import cv2
from pathlib import Path

path = Path().resolve().parent.parent.parent

coffee = cv2.imread(f"{path}/Images/Segmentação/coffee.jpeg")

gray = cv2.cvtColor(coffee, cv2.COLOR_BGR2GRAY)
threshold, otsu = cv2.threshold(gray, 0, 255, (cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU))


cv2.imshow("Coffee", coffee)
cv2.imshow("Otsu", otsu)

print(threshold)

cv2.waitKey(0)
cv2.destroyAllWindows()
