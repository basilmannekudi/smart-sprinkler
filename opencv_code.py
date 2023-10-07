import cv2
import serial
from playsound import playsound
# Play the audio file

# Load the cascade classifier for face detection
#face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
face_cascade = cv2.CascadeClassifier('fire_detection_cascade_model.xml')
# Open a video stream from the default camera
cap = cv2.VideoCapture(0)

# Initialize the serial port for communication with the Arduino
ser = serial.Serial('COM25', 9600)
playsound('welcome.mpeg')
while True:
    # Read a frame from the video stream
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)
    # Convert the frame to grayscale for face detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces using the cascade classifier
    faces = face_cascade.detectMultiScale(
        gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # Send the coordinates of the first face detected to the Arduino
    for x, y, w, h in faces:
        # sending coordinates to Arduino
        string = 'X{0:d}Y{1:d}'.format((x+w//2), (y+h//2))
        print(string)
        ser.write(string.encode('utf-8'))
        # plot the center of the face
        center = (x+w//2, y+h//2)
        cv2.circle(frame, center, 2, (0, 255, 0), 2)
        # plot the roi
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 3)
        if (640//2-50 < center[0] < 640//2+50) and (480//2-50 < center[1] < 480//2+50):
            # playsound('a.mp3')
            print("p")
            string = "p"
            ser.write(string.encode('utf-8'))
    if len(faces) == 0:
        print("s")
        string = "s"
        ser.write(string.encode('utf-8'))
    # plot the squared region in the center of the screen
    cv2.rectangle(frame, (640//2-50, 480//2-50),
                  (640//2+50, 480//2+50),
                  (255, 255, 255), 3)

    # out.write(frame)
    cv2.imshow('img', frame)
    # Press 'q' to quit the program
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video stream and serial port resources
cap.release()
ser.close()
cv2.destroyAllWindows()
