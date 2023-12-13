#if !defined(IO_H)
#define IO_H

void IO_init();

void IO_updateInput();

char IO_getInput();

void IO_render(char frame[FRAME_HEIGHT][FRAME_WIDTH]);

#endif // IO_H
