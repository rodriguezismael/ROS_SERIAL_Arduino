After installing the following tutorial we can install the ROS Arduino IDE. It allows your Arduino to become a ROS node which can directly publish and subscribe to ROS messages, publish TF transforms and get the ROS system time.

http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup


1- In the file pub_sinus.ino we find a code to generate a sinux wave and publish the generated data using a ROS Publisher, which we have called "sinus".

2- The file ntc_publisher.ino follows the same principle, it reads the values of a ntc (previously connected to an arduino device) and later publishes those lectures every 100 ms.



Once the code has been compiled and working using the arduino IDE and installed the ROS Serial we can proceed to subscribe to those published messages 
through the following process:


1- Firstly we have to launch the roscore in a new terminal window:

roscore

2- Next, run the rosserial client application that forwards your Arduino messages to the rest of ROS:

rosrun rosserial_python serial_node.py /dev/ttyUSB0 (in my computer's case /dev/ttyACM0)

3- Finally, we can call the topic. Also, we can check if everything is working well typing rostopic list to see all the messages that are being published:

rostopic echo sinus/ntc_msg (depending of which file you are launching)


Thanks
