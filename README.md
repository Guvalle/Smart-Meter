# Smart-Meter

## Code
**Smart meter is a project I made as my Electric Engineering undergraduate thesis.**
**The entire project is made to run on a Raspberry Pi (I used a Rpi 3 model B) atached to a simple acquisition circuit designed by me.**

This project runs a C++ code that samples the GPIO pins of the raspberry pi to measure the input signals for three voltages and three currents. It samples them at a sample rate of 30K samples/second, which divided by the 6 signals results in 5K samples/second on the power grid signal. By the Nyquist theorem it allows the meter to sample signals up to 2.5KHz, which, since the brazilian power grid operates in 60Hz, allows the meter to measure up to 41 harmonic components, but, since they get ateanuated by the end of the spectrum the software only aims to measure 15 of them.

With the sampled values the program calculates the rms voltage and current of each phase, instantaneous power, power factor, etc for the measured cycle, and stores all the values in a sqlite database table.

To show the data to the user a html page is hosted in the raspberry with a javascript code to read the database every second and update the values on screen. The values are then displayed in the following screens:

![powerMeterIm3sc1](https://user-images.githubusercontent.com/47705676/131225132-ed8414c1-c257-4a3b-a588-776cac7f0bce.jpg)

![powerMeterIm3sc](https://user-images.githubusercontent.com/47705676/131225140-1d5004b9-7848-48a4-927d-3169480b2e54.jpg)

## Hardware
The harwade attached to the raspberry is a simple circuit containing 3 voltage transformers used to isolate the meter from the power grid for safety, althoug it doesn't allow measurement of any DC component existing on it. And 3 devices that measure current through hall effect and output a voltage signal. Both the voltage and current circuits are atached to an analog/digital converter CI with 8 pins that samples them and outputs their values trough a serial output to the raspberry pi's GPIO pins.

Here you can see some pictures of the designs for the hardware board and the final built of the project:

![powerMeterIm1c(1)](https://user-images.githubusercontent.com/47705676/131225156-eb9aa37d-e299-490d-a9aa-8ee69e525fe5.jpg)

![powerMeterIm2c(1)](https://user-images.githubusercontent.com/47705676/131225162-15a29c29-688f-4ff6-8870-33507caddd13.jpg)

![powerMeterIm3](https://user-images.githubusercontent.com/47705676/131225167-a7f89f78-29c4-45d8-8f5f-f31b500c6514.jpg)

## Misc
*The project was named PDC-2017 as a homage to the team I worked with at a company back then. The team's name was PDC and was composed by my mentor who was a graduated Electrical Engineer and helped me with some of the conceptual definitions of the project and 4 developers who helped me with the code. All of them taught me a lot.*
