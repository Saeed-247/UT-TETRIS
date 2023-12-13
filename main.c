#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "settings.h"
#include "IO/io.h"
#include "UI/game.h"
#include "GAME/game.h"
#include "MENU/menu.h"

#define TIME_PER_FRAME (1000 / FPS)

extern int escaped;
extern int gameOver;
extern int state;

char frame[FRAME_HEIGHT][FRAME_WIDTH];
long cntFixedUpdate = 0;

/*
    This function is called at the begging of the game
*/
void start() {
    IO_init();
    
    MENU_start(frame, cntFixedUpdate, gameOver);
}

/*
    This function is called once per loop cycle
*/
void update() {
    IO_updateInput();

    if (state == 0) {
        MENU_update(frame, cntFixedUpdate);
    }
    else if (state == 1) {
        GAME_update(frame, cntFixedUpdate);
    }
}

/*
    This function is called once per frame
*/
void fixedUpdate() {
    if (state == 0) {
        MENU_fixedUpdate(frame, cntFixedUpdate);
    }
    else if (state == 1) {
        GAME_fixedUpdate(frame, cntFixedUpdate);
    }

    IO_render(frame);
    // render
}

/*
    Main game loop
*/
int main() {
    srand(time(0)); // This is used later to generate random shapes

    double lastFixedUpdateTime = 0;
    clock_t clockStart = clock();

    start();

    while (!escaped) {
        update();

        double timeSinceLastFrame = ((double)clock() - lastFixedUpdateTime) / CLOCKS_PER_SEC * 1000;
        if (timeSinceLastFrame >= TIME_PER_FRAME) {
            lastFixedUpdateTime = (double)clock();
            cntFixedUpdate++;
            fixedUpdate();
        }
    }

    clock_t clockEnd = clock();
    double totalSeconds = (double)(clockEnd - clockStart) / CLOCKS_PER_SEC;

    #if defined(DEBUG)
    
    // TODO add debug info
    
    #endif // DEBUG

    return 0;
}