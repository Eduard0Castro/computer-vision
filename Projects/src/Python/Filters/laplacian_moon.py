import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

moon = cv2.imread(f"{path}/Images/Filtros/moon.bmp")
laplacian_moon = cv2.Laplacian(moon, cv2.CV_8U)
final = cv2.subtract(moon, laplacian_moon)

cv2.imshow("Moon", moon)
cv2.imshow("Laplacian moon", laplacian_moon)
cv2.imshow("Final", final)

cv2.waitKey()
cv2.destroyAllWindows()



