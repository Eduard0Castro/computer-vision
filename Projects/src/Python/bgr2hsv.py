import cv2
import numpy as np

bgr = np.uint8([[[0,0,255]]])
hsv = cv2.cvtColor(bgr, cv2.COLOR_BGR2HSV)

hsv2 = np.uint8([[[0,255,255]]])
bgr2 = cv2.cvtColor(hsv2, cv2.COLOR_HSV2BGR)

print (hsv)
print (bgr2)
