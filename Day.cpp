#include "Day.h"
#include<string>
#include<vector>
#include<algorithm>
using namespace std;



Day::Day (std::string name,bool morning,bool afternoon)
{
    this->name = name;
    setMorning (morning);
    setAfternoon (afternoon);

}
void Day::addCourse(std::string time,std::string year)
{
    if(time.compare("Morning")==0){
        this->morningCourses.push_back(year);
        this->setMorning(false);

    }

    else{
         this->afternoonCourses.push_back(year);
         this->setAfternoon(false);
    }
}
 bool Day::containsYear(std::string time, std::string year)
 {
      if(time.compare("Morning")==0){
        if(std::find(this->morningCourses.begin(),this->morningCourses.end(),year)!=this->morningCourses.end())
            return true; //it contains
        else
            return false;
    }

    else{
          if(std::find(this->afternoonCourses.begin(),this->afternoonCourses.end(),year)!=this->afternoonCourses.end())
            return true;
        else
            return false;
    }
 }



void Day::setName(std::string x)
{
    this -> name = x;
}


void Day::setMorning (bool x)
{
    this -> morning = x;
}

void Day::setAfternoon (bool x)
{
    this -> afternoon = x;
}

std::string Day::getName()
{
    return this -> name;
}


bool Day::getAfternoon ()
{
    return this -> afternoon;
}

bool Day::getMorning ()
{
    return this -> morning;
}





Day::~Day()
{
    //dtor
}
