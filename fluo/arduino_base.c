#include <ShiftRegister74HC595.h>
#include "fluo_types.h"

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr[5] = {
    ShiftRegister74HC595 (3, 48, 49, 50),
    ShiftRegister74HC595 (5, 51, 52, 53),
    ShiftRegister74HC595 (5, 42, 43, 44),
    ShiftRegister74HC595 (3, 36, 37, 38),
    ShiftRegister74HC595 (4, 30, 31, 32)
};

uint8_t sr_map[12][12] = {
    {  4,  1,  1,  1,  4,  4,  4,  2,  0,  0,  3,  0 },
    {  4,  1,  1,  3,  3,  4,  4,  2,  0,  3,  3,  0 },
    {  2,  2,  3,  3,  3,  4,  4,  2,  3,  3,  2,  4 },
    {  3,  1,  1,  3,  2,  4,  4,  2,  2,  2,  4,  4 },
    {  1,  1,  1,  1,  2,  2,  4,  2,  0,  0,  2,  2 },
    {  2,  2,  1,  1,  3,  3,  0,  2,  3,  0,  0,  2 },
    {  2,  2,  2,  1,  1,  3,  0,  3,  3,  0,  0,  0 },
    {  1,  1,  1,  1,  1,  1,  0,  3,  0,  0,  0,  4 },
    {  4,  4,  4,  2,  2,  1,  0,  3,  3,  0,  4,  4 },
    {  1,  4,  2,  1,  1,  1,  2,  2,  3,  4,  2,  2 },
    {  4,  2,  1,  1,  1,  1,  2,  2,  4,  4,  0,  2 },
    {  2,  1,  1,  1,  1,  1,  2,  2,  4,  4,  3,  0 }
};

uint8_t pin_map[12][12] = {
    {  6, 29, 30, 31, 16, 17, 13, 23, 23, 21, 19, 16 },
    {  1, 28, 33, 13, 10, 22, 23, 22, 22, 23, 20, 18 },
    { 10, 11,  9, 15, 11, 18, 20, 19, 22, 21, 38,  8 },
    {  8, 26, 39, 14, 17, 11, 19, 35, 39, 36, 14,  9 },
    { 24, 25, 38, 36, 18, 16, 21, 21, 19, 17, 32, 37 },
    {  9, 13, 37, 35, 17, 18,  6, 20,  5,  7,  4, 33 },
    {  8, 14, 15, 34, 23, 16,  5,  4,  3,  2,  9,  8 },
    { 20, 21, 22, 19, 18, 15,  3,  6,  1, 11, 12, 28 },
    {  3,  5,  4,  5,  3, 14,  0,  7,  2, 10, 29, 27 },
    { 32,  7,  4,  4, 12, 13, 31, 29,  1, 31, 34,  6 },
    {  2,  2,  6, 16, 10, 11, 30, 26, 30, 24, 15, 25 },
    {  0,  1,  0, 17,  8,  9, 28, 27, 26, 25,  0, 13 }
};

inline void setLight(uint8_t row, uint8_t col, bool state) {
    // this should look like this:
    if (sr_map[row][col] <= 4) {
        sr[sr_map[row][col]].set(pin_map[row][col], state);
    }

    // but for now we're ignoring everything except the first board because of the clock pin stuff, so it's like:
    // if (sr_map[row][col] == 0) sr[sr_map[row][col]].set(pin_map[row][col], state);
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

void setup() {
    setAllLow();
    sr[4].set(0, HIGH);
}
