# Apollo Rover

## Summary 
The main focus of this project was to design and develop the mechanism for remote-controlled robot with a robotic arm for lifting samples from the surface of the moon. 
### Picture of the robot
<div style="text-align:center;">
<img src="./Apollo rover.JPG" width="400" height="600">  
</div>
 
## General Description 
⦁	Remote-controlled robot was  designed with with four wheels and a floor in the center where the collected samples will be put  and  programmed to provide a working facility for off-line programming of actual working robot in a remote environment and also it can be used in dangerous areas.
⦁	The robotic arm was designed with three degrees of freedom and programmed to accomplish accurately simple heavy material lifting task to assist astronauts.    
⦁	Wireless control was done by using a smart phone with android operating system through a Bluetooth module.
⦁	The robot was under testing and validating its performance and the results indicates that it can perform the lifting task properly.  

## Mechanical design  
⦁	3D printing method is used in this project to fabricate the components of the robotic arm. Therefore, it provided more precise dimensions and huge time and cost-saving in fabrication.  
⦁	The remote-controlled robot is equipped with 4 motors to link the wheels and ensure its navigation. 
⦁	The robotic arm is equipped with 3 servo motors to link the parts and bring arm movement.   
### Solidworks model
<div style="text-align:center;">
<img src="./MechanicalDesignApolloRover.JPG" width="400" height="600">  
</div>

### Hardware used
⦁	Arduino, an open-source computer hardware and software is applied to control the robotic arm by driving servo motors to be capable to modify the position. 

#### Keywords: 
Robotic Arm, Arduino,Lifting Mechanismes, Design, Validation, Four Degree of Freedom, Servo Motors, Bluetooth module.



















Technical details and Novelty analysis :
⦁	The mechanical conception of the robot was designed using SOLIDWORKS  a solid modeling computer-aided design. All the parts ( the robot’s base and the robotic arm) were designed with precise dimensions to create an adequate model.
⦁	


⦁	The navigation of the robot is controlled through a bleutooth module connected to an Arduino board, this microcontroller (main) is linked to another Arduino board (secondary) which controls the movement of the robotic arm which is connected to the same bleutooth module HC-05
⦁	The motors are linked to a 4-channel relay control board with optocoupler which represents a voltage divisor

⦁	The robotic  arm is equipped with  3 servo motors(Zbotic TowerPro 180 Degree Rotation Servo Motor) to link the parts and bring arm  movement. 

#### STM32 Board used: 
The sensors data acquisition and processing were done on the *IOT-node*: STM32L4 Discovery Kit. [link](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html)  
The choice of board is made for several reasons:  
  1- The presence of sensors embedded on the board (Accelerometer, Gyroscope and Magnetometer)  
  2- The presence of an STM32L475 microcontroller known for its low consumption therefore suitable for autonomous drones.  
  3- The presence of wireless communication modules for future improvements. (WIFI or Bluetooth)  

## Contact Information
If you would like to learn more about this project or get in touch with me, please feel free to do so through the following channels:
- [LinkedIn](https://www.linkedin.com/in/mariam-beji-90ab28178/)
- Email: mariambeji@ieee.org


