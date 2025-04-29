#include <cstring>
#include <iostream>
using namespace std;
class Parent{
private:
    int id;
    string name;

public:
    Parent():id(1),name("null"){
        cout<<"calling default constructor Parent()\n";
    }
    Parent(int i, string n):id(i),name(n){
        cout<<"calling default constructor Parent(int,string)\n";
    }

    friend ostream& operator<<(ostream&os, const Parent& p){
        return os<<"Parent:"<<p.id<<","<<p.name<<endl;
    }

};


int main(){
    Parent p1(101,"Liming");
    cout<<"values in p1:\n"<<p1<<endl;

    Parent p2(p1);
    cout<<"values in p2:\n"<<p2<<endl;

    Parent p3;
    cout<<"before assignment, values in p3:\n"<<p3<<endl;
    p3 = p2;
    cout<<"values in p3:\n"<<p3<<endl;
   
}