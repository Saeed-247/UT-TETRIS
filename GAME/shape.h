#if !defined(GAME_SHAPE_H)
#define GAME_SHAPE_H

/*
    Each shape is defined as a set of coordinate points
    The first point in each shape is the coordinates of the next point relative to the rotation pivot of the shape
    The rest of the points are the coordinate shape blocks on the game board
*/
typedef float Point[2];
typedef float Shape[1 + SHAPE_BLOCK_COUNT][2];

void SHAPE_translate(Shape, float, float);
void SHAPE_rotatePoint(Point);
void SHAPE_rotate(Shape, int);
void SHAPE_remove(Shape, char[BOARD_HEIGHT][BOARD_WIDTH]);
void SHAPE_add(Shape, char[BOARD_HEIGHT][BOARD_WIDTH]);
int SHAPE_collide(Shape, char[BOARD_HEIGHT][BOARD_WIDTH]);
void SHAPE_CPY(Shape, Shape);
void SHAPE_getShape(Shape, int);

#endif // GAME_SHAPE_H
