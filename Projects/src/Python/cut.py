import cv2
from pathlib import Path

path = Path().absolute().parent.parent

rolamento = cv2.imread(f"{path}/Images/Segmentação/sudoku.jpeg")


cut = rolamento[0:500,0:500]
cv2.imshow("Rolamento", cut)

cv2.imwrite(f"{path}/Images/Segmentação/sudoku.jpeg", cut)

cv2.waitKey(0)
cv2.destroyAllWindows()
    

def cortando_mulher():

    img = cv2.imread(f"{path}/Images/Filtros/womans.bmp")
    cv2.imshow("Womans", img)

    cut = img[0:500, 0:500]

    cv2.imwrite(f"{path}/Images/Filtros/woman.bmp", cut)

    key = cv2.waitKey(0)

    if key == 'q':
        cv2.destroyAllWindows()

def cortando_simb_radiotividade():
    img = cv2.imread(f"{path}/Images/Filtros/radiotivo.bmp")

    x1 = 0
    x2 = 500

    for i in range(0,3):

        if i == 2:
            x1 = x1 + 4
            x2 = x2 - 4
        cut = img[0:500, x1:x2]
        x1 += 540
        x2 += 540
        cv2.imwrite(f"{path}/Images/Filtros/radio_{i+1}.bmp", cut)

def cortando_fichas_vermelhas():

    fichas = cv2.imread(f"{path}/Images/Fichas/fichas_red.bmp")
    x1 = 0
    x2 = 303

    for i in range(0,4):
        ficha = fichas[0:303,x1:x2]
        cv2.imwrite("{}/Images/Fichas/red{}.bmp" .format(path, i+1), ficha)
        x1 = x2 + 26
        x2 = x1 + 303
