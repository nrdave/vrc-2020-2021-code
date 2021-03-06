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
const char * autonMap[] = {"None", "\n", "Test", "Skills", "\n", "Left", "Mid to Left", "\n", "Right", "Mid to Right", ""};

/**
 * The character array used by LVGL to hold the options in the
 * debug/telemetry data selection menu. Each entry in the array is 
 * a button in the matrix.
 * 
 */ 
const char * debugMap[] = {""};
/**
 * The enumerator used to store the ID of the current selected autonomous
 * It is set to value none by default so that if an autonomous routine is
 * not selected, the robot does not run an autonomous routine.
 */
Auton autonID = Auton::none;
/**
 * The LVGL objects for the GUI's screens.
 */ 
//The main menu screen
lv_obj_t * scrMain;
//The screen containing the autonomous routine selection menu
lv_obj_t * scrAuton;
//The screen containing the debug menu
lv_obj_t * scrDebug;

//The LVGL image object holding the main screen background
lv_obj_t * mainBackgroundIMG;
//The LVGL image object holding the auton screen background
lv_obj_t * autonBackgroundIMG;
//The LVGL image object holding the debug screen background
lv_obj_t * debugBackgroundIMG;
/**
 * Setting up the LVGL styles and colors I use to set the colors for LVGL 
 * objects.
 */ 

//LVGL default button style
static lv_style_t defaultStyle;
//LVGL button style for when a button or button matrix is pressed
static lv_style_t buttonStylePr;
//LVGL Style for the background of the autonMenu button matrix
static lv_style_t buttonMatrixStyle;

//LVGL color for the default object color
lv_color_t defaultObjectColor = LV_COLOR_MAKE(99, 46, 133);
//LVGL color for the default background color
lv_color_t defaultBorderColor = LV_COLOR_MAKE(194, 173, 209);
//LVGL color for the object color of buttonStylePr
lv_color_t buttonPrObjectColor = LV_COLOR_MAKE(67, 31, 89);
//LVGL color for the border color of buttonStylePr
lv_color_t buttonPrBorderColor = LV_COLOR_MAKE(142, 126, 153);
//LVGL color for the object color of buttonMatrixStyle
lv_color_t buttonMatrixObjectColor = LV_COLOR_MAKE(38, 17, 51);
//LVGL color for the border color of buttonMatrixStyle
lv_color_t buttonMatrixBorderColor = LV_COLOR_MAKE(97, 86, 104);
/**
 * Declaring the backgroundHome.c file as an LVGL image, so
 * it can be used in the creation of the main screen
 * background
 */ 
LV_IMG_DECLARE(backgroundHome);
/**
 * Declaring the backgroundAlt.c file as an LVGL image, so
 * it can be used in the creation of the autonomous menu background
 */ 
LV_IMG_DECLARE(backgroundAlt);
/**
 * The LVGL objects used for the navigation between the screens. 
 */ 
//The button to go from scrMain to scrAuton
lv_obj_t * navAuton;
//The button to go from scrAuton to scrMain
lv_obj_t * navMainFromAuton;
//The button to go from scrMain to scrDebug
lv_obj_t * navDebug;
//the button to go from scrAuton to scrMain
lv_obj_t * navMainFromDebug;
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
lv_obj_t * autonRunBtn;

/**
 * The LVGL objects used in the debug menu screen
 */ 
/**
 * LVGL button matrix the debug screen used to select which
 * subsystem data to display
 */ 
lv_obj_t * debugSelectBtnm;
/**
 * LVGL labels used to display the data selected
 */ 
lv_obj_t * debugData1;
lv_obj_t * debugData2;

void GUI::initialize()
{
    //Initializing the screens
    scrMain = createScreen();
    scrAuton = createScreen();
    scrDebug = createScreen();

    //Setting up the styles
    lv_style_copy(&defaultStyle, &lv_style_plain);
    defaultStyle.body.main_color = defaultObjectColor;
    defaultStyle.body.grad_color = defaultObjectColor;
    defaultStyle.text.color = LV_COLOR_WHITE;
    defaultStyle.body.border.color = defaultBorderColor;
    defaultStyle.body.radius = 15;
    defaultStyle.body.border.width = 2;

    lv_style_copy(&buttonStylePr, &defaultStyle);
    buttonStylePr.body.main_color = buttonPrObjectColor;
    buttonStylePr.body.grad_color = buttonPrObjectColor;
    buttonStylePr.body.border.color = buttonPrBorderColor;

    lv_style_copy(&buttonMatrixStyle, &defaultStyle);
    buttonMatrixStyle.body.border.width = 2;
    buttonMatrixStyle.body.padding.inner = 1;
    buttonMatrixStyle.body.padding.hor = 1;
    buttonMatrixStyle.body.padding.ver = 1;
    buttonMatrixStyle.body.main_color = buttonMatrixObjectColor;
    buttonMatrixStyle.body.grad_color = buttonMatrixObjectColor;
    buttonMatrixStyle.body.border.color = buttonMatrixBorderColor;

    //Initializing the backround images for the screens

    //Initializing the home screen background
    mainBackgroundIMG = lv_img_create(scrMain, NULL);
    lv_img_set_src(mainBackgroundIMG, &backgroundHome);
    lv_obj_align(mainBackgroundIMG, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    //Initializing the autonomous menu screen background
    autonBackgroundIMG = lv_img_create(scrAuton, NULL);
    lv_img_set_src(autonBackgroundIMG, &backgroundAlt);
    lv_obj_align(autonBackgroundIMG, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    //Initializing the debug menu screen background
    debugBackgroundIMG = lv_img_create(scrDebug, NULL);
    lv_img_set_src(debugBackgroundIMG, &backgroundAlt);
    lv_obj_align(debugBackgroundIMG, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    //Initializing the navigation buttons

    //Initializing the button to switch to the autonomous menu screen    
    navAuton = createButton(scrMain, LV_BTN_ACTION_CLICK, goToAuton, "Auton Menu", LV_ALIGN_IN_LEFT_MID, 10, 0, 125, 50);
    lv_btn_set_style(navAuton, LV_BTN_STATE_REL, &defaultStyle);
    lv_btn_set_style(navAuton, LV_BTN_STATE_PR, &buttonStylePr);

    //Initializing the button to return to the main menu from the autonomous screen
    navMainFromAuton = createButton(scrAuton, LV_BTN_ACTION_CLICK, goToMain, "Main Menu", LV_ALIGN_IN_LEFT_MID, 20, 0, 100, 50);
    lv_btn_set_style(navMainFromAuton, LV_BTN_STATE_REL, &defaultStyle);
    lv_btn_set_style(navMainFromAuton, LV_BTN_STATE_PR, &buttonStylePr);

    //Initializing the button to switch to the debug menu screen
    navDebug = createButton(scrMain, LV_BTN_ACTION_CLICK, goToDebug, "Debug Menu", LV_ALIGN_IN_RIGHT_MID, -10, 0, 125, 50);
    lv_btn_set_style(navDebug, LV_BTN_STATE_REL, &defaultStyle);
    lv_btn_set_style(navDebug, LV_BTN_STATE_PR, &buttonStylePr);

    //Initializing the button to return to the main menu from the autonomous screen
    navMainFromDebug = createButton(scrDebug, LV_BTN_ACTION_CLICK, goToMain, "Main Menu", LV_ALIGN_IN_TOP_LEFT, 10, 10, 125, 30);
    lv_btn_set_style(navMainFromDebug, LV_BTN_STATE_REL, &defaultStyle);
    lv_btn_set_style(navMainFromDebug, LV_BTN_STATE_PR, &buttonStylePr);


    //Initializing the Autonomous Menu

    //Initializing the autonomous selection button matrix
    autonMenu = createButtonMatrix(scrAuton, autonMap, updateAutonID, LV_ALIGN_IN_TOP_MID, 35, 20, 300, 200);
    lv_btnm_set_style(autonMenu, LV_BTNM_STYLE_BTN_REL, &defaultStyle);
    lv_btnm_set_style(autonMenu, LV_BTNM_STYLE_BG, &buttonMatrixStyle);
    lv_btnm_set_style(autonMenu, LV_BTNM_STYLE_BTN_PR, &buttonStylePr);

    //Initializing the label indicating the autonomous selected
    curAutonLbl = createLabel(scrAuton, "Auton", LV_ALIGN_IN_TOP_LEFT, 10, 10);

    //Initializing the Debug Menu
    debugSelectBtnm = createButtonMatrix(scrDebug, debugMap, updateTelemetryData, LV_ALIGN_IN_TOP_LEFT, 10, 45, 460, 50);
    lv_btnm_set_style(debugSelectBtnm, LV_BTNM_STYLE_BTN_REL, &defaultStyle);
    lv_btnm_set_style(debugSelectBtnm, LV_BTNM_STYLE_BG, &buttonMatrixStyle);
    lv_btnm_set_style(debugSelectBtnm, LV_BTNM_STYLE_BTN_PR, &buttonStylePr);   

    debugData1 = createLabel(scrDebug, "Debug Data", LV_ALIGN_IN_LEFT_MID, 10, -10); 
    debugData2 = createLabel(scrDebug, "Debug Data", LV_ALIGN_IN_LEFT_MID, 10, 55); 
    //Loading the main screen to the brain display
    lv_scr_load(scrMain);
}

lv_obj_t * GUI::createButton(lv_obj_t * parent, lv_btn_action_t pressType, lv_action_t function,
                             const char* text, lv_align_t align, 
                             lv_coord_t xCoord, lv_coord_t yCoord,
                             lv_coord_t width, lv_coord_t height)
{
    //Creating an LVGL button
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    //Setting the button's action upon a given type of trigger
    lv_btn_set_action(btn, pressType, function);   
    //Aligning the button relative to its parent
    lv_obj_align(btn, NULL, align, xCoord, yCoord);
    //Setting the button's size
    lv_obj_set_size(btn, width, height);
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

lv_obj_t * GUI::createButtonMatrix(lv_obj_t * parent, const char* map[], lv_btnm_action_t function,
                                   lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord, 
                                   lv_coord_t width, lv_coord_t height)
{
    //Creating an LVGL button matrix
    lv_obj_t * btnm = lv_btnm_create(parent, NULL);
    //Setting the button matrix's action upon a given type of trigger
    lv_btnm_set_action(btnm, function);   
    //Set the String array to be used to create the button matrix
    lv_btnm_set_map(btnm, map);
    //Aligning the button matrix relative to its parent
    lv_obj_align(btnm, NULL, align, xCoord, yCoord);
    //Setting the size of the button matrix
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
    if(txt == "Test") autonID = Auton::test;
    else if(txt == "None") autonID = Auton::none;
    else if(txt == "Skills") autonID = Auton::skills;
    else if(txt == "Left") autonID = Auton::left;
    else if(txt == "Mid to Left") autonID = Auton::midleft;
    else if(txt == "Right") autonID = Auton::right;
    else if(txt == "Mid to Right") autonID = Auton::midright;
    else autonID = Auton::none;
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
        case Auton::test:
            lv_label_set_text(curAutonLbl, "Test");
            break;
        case Auton::skills:
            lv_label_set_text(curAutonLbl, "Skills");
            break;
        case Auton::left:
            lv_label_set_text(curAutonLbl, "Left Corner");
            break;
        case Auton::midleft:
            lv_label_set_text(curAutonLbl, "Middle + Left Corner");
            break;
        case Auton::right:
            lv_label_set_text(curAutonLbl, "Right Corner");
            break;
        case Auton::midright:
            lv_label_set_text(curAutonLbl, "Middle + Right Corner");
            break;
        case Auton::none:
            lv_label_set_text(curAutonLbl, "No Auton Selected");
            break;
    }
}

lv_res_t GUI::updateTelemetryData(lv_obj_t * btnm, const char* txt)
{

    lv_label_set_text(debugData1, "No Data Selected");
    lv_label_set_text(debugData2, "No Data Selected"); 
    return LV_RES_OK;
}

void GUI::updateTelemetryLabel(lv_obj_t * label, Telemetry t)
{   
    /**
     * Creating char arrays to hold the rounded data for each telemetry value
     * I do this to cut the size of the data, rather than
     * printing every character, which includes a lot of zeros at the end
     * The arrays are 30 characters in order to include the labels for each data value
     */ 
    char pos[30]; 
    char targPos[30]; 
    char velo[30]; 
    char targVelo[30]; 
    char temp[30]; 
    char torque[30]; 
    //Creating a char[] to write the output to
    char output[256];
    //Printing the Telemetry values to their respective arrays
    snprintf(pos, 30, "Position: %f", t.pos);
    snprintf(targPos, 30, "Target Position: %f", t.targetPos);
    snprintf(velo, 30, "Velocity: %f", t.velo);
    snprintf(targVelo, 30, "Target Velocity%f", t.targetVelo);
    snprintf(temp, 30, "Temperature: %f", t.temp);
    snprintf(torque, 30, "Torque %f", t.torque);
    //Printing the shortened telemetry values to the output array
    snprintf(output, 256, "%s%s\n%s%s\n%s%s", pos, targPos, velo, targVelo, temp, torque);
    //Setting the text on the label
    lv_label_set_text(label, output);
}
/**
 * LVGL doesn't allow functions with parameters to be a callback function for a
 * button action, so I had to wrap a few functions, such as lv_scr_load(), which loads a screen,
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

lv_res_t GUI::goToDebug(lv_obj_t * btn)
{
    lv_scr_load(scrDebug);
    return LV_RES_OK;
}

lv_res_t GUI::runAuton(lv_obj_t * btn)
{
    autonomous();
    return LV_RES_OK;
}