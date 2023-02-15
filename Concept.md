# Concept

## Introduction

Lights on Parking is a project created to monitor the availability of parking spaces and consequently, if they are free, indicate them to the citizen through an app / web page, optimizing the traffic of those looking for a lot.

## Open Impact 

As a starting point for the project we took into consideration one of the themes offered by the Open Impact platform, namely Urban Regeneration, specifically the section relating to Sustainable Transport. We believe that our idea can provide a “smart” solution to a problem that is certainly very present in a chaotic city like Rome, that of parking.

## The problem
Nowadays to find a parking lot is a very big problem in the most of the cities: population of cities (and in particular in the big towns) is always growing up, and so the demand for available parking spaces is growing. The main problem is that the space in a town is limited and so the demand has exceeded the availability of parking lots, and so the research of a car parking free is very difficult. This problem has a big impact on the world under a lot of aspect: from the study conducted by INRIX in 2017, it is possible to see that this problem in UK causes a cost of £23.3 Billion a Year, and in particular for each citizen 44 hours wasted and £733 every year.From another study conducted by IBM in 2011 across 20 major international cities are arised several important data:
- Drivers in urban areas need nearly 20 minutes on average to find parking;
- Between 30 to 45 percent of traffic in cities is caused by drivers looking for parking;
- 60 percent of drivers reported giving up on finding parking at least once in the calendar year;
- 27 percent of the drivers surveyed got into arguments with fellow drivers over parking spaces.
So to find a parking lot is a big problem that has a big impact in the world.

To know more about the researches: 
- INRIX research (https://inrix.com/press-releases/parking-pain-uk/);
- IBM research (https://www.prnewswire.com/news-releases/ibm-global-commuter-pain-survey-traffic-congestion-down-pain-way-up-129446188.html).

## Existing approaches

There are other existing approaches that try to resolve the parking lot problem, we found three types of interesting approaches:
- PAYBYSKY – PARKING BY SATELLITE (http://paybysky.com/);
- PARKWISE – REAL-TIME PARKING GUIDANCE SOFTWARE (http://parkwise.mobi/);
- STANLEY ROBOTICS – AUTOMATED VALET PARKING( https://stanley-robotics.com/).

## Study Area

We have chosen to focus our studio in a very specific area, familiar to us, Via delle Sette Sale, near our university, La Sapienza, with the possibility in the future to extend it throughout the city. In fact, we usually have to go around looking for a parking space in that area for a long time, risking being late and creating unnecessary "traffic". In these cases, it would be useful to have an application that indicates an available parking space near your area.

## The device

Our device revolves ideally around the following sensor:

<img src="https://github.com/Progedit/Lights-on-Parking/blob/68f292d0ec77c6a3fbe19e27bb7182b3ca373e31/images/sensor.png" width=40% height=40%>

This sensor, once positioned and calibrated, allows to detect the presence of vehicles parked in the car park.
The technology used is able to record the variation of the earth's magnetic field in a solenoid induced by the presence of the ferrous mass of the vehicle. The requirements of this sensor are the following:
- The installation is extremely economical and practical as it is not necessary to intervene on the roads to lay cables;
- It also helps to ensure greater safety for pedestrians;
- Maximum privacy protection, infact the sensor records an anonymous data based on the variation of the earth's magnetic field;
- Easier maintenance;
- Improved aesthetics;
- The device turns on only when a vehicle is positioned on the free stall and so low battery consumptions.

This device is extremely versatile, with a very high level of efficiency and an unparalleled performance / price ratio.


However, for our university project we could not use this sensor because it is impossible to test it and therefore we replaced it with an ultrasonic sensor.

Communication with the user takes place via a web page / app, which indicates the places available in a specific area.

## Goals

We have extrapolated the following goals from a google form that we have submit to a randoms people who lives in different places: a little city, a big city or a suburban area of a city. 

The goals are:

- Possibility of giving the citizen a smart way to search for parking spaces.
<img src="https://github.com/Progedit/Lights-on-Parking/blob/bb1fbd40e96d720277dd34dc4504d3e9a08ba36e/images/Questionnaire/applicazione.jpg" width=70% height=70%>
This graphic is relative to a request of an new app that give the possibility to search and find a parking space before that we arrive in the specific zone. Almost the ninety percent of the persons have given a positive response.

- The driver, with Lights on parking, already knowing where to park, reduces his time inside the car, devoting the time purchased to something else.
<img src="https://github.com/Progedit/Lights-on-Parking/blob/bb1fbd40e96d720277dd34dc4504d3e9a08ba36e/images/Questionnaire/tempo.png" width=70% height=70%>

In this graph, roughly 50% of users spend between 30 minutes and an hour searching for parking,while 25% take more than an hour and the remaining less than 30 minutes. 


- The reduction of traffic and congestion.

- Lower consumption of fuel and therefore the reduction of ambiental pollution but also the lower waste of money on fuel.

The next graph is one of the many graphs that tell us how environmental pollution is growing from year to year, reaching historic peaks in recent years.

<img width="642" alt="grafico_emiss_CO2" src="https://user-images.githubusercontent.com/96829724/165388952-a4f9a20f-514c-41ce-87da-ff1c28347187.png">

- Lights on Parking can also benefit the driver's mood. We have found that searching for a parking space is stressful and counterproductive to the vast majority of users. It also affects the driver's punctuality, especially in the workplace.

<img src="https://github.com/Progedit/Lights-on-Parking/blob/0ec399643da04f97743a4bf577648ad1166d9df4/images/Questionnaire/stress_lavoro_studio.png" width=70% height=70%>

<img src="https://github.com/Progedit/Lights-on-Parking/blob/ba7d781e4507ae6c81868ac9a4e1615aa4b70694/images/Questionnaire/stress_uscite.png" width=70% height=70%>

The two previous graphs show that the search for a parking space is stressful for the interviewed users, in the first when you go to work or where you study and in the other when you go out for leisure.

While this other graph looks like the search for a parking space, it can affect the punctuality of the user.

<img src="https://github.com/Progedit/Lights-on-Parking/blob/c4b96af13ddb53fd79a76f0be98ec9ceda5aeb31/images/Questionnaire/puntualita.png" width=70% height=70%>

## Requirements

In our system we have 5 mainly requirements that are:

1. Space: public parking lots;
2. Information: availability or occupancy;
3. Individual: real time;
4. Energy consumptions: lower as possible.



DEVICE REQUIREMENTS

In the diagram below we show how our device is better than the other three, that are a pole installed on the sidewalk with an ultrasonic sensor, a top video camera installed on the light pole and a sensor under the asphalt.

<img width="691" alt="Device_Req" src="https://github.com/Progedit/Lights-on-Parking/blob/8e68d338d5536996ef16ae4b43af77c732fc9f08/images/Dev-req.png">

Our device:
- Respect the privacy of users.
- Not exposed to vandalism or bad weather.
- It does not need frequent maintenance.
- Not dangerous for pedestrians, cyclists, etc.

The following graph shows that most users prefer an invisible device over a visible one.

<img src="https://github.com/Progedit/Lights-on-Parking/blob/0f681f2ffee9e49596297f9472da8affa0392950/images/Questionnaire/tipologia_dispositivo.png" width=70% height=70%>




