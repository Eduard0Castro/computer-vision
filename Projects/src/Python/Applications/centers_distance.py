import cv2 
import numpy as np
from pathlib import Path
from math import sqrt, pow

path = Path().absolute().parent.parent.parent
video_path = f"{path}/Vídeos/movimentacao.mov"
cap = cv2.VideoCapture(video_path)

while cv2.waitKey(20) < 0:
    
    ret, frame = cap.read()
    if not ret:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    _, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY_INV)
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours) == 2:
        c1 = cv2.moments(contours[0], True)
        c2 = cv2.moments(contours[1], True)

        c1x = c1["m10"]/c1["m00"]
        c1y = c1["m01"]/c1["m00"]
        c2x = c2["m10"]/c2["m00"]
        c2y = c2["m01"]/c2["m00"]

        distancia = sqrt(pow(c2x - c1x, 2) + pow(c2y - c1y, 2))
        print("Distância: {:.2f}" .format(distancia))

    cv2.imshow("Video", frame)


cap.release()
cv2.destroyAllWindows()

