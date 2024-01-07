import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

rice = cv2.imread(f"{path}/Images/Morfologia/arroz.bmp")

open = cv2.morphologyEx(rice, cv2.MORPH_OPEN, 
                        cv2.getStructuringElement(cv2.MORPH_CROSS, (100,100)))
subt = cv2.subtract(rice, open)
added = cv2.add(subt, subt)

# As três operações feitas anteriormente podem ser simplificadas em duas:
top_hat = cv2.morphologyEx(rice, cv2.MORPH_TOPHAT,
                           cv2.getStructuringElement(cv2.MORPH_CROSS, (100,100)))
added_th = cv2.add(top_hat, top_hat)

cv2.imshow("Arroz", rice)
cv2.imshow("Abertura", open)
cv2.imshow("Subtraida", subt)
cv2.imshow("Adicionada", added)
cv2.imshow("Top Hat adicionada", added_th)

cv2.waitKey()
cv2.destroyAllWindows()