#include <TimerOne.h>
const int pin[]={14,14,2,3,4,5,6,7,8,9};
const int sensor = A5;
const int sensor1 =A4;
const int myLed = 6;
bool ledOn = false;
volatile byte digital_val;
// byte digital_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int i=2;
  while(i<=9)
  {
    pinMode (pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
    i++;
  }
  Timer1.initialize(1999000); // Calls every 50ms
  Timer1.attachInterrupt(myHandler);
  

}
volatile byte se = 0;
void myHandler(){
  delay(500);
  int okokval  = analogRead(A4);
  delay(500);
  okokval = analogRead(A4);
  int whatisthis;
  //= /*(okokval/1024)  * 10;  //*/map(okokval,0,1023,0,9);
  whatisthis = ((okokval < 900) ? ((okokval < 800) ? ((okokval < 700) ? ((okokval < 600)? ((okokval< 500)? ((okokval < 400)? ((okokval < 300)? ((okokval < 200) ? ((okokval < 100) ?1 : 100) : 2) : 3) : 4) : 5): 6): 7): 8): 9);

  if(se != whatisthis)
  {
    Serial.print("Sensor:  ");
    Serial.print(okokval);
    Serial.print("-->");
    Serial.println(whatisthis);
    se = whatisthis;
    seg7(whatisthis);
  }
  
  if(whatisthis < digital_val)
   {
    digitalWrite(myLed, HIGH);
   }
   else if(whatisthis > digital_val)
   {
    digitalWrite(myLed, LOW);
   }
}
int dv = 0;
void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  int sensor_value = analogRead(sensor);  
  digital_val = map(sensor_value,0, 1023,1,9);
  if(dv != digital_val)
  {
    Serial.print("SETTING:  ");
    Serial.print(sensor_value);
    Serial.print("->");
    Serial.println(digital_val);
    delay(500);
    seg7(digital_val);
    dv = digital_val;
    Timer1.restart(); 
  }
}

byte ar[][8]={{0,0,0,0,0,0,0,0},{2,2,7,3,4,5,8,9},{5,3,2,5,9,8,7,4},{5,3,2,5,7,8,4,9},{4,4,5,2,7,3,9,8},{5,3,4,5,7,8,2,9},{6,3,4,5,7,8,9,2},{3,2,3,7,4,5,8,9},{7,2,3,4,5,7,8,9},{6,2,3,4,5,7,8,9}};

void seg7(const int digital_val){
  int i,j=0;
  for(i=1,j=ar[digital_val][0];i<8;i++)
  {
    while(i<=j)
    {
      //Serial.println(ar[digital_val][i]);
      digitalWrite(ar[digital_val][i++],HIGH);
      //i++; 
    }
    digitalWrite(ar[digital_val][i],LOW);
    }
}





