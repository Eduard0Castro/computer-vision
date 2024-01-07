import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

andromeda = cv2.imread(f"{path}/Images/Morfologia/andromeda.bmp")

elementoEstruturante = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))
top_hat = cv2.morphologyEx(andromeda, cv2.MORPH_TOPHAT, elementoEstruturante)

cv2.imshow("Andromeda", andromeda)
cv2.imshow("Sem andromeda", top_hat)

cv2.waitKey()
cv2.destroyAllWindows()