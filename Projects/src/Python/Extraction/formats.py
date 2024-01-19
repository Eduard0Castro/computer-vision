import cv2 
from pathlib import Path

path = Path().absolute().parent.parent.parent

square = cv2.imread(f"{path}/Images/Extração/square.jpeg")
triangle = cv2.imread(f"{path}/Images/Extração/triangle.jpeg")
circle = cv2.imread(f"{path}/Images/Extração/circle.jpeg")

# Passando para escala de cinza, binária e canny:
gray = cv2.cvtColor(circle, cv2.COLOR_BGR2GRAY)
_, binary = cv2.threshold(gray, 127, 255, (cv2.THRESH_BINARY))
canny = cv2.Canny(binary, 200, 250)

# Primeira forma para encontrar área e perímetro:
contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
area = cv2.contourArea(contours[0])
perimetro = cv2.arcLength(contours[0], True)

print("Área: ", area)
print("Perímetro: {:.2f}" .format(perimetro))

# Segunda forma para encontrar área e perímetro:
area = 0
perimetro = 0
for x in range (0, binary.shape[0]):
    for y in range (0, binary.shape[1]):
        if binary [x, y] == 255:
            area += 1

        if canny[x, y] == 255:
            perimetro += 1

print("\nContagem área: ", area)
print("Contagem perímetro: ", perimetro)


cv2.waitKey()
cv2.destroyAllWindows()
