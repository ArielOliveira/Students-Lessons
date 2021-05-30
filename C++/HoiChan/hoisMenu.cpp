#include "menu.hpp"

Menu::Menu() :
pageNo(0),
maxPageNo(0),
maxMenuItem(0),
pageMenu(nullptr)
{}

Menu::Menu(int _pageNo, const string _pageMenu[]) :
    pageNo(_pageNo) {
        pageMenu = new string();

        if (sizeof(_pageMenu)> sizeof(std::string)) {
            maxMenuItem = sizeof(_pageMenu) / sizeof(std::string);
            maxPageNo = round ((maxMenuItem/2) + .5);
            
            for (int i =0; i < maxMenuItem; i++)
                pageMenu[i] = _pageMenu[i];
        }
    }

    // This function return the next pageNo
    int Menu::nextPageNo (){
        return pageNo+1;
    }

    // This function change the pageNo to next page
    void Menu::flipToNextPage (){
        pageNo += 1;
        pageNo = constrain(pageNo, 0, maxPageNo);
    }

    // This function change the pageNo to previous page
    void Menu::fliptoPrevPage (){
        pageNo -= 1;
        pageNo = constrain(pageNo, 0, maxPageNo);
    }

    // This function returns true if it's first page on the menu
    bool Menu::isFirstPage (){
        return pageNo == 0;
    }

    // This function returns true if it's any page between the first page
    // and the last page on the menu
    bool Menu::isContentPage (){
        return pageNo > 0 and pageNo < maxPageNo;
    }

    // This function returns true if it's last page on the menu
    bool Menu::isLastPage (){
        return pageNo == maxPageNo;
    }

    // This function returns the current menu item
    string Menu::currentMenuItem (){
        return pageMenu[pageNo];
    }

    // This function returns the next menu item
    string Menu::nextMenuItem (){
        return pageMenu[nextPageNo()];
    }