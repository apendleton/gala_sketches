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
    {  3,  1,  1,  1,  1,  1,  0,  3,  0,  0,  0,  4 },
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
    {  9, 13, 37, 35, 17, 16,  6, 20,  5,  7,  4, 33 },
    {  8, 14, 15, 34, 23, 18,  5,  4,  3,  2,  9,  8 },
    { 12, 21, 22, 19, 18, 15,  3,  6,  1, 11, 12, 28 },
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

    pinMode(2,INPUT_PULLUP);
    int flashMode = !(digitalRead(2));
    if (flashMode) {
        while (1) {
            setAllHigh();
            delay(1000);
            setAllLow();
            delay(1000);
        }
    }
}

void shuffle (uint8_t* array, int arrayLength) {
    int currentIndex = arrayLength, temporaryValue, randomIndex;

    // While there remain elements to shuffle...
    while (0 != currentIndex) {

        // Pick a remaining element...
        randomIndex = random(currentIndex);
        currentIndex -= 1;

        // And swap it with the current element.
        temporaryValue = array[currentIndex];
        array[currentIndex] = array[randomIndex];
        array[randomIndex] = temporaryValue;
    }
}
void bars(uint32_t _duration) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    setAllLow();

    for (uint8_t row = 0; row < 12; row+=2) {
        for (uint8_t i = 0; i < 12; i++) {
            setLight(row, i, HIGH);
        }
        delay(2000);
    }

    while (true) {
        if (millis() - t > duration) return;
        delay(100);
    }
}

void bars_sides(uint32_t _duration) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    setAllLow();

    for (uint8_t col = 0; col < 12; col++) {
        for (uint8_t row = 0; row < 12; row+=2) {
            uint8_t actual_col = (row % 4 == 0) ? col : (11 - col);
            setLight(row, actual_col, HIGH);
        }
        delay(1000);
    }

    while (true) {
        if (millis() - t > duration) return;
        delay(100);
    }
}

void bars_diag(uint32_t _duration) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    setAllLow();

    for (int8_t first_col = 0; first_col < 12; first_col++) {
        for (uint8_t row = 0; row < 12; row+=2) {
            int8_t col = first_col - row;
            if (col >= 0 && col <= 11) {
                setLight(row, (uint8_t)col, HIGH);
            }
            int8_t a_col = 21 - (first_col + row);
            if (a_col >= 0 && a_col <= 11) {
                setLight(row, (uint8_t)a_col, HIGH);
            }
        }
        delay(1000);
    }

    while (true) {
        if (millis() - t > duration) return;
        delay(100);
    }
}

void bars_crosswalk(uint32_t _duration) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    for (int8_t front_col = 0; front_col < 12; front_col++) {
        setAllLow();
        for (int8_t row = 0; row < 12; row+=2) {
            for (int8_t col = front_col; col >= 0; col -= 2) {
                setLight(row, col, HIGH);
            }
        }
        delay(250);
    }
    for (int8_t front_row = 11; front_row >= 0; front_row--) {
        for (int8_t col = 0; col < 12; col+=2) {
            for (int8_t row = front_row; row < 12; row += 2) {
                if (row < 11) setLight(row + 1, col, LOW);
                setLight(row, col, HIGH);
            }
        }
        delay(250);
    }

    while (true) {
        if (millis() - t > duration) return;
        delay(100);
    }
}

void snake(uint32_t _duration) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    setAllLow();

    uint8_t LENGTH = 6;
    uint8_t HEAD = LENGTH - 1;
    uint8_t TAIL = 0;

    uint8_t bodyRows[6];
    uint8_t bodyCols[6];

    for (uint8_t i = 0; i < LENGTH; i++) {
        bodyCols[i] = i;
        bodyRows[i] = 0;
        setLight(0, i, HIGH);
    }

    uint8_t nextRows[4];
    uint8_t nextCols[4];
    uint8_t count = 0;
    while (true) {
        if (millis() - t > duration) return;

        count = 0;

        if (bodyRows[HEAD] > 0 && bodyRows[HEAD - 1] != bodyRows[HEAD] - 1) {
            nextRows[count] = bodyRows[HEAD] - 1;
            nextCols[count] = bodyCols[HEAD];
            count++;
        }

        if (bodyRows[HEAD] < 11 && bodyRows[HEAD - 1] != bodyRows[HEAD] + 1) {
            nextRows[count] = bodyRows[HEAD] + 1;
            nextCols[count] = bodyCols[HEAD];
            count++;
        }

        if (bodyCols[HEAD] > 0 && bodyCols[HEAD - 1] != bodyCols[HEAD] - 1) {
            nextRows[count] = bodyRows[HEAD];
            nextCols[count] = bodyCols[HEAD] - 1;
            count++;
        }

        if (bodyCols[HEAD] < 11 && bodyCols[HEAD - 1] != bodyCols[HEAD] + 1) {
            nextRows[count] = bodyRows[HEAD];
            nextCols[count] = bodyCols[HEAD] + 1;
            count++;
        }

        uint8_t pick = random(count);
        uint8_t tailRow = bodyRows[TAIL];
        uint8_t tailCol = bodyCols[TAIL];
        for (uint8_t i = 0; i < LENGTH - 1; i++) {
            bodyRows[i] = bodyRows[i + 1];
            bodyCols[i] = bodyCols[i + 1];
        }
        bodyRows[HEAD] = nextRows[pick];
        bodyCols[HEAD] = nextCols[pick];
        setLight(bodyRows[HEAD], bodyCols[HEAD], HIGH);

        uint8_t doubleTail = false;
        for (uint8_t i = 0; i < LENGTH; i++) {
            doubleTail = doubleTail || (tailRow == bodyRows[i] && tailCol == bodyCols[i]);
        }
        if (!doubleTail) {
            setLight(tailRow, tailCol, LOW);
        }

        delay(200);
    }
}

void randomFade(uint32_t _duration, uint16_t topHold) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    setAllLow();

    uint8_t pixels[144];
    for (uint8_t i = 0; i < 144; i++) pixels[i] = i;

    uint8_t current = 0;
    uint8_t direction = LOW;
    while (true) {
        if (millis() - t > duration) return;

        if (current == 0) {
            if (direction) delay(topHold*1000);
            direction = direction == LOW ? HIGH : LOW;
            shuffle(pixels, 144);
        }
        uint8_t row = pixels[current] % 12;
        uint8_t col = (pixels[current] - row) / 12;
        setLight(row, col, direction);

        current = (current + 1) % 144;

        delay(100);
    }
}

void drops(uint32_t _duration) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    setAllLow();

    int8_t levels[12];
    int8_t active[12];
    int8_t activeCount = 12;
    for (int8_t i = 0; i < 12; i++) {
        levels[i] = 0;
        active[i] = i;
    }

    int8_t currentCol = -1;
    int8_t currentHeight = -1;
    int8_t target = -1;
    int8_t pick;
    int8_t direction = 1;

    while (true) {
        if (millis() - t > duration) return;

        if (currentHeight == target) {
            if (currentCol != -1) {
                levels[currentCol] += 1;
                if (levels[currentCol] == 12) {
                    int8_t tmp = active[pick];
                    active[pick] = active[activeCount - 1];
                    active[activeCount - 1] = tmp;
                    activeCount--;

                    if (activeCount == 0) {
                        activeCount = 12;
                        direction = (direction == 1 ? -1 : 1);
                        for (int8_t i = 0; i < 12; i++) {
                            levels[i] = 0;
                        }
                    }
                }
            }


            pick = random(activeCount);
            currentCol = active[pick];

            if (direction == 1) {
                currentHeight = 0;
                target = 12 - levels[currentCol];
            } else {
                currentHeight = (12 - levels[currentCol]);
                target = 13;
            }
        }

        if (currentHeight < 12) setLight(currentHeight, currentCol, HIGH);
        if (currentHeight > 0) setLight(currentHeight - 1, currentCol, LOW);
        currentHeight += 1;

        delay(25);
    }
}

orderedPair switchToOctantZeroFrom(uint8_t octant, int8_t x, int8_t y) {
    orderedPair out;
    switch(octant) {
        case 0: out = (orderedPair){x, y}; break;
        case 1: out = (orderedPair){y, x}; break;
        case 6: out = (orderedPair){-y, x}; break;
        case 7: out = (orderedPair){x, -y}; break;
    }
    return out;
}

orderedPair switchFromOctantZeroTo(uint8_t octant, int8_t x, int8_t y) {
    orderedPair out;
    switch(octant) {
        case 0: out = (orderedPair){x, y}; break;
        case 1: out = (orderedPair){y, x}; break;
        case 6: out = (orderedPair){y, -x}; break;
        case 7: out = (orderedPair){x, -y}; break;
    }
    return out;
}

void plotLine(int8_t _x0, int8_t _y0, int8_t _x1, int8_t _y1, int8_t state) {
    if (_x0 > _x1) {
        int8_t tmp = _x0;
        _x0 = _x1;
        _x1 = tmp;
        tmp = _y0;
        _y0 = _y1;
        _y1 = tmp;
    }

    int8_t _dx = _x1 - _x0;
    int8_t _dy = _y1 - _y0;

    int8_t octant;
    if (_dy >= 0) {
        if (_dx >= abs(_dy)) octant = 0;
        else octant = 1;
    } else {
        if (_dx <= abs(_dy)) octant = 6;
        else octant = 7;
    }

    orderedPair coords0 = switchToOctantZeroFrom(octant, _x0, _y0);
    int8_t x0 = coords0.x;
    int8_t y0 = coords0.y;

    orderedPair coords1 = switchToOctantZeroFrom(octant, _x1, _y1);
    int8_t x1 = coords1.x;
    int8_t y1 = coords1.y;

    int8_t dx = x1 - x0;
    int8_t dy = y1 - y0;
    int8_t D = 2 * dy - dx;
    int8_t y = y0;

    for (int8_t x = x0; (x0 <= x1 ? x <= x1 : x >= x1); x += (x0 > x1 ? -1 : 1)) {
        orderedPair rc = switchFromOctantZeroTo(octant, x, y);
        if (rc.x >= 0 && rc.x < 12 && rc.y >= 0 && rc.y < 12) setLight(rc.x, rc.y, state);
        if (D > 0) {
            y = y + 1;
            D = D - (2*dx);
        }
        D = D + (2*dy);
    }
}

void spokes(uint32_t _duration, uint8_t invert) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    int8_t state = invert ? LOW : HIGH;
    setAll(!state);

    int8_t i = 0;
    int8_t entries[] = {0, 8, 16};
    while (true) {
        if (millis() - t > duration) return;

        setAll(!state);
        for (int8_t j = 0; j < 3; j++) {
            int8_t pos = (entries[j] + i) % 23;
            int8_t row, col;
            if (pos < 12) {
                row = 0;
                col = pos;
            } else {
                row = pos - 11;
                col = 11;
            }
            plotLine(11, 0, row, col, state);
        }

        i = (i + 1) % 23;

        delay(100);
    }
}

void bars_sweep(uint32_t _duration) {
    unsigned long duration = _duration * 1000;
    unsigned long t = millis();

    setAllLow();

    for (int8_t row = 0; row < 12; row+=2) {
        for (int8_t low_row = 11; low_row >= row; low_row--) {
            for (uint8_t dark_row = row + 1; dark_row < 12; dark_row++) {
                for (uint8_t col = 0; col < 12; col++) {
                    setLight(dark_row, col, LOW);
                }
            }
            plotLine(row, 0, low_row, 11, HIGH);
            delay(150);
        }
    }

    while (true) {
        if (millis() - t > duration) return;
        delay(100);
    }
}
void loop() {
    drops(50);

    bars_sweep(30);
    randomFade(30,2);

    bars_sides(30);
    spokes(15, true);

    bars_diag(30);
    snake(30);

    bars_crosswalk(25);

    setAllLow();
    delay(30 * 1000);
    delay(30 * 1000);
}