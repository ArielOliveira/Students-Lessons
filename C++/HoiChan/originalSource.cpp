#include "libs.hpp"


//  ----------------------------------------------------------------------
//  Screen handling

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int menuPage = 0;
std::string menuItems[] = {"START CAPTURE", "START SHOWCASE" ,"PRESETS",
                           "SET TRIGGER", "SETTINGS", "ABOUT"};
int maxMenuPages = round(((sizeof(menuItems) / sizeof(std::string)) / 2) + .5);

// Bitmap icons drawn on screen
std::byte downArrow[8] = { (std::byte)0b00100, (std::byte)0b00100,
                           (std::byte)0b00100, (std::byte)0b00100,
                           (std::byte)0b00100, (std::byte)0b11111,
                           (std::byte)0b01110, (std::byte)0b00100 };
std::byte upArrow[8]   = { (std::byte)0b00100, (std::byte)0b01110,
                           (std::byte)0b11111, (std::byte)0b00100,
                           (std::byte)0b00100, (std::byte)0b00100,
                           (std::byte)0b00100, (std::byte)0b00100 };

// This function will generate the 2 menu items that can fit on the screen.
// They will change as you scroll through your menu.
// Up and down arrows will indicate your current menu position.
void mainMenuDraw() {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(menuItems[menuPage]);
    lcd.setCursor(1, 1);
    lcd.print(menuItems[menuPage + 1]);
    if (menuPage == 0) {
        lcd.setCursor(15, 1);
        lcd.write(std::byte(2));
    } else if (menuPage > 0 and menuPage < maxMenuPages) {
        lcd.setCursor(15, 1);
        lcd.write(std::byte(2));
        lcd.setCursor(15, 0);
        lcd.write(std::byte(1));
    } else if (menuPage == maxMenuPages) {
        lcd.setCursor(15, 0);
        lcd.write(std::byte(1));
    }
}


//  ----------------------------------------------------------------------
//  Reacting to button presses

// This function is called whenever a button press is evaluated.
// The LCD shield works by observing a voltage drop across the buttons all
// hooked up to A0.
int evaluateButton(int x) {
    int result = 0;
    if (x < 50) {
        result = 1;  // up
    } else if (x < 195) {
        result = 2;  // down
    }
    return result;
}

int readKey;

void operateMainMenu () {
    int activeButton = 0;
    while (activeButton == 0) {
        int button;
        readKey = analogRead(0);
        button = evaluateButton(readKey);
        switch (button) {
        case 0: // When button returns as 0 there is no action taken
            break;
        case 1:
            button = 0;
            menuPage = menuPage - 1;
            menuPage = constrain(menuPage, 0, maxMenuPages);
            mainMenuDraw ();
            activeButton = 1;
            break;
        case 2:
            button = 0;
            menuPage = menuPage + 1;
            menuPage = constrain(menuPage, 0, maxMenuPages);
            mainMenuDraw ();
            activeButton = 1;
            break;
        }
    }
}


//  ----------------------------------------------------------------------
//  Top level 

void setup() {
    lcd.begin(16, 2);
    lcd.createChar(std::byte(1), upArrow);
    lcd.createChar(std::byte(2), downArrow);
}

void loop() {
    mainMenuDraw();
    operateMainMenu();
}

// To simulate the rest of the toolchain
int main () {
    setup ();
    while (true) {
        loop ();
    }
}
