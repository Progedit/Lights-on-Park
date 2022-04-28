# Evaluation

## Energy consumption

We have analyzed energy consumption trying to reduce it efficiently, lightening the cycle of duty, activating the device at specific time intervals. In fact, continuously checking if the parking space is occupied, when it already is, is not an efficient solution, because  the situation will hardly change in a short time.

Therefore we decided to check the parking status, varying the measurement time intervals, putting the device in sleep-mode between one data measurement and another, based on the situation in which we find ourselves:
- If the parking space is free, it's easier to be occupied in a short period of time, so let's measure the situation with a higher frequency                           through the sensor.
  Our idea is to measure the data every minute.
- If the parking space is occupied, there are less chances that it being vacated in a short time, so measurement is less frequent.
In this case, the idea is to measure the data every 10 minutes.

In addition to analyzing the consumption related to the electronic part, we also investigated on the activity of sending data, in order to optimize battery life. (sending data is the most expensive phase from an energy point of view). The data is not sent at each measurements, but only when there is a change in the parking status:
- Empty parking space -> Occupied parking space.
- Occupied parking space -> Empty parking space.

#### Devices consumptions:
- Battery: 14000mA power bank
- Ultrasonic sensor consumes 15mAh
- Board STM32 consumes:
    - 12.7mAh in run mode
    - 0.82mAh in sleep mode

## More details

We have choosen three specific cases:

1) Constantly connected device:
   - In 1 hour it consumes (15 + 12.7) mAh = 27.7mAh
   - In one day it consumes 664.8mAh
   - The device discharges after approximately 21 days.

2) Device with always free parking (worst case):
   - We check parking situation every minute.
   - 59s sleep mode. -> 3540s of sleep mode -> consumes 0.80mA in one hour.
   - 1s run mode. -> 60s of run mode -> consumes 0.46mA in one hour
   - Overall in 1 hour it consumes (0.80 + 0.46) mA = 1.26mA.
   - In one day it consumes 30.42mA.
   - The device discharges after approximately 460 days.

3)  Device with always occupied parking (best case):
   - We check parking situation every 10 minutes.
   - 3594s of sleep mode in 1 hour -> consumes 0.818mA in one hour
   - 6s of run mode in 1 hour -> consumes 0.046mA in one hour
   - Overall in 1 hour it consumes (0.818 + 0.046) mA = 0.864mA
   - In one day it consumes 20.736mA.
   - The device discharges after approximately 675 days.

So in a real operating situation of the device, the battery life varies from a minimum of 460 days to a maximum of 675 days, against only 21 days if the device is constantly in run mode.





