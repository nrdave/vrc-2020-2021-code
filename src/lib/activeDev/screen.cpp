#include "main.h"

/**
 * The implementation of the Screen class.
 * This file contains the source code for the Screen class 
 * along with explanations of the code
 */ 

Screen::Screen(const char * name)
{
    /**
     * Initializing scr as an LVGL screen.
     * The 2 values passed into the LVGL object create function are
     * null to indicate that the object has no parent and that
     * it should not be the copy of anything. LVGL sees the lack
     * of a parent and makes this a screen
     */ 
    lv_obj_t * scr = lv_obj_create(NULL, NULL);

    screenName = name;
}

lv_res_t Screen::loadScreen()
{
    lv_scr_load(scr);
    return LV_RES_OK;
}

const char * Screen::getName()
{
    return screenName;
}