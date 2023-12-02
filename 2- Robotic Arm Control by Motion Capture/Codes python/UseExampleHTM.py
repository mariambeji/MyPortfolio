# -*- coding: utf-8 -*-
"""
Created on Tue May  4 09:50:58 2021

@author: Imed / Mariam / Taher / Khalil
"""

import cv2
import mediapipe as mp
import time
import HandTrackingModule as htm
 
x= 0 
y = 0
pTime = 0
cTime = 0
cap = cv2.VideoCapture(0)
detector = htm.handDetector()

tipIds = [4, 8, 12, 16, 20]

while True:
    success, img = cap.read()
    img = detector.findHands(img, draw=True )
    lmList = detector.findPosition(img, draw=False)
    if len(lmList) != 0:
        #print(lmList[0])
        '''   
        if int(lmList[0][1])- x  < -6 :  
            print("droite")
        elif int(lmList[0][1])  - x > 6 : 
            print("gauche")
        else :     
            print('stationnaire')
        x =  int(lmList[0][1]) '''
           
        if int(lmList[0][2])- x  < -6 :  
            print("haut")
        elif int(lmList[0][2])  - x > 6 : 
            print("bas")
        else :     
            print('stationnaire')
        x =  int(lmList[0][2]) 
        
    

        '''
        #####################################################################

        fingers = []
 
        # Thumb
        if lmList[tipIds[0]][1] > lmList[tipIds[0] - 1][1]:
            fingers.append(1)
        else:
            fingers.append(0)
 
        # 4 Fingers
        for id in range(1, 5):
            if lmList[tipIds[id]][2] < lmList[tipIds[id] - 2][2]:
                fingers.append(1)
            else:
                fingers.append(0)
 
        #print(fingers)
        totalFingers = fingers.count(1)
        print(totalFingers)
        if totalFingers == 0 : 
            print('closed')
        else  : 
            print('open')'''
        #############################################################################    
 
    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime
 
    cv2.putText(img, str(int(fps)), (10, 70), cv2.FONT_HERSHEY_PLAIN, 3,
                (255, 0, 255), 3)
 
    cv2.imshow("Image", img)
    cv2.waitKey(1)
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()