#include <TimerOne.h>
const int sensor = A5;
const int sensor1 =A4;
const int myLed = 13;
volatile byte se = 0;
static byte iterator = 10;
static byte count = 50;
volatile byte digital_val;
volatile byte dv = 0;
const byte pin[]={14,14,2,3,4,5,6,7,8,9};
const byte ar[][8]={{0,0,0,0,0,0,0,0},{2,2,7,3,4,5,8,9},{5,3,2,5,9,8,7,4},{5,3,2,5,7,8,4,9},{4,4,5,2,7,3,9,8},{5,3,4,5,7,8,2,9},{6,3,4,5,7,8,9,2},{3,2,3,7,4,5,8,9},{7,2,3,4,5,7,8,9},{6,2,3,4,5,7,8,9}};
bool ledOn = false;
bool state = false;

void setup() {
  Serial.begin(9600);
  int i = 2;
  while( i <= 9 )
  {
    pinMode (pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
    i++;
  }
  Timer1.initialize(1000000); // Calls every 50ms
  Timer1.attachInterrupt(myHandler);
}
void myHandler(){
  // If timer not elapsed for 10 times do nothn (NOP)
  if(iterator == 0)
  {
    // Reinstate the iterator
    iterator = 10;
    delay(500); // This delay to stabilize the voltage of the sensor else it would fluctuate
    volatile int okokval  = analogRead(A4);
    delay(500); // a stability delay same as above
    okokval = analogRead(A4); // redundant read for sanity
    volatile int whatisthis;

    // self written map function  a nested condition statement
    whatisthis = ((okokval < 900) ? ((okokval < 800) ? ((okokval < 700) ? ((okokval < 600)? ((okokval< 500)? ((okokval < 400)? ((okokval < 300)? ((okokval < 200) ? ((okokval < 100) ?9 : 100) : 9-1) : 9-2) : 9-3) : 9-4): 9-5): 9-6): 9-7): 9-8);

    // If the moisture sensor changes its value  from the previously known value 
    // update display
    if(se != whatisthis)
    {
      delay(10);
      Serial.print("sEnsor:  ");
      delay(10);
      Serial.print(okokval);
      delay(10);
      Serial.print("-->");
      delay(10);
      Serial.println(whatisthis);
      delay(10);
      // update the recorded store value
      se = whatisthis;
      // Update the seven segment now
      seg7(whatisthis);
    } // id se != whatisthis
    // If moisture sensor reading is less than user setting
    if(whatisthis < digital_val)
     {
        // Set the action pin HIGH
        if(count > 0){
          state = !state; // toggle the state
          digitalWrite(myLed, state);
          delay(100);
          if(state)
          Serial.println("PING");
          else
          Serial.println("PONG");
          count --; // decrement the toggle time
        }else {
          state = LOW;
          digitalWrite(myLed, state);
          delay(100);
        }
     } else if(whatisthis > digital_val) {
      // else set the action pin LOW
      digitalWrite(myLed, LOW);
      count = 50;
      Serial.println("shut up");
     }
  } // end of (iterator == 0)
  // decrement the iterator block
  iterator--;
} // end of function

void loop() {
  delay(500);
  int sensor_value = analogRead(sensor); 
  delay(50); 
  digital_val = map(sensor_value,0, 1023,1,9);
  if(dv != digital_val)
  {
    Serial.print("SETTING:  ");
    delay(10);
    Serial.print(sensor_value);
    delay(10);
    Serial.print("->");
    delay(10);
    Serial.println(digital_val);
    delay(50);
    seg7(digital_val);
    dv = digital_val;
    se = 0; //deliberately making the count to miss a pass and read the sensor to update the display
    Timer1.restart(); 
  }
}
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





