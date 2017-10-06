#include <ShiftRegister74HC595.h>

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

void loop() {

  //  sr.setAllHigh(); // set all pins HIGH
  //  delay(500);

  for (int i = 0; i < 5; i++) {
    sr[i].setAllLow(); // set all pins LOW
  }  
  delay(350);

  rowByRow();
}

void oneByOne() {
  for (int row = 0; row < 12; row++) {
    for (int col = 0; col < 12; col++) {
      setLight(row, col, HIGH); // set single pin HIGH
      delay(200); 
    }
  }
}

void rowByRow() {
  for (int rowToLight = 0; rowToLight < 12; rowToLight++) {
    for (int row = 0; row < 12; row++) {
      for (int col = 0; col < 12; col++) {
        setLight(row, col, row == rowToLight ? HIGH : LOW); // set single pin HIGH
      }
    }
    delay(200); 
  }
}

void colByCol() {
  for (int colToLight = 0; colToLight < 12; colToLight++) {
    for (int row = 0; row < 12; row++) {
      for (int col = 0; col < 12; col++) {
        setLight(row, col, col == colToLight ? HIGH : LOW); // set single pin HIGH
      }
    }
    delay(200); 
  }
}

void colBounce() {
  while (true) {
    for (int colToLight = 0; colToLight < 12; colToLight++) {
      for (int row = 0; row < 12; row++) {
        for (int col = 0; col < 12; col++) {
          setLight(row, col, col == colToLight ? HIGH : LOW); // set single pin HIGH
        }
      }
      delay(200); 
    }
    for (int colToLight = 10; colToLight > 0; colToLight--) {
      for (int row = 0; row < 12; row++) {
        for (int col = 0; col < 12; col++) {
          setLight(row, col, col == colToLight ? HIGH : LOW); // set single pin HIGH
        }
      }
      delay(200); 
    }
  }
}