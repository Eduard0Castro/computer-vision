import cv2
from pathlib import Path
import numpy as np

path = Path().absolute().parent.parent.parent

def Hu(src):
    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    _,binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

    moments = cv2.moments(binary, True)
    hu = cv2.HuMoments(moments)
    print(moments)

    # Valores tratados com transformação logaritmica apresentam
    # melhor resultado com figuras planas
    print(-np.sign(hu) * np.log10(np.abs(hu)))
    print()
    


rodela1 = cv2.imread(f"{path}/Images/Extração/rodela1.jpeg")
rodela2 = cv2.imread(f"{path}/Images/Extração/rodela2.jpeg")
rodela3 = cv2.imread(f"{path}/Images/Extração/rodela3.jpeg")

Hu(rodela1)
Hu(rodela2)
Hu(rodela3)

