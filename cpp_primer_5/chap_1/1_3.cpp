//
// Created by yifan on 29/11/20.
//

//pointer and array

string nums[] = {"one", "two"};
string *p = &nums[0]; // p is pointing to the first element of array

string *p2 = nums; // same as = &nums[0]

auto nums2(nums); // num2 is a string pointer pointing to the first element of nums

// iter
int arr[] = {0,1,2,3,4};
int *p1 = arr;
++p1; // p1 is pointing to arr[1]

// c++ 11 begin and end return the pointer
int *pbeg = begin(arr);
int *pend = end(arr);
while(pbeg != pend && *pbeg >0)
{
    ++pbeg;
};
// difference between 2 pointer is ptrdiff_t

int ia[] = {0,2,4,6,8};
int last = *(ia +4); // ->ia[4]

// string

// better to use string instead of c type char
string s("hello, world");
const char *str = s.c_str();
// modern cpp try to use vector and iter instead of pointer and array


