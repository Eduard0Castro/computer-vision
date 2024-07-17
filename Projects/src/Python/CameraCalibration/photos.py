import cv2
from time import sleep

cap = cv2.VideoCapture(0)

for i in range(100):
    success, frame = cap.read()

    if not success:
        break

    sleep(0.2)

    cv2.imwrite(f"dataset/chessboard{i}.jpg", frame)

    cv2.waitKey(1)
