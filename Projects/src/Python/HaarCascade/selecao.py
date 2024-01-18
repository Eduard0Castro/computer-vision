import cv2
from pathlib import Path

path = Path().absolute().parent.parent.parent

selecao = cv2.imread(f"{path}/Images/HaarCascade/selecao.jpg")
haarcascade = cv2.CascadeClassifier(f"{path}/XML/haarcascade_frontalface_default.xml")

gray = cv2.cvtColor(selecao, cv2.COLOR_BGR2GRAY)

faces = haarcascade.detectMultiScale(gray, 1.3, 5, 0, (30,30))

for (x, y, w, h) in faces:
    cv2.rectangle(selecao, (x, y), (x + w, y + h), (0, 0, 255), 2)

print(f"Número de faces: {len(faces)}")
cv2.imshow("Selecao", selecao)

cv2.waitKey()
cv2.destroyAllWindows()