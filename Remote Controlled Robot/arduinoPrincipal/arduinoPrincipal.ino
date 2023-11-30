  
#define M1av 4
#define M1ar 3
#define M2av 8
#define M2ar 7
#define M3av 9
#define M3ar 10
#define M4av 6
#define M4ar 5

 char A;  

void setup() 
{
pinMode (M1av, OUTPUT);
pinMode (M1ar, OUTPUT);
 pinMode(M2av, OUTPUT);
 pinMode(M2ar, OUTPUT);
 pinMode(M3av, OUTPUT);
 pinMode(M3ar, OUTPUT);
 pinMode(M4av, OUTPUT);
 pinMode(M4ar, OUTPUT);
 pinMode(11, OUTPUT);

Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
      A=Serial.read();
      if(A=='F')
      {
       Avancer();
      }
      else if(A=='B')
      {
        Reculer();
      }
      else if (A=='R')
      {
        Right();
      }
      else if(A=='L')
      {
         Left();
      }
      else if(A=='W') //upbras();
      {
        analogWrite(11,50);
      }
      else if(A=='U') //downbras();
      {
        analogWrite(11,100);
      }
      else if(A='V') //turnbras();
      {
         analogWrite(11,150);
      }
      else if(A='G') //OPENbras()
      {
        analogWrite(11,200);
      }
       else if(A='I') // CLOSEbras()
      {
        analogWrite(11,250);
      }
      

  }


}
void Avancer(){
  
     digitalWrite (M1av,HIGH );
   digitalWrite (M1ar, LOW);
   digitalWrite (M2av, HIGH);
   digitalWrite (M2ar, LOW);
   digitalWrite (M3av, HIGH);
   digitalWrite (M3ar, LOW);
   digitalWrite (M4av,HIGH);
   digitalWrite (M4ar, LOW);}
void Reculer(){
  
     digitalWrite (M1av,LOW );
   digitalWrite (M1ar, HIGH);
   digitalWrite (M2av, LOW);
   digitalWrite (M2ar, HIGH);
   digitalWrite (M3av, LOW);
   digitalWrite (M3ar, HIGH);
   digitalWrite (M4av, LOW);
   digitalWrite (M4ar, HIGH);}

void Right(){
  
    digitalWrite (M1av,HIGH);
   digitalWrite (M1ar, LOW);
   digitalWrite (M2av, LOW);
   digitalWrite (M2ar, HIGH);
   digitalWrite (M3av, LOW);
   digitalWrite (M3ar, HIGH);
   digitalWrite (M4av, HIGH);
   digitalWrite (M4ar, LOW);}
void Left(){
  
    digitalWrite (M1av,LOW );
   digitalWrite (M1ar, HIGH);
   digitalWrite (M2av, HIGH);
   digitalWrite (M2ar, LOW);
   digitalWrite (M3av, HIGH);
   digitalWrite (M3ar, LOW);
   digitalWrite (M4av, LOW);
   digitalWrite (M4ar, HIGH);}
