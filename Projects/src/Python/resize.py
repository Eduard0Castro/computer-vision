import cv2
from pathlib import Path

path = Path().absolute().parent.parent

def resize(img):
    max_width = 600
    width = img.shape[1]
    height = img.shape[0]
    proporcao = width/height

    if width > max_width:
        width = max_width
        height = int(width/proporcao)

        img = cv2.resize(img, (width, height))

    return img


img = cv2.imread(f"{path}/Images/HaarCascade/flamengo.jpg")

cv2.imshow("Original", img)

img = resize(img)

print(img.shape[1])

cv2.imshow("Resized", img)
cv2.waitKey()
cv2.destroyAllWindows()