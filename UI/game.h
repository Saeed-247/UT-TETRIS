#if !defined(UI_GAME_H)
#define UI_GAME_H

#include "GAME/shape.h"

void UI_initGame(char frame[FRAME_HEIGHT][FRAME_WIDTH]);

void UI_updateBoard(char board[BOARD_HEIGHT][BOARD_WIDTH], char frame[FRAME_HEIGHT][FRAME_WIDTH]);

void UI_updateScore(int score, char frame[FRAME_HEIGHT][FRAME_WIDTH]);

void UI_updateNShape(Shape nextShape, char frame[FRAME_HEIGHT][FRAME_WIDTH]);

void UI_showEndMessageBox(int score, int highScore, char frame[FRAME_HEIGHT][FRAME_WIDTH]);

#endif // UI_GAME_H
