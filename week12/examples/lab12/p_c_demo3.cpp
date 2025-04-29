#include <iostream>
#include <cstring>
using namespace std;
class Parent{
private:
    int id;
    char* name;

public:
    Parent(int i=0, const char* n="null");
    Parent(const Parent& p);
    virtual ~Parent();
    Parent& operator=(const Parent& prhs);

    friend ostream& operator<<(ostream& os, const Parent& p){
        os<<"Parent:"<<p.id<<", "<<p.name<<endl;
        return os;
    } 
};

class Child: public Parent{
private:
    char* style;
    int age; 

public:
    Child(int i=0, const char* n="null", const char* s="null", int a=0);
    Child(const Child& c);
    ~Child();
    Child& operator=(const Child& crhs);
    friend ostream& operator<<(ostream& os, const Child& c){
        os<<(Parent&)c<<"Child:"<<c.style<<", "<<c.age<<endl;
        return os;
    } 
};

Parent::Parent(int i, const char* n){
    cout<<"calling Parent defautl constructor Parent()\n";
    id = i;
    name = new char[strlen(n) + 1];
    //strcpy_s(name,strlen(n)+1, n);
    strncpy(name, n,strlen(n)+1);
}

Child::Child(int i, const char* n, const char* s, int a): Parent(i,n){
    cout<<"call Child default constructor Child()\n";
    style = new char[strlen(s) + 1];
    //strcpy_s(style,strlen(s)+1, s);
    strncpy(style, s,strlen(s)+1);
    age=a;
}

Parent:: ~Parent(){
    cout<< "call Parent destructor.\n";
    delete [] name;
}
Child::~Child(){
    cout<<"call Child destructor.\n";
    delete[] style;
}

Parent::Parent(const Parent& p){
    cout<<"calling Parent copy constructor Parent(const Parent&)\n";
    id = p.id;
    name = new char[strlen(p.name)+1];
    //strcpy_s(name, strlen(p.name)+1, p.name);
    strncpy(name, p.name,strlen(p.name)+1);
}

Child::Child(const Child& c):Parent(c){
    cout<<"calling Child copy constructor Child(const Child&)\n";
    age = c.age;
    style = new char[strlen(c.style)+1];
    //strcpy_s(style, strlen(c.style)+1, c.style);
    strncpy(style, c.style, strlen(c.style)+1);
}

Parent& Parent::operator=(const Parent& prhs){
    cout<<"call Parent assignment operator:\n";
    if(this == &prhs)
        return *this;

    delete []name;
    this->id = prhs.id;
    name = new char[strlen(prhs.name)+1];
    //strcpy_s(name,strlen(prhs.name)+1, prhs.name);
    strncpy(name,prhs.name,strlen(prhs.name)+1);
    return *this;    
}

Child& Child::operator=(const Child& crhs){
    cout<<"call Child assignment operator:\n";
    if(this == &crhs)
        return *this;
    Parent::operator=(crhs);

    delete []style;
    style = new char[strlen(crhs.style)+1];
    //strcpy_s(style,strlen(crhs.style)+1,crhs.style);
    strncpy(style,crhs.style,strlen(crhs.style)+1);
    age = crhs.age;

    return *this;    
}

int main(){
    Parent p1;
    cout<< "value in p1\n"<<p1<<endl;

    Parent p2(101, "Liming");
    cout<< "value in p2\n"<<p2<<endl;

    Parent p3(p1);
    cout<< "value in p3\n"<<p3<<endl;
    p1 = p2;
    cout<< "value in p1\n"<<p1<<endl;

    Child c1;
    cout<<"value in c1\n"<<c1<<endl;

    Child c2(201, "Wuhong","teenager",15);
    cout<<"value in c2\n"<<c2<<endl;

    Child c3(c1);
    cout<< "value in c3\n"<<c3<<endl;
    c1=c2;
    cout<<"value in c1\n"<<c1<<endl;

    return 0;
}