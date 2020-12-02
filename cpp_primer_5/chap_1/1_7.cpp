//
// Created by yifan on 29/11/20.
//
//class

struct Sales_data{
    std::string isbn() const { return bookNo;} // return this->bookNo const is used for this
};

// it is similar to
std:: string Sales_data::isbn(const Sales_data *const this) { return this->bookNo; }

// return *this; is a trick

//cpp 11
Sales_data() = default; //default constructor fun

Sales_data(const std::string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n) {}; // init bookNo, units_sold and revenue with input params

// public & private

// class & struct

// by default, use class because class by default set as private

// inline function can save the compile time during compiling

// mutable can be changed in const member fun


// static obj is outside of instance and shared by all instances


//friend: allow function to access private element


typedef std::string::size_type pos;
using pos = std::string::size_type;

// the above 2 are the same, give size_type second name as pos


