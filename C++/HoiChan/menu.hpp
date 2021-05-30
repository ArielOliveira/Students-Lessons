#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include "lcdLibrary.hpp"

using std::string;

class Menu {
    private:
        int pageNo;
        int maxPageNo;
        int maxMenuItem;

        string* pageMenu;

    public:
        Menu();
        Menu(int pageNo, const string pageMenu[], int _maxMenuItem);

        // This function return the next pageNo
        int nextPageNo() const;

        // This function change the pageNo to next page
        void flipToNextPage();

        // This function change the pageNo to previous page
        void flipToPrevPage();

        // This function returns true if it's first page on the menu
        bool isFirstPage() const;

        // This function returns true if it's last page on the menu
        bool isLastPage() const;

        // This function returns true if it's any page between the first page
        // and the last page on the menu
        bool isContentPage () const;

        // This function returns the current menu item
        std::string currentMenuItem() const;

        // This function returns the next menu item
        std::string nextMenuItem() const;
};  

#endif