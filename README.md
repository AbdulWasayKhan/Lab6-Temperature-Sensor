# Lab6-Temperature-Sensor

## An IoT Temperature Sensor:

This lab deals with measuring temperature with Raspberry Pi. In Raspberrypi kit there is a temperature sensor component which I used in the lab. The goal here is to wire up the sensor so that one can read the temperature, and then set up an IFTTT service that will send 
you a message every time the temperature changes by more than a degree C.

###Building the Temperature Circuit:

Use the wire stripper to strip back the outer black insulation an inch or so of the temperature senser and then strip each of the individual wires so that approximately half an inch of bare wire is exposed. Identify a red, yellow and black prototyping wire with a male end on it. Cut the other end off and strip about half an inch of wire on each of the prototyping wires. Now twist the prototyping wires to the three exposed wires of the sensor. For each wire, use electrical tape to secure the twist and then tape the bundle of wires together. (Less tape is better than more tape here,.) The goal is to attach a prototyping board pin to each of the three wires and to maintain the colours (red, yellow and black). By the way, if you can’t find perfect matches that’s fine. You will just have to remember the change in wire colour. Now for the circuity, the black wire is connected to ground, the red wire to +3.3V and the yellow wire connects to GPIO Pin 4. (Note: Not the WiringPi library Pin 4, the GPIO Pin 4.) There is one critical aspect in
this lab however, the resistor in the circuit between the power and signal lines must be a 4.7K Ohm resistor. You cannot use just any resistor.

You can identify the resistance of a resistor by the colour bands along the body. There will be either four or five colour bands on the body. For a 4.7K Ohm resistor, if there are four bands then the band colours will be yellow, purple, red, gold (in that order). If there are five bands then the band colours will be yellow, purple, black, brown, brown (in that order). Of course, if you happen to have a multimeter hanging around you can measure the resistance of the resistor. A multimeter will have a setting with a Omega signal on it. If you connect the two probes to the two ends of the resistor (by pushing them with your fingers, for example), the resistance can be read off from the multimeter.

###Enabling 1-wire on your Raspberry Pi:

On your Raspberry Pi execute sudo raspi-config. This will bring up the menu shown below. Select the Interfacing options and from there select the 1-wire enable/disable option. Enable the option. (Later if you want to disable the option select disable here.) Exit out of the raspi-config tool. The 1-wire protocol maps 1-wire devices to character files in the file system so that they can be treated like normal input-output devices and processed using standard read/write tools including the read/write libraries. So before proceeding further, if you have not yet done so, build the circuit associated with this lab and wire it up to your Raspberry Pi. If you have not yet built the circuit and attached it to your Raspberry Pi then you are not going to see a similar output to that shown below.
The 1-wire library supports multiple devices on 1-wire (hence the name). The library maps all of the devices to the directory
/sys/bus/w1/devices
Every device on the bus is assigned an ID. The ID’s for the temperature sensors all start with 28-. If you look into this directory you should see a file that starts with 28- .... Yours will be different. 
This file is a directory. If you look in this directory you will see a number of files. For example, you should see something like

pi@mypi:/sys/bus/w1/devices/28-0118423e95ff$ ls -l
total 0
lrwxrwxrwx 1 root root 0 Oct 24 03:44 driver -> ../../../bus/w1/
drivers/w1_slave_driver
drwxr-xr-x 3 root root 0 Oct 24 03:44 hwmon
-r--r--r-- 1 root root 4096 Oct 24 03:44 id
-r--r--r-- 1 root root 4096 Oct 24 03:44 name
drwxr-xr-x 2 root root 0 Oct 24 03:44 power
lrwxrwxrwx 1 root root 0 Oct 24 03:44 subsystem -> ../../../bus/w1
-rw-r--r-- 1 root root 4096 Oct 24 03:44 uevent
-rw-r--r-- 1 root root 4096 Oct 24 03:44 w1_slave
The contents of some of these files are obvious. The file ‘name’, for example contains the name of the device. The file that is most interesting for our purposes is the file w1_slave. If you print it out (say using the cat
command), you will see that it contains something like
pi@mypi:/sys/bus/w1/devices/28-0118423e95ff$ cat w1_slave
46 01 4b 46 7f ff 0c 10 2f : crc=2f YES
46 01 4b 46 7f ff 0c 10 2f t=20375
The number at the end of the second line (t=20375) is the current
temperature read by the device in degrees C multiplied by 1000. Or, to
put it another way, when I wrote this it was a little over 20C. If you hold
onto the device tightly for a moment or two, and then re-cat the file, you
will see that the output changes. So, for example, when I do this I receive
pi@mypi:/sys/bus/w1/devices/28-0118423e95ff$ cat w1_slave
dc 01 4b 46 7f ff 0c 10 45 : crc=45 YES
dc 01 4b 46 7f ff 0c 10 45 t=29750

####The Computational task:

Write a code that monitors the state of your thermometer and sends updates to an IFTTT Application under certain conditions as described below. First, to make your code more portable, it should take the serial number string of your temperature sensor as its
only argument. If your code does not receive a single argument when run, it should print out a usage message and exit. If at any time the temperature sensor cannot be found in the 1-wire devices file structure, then your program should print out an error message and exit. Your code should monitor the temperature of the thermometer. Once a second it should read the sensor and convert the temperature (found at the end of the second line in the w1_slave file) into degrees C. If this is the first reading, or if the reading has changed by more than 1 degree since the last message has been sent, your code should send the new temperature to the IFTTT server. The message you send should include the lowest temperature you have seen, the highest temperature you have seen, and the new temperature. After doing this lab, you will have a tool that monitors the temperature in your space and alerts you whenever the temperature changes by 1C or more.
