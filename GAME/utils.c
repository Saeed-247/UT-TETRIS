#include <stdlib.h>
#include <time.h>

#include "settings.h"
#include "utils.h"

int randint(int min, int max) {
    return min + (rand() % (max - min));
}