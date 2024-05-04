import cv2
import numpy as np


cap  = cv2.VideoCapture(0)

mat_min = 87
mat_max = 146
sat_min = 147
sat_max = 255
brilho_min = 100
brilho_max = 255

cv2.namedWindow("Barra de Selecao", cv2.WINDOW_AUTOSIZE)


cv2.createTrackbar("Mat Min", "Barra de Selecao", mat_min, 255, lambda value:value)
cv2.createTrackbar("Mat Max", "Barra de Selecao", mat_max, 255, lambda value:value)

cv2.createTrackbar("Sat Min", "Barra de Selecao", sat_min, 255, lambda value:value)
cv2.createTrackbar("Sat Max", "Barra de Selecao", sat_max, 255, lambda value:value)

cv2.createTrackbar("Brilho min", "Barra de Selecao", brilho_min, 255, lambda value:value)
cv2.createTrackbar("Brilho Max", "Barra de Selecao", brilho_max, 255, lambda value:value)



while True:
    _, cam = cap.read()

    
    min = np.array([mat_min, sat_min, brilho_min])
    max = np.array([mat_max, sat_max, brilho_max])

    cam = cv2.flip(cam, 1)
    img_hsv = cv2.cvtColor(cam, cv2.COLOR_BGR2HSV)

    mask = cv2.inRange(img_hsv, min, max)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, 
                     cv2.getStructuringElement(cv2.MORPH_RECT, (3,3)), iterations = 2)

    cv2.imshow("Camera", cam)
    cv2.imshow("Mascara", mask)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
    

