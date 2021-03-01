#include <iostream>

using std::cin,
      std::cout,
      std::ostream;

#include "Vector.h"


int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    // DEMONSTRATION OF WORK

    // arr1
    Vector arr1 = Vector(3, 0);
    for (int i = 0; i < 10; i++)
        arr1.Push(i);

    cout<<arr1;
    cout<<arr1.FindFirst(9)<<"\n";

    // arr2
    Vector arr2 = Vector(arr1);
    arr2.Remove(5);
    cout<<arr2;

    // arr3
    Vector arr3;
    arr3 = arr1;
    arr3.Push(500);
    cout<<arr3;

    // arr4
    Vector arr4 = arr3;
    arr4.Insert(5, -2);
    arr4.Insert(5, -2);
    cout<<arr4;



    return 0;
}




