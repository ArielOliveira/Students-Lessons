#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const double EPSILON = 0.0001;

int compare(double a, double b) {
    double diff = abs(a - b);
    if (diff < EPSILON) {       
        return 1;
    } else {
        return 0;
    }
}

int main() {          
    double m_l2[10] = {57.05132, 71.0779, 99.13106, 113.15764, 113.15764, 115.0874, 129.11398, 97.11518, 101.10388, 87.0773};
    double m_l[10] = {12.05132, 178.0779, 52.13106, 44.15764, 100.15764, 726.0874, 109.11398, 9.11518, 198.10388, 87.0773};
    
    std::vector<double> b;
    
    for (int d = 0; d < 10; d++){
        for(int e = 0; e < 10; e++){
            for(int f = 0; f < 10; f++){
                for(int g = 0; g < 10; g++){
                    for(int h = 0; h < 10; h++){
                        b.push_back(m_l2[d]+m_l2[e]+m_l2[f]+m_l2[g]+m_l2[h]);
                        }}}}}


    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end(), compare), b.end());
    
    std::cout << b.size() << std::endl;
    std::cout << std::fixed;
    std::cout.precision(4);
    
    int count = 0;
    for (auto number : b) {
        count++;
        std::cout << "  '" << number << "'  ";
        if (count >= 6) {
            std::cout << std::endl;
            count = 0;
        }
    }


    std::cout << std::endl;

    cout << "The size of the b is: " << b.size() << std::endl;
    cout << " " << std::endl;

    return 0;
}