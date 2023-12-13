#include "settings.h"
#include "GAME/game.h"
#include "GAME/shape.h"
#include "GAME/utils.h"
#include "UI/game.h"
#include "IO/io.h"
#include "IO/utils.h"
#include "MENU/menu.h"

int gameOver = 1;
static int fallSpeed = GAME_DEFAULT_FALL_SPEED;
static int score = 0;
static int highScore = 0;
static char gameBoard[BOARD_HEIGHT][BOARD_WIDTH];

extern int state;

Shape currentShape, nextShape;

/*
    This function is called at the begging of the game
*/
void GAME_start(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt, int reset) {
    if (reset) {
        // clearing The gameBoard
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                gameBoard[i][j] = ' ';
            }
        }

        // Resetting variables
        score = 0;
        gameOver = 0;
        fallSpeed = GAME_DEFAULT_FALL_SPEED;
        
        // spawning current shape and generate the next shape
        SHAPE_getShape(nextShape, randint(0, SHAPE_COUNT));
        GAME_generateNextShape();
    }

    // drawing the initail game frame
    UI_initGame(frame);
    UI_updateNShape(nextShape, frame);
    UI_updateScore(score, frame);
}

/*
    This function is called once per loop cycle
*/
void GAME_update(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt) {
    /*
        read input if there is input available 
        if there is no input available ch will be '-'
    */
    char ch = IO_getInput();

    // check if ESC key is pressed
    if ((int)ch == KEY_ESC) {
        state = 0;
        MENU_start(frame, frameCnt, gameOver);
    }

     // Manage user input
    switch(IO_toUpper(ch)) {
        case KEY_A:
            GAME_moveLeft();
            break;
        case KEY_D:
            GAME_moveRight();
            break;
        case KEY_S:
            GAME_increaseSpeed();
            break;
        case KEY_SPACE:
            GAME_rotateShape(3);
            break;
        case KEY_Z:
            GAME_rotateShape(1);
            break;
        case KEY_0:
            if (gameOver) {
                GAME_start(frame, frameCnt, 1);
            }
            break;
    }
}

/*
    This function is called once per frame
*/
void GAME_fixedUpdate(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt) {
    if (gameOver) {
        return;
    }

    // Insert current shape into the gameboard
    SHAPE_add(currentShape, gameBoard);

    /*
        The following if block is executed based on the fall speed
        all game functions that are based on game speed should be inside this block
    */
    if (frameCnt % fallSpeed == 0) {
        /*
            This next if block will be executed if we can not move current shape down anymore
            other wise its will only move down current shape
        */
        if (GAME_moveDown()) {
            // Reset the fall speed for the next shape
            fallSpeed = GAME_DEFAULT_FALL_SPEED - (score / GAME_LEVEL_SCORE) * GAME_FALL_SPEED_STEP_PER_LEVEL;
            if (fallSpeed < GAME_FAST_FALL_SPEED) {
                fallSpeed = GAME_FAST_FALL_SPEED;
            }

            // Remove full rows and updating the score
            score += 10 * GAME_removeFullRows();
            UI_updateScore(score, frame);

            // Generate the next shape
            GAME_generateNextShape();
            UI_updateNShape(nextShape, frame);

            /*
                If the newly generated shape collides with any other block
                that block reached the top row and we can no longer generate the shape
                so the game is over
            */
            if (SHAPE_collide(currentShape, gameBoard)) {
            
                gameOver = 1;
                if (score > highScore) {
                    highScore = score;
                }
                UI_showEndMessageBox(score, highScore, frame);
                return;
            }
        }
    }

    // Update frame
    UI_updateBoard(gameBoard, frame);
}

/*
    This function increases current shape fall speed by GAME_FALL_SPEED_STEP amount
*/
void GAME_increaseSpeed() {
    fallSpeed -= GAME_FALL_SPEED_STEP;
    if (fallSpeed < GAME_FAST_FALL_SPEED) {
        fallSpeed = GAME_FAST_FALL_SPEED;
    }
}

/*
    This function moves down the current shape 1 block and returns 0 if it can be moved down
    otherwise 1 will be returned
*/
int GAME_moveDown() {
    int collide = 0;
    SHAPE_remove(currentShape, gameBoard);
    SHAPE_translate(currentShape, 0, 1);
    if (SHAPE_collide(currentShape, gameBoard)) {
        SHAPE_translate(currentShape, 0, -1);
        collide = 1;
    }
    SHAPE_add(currentShape, gameBoard);
    return collide;
}

/*  
    This function moves the current shape to the left by 1 block if the current shape can move to the left
*/
void GAME_moveLeft() {
    SHAPE_remove(currentShape, gameBoard);
    SHAPE_translate(currentShape, -1, 0);
    if (SHAPE_collide(currentShape, gameBoard)) {
        SHAPE_translate(currentShape, 1, 0);
    }
    SHAPE_add(currentShape, gameBoard);
}

/*
    This function moves the current shape to the right by 1 block if the current shape can move to the right
*/
void GAME_moveRight() {
    SHAPE_remove(currentShape, gameBoard);
    SHAPE_translate(currentShape, 1, 0);
    if (SHAPE_collide(currentShape, gameBoard)) {
        SHAPE_translate(currentShape, -1, 0);
    }
    SHAPE_add(currentShape, gameBoard);
}

/*
    This function rotates the current shape (times * 90) degrees counter clockwise if the current shape can rotate that much
*/
void GAME_rotateShape(int times) {
    SHAPE_remove(currentShape, gameBoard);
    SHAPE_rotate(currentShape, times);
    if (SHAPE_collide(currentShape, gameBoard)) {
        SHAPE_rotate(currentShape, 4 - times);
    }
    SHAPE_add(currentShape, gameBoard);
}

/*
    This function replaces the current shape with the next shape and generates a new next shape randomly
*/
void GAME_generateNextShape() {
    SHAPE_CPY(currentShape, nextShape);
    SHAPE_getShape(nextShape, randint(0, SHAPE_COUNT));
}

/*
    This function will remove the full rows and will shift down other blocks. it returns the numbers of full rows removed
*/
int GAME_removeFullRows() {
    int cntFullRows = 0;
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        //  Checking it the ith row is full
        int full = 1; 
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (gameBoard[i][j] != '#') {
                full = 0;
                break;
            }
        }

        /*
            Shifting down the ith row
            This will also shift full rows, but they will be replaced later by the rows above.
        */
        for (int j = 0; j < BOARD_WIDTH; j++) {
            gameBoard[i + cntFullRows][j] = gameBoard[i][j];
            if (full || cntFullRows) {
                gameBoard[i][j] = ' ';
            }
        }
        
        if (full) {
            cntFullRows++;
        }
    }
    return cntFullRows;
}