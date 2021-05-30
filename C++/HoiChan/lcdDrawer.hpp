#ifndef LCD_DRAWER_HPP
#define LCD_DRAWER_HPP


#include "lcdLibrary.hpp"
#include "menu.hpp"

#include <cstddef>

using std::byte;

enum ActionType { Up, Down, Nth};

class lcdDrawer {
    private:
        LiquidCrystal* lcd;

        byte upArrow[8];
        byte downArrow[8];

        void drawDownArrow();
        void drawUpArrow();

        void drawCurrentMenuItem(const Menu& menu);
        void drawNextMenuItem(const Menu& menu);

        void indicateCurrentMenuPosition(const Menu& menu);
    public:
        lcdDrawer(int pinNumRS, int pinNumEnable, int pinNumD4, int pinNumD5,
                   int pinNumD6, int pinNumD7, byte upArrow[8], byte downArrow[8]);

        void drawLCD(const Menu& menu);

        void defineArrow(const byte arrowSource[8], ActionType action);
};

#endif