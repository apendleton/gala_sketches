#include "sim.c"
#include "lib.c"
#include "fluo_types.h"
#include "scenes.c"
#include "program.c"

int main(int argc, char** argv) {
    drawBox();
    srand(time(NULL));

    while(1) loop();

    return 0;
}