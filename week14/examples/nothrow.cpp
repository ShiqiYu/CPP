#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    size_t length = 80000000000L;
    int * p = NULL;
    
    try {
        cout << "Trying to allocate a big block of memory" << endl;
        p = new int[length];
        //p = new(nothrow) int[length];
        cout << "No exception." << endl;
    }
    catch (std::bad_alloc & ba)
    {
        cout << "bad_alloc exception!" << endl;
        cout << ba.what() << endl;
    }
    
    if(p)
        cout << "Memory successfully allocated." << endl;
    else
        cout << "So bad, null pointer." << endl;

    if(p)
        delete [] p;
    return 0;
}

