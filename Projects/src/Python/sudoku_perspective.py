import cv2
import numpy as np
from pathlib import Path

img_path = Path().absolute().parent.parent
sudoku = cv2.imread("{}/Images/sudoku.bmp" .format(img_path))

src = np.float32([[189, 87], [459,84], [192, 373], [484,372]])
dst = np.float32([[0,0], [500,0], [0,500], [500,500]])

matriz = cv2.getPerspectiveTransform(src, dst)
perspective = cv2.warpPerspective(sudoku, matriz, (500,500))

cv2.imshow("Original ", sudoku)
cv2.imshow("Perspective", perspective)
cv2.waitKey(0)




def cut_sudoku():
    sudoku = cv2.imread("{}/Images/sudoku.bmp" .format(img_path))

    crop = sudoku[0:500,0:500]
    cv2.imwrite("{}/Images/sudoku_re.bmp" .format(img_path), crop)

    cv2.imshow("Sudoku", sudoku)
