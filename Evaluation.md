# Evaluation

## Energy consumption

The major constraint that we have is about energy consumption: once the device is installed, it is difficult to maintain it so we want that the battery life to be as long as possible. We analyzed this problem trying to reduce the energy consumption as much possible, activating the device at specific time intervals. In fact, continuously checking if the parking space is occupied, when it already is, is not an efficient solution, because the situation will hardly change in a short time and so it is an unnecessary wast of energy. Furthemore we also want to optimize energy consumption for sending data to the cloud.

### Sensor sampling frequency 
Therefore we decided to check the parking status, varying the measurement time intervals, putting the device in sleep-mode between one data measurement and another; we believe it is a good compromise between energy consumption and data availability. From the proportion time, the cars spend on average 4,4% of the time driving and the 95,6% parked. The analysis is revealed in Standing Still – a new report by the RAC Foundation – which looks at data provided by the leading net zero data analytics consultancy Field Dynamics and the Ordnance Survey, as well as government statistics. See more here: https://www.racfoundation.org/media-centre/cars-parked-23-hours-a-day. 

Of this 95.6%, 72.6% includes parking at home while hang around, but since we want our device to be usable anywhere regardless the context, we make no distinction between the two data and assume that the car is parked 95.6% of the time.

So from these data we based our assumption with regard to how many times to measure the current state of a determinate parking lot: we want to measure the state more frequently when it is free, because it is more probable that there will be a change from free to occupied.

- If the parking space is free, it's easier to be occupied in a short time, so let's measure the situation with a higher frequency                           through the sensor.
- If the parking space is occupied, there are less chances that it being vacated in a short time, so measurement is less frequent.


### Radio usage
In addition to analyzing the consumption related to the electronic part, we also investigated on the activity of sending data, in order to optimize battery life. (sending data is the most expensive duty from an energy point of view). 

Obviously the first possible approach is to send data for every measurement, keeping continuos track of every measurement. But for our purpose it is unnecessary: we want to display to the user if a determine parking lot is free or not, so it is a big waste of energy to send to cloud a data egual to the previous one. So we done the following assumption.
The data are not sent at each measurements, but only when there is a change in the parking status:
- Empty parking space -> Occupied parking space.
- Occupied parking space -> Empty parking space.

This greatly reduce energy consumptions, and it is perfect for our interest. In this way we can also be compliant with the LoRa duty cycle restrictions.

## More details of analysis

### Devices consumptions:
- Battery: 14000mA power bank
- Ultrasonic sensor consumes 15mAh
- Board STM32 consumes:
    - 12.7mAh in run mode
    - 0.82mAh in sleep mode

### Energy consumption of the device

So from these data exposed above, we based our assumption with regard to how many times to measure the current state of a determinate parking lot: we want to measure the state more frequently when it is free, because it is more probable that there will be a change from free to occupied.

Initially we thought to measure every 1 minute if the parking lot is free, so doing a simple calculation (4,4 : 95,6 = 1 : x) we measure if a it is occupied every 22 minute. After some simulations we saw that in this way we don’t have much accuracy, because measure every 22 minute is cause of a lot error data. So we reduce these times of measure and we check the state of a parking every 30 seconds if it is free and every 10 minutes if it is occupied. This is the best compromise between accuracy and energy consumption.

We have choosen three specific cases:

1) Constantly connected device:
   - In 1 hour it consumes (15 + 12.7) mA = 27.7mA
   - In one day it consumes 664.8mA
   - The device discharges after approximately 21 days.

2) Device with always free parking (worst case):
   - We check parking status 30s.
   - 58s sleep mode in a minute. -> 3480s of sleep mode in a hour -> consumes 0.79mA in one hour.
   - 2s run mode in a minute. -> 120s of run mode in a hour -> consumes 0.42mA in one hour
   - Overall in 1 hour it consumes (0.79 + 0.42) mA = 1.21mA.
   - In one day it consumes 29.04mA.
   - The device discharges after approximately 482 days.

3)  Device with always occupied parking (best case):
    - We check parking status every 10 minutes.
    - 3594s of sleep mode in 1 hour -> consumes 0.818mA in one hour
    - 6s of run mode in 1 hour -> consumes 0.046mA in one hour
    - Overall in 1 hour it consumes (0.818 + 0.046) mA = 0.864mA
    - In one day it consumes 20.736mA.
    - The device discharges after approximately 675 days.

So in a real operating situation of the device, the battery life varies from a minimum of 482 days to a maximum of 675 days, against only 21 days if the device is constantly in run mode.

### Network usage
This architecture does not have any particular network constraint. We focused on analysing the latency time between the measurement and the receiving the message. The time interval is composed by:
* Time of the Ultrasonic sensor (T<sub>Ultrasonic</sub>): the time needed to compute the measurements of the current state.
* Time send Message (T<sub>Message</sub>): the time needed to send a message.
* Time on Air (T<sub>Air</sub>): the time needed to a message to go from the board to the LoRa gateway.
* Time of Cloud (T<sub>Cloud</sub>): the time from the LoRa gateway to the end-user.

So to measure the time from the measurement to the moment where the data are available (and so the latency) we have to do the following calculation:

T<sub>Ultrasonic</sub>+T<sub>Message</sub>+T<sub>Air</sub>+T<sub>Cloud</sub>

Let's see in detail the values of these parameters:
* T<sub>Ultrasonic</sub> = 1s because the system performs the measurement for one second.
* T<sub>Air</sub> = 0.05s because the board dose not take more that 0.05ms to compute the measurement and send it on the network.
* T<sub>Air</sub> = 0.07s - 0.08s. To compute this value we use the tools available [here](https://www.thethingsnetwork.org/airtime-calculator). The messages we send are *occupied* and *free* so they have respectively 8 and 4 bytes of payload, and the header packet of Lora is 13 bytes. So the input bytes is of 21 size, the speding factor is 7, the region is EU868 and the bandwidth is 125hHz, and from this values we compute the airtime from the board to the gateway.
* T<sub>Cloud</sub> = 2s this is the time needed on the cloud to process the data and it does not take more than 2s.

So:

T<sub>Ultrasonic</sub>+T<sub>Message</sub>+T<sub>Air</sub>+T<sub>Cloud</sub> = 1s+0.05s+0.08s+2s≃3s

[Here](https://github.com/Progedit/Lights-on-Parking/blob/main/2nd_Delivery/Evaluation.md) is possible to see the previous evaluation done in the second delivery.
