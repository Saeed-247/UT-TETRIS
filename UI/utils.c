#include <string.h>
#include <math.h>

#include "settings.h"
#include "utils.h"

void UI_rightAlignText(const char* text, char * buffer, int size , int padding) {
    int i = 0;
    for (; i < padding && i < size; i++) {
        *(buffer + i) = ' ';
    }
    for (; i < size && text[i - padding]; i++) {
        *(buffer + i) = text[i - padding];
    }
    for (; i < size; i++) {
        *(buffer + i) = ' ';
    }
}

void UI_centerAlignText(const char* text, char * buffer, int size) {
    int text_size = strlen(text);
    int right_padding = (size - text_size) / 2;
    if (right_padding < 0)
        right_padding = 0;
    UI_rightAlignText(text, buffer, size, right_padding);
}

void UI_drawBorder(char frame[FRAME_HEIGHT][FRAME_WIDTH], int x, int y, int w, int h) {
    for (int i = 1; i < w - 1; i++) {
        frame[y][x + i] = frame[y + h - 1][x + i] = '-';
    }
    for (int i = 1; i < h - 1; i++) {
        frame[y + i][x] = frame[y + i][x + w - 1] = '|';
    }
    frame[y][x] = frame[y][x + w - 1] = frame[y + h - 1][x] = frame[y + h - 1][x + w - 1] = '*';
}