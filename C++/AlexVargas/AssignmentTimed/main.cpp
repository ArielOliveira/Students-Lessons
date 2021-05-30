#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <vector>
#include <map>
#include <ostream>

using std::ostream;

class Student {
private:
  std::string name;   // full name
  int year;           // expected graduation
  float gpa;          // [0, 4.0]
  
public:
	Student(std::string name_, int gradYear) : name(name_), year(gradYear), gpa(0) {};
  std::string getName() { return name; }
  int getYear() { return year; }
  int getGPA() { return gpa; }
  void setGPA(float gpa) { 
     if (gpa >= 0 && gpa <= 4) 
        this->gpa = gpa; 
  }


  void extraYear() { year++; }
};


class Course {
private:
  double number;
  std::string name;
	std::vector <Student*> roster;

  
public:
  Course(double num, std::string nm) : 
     number(num), name(nm)
     { }

  // add a (pointer to) Student s
  // to the roster for this course
  Course & operator+=(Student & s) {
      roster.push_back(&s);

      return *this;
  }

  // create a map of Student pointers
  // according to the graduation years
  std::map<int,std::vector<Student*>> studentsByYear() const {
        std::map<int, std::vector<Student*>> studentYearMap;

        for (std::vector<Student*>::const_iterator it = roster.begin(); it != roster.end(); it++)
                studentYearMap[*(it)->getYear()] = it;

        return studentYearMap;
  }

friend ostream& operator << (ostream &out, const Course &c) {}

};

void append(std::istream & is, std::vector<Student> & vec) {
    std::string line;
    std::string name, year, gpa;

    while(getline(is, line)) {
        size_t idx = line.find_first_of(' ');
        name = line.substr(0, idx);

        size_t idx2 = line.find_first_not_of(' ', idx);
        year = line.substr(idx, idx2);

        gpa = line.substr(idx2, line.size());

        std::cout  << year << std::endl;
        std::stringstream ss;
	
        int yearN = 0;
        double gpaN = 0;

        ss << year;  
        ss >> yearN;

        ss << gpa;
        ss >> gpaN;
        Student student(name, yearN);
        student.setGPA(gpaN);

        vec.push_back(student);
    }
}


/* 4.3
Write the complete definition of the operator+= function
 as it would appear in a Course.cpp implementation file
 . The purpose is to add a student (address) to the roster
  of a course. (See function header above in Course.h.)

4.4
Write the complete definition of the studentsByYear function
as it would appear in a Course.cpp implementation file.
(See function header above in Course.h.) The purpose of this
function is to create and return a map where the keys are 
graduation years and the values associated with them are 
vectors of pointers to the students in the course with that 
particular graduating year.

*/

int main() {
    Course course(2, "hellow");

    std::ifstream file("hermione.txt");

    std::vector<Student> vec;

    append(file, vec);

    for (auto v : vec)
        //course += v;
        std::cout << v.getName() << " " << v.getYear() << " " << v.getGPA();
}