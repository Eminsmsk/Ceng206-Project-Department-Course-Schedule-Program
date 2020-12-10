#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Classroom.h"
#include "Course.h"
#include "Day.h"
#include "Main.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getvectors(vector<Course> *courses,vector<Classroom> *clss,int numOfServices );

    inline  bool  isOverlap(std::string day,std::string time,std::string year);

private slots:

    void on_pushButton_3_clicked();

    void on_BT_Add_new_course__clicked();

    void on_BT_Add_Busy_course__clicked();

    void on_BT_CreateSchedule_clicked();

    void on_button_addClasses_clicked();

    void on_pushButton_bring_clicked();

private:
    Ui::MainWindow *ui;
    int bigClassSize;
    int smallClassSize;
    int flag;
    int numOfServices;
    vector<Course>  *allCourses;
    vector<Classroom> *allClassrooms;
    vector < vector < string > > busy;

};
#endif // MAINWINDOW_H
