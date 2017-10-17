#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define HIGH 1
#define LOW 0

#define true 1
#define false 0

#define delay(x) usleep(1000*x)

void setLight(uint8_t row, uint8_t col, uint8_t state) {
    printf("\033[%d;%dH%s\n", row + 2, (col * 2) + 2, state ? "\u2588\u2588" : "  ");
}

void setAll(uint8_t state) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            setLight(i, j, state);
        }
    }
}

void setAllHigh() {
    setAll(HIGH);
}

void setAllLow() {
    setAll(LOW);
}

int _random(int min, int max) {
    return (rand() % (max - min)) + min;
}

#define _random(a) _random(0, a)

void shuffle (uint8_t* array, int arrayLength) {
    int currentIndex = arrayLength, temporaryValue, randomIndex;

    // While there remain elements to shuffle...
    while (0 != currentIndex) {

        // Pick a remaining element...
        randomIndex = _random(currentIndex);
        currentIndex -= 1;

        // And swap it with the current element.
        temporaryValue = array[currentIndex];
        array[currentIndex] = array[randomIndex];
        array[randomIndex] = temporaryValue;
    }
}

void drawBox() {
    // clear
    printf("\e[1;1H\e[2J");
    printf("\e[?25l");

    // draw box
    printf("\u250c");
    for (int i = 0; i < 24; i++) {
        printf("\u2500");
    }
    printf("\u2510\n");

    for (int j = 0; j < 12; j++) {
        printf("\u2502");
        for (int i = 0; i < 24; i++) {
            printf(" ");
        }
        printf("\u2502\n");
    }

    printf("\u2514");
    for (int i = 0; i < 24; i++) {
        printf("\u2500");
    }
    printf("\u2518\n");
}