#pragma once
#include "pros/apix.h"

/**
 * The header file for the GUI namespace. The GUI uses a namespace rather
 * than a class due to the nature of the LittleVGL C graphics library. I've
 * tried using classes, but they run into too many issues with LVGL functions
 * 
 * The GUI namespace contains the LVGL objects and functions used to create and
 * set up a GUI menu. I used a namespace so that rather than creating everything
 * in initialize.cpp, I can put most of the code here and simply run the necessary
 * functions from initialize.cpp, making everything a lot cleaner
 */ 

namespace GUI
{
    /**
     * The LVGL objects for the GUI's screens. As of now there are 2, the main 
     * home screen and the screen for autonomous selection
     */ 
    lv_obj_t * scrMain;
    lv_obj_t * scrAuton;

    /**
     * The LVGL objects used for the navigation between the screens. There are
     * 2 per screen besides the main menu, so currently just 2
     */ 
    lv_obj_t * navAuton;
    lv_obj_t * navMainFromAuton;

    /**
     * The LVGL objects used in the autonomous routine selection menu. There are 
     * 
     * 
     */ 
    //lv_obj_t * autonMenu;
    //lv_obj_t * curAutonLbl;
    //lv_obj_t * runAuton;

    //Function to initialize the entire GUI
    void initialize();


    //Function to initialize the screens
    void initScreens();

    //Function to initialize the navigation buttons
    void initNavButtons();

    //Functions to navigate to specific LVGL Screens. Used in the navigation buttons
    lv_res_t goToMain(lv_obj_t * btn);
    lv_res_t goToAuton(lv_obj_t * btn);
}