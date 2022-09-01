# Elevated Fish Tank Main Code
A Particle project named Fish Tank Main Code


Code to be uploaded to a particle microcontroller for my fish tank

#### ```/src``` folder:  
This is the source folder that contains the firmware files for the project. It should *not* be renamed. 
Anything that is in this folder when compiled  project will be sent into a firmware binary for the Particle device that targeted.

#### ```.ino``` file:

This file is the firmware that will run as the primary application on the Particle Argon. In the header I call the libraries I need, declare my objects, and setup global variables like the pin Numbers my circuits take and send readings from. 

It also contains a `setup()` in setup enable the pinModes and setUp the other parts of my code that I only want to run once when the code starts up initially. I set up certain aspects of my code such as bool value

and `loop()` function, us written in C++. For more information about using the Particle firmware API to create firmware for the Particle Argon, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.
 
#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries that your project depends on. Dependencies are added automatically to your `project.properties` file when you add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to your project

#### Projects with multiple sources
If you would like add additional files to your application, they should be added to the `/src` folder. All files in the `/src` folder will be sent to the Particle Cloud to produce a compiled binary.

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
