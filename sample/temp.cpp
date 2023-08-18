#include <iostream>

namespace foo
{
class FooClass
{
public:
    FooClass(int a1, int a2,
        int a3) :
        a1(a1), a2(a2), a3(a3) { int x[] = { 1, 2, 3 }; auto y = { a1, a2, a3 }; }

private:
    int a1;
    int a2;
    int a3;
};


int main()
{
    int x = 1;

    if (x == 1)
        return 124;

    else if (x == 2) {
        return 12;
    }

    else
        return 14;


    if (x == 12)
        if (x == 13)
            return 14;
    else
        return 15;


    if (x == 1) {
        if (x == 2)
            return 1;
    }
    else
        return 0;

    
    if (x == 101)
        if (x == 102)
            while(true)
                return 103;
    else
        return 104;


    int a1 = 0;
    int a2 = 1;
    int a3 = 2;
    while(true) {

        int temp = a1;
        a1 = a2;
        a2 = a3;
        a3 = temp;
        temp = temp
            * a1
            * a2
            * a3;
    }

    return 0;
}
}