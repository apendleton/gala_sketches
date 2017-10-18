#include <ShiftRegister74HC595.h>
#include "fluo_types.h"

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr[5] = {
    ShiftRegister74HC595 (4, 6, 1, 2),
    ShiftRegister74HC595 (4, 5, 1, 2),
    ShiftRegister74HC595 (4, 4, 1, 2),
    ShiftRegister74HC595 (4, 3, 1, 2),
    ShiftRegister74HC595 (4, 0, 1, 2)
};

uint8_t sr_map[12][12] = {
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4 },
    { 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 0, 4 },
    { 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4 },
    { 4, 0, 0, 4, 4, 4, 4, 4, 0, 4, 4, 0 },
    { 4, 4, 0, 4, 4, 0, 0, 0, 4, 4, 4, 4 },
    { 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
    { 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
    { 4, 4, 4, 4, 4, 0, 0, 4, 4, 4, 4, 4 },
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 4 },
    { 4, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 4 },
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4 },
    { 4, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 4 }
};

uint8_t pin_map[12][12] = {
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0 },
    { 0,  0,  0,  0,  0,  0, 23,  0,  0,  0, 31,  0 },
    { 0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 0, 19, 17,  0,  0,  0,  0,  0, 29,  0,  0, 28 },
    { 0,  0, 18,  0,  0, 20, 21, 22,  0,  0,  0,  0 },
    { 0,  0,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  6,  7,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 26, 27,  0 },
    { 0,  0,  0,  2,  4,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25,  0 },
    { 0, +0,  1,  0,  0,  0,  0,  0,  0, 15, 24,  0 }
};

void setup() {
}

inline void setLight(uint8_t row, uint8_t col, bool state) {
    // this should look like this:
    // sr[sr_map[row][col]].set(pin_map[row][col], state);

    // but for now we're ignoring everything except the first board because of the clock pin stuff, so it's like:
    if (sr_map[row][col] == 0) sr[sr_map[row][col]].set(pin_map[row][col], state);
}

void setAll(bool state) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            setLight(i, j, state);
        }
    }
}

void setAllHigh() {
    for (int i = 0; i < 5; i++) {
        sr[i].setAllHigh(); // set all pins LOW
    }
}

void setAllLow() {
    for (int i = 0; i < 5; i++) {
        sr[i].setAllLow(); // set all pins LOW
    }
}

