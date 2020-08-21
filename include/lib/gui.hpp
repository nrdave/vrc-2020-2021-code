#pragma once
#include "pros/apix.h"

/**
 * The header file for the GUI namespace. The GUI uses a namespace rather
 * than a class due to the nature of the LittleVGL C graphics library. I've
 * tried using classes, but they run into too many issues with LVGL functions
 * 
 * The GUI namespace contains the fnctions used to create and
 * set up a GUI menu. I used a namespace so that rather than creating everything
 * in initialize.cpp, I can put most of the code here and simply run the necessary
 * functions from initialize.cpp, making everything a lot cleaner
 */ 

namespace GUI
{

    //Function to initialize the entire GUI
    void initialize();


    //Function to initialize the screens
    void initScreens();

    //Function to initialize the navigation buttons
    void initNavButtons();

    /**
     * Function to initialize the autonomous selection menu
     */ 
    void initAutonMenu();

    /**
     * The callback function for the auton selection button matrix
     * Although the function is never explicitly called, the parameters
     * exist to allow LVGL to pass in the needed values from the button
     * matrix
     */ 
    lv_res_t updateAutonID(lv_obj_t * btnm, const char * txt);

    //The function to update label displaying the selected autonomous routine
    void updateAutonLbl();

    //Functions to navigate to specific LVGL Screens. Used in the navigation buttons
    lv_res_t goToMain(lv_obj_t * btn);
    lv_res_t goToAuton(lv_obj_t * btn);
}