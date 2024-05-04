import cv2
import cvzone
import cvzone.ColorModule 

cap = cv2.VideoCapture(0)
color_finder = cvzone.ColorModule.ColorFinder(False)

hsv_values = {'hmin': 0, 'smin': 156, 'vmin': 97, 'hmax': 179, 'smax': 255, 'vmax': 160}

while cv2.waitKey(1)<0:
    success, img = cap.read()

    if not success:
        break

    detected, mask = color_finder.update(img, hsv_values)
    contornada, con_found = cvzone.findContours(img, mask, c=(0,255,0), )
    if len(con_found) > 0:
        bbox = con_found[0]['bbox']
        cvzone.putTextRect(contornada, "Vermelho", (bbox[0]+bbox[2], bbox[1]), 2 , 1,
                           colorT=(0,0,0), colorR=(255,255,255))

    stacked = cvzone.stackImages([img, detected, mask, contornada], 2, 0.6)

    cv2.imshow("Result", stacked)


