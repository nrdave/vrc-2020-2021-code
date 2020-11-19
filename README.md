# Knights Code

This branch contains the code for team 6030K, the Knights, for the 2020-2021 VEX Robotics Season, Change Up

## Project Structure

### Code Library

The majority of the source code resides in the lib folder under src. This folder contains user-written source files that serve as a class library allowing for robot programming. For example, the TankDrive class, which allows for the creation of an object representing the drivetrain, allows for a variety of parameters in its constructors that let the user define  values like motor ports, gearsets, wheel diameter, and base width.

The exception to this is the GUI namespace. As LittleVGL (the graphics library included with PROS) doesn't seem to play nice with classes (as it is a C-based library) attempting to use it in a class led to signifigant issues caused by LVGL's nature. So, I elected to instead use a namespace to contain all code and objects. This allowed me to still organize the code reasonably well without running into any issues.

The documentation for the classes (and the GUI namespace) are split between the header and source files for each class. The header files, found in the lib folder under include, contain descriptions of each class and function, while the source files contain documentation about the inner workings of each function.

Files in the activeDev folder are still being written. Files outside activeDev are separated so as to exclude them from the PROS hot image, so that they are only included in wired uploads, rather than wireless ones. In theory, once a library file is finished (i.e. it has been tested and found to work without issues), there is no reason to include it in the image PROS sends to the V5 Brain in a wireless upload.

### PROS Files

When a new PROS project is created, the PROS conductor automatically generates a few files. Files like common.mk, Makefile, and project.pros generally should never be touched. The same goes for files in the #include directory. The only exception to this is main.h, which is used to collect all the header files included with PROS. These headers include PROS's own api.h, which contains all the PROS API headers, and OkapiLib's api.hpp, which contains OkapiLib's headers. In addition to the included headers, main.h is intended for users to #include their own header files in. Finally, main.h includes declarations for the functions that the PROS kernel runs when a program is run on the V5 Brain. These functions are:
 - opcontrol(), which runs when the Brain is in its driver control mode (without any competition switch or field control input, the Brian defaults to this mode)
 - initialize(), which runs when the program is initially run
 - autonomous(), which runs when the Brain is in its autonomous mode (set through either a competition switch or field control system)
 - disabled(), which runs whenever the Brain is disabled by a competition switch or the field control system
 - competition_initialize(), which runs after initialize() and before autonomous() if the Brain is connected to a field control system or competition switch.

The only source file the PROS conductor generates is main.cpp. This is where all of the aforementioned functions are defined by the user. In my case, I only use opcontrol(), initialize(), and autonomous(). However, since
1. I plan to use hot-cold linking to wirelessly upload, and 
2. I will likely be writing a fair bit of code in autonomous, and likely opcontrol

I decided to use PROS's old file format of having 3 source files: autonomous.cpp (which contains autonomous()), opcontrol.cpp(which contains opcontrol()), and initialize.cpp(which contains initialize(), disabled(), and competition_initialize()). 