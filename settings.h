#if !defined(SETTINGS_H)
#define SETTINGS_H

//  General Settings

/////////////////////////////////////////////////////////////////////
//                          MAINMENU Settings
/////////////////////////////////////////////////////////////////////
#define MAINMENU_WIDTH 20
#define MAINMENU_ITEMS_COUNT 3
#define MAINMENU_ITEMS_LIST {"[0] RESUME GAME", "[1] NEW GAME", "[ESC] QUIT"}
#define MAINMENU_ITEM_TOP_MARGIN 1

/////////////////////////////////////////////////////////////////////
//                          Game Settings
/////////////////////////////////////////////////////////////////////
#define GAME_LEVEL_SCORE 50

//      GAME BOARD
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

//      GAME SPEED
#define GAME_DEFAULT_FALL_SPEED 40
#define GAME_FAST_FALL_SPEED 5
#define GAME_FALL_SPEED_STEP 5
#define GAME_FALL_SPEED_STEP_PER_LEVEL 5

//      SHAPE
#define SHAPE_COUNT 7
#define SHAPE_BLOCK_COUNT 4

#define SHAPE_O {{0.5, 0.5}, {BOARD_WIDTH / 2, 1}, {BOARD_WIDTH / 2 + 1, 1}, {BOARD_WIDTH / 2, 2}, {BOARD_WIDTH / 2 + 1, 2}} // The O shape
#define SHAPE_I {{1, 0}, {BOARD_WIDTH / 2 - 1, 1}, {BOARD_WIDTH / 2, 1}, {BOARD_WIDTH / 2 + 1, 1}, {BOARD_WIDTH / 2 + 2, 1}} // The I shape
#define SHAPE_S {{0, 1}, {BOARD_WIDTH / 2, 1}, {BOARD_WIDTH / 2 + 1, 1}, {BOARD_WIDTH / 2 - 1, 2}, {BOARD_WIDTH / 2, 2}} // The S shape
#define SHAPE_Z {{1, 1}, {BOARD_WIDTH / 2 - 1, 1}, {BOARD_WIDTH / 2, 1}, {BOARD_WIDTH / 2, 2}, {BOARD_WIDTH / 2 + 1, 2}} // The Z shape
#define SHAPE_L {{-1, 1}, {BOARD_WIDTH / 2 + 1, 1}, {BOARD_WIDTH / 2 - 1, 2}, {BOARD_WIDTH / 2, 2}, {BOARD_WIDTH / 2 + 1, 2}} // The L shape
#define SHAPE_J {{1, 1}, {BOARD_WIDTH / 2 - 1, 1}, {BOARD_WIDTH / 2 - 1, 2}, {BOARD_WIDTH / 2, 2}, {BOARD_WIDTH / 2 + 1, 2}} // The J shape
#define SHAPE_T {{0, 1}, {BOARD_WIDTH / 2, 1}, {BOARD_WIDTH / 2 - 1, 2}, {BOARD_WIDTH / 2, 2}, {BOARD_WIDTH / 2 + 1, 2}} // the T shape

#define SHAPE_LIST {SHAPE_O, SHAPE_I, SHAPE_S, SHAPE_Z, SHAPE_L, SHAPE_J, SHAPE_T}


/////////////////////////////////////////////////////////////////////
//                            UI Settings 
/////////////////////////////////////////////////////////////////////

//      BORDER
#define UI_TOP_PADDING 0
#define UI_BOTTOM_PADDING 0
#define UI_LEFT_PADDING 1
#define UI_RIGHT_PADDING 1

//      GAMEBOARD
#define UI_BOARD_X (UI_LEFT_PADDING + 2)
#define UI_BOARD_Y (UI_TOP_PADDING + 2)

//      SIDE MENU
#define UI_SIDEMENU_CONTENT_WIDTH 10
#define UI_SIDEMENU_LEFT_MARGIN 1

//      SCORE_BOX
#define UI_SCORE_BOX_TOP_MARGIN 1
#define UI_SCORE_BOX_HEIGHT 7

//      NEXT SHAPE box
#define UI_NSHAPE_BOX_TOP_MARGIN 1
#define UI_NSHAPE_BOX_HEIGHT 9

//      END GAME MESSAGE box
#define EMG_HEIGHT 6
#define EMG_WIDTH 35

//      OTHER UI SETTINGS
#define UI_SIDEMENU_WIDTH (UI_SIDEMENU_CONTENT_WIDTH + 2)

#define UI_SCORE_BOX_X (2 * BOARD_WIDTH + 2 + UI_SIDEMENU_LEFT_MARGIN + UI_LEFT_PADDING + 1)
#define UI_SCORE_BOX_Y (UI_SCORE_BOX_TOP_MARGIN)
#define UI_SCORE_X (UI_SCORE_BOX_X + 1)
#define UI_SCORE_Y (UI_SCORE_BOX_Y + UI_SCORE_BOX_HEIGHT / 2 + 1)

#define UI_NSHAPE_BOX_X (UI_SCORE_BOX_X)
#define UI_NSHAPE_BOX_Y (UI_SCORE_BOX_Y + UI_SCORE_BOX_HEIGHT + UI_NSHAPE_BOX_TOP_MARGIN)
#define UI_NSHAPE_X (UI_NSHAPE_BOX_X + 1)
#define UI_NSHAPE_Y (UI_NSHAPE_BOX_Y + 3)
#define UI_NSHAPE_W (UI_SIDEMENU_CONTENT_WIDTH)
#define UI_NSHAPE_H (UI_NSHAPE_BOX_HEIGHT - 4)

/////////////////////////////////////////////////////////////////////
//                         IO Settings
/////////////////////////////////////////////////////////////////////
#define FPS 60
#define FRAME_WIDTH (4 + 2 * BOARD_WIDTH + UI_SIDEMENU_WIDTH + UI_LEFT_PADDING + UI_RIGHT_PADDING + UI_SIDEMENU_LEFT_MARGIN)
#define FRAME_HEIGHT (4 + BOARD_HEIGHT + UI_TOP_PADDING + UI_BOTTOM_PADDING)

#define KEY_ESC 27
#define KEY_A 65
#define KEY_D 68
#define KEY_S 83
#define KEY_Z 90
#define KEY_SPACE 32
#define KEY_0 48
#define KEY_1 49



#endif // SETTINGS_H
