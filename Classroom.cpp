#include "Classroom.h"
#include <iostream>
#include "Day.h"
#include <string>
using namespace std;

Classroom::Classroom()
{
    //ctor
}

Classroom::Classroom(std::string x,std::string y)
{
    this->classroomName=x;
    this->ClassroomType=y;

    this->days.push_back(Day("Monday"));
    this->days.push_back(Day("Tuesday"));
    this->days.push_back(Day("Wednesday"));
    this->days.push_back(Day("Thursday"));
    this->days.push_back(Day("Friday"));

}

Classroom::~Classroom()
{

}



void Classroom::display()
{
    cout<<"Classroom Name: "<<getClassroomName()<<"\n"<<"Classroom Type: "<<getClassroomType()<<endl;
}

bool Classroom::isYearAvailable(std::string day,std::string time, std::string year)
{
    if(day.compare("Monday")==0){

          return !(this->days[0].containsYear(time,year));

   }
   else if(day.compare("Tuesday")==0){

         return !(this->days[1].containsYear(time,year));

   }
   else if(day.compare("Wednesday")==0){

            return !(this->days[2].containsYear(time,year));

   }
   else if(day.compare("Thursday")==0){

            return !(this->days[3].containsYear(time,year));

   }
   else{
           return !(this->days[4].containsYear(time,year));

   }

}



bool Classroom::isAvailable(std::string day,std::string time)
{
   if(day.compare("Monday")==0  ){
        if(time.compare("Morning")==0)
            return this->days[0].getMorning();
        else
            return this->days[0].getAfternoon();
   }
   else if(day.compare("Tuesday")==0){
        if(time.compare("Morning")==0)
            return this->days[1].getMorning();
        else
            return this->days[1].getAfternoon();
   }
   else if(day.compare("Wednesday")==0){
        if(time.compare("Morning")==0)
            return this->days[2].getMorning();
        else
            return this->days[2].getAfternoon();
   }
   else if(day.compare("Thursday")==0){
        if(time.compare("Morning")==0)
            return this->days[3].getMorning();
        else
            return this->days[3].getAfternoon();
   }
   else{
        if(time.compare("Morning")==0)
            return this->days[4].getMorning();
        else
            return this->days[4].getAfternoon();
   }


}
void Classroom::setClass(std::string day,std::string time,std::string year)
{
    if(day.compare("Monday")==0){

            this->days[0].addCourse(time,year);

   }
   else if(day.compare("Tuesday")==0){

             this->days[1].addCourse(time,year);

   }
   else if(day.compare("Wednesday")==0){

            this->days[2].addCourse(time,year);

   }
   else if(day.compare("Thursday")==0){

            this->days[3].addCourse(time,year);

   }
   else{
             this->days[4].addCourse(time,year);

   }

}




 void Classroom::setClassroomName( std::string x)
 {
     this->classroomName = x;
 }

void Classroom::setClassroomType( std::string x)
{

      this->ClassroomType=x;
}

std::string Classroom::getClassroomName()
{
    return this->classroomName;
}

std::string Classroom::getClassroomType()
{
    return this->ClassroomType;
}
