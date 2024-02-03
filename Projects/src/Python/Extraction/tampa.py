import cv2
from pathlib import Path
from statistics import mode

path = Path().absolute().parent.parent.parent

tampa_bgr = cv2.imread(f"{path}/Images/Extração/tampa3.jpeg")
tampa_cinza = cv2.imread(f"{path}/Images/Extração/tampa2.jpeg")
tampa_bin = cv2.imread(f"{path}/Images/Extração/tampa1.jpeg")

tampa_cinza = cv2.cvtColor(tampa_cinza, cv2.COLOR_BGR2GRAY)

cv2.imshow("Tampa cinza", tampa_cinza)
cv2.imshow("Tampa binaria", tampa_bin)

# Moda das imagens:
moda_cinza = mode(tampa_cinza.ravel())
moda_bin = mode(tampa_bin.ravel())

print(moda_cinza)
print(moda_bin)

print()

# Média das cores em cada canal:
print(cv2.mean(tampa_bgr))
print(cv2.mean(tampa_cinza))

_, binary = cv2.threshold(tampa_cinza, 220, 255, cv2.THRESH_BINARY_INV)
binary = cv2.morphologyEx(binary, cv2.MORPH_OPEN, 
                          cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3,3)))

cv2.imshow("Binary", binary)
cv2.waitKey()
cv2.destroyAllWindows()