#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include "iostream"
#include "Classroom.h"
#include "Course.h"
#include "Day.h"
#include "Main.h"
#include <QString>
#include <vector>
#include <sstream>
#include <algorithm>
#include <QMessageBox>
using namespace std;

inline bool sortCompulsory( Course &lhs,  Course &rhs) { return lhs.getStatus() < rhs.getStatus(); }
inline  bool  MainWindow::isOverlap(std::string day,std::string time,std::string year)
{

    for(int i=0;i<(int)allClassrooms->size();i++)
    {
        if(!allClassrooms->at(i).isYearAvailable(day,time,year))
            return true;
    }
    return false;
}





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::getvectors(vector<Course> *courses, vector<Classroom> *clss,int numOfServices){
    this->allCourses = courses;
    this->allClassrooms = clss;
    this->numOfServices = numOfServices;
}



void MainWindow::on_BT_Add_new_course__clicked()
{ // NEW COURSELAR EKLEME BUTONU

    string name = ui->TA_name_new_Course->text().toStdString();
    string code = ui->TA_code_new_Course->text().toStdString();
    string Instructor = ui->TA_Instructor_new_Course->text().toStdString();
    string year = ui->comboBox_year->currentText().toStdString();
    string credit =ui->Credit_Combo->currentText().toStdString();
    string department = ui->Department_Combo->currentText().toStdString();
    string status = ui->comboBox_status->currentText().toStdString();
    if(name.empty() || code.empty() || Instructor.empty())
    {
         QMessageBox::critical(this, "Warning", "ENTER ALL INFORMATION");
    }else{
    int flag=1;
    Course Course_Info(code,name,year,credit,status,department,Instructor);
    for (int i=0;i<(int)allCourses->size();i++) {
        if(allCourses->at(i)==Course_Info)
            flag=0;
    }
    if(flag){
        allCourses->push_back(Course_Info);
        QMessageBox::information(this, "Info", "THE COURSE IS ADDED!");
    }
    else
        QMessageBox::critical(this, "Warning", "THIS COURSE ALREADY EXISTS!");
    }
     ui->TA_name_new_Course->setText("");
     ui->TA_code_new_Course->setText("");
     ui->TA_Instructor_new_Course->setText("");
     ui->comboBox_year->setCurrentIndex(-1);
     ui->Credit_Combo->setCurrentIndex(-1);
     ui->Department_Combo->setCurrentIndex(-1);
     ui->comboBox_status->setCurrentIndex(-1);
}



void MainWindow::on_pushButton_3_clicked()
{
   string combo = ui->comboBox_REmove->currentText().toStdString();

    for(int i=0;i<(int)allCourses->size();i++) {

        if(  allCourses->at(i).getCourseCode().compare(combo)== 0  )  {

            allCourses->erase(allCourses->begin()+i);
        }
    }


}

void MainWindow::on_button_addClasses_clicked()
{
    if(!ui->TA_Big_Class->text().toStdString().empty() && !ui->TA_Small_Class->text().toStdString().empty()){
    allClassrooms->clear();
    int x;
    string tmp;
    tmp= ui->TA_Big_Class->text().toStdString();
    stringstream s1(tmp); // bu iki satır stringi integera çevirmek için.
    s1 >> x;
    this->bigClassSize = x;


    tmp= ui->TA_Small_Class->text().toStdString();
    stringstream s2(tmp); // bu iki satır stringi integera çevirmek için.
    s2 >> x;
    this->smallClassSize=x;

    for(int i=1;i<=bigClassSize;i++){
        string bigClass = "bigClass";
        stringstream numOfclass;
        numOfclass << i;
        string number = numOfclass.str();
        Classroom c(bigClass.append(number),bigClass);
        this->allClassrooms->push_back(c);
    }


    for(int i=1;i<=smallClassSize;i++){
        string smallClass = "smallClass";
        stringstream numOfclass;
        numOfclass << i;
        string number = numOfclass.str();
        Classroom c(smallClass.append(number),smallClass);
        this->allClassrooms->push_back(c);
    }
     QMessageBox::information(this, "Info", "THE CLASSES ARE ADDED!");
    }
    else{
        QMessageBox::critical(this, "Warning", "ENTER NUMBER OF CLASSES!");
    }
}

void MainWindow::on_BT_Add_Busy_course__clicked()
{
    vector <string> temp;
    temp.push_back(ui->Busy_Courses_comboBox->currentText().toStdString());
    temp.push_back(ui->busy_days_combo->currentText().toStdString());
    temp.push_back(ui->comboBox_time->currentText().toStdString());
    for(int i=0;i<(int)allCourses->size();i++)
    {

            if(ui->Busy_Courses_comboBox->currentText().toStdString().compare(allCourses->at(i).getCourseCode())==0)
            {
                allCourses->at(i).addBusyTime(temp);
                break;
            }


    }

}

void MainWindow::on_BT_CreateSchedule_clicked()
{
     ui->textEdit->setText("");
     std::sort(allCourses->begin()+numOfServices-1,allCourses->end(),sortCompulsory);

     cout<<"\n\n\n\n---------COURSES-------------"<<endl;
     cout << "Total # of Courses : " << allCourses->size() << endl;
     for(int z=0;z<(int)allCourses->size();z++){
         allCourses->at(z).display();
     }



     bool flag;
     vector <std::string> tempDays;
     tempDays.push_back("Monday");
     tempDays.push_back("Tuesday");
     tempDays.push_back("Wednesday");
     tempDays.push_back("Thursday");
     tempDays.push_back("Friday");
     vector <std::string> tempTimes;
     tempTimes.push_back("Morning");
     tempTimes.push_back("Afternoon");



     if(allClassrooms->size()>0)
     {




     //service dersleri
     int startingSmall = this->bigClassSize;
      cout<<"Classroom number: "<<allClassrooms->size()<<endl;
     for(int i=0;i<(int)(numOfServices-1);i++){
             if(allCourses->at(i).getStatus().compare("C")==0){

                   for(int z=0;z<bigClassSize;z++)
                     {
                         if(allClassrooms->at(z).isAvailable(allCourses->at(i).getDay(),allCourses->at(i).getTime()))
                             {
                                 allClassrooms->at(z).setClass(allCourses->at(i).getDay(),allCourses->at(i).getTime(),allCourses->at(i).getYear());
                                 allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());

                                     break;
                             }
                     }
             }
             else{
                 for(int j=startingSmall;j<(int)allClassrooms->size();j++){
                     if(allClassrooms->at(j).isAvailable(allCourses->at(i).getDay(),allCourses->at(i).getTime()))
                         {
                             allClassrooms->at(j).setClass(allCourses->at(i).getDay(),allCourses->at(i).getTime(),allCourses->at(i).getYear());
                             allCourses->at(i).setClassroomName(allClassrooms->at(j).getClassroomName());
                             break;
                         }

                 }
                  if(allCourses->at(i).getClassroomName().size()==0){
                        for(int z=0;z<bigClassSize;z++)
                         {
                         if(allClassrooms->at(z).isAvailable(allCourses->at(i).getDay(),allCourses->at(i).getTime()))
                             {
                                 allClassrooms->at(z).setClass(allCourses->at(i).getDay(),allCourses->at(i).getTime(),allCourses->at(i).getYear());
                                 allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());

                                     break;
                             }
                         }


                     }




             }


     }


     //busy dersler
     for(int i=(int)numOfServices-1;i<(int)allCourses->size();i++)
     {
         flag=false;
         if(allCourses->at(i).hasBusyTime()){
         for(int j=0;j<5;j++)        //5gün
             {
                 for(int k=0;k<2;k++)    //2vakit
                 {
                     if(!isOverlap(tempDays[j],tempTimes[k],allCourses->at(i).getYear())&&!allCourses->at(i).containsBusy(tempDays[j],tempTimes[k]))   //çakışma ve busy time yoksa
                     {
                       if(allCourses->at(i).getStatus().compare("C")==0){ //Compulsory ders ise büyük sınıflardan boş olana ata

                          for(int z=0;z<bigClassSize;z++)
                         {
                             if(allClassrooms->at(z).isAvailable(tempDays[j],tempTimes[k]))
                             {
                                 allCourses->at(i).setDay(tempDays[j]);
                                 allCourses->at(i).setTime(tempTimes[k]);
                                 allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());
                                 allClassrooms->at(z).setClass(tempDays[j],tempTimes[k],allCourses->at(i).getYear());
                                 flag=true;
                                 break;
                             }
                         }
                       }
                       else{ //Elective ders ise önce küçük sınıf bak eğer yoksa büyük sınıflara bak.

                         for(int z=startingSmall;z<(int)allClassrooms->size();z++){
                             if(allClassrooms->at(z).isAvailable(tempDays[j],tempTimes[k]))
                             {
                                 allCourses->at(i).setDay(tempDays[j]);
                                 allCourses->at(i).setTime(tempTimes[k]);
                                 allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());
                                 allClassrooms->at(z).setClass(tempDays[j],tempTimes[k],allCourses->at(i).getYear());
                                 flag=true;
                                 break;
                             }

                         }
                         if(allCourses->at(i).getClassroomName().size()==0){
                             for(int z=0;z<bigClassSize;z++)
                             {
                                 if(allClassrooms->at(z).isAvailable(tempDays[j],tempTimes[k]))
                                 {
                                     allCourses->at(i).setDay(tempDays[j]);
                                     allCourses->at(i).setTime(tempTimes[k]);
                                     allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());
                                     allClassrooms->at(z).setClass(tempDays[j],tempTimes[k],allCourses->at(i).getYear());
                                     flag=true;
                                     break;
                                 }
                             }
                         }

                       }
                     }

                     if(flag==true){break;}
                 }
                  if(flag==true){break;}
             }
             }
             startingSmall=bigClassSize;
     }



     //compulsory dersler
     int startingComp = numOfServices-1;
     int endingComp = startingComp;
     for(int i=startingComp;i<(int)allCourses->size();i++)
     {
         if(allCourses->at(i).getStatus().compare("E")==0)
             break;
         endingComp++;
     }
     endingComp--;


     for(int i=startingComp;i<=endingComp;i++)
     {
         flag=false;
         if(allCourses->at(i).getClassroomName().empty())    //atanmış busy dersleri geçmek için
         {
             for(int j=0;j<5;j++)        //5gün
             {
                 for(int k=0;k<2;k++)    //2vakit
                 {
                     if(!isOverlap(tempDays[j],tempTimes[k],allCourses->at(i).getYear()))   //çakışma yoksa
                     {
                         for(int z=0;z<bigClassSize;z++)
                         {
                             if(allClassrooms->at(z).isAvailable(tempDays[j],tempTimes[k]))
                             {
                                 allCourses->at(i).setDay(tempDays[j]);
                                 allCourses->at(i).setTime(tempTimes[k]);
                                 allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());
                                 allClassrooms->at(z).setClass(tempDays[j],tempTimes[k],allCourses->at(i).getYear());
                                 flag=true;
                                 break;
                             }
                         }
                     }
                     if(flag==true){break;}
                 }
                  if(flag==true){break;}
             }

         }

     }




     //Elective dersler

     int startingElective=endingComp+1;
     for(int i=startingElective;i<(int)allCourses->size();i++)
     {
         flag=false;
         if(allCourses->at(i).getClassroomName().empty())
         {
              for(int j=0;j<5;j++)        //5gün
             {
                 for(int k=0;k<2;k++)    //2vakit
                 {
                     if(!isOverlap(tempDays[j],tempTimes[k],allCourses->at(i).getYear()))   //çakışma yoksa
                     {
                         for(int z=0;z<bigClassSize;z++)
                         {
                             if(allClassrooms->at(z).isAvailable(tempDays[j],tempTimes[k]))
                             {
                                 allCourses->at(i).setDay(tempDays[j]);
                                 allCourses->at(i).setTime(tempTimes[k]);
                                 allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());
                                 allClassrooms->at(z).setClass(tempDays[j],tempTimes[k],allCourses->at(i).getYear());
                                 flag=true;
                                 break;
                             }
                         }

                           if(allCourses->at(i).getClassroomName().size()==0){
                             for(int z=startingSmall;z<(int)allClassrooms->size();z++){
                                 if(allClassrooms->at(z).isAvailable(tempDays[j],tempTimes[k]))
                                 {
                                     allCourses->at(i).setDay(tempDays[j]);
                                     allCourses->at(i).setTime(tempTimes[k]);
                                     allCourses->at(i).setClassroomName(allClassrooms->at(z).getClassroomName());
                                     allClassrooms->at(z).setClass(tempDays[j],tempTimes[k],allCourses->at(i).getYear());
                                     flag=true;
                                     break;
                                 }

                             }

                           }



                     }
                     if(flag==true){break;}
                 }
                  if(flag==true){break;}
             }

         }


     }
    int isCreated = 1;
    for(int i=0;i<(int)allCourses->size();i++)
    {
     if(allCourses->at(i).getClassroomName().empty())
        isCreated=0;
    }
    string x="";
    if(isCreated){
        ui->textEdit->setText("Courses And Classrooms\n-------------------------\n");
        flag=false;
        for(int i=0;i<5;i++){

            for(int j=0;j<2;j++){
                for(int z=0;z<(int)allCourses->size();z++){
                    if(allCourses->at(z).getDay().compare(tempDays[i])==0 && allCourses->at(z).getTime().compare(tempTimes[j])==0 )
                        x += allCourses->at(z).getDay()+" "+allCourses->at(z).getTime()+" "+allCourses->at(z).getYear()+".year "
                               +allCourses->at(z).getClassroomName()+" "
                       +allCourses->at(z).getCourseCode()+" "+allCourses->at(z).getStatus()+" "+allCourses->at(z).getUnit()+"\n";

                    }
                    x+="\n";
                if(flag==true){break;}
            }

            if(flag==true){break;}
        }

    }
    else{
       x+="The schedule cannot be created!";
    }

    ui->textEdit->append(QString::fromStdString(x));


    //Objeleri temizle
    for(int i=0;i<(int)allCourses->size();i++)
    {
        if(allCourses->at(i).getUnit().compare("S")==0)
            allCourses->at(i).setClassroomName("");
        else{
            allCourses->at(i).setDay("");
            allCourses->at(i).setTime("");
            allCourses->at(i).setClassroomName("");
        }
    }
    }
     else
     {
         ui->textEdit->setText("Add Classrooms first!");
     }

    allClassrooms->clear();
    ui->TA_Big_Class->setText("");
    ui->TA_Small_Class->setText("");



}








void MainWindow::on_pushButton_bring_clicked()
{

    for (int i=numOfServices-1;i<(int)allCourses->size();i++) {
        string x = allCourses->at(i).getCourseCode();
        ui->Busy_Courses_comboBox->addItem(QString::fromStdString(x));
    }


}
