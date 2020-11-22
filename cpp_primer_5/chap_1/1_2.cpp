//
// Created by yifan on 22/11/20.
//

// init and resign are 2 totally different operations

// 20 24 0x14  totally different

//literal  different types

// c++ 11 int units_sold{0}; list initialization
//e.g. error

#include <iostream>
#include <cstdlib>
long double ld = 3.1415;
int a{ld};


// correct, but ld converted from long double to int
int c(ld);

// best practice: to init all variables within the class

//declare
extern int t;
//define
int i;

int _;


//scope

// avoid duplicated naming

//Reference (by default lvalue reference)
int ival = 1024;
int &refVal = ival; //refVal is another name of ival

// error
int &refVal2; // ref must be inited

// reference is another name of existing object
refVal =2;
int ii = refVal;

int &refVal3 = refVal; //refVal3 is another name of ival

// reference must be binded with object


// pointer is an object
// pointer don't need to be inited when declaring

int *ip1, *ip2;
double dp, *dp2;

// pointer stores the address of an object
int val = 42;
int *p = &val; // p stores the address of val here & is not a reference
std::cout << *p;
*p = 0; // val is 0

// null pointer

int *p1 = nullptr; // C++ 11 new standard

int *p3 = NULL; // try to avoid it

// best practice: init all pointers

// if have to use it , try to set it as nullptr or 0
int *p12 = nullptr; // init pointer but doesn't point to any objects

p12 = &val;  // p12 -> val
*p12 = 0; //val is 0 now, p12 is still -> val

//void*

//point of any type of object

int t1 = 1;
void *pp = &t1;

//**

int **ppi = &p12;

// pointer is an object, we can define a ref to a pointer

int j = 42;
int *p;
int *&r = p;

r = &j; //  p->i
*r =0; // i =0


//const
const int con = 512;
// must init
// by default const object only works in the current file
// share with other file

// file1.cpp
extern const int bufsize = fcn();
// file1.h
extern const int bufsize;

// const ref
// when initing const ref, we can use any way of init. as far as the init value can be converted to the required type
int i = 42;
const int &r1 = i;
const int &r2 = 42;
const int &r3 = r1 * 2;

//incorrect
int &r4 = r1*2; // r4 is not a const ref

// pointer to const & const pointer

//pointer to const
const double pi = 3.14;
const double *pter = &pi;
double dval = 4.14;
pter = &dval; // can be changed to point to another val

//const pointer
int errNum = 0;
int *const curErr = &errNum; //curErr will always point to errNum
// top level const and low level const

// const expression
// cpp 11 can use constexpr to declare it
constexpr int mf = 20;

//literal type
// string class is not literal type

// type alias
typedef double wages;
typedef wages base, *p;

using SI = Sales_item;

// cpp 11 auto

auto item = va1+val2;
// auto online type should be the same

//incorrect
auto su =0, pi = 3.14;

// auto will ignore top level const so have to manually set it up
const auto &j = 43;

// cpp11 decltype

decltype(fu()) a =x;
decltype((v)) d; // reference





