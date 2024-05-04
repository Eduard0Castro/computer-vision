import cv2
import cvzone
from pathlib import Path

import cvzone.Utils

path = Path().absolute().parent.parent.parent
print(path)

cap = cv2.VideoCapture(0)
blackbee = cv2.imread(f"{path}/Images/CVZone/blackbee.png", cv2.IMREAD_UNCHANGED)
blackbee = cv2.resize(blackbee, (100,100))
unifei = cv2.imread(f"{path}/Images/CVZone/unifei.png", cv2.IMREAD_UNCHANGED)
unifei = cv2.resize(unifei, (100,100))



while cv2.waitKey(1) < 0:

    sucess, frame = cap.read()
    cvzone.cornerRect(frame, (150, 150, 300, 300), colorR=(0,0,255))
    frame = cvzone.overlayPNG(frame, blackbee, (10,10))
    frame = cvzone.overlayPNG(frame, unifei, (frame.shape[1]-unifei.shape[1]-10, 10))

    rotated = cvzone.Utils.rotateImage(frame, 45)
    rotated = cv2.resize(rotated, (640,480))

    canny = cv2.Canny(frame, 50, 150)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    stackedImg = cvzone.stackImages([frame, gray, canny, rotated], 2, 0.6)

    cv2.imshow("All of them", stackedImg)