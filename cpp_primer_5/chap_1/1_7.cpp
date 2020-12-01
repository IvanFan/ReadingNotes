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



