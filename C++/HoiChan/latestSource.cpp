#include "libs.hpp"

// Define the struct for the menuItem
struct TheMenu {
    int pageNo;
    int maxPageNo;
    int maxMenuItem;
    std::string* pageMenu;

    // This function return the next pageNo
    int nextPageNo () {
        return pageNo+1;
    }

    // This function takes the inputNum to set the maxMenuItem
    void setmaxMenuItem (int inputNum) {
        maxMenuItem = inputNum;
    }

    // This function takes the inputStringList to set pageMenu
    void setPageMenu (std::string* inputStringList) {
        pageMenu = inputStringList;
    }

    // This function calculate the maxPageNo
    void calmaxPageNo () {
        maxPageNo = round((maxMenuItem / 2) + .5);
    }

    // This function change the pageNo to next page
    void flipToNextPage () {
        pageNo += 1;
        pageNo = constrain(pageNo, 0, maxPageNo);
    }

    // This function change the pageNo to previous page
    void fliptoPrevPage () {
        pageNo -= 1;
        pageNo = constrain(pageNo, 0, maxPageNo);
    }

    // This function returns true if it's first page on the menu
    bool isfirstPage () {
        return pageNo == 0;
    }

    // This function returns true if it's any page between the first page
    // and the last page on the menu
    bool iscontentPage () {
        return pageNo > 0 and pageNo < maxPageNo;
    }

    // This function returns true if it's last page on the menu
    bool islastPage () {
        return pageNo == maxPageNo;
    }

    // This function returns the current menu item
    std::string currentMenuItem () {
        return pageMenu[pageNo];
    }

    // This function returns the next menu item
    std::string nextMenuItem () {
        return pageMenu[nextPageNo()];
    }

};

//  ----------------------------------------------------------------------
//  Screen handling

// Global variable init
LiquidCrystal g_lcd(8, 9, 4, 5, 6, 7);
TheMenu g_theMenuPage;
enum buttonActionType { Up, Down, Nth};

// This function define the custom Down Arrow char on LCD
void defineDownArrow (LiquidCrystal lcdPanel) {
    std::byte downArrow[8] = { (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b11111,
                            (std::byte)0b01110, (std::byte)0b00100 };

    lcdPanel.createChar(std::byte(2), downArrow);
}

// This function define the custom Up Arrow char on LCD
void defineUpArrow (LiquidCrystal lcdPanel) {
    std::byte upArrow[8]   = { (std::byte)0b00100, (std::byte)0b01110,
                            (std::byte)0b11111, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100,
                            (std::byte)0b00100, (std::byte)0b00100 };
                            
    lcdPanel.createChar(std::byte(1), upArrow);
}

void defineMyMenuPage (TheMenu myMenuPage ) {
    const int maxMenuItem = 6;
    std::string mymenuItems[maxMenuItem] = {"START CAPTURE", "START SHOWCASE" ,"PRESETS",
                           "SET TRIGGER", "SETTINGS", "ABOUT"};
    myMenuPage.setmaxMenuItem (maxMenuItem);
    myMenuPage.setPageMenu (mymenuItems);
    myMenuPage.calmaxPageNo();
}

// This funciton will draw the up arrow to the LCD
void drawDownArrowOnLCD (LiquidCrystal lcdPanel) {
    lcdPanel.setCursor(15, 1);
    lcdPanel.write(std::byte(2));
}

// This function will draw the down arrow to the LCD
void drawUpArrowOnLCD (LiquidCrystal lcdPanel) {
    lcdPanel.setCursor(15, 0);
    lcdPanel.write(std::byte(1));
}

// This function will draw the current menu item on LCD
void drawCurrentMenuItemOnLCD (LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    lcdPanel.setCursor(1, 0);
    lcdPanel.print(myMenuPage.currentMenuItem());
}

// This function will draw the next menu item on LCD
void drawNextMenuItemOnLCD (LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    lcdPanel.setCursor(1, 1);
    lcdPanel.print(myMenuPage.nextMenuItem());
}

// This function draw the up and down arrows on the LCD to indicate 
// current menu position
void indicateCurrentMenuPositionOnLCD (LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    if (myMenuPage.isfirstPage()) {
        drawDownArrowOnLCD(lcdPanel);
    }
    if (myMenuPage.iscontentPage()) {
        drawDownArrowOnLCD(lcdPanel);
        drawUpArrowOnLCD(lcdPanel);
    } 
    if (myMenuPage.islastPage()) {
        drawUpArrowOnLCD(lcdPanel);
    }
}

// This function will generate the 2 menu items that can fit on the screen.
// They will change as you scroll through your menu.
// Up and down arrows will indicate your current menu position.
void mainMenuDraw(LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    lcdPanel.clear();
    drawCurrentMenuItemOnLCD(lcdPanel, myMenuPage);
    drawNextMenuItemOnLCD(lcdPanel, myMenuPage);
    indicateCurrentMenuPositionOnLCD(lcdPanel, myMenuPage);
}

//  ----------------------------------------------------------------------
//  Reacting to button presses

// This function return true if there's no action taken for the button pressed
bool isNoButtonPressed ( buttonActionType activeButton ) {
    return activeButton == Nth;
}
// This function is called whenever a button press is evaluated.
// The LCD shield works by observing a voltage drop across the buttons all
// hooked up to A0.
buttonActionType evaluateButton(const int volDrop) {
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

// This function move up the menu and display the menu item
void moveUpMenuOnLCD (LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    myMenuPage.fliptoPrevPage();
    mainMenuDraw (lcdPanel, myMenuPage);  
}

// This function move down the menu and display the menu item
void moveDownMenuOnLCD (LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    myMenuPage.flipToNextPage();
    mainMenuDraw (lcdPanel, myMenuPage);  
}

// This function move up or down the menu page according to the button pressed
void operateMainMenu (LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    buttonActionType buttonAction = Nth;
    mainMenuDraw(lcdPanel, myMenuPage);
    while (isNoButtonPressed(buttonAction)) {
        buttonAction = checkButtonAction();
        switch (buttonAction) {
        case Nth: // When buttonAction returns as Nth there is no action taken
            break;
        case Up:
            moveUpMenuOnLCD(lcdPanel, myMenuPage);
            break;
        case Down:            
            moveDownMenuOnLCD(lcdPanel, myMenuPage);
            break;
        default:
            break;
        }
    }
}

//  ----------------------------------------------------------------------
//  Top level 

void setup(LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    lcdPanel.begin(16, 2);
    defineDownArrow (lcdPanel);
    defineUpArrow (lcdPanel);
    defineMyMenuPage(myMenuPage);
}

void loop(LiquidCrystal lcdPanel, TheMenu myMenuPage) {
    operateMainMenu(lcdPanel, myMenuPage);
}

// To simulate the rest of the toolchain
int main () {
    setup (g_lcd, g_theMenuPage);
    while (true) {
        loop (g_lcd, g_theMenuPage);
    }
}
