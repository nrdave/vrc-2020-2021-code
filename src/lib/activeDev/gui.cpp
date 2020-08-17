#include "main.h"

/**
 * The implementations for the GUI namespace functions
 * These functions initialize LVGL objects or handle
 * event triggers from those objects.
 */ 

void GUI::initScreens()
{
    /**
     * To initalize a screen in LVGL, you use the lv_obj_create() function with NULL
     * for both parameters
     */ 
    scrMain = lv_obj_create(NULL, NULL);
    scrAuton = lv_obj_create(NULL, NULL);
}

void GUI::initialize()
{
    //Calling all init functions
    initScreens();
    initNavButtons();
}

void GUI::initNavButtons()
{
    /**
     * Initializing the navigation buttons with the lv_btn_create function, which
     * creates. The first parameter is the parent object (in this case, each button's
     * respective screen), while the second parameter an object to copy
     */ 
    navAuton = lv_btn_create(scrMain, NULL);
    navMainFromAuton = lv_btn_create(scrAuton, NULL);
    /**
     * Setting the action of each button when clicked to the function to 
     * switch to each button's screen to navigate to.
     */ 
    lv_btn_set_action(navAuton, LV_BTN_ACTION_CLICK, goToAuton);
    lv_btn_set_action(navMainFromAuton, LV_BTN_ACTION_CLICK, goToMain);
    //Aligning each button relative to the screen
    lv_obj_align(navAuton, NULL, LV_ALIGN_IN_LEFT_MID, 20, 0);
    lv_obj_align(navMainFromAuton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);
}


/**
 * LVGL doesn't allow functions with parameters to be a callback function for a
 * button action, so I had to wrap the lv_scr_load() function, which loads a screen,
 * in a format that the lv_btn_set_action() function would accept
 */ 
lv_res_t GUI::goToAuton(lv_obj_t * btn)
{
    lv_scr_load(scrAuton);
    return LV_RES_OK;
}

lv_res_t GUI::goToMain(lv_obj_t * btn)
{
    lv_scr_load(scrMain);
    return LV_RES_OK;
}