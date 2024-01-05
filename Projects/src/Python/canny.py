import cv2
from pathlib import Path

path = Path().absolute().parent.parent


parking = cv2.imread("{}/Images/Filtros/parking1.bmp" .format(path))
filtrada = cv2.bilateralFilter(parking, 10, 75, 75)
canny = cv2.Canny(filtrada, 100, 200)

cv2.imshow("Parking", parking)
cv2.imshow("Canny", canny)

key = cv2.waitKey()

if key == 'q':
    cv2.destroyAllWindows()