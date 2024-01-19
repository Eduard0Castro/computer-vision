import cv2
from pathlib import Path

path = Path().absolute().parent.parent

img = cv2.imread(f"{path}/Images/HaarCascade/flamengo.jpg")

resized = cv2.resize(img, (666, 499))

cv2.imwrite(f"{path}/Images/HaarCascade/flamengo.jpg", resized)

cv2.imshow("Flamengo", resized)

cv2.waitKey()
cv2.destroyAllWindows()