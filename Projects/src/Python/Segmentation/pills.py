import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

pills = cv2.imread(f"{path}/Images/Segmentação/pills.jpeg")

# Binarização Global:
_, normal_binary = cv2.threshold(pills, 70, 255, cv2.THRESH_BINARY)
normal_binary = cv2.erode(normal_binary,
                          cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3,3)))


# Binarização Adaptativa
gray = cv2.cvtColor(pills, cv2.COLOR_BGR2GRAY)
filtered = cv2.medianBlur(gray, 7)
adaptive_binary = cv2.adaptiveThreshold(filtered, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, 
                                            cv2.THRESH_BINARY_INV, 11, 5)

cv2.imshow("Pills", pills)
cv2.imshow("Normal binary", normal_binary)
cv2.imshow("Adaptative binary", adaptive_binary)

cv2.waitKey()
cv2.destroyAllWindows()