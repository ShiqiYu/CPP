#include <iostream>
#include <cstring>

using namespace std;

class Student
{
  private:
    static size_t student_total; // declaration only
    //inline static size_t student_total = 0; //C++17, definition outside isn't needed
    char * name;
    int born;
    bool male; 
  public:
    Student()
    {
        student_total++;
        name = new char[1024]{0};
        born = 0;
        male = false;
        cout << "Constructor: Person(): student_total = " << student_total << endl;
    }
    Student(const char * initName, int initBorn, bool isMale)
    {
        student_total++;
        name =  new char[1024];
        setName(initName);
        born = initBorn;
        male = isMale;
        cout << "Constructor: Person(const char, int , bool): student_total = " << student_total << endl;
    }
    ~Student()
    {
        student_total--;
        cout << "To destroy object: " << name ;
        cout << ". Then " << student_total << " students are left" << endl;
        delete [] name;
    }

    void setName(const char * s)
    {
        strncpy(name, s, 1024);
    }
    void setBorn(int b)
    {
        born = b;
    }
    static size_t getTotal() {return student_total;}
    // the declarations, the definitions are out of the class
    void setGender(bool isMale);
    void printInfo();
};

void Student::setGender(bool isMale)
{
    male = isMale;
}
void Student::printInfo()
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Born in " << born << std::endl;
    std::cout << "Gender: " << (male ? "Male" : "Female") << std::endl;
}

//size_t Student::student_total = 0; // definition it here

int main()
{
    cout << "---We have " << Student::getTotal() << " students---" << endl;

    Student * class1 = new Student[3]{
        {"Tom", 2000, true},
        {"Bob", 2001, true},
        {"Amy", 2002, false},
    };

    cout << "---We have " << Student::getTotal() << " students---" << endl;

    Student yu("Yu", 2000, true);

    cout << "---We have " << Student::getTotal() << " students---" << endl;

    class1[1].printInfo();
    delete []class1;

    cout << "---We have " << Student::getTotal() << " students---" << endl;

    return 0;
}