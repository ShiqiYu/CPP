class Base 
{
  protected:
    int n;
  private:
    void foo1(Base& b)
    {
        n++;    // Okay
        b.n++;  // Okay
    }
};
 
class Derived : public Base 
{
    void foo2(Base& b, Derived& d) 
    {
        n++;        //Okay
        this->n++;  //Okay
        //b.n++;      //Error. You cannot access a protected member through base
        d.n++;      //Okay
    }
};
 
void compare(Base& b, Derived& d) // a non-member non-friend function
{
    // b.n++; // Error
    // d.n++; // Error
}