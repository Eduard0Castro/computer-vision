import cv2
from pathlib import Path 

path = Path().absolute().parent.parent.parent

ruido_ex = cv2.imread(f"{path}/Images/Morfologia/rolamento_ruido.bmp")
ruido_in = cv2.imread(f"{path}/Images/Morfologia/ruido_interno.bmp")

open = cv2.morphologyEx(ruido_ex, cv2.MORPH_OPEN, 
                        cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3,3)))
close = cv2.morphologyEx(ruido_in, cv2.MORPH_CLOSE, 
                         cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5)))

cv2.imshow("Ruido Externo", ruido_ex)
cv2.imshow("Abertura", open)
cv2.imshow("Ruido Interno", ruido_in)
cv2.imshow("Fechamento", close)

cv2.waitKey(0)
cv2.destroyAllWindows()