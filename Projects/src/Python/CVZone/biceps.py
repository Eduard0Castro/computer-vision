from cvzone.PoseModule import PoseDetector
import cv2
import cvzone

cap = cv2.VideoCapture(0)

detector = PoseDetector(staticMode=False, # Quando true, detecta em uma única imagem, False detecta em video    
                        modelComplexity=1, # Complexidade do modelo de detecção. Mais complexo, maior po valor, mais pesado
                        smoothLandmarks=True, #Suavizar landmarks
                        enableSegmentation=False, # Segmentar pessoa do do fundo
                        smoothSegmentation=True, # Suavizar a segmentação
                        detectionCon=0.6, 
                        trackCon=0.5)


acoes = {(0,0): "Nada",
         (1,0): "Direito",
         (0,1): "Esquerdo",
         (1,1): "Toma esse double biceps"}

while cv2.waitKey(1) < 0:
    success, frame = cap.read()

    if not success:
        break

    img = detector.findPose(frame)

    lmList, bbox = detector.findPosition(img, draw=False, bboxWithHands=False)

    if lmList:
        # distance, img, info = detector.findDistance(lmList[11][0:2],
        #                                             lmList[15][0:2],
        #                                             img=img, 
        #                                             color=(0,255,0), 
        #                                             scale=5)
        
        angle, img = detector.findAngle(lmList[11][0:2],
                                        lmList[13][0:2],
                                        lmList[15][0:2], img, 
                                        (0,0,255), 10)
        
        angle2, img = detector.findAngle(lmList[12][0:2],
                                lmList[14][0:2],
                                lmList[16][0:2], img, 
                                (0,0,255), 10)
        
        
        isClosedSixty = detector.angleCheck(myAngle=angle,
                                            targetAngle=60,
                                            offset=20)
        
        isClosed3hundred = detector.angleCheck(myAngle=angle2,
                                               targetAngle=300,
                                               offset=20)
        
        pose = (isClosed3hundred, isClosedSixty)

        biceps = acoes.get(pose, None)

        if biceps:

            cvzone.putTextRect(img, biceps, (20, 40), 2, 2, colorT=(0,0,0), colorR=(255,255,255))
            
    cv2.imshow("Pose detection", img)


