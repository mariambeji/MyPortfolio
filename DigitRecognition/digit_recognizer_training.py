
import sys
import cv2
import numpy as np
from picture import Pic


class DigitRecognizerTraining:
    """Class used to train digits on an image"""

    def __init__(self):
        test = Pic(pic_name='test.PNG', contour_w=120, contour_h=184)
        pic1 = Pic(pic_name='pic1.jpg', contour_w=40, contour_h=60)
        pic2 = Pic(pic_name='pic2.jpg', contour_w=63, contour_h=98)
        pic3 = Pic(pic_name='pic3.jpg', contour_w=94, contour_h=135)
        pic4 = Pic(pic_name='pic4.jpg', contour_w=46, contour_h=71)
        pic5 = Pic(pic_name='pic5.jpg', contour_w=90, contour_h=130)
        self.training_pics = [test, pic1, pic2, pic3, pic4,pic5]

    def train(self):
        """Method to train digits"""
        # Loop all images to train
        for training_pic in self.training_pics:
            im = cv2.imread(training_pic.pic_name)
            #img2 = cv2.cvtColor(im, cv2.COLOR_RGB2BGR)
            ## IMAGE PREPARE
            gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
            blur = cv2.medianBlur(gray, 7)
            thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 37, 1)

            contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE) #lawajna aal les contour
            samples = np.empty((0, 100))
            responses = []
            keys = [i for i in range(48, 58)]

            for cnt in contours:
                contour_h = training_pic.contour_h  # for code clarity
                contour_w = training_pic.contour_w
                if cv2.contourArea(cnt) > (training_pic.contour_h * 2):  #surface taa lcontour> h*2?
                    [x, y, w, h] = cv2.boundingRect(cnt)
                    if (h >= 0.9*contour_h) and (h <= 1.1*contour_h) and (w > 0.9*contour_w) and (w < 1.1*contour_w):
                        cv2.rectangle(im, (x - 1, y - 1), (x + 1 + w, y + 1 + h), (0, 0, 255), 1)#draws a rectangle using 2 opposite corners
                        roi = thresh[y:y + h, x:x + w]
                        roismall = cv2.resize(roi, (10, 10))
                        cv2.imshow('Training: Enter digits displayed in the red rectangle!', im)
                        key = cv2.waitKey(0)

                        if key == 27:  # (escape to quit)
                            self.save_data(samples, responses)
                            cv2.destroyAllWindows()
                            sys.exit()
                        elif key in keys:  # (append data)
                            responses.append(int(chr(key)))
                            sample = roismall.reshape((1, 100))
                            samples = np.append(samples, sample, 0)
        # Save collected data
        self.save_data(samples, responses)

    @staticmethod
    def save_data(samples, responses):
        """Method to save trained data"""
        responses = np.array(responses, np.float32)
        responses = responses.reshape((responses.size, 1))
        np.savetxt('ocr_training.data', samples)
        np.savetxt('ocr_responses.data', responses)
        print ("training complete")

# Start the training process
if __name__ == '__main__':
    DigitRecognizerTraining().train()