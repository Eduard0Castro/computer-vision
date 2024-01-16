import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

puzzle = cv2.imread(f"{path}/Images/Extração/puzzle.bmp")
copy = puzzle.copy()
copy_ellipse = puzzle.copy()
gray = cv2.cvtColor(puzzle, cv2.COLOR_BGR2GRAY)
_, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)


# Retângulo envolvente
contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
x, y, w, h = cv2.boundingRect(contours[0])
cv2.rectangle(puzzle, (x, y), (x + w, y + h), (0, 255, 0), 1)
cv2.imshow("Puzzle", puzzle)


# Círculo envolvente:
(x, y), radius = cv2.minEnclosingCircle(contours[0])
center = (int(x), int(y))
radius = int(radius)
cv2.circle(copy, center, radius, (0, 255, 0), 1)
cv2.imshow("Puzzle circle", copy)


# Elipse envolvente:
ellipse = cv2.fitEllipse(contours[0])
cv2.ellipse(copy_ellipse, ellipse, (0,255,0), 1)
cv2.imshow("Puzzle ellipse", copy_ellipse)

angulo = ellipse[2]

print("Ângulo: ", angulo)

cv2.waitKey()
cv2.destroyAllWindows()