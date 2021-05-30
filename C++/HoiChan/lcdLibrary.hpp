#ifndef LCD_LIBRARY_HPP
#define LCD_LIBRARY_HPP

#include <string>
#include <cstddef>


//  ----------------------------------------------------------------------
//  LCD driver

// All methods here are stubs, replacing real library functionality it's too
// annoying to set up a toolchain for.
// 
struct LiquidCrystal {
    // Sets up the connection between the screen and the microcontroller
    LiquidCrystal (int pinNumRS, int pinNumEnable, int pinNumD4, int pinNumD5,
                   int pinNumD6, int pinNumD7) {
        (void)pinNumRS; (void)pinNumEnable; (void)pinNumD4; (void)pinNumD5;
        (void)pinNumD6; (void)pinNumD7;
    }

    // Clears the LCD screen and positions the cursor in the upper-left corner.
    void clear () {}

    // Initializes the interface to the LCD screen, and specifies the dimensions
    // (width and height) of the display.
    // begin() needs to be called before any other LCD library commands.
    void begin (int cols, int rows) {
        (void)cols; (void)rows;
    }

    // Position the LCD cursor; that is, set the location at which subsequent
    // text written to the LCD will be displayed.
    void setCursor (int col, int row) {
        (void)col; (void)row;
    }

    // Prints text to the LCD.
    void print (const std::string &str) {
        (void)str;
    }

    // Write a character to the LCD.
    void write (std::byte num) {
        (void)num;
    }

    // Create a custom character (glyph) for use on the LCD.
    void createChar (std::byte num, const std::byte data[8]) {
        (void)num; (void)data;
    }
};


//  ----------------------------------------------------------------------
//  Maths (ish)

inline int round (float x) {
    if (x >= 0) {
        return static_cast<int> (x + 0.5);
    } else {
        return static_cast<int> (x - 0.5);
    }
}

template <typename T>
inline T constrain (T val, T low, T high) {
    if (val < low) {
        return low;
    } else
    if (val < high) {
        return val;
    } else {
        return high;
    }
}


//  ----------------------------------------------------------------------
//  Hardware interaction

// Reads voltage off a microcontroller pin.
// Again, stub function.
inline int analogRead (int pinNum) {
    (void)pinNum;
    return -1;
}

#endif
