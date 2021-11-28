#include <iostream>
using namespace std;

class Base
{
  public:
    int a;
    int b;
    Base(int a = 0, int b = 0)
    {
        this->a = a;
        this->b = b;
        cout << "Constructor Base::Base(" << a << ", " << b << ")" << endl;
    }
    ~Base()
    {
        cout << "Destructor Base::~Base()" << endl;
    }
    int product()
    {
        return a * b;
    }
    friend std::ostream & operator<<(std::ostream & os, const Base & obj)
    {
        os << "Base: a = " << obj.a << ", b = " << obj.b;
        return os;
    }
};

class Derived: public Base
{
  public:
    int c;
    Derived(int c): Base(c - 2, c - 1), c(c)
    {
        this->a += 3; //it can be changed after initialization
        cout << "Constructor Derived::Derived(" << c << ")" << endl;
    }
    ~Derived()
    {
        cout << "Destructor Derived::~Derived()" << endl;
    }
    int product()
    {
        return Base::product() * c;
    }
    friend std::ostream & operator<<(std::ostream & os, const Derived & obj)
    {
        // call the friend function in Base class
        os << static_cast<const Base&>(obj) << endl;

        os << "Derived: c = " << obj.c;
        return os;
    }
};

int main()
{
    {
        Base base(1, 2);
        cout << base << endl;
    }
    cout << "----------------------" << endl;
    {
        Derived derived(5);
        cout << derived << endl;
        cout << "Product = " << derived.product() << endl; 
    }
    return 0;
}
