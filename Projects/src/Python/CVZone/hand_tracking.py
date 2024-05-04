import cv2
from cvzone.HandTrackingModule import HandDetector

cap = cv2.VideoCapture(0)

hand_detector = HandDetector(staticMode=False, maxHands=3, modelComplexity=1, 
                             detectionCon=0.6, minTrackCon=0.5)

while cv2.waitKey(1) < 0:
    success, frame  = cap.read()
    # frame = cv2.flip(frame, 1)
    hands, img = hand_detector.findHands(frame, True, True)

    if len(hands) > 0:
        handOne = hands[0]
        # handTwo = hands[1]

        lmListOne = handOne["lmList"]
        # lmListTwo = handTwo["lmList"]

        bbox = handOne["bbox"]
        center = handOne["center"]
        handType = handOne["type"]

        fingersOne = hand_detector.fingersUp(handOne)

        tipIndexFingerOne = lmListOne[8][0:2] #indicador: 8 Vai de 4 em 4 as pontas dos dedos
        tipIndexFingerTwo = lmListOne[12][0:2] 


        distance, info, img = hand_detector.findDistance(tipIndexFingerOne, tipIndexFingerTwo, 
                                                            img, color=(0,255,0), scale=3)
        print(distance)

    cv2.imshow("Hands", img)
