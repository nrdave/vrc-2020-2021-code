# Knights Code

This branch contains the code for team 6030K, the Knights, for the 2020-2021 VEX Robotics Season, Change Up

## Project Structure

### Class Library

The majority of the source code resides in the lib folder under src. This folder contains user-written source files that
serve as a class library allowing for robot programming. For example, the Chassis class, which allows for the creation of
an object representing the drivetrain, allows for a variety of parameters in its constructors that let the user define 
values like motor ports, gearsets, wheel diameter, and base width.

The exception to this is gui.cpp. As LittleVGL (the graphics library included with PROS) doesn't seem to play nice with classes (as it is a C-based library) attempting to use it in a class led to signifigant issues caused by LVGL's nature. So, I elected to instead use a namespace to contain all code and objects. This allowed me to still organize the code reasonably well without running into any issues.

The documentation for the classes are split between the header and source files for each class. The header files, found
in the lib folder under include, contain descriptions of each class and function, while the source files contain documentation
about the inner workings of each function.

Files in the activeDev folder are still being written. Files outside activeDev are separated so as to exclude them from the PROS hot image, so that they are only included in wired uploads, rather than wireless ones. In theory, once a library file is finished (i.e. it has been tested and found to work without issues), there is no reason to include it in the image PROS sends to the V5 Brain in a wireless
upload.

### PROS Function Files

When you create a new PROS project, all the functions defined in main.h (like opcontrol, autonomous, initialize, and disabled) are
included in a single main.cpp file. However, PROS used to split the functions into 3 files, opcontrol.cpp, autonomous.cpp, and
initialize.cpp. Last year, I just used the PROS-generated main.cpp, but this year, I've decided to separate the functions like how
PROS used to. I think this improves organization, since having the GUI initialization and a long autonomous program followed by the opcontrol function might get a bit hectic. Also, I can exclude files from the PROS hot image once they are done.