#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Day.h"
#include <string>
#include "Course.h"
#include "Classroom.h"
#include <algorithm>
#include "mainwindow.h"

#include <QApplication>

using namespace std;


bool sortService( Course &lhs,  Course &rhs) { return lhs.getUnit() > rhs.getUnit(); }


int readFile(ifstream& file, vector< vector <string> > &vect, int x=3)
{
    try
    {
        if(!file.good())
            throw -1;
         while(file.good())
        {
            vector <string> temp;
            string line;
            getline (file, line); // burda exceldeki satiri direk aliyor ; lü halini
            stringstream str (line);
            string val;
            for (int i = 0; i < x; i++)
            {
                getline (str, val, ';'); // burda o aldigimiz satiri ; ile ayirarak eleman eleman aliyoz
               temp.push_back (val); // tek satirlik vectore atiyoz
            }
            vect.push_back (temp); // burda da o tek satirlik vectorü iki boyutlu vektöre atiyoz

        }

        file.close ();
        return vect.size();
    }catch(int a)
    {
        cout << "Error When Opening The File. Error Code : " << a << endl;
        return -1;
    }

}



int main(int argc, char *argv[])
{
    ifstream coursesCsv;
    ifstream clss;
    coursesCsv.open("courses.csv");
    vector < vector < string > > info;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    vector<Classroom> allClassrooms;
    vector<Course> allCourses;


    readFile(coursesCsv,info,7);


    for (int k = 0; k <(int)info.size()-1; k++)
    {
        string courseCode= info[k][0];
        string courseName=info[k][1];
        string year=info[k][2];
        string credit=info[k][3];
        string status=info[k][4];
        string unit=info[k][5];
        string instructor=info[k][6];
        Course tempCourse(courseCode,
        courseName,
        year,
        credit,
        status,
        unit,instructor);
        allCourses.push_back(tempCourse);
    }



    vector < vector < string > > service;

    ifstream svc;

    svc.open("service.csv");
    int numOfServices =readFile(svc,service);

    std::sort(allCourses.begin(),allCourses.end(),sortService);
    w.getvectors(&allCourses,&allClassrooms,numOfServices);

    //servis derslerinin gün ve zamanlarını ayarlama
    for(int i=0;i<(int)service.size();i++){
        allCourses[i].setDay(service[i][1]);
        allCourses[i].setTime(service[i][2]);

    }





    return a.exec();



    return 0;

}
