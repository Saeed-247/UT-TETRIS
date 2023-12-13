#include "settings.h"
#include "UI/menu.h"
#include "UI/utils.h"

void UI_showMainMenu(char frame[FRAME_HEIGHT][FRAME_WIDTH], int startIndex) {
    int cntMenuItems = MAINMENU_ITEMS_COUNT - startIndex;
    char* menuItems[MAINMENU_ITEMS_COUNT] = MAINMENU_ITEMS_LIST;

    int topMargin = (FRAME_HEIGHT - cntMenuItems * (MAINMENU_ITEM_TOP_MARGIN + 1)) / 2;
    int leftMargin = (FRAME_WIDTH - MAINMENU_WIDTH) / 2;

    /*
        filling the frame buffer with ' ' character
        we need to do this to replace all null characters
    */
    for (int i = 0; i < FRAME_HEIGHT; i++) {
        for (int j = 0; j < FRAME_WIDTH ; j++) {
            frame[i][j] = ' ';
        }
    }

    // drawing outer border
    UI_drawBorder(frame, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);

    for (int i = startIndex; i < MAINMENU_ITEMS_COUNT; i++) {
        UI_centerAlignText(menuItems[i], frame[topMargin + (MAINMENU_ITEM_TOP_MARGIN + 1) * (i - startIndex)] + leftMargin, MAINMENU_WIDTH);
    }
}