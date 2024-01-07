import cv2
from pathlib import Path

path  = Path().absolute().parent.parent.parent

gear = cv2.imread(f"{path}/Images/Morfologia/engrenagem.bmp")

elementoEstruturante = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))
erosao = cv2.erode(gear, elementoEstruturante, 1)
abertura = cv2.morphologyEx(gear, cv2.MORPH_OPEN, elementoEstruturante)

cv2.imshow("Gear", gear)
cv2.imshow("Erosao", erosao)
cv2.imshow("Abertura", abertura)

cv2.waitKey()
cv2.destroyAllWindows()
