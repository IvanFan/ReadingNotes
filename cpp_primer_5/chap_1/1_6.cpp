//
// Created by yifan on 29/11/20.
//

// function

//local static object

#include <cstring>

static size_t size = 0;

// function declare
void print(int a, int b);

// pass parameters
// passed by reference
void reset(int *ip)
{
    *ip = 0; // the object that ip pointing to has been changed , ip is a new pointer
    ip = 0; // ip not changed outside
}

int i = 42;
reset(&i); // the value of i has been changed

void reset2(int &i)
{
    i = 0;
}
int j = 42;
reset(j); // the value of j has been changed

// main params

int main(int argc, char *argv[]) { ... }

//return c++11

return {"abc", "def"};



// passed by value

//overload same names different params

//function pointer