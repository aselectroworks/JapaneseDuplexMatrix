#include "DuplexMatrix.h"
#include "OneButton.h"

DuplexMatrix::DuplexMatrix(int8_t colPins[], int8_t rowPins[], int8_t numCols, int8_t numRows) {
    this->colPins = colPins;
    this->rowPins = rowPins;
    this->numCols = numCols;
    this->numRows = numRows;
    this->keyMatrix = NULL;

#ifdef DUPLEXMATRIX_DEBUG
    DEBUG_PRINTER.begin(115200);
#endif
    DEBUG_PRINTLN("Call Contructor");
}

DuplexMatrix::~DuplexMatrix() {}

void DuplexMatrix::begin() {
    // Create the buttons
    keyMatrix = new OneButton[numCols * (numRows * 2)];

    position = (Position_t *)malloc(sizeof(Position_t) * numCols * (numRows * 2));
    for (uint8_t i = 0; i < numRows * 2; i++) {
        for (uint8_t j = 0; j < numCols; j++) {
            position[i * numCols + j].col = j;
            position[i * numCols + j].row = i;
        }
    }
}

void DuplexMatrix::scan() {
    // 1st Half of the matrix scan(Cols to Rows)
    for (uint8_t i = 0; i < numRows; i++) {
        pinMode(rowPins[i], INPUT);
    }
    for (uint8_t i = 0; i < numCols; i++) {
        pinMode(colPins[i], INPUT);
    }
    for (uint8_t i = 0; i < numCols; i++) {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH);
        for (uint8_t j = 0; j < numRows; j++) {
            // Read the button state
            bool buttonState = digitalRead(rowPins[j]) == HIGH;
            // Update the button state
            //DEBUG_PRINTF("Tick Button: %d, x=%2d, y=%2d\r\n", ((2 * j) * numCols) + i, i, 2 * j);
            keyMatrix[((2 * j) * numCols) + i].tick(buttonState);
        }
        pinMode(colPins[i], INPUT);
    }
    // 2nd Half of the matrix scan(Rows to Cols)
    for (uint8_t i = 0; i < numCols; i++) {
        pinMode(colPins[i], INPUT);
    }
    for (uint8_t i = 0; i < numRows; i++) {
        pinMode(rowPins[i], INPUT);
    }
    for (uint8_t i = 0; i < numRows; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
        for (uint8_t j = 0; j < numCols; j++) {
            // Read the button state
            bool buttonState = digitalRead(colPins[j]) == HIGH;
            // Update the button state
            //DEBUG_PRINTF("Tick Button: %d, x=%2d, y=%2d \r\n", ((2 * i + 1) * numCols) + j, j, 2 * i + 1);
            keyMatrix[((2 * i + 1) * numCols) + j].tick(buttonState);
        }
        pinMode(rowPins[i], INPUT);
    }
}

void DuplexMatrix::state(int8_t *states) {
    for (uint8_t i = 0; i < (numRows * 2); i++) {
        for (uint8_t j = 0; j < numCols; j++) {
            states[(i * numCols) + j] = keyMatrix[(i * numCols) + j].state();
        }
    }
#ifdef DUPLEXMATRIX_DEBUG
    Serial.printf("States: ");
    for (uint8_t i = 0; i < (numRows * 2); i++) {
        for (uint8_t j = 0; j < numCols; j++) {
            Serial.printf("%d ", states[(i * numCols) + j]);
        }
    }
    Serial.printf("\r\n");
#endif
    return;
}

int8_t DuplexMatrix::state(int8_t col, int8_t row) { return keyMatrix[(row * numCols) + col].state(); }

// Callbacks
void DuplexMatrix::attachPress(int8_t col, int8_t row, void (*callback)(void *)) {
    keyMatrix[(row * numCols) + col].attachPress(callback, &position[row * numCols + col]);
}
void DuplexMatrix::attachClick(int8_t col, int8_t row, void (*callback)(void *)) {
    keyMatrix[(row * numCols) + col].attachClick(callback, &position[row * numCols + col]);
}
void DuplexMatrix::attachDoubleClick(int8_t col, int8_t row, void (*callback)(void *)) {
    keyMatrix[(row * numCols) + col].attachDoubleClick(callback, &position[row * numCols + col]);
}
void DuplexMatrix::attachMultiClick(int8_t col, int8_t row, void (*callback)(void *)) {
    keyMatrix[(row * numCols) + col].attachMultiClick(callback, &position[row * numCols + col]);
}
void DuplexMatrix::attachLongPressStart(int8_t col, int8_t row, void (*callback)(void *)) {
    keyMatrix[(row * numCols) + col].attachLongPressStart(callback, &position[row * numCols + col]);
}
void DuplexMatrix::attachLongPressStop(int8_t col, int8_t row, void (*callback)(void *)) {
    keyMatrix[(row * numCols) + col].attachLongPressStop(callback, &position[row * numCols + col]);
}
void DuplexMatrix::attachDuringLongPress(int8_t col, int8_t row, void (*callback)(void *)) {
    keyMatrix[(row * numCols) + col].attachDuringLongPress(callback, &position[row * numCols + col]);
}
void DuplexMatrix::attachIdle(int8_t col, int8_t row, void (*callback)(void)) {
    keyMatrix[(row * numCols) + col].attachIdle(callback);
}