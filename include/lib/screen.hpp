#pragma once
#include "pros/apix.h"

/**
 * The header file for the screen class. This class is used to create an individual screen
 * for the GUI. This class will hold all the individual LVGL elements on each screen, while
 * the GUI handles inter-screen relations
 */ 

class Screen
{
    private:
        /**
         * The LVGL screen object which forms the base of this class. This class exists to
         * ease the addition of LVGL elements onto a screen in an object, as doing so in the
         * main GUI class proved to be tedious
         */ 
        lv_obj_t * scr;

        const char * screenName;
    public:
        /**
         * The Screen class constructor.
         * It only needs to initialize the LVGL screen
         */ 
        Screen(const char * name);
        /**
         * This function creates an LVGL button object on the screen, sets its position, name,
         * and the action when clicked
         */ 
        void addButton(lv_obj_t * button, const char *name, lv_align_t align, lv_coord_t x_offset, lv_coord_t y_offset, lv_action_t function);

        lv_res_t loadScreen();

        const char * getName();
};