#include "sim.c"
#include "scenes.c"

#include "program.c"

int main(int argc, char** argv) {
    drawBox();
    srand(time(NULL));

    loop();

    return 0;
}