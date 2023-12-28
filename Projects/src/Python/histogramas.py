import cv2
import pathlib
from matplotlib import pyplot as grafico

img_path = pathlib.Path().absolute().parent.parent
img = cv2.imread(f"{img_path}/Images/clock.bmp")

img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
equalizated = cv2.equalizeHist(img)

cv2.imshow("Clock", img)
cv2.imshow("Equalizated", equalizated)

grafico.hist(img.ravel(), 256, (0,255))
grafico.figure()

grafico.hist(equalizated.ravel(), 256, (0,255))
grafico.show()
# blue, green, red = cv2.split(img)

# grafico.hist(blue.ravel(), 256, (0, 255))
# grafico.figure()

# grafico.hist(green.ravel(), 256, (0, 255))
# grafico.figure()

# grafico.hist(red.ravel(), 256, (0, 255))
# grafico.show()
cv2.waitKey(0)
cv2.destroyAllWindows

