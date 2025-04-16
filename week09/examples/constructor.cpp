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
        name[0] = '\0';
        born = 0;
        male = false;
        cout << "Constructor: Person()" << endl;
    }
    Student(const char * initName): born(0), male(false)
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
        if (s == NULL)
        {
            std::cerr << "The input is NULL." << std::endl;
            return;
        }
        size_t len = sizeof(name) - 1;
        strncpy(name, s, len);
        name[len] = '\0';
    }
    void setBorn(int b)
    {
        if (b >= 1990 && b <= 2020 )
            born = b;
        else
            std::cerr << "The input b is " << b << ", and should be in [1990, 2020]." << std::endl;
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

    Student * s =  new Student();
    // Student * s =  new Student; // the same
    s->printInfo();
    delete s;

    return 0;
}