AK9750 Visualizer
========================================

![AK9750 Visualizer Processing Sketch](https://cdn.sparkfun.com//assets/parts/1/2/2/4/8/AK9750_Visualizer.jpg)

The visualizer sketch shows four circles. The brightness of the red is based on the IR readings from the AK9750. This is a good way to see how the sensor responds to humans walking through a scene.

There is one line in the sketch that will need to be adapted to your environment:

    sensorValue[x] = map(float(tempValues[x]), -200, 400, 0, 255);

This line maps an IR reading from -200/400 to 0/255 (allowed red colors). Your sensor readings may be lower than -200 and greater than 400 depending on your environment.

License Information
-------------------

This product is _**open source**_!

Please review the LICENSE.md file for license information.

If you have any questions or concerns on licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

_<COLLABORATION CREDIT>_
