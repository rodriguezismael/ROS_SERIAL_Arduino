#include <ros.h>
#include <std_msgs/Float32.h>
#include <math.h>

ros::NodeHandle nh;    //Creamos nodo
std_msgs::Float32 msg_ntc;  //Creamos mensaje indicando tipo
ros::Publisher pub_ntc("ntc_value", &msg_ntc);  //Creamos publisher

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 Temp = (Temp * 9.0)/ 5.0 + 32.0; 
 return Temp;
}

int num;

void setup () {
  nh.initNode();  //Inicializar nodo  
  nh.advertise(pub_ntc);
}

void loop () {
  
  float val;                
  double temp;            
  temp = Thermistor(val);    

  //Create an integer variable
    val = analogRead(0);
    msg_ntc.data = temp;  //Añadir datos en el mensaje
    pub_ntc.publish(&msg_ntc);  //Publicamos mensaje
    nh.spinOnce();  //Activar nodo
    delay(100); //wait 100ms
  
  
}



