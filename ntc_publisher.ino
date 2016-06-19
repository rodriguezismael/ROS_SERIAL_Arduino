#include <math.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include <stdio.h>

//Set up the ros node and publisher
ros::NodeHandle nh;
std_msgs::Float32 sinus_msg;
ros::Publisher pub_sinus("sinus", &sinus_msg);

float myPI = 3.141593;
float alpha = 0;
int led = 13; //Digital pin 13

int analogPin=0;   // Which pin will be the input of the Voltage-Divider

float Vin=5.0;     // [V]        Supply voltage in the Voltage-Divider
float Raux=10000;  // [ohm]      Secondary resistor in the Voltage-Divider
float R0=10000;    // [ohm]      NTC nominal value at 25ºC
float T0=293.15;   // [K] (25ºC)

float Vout=0.0;    // [V]        Voltage given by the Voltage-Divider
float Rout=0.0;    // [ohm]      Current NTC resistance

float T1=273;      // [K]        Temperature at first testing point
float T2=373;      // [K]        Temperature at second testing point
float RT1=19750;   // [ohms]     Resistance at 273K (0ºC)
float RT2=2150;    // [ohms]     Resistance at 373K (100ºC)

float beta=0.0;    // [K]        Beta parameter
float Rinf=0.0;    // [ohm]      Rinf parameter
float TempK=0.0;   // [K]        Temperature output in Kelvin
float TempC=0.0;   // [ºC]       Temperature output in Celsius


void setup () {
  // Open serial
  //Serial.begin(9600);
  // Initialize the digital pin as an output
  pinMode(led, OUTPUT);
  
  nh.initNode();
  nh.advertise(pub_sinus);
  
  //Serial port configuration
  Serial.begin(9600);

  //Input pin configuration
  pinMode(analogPin, INPUT);

  //Global parameters calculation
  beta=(log(RT1/RT2))/((1/T1)-(1/T2));
  Rinf=R0*exp(-beta/T0);
}

void loop() {
  
  digitalWrite(led, LOW);
  
  for (float alpha = 0; alpha <= 2*myPI; alpha = alpha + (2*myPI)/180) {    // period complete
  
    //Serial.println(alpha, DEC);
    //Serial.println(sin(alpha), DEC);
    
    sinus_msg.data = sin(alpha);
    pub_sinus.publish(&sinus_msg);
    nh.spinOnce();
    
    // Sleep
    delay(100);                  // wait 100ms
    
    //Current NTC resistance value calculation (through Vout)
  Vout=Vin*((float)(analogRead(analogPin))/1024.0);
  Rout=(Raux*Vout/(Vin-Vout));

  //Temperature calculation
  TempK=(beta/log(Rout/Rinf));
  TempC=TempK-273.15;

  //Data population
  Serial.print(TempC);
  Serial.print(" ºC (");
  Serial.print(TempK);
  Serial.println(" K)");

  delay(1000);
  
  }
  
  digitalWrite(led, HIGH);      // period alert
  delay(250);
}
