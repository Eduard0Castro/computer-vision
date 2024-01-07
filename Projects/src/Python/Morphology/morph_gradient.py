import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

rolamento = cv2.imread(f"{path}/Images/Morfologia/rolamento.bmp")

elementoEstruturante = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3,3))
gradient = cv2.morphologyEx(rolamento, cv2.MORPH_GRADIENT, elementoEstruturante)

cv2.imshow("Rolamento", rolamento)
cv2.imshow("Gradiente", gradient)

cv2.waitKey()
cv2.destroyAllWindows()



