int pos = 0;
int ppos = 0;
int ypos = 0;
int pump = 2;
#include <Servo.h>
Servo servoVer; //Vertical Servo
Servo servoHor; //Horizontal Servo
Servo servoPmp;
int x;
int y;
int prevX;
int prevY;
void setup()
{
  pinMode(pump,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(pump,LOW);
  
  Serial.begin(9600);
 servoHor.attach(9);
  servoVer.attach(10);
    servoPmp.attach(11);
  //servoVer.attach(10);//Attach Horizontal Servo to Pin 6
  servoPmp.write(90);
  //Attach Horizontal Servo to Pin 6
  servoHor.write(90); //120 //60
  servoVer.write(90); //120 //60
    delay(1000);
}
void Pos()
{
  if(prevX != x || prevY != y)
  {
//    int servoX = map(x, 600, 0, 70, 179);
    int servoY = map(y, 700, 0, 120, 60);
    int servoX = map(x, 650, 0, 120, 60);

    servoX = min(servoX, 120);
    servoX = max(servoX, 60);
    servoY = min(servoY, 120);
    servoY = max(servoY, 60);
    
    servoHor.write(servoX);
    servoVer.write(servoY);
  }
}
void loop()
{
char input = Serial.read();
    if (input == 'X')
    {
      x = Serial.parseInt();
      if (Serial.read() == 'Y')
      {
        y = Serial.parseInt();
        Pos();
      }
    }
    else if (input == 'p')
    {
      digitalWrite(pump, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
      sweepPump();
    }
    else if (input == 's')
    {
      digitalWrite(pump, LOW);
      digitalWrite(LED_BUILTIN, LOW);
      //sweep();
    }
    

    while(Serial.available() > 0)
    {
      Serial.read();
    }
  
//  }else
//  {
//     //sweep(); 
//    }
}
void sweep()
{
  for (pos = 60; pos <= 120; pos += 30) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      servoHor.write(pos); 
     for (ypos = 60; ypos <= 120; ypos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoVer.write(ypos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15 ms for the servo to reach the position
  }
  for (ypos = 120; ypos >= 60; ypos -= 1) { // goes from 180 degrees to 0 degrees
    servoVer.write(ypos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15 ms for the servo to reach the position
  }
      
    
    // waits 15 ms for the servo to reach the position
  }
  for (pos = 120; pos >= 60; pos -= 30) { // goes from 180 degrees to 0 degrees
    servoHor.write(pos);              // tell servo to go to position in variable 'pos'
   for (ypos = 60; ypos <= 120; ypos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoVer.write(ypos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15 ms for the servo to reach the position
  }
  for (ypos = 120; ypos >= 60; ypos -= 1) { // goes from 180 degrees to 0 degrees
    servoVer.write(ypos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15 ms for the servo to reach the position
  }
  }
}
void sweepPump()
{
  for (ppos = 65; ppos <= 110; ppos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      servoPmp.write(ppos); 
     delay(3);
      
    
    // waits 15 ms for the servo to reach the position
  }
  for (ppos = 110; ppos >= 65; ppos -= 1) { // goes from 180 degrees to 0 degrees
    servoPmp.write(ppos);              // tell servo to go to position in variable 'pos'
  delay(3);
  }
}
