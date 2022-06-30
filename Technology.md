# Technology
The project is built in a STM-32 LoRaWAN Discovery Board in which we implemented an ultrasonic proximity sensor which is used to determine when a car is parked in a certain parking lot.
For the software components, we created the main firmware file in Riot OS (it is an operating system for the embedded systems), and we use LoRa-Wan connection to communicate between every devices of each car park and the edge that manages the area in question (the aggregating gateway); we also use MQTT to forward the information of the area to our cloud broker, in this particular case AWS cloud, that saves the data in a database (in particular DynamoDB). After the cloud has collected the parking data in a specific area, these are shown and available for consultation by the user through a web page.
Let’s look at these components in more details.

## Hardware
### STM-32 LoRaWAN Discovery Board
<img src="https://github.com/Progedit/Lights-on-Parking/blob/7f7f6ebc3b4780be028bdf3520b7de48cc5d95fe/images/lora.jpg" width=55% height=55%>
The B-L072Z-LRWAN1 LoRa®/Sigfox™ Discovery kit is a development tool to learn and develop solutions based on LoRa®, Sigfox™, and FSK/OOK technologies. This Discovery kit features the all-in-one CMWX1ZZABZ-091 open module by Murata. The module is powered by an STM32L072CZ microcontroller and SX1276 transceiver. The transceiver features the LoRa® long-range modem, providing ultra-long-range spread-spectrum communication and high interference immunity, minimizing current consumption.
<br/>
<br/>
The databrief is available here: https://www.st.com/resource/en/user_manual/dm00329995-discovery-kit-for-lorawan-sigfox-and-lpwan-protocols-with-stm32l0-stmicroelectronics.pdf

### Ultrasonic Sensor
<img src="https://github.com/Progedit/Lights-on-Parking/blob/e16710c8107c9f4f39fad81d472b33643338de2c/images/Ultrasonic%20Sensor.jpg" width=45% height=45%>
Ultrasonic sensor HC-SR04: The HC-SR04 ultrasonic sensor uses sonar to determine distance to an object like bats or dolphins do. It offers excellent non-contact range detection with high accuracy and stable readings in an easy-to-use package. It operates in a distance range going from 2cm to 400 cm. Its operation is not affected by sunlight or black material.
The sensor come with 4 pins that correspond:

- VCC = +5VDC.
- Working current = 15mA.
- Trig = Trigger input of Sensor.
- Echo = Echo output of Sensor.
- GND = GND.
<img src="https://github.com/Progedit/Lights-on-Parking/blob/2f1fd3841eb37c18bd1a7566bdf66c492066c718/images/Ultrasonic_Sensor.jpg" width=50% height=50%>

Datasheet is available here: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf

### How they interact between them: 
<img src="https://github.com/Progedit/Lights-on-Parking/blob/f19e51a59780010502f57b1a080983abecc6f10a/images/Schema_Hardware_Fritizing.png" width=72% height=72%>

## Software
<b>RIOT OS</b>: RIOT is a small operating system for networked, memory-constrained systems with focus on low-power wireless Internet of Things devices. It is open-source software.
RIOT is based on a microkernel architecture and in constrast to other operating systems with similarly low memory use, it allows applications software programming with the programming language C and C++, also by an experimental API. It has full multithreading and real-time abilities, and also SSL and TLS are supported by popular libraries.
Riot OS gives us the possibility to create the main file that can be flashed in a big range of boards or simulate the functioning of the software in the terminal.

<b>AWS</b>: AWS IoT Core allows to connect devices to AWS services or to other devices, protect data and interactions, process and perform actions on device data, enable interactions between applications and devices even when they are offline and consequently produce low-cost devices with Alexa integrated.
The data are stored in DynamoDB: it is a fully managed proprietary NoSQL database service that supports key–value and document data structures and is offered by Amazon as part of the Amazon Web Services.

<b>WebApp</b>: It is a simple web page through which the user can interact with the system. Here you can monitor the situation of an area of the city, seeing how many parking spaces are available in that area.

<img src="https://github.com/Progedit/Lights-on-Parking/blob/3da7682dfb0566750f19ed1f9a12b4f4fa52dd9c/images/Schema.png" width=85% height=85%>

<b>MQTT (MQ Telemetry Transport)</b>: is a standard ISO publish-subscribe light messaging protocol that sits on top of TCP/IP. It is designed for situations where low impact is required and where bandwidth is limited. The publish-subscribe pattern requires a messaging broker: the broker is responsible for distributing the messages to the intended clients.

<b>LoRa</b>: it is the physical layer or the wireless modulation utilized to create the long range communication link. The advantage of LoRa is in the technology’s long range capability. A single gateway or base station can cover entire cities or hundreds of square kilometers.
The LoRaWAN specification is a Low Power, Wide Area (LPWA) networking protocol designed to wirelessly connect battery operated ‘things’ to the internet in regional, national or global networks, and targets key Internet of Things (IoT) requirements such as bi-directional communication, end-to-end security, mobility and localization services. It defines the communication protocol and system architecture for the network while the LoRa physical layer enables the long-range communication link. The protocol and network architecture have the most influence in determining the battery lifetime of a node, the network capacity, the quality of service, the security, and the variety of applications served by the network.
For more details see here: https://lora-alliance.org/lorawan-for-developers/

<b>The Things Network</b>: The Things Network is a global collaborative Internet of Things ecosystem that creates networks, devices and solutions using LoRaWAN.
The Things Network runs The Things Stack Community Edition, which is a crowdsourced, open and decentralized LoRaWAN network. This network is a great way to get started testing devices, applications, and integrations, and get familiar with LoRaWAN.
