
import cv2
import numpy as np
from picture import Pic
from testdigit import FontSize

class DigitRecognizerTesting:
    """Class used to test digits on an image"""

    def __init__(self):
        self.image_to_test = Pic(pic_name="test.jpg", contour_w=49, contour_h=63)
        self.load_training_data()
        self.model = cv2.ml.KNearest_create()
        self.model.train(self.samples, cv2.ml.ROW_SAMPLE, self.responses)
        FontSize.picture = self.image_to_test

    def load_training_data(self):
        self.samples = np.loadtxt('ocr_training.data', np.float32)
        self.responses = np.loadtxt('ocr_responses.data', np.float32)
        self.responses = self.responses.reshape((self.responses.size, 1))

    def test(self):
        contour_h = self.image_to_test.contour_h  # for code clarity
        contour_w = self.image_to_test.contour_w
        im = cv2.imread(self.image_to_test.pic_name)
        out = np.zeros(im.shape, np.uint8)
        print("contours:", contour_h, contour_w)
        ## IMAGE FILTERS
        gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
        blur = cv2.medianBlur(gray, 7)
        thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 37, 1)

        number_output = "";
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        for cnt in contours:
            if cv2.contourArea(cnt) > contour_h:
                [x, y, w, h] = cv2.boundingRect(cnt)
                if (h >= (0.9*contour_h)) and (h <= (1.1*contour_h))and (w > (0.9*contour_w)) and (w < (1.1*contour_w)):
                    cv2.rectangle(im, (x - 1, y - 1), (x + 1 + w, y + 1 + h), (0, 255, 0), 1)
                    roi = thresh[y:y + h, x:x + w]
                    roismall = cv2.resize(roi, (10, 10))
                    roismall = roismall.reshape((1, 100))
                    roismall = np.float32(roismall)
                    retval, results, neigh_resp, dists = self.model.findNearest(roismall, k=1)
                    string = str(int((results[0][0])))
                    number_output += string
                    cv2.putText(out, string, (x, y + h), 0, 1, (0, 255, 0))

        reversed_number_output = number_output[::-1]
        print("Detected number: " + reversed_number_output)
        cv2.imshow('input', im)
        cv2.imshow('output', out)
        cv2.waitKey(0)

# Start the testing process
if __name__ == '__main__':
    DigitRecognizerTesting().test()