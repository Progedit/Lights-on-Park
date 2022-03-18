# Technology
The project is built in a STM32 Nucleo-64 board, in which we implemented an ultrsonic proximity sensor and a motion sensor: respectively one of them is used to determine when a car is parked in a certain parking lot, while the other is used to determine when a pedestrian is walking near the pole. In this way, with the second sensor we are able to understand when to turn on the light always connected to the board.
For the software components, we created the main firmware file in Riot OS (it is an operating system for the embedded systems), and we use MQTT-S connection to communicate between every devices of each car park and the “main” device that manages the area in question (the aggregating gateway); we also use MQTT to forward the information of the area to our cloud broker, in this particular case AWS cloud. After the cloud has collected the parking data in a specific area, these are shown and available for consultation by the user within a web page.
Let’s look at these components in more details.

## Hardware

### STM-32 Nucleo Board
<img src="images/STM-32%20NucleoBoard.jpg" width=55% height=55%>
STM32 Nucleo-64 board: The STM32 Nucleo-64 board provides an affordable and flexible way for users to try out new concepts and build prototypes by choosing from the various combinations of performance and power consume features, provided by the STM32 microcontroller. It has 1 user LED shared with ARDUINO, 1 user and 1 reset push-buttons, 32.768 kHz crystal oscillator, board connectors and flexible power-supply options.
The databrief is available here: https://www.st.com/resource/en/data_brief/nucleo-f401re.pdf

### Ultrasonic Sensor
<img src="images/Ultrasonic%20Sensor.jpg" width=45% height=45%>

### LED Light
<img src="images/LED.jpg" width=45% height=45%>
