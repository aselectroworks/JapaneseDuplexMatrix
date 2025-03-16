#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "OneButton.h"

// Uncomment to enable debug messages
//#define DUPLEXMATRIX_DEBUG

// Define where debug output will be printed
#define DEBUG_PRINTER Serial

// Setup debug printing macros
#ifdef DUPLEXMATRIX_DEBUG
#define DEBUG_PRINT(...)                           \
    {                                              \
        DEBUG_PRINTER.printf("[DuplexMatrix]: "); \
        DEBUG_PRINTER.print(__VA_ARGS__);          \
    }
#define DEBUG_PRINTLN(...)                         \
    {                                              \
        DEBUG_PRINTER.printf("[DuplexMatrix]: "); \
        DEBUG_PRINTER.println(__VA_ARGS__);        \
    }
#define DEBUG_PRINTF(...)                          \
    {                                              \
        DEBUG_PRINTER.printf("[DuplexMatrix]: "); \
        DEBUG_PRINTER.printf(__VA_ARGS__);         \
    }
#else
#define DEBUG_PRINT(...) \
    {}
#define DEBUG_PRINTLN(...) \
    {}
#define DEBUG_PRINTF(...) \
    {}
#endif

class DuplexMatrix
{
    public: 
    DuplexMatrix(int8_t rowPins[], int8_t colPins[], int8_t numRows, int8_t numCols);
    ~DuplexMatrix();
    void begin();
    void scan(); 
    void state(int8_t *states); 
    int8_t state(int8_t col, int8_t row);

    typedef struct {
        int8_t col; 
        int8_t row; 
    } Position_t; 

    void attachPress(int8_t col, int8_t row, void (*callback)(void *));
    void attachClick(int8_t col, int8_t row, void (*callback)(void *));
    void attachDoubleClick(int8_t col, int8_t row, void (*callback)(void *));
    void attachMultiClick(int8_t col, int8_t row, void (*callback)(void *));
    void attachLongPressStart(int8_t col, int8_t row, void (*callback)(void *));
    void attachLongPressStop(int8_t col, int8_t row, void (*callback)(void *));
    void attachDuringLongPress(int8_t col, int8_t row, void (*callback)(void *));
    void attachIdle(int8_t col, int8_t row, void (*callback)(void));

    private: 
    int8_t* rowPins;
    int8_t* colPins;
    int8_t numRows;
    int8_t numCols;

    OneButton *keyMatrix; 
    Position_t *position;
}; 