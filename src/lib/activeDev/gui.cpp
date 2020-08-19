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
 * The LVGL button matrix objects that allows users to select an autonomous
 * routine.
 */ 
lv_obj_t * autonMenu;

//A label indicating what autonomous routine is currently selected
lv_obj_t * curAutonLbl;
//A button to run the current autonomous selected. Used for testing
lv_obj_t * runAuton;

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

void GUI::initAutonMenu()
{

    autonMenu = lv_btnm_create(scrAuton, NULL);
    lv_btnm_set_map(autonMenu, autonMap);
    lv_btnm_set_action(autonMenu, updateAutonID);
    lv_obj_align(autonMenu, NULL, LV_ALIGN_IN_TOP_MID, 35, 20);
    lv_obj_set_size(autonMenu, 300, 200);

    curAutonLbl = lv_label_create(scrAuton, NULL);
    lv_obj_align(curAutonLbl, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_label_set_text(curAutonLbl, "Auton");    
}

lv_res_t GUI::updateAutonID(lv_obj_t * btnm, const char * txt){

    if(txt == "Test") autonID = AUTON_TEST;
    else if(txt == "None") autonID = AUTON_NONE;
    else autonID = AUTON_NONE;
    updateAutonLbl();
    return LV_RES_OK;
}

void GUI::updateAutonLbl()
{
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