#include <string.h>

#include "settings.h"
#include "shape.h"

// A list of all available shapes
static float shapeList[SHAPE_COUNT][SHAPE_BLOCK_COUNT + 1][2] = SHAPE_LIST;

void SHAPE_translate(Shape shape, float x, float y) {
    for (int i = 1; i <= SHAPE_BLOCK_COUNT; i++) {
        shape[i][0] += x;
        shape[i][1] += y;
    }
}

/*
    This function rotates the input point 90 degrees counterclockwise around the origin
*/
void SHAPE_rotatePoint(Point p) {
    float temp = p[1];
    p[1] = -p[0];
    p[0] = temp;
}

/*
    This function rotates the given shape (times x 90) degrees counterclockwise around the shape rotation pivot
*/
void SHAPE_rotate(Shape shape, int times) {
    // First, we translate shape such that pivot coordinates become (0, 0)
    float xt = shape[0][0] + shape[1][0];
    float yt = shape[0][1] + shape[1][1];
    SHAPE_translate(shape, -xt, -yt);

    // Rotating each point
    for (int i = 0; i <= SHAPE_BLOCK_COUNT; i++) {
        for (int j = 0; j < times; j++) {
            SHAPE_rotatePoint(shape[i]);
        }
    }

    // Now we translate the rotated shape back to its original position
    SHAPE_translate(shape, xt, yt);
}


void SHAPE_remove(Shape shape, char board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 1; i <= SHAPE_BLOCK_COUNT; i++) {
        board[(int)shape[i][1] - 1][(int)shape[i][0] - 1] = ' ';
    }
}

void SHAPE_add(Shape shape, char board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 1; i <= SHAPE_BLOCK_COUNT; i++) {
        board[(int)shape[i][1] - 1][(int)shape[i][0] - 1] = '#';
    }
}

/*
    This function check if the shape collides with any other block on the game board
    It will return 1 if it collides and 0 if it is otherwise
*/
int SHAPE_collide(Shape shape, char board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 1; i <= SHAPE_BLOCK_COUNT; i++) {
        if (shape[i][0] > BOARD_WIDTH || shape[i][1] > BOARD_HEIGHT || shape[i][0] < 1 || shape[i][1] < 1) {
            return 1;
        }
        if (board[(int)shape[i][1] - 1][(int)shape[i][0] - 1] != ' ') {
            return 1;
        }
    }
    return 0;
}

void SHAPE_CPY(Shape dist, Shape src) {
    for (int i = 0; i <= SHAPE_BLOCK_COUNT; i++) {
        for (int j = 0; j < 2; j++) {
            dist[i][j] = src[i][j];
        }
    }
}

void SHAPE_getShape(Shape shape, int id) {
    SHAPE_CPY(shape, shapeList[id]);
}