#ifndef DAY_H
#define DAY_H
#include<vector>
#include <string>

using namespace std;

class Day
{
    public:

        Day(std::string name,bool morning=true,bool afternoon=true);
        ~Day();
        void setAfternoon (bool x);
        void setMorning (bool x);
        bool getAfternoon ();
        bool getMorning ();
        void setName(std::string x);
        std::string getName();
        void addCourse(std::string time,std::string year);
        bool containsYear(std::string time, std::string year);

    protected:

    private:
        bool morning;
        bool afternoon;
        std::string name;
        vector <string> morningCourses;
        vector <string> afternoonCourses;

};

#endif // DAY_H
