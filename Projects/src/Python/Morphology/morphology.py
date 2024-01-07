import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

rolamento = cv2.imread(f"{path}/Images/Morfologia/rolamento.bmp")

eroded = cv2.erode(rolamento, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (6,6)), 2)
dilated = cv2.dilate(rolamento, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5)), 2)

cv2.imshow("Original", rolamento)
cv2.imshow("Eroded", eroded)
cv2.imshow("Dilated", dilated)

key = cv2.waitKey()
cv2.destroyAllWindows()