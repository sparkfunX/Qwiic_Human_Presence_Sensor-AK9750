Qwiic Human Presence Sensor - AK9750
========================================

![Qwiic Human Presence Sensor - AK9750](https://cdn.sparkfun.com//assets/parts/1/2/2/4/8/Qwiic-AK9750-3.jpg)

[*SPX-14289*](https://www.sparkfun.com/products/14289)

The AK9750 is a passive infrared sensor with four discrete sensors built into one digital package. PIRs are most often used in security systems to detect the movement of a human talking through the room. If you've ever seen a 1" white sphere in the corner of a room, that's a PIR. We sell a [simple PIR](https://www.sparkfun.com/products/13285) as well. The problem with PIRs is many fold. The vast majority of PIRs use a simple on/off interface. The AK9750 is a digital sensor giving you a 16-bit digital value over I<sup>2</sup>C. Furthermore, the AK9750 has *four* sensors built in! This allows you to detect not only presence but relative distance and direction of movement (for example: PIR2 went off then PIR4 went off so the human is moving left to right).

Each of the four sensors outputs the IR current in pico-amps (-14,286 to 14,286pA). A PIR reading can vary from roughly -200 (no human present) to 1500 when a human is detected standing in front of a given channel but it varies due to environmental factors and other heat sources in view. We've written a library to control the sensor and included a examples showing how to output the sensor readings. We've also written a Processing sketch to visualize the IR sensor readings in real time. 

The Qwiic Human Presence Sensor - AK9750 is rear mounted through the 0.8mm thick PCB. Additionally, the sensor ships without a lens. We've found the sensor to perform quite well and detect human movement over 10 feet (3 meters) away without the standard Fresnel lens. 

Need many eyes in the sky? The ADR jumpers allow up to 3 sensors on a bus. Need more? Our [Qwiic Mux](https://www.sparkfun.com/products/14257) will enable up to 192 sensors for a total of 768 presence readings. Eeek!

This board includes Qwiic connectors. The [Qwiic system](http://www.sparkfun.com/qwiic) enables fast and solderless connection between popular platforms and various sensors and actuators. You can read more about the Qwiic system [here](http://www.sparkfun.com/qwiic).

Repository Contents
-------------------

* **/Documents** - AK9750 datasheet and graph of movement detection. 
* **/Firmware** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/Hardware** - Source files for the PCB layout in EAGLE (.brd, .sch).
* **/Visualizer** - Processing sketch with matching Arduino sketch to see data on a heat map.

License Information
-------------------

This product is _**open source**_!

Please review the LICENSE.md file for license information.

If you have any questions or concerns on licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

_<COLLABORATION CREDIT>_
