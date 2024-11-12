#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include<string>
using namespace std;

class Employee 
{
public:

    Employee() : name(""), salary(0.0) {} 

    Employee(const std::string& employeeName, double employeeSalary) 
        : name(employeeName), salary(employeeSalary) {}

    const string & getName( ) const
    { return name; } 

    const double & getSalary( ) const
    { return salary; } 

bool operator==( const Employee & rhs ) const 
{ return getName( ) == rhs.getName( ); } 

bool operator!=( const Employee & rhs ) const 
{ return !( *this == rhs ); }

private: 
    string name; 
    double salary; 
};


template<>
class hash<Employee> 
{
public:
    size_t operator()( const Employee &item )
    {
        static hash<string> hf;
        return hf( item.getName( ) );
    }
};

#endif
