import cv2
import cvzone
from pathlib import Path

path = Path().absolute().parent.parent.parent
img_shapes = cv2.imread(f"{path}/Images/CVZone/shapes.png")

canny = cv2.Canny(img_shapes, 50, 150)
dilated = cv2.dilate(canny, cv2.getStructuringElement(cv2.MORPH_DILATE, (5,5)), iterations=2)

final, contContours = cvzone.findContours(img_shapes, dilated, filter=[8], c=(0,0,0), ct = (0,0,0))

img_stacked = cvzone.stackImages([img_shapes, final], 2, 0.6)
print(contContours[0]['center'])

cv2.imshow("Contornada", final)

cv2.waitKey(0)
cv2.destroyAllWindows()


