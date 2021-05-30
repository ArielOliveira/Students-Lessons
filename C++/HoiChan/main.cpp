#include <iostream>
#include <vector>

#include "menu.hpp"
#include "lcdDrawer.hpp"

using std::cout;
using std::endl;

// This function return true if there's no action taken for the button pressed
bool isNoButtonPressed ( ActionType activeButton ) {
    return activeButton == Nth;
}
// This function is called whenever a button press is evaluated.
// The LCD shield works by observing a voltage drop across the buttons all
// hooked up to A0.
ActionType evaluateButton(const int volDrop) {
    if (volDrop < 50) {
        return Up;
    }
    if (volDrop < 195) {
        return Down;
    }
    return Nth;
}

// This function return Up, Down or Nth according to the key pressed
ActionType checkButtonAction () {
    int readKey = analogRead(0);
    return evaluateButton(readKey);
}

// This function move up the menu and display the menu item
void moveUpMenuOnLCD (lcdDrawer* lcd, Menu* menu) {
    menu->flipToPrevPage();
    lcd->drawLCD(*menu);
}

// This function move down the menu and display the menu item
void moveDownMenuOnLCD (lcdDrawer* lcd, Menu* menu) {
    menu->flipToNextPage();
    lcd->drawLCD(*menu);  
}

// This function move up or down the menu page according to the button pressed
void operateMainMenu (lcdDrawer* lcd, Menu* menu) {
    ActionType buttonAction = Nth;
    
    lcd->drawLCD(*menu);

    while (isNoButtonPressed(buttonAction)) {
        buttonAction = checkButtonAction();
        switch (buttonAction) {
        case Nth: // When buttonAction returns as Nth there is no action taken
            break;
        case Up:
            moveUpMenuOnLCD(lcd, menu);
            break;
        case Down:            
            moveDownMenuOnLCD(lcd, menu);
            break;
        default:
            break;
        }
    }
}

int main() {
    // Not really necessary to allocate on the heap
    std::string mymenuItems[] = {"START CAPTURE", "START SHOWCASE" ,"PRESETS",
                           "SET TRIGGER", "SETTINGS", "ABOUT"};

    Menu* menu = new Menu(0, mymenuItems, sizeof(mymenuItems) / sizeof(std::string));

    std::byte upArrow[8]   = { (std::byte)0b00100, (std::byte)0b01110,
                            (std::byte)0b11111, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100 };

    std::byte downArrow[8] = { (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b11111,
                            (std::byte)0b01110, (std::byte)0b00100 };

    lcdDrawer* drawer = new lcdDrawer(8, 9, 4, 5, 6, 7, downArrow, upArrow);


    drawer->drawLCD(*menu);

    operateMainMenu(drawer, menu);

    Menu menu2;
    
    delete menu;
    return 0;
}