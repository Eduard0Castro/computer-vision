import cv2
import numpy as np
import glob

# Chessboard parameters
chessboard_size = (9, 7)  # Number of inner corners on the board (width x height)

# Prepare 3D object points
objp = np.zeros((np.prod(chessboard_size), 3), dtype=np.float32)
objp[:, :2] = np.indices(chessboard_size).T.reshape(-1, 2)

# Lists to store 3D object points and 2D image points
object_points = []
image_points = []

list_of_image_files = glob.glob('./dataset/*.jpg')

# Load and process each image
for image_file in list_of_image_files:
    image = cv2.imread(image_file)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Detect chessboard corners
    ret, corners = cv2.findChessboardCorners(gray, chessboard_size, None)

    # If corners are found, add object and image points
    if ret:
        object_points.append(objp)
        image_points.append(corners)

        # Draw and display the corners
        cv2.drawChessboardCorners(image, chessboard_size, corners, ret)
        cv2.imshow('img', image)
        cv2.waitKey(500)

cv2.destroyAllWindows()

# Calibrate the camera
ret, K, dist, rvecs, tvecs = cv2.calibrateCamera(
    object_points, image_points, gray.shape[::-1], None, None
)

print("Calibration matrix K:\n", K)
print("Distortion:", dist.ravel())