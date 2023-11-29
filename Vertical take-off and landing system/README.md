## Configuration

![image](https://user-images.githubusercontent.com/108965218/234114124-fccff55d-0676-4206-b11d-78cddeb204d6.png)

For the configuration part, we use the VISA configure Serial Port block, having downloaded the necessary drivers beforehand.
Then we create the control blocks and/or constants necessary for its proper functioning: in our case we will specify 
- The Visa Resource Name (to choose the appropriate COM port) 
- The activation of a termination character to separate the different messages during reception
- The baud rate which will be identical to the one used by the microcontroller.
- The existence or not of a parity bit 
- As well as the size of the UART payload


## Writing from LabVIEW

![image](https://user-images.githubusercontent.com/108965218/234114163-1942399b-5455-4eb3-b8ea-0cb031398cd1.png)

In our case, we have several variables to transmit from LabVIEW to the microcontroller used: 
- A boolean variable indicating the start or stop of the system
- Real numbers containing the constants Kp, Ki and Kd of our implemented PID.
- A float containing the instruction for tests.
Therefore, it is necessary to separate the variables with " \n " to break up the message when receiving. 
So our frame of data to be sent is a character string containing the variables to be sent separated by a predefined character " \n " where from the necessity to convert the variables into character strings and to carry out a concatenation before sending it.
It is necessary to implement on microcontroller an algorithm of decomposition of the sent frame to be able to extract the data.


## Reading from LabVIEW

![image](https://user-images.githubusercontent.com/108965218/234114256-a3cf5463-6ac9-472e-8869-f538b166fff6.png)

LabVIEW is used in our case to receive the measured angular position on microcontroller.
To solve communication problems, we have deliberately sent the measured angle with an offset of + 90 degrees to ensure that the number is always positive. 
This angle is processed in LabVIEW to be corrected and displayed on a graph.
From the received angles we drift twice to obtain respectively a speed and an angular acceleration.
We also perform a filtering on the calculated velocity to smooth the obtained curve.
Moreover, we use the angular position and the angular velocity to plot the phase plane in real time by designating them respectively as X and Y.


## Final result

![image](https://user-images.githubusercontent.com/108965218/234114318-0fba38cf-1e1e-42cb-a391-ef5e3237cb90.png)

![image](https://user-images.githubusercontent.com/108965218/234114350-7ed35a45-60a3-4fe6-991a-769443fc2d48.png)

![image](https://user-images.githubusercontent.com/108965218/234114382-11c57881-a03b-4018-a8ca-536aba07d94a.png)

![image](https://user-images.githubusercontent.com/108965218/234114415-4a87dae7-625f-4f6a-b8e8-59ff995dff2f.png)

![image](https://user-images.githubusercontent.com/108965218/234114442-8c04389a-e7e1-43d4-b80a-155b023d43b5.png)
