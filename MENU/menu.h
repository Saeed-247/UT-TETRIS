#if !defined(MENU_MENU_H)
#define MENU_MENU_H

void MENU_start(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt, int startIndex);
void MENU_update(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt);
void MENU_fixedUpdate(char frame[FRAME_HEIGHT][FRAME_WIDTH], long frameCnt);
void changeState();

#endif // MENU_MENU_H
