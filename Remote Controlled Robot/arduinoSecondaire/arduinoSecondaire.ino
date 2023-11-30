#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3; 
 int pos = 0; 
 int c=0;
void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
  myservo1.attach(9); //TOCHECK
  myservo2.attach(11); 
  myservo3.attach(15); 
}

void loop() {
  c=analogRead(A0);
  if(c!=0){
if(c<75) {
  upbras();
}
else if((c>75)&&(c<125)){
  downbras();
}
else if ((c>125)&&(c<175)){
  TURNbras();
}
else if ((c>175)&&(c<225)){
  OPENbras();
}
else if (c>225){
  CLOSEbras();
}

}
}

   void upbras(){
     for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

   }
 void downbras(){
     for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    }

     void TURNbras(){
     for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    }

     void OPENbras(){
     for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    }
         void CLOSEbras(){
     for (pos = 0; pos <= 100; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    }
