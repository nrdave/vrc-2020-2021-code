#pragma once
//The PROS Documentation instructs users to include the apix.h file if they want to use LVGL
#include "pros/apix.h"
#include <vector>

/**
 * The header file for the GUI class, which allows for the creation of an LVGL-based
 * GUI. LVGL, which stands for Little Video Graphics Library, is an open source C-based 
 * graphics library. The PROS developers have configured all necessary LVGL settings
 * in the PROS API files, so setting up a GUI is relatively simple.
 */ 

class GUI
{


    public:
        GUI(std::initializer_list<lv_obj_t*> scrs);

    private:
        std::vector<lv_obj_t*> screens;
};