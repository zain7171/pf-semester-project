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
void addPatient(Patient*&, int&);
void updatePatient(Patient*, int);
void deletePatient(Patient*&, int&);
void viewPatient(Patient*, int);
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
    cout<<"============================================="<<endl;
    cout<<"        HOSPITAL MANAGEMENT SYSTEM"<<endl;
    cout<<"============================================="<<endl;
    cout<<endl;
    int id;
    string pass;
    cout<<"Enter Employee ID: ";
    cin>>id;
    cout<<"Enter Password: ";
    cin>>pass;
    while (id!=123 && pass!="pass123")
    {
        cout<<"Incorrect credentials, please try again."<<endl;
        cout<<endl;
        cout<<"Enter Employee ID: ";
        cin>>id;
        cout<<"Enter Password: ";
        cin>>pass;
    }
    cout<<endl;
    cout<<"Login Successful!"<<endl;
    cout<<endl;
    int choice;
    do
    {
        cout<<"=================== Main Menu ========================="<<endl;
        cout<<endl;
        cout<<"1) Patient Management"<<endl;
        cout<<"2) Doctor Management"<<endl;
        cout<<"3) Appointments"<<endl;
        cout<<"4) Treatments & Billing"<<endl;
        cout<<"5) Search/Reports"<<endl;
        cout<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if (choice == 6)
            break;
        else
        {
            cout<<endl;
            if (choice == 1)
            {
                int choice2;
                cout<<"You have entered Patient Management, please select an option."<<endl;
                cout<<"1) Add Patient"<<endl;
                cout<<"2) Update Patient"<<endl;
                cout<<"3) View Patient"<<endl;
                cout<<"4) Delete Patient"<<endl;
                cout<<endl;
                cout<<"Enter choice: ";
                cin>>choice2;
                if (choice2 == 1)
                    addPatient(patients,total_pat);
                else if (choice2 == 2)
                    updatePatient(patients,total_pat);
                else if (choice2 == 3)
                    viewPatient(patients,total_pat);
                else if (choice2 == 4)
                    deletePatient(patients,total_pat);
            }
        }
    } while (true);
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
void addPatient(Patient* &patients, int &count)
{
    Patient* temp = new Patient[count+1];
    for (int i=0; i<count; i++)
        temp[i] = patients[i];
    delete [] patients;
    patients = temp;
    cout<<"Enter ID: ";
    cin>>patients[count].patientId;
    cout<<"Enter age: ";
    cin>>patients[count].age;
    cin.ignore();
    cout<<"Enter name: ";
    getline(cin,patients[count].name);
    cout<<"Enter gender: ";
    getline(cin,patients[count].gender);
    cout<<"Enter contact: ";
    getline(cin,patients[count].contact);
    cout<<"Enter balance: ";
    cin>>patients[count].balance;
    count++;
}
void updatePatient(Patient* patients, int count)
{
    int check_id;
    cout<<"Enter ID to update: ";
    cin>>check_id;
    int c;
    cout<<"Select what field you want to update:"<<endl;
    cout<<"1) Patient name"<<endl;
    cout<<"2) Age"<<endl;
    cout<<"3) Gender"<<endl;
    cout<<"4) Contact"<<endl;
    cout<<"5) Balance"<<endl;
    cout<<"Enter choice: ";
    cin>>c;
    for (int i=0; i<count; i++)
    {
        if (patients[i].patientId == check_id)
        {
            if (c == 1)
            {
                cin.ignore();
                cout<<"Enter updated name: ";
                getline(cin,patients[i].name);
            }
            else if (c == 2)
            {
                cout<<"Enter updated age: ";
                cin>>patients[i].age;
            }
            else if (c == 3)
            {
                cout<<"Enter updated Gender: ";
                cin>>patients[i].gender;
            }
            else if (c == 4)
            {
                cout<<"Enter updated contact: ";
                cin>>patients[i].contact;
            }
            else if (c == 5)
            {
                cout<<"Enter updated balance: ";
                cin>>patients[i].balance;
            }
            break;
        }
    }
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create file temp.txt";
        exit(1);
    }
    char hash = '#';
    bool first = true;
    for (int i=0; i<count; i++)
    {
        if (first)
            first = false;
        else
            tempFile<<endl;
        tempFile<<patients[i].patientId<<hash
        <<patients[i].name<<hash<<patients[i].age
        <<hash<<patients[i].gender<<hash<<patients[i].contact
        <<hash<<patients[i].balance;
    }
    tempFile.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");
}
void deletePatient(Patient* &patients, int &count)
{
    int check_id;
    cout<<"Enter patient ID to delete record: ";
    cin>>check_id;
    Patient* temp = new Patient[count-1];
    int index = 0;
    for (int i=0; i<count; i++)
    {
        if (patients[i].patientId != check_id)
        {
            temp[index] = patients[i];
            index++;
        }
    }
    delete [] patients;
    patients = temp;
    count--;
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create file temp.txt"<<endl;
        exit(1);
    }
    bool first = true;
    char hash = '#';
    for (int i=0; i<count; i++)
    {
        if (first)
            first = false;
        else
            tempFile<<endl;
        tempFile<<patients[i].patientId<<hash
        <<patients[i].name<<hash<<patients[i].age
        <<hash<<patients[i].gender<<hash<<patients[i].contact
        <<hash<<patients[i].balance;
    }
    tempFile.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");
}
void viewPatient(Patient *patients, int count)
{
    int check_id;
    cout<<"Enter patient ID to view patient details: ";
    cin>>check_id;
    for (int i=0; i<count; i++)
    {
        if (patients[i].patientId == check_id)
        {
            cout<<"Patient Details: "<<endl;
            cout<<"Patient ID: "<<patients[i].patientId<<endl;
            cout<<"Patient Name: "<<patients[i].name<<endl;
            cout<<"Patient Age: "<<patients[i].age<<endl;
            cout<<"Patient Gender: "<<patients[i].gender<<endl;
            cout<<"Patient Contact: "<<patients[i].contact<<endl;
            cout<<"Patient Balance: "<<patients[i].balance<<endl;
            break;
        }
    }
}