//
// Created by yifan on 22/11/20.
//
#include <iostream>
#include "Sales_item.h"

int main()
{
   // std::cout << "Enter two number:" << std::endl;
   // int v1 = 0, v2 = 0;
   // std::cin >> v1 >> v2;
   // std::cout << "The sum of " << v1 << " and " << v2
   //           << " is " << v1 * v2 << std::endl;

    //std::cout << "Hello World" << std::endl;
    std::cout << "/*";
    std::cout << "*/";
    std::cout << /* "*/" */";
    //std::cout << /* "*/" /* "/*" */";

    std::cout << std::endl;
    int val = 50, sum = 0;
    while ( val <= 100)
    {
        sum += val;
        ++val;
    }
    std::cout << "Sum of 1 to 10 is "
              << sum << std::endl;
    val = 10;
    while ( val >= 0)
    {
        std::cout << "Cur val is "
                  << val << std::endl;
        --val;
    }

    sum = 0;
    for (int i = -100; i <= 100; ++i )
    {
        sum += i;
    }
    std::cout << sum << std::endl;

/*    sum = 0, val = 0;
    while ( std::cin >> val )
    {
        sum += val;
    }
    std::cout << "SUM is:" << sum << std::endl;*/

    Sales_item item1, item2;
    std::cin >> item1 >> item2;
    if (item1.isbn() == item2.isbn())
    {
        std::cout << item1 + item2 << std::endl;
        return 0;
    }
    else
    {
        std::cerr << "Fail same isbn" << std::endl;
        return -1;
    }


    return 0;
}


