#include <iostream>
#include <cstring>

using namespace std;

class Student
{
  private:
    const int BMI = 24;
    char * name;
    int born;
    bool male; 
  public:
    Student()
    {
        name = new char[1024]{0};
        born = 0;
        male = false;
        BMI = 25;//can it be modified?
        cout << "Constructor: Person()" << endl;
    }
    Student(const char * name, int born, bool male)
    {
        this->name =  new char[1024];
        setName(name);
        this->born = born;
        this->male = male;
        cout << "Constructor: Person(const char, int , bool)" << endl;
    }
    ~Student()
    {
        cout << "To destroy object: " << name << endl;
        delete [] name;
    }

    void setName(const char * s)
    {
        if (s == NULL)
        {
            std::cerr << "The input is NULL." << std::endl;
            return;
        }
        size_t len = 1024 - 1;
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
    int getBorn() const
    {
        born++; //Can it be modified?
        return born;
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
    Student yu("Yu", 2000, true);
    cout << "yu.getBorn() = " << yu.getBorn() << endl;
    return 0;
}