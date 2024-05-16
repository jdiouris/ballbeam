#include <Servo.h>
#include "Adafruit_VL53L0X.h"
#include <MsTimer2.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
/* ----------------------------------------*/
/* Démo sonar                              */
/*                                         */
// Broches                                  

// servo : 5
#define SERVOPIN 5

#define IND 2
#define ALIMC 3

// potentiometres
#define P1 1
#define P0 0
#define P2 2

// valeurs extrèmes servo
#define minServo 600
#define maxServo 1500
// PID
// float kp=1;
// float kd=0.5;
// float ki=0.4;
 float kp=3;
 float kd=0.8;
 float ki=0.4;
 
 float kkd=0;
 float kki=0;
 float Te=40e-3;
 float consigne=250;
 float erreur;
 float erreurP;
 float integrale;
 float deriv;
 // Moyennage mesures
 float alpha=0.8;
 float alphad=0.85;
 
 // Flag Timer période d'échantillonnage
 int fchange;
 float dCor;
 int distance;
 float angle;
 float angleZero;
// servo rotation
 Servo servo;
 //

int fcoef=1;   // envoie des coefs

int t=0;


void testAngle()
{
  float pas=1;
  angle=minServo;
  while (1)
  {
   if (angle>(maxServo-1)) pas=-1;
   if (angle<(minServo+1)) pas=1;
   servo.writeMicroseconds(angle);
   Serial.print(angle);Serial.println();
   delay(4); 
  }
}

// Interruprtion toute les période d'échantillonage
void period()
{  
  fchange=1;
}

int mesDistance(int N)
{
  float distance=0;
  for (int  i=0; i<N; i++)
  {
     while (!lox.isRangeComplete());
          distance+=lox.readRange();
  }
  return (int)(distance/N+0.5);
  
}

void setup() {   
  /* Initialise le port série */
  Serial.begin(57600);
  while (!Serial);
  pinMode(IND,OUTPUT);
  
  digitalWrite(IND,0);
  pinMode(ALIMC,OUTPUT);
  digitalWrite(ALIMC,1);
  // Servo 

  angleZero=(minServo+maxServo)/2;
  angle=angleZero;
  

  // Init capteur de distance VL53L0X
  while (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    digitalWrite(ALIMC,0);
    delay(100);
    digitalWrite(ALIMC,1);
    delay(100);
  }

  lox.startRangeContinuous();

  // Asservissement
  erreurP=0;
  integrale=0;
  deriv=0;
  kkd=kd/Te;
  kki=ki*Te;
  
  // Servo
  servo.writeMicroseconds(minServo);
  servo.attach(SERVOPIN);
//  for (int a=minServo; a<=angleZero; a++)
//  {
//      servo.writeMicroseconds(a);
//      delay(2);
//  }
  delay(100);
  // Interruption périodique
  MsTimer2::set(40, period); // 100ms period
  MsTimer2::start();
  
}





void loop() {

if (fchange==1)
{
    digitalWrite(IND,1);
  
    fchange=0;
  
    while (!lox.isRangeComplete());
    distance=distance*alpha+(1-alpha)*lox.readRange();
 

    // Asservissement
    erreur=distance-consigne;
    integrale+=kki*erreur;
    if (integrale>maxServo-angleZero) integrale=maxServo-angleZero;
    if (integrale<minServo-angleZero) integrale=minServo-angleZero;
    deriv=alphad*deriv+(distance-erreurP)*kkd*(1-alphad);
    angle=erreur*kp+deriv+integrale+angleZero;

    erreurP=distance;
    
    // Saturation comande
    if (angle>maxServo) angle=maxServo;
    if (angle<minServo) angle=minServo;
    // commande
    servo.writeMicroseconds(angle);
     
     Serial.print(distance); 
     if (fcoef==1)
     {
     Serial.print(","); Serial.print(int(kp*100));
     Serial.print(","); Serial.print(int(ki*100));
     Serial.print(","); Serial.print(int(kd*100));
     fcoef=0;
     }
     //Serial.print(","); Serial.print(angle);
     Serial.println();
     int v=1023-analogRead(P2);
     float x=(v/100)/2.0;
     if (x!=kp) { kp=x; fcoef=1;}
      v=1023-analogRead(P1);
      x=(v/100)/10.0;
      if (x!=ki) { ki=x; kki=ki*Te; fcoef=1; }
      v=1023-analogRead(P0);
      x=(v/100)/10.0;
      if (x!=kd) { kd=x; kkd=kd/Te; fcoef=1; }
     

     digitalWrite(IND,0);


}


}
