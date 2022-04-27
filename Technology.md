# Technology
The project is built in a STM32 Nucleo-64 board, in which we implemented an ultrsonic proximity sensor which is used to determine when a car is parked in a certain parking lot.
For the software components, we created the main firmware file in Riot OS (it is an operating system for the embedded systems), and we use LoRa-Wan connection to communicate between every devices of each car park and the edge that manages the area in question (the aggregating gateway); we also use MQTT to forward the information of the area to our cloud broker, in this particular case AWS cloud, that saves the data in a database (in particular DynamoDB). After the cloud has collected the parking data in a specific area, these are shown and available for consultation by the user through a web page.
Let’s look at these components in more details.

## Hardware
### STM-32 Nucleo Board
<img src="https://github.com/Progedit/Lights-on-Parking/blob/e16710c8107c9f4f39fad81d472b33643338de2c/images/STM-32%20NucleoBoard.jpg" width=55% height=55%>
STM32 Nucleo-64 board: The STM32 Nucleo-64 board provides an affordable and flexible way for users to try out new concepts and build prototypes by choosing from the various combinations of performance and power consume features, provided by the STM32 microcontroller. It has 1 user LED shared with ARDUINO, 1 user and 1 reset push-buttons, 32.768 kHz crystal oscillator, board connectors and flexible power-supply options.
<br/>
<br/>
The databrief is available here: https://www.st.com/resource/en/data_brief/nucleo-f401re.pdf

### Ultrasonic Sensor
<img src="https://github.com/Progedit/Lights-on-Parking/blob/e16710c8107c9f4f39fad81d472b33643338de2c/images/Ultrasonic%20Sensor.jpg" width=45% height=45%>
Ultrasonic sensor HC-SR04: The HC-SR04 ultrasonic sensor uses sonar to determine distance to an object like bats or dolphins do. It offers excellent non-contact range detection with high accuracy and stable readings in an easy-to-use package. It operates in a distance range going from 2cm to 400 cm. Its operation is not affected by sunlight or black material.
The sensor come with 4 pins that correspond:

- VCC = +5VDC.
- Working current = 15mA.
- Trig = Trigger input of Sensor.
- Echo = Echo output of Sensor.
- GND = GND.
<img src="https://github.com/Progedit/Lights-on-Parking/blob/32e45f9625e40ac8e2f0cb45254b09a741bf0728/images/Ultrasonic%20sensor2.png" width=35% height=35%>

Datasheet is available here: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf

### How they interact between them: 
<img src="https://github.com/Progedit/Lights-on-Parking/blob/e16710c8107c9f4f39fad81d472b33643338de2c/images/Hardware%20Component's%20Schema.png" width=85% height=85%>

## Software
RIOT OS: RIOT is a small operating system for networked, memory-constrained systems with focus on low-power wireless Internet of Things devices. It is open-source software.
RIOT is based on a microkernel architecture and in constrast to other operating systems with similarly low memory use, it allows applications software programming with the programming language C and C++, also by an experimental API. It has full multithreading and real-time abilities, and also SSL and TLS are supported by popular libraries.
Riot OS gives us the possibility to create the main file that can be flashed in a big range of boards or simulate the functioning of the software in the terminal.

AWS: AWS IoT Core allows to connect devices to AWS services or to other devices, protect data and interactions, process and perform actions on device data, enable interactions between applications and devices even when they are offline and consequently produce low-cost devices with Alexa integrated.

WebApp: It is a simple web page through which the user can interact with the system. Here you can monitor the situation of an area of the city, seeing how many parking spaces are available in that area.

<img src="https://github.com/Progedit/Lights-on-Parking/blob/e16710c8107c9f4f39fad81d472b33643338de2c/images/Software%20Components'%20Schema.png" width=85% height=85%>

MQTT-S aggregating gateway:MQTT (MQ Telemetry Transport) is a standard ISO publish-subscribe light messaging protocol that sits on top of TCP/IP. It is designed for situations where low impact is required and where bandwidth is limited. The publish-subscribe pattern requires a messaging broker: the broker is responsible for distributing the messages to the intended clients.
MQTT-SN is a variation of the protocol intended for embedded systems that are not TCP/IP based.

LoRaWAN is one of several protocols developed to define the upper layers of the network. LoRaWAN is a cloud-based MAC (Media Access Control) layer protocol but serves primarily as a network layer protocol for managing communications between LPWAN (Low Power Wide Area Network) gateways 

