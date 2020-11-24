#pragma once
#include "pros/apix.h"
#include "library.hpp"
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

    /**
     * A function containing all the function calls I make to initialize the GUI
     * This allows me to write all the GUI code in gui.cpp, and just call this function
     * in initialize.cpp, rather than initialize the GUI in the PROS initialize() function
     */ 
    void initialize();

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
     * @param width: the width of the button 
     * @param height: the height of the button     
     * @param btnStyleRel: the LVGL style of the button when released, used to set the colors, shape, and
     *                     other cosmetic factors of the button when it isn't pressed     
     * @param btnStylePr: the LVGL style of the button when pressed, used to set the colors, shape, and
     *                     other cosmetic factors of the button when it is being pressed
     */ 
    lv_obj_t * createButton(lv_obj_t * parent, lv_btn_action_t pressType, lv_action_t function,
                            const char* text, lv_align_t align, lv_coord_t xCoord, 
                            lv_coord_t yCoord, lv_coord_t width, lv_coord_t height,
                            lv_style_t btnStyleRel, lv_style_t btnStylePr);


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

    /**
     * A function to create an LVGL button matrix object. It packages all the LVGL functions to 
     * create, set the character map of, and align and size the button matrix into one function
     * 
     * @param parent: the LVGL object the image should be created in
     * @param map: a pointer to a String array used to generate the matrix of
     *             buttons and their labels
     * @param function: the function to be called when a button in the matrix is clicked
     * @param align: the LVGL alignment type, aligns relative to the parent object
     * @param xCoord: the x coordinate offset from the given alignment
     * @param yCoord: the y coordinate offset from the given alignment
     * @param width: the width of the button matrix
     * @param height: the height of the button matrix
     * @param btnmStyleRel: the LVGL style of the button matrix when pressed, used to set the colors, shape, and
     *                     other cosmetic factors of the button matrix when one of the buttons are being pressed  
     * @param btnmStylePr: the LVGL style of the button matrix when pressed, used to set the colors, shape, and
     *                     other cosmetic factors of the button matrix when no buttons are being pressed
     * @param btnmStyleBG: The LVGL style of the button matrix's background    
     */ 
    lv_obj_t * createButtonMatrix(lv_obj_t * parent, const char* map[], lv_btnm_action_t function,
                                  lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord,
                                  lv_coord_t width, lv_coord_t height,
                                  lv_style_t btnmStyleRel, lv_style_t btnmStylePr, lv_style_t btnmStyleBG);

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

    void updateTelemetryLabel(lv_obj_t * label, Telemetry t);

    /**
     * A function used to call autonomous() when the runAuton button is pressed
     * LVGL requires callback functions to return type lv_res_t, so I had
     * to wrap autonomous() in this function
     */ 
    lv_res_t runAuton(lv_obj_t * btn);

    //Functions to navigate to specific LVGL Screens. Used in the navigation buttons
    lv_res_t goToMain(lv_obj_t * btn);
    lv_res_t goToAuton(lv_obj_t * btn);
    lv_res_t goToDebug(lv_obj_t * btn);
}