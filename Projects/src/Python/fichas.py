import cv2
import numpy as np 
from pathlib import Path

img_path = Path().absolute().parent.parent

red_chips = cv2.imread("{}/Images/Fichas/ficha1.bmp" .format(img_path))
black_chips = cv2.imread("{}/Images/Fichas/ficha2.bmp" .format(img_path))
added = cv2.add(red_chips, black_chips)
cv2.imwrite(f"{img_path}/Images/Fichas/fichas_add.bmp", added)




def cut_chips():

    fichas = cv2.imread("{}/Images/Fichas/fichas_juntas.bmp" .format(img_path))
    x = 0
    y = 0
    x2 = 500

    for i in range (3,6):
        
        #Começa com height e depois width (y,x) 
        crop = fichas[y:500, x:x2]
        cv2.imwrite(f"{img_path}/Images/Fichas/ficha{i+1}.bmp", crop)
        x += 540
        x2 += 540
        print(f"Imagem{i+1}")




