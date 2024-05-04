#include <iostream>
#include <cstring>

class Student
{
  public:
    char name[4];
    int born;
    bool male; 
    void setName(const char * s)
    {
        size_t len = sizeof(name) - 1;
        strncpy(name, s, len);
    }
    void setBorn(int b)
    {
        if (b >= 1990 && b <= 2020 )
            born = b;
        else
            std::cerr << "The input b is " << b << ", and should be in [1990, 2020]." << std::endl;
    }
    void setGender(bool isMale)
    {
        male = isMale;
    }
    void printInfo()
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Born in " << born << std::endl;
        std::cout << "Gender: " << (male ? "Male" : "Female") << std::endl;
    }
};

int main()
{
    Student yu;
    yu.setName("Yu");
    yu.setBorn(2000);
    yu.setGender(true);
    yu.born = 2001; // it can also be manipulated directly
    yu.printInfo();
    std::cout << "It's name is " << yu.name << std::endl; 
    return 0;
}