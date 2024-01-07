import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent


parking = cv2.imread("{}/Images/Filtros/parking1.bmp" .format(path))

bilateral = cv2.bilateralFilter(parking, 10, 75, 75)
gaussian = cv2.GaussianBlur(parking, (5,5), 0)

canny = cv2.Canny(parking, 100, 200)
canny_gaussian = cv2.Canny(gaussian, 100, 200)
canny_bilateral = cv2.Canny(bilateral, 100,200)

cv2.imshow("Parking", parking)
cv2.imshow("Canny", canny)
cv2.imshow("Canny Gaussian", canny_gaussian)
cv2.imshow("Canny bilateral", canny_bilateral)


cv2.waitKey()
cv2.destroyAllWindows()