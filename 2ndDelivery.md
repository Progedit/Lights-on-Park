## Second Delivery

### First Delivery Comments

   1. Sensors Calibration
   
   2. Where we want to use this product ? Sea , River ?
   
   3. Using Wifi Module -> Energy Consumer
   
   4.  Using Water Pump and Relay -> It is not applicable in the sea or river!
   
   5. Incorrect using of Personas and Scenarios
   
   6. Evaluation  
   
   7. Security
   
   
   
### Justification For Comments:

1. Its better to calibrate the sensors in a periodic way  , every 1 month can be suitable!
      
* **Temperature sensor:** First to simply check the sensor, we can measure something which we know its temperature,
	  boiling water (100°C) and melting ice (0°C), then we can do the calibration if there is any difference between the measurement values.
      
* **Turbidity sensor:**  First we can measure clean water with zero turbidity which gives out 4.2 - 4.21 Volt, if the value is different from 4.2 , we can fix it by rotating the potentiometer in sensor available on the A & D converter circuit.
	  
* **pH sensor:**  For this we can consider very pure water as reference which has a pH value between 6.9 and 7 , then if the sensor gives out aother value, we can fix it using the Trimmer on the sensor to adjust it.
2. We are going to consider the **Artificial Pond** placed at remote location(not in the sea or river). They can be located in different places.                         
3. We are using **Wifi Module (ESP-01S ESP8266) only for testing and presenting the protptype** but it will not be used in a actual product as it consumes a lot of energy. We can use LoRaWan or any low-power modules instead for the actual implementation.
4. Based on the 2nd comment, we are going to consider fishponds outside the sea/river, on land. Therfore using water pump and relay for fishponds on land , will be applicable.
5. The Concept.md file containing the personas and scenarios are also updated.
6. We still do not know how to evaluate the performance of the product and the whole aspects of it. We are still working on it.
7. We do not conclude anything related to the security uptil now.
	
	
### Changes

* Concept:
	
	The Personas and scenario were used in a wrong way. The updated version presented here.
	
	https://github.com/rishiraj09/iot_water_monitoring_sys/blob/main/Concept.md
	
* Technology:
	
	Some changes have been made . The updated version presented here.
	
	https://github.com/rishiraj09/iot_water_monitoring_sys/blob/main/Technology.md

* Updated System Architecture:
	![arch](https://user-images.githubusercontent.com/30042823/118987765-68f19480-b935-11eb-9a99-434f7cdbf37f.jpeg)

	
* Evaluation:
	
	We still do not know which metrics to considered for the evaluation of product performances.
	
	
### Technical Work 

In general , we are going to complete everything in the device level first and then we can go further.

* Connecting Sensors
	
	* Tempreture Sensor : We have connected DS18B20 sensor to an Arduino Uno and checked the sensor values are being received. 
	Then we have tried to connect Arduino to STM32-F401RE using I2C protocol for sending sensor values to STM board.
	We have problem receiving sensor values by STM board through I2C protocol. We still working on it.
	
	
	* Turbidity Sensor :  We have connected turbidity sensor to an Arduino Uno and checked the sesnor values are being received . 
	Next we are going to establish I2C protocol between the arduino and the STM32-F401RE.
	
	* pH Sensor : We are trying to connect this sensor.
	
	
### Missing Functionalities

    1. Security Measures.
	
	2. Energy Opimization ( Using different sensors , boards , wifi module)
	
	3. Establishment of MQTT-SN with the AWS cloud.

	4. Web Dashboard.
	
