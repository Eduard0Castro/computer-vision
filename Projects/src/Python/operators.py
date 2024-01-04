import cv2
from pathlib import Path

path = Path().absolute().parent.parent

parking = cv2.imread(f"{path}/Images/Filtros/parking1.bmp")
median = cv2.medianBlur(parking, 3)
bilateral = cv2.bilateralFilter(parking, 10, 75, 75)

sobelX = cv2.Sobel(bilateral, cv2.CV_8U, 1, 0, 3)
sobelY = cv2.Sobel(bilateral, cv2.CV_8U, 0, 1, 3)
laplacian = cv2.Laplacian(bilateral, cv2.CV_8U)


cv2.imshow("Parking", parking)
cv2.imshow("Filtro de mediana", median)
cv2.imshow("Bilateral", bilateral)

cv2.imshow("SobelX", sobelX)
cv2.imshow("SobelY", sobelY)
cv2.imshow("Laplacian", laplacian)

key = cv2.waitKey()

if key == 'q':
    cv2.destroyAllWindows()