#include <iostream>
#include <typeinfo>

using namespace std;

class Person
{
protected:
    string name;
public:
    Person(string name=""):name(name){};
    virtual ~Person(){}
    string getInfo(){return name;}
};

class Student: public Person
{
    string studentid;
public:
    Student(string name="", string sid=""):Person(name),studentid(sid){};
    string getInfo(){return name+":"+studentid;}
};

int main()
{
    string s("hello");

    cout << "typeid.name of s           is " << typeid(s).name() << endl;
    cout << "typeid.name of std::string is " << typeid(std::string).name() << endl;
    cout << "typeid.name of Student     is " << typeid(Student).name() << endl;

    if(typeid(std::string) == typeid(s))
        cout << "s is a std::string object." << endl;

    return 0;
}

