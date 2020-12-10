#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "Day.h"
#include <string>
#include<vector>

class Classroom
{
    public:
        Classroom();
        Classroom(std::string x,std::string y);
        ~Classroom();
        void setClassroomName( std::string x);
        void setClassroomType( std::string x);
        std::string getClassroomName();
        std::string getClassroomType();
        void display();
        bool isAvailable(std::string day,std::string time);
        void setClass(std::string day,std::string time,std::string year);
        bool isYearAvailable(std::string day,std::string time, std::string year);

    protected:

    private:
         std::string classroomName;
         std::string ClassroomType;
         vector<Day> days;
};

#endif // CLASSROOM_H
