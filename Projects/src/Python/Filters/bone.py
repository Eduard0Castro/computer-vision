import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

bone = cv2.imread("{}/Images/Filtros/bone.bmp" .format(path))

gaussian = cv2.GaussianBlur(bone, (13,13), 3)
bordas = 3*cv2.subtract(bone, gaussian)
final = cv2.add(bone, bordas)

cv2.imshow("Original", bone)
cv2.imshow("Gaussiana", gaussian)
cv2.imshow("Bordas", bordas)
cv2.imshow("Final", final)

cv2.waitKey()
cv2.destroyAllWindows()

