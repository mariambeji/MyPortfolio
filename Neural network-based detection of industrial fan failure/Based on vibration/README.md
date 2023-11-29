## Presentation 

The work consists in training a classification model to detect the state of a fan in an industrial environment. The dataset used can be found through this link:

https://sensiml.com/datadepot/pdm-fan-motor-demo-v1/

This dataset is intended to rapidly build smart sensor data time series classification algorithms to translate raw physical sensor data into application-specific perception events using pattern recognition.  
These events include blade shock, hub imbalance, and frame shock.  The engine state classification includes these events, as well as vibration detection of engine on and off states.
All fan-related event classifications are based on the monitoring of vibrations/movements detected by the on-board inertial measurement unit (6-axis accelerometer and gyro sensor). In this way, the dataset simulates a common use case desired in industrial predictive maintenance applications for a global sensor system that can detect equipment utilization, failure states, and performance degradation with minimal or no incursion into existing electromechanical systems used for control and operation.
The data set consists of captured sessions of raw IMU sensor values sampled at 416 Hz.  Each session contains labelled segments of a given fan state/classification type from the following class map of events to be recognized:

![image](https://user-images.githubusercontent.com/108965218/234117079-2f72806f-ed4b-4009-b672-a7d80ba0ac40.png)

The choice of the model was made under the constraints and the limitations of the STM32 .We based ourselves on a model of human activity recognition that we adapted to our needs . We're feeding it 80 samples for each axis of the gyro and the accelero.

## Flowchart

The program implemented on microcontroller follows the following flowchart:

![image](https://user-images.githubusercontent.com/108965218/234117234-a432dd39-b6c7-4f87-b7b8-d80f75665517.png)
