CC=gcc
CFLAGS = -I.
DEPS = settings.h IO/io.h IO/utils.h UI/utils.h UI/game.h UI/menu.h GAME/game.h GAME/shape.h GAME/utils.h MENU/menu.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

project: IO/io.o IO/utils.o UI/utils.o UI/game.o UI/menu.o GAME/game.o GAME/shape.o GAME/utils.o MENU/menu.o main.o
	$(CC) -o game.exe IO/io.o IO/utils.o UI/utils.o UI/game.o UI/menu.o GAME/game.o GAME/shape.o GAME/utils.o MENU/menu.o main.o