#include"cleaning.h"
using namespace std;
struct Patient
{
    int patientId;
    string name;
    int age;
    string gender;
    string contact;
    double balance;
};
struct Doctor
{
    int doc_id;
    string name;
    string speciality;
    int experience;
};
struct Appointment
{
    int patientId;
    int doctorId;
    char date[11];
    char time[10];
};
struct Treatment
{
    int patientId;
    string description;
    double cost;
    bool paid;
};
void count_records(ifstream&, int&);
void fillPatients(ifstream&, Patient&);
void fillDoctors(ifstream&, Doctor&);
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
    int total_pat = 0;
    int total_doc = 0;
    patientFile.clear();
    patientFile.open("patients.txt");
    if (patientFile.fail())
    {
        cout<<"Failed to open file patients.txt"<<endl;
        exit(1);
    }
    count_records(patientFile,total_pat);
    patientFile.close();
    patientFile.clear();
    Patient* patients = new Patient[total_pat];
    ifstream docFile("doctors.txt");
    if (docFile.fail())
    {
        cout<<"Failed to open doctors.txt"<<endl;
        exit(1);
    }
    count_records(docFile,total_doc);
    docFile.close();
    docFile.clear();
    Doctor* doctors = new Doctor[total_doc];
    ifstream inFile("patients.txt");
    if (inFile.fail())
    {
        cout<<"Failed to open file patients.txt"<<endl;
        exit(1);
    }
    for (int i=0; i<total_pat; i++)
        fillPatients(inFile,patients[i]);
    inFile.close();
    inFile.clear();
    inFile.open("doctors.txt");
    if (inFile.fail())
    {
        cout<<"Failed to open doctors.txt"<<endl;
        exit(1);
    }
    for (int i=0; i<total_doc; i++)
        fillDoctors(inFile,doctors[i]);
    inFile.close();
    return 0;
}
void count_records(ifstream &patientFile, int &total)
{
    string line;
    while (getline(patientFile,line))
        total++;
}
void fillPatients(ifstream &inFile, Patient &p)
{
    int id,age;
    string name,gender,contact;
    double balance;
    char hash;
    inFile>>id>>hash;
    getline(inFile,name,'#');
    inFile>>age>>hash;
    getline(inFile,gender,'#');
    getline(inFile,contact,'#');
    inFile>>balance;
    p.age = age;
    p.balance = balance;
    p.contact = contact;
    p.gender = gender;
    p.name = name;
    p.patientId = id;
}
void fillDoctors(ifstream &inFile, Doctor &d)
{
    int id,experience;
    string name, speciality;
    char hash;
    inFile>>id>>hash;
    getline(inFile,name,'#');
    getline(inFile,speciality,'#');
    inFile>>experience;
    d.doc_id = id;
    d.experience = experience;
    d.name = name;
    d.speciality = speciality;
}