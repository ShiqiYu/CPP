#include <iostream>
#include <string>
using namespace std;

class Person
{
  public:
    string name;
    Person(string n): name(n){}
    virtual void print()
    {
        cout << "Name: " << name << endl;
    }
};

class Person2
{
  public:
    string name;
    Person2(string n): name(n){}
    virtual void print() = 0; 
};

class Student: public Person
{
  public:
    string id;
    Student(string n, string i): Person(n), id(i){}
    void print() override
    {
        cout << "Name: " << name;
        cout << ". ID: " << id << endl;
    }
};

int main()
{
    {
        Person * p = new Student("xue", "2020");
        p->print(); //if print() is not a virtual function, different output
        delete p;
    }

    // {
    //     Student stu("yu", "2019");
    //     stu.print();
    //     static_cast<Person>(stu).print();
    // }

    return 0;
}