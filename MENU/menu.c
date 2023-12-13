#include "settings.h"
#include "MENU/menu.h"
#include "IO/io.h"
#include "UI/menu.h"
#include "UI/game.h"
#include "GAME/game.h"

extern int gameOver;
extern int escaped;

// state = 1 -> game, state = 0 -> main menu
int state = 0;

/*
    This function is called once we switch to the main-menu
*/
void MENU_start(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt, int startIndex) {
    UI_showMainMenu(frame, startIndex);
}

/*
    This function is called once per loop cycle
*/
void MENU_update(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt) {

}

/*
    This function is called once per frame
*/
void MENU_fixedUpdate(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt) {
    /*
        read input if there is input available 
        if there is no input available ch will be '-'
    */
    char ch = IO_getInput();

    // check if ESC key is pressed
    if ((int)ch == KEY_ESC) {
        escaped = 1;
    }

    // Manage user input
    switch(ch) {
        case KEY_0:
            if (!gameOver) {
                state = 1;
                GAME_start(frame, frameCnt, 0);
            }
            break;
        case KEY_1:
            state = 1;
            GAME_start(frame, frameCnt, 1);
            break;
    }

}