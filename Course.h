#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
class Course
{
    public:
        Course(std::string courseCode,
        std::string courseName,
        std::string year,
        std::string credit,
        std::string status,
        std::string unit,
        std::string instructor);

        void display();
        std::string getCourseCode();
        std::string getCourseName();
        std::string getYear();
        std::string getCredit();
        std::string getStatus();
        std::string getUnit();
        std::string getInstructor();
        std::string getDay();
        std::string getTime();
        std::string getClassroomName();
        void setCourseCode(std::string x);
        void setCourseName(std::string x);
        void setYear(std::string x);
        void setCredit(std::string x);
        void setStatus(std::string x);
        void setUnit(std::string x);
        void setInstructor(std::string x);
        void setDay(std::string x);
        void setTime(std::string x);
        void setClassroomName(std::string x);
        void addBusyTime(std::vector<std::string> busy);
        bool hasBusyTime();
        bool containsBusy(std::string day,std::string time);
        friend bool operator== ( Course c1,  Course c2);

    protected:

    private:
        std::string courseCode;
        std::string courseName;
        std::string year;
        std::string credit;
        std::string status;
        std::string unit;
        std::string instructor;
        std::string day;
        std::string time;
        std::string classroomName;
        std::vector< std::vector<std::string> > busyTimes;
};

#endif // COURSE_H
