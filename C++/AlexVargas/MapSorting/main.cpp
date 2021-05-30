#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;

using std::cout;
using std::endl;

class myClass {
    private:
        string name;

    public:
        myClass(string _name) : name(_name) {}

        friend bool operator<(const myClass& lhs, const myClass& rhs) {
            return lhs.name.compare(rhs.name) < 0;
        }

        const string getName() const { return name; }
};


int main() {
    map<myClass, int> namesID = {{myClass("Ezra"), 1}, {myClass("Allan"), 2}, {myClass("Abriel"), 3}, {myClass("Beto"), 4}, {myClass("Ariel"), 0}};

    for (auto element : namesID)
        cout << element.first.getName() << " " << element.second << endl;

    return 0;
}