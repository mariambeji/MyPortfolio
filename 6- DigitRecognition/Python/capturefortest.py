import cv2
import numpy as np
from PIL import Image

class Camera:
    """Class that opens camera for test"""

    def __init__(self, pic_name='test.jpg'):
        self.pic_name = pic_name

    def filter(self):
        im = cv2.imread(self.pic_name)
        # img2 = cv2.cvtColor(im, cv2.COLOR_RGB2BGR)
        gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
        blur = cv2.medianBlur(gray, 7)
        thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 37, 1)
        return thresh
    def capture(self):
        ##open camera
        cam= cv2.VideoCapture(0)
        # Check if the webcam is opened correctly
        if not cam.isOpened():
            raise IOError("Cannot open webcam")
        while (True):
            frame_width = int(cam.get(3))
            frame_height = int(cam.get(4))
            result, frame = cam.read()
            if result:
                cv2.imshow(self.pic_name, frame)  # display the captured image
                if cv2.waitKey(1) & 0xFF == ord('y'):  # save on pressing 'y'
                    cv2.imwrite(self.pic_name, frame)
                    print('image', self.pic_name , 'was saved', )
                    cv2.destroyAllWindows()
                    break
            else:
                break
        cam.release()

    def flip(self):
        # #if it's flipped
        #img = np.array(Image.open('pic.jpg'))
        #Image.fromarray(np.fliplr(img)).save('flipimg.jpg')
        flipimg=cv2.imread('flipimg.jpg')
        cv2.imshow("flipped image", flipimg)
        cv2.waitKey(0)
        cv2.destroyWindow("flipped image")

# Start the training process
if __name__ == '__main__':
    Camera().capture()


