import cv2
import cvzone
from cvzone.FaceDetectionModule import FaceDetector

cap = cv2.VideoCapture(0)

face_detector = FaceDetector(minDetectionCon=0.5, modelSelection=0)

while cv2.waitKey(1) < 0:
    success, img = cap.read()

    img, bboxs = face_detector.findFaces(img, False)


    if bboxs:

        for bbox in bboxs:
            center = bbox["center"]
            x, y, w, h = bbox["bbox"]
            score = int(bbox["score"][0]*100)

            cv2.circle(img, center, 5, (0,255,0), cv2.FILLED)
            cvzone.putTextRect(img, f"{score}%", (x-10, y-10), 2)
            cvzone.cornerRect(img, [x, y, w, h])

    cv2.imshow("Faces", img)

