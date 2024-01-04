import cv2
from pathlib import Path

path = Path().absolute().parent.parent

fifty = cv2.imread("{}/Images/Filtros/fifty_cut.bmp" .format(path))
SaltPepper = cv2.imread(f"{path}/Images/Filtros/SaltPepper.bmp")

# o segundo parametro das funções são as dimensões 
# da máscara que será aplicada.(5,5) significa que 
# a máscara vai pegar os valores dos vizinhos do 
# pixel central (pixel-alvo) e a função faz o cálculo
# do valor médio da vizinhança e substitui no valor do pixel central
average = cv2.blur(fifty, (5,5))
gaussian = cv2.GaussianBlur(fifty, (5,5), 0) #último parâmetro é o sigma, 
                                             #que indica o grau de suavização desejado
woman = cv2.medianBlur(SaltPepper, 5)

cv2.imshow("Fifty", fifty)
cv2.imshow("Filtro de media", average)
cv2.imshow("Filtro gaussiano", gaussian)

cv2.imshow("Ruido", SaltPepper)
cv2.imshow("Tratada", woman)

key = cv2.waitKey(0)

if key == 'q':
    cv2.destroyAllWindows()