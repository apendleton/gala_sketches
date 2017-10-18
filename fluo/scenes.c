#include <time.h>

void bars(uint16_t duration) {
    time_t t = time(NULL);

    setAllLow();

    uint8_t current = 0;

    while (true) {
        if (time(NULL) - t > duration) return;

        if (current < 6) {
            for (uint8_t i = 0; i < 12; i++) {
                setLight(current * 2, i, HIGH);
            }
        } else if (current >= 60) {
            current = 7;
        }

        current += 1;

        delay(2000);
    }
}

void snake(uint16_t duration) {
    time_t t = time(NULL);

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
        if (time(NULL) - t > duration) return;

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

void randomFade(uint16_t duration, uint16_t topHold) {
    time_t t = time(NULL);

    setAllLow();

    uint8_t pixels[144];
    for (uint8_t i = 0; i < 144; i++) pixels[i] = i;

    uint8_t current = 0;
    uint8_t direction = LOW;
    while (true) {
        if (time(NULL) - t > duration) return;

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

void drops(uint16_t duration) {
    time_t t = time(NULL);

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
        if (time(NULL) - t > duration) return;

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

void spokes(uint16_t duration, uint8_t invert) {
    time_t t = time(NULL);

    int8_t state = invert ? LOW : HIGH;
    setAll(!state);

    int8_t i = 0;
    int8_t entries[] = {0, 8, 16};
    while (true) {
        if (time(NULL) - t > duration) return;

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