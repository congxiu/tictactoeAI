#include <iostream>
#include <tuple>
using namespace std;

typedef tuple<int, char> mytuple;

tuple<int, char> testTuple(int a, char b)
{
    cout << a << b << endl;
    return tuple<int, char> (a, b);
}

int testArray(int anArray[3])
{
    anArray[2] = 1;
    return anArray[2];
}

int main()
{
    std::tuple<int, char> foo (10, 'x');
    auto bar = std::make_tuple ("test", 3.1, 14, 'y');

    get<2>(bar) = 100;

    int myint; char mychar;

    tie (ignore, ignore, myint, mychar) = bar;

    mychar = get<3>(bar);

    foo = testTuple(3, 'a');    
    tuple<int, char> foo2 = testTuple(111, 'b');

    cout << get<0>(foo2) << get<1>(foo2) << endl;
    mytuple foo3[2] = {foo, foo2};
    int tryThis[3] = {1,3,4};

    cout << testArray(tryThis) << tryThis[2] << endl;

    int twoArray[2][2] = {1,2,3,4};
    int twoArrayCopy[2][2];
    memcpy(twoArrayCopy, twoArray, sizeof(int) * 4);

    for (int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            cout << twoArray[i][j] << ' ' << twoArrayCopy[i][j] << endl;
        }
    }
    return 0;
}
