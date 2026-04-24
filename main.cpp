#include"cleaning.h"
using namespace std;
int main ()
{
    fstream app_file("appointments.txt", ios::in);
    if (app_file.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    fixTime(app_file);
    app_file.clear();
    app_file.open("appointments.txt", ios::in);
    if (app_file.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    fixDate(app_file);
    ifstream patientFile("patients.txt");
    if (patientFile.fail())
    {
        cout<<"Failed to open file patients.txt"<<endl;
        exit(1);
    }
    fixGenderPatient(patientFile);
    patientFile.clear();
    patientFile.open("patients.txt");
    if (patientFile.fail())
    {
        cout<<"Failed to open file patients.txt"<<endl;
        exit(1);
    }
    checkDuplicate(patientFile);
    return 0;
}