import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

video_path = f"{path}/Vídeos/movimentacao.mov"

cap = cv2.VideoCapture(video_path)
min = (160, 100, 100)
max = (200, 255, 255)
struturingElement = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (9,9))
pixels = list()
cont = 0
index = 0


while (cv2.waitKey(25) < 0):
    
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    binary = cv2.inRange(hsv, min, max)
    binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, struturingElement, iterations=2)
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)


    if len(contours) >= 1:
        cont += 1
        perimetro = cv2.arcLength(contours[0], True)
        polygon = cv2.approxPolyDP(contours[0], 0.1*perimetro, True)
        x, y, w, h = cv2.boundingRect(polygon)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0,255,0), 2)

        center = cv2.moments(polygon, True)

        if cont == 10:
            x = int(center["m10"]/center["m00"])
            y = int(center["m01"]/center["m00"])
            pixels.append([x, y])
            cont = 0
            
            distancia = pixels[len(pixels)-1][0] - pixels[index][0]
            if  distancia > 5:
                print("Direita")

            elif distancia < -5:
                print("Esquerda")
            index = len(pixels) -1


    cv2.imshow("Original", frame)
    cv2.imshow("Video", binary)



cap.release()
cv2.destroyAllWindows()