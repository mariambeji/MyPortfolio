import cv2

import numpy as np
from PIL import Image
from capturefortest import Camera

name=['pic1.jpg', 'pic2.jpg', 'pic3.jpg', 'pic4.jpg', 'pic5.jpg']

for i in range(5):
    Cam = Camera(name[i])
    Cam.capture()


