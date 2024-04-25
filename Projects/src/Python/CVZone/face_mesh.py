import cv2
from cvzone.FaceMeshModule import FaceMeshDetector
from time import time

cap = cv2.VideoCapture(0)

detector = FaceMeshDetector(staticMode=False, maxFaces=1, minDetectionCon=0.5, minTrackCon=0.5)
piscada = 0

time_now = time()

while cv2.waitKey(1)<0:
    success, frame = cap.read()

    if not success:
        break

    img, faces = detector.findFaceMesh(frame, True)

    for face in faces:
        left_eye_upPoint = face[159]
        left_eye_downPoint = face[23]

        distance_eye, info = detector.findDistance(left_eye_downPoint, left_eye_upPoint)
        if distance_eye < 15 and time() - time_now > 0.6:
            piscada+=1
            time_now = time()
            print("Piscadas: {}" .format(piscada))

    cv2.imshow("Faces", img)
    