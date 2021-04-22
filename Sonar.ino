//This program: uses a small servo motor and a HCSR04 ultrasonic sensor
//NOTE: on baud rate
//      high baud rate, greater bandwidth needed for signal channel, but not very tolerant to noise
//      low baud rate,  narrarow bandwidth, depend on coding scheme can be very tolerant to noise in signal channel


#include <Servo.h>
#include <math.h>
#include <SR04.h>
#define TRIG_PIN 12
#define ECHO_PIN 11


SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN); // this is probably a structure, under SR04.h file, and the functon
                                     //defined is SR04(input_pin, output_pin)
                                     //sr04 is probably a member of this structure


Servo myservo;  // create servo object to control a servo; accesses the struct tag and part 'Servo' 
// twelve servo objects can be created on most boards


int pos = 45;    // variable to store the servo position
long a;
long y[91];
int i=0;
void setup() 
{
  //------Similar to SR04 example in lib. folder
   myservo.attach(9);  // attaches the servo on pin 9 to the servo object
   delay(1000);
  //-----

  
   myservo.write(90);              // tell servo to go to position in variable 'pos'-->init. pos = 90deg
   delay(3000);                       // waits 15ms for the servo to reach the position
   Serial.begin(250000);          //higher baudrate
   delay(5);
   pos=45;
}

void loop() {
   
   for(pos=65;pos<116;pos+=1)//initializing the loop at starting range of 65deg to then apply the code effects
   {
    
    myservo.write(pos);// write the position to init. range 65, so it moves it to 65 deg
    delay(15);
    
    a=sr04.DistanceAvg(1,5); 
    
   // delay(5);   
   //for(int j=0;j<10;j+=1)               
    y[i++]=int(a*abs(sin(pos*3.1415/180.0))); //stores into array, starting y[0],until it reaches 115 deg. 
                                            //
                                            //
    Serial.println(y[i-1]);//will print out value, at every loop it prints out the value of of the last calculated
                           //...now converted linear distance stored in an array index. ex. i = 1, prints value at i = 0, etc.
   }
    

//pos=pos-1;
delay(100);
i=i-1;//

 for(pos=115; pos >= 65; pos-=1)
   {
    myservo.write(pos);
    delay(15);
    a=sr04.DistanceAvg(1,5);
    //delay(5); 
    //for(int j=0;j<10;j+=1)  
    y[i--]=int(a*abs(sin(pos*3.1415/180.0)));
    Serial.println(y[i+1]);
   } 
   //Serial.println(i);
   pos=pos+1;  
     i=i+1; 
 }
