# Arduino Dust Sensor
Arduino code and board connections for Sharp GP2Y dust sensor.

## Board Connections
The diagram bellow represents the board connections:

![board connections](https://imagehost.imageupload.net/2020/04/17/arduino-connections.jpg)

1. Power Ground
2. 5V External Power
3. Sensors Ground
4. Sensors 5V Power
5. Temperature Digital Output (optional)
6. Humidity Digital Output (optional)
7. SD Adapter CS
8. SD Adapter SCK
9. SD Adapter MOSI
10. SD Adapter MISO
11. Dust Sensor Digital Input
12. Dust Sensor Analog Output

![board connections](https://imagehost.imageupload.net/2020/04/17/sensor-board-connections.jpg)

Full images:
- [Arduino Board Connections](https://imagehost.imageupload.net/2020/04/17/arduino-connections-full.jpg)
- [Sensor Photo](https://imagehost.imageupload.net/2020/04/17/sensor-board-connections-full.jpg)

## Calibration Process
For the calibration process, a closed insulated box was used, where the sensor's output voltage measures were compared with the measures of a GRIMM high accuracy dust sensor, using ammonium sulfate solution.

### Measures Comparison

![Measures Comparison](https://imagehost.imageupload.net/2020/04/17/measures-time.jpg)

### Relation between sensor's volt measures and mass concentration

![Measures Comparison](https://imagehost.imageupload.net/2020/04/17/mass_volt.jpg)

Finally, using Cooks distance to remove the outliers and fitting the results in a first degree polynomial equation, we end up with the following equation:

$$Dust Density = (0.986 * Voltage - 0.582) * 1000 [um/m^3]$$

