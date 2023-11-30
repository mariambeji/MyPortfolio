import sys
import cv2
import numpy as np
from picture import Pic

class FontSizeTraining:
    """Class used to train digits on an image"""

    def __init__(self):
        test = Pic(pic_name='test.PNG', contour_w=120, contour_h=184)
        testjpg = Pic(pic_name='test.jpg', contour_w=10, contour_h=200)
        pic1 = Pic(pic_name='pic1.jpg', contour_w=10, contour_h=200)
        pic2 = Pic(pic_name='pic2.jpg', contour_w=40, contour_h=60)
        pic3 = Pic(pic_name='pic3.jpg', contour_w=10, contour_h=200)
        pic4 = Pic(pic_name='pic4.jpg', contour_w=10, contour_h=200)
        pic5 = Pic(pic_name='pic5.jpg', contour_w=10, contour_h=200)
        self.training_pic = test
        self.rtion = 0.5 #ratio typo min à mettre dans les conditions de détection digits
        self.rtiox = 0.77 #ratio typo max

    def find(self):
        im = cv2.imread(self.training_pic.pic_name)
        #img2 = cv2.cvtColor(im, cv2.COLOR_RGB2BGR)
        ## IMAGE filters
        gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
        blur = cv2.medianBlur(gray, 7)
        thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 37, 1)
        i=-1 #lezem toussel lel 3 in our case we only have 3 digits each time
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE) #lawajna aal les contour
        Listh = []
        Listw = []
        minh=200
        maxh=10
        minw = 200
        maxw = 10
        contour_h = self.training_pic.contour_h  # for code clarity
        contour_w = self.training_pic.contour_w
        for cnt in contours:
            [x, y, w, h] = cv2.boundingRect(cnt)
            if cv2.contourArea(cnt) > 200: #(self.training_pic.contour_h * 2):  #if 1st condition nécessaire surface taa lcontour> h*2?
                if (h > w) and (w/h > self.rtion) and (w/h < self.rtiox): # if 2nd conditions nécessaires aal typos
                    i = i + 1
                    print(self.training_pic.pic_name, "list contour:", w, h, "contour reel", cv2.contourArea(cnt))
                    # Ajout d'éléments dans la liste
                    if h< minh:
                        minh=h
                    if w< minw:
                        minw=w
                    if h>maxh:
                        maxh=h
                    if h>maxw:
                        maxw=w
                    Listh.append(h)
                    Listw.append(w)
                    print(Listw, Listh)
                    print(i)
                    if (maxh-minh)<15:
                        contour_h= int(minh+(maxh-minh)/2)
                        contour_w= int(minw+(maxw-minw)/2)
                    """ when above works we need to set contour_h o w to new value eli kherjou m tableau"""
                    if (h >= 0.7 * contour_h) and (h <= 1.3 * contour_h) and (w > 0.7 * contour_w) and (
                            w < 1.3 * contour_w):
                        cv2.rectangle(im, (x - 1, y - 1), (x + 1 + w, y + 1 + h), (0, 0, 255),
                                      1)  # draws a rectangle using 2 opposite corners
                        cv2.imshow('Training: Enter digits displayed in the red rectangle!', im)
                        key = cv2.waitKey(0)

                        if key == 27:  # (escape to quit)
                            cv2.destroyAllWindows()
                            sys.exit()


        
        
        print("new contours:",contour_w,contour_h)
        




# Start the training process
if __name__ == '__main__':
    FontSizeTraining().find()