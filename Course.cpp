#include <iostream>
#include "Course.h"
#include <vector>
#include <string>
using namespace std;

Course::Course(std::string courseCode,
        std::string courseName,
        std::string year,
        std::string credit,
        std::string status,
        std::string unit,
        std::string instructor
)
{
    this -> courseCode = courseCode;
    this -> courseName = courseName;
    this -> year = year;
    this -> credit = credit;
    this -> status = status;
    this -> unit = unit;
    this -> instructor = instructor;

}

void Course::display()
{
    cout<<getCourseCode()<<" "<<getCourseName()<<" "<<getYear()<<" "<<getCredit() <<" "<<getStatus()<<" "<<getUnit()<<" "<<getStatus()<<endl;
}


bool operator== ( Course c1,  Course c2)
{

     return (c1.getCourseCode()== c2.getCourseCode() && c1.getCourseName()== c2.getCourseName());
}



void Course::addBusyTime(std::vector<std::string> busy)
{

  this->busyTimes.push_back(busy);


}
bool Course::hasBusyTime()
{
    if(this->busyTimes.size()>0)
        return true;
    else
        return false;
}


bool Course::containsBusy(std::string day,std::string time)
{
   for(int i=0;i<(int)this->busyTimes.size();i++)
   {
       if(this->busyTimes[i][1].compare(day)==0 && this->busyTimes[i][2].compare(time)==0)
        return true;
   }
   return false;
}






void Course::setCourseCode (string x)
{
    this -> courseCode = x;
}


void Course::setCourseName (string x)
{
    this -> courseName = x;
}


void Course::setYear (string x)
{
    this -> year = x;
}


void Course::setCredit (string x)
{
    this -> credit = x;
}


void Course::setStatus (string x)
{
    this -> status = x;
}


void Course::setUnit (string x)
{
    this -> unit = x;
}


void Course::setInstructor (std::string x)
{
    this -> instructor = x;
}

void Course::setDay(std::string x)
{
    this -> day =x;
}

void Course::setTime(std::string x)
{
     this -> time =x;
}

void Course::setClassroomName(std::string x)
{
     this -> classroomName =x;
}




string Course::getCourseCode ()
{
    return this -> courseCode;
}


string Course::getCourseName ()
{
   return this -> courseName ;
}


string Course::getYear ()
{
   return this -> year;
}


string Course::getCredit ()
{
    return this -> credit;
}


string Course::getStatus ()
{
    return this -> status ;
}


string Course::getUnit ()
{
   return this -> unit ;
}


string Course::getInstructor ()
{
   return this -> instructor ;
}


string Course::getDay()
{
    return this -> day ;
}


string Course::getTime()
{
    return this -> time ;
}


string Course::getClassroomName()
{
    return this -> classroomName ;
}



