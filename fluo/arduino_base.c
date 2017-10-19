#include <ShiftRegister74HC595.h>
#include "fluo_types.h"

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr[5] = {
    ShiftRegister74HC595 (5, 48, 49, 50),
    ShiftRegister74HC595 (5, 51, 52, 53),
    ShiftRegister74HC595 (3, 42, 43, 44),
    ShiftRegister74HC595 (3, 36, 37, 38),
    ShiftRegister74HC595 (4, 30, 31, 32)
};

uint8_t sr_map[12][12] = {
    {  3,  2,  3,  0,  0,  0,  0,  0,  0,  0,  4,  2 },
    {  0,  0,  0,  0,  0,  3,  4,  0,  0,  0,  4,  2 },
    {  0,  0,  0,  4,  3,  0,  0,  0,  2,  3,  3,  3 },
    {  3,  4,  4,  0,  0,  0,  0,  0,  4,  2,  3,  4 },
    {  3,  2,  4,  0,  0,  4,  4,  4,  1,  1,  2,  1 },
    {  3,  2,  4,  0,  1,  1,  1,  1,  1,  1,  2,  1 },
    {  2,  2,  4,  0,  1,  2,  2,  1,  1,  1,  1,  3 },
    {  0,  0,  0,  0,  2,  4,  4,  1,  1,  1,  1,  3 },
    {  0,  0,  0,  2,  3,  3,  1,  1,  1,  4,  4,  1 },
    {  0,  0,  2,  4,  4,  1,  1,  3,  2,  2,  2,  1 },
    {  0,  2,  3,  3,  1,  1,  1,  3,  2,  3,  4,  1 },
    {  2,  4,  4,  1,  1,  1,  1,  3,  2,  4,  4,  1 }
};

uint8_t pin_map[12][12] = {
    { 22,  9, 23, 24, 17, 18, 19, 20, 21, 22, 30, 11 },
    { 30, 28, 26, 25, 16,  1, 23, 15, 14, 23, 31, 12 },
    { 31, 29, 27, 16,  0, 11, 12, 13, 10,  2,  3,  4 },
    { 21, 19, 17,  2,  1, 10,  9,  8, 29, 13,  5, 28 },
    { 20,  7, 18,  3,  0, 20, 21, 22, 25, 24, 14, 34 },
    { 19,  6,  3,  4, 30, 29, 28, 27, 26,  5, 15, 35 },
    {  5,  4,  5,  5, 31, 17, 18,  7,  6,  4,  3,  6 },
    { 38, 39,  7,  6, 16,  6,  7, 14,  0,  1,  2,  7 },
    { 35, 36, 37,  3,  9, 10, 12, 13, 15, 26, 27, 36 },
    { 33, 34,  2,  2,  4,  9, 11, 11, 19, 22, 23, 37 },
    { 32,  1, 14, 15, 22,  8, 10, 12, 20,  8, 25, 38 },
    {  0,  0,  1, 23, 21, 20, 19, 13, 21, 15, 24, 39 },
};

void setup() {
}

inline void setLight(uint8_t row, uint8_t col, bool state) {
    // this should look like this:
    sr[sr_map[row][col]].set(pin_map[row][col], state);

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

