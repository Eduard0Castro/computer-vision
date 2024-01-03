import cv2
from pathlib import Path

path = Path().absolute().parent

img = cv2.imread("{}/Images/fifty_cut.bmp" .format(path))

# o segundo parametro das funções são as dimensões da máscara que será aplicada.
# (5,5) significa que as máscara vai pegar os valores dos vizinhos do pixel central (pixel-alvo)
# e a função faz o cálculo do valor médio da vizinhança e substitui no valor do pixel central
average = cv2.blur(img, (5,5))
gaussian = cv2.GaussianBlur(img, (5,5), 0) #último parâmetro é o sigma, 
                                           #que indica o grau de suavização desejado

cv2.imshow("Image", img)
cv2.imshow("Filtro de media", average)
cv2.imshow("Filtro gaussiano", gaussian)

key = cv2.waitKey(0)

if key == 'q':
    cv2.destroyAllWindows()