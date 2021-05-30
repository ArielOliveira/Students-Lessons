#include "libs.hpp"
#include <vector>

//  ----------------------------------------------------------------------
//  Screen handling


// Prepare the global variables
// Sets up the connection between the screen and the microcontroller
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int menuPage;
int maxMenuPages;
std::vector<std::string> menuItems;
enum buttonActionType { Up, Down, Nth};

// This function define the menu items to be shown on the LCD
void defineMenuItems () {
    menuPage = 0;
    menuItems = {"START CAPTURE", "START SHOWCASE" ,"PRESETS",
                            "SET TRIGGER", "SETTINGS", "ABOUT"};
    maxMenuPages = round(((sizeof(menuItems) / sizeof(std::string)) / 2) + .5);
}

// This function define the custom Down Arrow char on LCD
void defineDownArrow () {
    std::byte downArrow[8] = { (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b11111,
                            (std::byte)0b01110, (std::byte)0b00100 };

    lcd.createChar(std::byte(2), downArrow);
}

// This function define the custom Up Arrow char on LCD
void defineUpArrow () {

    std::byte upArrow[8]   = { (std::byte)0b00100, (std::byte)0b01110,
                            (std::byte)0b11111, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100 };
                            
    lcd.createChar(std::byte(1), upArrow);
}

// This funciton will draw the up arrow to the LCD
void drawDownArrow () {
    lcd.setCursor(15, 1);
    lcd.write(std::byte(2));
}

// This function will draw the down arrow to the LCD
void drawUpArrow () {
    lcd.setCursor(15, 0);
    lcd.write(std::byte(1));
}

// This function return the next menuPage number
int nextPage() {
    return menuPage + 1;
}

// This function will draw the current menu item to the LCD
void drawCurrentMenuItem () {
    lcd.setCursor(1, 0);
    lcd.print(menuItems[menuPage]);
}

// This function will draw the next menu item to the LCD
void drawNextMenuItem () {
    lcd.setCursor(1, 1);
    lcd.print(menuItems[nextPage()]);
}

// This function returns true if it's first page on the menu
bool isfirstPage () {
    return menuPage == 0;
}

// This function returns true if it's any page between the first page
// and the last page on the menu
bool iscontentPage () {
    return menuPage > 0 and menuPage < maxMenuPages;
}

// This function returns false if it's last page on the menu
bool islastPage () {
    return menuPage == maxMenuPages;
}

// This function draw the up and down arrows to indicate the current menu 
// position
void indicateCurrentMenuPosition () {
    if ( isfirstPage() ) {
        drawDownArrow() ;
    }
    if ( iscontentPage() ) {
        drawDownArrow();
        drawUpArrow() ;      
    }
    if ( islastPage() ) {
        drawUpArrow() ;
    }
}

// This function will generate the 2 menu items that can fit on the screen.
// They will change as you scroll through your menu.
// Up and down arrows will indicate your current menu position.
void mainMenuDraw() {
    lcd.clear();
    drawCurrentMenuItem ();
    drawNextMenuItem ();
    indicateCurrentMenuPosition ();
}

//  ----------------------------------------------------------------------
//  Reacting to button presses

// This function is called whenever a button press is evaluated.
// The LCD shield works by observing a voltage drop across the buttons all
// hooked up to A0.
buttonActionType evaluateButton(int volDrop) {
    if (volDrop < 50) {
        return Up;
    }
    if (volDrop < 195) {
        return Down;
    }
    return Nth;
}

// This function return Up, Down or Nth according to the key pressed
buttonActionType checkButtonAction () {
    int readKey = analogRead(0);
    return evaluateButton(readKey);
}

// This function return true if there's no action taken for the button pressed
// bool isNoButtonPressed ( int activeButton ) {
//     return activeButton == 0;
// }

bool isNoButtonPressed ( buttonActionType activeButton ) {
    return activeButton == Nth;
}

// This function move the menu page to the previous item
void gotoPrevoiusPage () {
    menuPage -= 1;
}

// This function move the menu page to the next item
void gotoNextPage () {
    menuPage += 1;
}

// This function constraint the menu page to be within range
void constraintMenuPage () {
    menuPage = constrain(menuPage, 0, maxMenuPages);
}

// This function go up the menu page
void goUpMenuPage () {
    gotoPrevoiusPage ();
    constraintMenuPage ();
    mainMenuDraw ();
}

// This function go down the menu page
void goDownMenuPage () {
    gotoNextPage ();
    constraintMenuPage ();
    mainMenuDraw ();    
}

// This function move up or down the menu page according to the button pressed
void operateMainMenu () {
    buttonActionType buttonAction = Nth;
    while (isNoButtonPressed(buttonAction)) {
        buttonAction = checkButtonAction();
        switch (buttonAction) {
        case Nth: // When buttonAction returns as Nth there is no action taken
            break;
        case Up:
            goUpMenuPage();
            break;
        case Down:
            goDownMenuPage();        
            break;
        }
    }
}


//  ----------------------------------------------------------------------
//  Top level 

void setup() {
    defineMenuItems ();
    lcd.begin(16, 2);
    defineDownArrow ();
    defineUpArrow ();
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
