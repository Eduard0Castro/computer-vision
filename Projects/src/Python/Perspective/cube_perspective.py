import cv2 
from pathlib import Path
import numpy as np  

path = Path().absolute().parent.parent.parent

cube = cv2.imread("{}/Images/Perspective/cube.jpeg" .format(path))

cv2.imshow("Cube", cube)

src = np.float32([[55, 179], [208,212], [126, 386], [279, 427]])
dst = np.float32([[0, 0], [150, 0], [0, 150], [150,150]])


matriz = cv2.getPerspectiveTransform(src, dst)
final_cube = cv2.warpPerspective(cube, matriz, (150,150))


cv2.imshow("Cube", final_cube)
cv2.waitKey()
cv2.destroyAllWindows()

#57, 179
#208,211
#128,386
#279,425
