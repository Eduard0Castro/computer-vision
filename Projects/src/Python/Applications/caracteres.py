import cv2
from pathlib import Path
import pytesseract

path = Path().absolute().parent.parent.parent

video = f"{path}/Vídeos/caracteres.mov"
valor_anterior = 0
index = 0


cap = cv2.VideoCapture(video)

while cv2.waitKey(10) < 0:
    ret, frame = cap.read()
    if not ret:
        break

    if index == 15:
        valor_atual = pytesseract.image_to_string(frame)

        if valor_anterior != valor_atual:
            valor_anterior = valor_atual
            print(valor_atual)
        index = 0

    index += 1
    cv2.imshow("Video", frame)

cap.release()
cv2.destroyAllWindows()

