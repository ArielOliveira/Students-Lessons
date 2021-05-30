test: main.o menu.o lcdDrawer.o
	mingw32-g++ -Wall -Werror -Wextra -std=c++17 $^ -o test.exe

main.o: main.cpp menu.hpp lcdDrawer.hpp lcdLibrary.hpp
	mingw32-g++ -Wall -Werror -Wextra -std=c++17 -c $< -o main.o

menu.o: menu.cpp menu.hpp
	mingw32-g++ -Wall -Werror -Wextra -std=c++17 -c $< -o menu.o

lcdDrawer.o: lcdDrawer.cpp lcdDrawer.hpp lcdLibrary.hpp
	mingw32-g++ -Wall -Werror -Wextra -std=c++17 -c $< -o lcdDrawer.o

clean:
	del *.o