#include <stdio.h>

#include "settings.h"
#include "UI/game.h"
#include "UI/utils.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

/*
    This function draws the game main UI
*/
void UI_initGame(char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
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

    // draw game board border
    UI_drawBorder(frame, UI_LEFT_PADDING + 1, UI_TOP_PADDING + 1, 2 * BOARD_WIDTH + 2, BOARD_HEIGHT + 2);

    // drawing score box
    UI_drawBorder(frame, UI_SCORE_BOX_X, UI_SCORE_BOX_Y, UI_SIDEMENU_CONTENT_WIDTH + 2, 3);
    UI_drawBorder(frame, UI_SCORE_BOX_X, UI_SCORE_BOX_Y, UI_SIDEMENU_CONTENT_WIDTH + 2, UI_SCORE_BOX_HEIGHT);
    UI_centerAlignText("SCORE", frame[UI_SCORE_BOX_Y + 1] + UI_SCORE_BOX_X + 1, UI_SIDEMENU_CONTENT_WIDTH);

    // drawing next shape box
    UI_drawBorder(frame, UI_NSHAPE_BOX_X, UI_NSHAPE_BOX_Y, UI_SIDEMENU_CONTENT_WIDTH + 2, 3);
    UI_drawBorder(frame, UI_NSHAPE_BOX_X, UI_NSHAPE_BOX_Y, UI_SIDEMENU_CONTENT_WIDTH + 2, UI_NSHAPE_BOX_HEIGHT);
    UI_centerAlignText("NEXT", frame[UI_NSHAPE_BOX_Y + 1] + UI_NSHAPE_BOX_X + 1, UI_SIDEMENU_CONTENT_WIDTH);    
}

/*
    This function gets the game board and current frame as input and adds the game board to the frame
*/
void UI_updateBoard(char board[BOARD_HEIGHT][BOARD_WIDTH], char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == '#') {
                frame[UI_BOARD_Y + i][UI_BOARD_X + 2 * j] = '[';
                frame[UI_BOARD_Y + i][UI_BOARD_X + 2 * j + 1] = ']';
            }
            else {
                frame[UI_BOARD_Y + i][UI_BOARD_X + 2 * j] = frame[UI_BOARD_Y + i][UI_BOARD_X + 2 * j + 1] = ' ';
            }
        }
    }
}

/*
    This function gets the current frame and a score and updates the current frame score box
*/
void UI_updateScore(int score, char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
    // convert score to string
    char scoreStr[UI_SIDEMENU_CONTENT_WIDTH];
    sprintf(scoreStr, "%d", score);
    
    UI_centerAlignText(scoreStr, frame[UI_SCORE_Y] + UI_SCORE_X, UI_SIDEMENU_CONTENT_WIDTH);
}

/*
    This function gets a Shape as input and displays it in the next shape box
*/
void UI_updateNShape(Shape nextShape, char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
    //  creating an empty buffer the size of the next shape box
    char buffer[UI_NSHAPE_H][UI_NSHAPE_W];
    for (int i = 0; i < UI_NSHAPE_H; i++) {
        for (int j = 0; j < UI_NSHAPE_W; j++) {
            buffer[i][j] = ' ';
        }
    }

    /*
        Finding the width, height, min_x, and min_y of the shape
        These values are then used to display the shape in the center of the box
    */
    int min_x = 1e5, min_y = 1e5, max_x = -1e5, max_y = -1e5, w, h;
    for (int i = 1; i <= SHAPE_BLOCK_COUNT; i++) {
        min_x = min(min_x, nextShape[i][0]);
        max_x = max(max_x, nextShape[i][0]);
        min_y = min(min_y, nextShape[i][1]);
        max_y = max(max_y, nextShape[i][1]);
    }
    h = max_y - min_y + 1;
    w = max_x - min_x + 1;

    int topPadding = (UI_NSHAPE_H - h) / 2;
    int leftPadding = (UI_NSHAPE_W - 2 * w) / 2;

    // adding the shape to our buffer
    for (int i = 1; i <= SHAPE_BLOCK_COUNT; i++) {
        buffer[topPadding + (int)nextShape[i][1] - min_y][leftPadding + 2 * ((int)nextShape[i][0] - min_x)] = '[';
        buffer[topPadding + (int)nextShape[i][1] - min_y][leftPadding + 2 * ((int)nextShape[i][0] - min_x) + 1] = ']';
    }

    // printing the buffer to the frame
    for (int i = 0; i < UI_NSHAPE_H; i++) {
        for (int j = 0; j < UI_NSHAPE_W; j++) {
            frame[UI_NSHAPE_Y + i][UI_NSHAPE_X + j] = buffer[i][j];
        }
    }
    
}

/*
    This function draws the end-game message box in the center of the frame
*/
void UI_showEndMessageBox(int score, int highScore, char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
    char scoreStr[50], highScoreStr[50];
    sprintf(scoreStr, "SCORE: %d", score);
    sprintf(highScoreStr, "HIGH SCORE: %d", highScore);

    int topMargin = (FRAME_HEIGHT - EMG_HEIGHT) / 2;
    int leftMargin = (FRAME_WIDTH - EMG_WIDTH) / 2;

    UI_drawBorder(frame, leftMargin - 1, topMargin - 1, EMG_WIDTH + 2, EMG_HEIGHT + 2);
    UI_centerAlignText("GAME OVER", frame[topMargin] + leftMargin, EMG_WIDTH);
    UI_centerAlignText("", frame[topMargin + 1] + leftMargin, EMG_WIDTH);
    UI_centerAlignText(scoreStr, frame[topMargin + 2] + leftMargin, EMG_WIDTH);
    UI_centerAlignText(highScoreStr, frame[topMargin + 3] + leftMargin, EMG_WIDTH);
    UI_centerAlignText("", frame[topMargin + 4] + leftMargin, EMG_WIDTH);
    UI_centerAlignText("[0]RETRY   [ESC]MAINMENU", frame[topMargin + 5] + leftMargin, EMG_WIDTH);
}