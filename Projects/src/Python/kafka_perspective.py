import cv2
from pathlib import Path
import numpy as np

img_path = Path().absolute().parent.parent

kafka = cv2.imread("{}/Images/Perspective/franz.jpg" .format(img_path))
resized = cv2.resize(kafka, [365, 650])
cv2.imshow("Franz", resized)
print(img_path)

src = np.float32([[46,347], [167,295], [226,476], [346,370]])
dst = np.float32([[0,0], [200,0], [0,350], [200, 350]])

matriz_trans = cv2.getPerspectiveTransform(src, dst)

modificada = cv2.warpPerspective(resized, matriz_trans, (200,350))
cv2.imshow("Modificada", modificada)

cv2.waitKey(0)


