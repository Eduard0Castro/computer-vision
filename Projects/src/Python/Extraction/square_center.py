import cv2 
from pathlib import Path

path = Path().absolute().parent.parent.parent

square = cv2.imread(f"{path}/Images/Extração/square.jpeg", 0)

moments = cv2.moments(square, True)

cx = int(moments['m10']/moments['m00'])
cy = int(moments['m01']/moments['m00'])

print(cx, cy)