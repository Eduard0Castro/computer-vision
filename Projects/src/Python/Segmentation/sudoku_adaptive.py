import cv2
from pathlib import Path
import numpy as np

path = Path().resolve().parent.parent.parent

sudoku = cv2.imread(f"{path}/Images/Segmentação/sudoku.jpeg")

#Perspectiva sudoku:

width = 282
height = 292
src = np.float32([[55,99], [337,99], 
                 [55,395], [337,392]])
dst = np.float32([[0,0], [width, 0], 
                 [0, height], [width, height]])

matriz = cv2.getPerspectiveTransform(src, dst)
sudoku = cv2.warpPerspective(sudoku, matriz, (width, height))

# Binarização:
gray = cv2.cvtColor(sudoku, cv2.COLOR_BGR2GRAY)
_, binaria_normal = cv2.threshold(gray, 125, 255, cv2.THRESH_BINARY_INV)
adaptive_binary = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, 
                                        cv2.THRESH_BINARY_INV, 11, 10)

cv2.imshow("Sudoku", sudoku)
cv2.imshow("Binaria Global", binaria_normal)
cv2.imshow("Binaria adaptativa", adaptive_binary)

cv2.waitKey()
cv2.destroyAllWindows()