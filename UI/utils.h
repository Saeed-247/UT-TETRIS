#if !defined(UI_UTILS_H)
#define UI_UTILS_H

void UI_rightAlignText(const char*, char *, int, int);

void UI_centerAlignText(const char*, char *, int);

void UI_drawBorder(char frame[FRAME_HEIGHT][FRAME_WIDTH], int x, int y, int w, int h);

#endif // UI_UTILS_H
