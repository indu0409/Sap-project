import cv2 as cv
haar_cascade=cv.CascadeClassifier('haar_face.xml')
c=cv.VideoCapture(0)

while True:
    isTrue,frame=c.read()
    gray=cv.cvtColor(frame,cv.COLOR_BGR2GRAY)
    faces_rect=haar_cascade.detectMultiScale(gray,scaleFactor=1.1,minNeighbors=4)
    for (x,y,w,h) in faces_rect:
       cv.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),thickness=2)
    cv.imshow('FaceDetection',frame)
    if cv.waitKey(20) & 0xFF==ord('d'):
        break
print(f'Number of faces found={len(faces_rect)}')

c.release()
cv.destroyAllWindows()