#include <math.h>
#include <ros.h>
#include <std_msgs/Float32.h>

//Set up the ros node and publisher
ros::NodeHandle nh;
std_msgs::Float32 sinus_msg;
ros::Publisher pub_sinus("sinus", &sinus_msg);

const float myPI = 3.141593;
float alpha = 0;
int led = 13; //Digital pin 13

void setup () {
  // Open serial
  //Serial.begin(9600);
  // Initialize the digital pin as an output
  pinMode(led, OUTPUT);
  
  nh.initNode();
  nh.advertise(pub_sinus);
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
  }
  
  digitalWrite(led, HIGH);      // period alert
  delay(250);
}
