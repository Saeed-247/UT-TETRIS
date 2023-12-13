#include "IO/utils.h"

char IO_toUpper(char x) {
    if (x > 96)
        x -= 32;
    return x;
}