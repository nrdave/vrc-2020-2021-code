#include "main.h"

/**
 * The implementations for the GUI namespace functions, along with the
 * declarations of all LVGL objects used.
 * The functions initialize LVGL objects or handle
 * event triggers from those objects.
 * 
 * The LVGL objects are declared here, as doing so in the header file leads
 * to multiple definition errors
 */


/**
 * The character array used by LVGL to hold all the options in the
 * autonomous routine selection menu. Each entry in the array is 
 * a button in the matrix, while the \n characters indicate a switch
 * to a new line
 */ 
const char * autonMap[] = {"Test", "\n", "None"};

/**
 * The variable used to store the ID of the current selected autonomous
 * It is set to 0 so that if no autonomous is selected, the value of 
 * autonID corresponds to not running an autonomous routine.
 */
int autonID = 0;
/**
 * The LVGL objects for the GUI's screens. As of now there are 2, the main 
 * home screen and the screen for autonomous selection
 */ 
//The main menu screen
lv_obj_t * scrMain;
//The screen containing the autonomous routine selection menu
lv_obj_t * scrAuton;

//The LVGL image object holding the main screen background
lv_obj_t * mainBackgroundIMG;
//The LVGL image object holding the auton screen background
lv_obj_t * autonBackgroundIMG;


//LVGL style object used to make the auton screen background translucent
static lv_style_t autonIMGstyle;

/**
 * Declaring the background.c file as an LVGL image, so
 * it can be used in the creation of the main screen
 * background
 */ 
LV_IMG_DECLARE(background);
/**
 * The LVGL objects used for the navigation between the screens. There are
 * 2 per screen besides the main menu, so currently just 2
 */ 
//The button to go from scrMain to scrAuton
lv_obj_t * navAuton;
//The button to go from scrAuton to scrMain
lv_obj_t * navMainFromAuton;

/**
 * The LVGL objects used in the autonomous routine selection menu.
 */ 

/**
 * The LVGL button matrix object that allows users to select an autonomous
 * routine.
 */ 
lv_obj_t * autonMenu;

//A label indicating what autonomous routine is currently selected
lv_obj_t * curAutonLbl;
//A button to run the current autonomous selected. Used for testing
lv_obj_t * runAuton;

void GUI::initialize()
{
    //Initializing the screens
    scrMain = createScreen();
    scrAuton = createScreen();

    //Initializing the backround images for the screens

    //Initializing the home screen background
    mainBackgroundIMG = createImage(scrMain, background, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    //Initializing the autonomous menu screen background
    autonBackgroundIMG = createImage(scrAuton, background, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    //Making the autonomous selection background mostly transparent
    lv_style_copy(&autonIMGstyle, &lv_style_scr);
    autonIMGstyle.image.opa = LV_OPA_10;
    lv_img_set_style(autonBackgroundIMG, &autonIMGstyle);

    //Initializing the navigation buttons

    //Initializing the button to switch to the autonomous menu screen    
    navAuton = createButton(scrMain, LV_BTN_ACTION_CLICK, goToAuton, "Auton Menu", LV_ALIGN_IN_LEFT_MID, 20, 0);

    //Initializing the button to return to the main menu from the autonomous screen
    navMainFromAuton = createButton(scrMain, LV_BTN_ACTION_CLICK, goToMain, "Main Menu", LV_ALIGN_IN_TOP_LEFT, 20, 20);

    //Initializing the Autonomous Menu

    //Initializing the autonomous selection button matrix
    autonMenu = createButtonMatrix(scrAuton, autonMap, updateAutonID, LV_ALIGN_IN_TOP_MID, 35, 20, 300, 200);

    //Initializing the label indicating the autonomous selected
    curAutonLbl = createLabel(scrAuton, "Auton", LV_ALIGN_IN_TOP_LEFT, 10, 10);
}

lv_obj_t * GUI::createImage(lv_obj_t * parent, const lv_img_dsc_t imgSRC, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord)
{
    //Creating an LVGL image
    lv_obj_t * img = lv_img_create(parent, NULL);
    //Setting the source file for the image data
    lv_img_set_src(img, &imgSRC);
    //Aligning the image relative to its parent
    lv_obj_align(img, NULL, align, xCoord, yCoord);
    /**
     * Return the created image
     * This returns the image to the declared LVGL object in
     * initialize, making that object into an identical image to 
     * the image img created in this function.
     */ 
    return img;
}

lv_obj_t * GUI::createButton(lv_obj_t * parent, lv_btn_action_t pressType, lv_action_t function, const char* text, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord)
{
    //Creating an LVGL button
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    //Setting the button's action upon a given type of trigger
    lv_btn_set_action(btn, pressType, function);   
    //Aligning the button relative to its parent
    lv_obj_align(btn, NULL, align, xCoord, yCoord);
    //Creating a label for the button
    lv_obj_t * label = createLabel(btn, text, LV_ALIGN_CENTER, 0, 0);
    /**
     * Return the created button
     * This returns the button to the declared LVGL object in
     * initialize, making that object into an identical button to 
     * the button btn created in this function.
     */ 
    return btn;
}

lv_obj_t * GUI::createLabel(lv_obj_t * parent, const char* text, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord)
{
    //Creating a LVGL Label
    lv_obj_t * lbl = lv_label_create(parent, NULL);
    //Aligning the label relative to its parent
    lv_obj_align(lbl, NULL, align, xCoord, yCoord);
    //Setting the label's text
    lv_label_set_text(lbl, text);  
    /**
     * Return the created label
     * This returns the label to the declared LVGL object in
     * initialize, making that object into an identical label to 
     * the label lbl created in this function.
     */ 
    return lbl;
}


lv_obj_t * GUI::createButtonMatrix(lv_obj_t * parent, const char* map[], lv_btnm_action_t function, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord, lv_coord_t width, lv_coord_t height)
{
    //Creating an LVGL button matrix
    lv_obj_t * btnm = lv_btnm_create(parent, NULL);
    //Setting the button matrix's action upon a given type of trigger
    lv_btnm_set_action(btnm, function);   
    //Set the String array to be used to create the button matrix
    lv_btnm_set_map(btnm, map);
    //Aligning the button matrix relative to its parent
    lv_obj_align(btnm, NULL, align, xCoord, yCoord);

    lv_obj_set_size(btnm, width, height);
    /**
     * Return the created button matrix
     * This returns the button matrix to the declared LVGL object in
     * initialize, making that object into an identical button matrix to 
     * the button matrix btnm created in this function.
     */ 
    return btnm;
}

lv_obj_t * GUI::createScreen()
{
    /**
     * This function merely hides the calling of lv_obj_create(NULL, NULL)
     * so the function itself just creates a screen and returns it
     */ 
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    return scr;
}

lv_res_t GUI::updateAutonID(lv_obj_t * btnm, const char * txt){
    /**
     * Running the current selected button in the matrix through a
     * series of if-else-if statements to determine which autonomous
     * routine is selected. If there are any issues, the function
     * defaults to no autonomous
     */ 
    if(txt == "Test") autonID = AUTON_TEST;
    else if(txt == "None") autonID = AUTON_NONE;
    else autonID = AUTON_NONE;
    //Updating the label for the current selected autonomous
    updateAutonLbl();
    return LV_RES_OK;
}

void GUI::updateAutonLbl()
{
    /**
     * Using autonID as a switch, the function determines
     * the current autonomous routine selected and sets 
     * the current Autonomous label to the corresponding
     * text
     */ 
    switch(autonID)
    {
        case AUTON_TEST:
            lv_label_set_text(curAutonLbl, "Test");
            break;
        case AUTON_NONE:
            lv_label_set_text(curAutonLbl, "No Auton Selected");
            break;
    }
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