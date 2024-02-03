import cv2
from pathlib import Path
import numpy as np

path = Path().absolute().parent.parent.parent
video = cv2.VideoCapture(f"{path}/Vídeos/objetos-coloridos-480.mov")
index = 0
lastscreen = 0
contb = contg = contr = 0


while True:
    ret, frame = video.read()
    if ret is False: break
    
    index += 1
    media = cv2.mean(frame)
    maior = np.amax(media)
    

    if index == 30:
        if int(media[0]) == int(media[2]):
            lastscreen = 0
        else:

            if lastscreen == 0:
                lastscreen = 1
                print("Oi")
                if media[0] == maior:
                    print("Tampa azul!")
                    contb += 1
                elif media[1] == maior:
                    print("Tampa verde!")
                    contg += 1
                else:
                    print("Tampa vermelha")
                    contr += 1

        index = 0


    cv2.imshow("Video", frame)

    if(cv2.waitKey(10) & 0xFF == ord("q")):
        break

print("Tampas azuis: {}" .format(contb))
print("Tampas verdes: {}" .format(contg))
print("Tampas vermelhas: {}" .format(contr))
