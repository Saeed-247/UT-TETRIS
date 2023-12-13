#if !defined(GAME_GAME_H)
#define GAME_GAME_H

void GAME_start(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt, int reset);
void GAME_update(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt);
void GAME_fixedUpdate(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt);
void GAME_increaseSpeed();
void GAME_moveRight();
void GAME_moveLeft();
int GAME_moveDown();
void GAME_rotateShape(int times);
void GAME_generateNextShape();
int GAME_removeFullRows();
void GAME_over();

#endif // GAME_GAME_H
