#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <stack>
#include <sstream>
#include <iomanip>
#include "main.hpp"
#include "parse.hpp"

template<typename T>
std::string getString(T value) { return ""; }

template<>
std::string getString<int>(int value) {
    std::ostringstream ss;
    ss << value;
    std::string s(ss.str());

    return s;
}

template<>
std::string getString<float>(float value) {
    std::ostringstream ss;
    ss << value;
    std::string s(ss.str());

    return s;
}

template<>
std::string getString<char>(char value) {
    std::stringstream ss;
    std::string s;

    ss << value;
    ss >> s;

    return s;
}

enum AlignType {
    NONE,
    LEFT,
    RIGHT
};

struct ConfigData {
    int min;
    int max;
    int width;
    AlignType align;
    int stretch;
    int header;

    std::string toString() {
        std::stringstream ss;
        std::string s;

        s += "config.min=" + getString<int>(min) + '\n';
        s += "config.max=" + getString<int>(max) + '\n';
        s += "config.width=" + getString<int>(width) + '\n';
        
        if (align == LEFT) {
            s += "config.align=left\n";  
        } else if (align == RIGHT) {
            s += "config.align=right\n";
        }

        if (stretch != -1) {
            s += "config.stretch=" + getString<int>(stretch) + '\n';
        }

        if (header == 0) {
            s += "config.header=" + getString<int>(header) + '\n';
        }

        return s;
    }
};

template<typename T>
bool drawElement(AlignType align, int width, T value) {
    std::string s = getString<T>(value);
    
    std::cout << "|";
    int spacesToFill = width-s.size()-1;

    if (spacesToFill < 1) {
        std::cout << " ### ";
        return false;
    } else if (align == LEFT) {
        std::cout << " " << s;
        for (int i = 0; i < spacesToFill; i++)
            std::cout << " ";
    } else if (align == RIGHT) {
        for (int i = 0; i < spacesToFill; i++)
            std::cout << " ";
        std::cout << s << " ";
    }
    return true;
}

void drawLine(int width, int rows) {
    for (int i = 0; i < rows; i++) {
        std::cout << "+";
        for (int j = 0; j < width; j++) {
            std::cout << "-";
        }
    }
    std::cout << "+" << std::endl;
}

void drawBlank(int width) {
    std::cout << "|";
    for (int i = 0; i < width; i++)
        std::cout << " ";
}

void drawHeader(AlignType align, int width, int rows) {
    drawLine(width, rows+1);
    drawBlank(width);
    char alphabet = 'A';
    for (int i = 0; i < rows; i++) {
        drawElement<char>(align, width, (alphabet+i));
    }
    std::cout << "|" << std::endl;
}

int main(){  
    // variable for decoded config
    ConfigData configData = {-99, 100, 0, NONE, -1, 1};
    config_t config;
    std::string line;
    do {
        std::getline(std::cin, line);

        config = getConfig(line);
        if(config.valid) {
            if (config.type.compare("min") == 0) {
                std::stringstream(config.value) >> configData.min;
            } else if (config.type.compare("max") == 0) {
                std::stringstream(config.value) >> configData.max;
            } else if (config.type.compare("width") == 0) {
                std::stringstream(config.value) >> configData.width;
                 if (configData.width < 0) {
                    std::cerr << "Invalid configuration " << std::endl;
                    exit(102);
                } else if (configData.width <= 2) {
                    std::cerr << "Cell is too short" << std::endl;
                    exit(103);
                }
            } else if (config.type.compare("align") == 0) {
                if (config.value.compare("left") == 0) {
                    configData.align = LEFT;

                } else if (config.value.compare("right") == 0) {
                    configData.align = RIGHT;

                }
            } else if (config.type.compare("header") == 0) {
                std::stringstream(config.value) >> configData.header; 
            } else if (config.type.compare("stretch") == 0) {
                std::stringstream(config.value) >> configData.stretch;
            }
        }
    } while(config.valid);


    
    std::vector<std::vector<int>> values;

    size_t maxRows = 0;
    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;
        
        while (std::getline(ss,cell, ';')) {
            try {   // if loaded cell is number                 
                number = std::stoi(cell);
				row.push_back(number);
                if (number < configData.min || number > configData.max) {
                    std::cerr << "Out of range" << std::endl;
                    exit(100);
                }
            } catch(const std::exception& e) { // if there is a text (SUM?)
                int sum = 1;
                char alphabet = 'A';
                
                std::string test = "SUM(";
                test.append(1, alphabet);
                test.append(1, ':');
                test.append(1, alphabet+row.size()-1);
                test += ')';
                                
                if (cell.compare(test) != 0) {
                    std::cerr << "Invalid input" << std::endl;
                    exit(101);
                }
                row.push_back(sum);
            }
            if (row.size() > maxRows)
                maxRows = row.size();
        }   
        values.push_back(row);     
    }
    
    if (configData.stretch == 1)
        configData.width++;

    // print out the config - TODO
    std::cout << configData.toString() << std::endl;


    int rowsToDraw = maxRows;
    if (configData.header == 1) {
        drawHeader(configData.align, configData.width+2, maxRows);
        rowsToDraw = maxRows+1;
    }

	// print table
    for (std::size_t i = 0; i < values.size(); i++){
        auto it = values[i].begin();
        drawLine(configData.width+2, rowsToDraw);
        float sum = 0;
         if (configData.header == 1)
            drawElement<float>(configData.align, configData.width+2, i+1);
        for (std::size_t j = 0; j < maxRows; j++) {
            if (it != values[i].end()) {   
                if (*it == 1) {
                    drawElement<float>(configData.align, configData.width+2, sum);
                    if (*std::next(it) == 1) {
                        sum += sum;
                    }

                } else {
                    sum += *it; 
                    drawElement<float>(configData.align, configData.width+2, values[i][j]);
                }
                it++; 
            } else if (it == values[i].end() && *it == 1)
                drawElement<float>(configData.align, configData.width+2, sum);
              else 
                drawBlank(configData.width+2);
        }
        std::cout << "|" << std::endl;
    }

    drawLine(configData.width+2, rowsToDraw);

    return 0;
}