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

    /**
     * A function to create an LVGL image object. It packages all the LVGL functions to create,
     * set the source file of, and align an image into one function
     * 
     * @param parent: the LVGL object the image should be created in
     * @param imgSRC: the file where the image source data is contained (this file needs to be
     *         LV_IMG_DECLARE'd before passing it in)
     * @param align: the LVGL alignment type, aligns relative to the parent object
     * @param xCoord: the x coordinate offset from the given alignment
     * @param yCoord: the y coordinate offset from the given alignment
     */ 
    lv_obj_t * createImage(lv_obj_t * parent, const lv_img_dsc_t imgSRC, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord);

    /**
     * A function to create an LVGL button object. It packages all the LVGL functions to create,
     * set the press type and action, and align a button into one function, as well as handling
     * the creation of a label for the button
     * 
     * @param parent: the LVGL object the image should be created in
     * @param pressType: the button press type (Click, hold, long press, etc.)
     * @param function: the function to be called when the button is triggered
     * @param text: the label text on the button
     * @param align: the LVGL alignment type, aligns relative to the parent object
     * @param xCoord: the x coordinate offset from the given alignment
     * @param yCoord: the y coordinate offset from the given alignment
     */ 
    lv_obj_t * createButton(lv_obj_t * parent, lv_btn_action_t pressType, lv_action_t function, const char* text, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord);


    /**
     * A function to create an LVGL image object. It packages all the LVGL functions to create,
     * set the source file of, and align an image into one function
     * 
     * @param parent: the LVGL object the image should be created in
     * @param text: the text of the label
     * @param align: the LVGL alignment type, aligns relative to the parent object
     * @param xCoord: the x coordinate offset from the given alignment
     * @param yCoord: the y coordinate offset from the given alignment
     */ 
    lv_obj_t * createLabel(lv_obj_t * parent, const char* text, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord);


    lv_obj_t * createButtonMatrix(lv_obj_t * parent, const char* map[], lv_btnm_action_t function, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord, lv_coord_t width, lv_coord_t height);

    /**
     * A function to create an LVGL screen. It simply wraps the LVGL lv_obj_create(NULL, NULL)
     * function call, used to create a screen, in a nicer format
     */ 
    lv_obj_t * createScreen();

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