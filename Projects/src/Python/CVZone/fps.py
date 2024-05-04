import cv2
from cvzone.FPS import FPS


fpsReader = FPS(30)

cap = cv2.VideoCapture(0)

cap.set(cv2.CAP_PROP_FPS, 30)

while cv2.waitKey(1) < 0:
    ret, frame  = cap.read()

    fps, img = fpsReader.update(frame,(20,20), (255,255,255), (0,0,0), 1, 2)
    cv2.imshow("FPS mostra", img)