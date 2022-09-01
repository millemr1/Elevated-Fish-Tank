# Elevated Fish Tank Main Code
A Particle project named Fish Tank Main Code
Written Initiallty in Visual Studio Code


Code to be uploaded to a particle microcontroller for my fish tank

#### ```/src``` folder:  
This is the source folder that contains the firmware files for the project. It should *not* be renamed. 
Anything that is in this folder when compiled  project will be sent into a firmware binary for the Particle device that targeted.

#### ```.ino``` file:

This file is the firmware that will run as the primary application on the Particle Argon. The main functionalities are  for running a DIY turbidity sensor code, calculating its readings in `readTurbidty`, timed feeding, automated lights on and off, checking temp and PH levels, and publishing this data to a feeds that a user can check remotely. This porject is useful for people who want to play around with their own microcontrollers at home, and pamper their fish. This code should be run once the circuits are wired up, and the PH sensor is calibrated (see Auto PH Calibration also in this repository). 


##About '.ino' Code Structure

In the header I call the libraries I need, declare my objects, and setup global variables like the pin numbers my circuits take and send readings to and from. 

Next is the set up which contains a `setup()` this is where code that only needs to run once iniatlly runs like pinModes, functions like mqtt.connect, and initalization of objects, and the setting of certain global boolean variables takes place.

The `loop()` function is written in C++. Functions I want to run repeatedly, or sensor readings I want to be updated repeately run here even when set on a timer. The loop() function acts as a traffic cop for the functionality of my code. It can be likened to main() on non-embedded software systems. 

--For more information about using the Particle firmware API to create firmware for the Particle Argon, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.
 
#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries my project depends upon. Dependencies are added automatically to this file`project.properties` file when I add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to the Fish Tank
The only additional libraries not registered with Particle is "SendandPullfromEEPROM.h" file which is where the PH calibration values get stored after the Autocalibration code has been run. This custom library was written by me, and allows me to automate the calbration process for the Grove - PH Sensor Kit (E-201C-Blue) keeping the PH level for my fish's water accutate.


## Compiling this code

If you want to compile this project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE (I used Visual Studio Code). The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including the `.ino` application file
- The `project.properties` file for this project
- Any libraries stored under `lib/<libraryname>/src` (for information about which consult the src)
