import cv2
class Pic:
    """Class that represents a picture to train or test"""

    def __init__(self, pic_name="test.PNG", contour_w=160, contour_h=190):
        self.pic_name = pic_name
        self.contour_w = contour_w
        self.contour_h = contour_h
        self.rtion = 0.62  # ratio typo min à mettre dans les conditions de détection digits
        self.rtiox = 0.77  # ratio typo max

    def filter(self):
        im = cv2.imread(self.pic_name)
        # img2 = cv2.cvtColor(im, cv2.COLOR_RGB2BGR)
        gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
        blur = cv2.medianBlur(gray, 7)
        thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 37, 1)
        return thresh
    def find(self):
        thresh1 = self.filter()
        contour_h = 0
        contour_w = 0
        contours, hierarchy = cv2.findContours(thresh1, cv2.RETR_LIST,
                                               cv2.CHAIN_APPROX_SIMPLE)  # lawajna aal les contour
        minh = 200
        maxh = 10
        minw = 200
        maxw = 10
        for cnt in contours:
            if cv2.contourArea(cnt) > (
                    self.contour_h * 2):  # if 1st condition nécessaire surface taa lcontour> h*2?
                [x, y, w, h] = cv2.boundingRect(cnt)
                if (h > w) and (w / h > self.rtion) and (
                        w / h < self.rtiox):  # if 2nd conditions nécessaires aal typos
                    print(self.pic_name, "list contour:", w, h)
                    # Ajout d'éléments dans la liste
                    if h < minh:
                        minh = h
                    if w < minw:
                        minw = w
                    if h > maxh:
                        maxh = h
                    if h > maxw:
                        maxw = w
                    if (maxh - minh) < 15:
                        contour_h = int(minh + (maxh - minh) / 2)
                        contour_w = int(minw + (maxw - minw) / 2)
        print("new contours:", contour_h, contour_w)
        self.contour_h = contour_h  # for code clarity
        self.contour_w = contour_w

# Start the training process
if __name__ == '__main__':
    Pic().find()