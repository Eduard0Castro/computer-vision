import cv2
from cvzone.SelfiSegmentationModule import SelfiSegmentation
import cvzone
from pathlib import Path

path = Path().absolute().parent.parent.parent
blackbee = cv2.resize(cv2.imread(f"{path}/Images/CVZone/blackbee.png"), (640,480))


cap = cv2.VideoCapture(0)
segmentor = SelfiSegmentation(model=1)

while cv2.waitKey(1) < 0:
    success, frame = cap.read()

    if not success:
        break

    img = segmentor.removeBG(frame, blackbee, 0.3)

    img_stacked = cvzone.stackImages([frame, img], 2, 0.6)
    cv2.imshow("Images", img_stacked)

cap.release()
cv2.destroyAllWindows()
