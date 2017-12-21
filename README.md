# RHTEMPer
Temperature (oC) and Humidity (%) serial reporter for Arduino and Xinda DHT11-style sensor.

* Sensor output connected to pin 4.
* View 115200 baud serial output with serial monitor/terminal emulator.
* To forward /dev/ttyACM0 on myHost.local to a TCP connection listener issue: 
<br>   ```sudo socat -d -d tcp-l:54321,reuseaddr file:/dev/ttyACM0,b115200,raw,echo=0```
* To view stream on reciever issue:
   ```nc myHost.local 54321```
