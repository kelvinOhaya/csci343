// This program shows an example of Open Record, all content are public!
// compiled with g++ -std=c++1z EmployeeRecord.h
// OpenRecord to store Employee Records.

#pragma once
#include <string>
#include <iostream>

using namespace std;

//
// Create EmployeeRecord
//
class EmployeeRecord
{
   // EEID,Full Name,Job Title,Gender,Age,Annual Salary,City,
public:
   string name;
   string address;
   string jobTitle;
   string gender;
   string city;
   int age;
   int salary;

   EmployeeRecord() : age(0), salary(0) {}
   ~EmployeeRecord() {}

   void clear(void)
   {
      name = "";
      address = "";
      jobTitle = "";
      gender = "";
      city = "";
      age = 0;
      salary = 0;
   } // clear

   EmployeeRecord &operator=(EmployeeRecord &rhs)
   {
      name = rhs.name;
      address = rhs.address;
      jobTitle = rhs.jobTitle;
      city = rhs.city;
      age = rhs.age;
      salary = rhs.salary;

      return *this;
   } // operator =

   void transferFrom(EmployeeRecord &source)
   {
      name = source.name;
      address = source.address;
      jobTitle = source.jobTitle;
      city = source.city;
      age = source.age;
      salary = source.salary;
   } // transferFrom

   // overloading the output operator.The outputSequence function will make use
   // of this. Must be friend becuse EmployeeRecord is not primitive type.

   friend ostream &operator<<(ostream &os, EmployeeRecord &r)
   {
      os << "Employee: " << r.name << "\nAge: " << r.age << "\nAddress: " << r.address << "\nJob: " << r.jobTitle << "\nCity: " << r.city << "\nSalary: " << r.salary << "\n";
      return os;
   } // operator <<
};
