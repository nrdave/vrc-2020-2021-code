#include "main.h"

GUI::GUI(Screen main, std::initializer_list<Screen> scrs)
{
    scrMain = main;
    screens = scrs;
    for(Screen& s : screens)
    {
        s.addButton(lv_obj_t * goToMain, main.getName(), LV_ALIGN_IN_LEFT_MID, 20, 0, main.loadScreen());
        main.addButton(lv_obj_t * b, s.getName(), LV_ALIGN_IN_LEFT_MID, 20, 0, s.loadScreen());
    }
}

