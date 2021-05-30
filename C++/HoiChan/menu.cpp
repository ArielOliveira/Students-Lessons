#include "menu.hpp"

#include <iostream>

Menu::Menu() :
pageNo(0),
maxPageNo(0),
maxMenuItem(0),
pageMenu(nullptr) 
{}

Menu::Menu(int _pageNo, const string _pageMenu[], int _maxMenuItem) :
    pageNo(_pageNo),
    maxMenuItem(_maxMenuItem) {
        pageMenu = new string();

        if (maxMenuItem > 0) {
            maxPageNo = round((maxMenuItem / 2) + .5);

            for (int i = 0; i < maxMenuItem; i++)
                pageMenu[i] = _pageMenu[i]; 
       }
}

// This function return the next pageNo
int Menu::nextPageNo() const { return pageNo+1; }

// This function change the pageNo to next page
void Menu::flipToNextPage() {
    pageNo += 1;
    pageNo = constrain(pageNo, 0, maxPageNo);
}

// This function change the pageNo to previous page
void Menu::flipToPrevPage() {
    pageNo -= 1;
    pageNo = constrain(pageNo, 0, maxPageNo);
}

// This function returns true if it's first page on the menu
bool Menu::isFirstPage() const { return pageNo == 0; }

// This function returns true if it's last page on the menu
bool Menu::isLastPage() const {  return pageNo == maxPageNo; }

// This function returns true if it's any page between the first page
// and the last page on the menu
bool Menu::isContentPage () const { return pageNo > 0 && pageNo < maxPageNo; }

// This function returns the current menu item
string Menu::currentMenuItem() const {  return pageMenu[pageNo]; }

// This function returns the next menu item
string Menu::nextMenuItem() const { return pageMenu[nextPageNo()]; }
