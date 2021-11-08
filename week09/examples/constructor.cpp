#include <iostream>
#include <cstring>

using namespace std;

class Student
{
  private:
    char name[4];
    int born;
    bool male; 
  public:
    Student()
    {
        name[0] = 0;
        born = 0;
        male = false;
        cout << "Constructor: Person()" << endl;
    }
    Student(const char * initName): born(0), male(true)
    {
        setName(initName);
        cout << "Constructor: Person(const char*)" << endl;
    }
    Student(const char * initName, int initBorn, bool isMale)
    {
        setName(initName);
        born = initBorn;
        male = isMale;
        cout << "Constructor: Person(const char, int , bool)" << endl;
    }

    void setName(const char * s)
    {
        strncpy(name, s, sizeof(name));
    }
    void setBorn(int b)
    {
        born = b;
    }
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

int main()
{
    Student yu;
    yu.printInfo();

    yu.setName("Yu");
    yu.setBorn(2000);
    yu.setGender(true);
    yu.printInfo();

    Student li("li");
    li.printInfo();

    Student xue = Student("XueQikun", 1962, true);
    //a question: what will happen since "XueQikun" has 4+ characters?
    xue.printInfo();

    Student * zhou =  new Student("Zhou", 1991, false);
    zhou->printInfo();
    delete zhou;

    return 0;
}