#include "lcdDrawer.hpp"

lcdDrawer::lcdDrawer(int pinNumRS, int pinNumEnable, int pinNumD4, int pinNumD5,
    int pinNumD6, int pinNumD7, std::byte upArrow[8], std::byte downArrow[8]) {
    
    lcd = new LiquidCrystal(pinNumRS, pinNumEnable, pinNumD4, pinNumD5, pinNumD6, pinNumD7);            

    defineArrow(upArrow, Up);
    defineArrow(downArrow, Down);
}

void lcdDrawer::drawLCD(const Menu& menu) {
    lcd->clear();

    drawCurrentMenuItem(menu);
    drawNextMenuItem(menu);
    indicateCurrentMenuPosition(menu);
}

void lcdDrawer::drawDownArrow() {
    lcd->setCursor(15, 1);
    lcd->write(std::byte(2));
}
void lcdDrawer::drawUpArrow() {
    lcd->setCursor(15, 0);
    lcd->write(std::byte(1));
}

void lcdDrawer::drawCurrentMenuItem(const Menu& menu) {
    lcd->setCursor(1, 0);
    lcd->print(menu.currentMenuItem());
}

void lcdDrawer::drawNextMenuItem(const Menu& menu) {
    lcd->setCursor(1, 1);
    lcd->print(menu.nextMenuItem());
}

void lcdDrawer::indicateCurrentMenuPosition(const Menu& menu) {
    if (menu.isFirstPage()) {
        drawDownArrow();
        return;
    }
    
    if (menu.isContentPage()) {
        drawDownArrow();
        drawUpArrow();
        return;
    } 
    
    if (menu.isLastPage()) {
        drawUpArrow();
    }
}

void lcdDrawer::defineArrow(const std::byte arrowSource[8], ActionType action) {
    switch(action) {
        case Up: 
            for (int i = 0; i < 8; i++)
                upArrow[i] = arrowSource[i];
            lcd->createChar(std::byte(1), upArrow);
            break;
        case Down:
            for (int i = 0; i < 8; i++)
                downArrow[i] = arrowSource[i];
            lcd->createChar(std::byte(2), downArrow);
            break;
        default: // should not happen
            break;
    }
}

