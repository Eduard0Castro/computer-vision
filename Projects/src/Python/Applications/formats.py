import cv2
from pathlib import Path
import numpy as np

path = Path().absolute().parent.parent.parent

video = cv2.VideoCapture(f"{path}/Vídeos/formas-geometricas-480.mov")
medidos = np.zeros(7, int)
index = verticesAnteriores = 0


while (True):
    ret,frame_original = video.read()
    if ret is False:
       break

    gray = cv2.cvtColor(frame_original, cv2.COLOR_BGR2GRAY)
    ret, frame = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

    media = int(cv2.mean(frame)[0])

    if media != 0:
        
        if media == int(cv2.mean(medidos)[0]):

            contours, hierarchy = cv2.findContours(frame, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
            perimetro = cv2.arcLength(contours[0], True)
            poligono = cv2.approxPolyDP(contours[0], 0.03*perimetro, True)
            vertices = len(poligono)

            (x, y), radius = cv2.minEnclosingCircle(poligono)
            center = (int(x), int(y))
            cv2.circle(frame_original, center, int(radius), (0, 255 , 0), 2)
            
            if vertices != verticesAnteriores:
                verticesAnteriores = vertices
                if vertices == 3: print("Triângulo")
                elif vertices == 4: print("Quadrilátero")
                elif vertices > 7 : print("Círculo")  

        medidos[index] = media
        
        if index == 6:
            index = -1

        index += 1


    cv2.imshow("Video", frame_original)

    if cv2.waitKey(10) & 0xFF == ord("q"):
        break

video.release()
cv2.destroyAllWindows()
    