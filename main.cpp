#include"cleaning.h"
#include<cstring>
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
void fillAppointments(ifstream&, Appointment&);
void fillTreatments(ifstream&, Treatment&);
void addPatient(Patient*&, int&);
void updatePatient(Patient*, int);
void deletePatient(Patient*&, int&);
void viewPatients(Patient*, int);
void addDoctor(Doctor*&, int&);
void updateDoctor(Doctor*, int);
void deleteDoctor(Doctor*&, int&);
void viewDoctors(Doctor*, int);
void scheduleAppointment(Appointment*&, int&, Patient*, int, Treatment*&, int&);
void cancelAppointment(Appointment*&, int&);
void viewAppointments(Appointment* , int);
void addTreatment(Treatment*, int);
void viewTreatments(Treatment*, int);
void updatePayment(Treatment*, int);
void generateBill();
void searchPatientsBydoc_ID(Appointment*, int, Patient*, int);
void searchDoctorBySpecialty(Doctor*, int);
void viewTreatmentsByDoctor(Appointment*, int, Treatment*, int);
void sortDoctorsByExperience(Doctor*, int);
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
    inFile.clear();
    ifstream appointmentFile("appointments.txt");
    if (appointmentFile.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    int total_app = 0;
    count_records(appointmentFile,total_app);
    appointmentFile.close();
    Appointment* appointments = new Appointment[total_app];
    inFile.open("appointments.txt");
    if (inFile.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    for (int i=0; i<total_app; i++)
        fillAppointments(inFile,appointments[i]);
    inFile.close();
    inFile.clear();
    ifstream treatFile("treatments.txt");
    if (treatFile.fail())
    {
        cout<<"Failed to open file treatments.txt"<<endl;
        exit(1);
    }
    int total_treat = 0;
    count_records(treatFile,total_treat);
    treatFile.close();
    Treatment* treatments = new Treatment[total_treat];
    inFile.open("treatments.txt");
    if (inFile.fail())
    {
        cout<<"Failed to open file treatments.txt"<<endl;
        exit(1);
    }
    for (int i=0; i<total_treat; i++)
        fillTreatments(inFile,treatments[i]);
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
    while (id!=123 || pass!="pass123")
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
        cout<<endl<<endl;
        cout<<"=================== Main Menu ========================="<<endl;
        cout<<endl;
        cout<<"1) Patient Management"<<endl;
        cout<<"2) Doctor Management"<<endl;
        cout<<"3) Appointments"<<endl;
        cout<<"4) Treatments & Billing"<<endl;
        cout<<"5) Search/Reports"<<endl;
        cout<<"6) Exit"<<endl;
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
                cout<<endl;
                cout<<"1) Add Patient"<<endl;
                cout<<"2) Update Patient"<<endl;
                cout<<"3) View Patient"<<endl;
                cout<<"4) Delete Patient"<<endl;
                cout<<endl;
                cout<<"Enter choice: ";
                cin>>choice2;
                cout<<endl;
                if (choice2 == 1)
                    addPatient(patients,total_pat);
                else if (choice2 == 2)
                    updatePatient(patients,total_pat);
                else if (choice2 == 3)
                    viewPatients(patients,total_pat);
                else if (choice2 == 4)
                    deletePatient(patients,total_pat);
            }
            else if (choice == 2)
            {
                int choice2;
                cout<<"You have entered Doctor Management, please select an option:"<<endl;
                cout<<endl;
                cout<<"1) Add Doctor"<<endl;
                cout<<"2) Update Doctor"<<endl;
                cout<<"3) Delete Doctor"<<endl;
                cout<<"4) View all Doctors"<<endl;
                cout<<endl;
                cout<<"Enter choice: ";
                cin>>choice2;
                cout<<endl;
                if (choice2 == 1)
                    addDoctor(doctors,total_doc);
                else if (choice2 == 2)
                    updateDoctor(doctors,total_doc);
                else if (choice2 == 3)
                    deleteDoctor(doctors,total_doc);
                else if (choice2 == 4)
                    viewDoctors(doctors,total_doc);
            }
            else if (choice == 3)
            {
                int choice2;
                cout<<"You have entered Appointments management, please select an option:"<<endl;
                cout<<endl;
                cout<<"1) Schedule Appointment"<<endl;
                cout<<"2) Cancel Appointment"<<endl;
                cout<<"3) View Appointments"<<endl;
                cout<<endl;
                cout<<"Enter choice: ";
                cin>>choice2;
                cout<<endl;
                if (choice2 == 1)
                    scheduleAppointment(appointments,total_app,patients,total_pat,treatments,total_treat);
                else if (choice2 == 2)
                    cancelAppointment(appointments,total_app);
                else if (choice2 == 3)
                    viewAppointments(appointments,total_app);
            }
            else if (choice == 4)
            {
                int choice2;
                cout<<"You have entered Treatments/Billing management, please select an option:"<<endl;
                cout<<endl;
                cout<<"1) View Treatments"<<endl;
                cout<<"2) Update Payment Status"<<endl;
                cout<<endl;
                cout<<"Enter choice: ";
                cin>>choice2;
                cout<<endl;
                if (choice2 == 1)
                    viewTreatments(treatments,total_treat);
                else if (choice2 == 2)
                    updatePayment(treatments,total_treat);
            }
            else if (choice == 5)
            {
                int choice2;
                cout<<"You have entered Search/Reports, please select an option:"<<endl;
                cout<<endl;
                cout<<"1) Search Patients by Doctor ID"<<endl;
                cout<<"2) Search Doctor by Specialty"<<endl;
                cout<<"3) View Treatments by Doctor"<<endl;
                cout<<"4) Generate Bill"<<endl;
                cout<<"5) Sort Doctors by Experience"<<endl;
                cout<<endl;
                cout<<"Enter choice: ";
                cin>>choice2;
                cout<<endl;
                if (choice2 == 1)
                    searchPatientsBydoc_ID(appointments,total_app,patients,total_pat);
                else if (choice2 == 2)
                    searchDoctorBySpecialty(doctors,total_doc);
                else if (choice2 == 3)
                    viewTreatmentsByDoctor(appointments,total_app,treatments,total_treat);
                else if (choice2 == 4)
                    generateBill();
                else if (choice2 == 5)
                    sortDoctorsByExperience(doctors,total_doc);
            }
        }
    } while (true);
    delete[] patients;
    delete[] doctors;
    delete[] appointments;
    delete[] treatments;
    return 0;
}
void count_records(ifstream &file, int &total)
{
    string line;
    while (getline(file,line))
    {
        if (line.empty())
            continue;
        total++;
    }
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
void fillAppointments(ifstream &inFile, Appointment &a)
{
    int patID,docID;
    char date[11];
    char time[10];
    char hash;
    inFile>>patID>>hash>>docID>>hash;
    inFile.getline(date,11,'#');
    inFile.getline(time,10);
    a.patientId = patID;
    a.doctorId = docID;
    strcpy(a.date, date);
    strcpy(a.time, time);
}
void fillTreatments(ifstream &inFile, Treatment &t)
{
    int patID;
    string desc;
    double cost;
    string p;
    char hash;
    inFile>>patID>>hash;
    getline(inFile,desc,'#');
    inFile>>cost>>hash>>p;
    t.patientId = patID;
    t.description = desc;
    t.cost = cost;
    if (p == "true")
        t.paid = true;
    else
        t.paid = false;
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
    ofstream appFile("patients.txt", ios::app);
    if (appFile.fail())
    {
        cout<<"Failed to open file patients.txt"<<endl;
        exit(1);
    }
    char hash = '#';
    appFile<<endl;
    appFile<<patients[count].patientId<<hash
    <<patients[count].name<<hash
    <<patients[count].age<<hash
    <<patients[count].gender<<hash
    <<patients[count].contact<<hash
    <<patients[count].balance;
    appFile.close();
    count++;
}
void updatePatient(Patient* patients, int count)
{
    int check_id;
    cout<<"Enter ID to update: ";
    cin>>check_id;
    bool found = false;
    for (int i=0; i<count; i++)
    {
        if (patients[i].patientId == check_id)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout<<"Patient ID not found."<<endl;
        return;
    }
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
    bool found = false;
    for (int i=0; i<count; i++)
    {
        if (patients[i].patientId == check_id)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout<<"Patient ID not found."<<endl;
        return;
    }
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
void viewPatients(Patient *patients, int count)
{
    int check_id;
    cout<<"Enter Patient ID to view: ";
    cin>>check_id;
    bool found = false;
    for (int i=0; i<count; i++)
    {
        if (patients[i].patientId == check_id)
        {
            found = true;
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
    if (!found)
        cout<<"Patient ID not found."<<endl;
}
void addDoctor(Doctor* &doctors, int &count)
{
    Doctor* temp = new Doctor[count+1];
    for (int i=0; i<count; i++)
        temp[i] = doctors[i];
    delete [] doctors;
    doctors = temp;
    cout<<"Enter ID: ";
    cin>>doctors[count].doc_id;
    cin.ignore();
    cout<<"Enter name: ";
    getline(cin,doctors[count].name);
    cout<<"Enter speciality: ";
    getline(cin,doctors[count].speciality);
    cout<<"Enter experience: ";
    cin>>doctors[count].experience;
    ofstream appFile("doctors.txt", ios::app);
    if (appFile.fail())
    {
        cout<<"Failed to open file doctors.txt"<<endl;
        exit(1);
    }
    char hash = '#';
    appFile<<endl;
    appFile<<doctors[count].doc_id<<hash
    <<doctors[count].name<<hash
    <<doctors[count].speciality<<hash
    <<doctors[count].experience;
    appFile.close();
    count++;
}
void updateDoctor(Doctor* doctors, int count)
{
    int check_id;
    cout<<"Enter ID to update: ";
    cin>>check_id;
    bool found = false;
    for (int i=0; i<count; i++)
    {
        if (doctors[i].doc_id == check_id)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout<<"Doctor ID not found."<<endl;
        return;
    }
    int c;
    cout<<"Select what field you want to update:"<<endl;
    cout<<"1) Doctor Name"<<endl;
    cout<<"2) Doctor Speciality"<<endl;
    cout<<"3) Doctor Experience"<<endl;
    cout<<"Enter choice: ";
    cin>>c;
    for (int i=0; i<count; i++)
    {
        if (doctors[i].doc_id == check_id)
        {
            if (c == 1)
            {
                cin.ignore();
                cout<<"Enter updated name: ";
                getline(cin,doctors[i].name);
            }
            else if (c == 2)
            {
                cin.ignore();
                cout<<"Enter updated speciality: ";
                getline(cin,doctors[i].speciality);
            }
            else if (c == 3)
            {
                cout<<"Enter updated experience: ";
                cin>>doctors[i].experience;
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
        tempFile<<doctors[i].doc_id<<hash
        <<doctors[i].name<<hash<<doctors[i].speciality
        <<hash<<doctors[i].experience;
    }
    tempFile.close();
    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");
}
void deleteDoctor(Doctor* &doctors, int &count)
{
    int check_id;
    cout<<"Enter doctor ID to delete record: ";
    cin>>check_id;
    bool found = false;
    for (int i=0; i<count; i++)
    {
        if (doctors[i].doc_id == check_id)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout<<"Doctor ID not found."<<endl;
        return;
    }
    Doctor* temp = new Doctor[count-1];
    int index = 0;
    for (int i=0; i<count; i++)
    {
        if (doctors[i].doc_id != check_id)
        {
            temp[index] = doctors[i];
            index++;
        }
    }
    delete [] doctors;
    doctors = temp;
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
        tempFile<<doctors[i].doc_id<<hash
        <<doctors[i].name<<hash<<doctors[i].speciality
        <<hash<<doctors[i].experience;
    }
    tempFile.close();
    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");
}
void viewDoctors(Doctor *doctors, int count)
{
    bool first = true;
    for (int i=0; i<count; i++)
    {
        if (first)
            first = false;
        else
            cout<<endl;
        cout<<"Doctor "<<i+1<<" Details:"<<endl;
        cout<<"Doctor ID: "<<doctors[i].doc_id<<endl;
        cout<<"Doctor Name: "<<doctors[i].name<<endl;
        cout<<"Doctor Speciality: "<<doctors[i].speciality<<endl;
        cout<<"Doctor Experience: "<<doctors[i].experience<<endl;
    }
}
void scheduleAppointment(Appointment*& appointments, int &count, Patient* patients, int total_pat, Treatment*& treatments, int &total_treat)
{
    int check_id;
    cout<<"Enter Patient ID: ";
    cin>>check_id;
    cin.ignore();
    string tr;
    cout<<"Enter Treatment: ";
    getline(cin,tr);
    double tr_cost = 0;
    bool found = false;
    for (int i=0; i<total_pat; i++)
    {
        if (patients[i].patientId == check_id)
        {
            for (int j=0; j<total_treat; j++)
            {
                if (treatments[j].description == tr)
                {
                    found = true;
                    if (patients[i].balance < treatments[j].cost)
                    {
                        cout<<"Insufficient balance, appointment denied."<<endl;
                        return;
                    }
                    tr_cost = treatments[j].cost;
                    patients[i].balance -= treatments[j].cost;
                    break;
                }
            }
            break;
        }
    }
    if (!found)
    {
        cout<<"Patient or Treatment not found."<<endl;
        return;
    }
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create temp.txt"<<endl;
        exit(1);
    }
    bool first = true;
    char hash = '#';
    for (int i=0; i<total_pat; i++)
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
    rename("temp.txt","patients.txt");
    Appointment* temp = new Appointment[count+1];
    for (int i=0; i<count; i++)
        temp[i] = appointments[i];
    delete [] appointments;
    appointments = temp;
    appointments[count].patientId = check_id;
    cout<<"Enter Doctor ID: ";
    cin>>appointments[count].doctorId;
    cout<<"Enter Date: ";
    cin.ignore();
    cin.getline(appointments[count].date,11);
    cout<<"Enter Time: ";
    cin.getline(appointments[count].time,10);
    ofstream appFile("appointments.txt", ios::app);
    if (appFile.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    appFile<<endl;
    appFile<<appointments[count].patientId<<hash
    <<appointments[count].doctorId<<hash
    <<appointments[count].date<<hash
    <<appointments[count].time;
    appFile.close();
    count++;
    Treatment* ttemp = new Treatment[total_treat+1];
    for (int i=0; i<total_treat; i++)
        ttemp[i] = treatments[i];
    delete [] treatments;
    treatments = ttemp;
    treatments[total_treat].patientId = check_id;
    treatments[total_treat].description = tr;
    treatments[total_treat].cost = tr_cost;
    treatments[total_treat].paid = true;
    total_treat++;
    addTreatment(treatments,total_treat);
}
void cancelAppointment(Appointment* &appointments, int &count)
{
    int check_id;
    cout<<"Enter Patient ID to cancel appointment: ";
    cin>>check_id;
    bool found = false;
    for (int i=0; i<count; i++)
    {
        if (appointments[i].patientId == check_id)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout<<"Patient ID not found in appointments."<<endl;
        return;
    }
    Appointment* temp = new Appointment[count-1];
    int index = 0;
    for (int i=0; i<count; i++)
    {
        if (appointments[i].patientId != check_id)
        {
            temp[index] = appointments[i];
            index++;
        }
    }
    delete [] appointments;
    appointments = temp;
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
        tempFile<<appointments[i].patientId<<hash
        <<appointments[i].doctorId<<hash
        <<appointments[i].date<<hash
        <<appointments[i].time;
    }
    tempFile.close();
    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");
}
void viewAppointments(Appointment *appointments, int count)
{
    bool first = true;
    for (int i=0; i<count; i++)
    {
        if (first)
            first = false;
        else
            cout<<endl;
        cout<<"Appointment "<<i+1<<" Details: "<<endl;
        cout<<"Patient ID: "<<appointments[i].patientId<<endl;
        cout<<"Doctor ID: "<<appointments[i].doctorId<<endl;
        cout<<"Appointment Date: "<<appointments[i].date<<endl;
        cout<<"Appointment Time: "<<appointments[i].time<<endl;
    }
}
void addTreatment(Treatment* treatments, int count)
{
    ofstream treatFile("treatments.txt", ios::app);
    if (treatFile.fail())
    {
        cout<<"Failed to open file treatments.txt"<<endl;
        exit(1);
    }
    char hash = '#';
    treatFile<<endl;
    treatFile<<treatments[count-1].patientId<<hash
    <<treatments[count-1].description<<hash
    <<treatments[count-1].cost<<hash
    <<treatments[count-1].paid;
}
void viewTreatments(Treatment* treatments, int count)
{
    int check_id;
    cout<<"Enter Patient ID to display treatments for: ";
    cin>>check_id;
    cout<<"Treatment Details for Patient "<<check_id<<":"<<endl;
    int t_count = 0;
    bool first = true;
    for (int i=0; i<count; i++)
    {
        if (treatments[i].patientId == check_id)
        {
            if (first)
                first = false;
            else
                cout<<endl;
            t_count++;
            cout<<"Treatment: "<<t_count<<" Description: "<<treatments[i].description<<endl;
            cout<<"Cost: "<<treatments[i].cost<<endl;
            cout<<"Payment Status (true for paid, false unpaid): "<<treatments[i].paid<<endl;
        }
    }
    if (t_count == 0)
        cout<<"No treatments found for this Patient ID."<<endl;
}
void updatePayment(Treatment *treatments, int count)
{
    int check_id;
    cout<<"Enter Patient ID to update payment status: ";
    cin>>check_id;
    cin.ignore();
    bool found = false;
    bool found2 = false;
    for (int i=0; i<count; i++)
    {
        if (treatments[i].patientId == check_id)
        {
            string d;
            found = true;
            cout<<"Patient ID found."<<endl;
            cout<<"Enter treatment: ";
            getline(cin,d);
            if (treatments[i].description == d)
            {
                found2 = true;
                cout<<"Treatment found."<<endl;
                bool p;
                cout<<"Enter updated payment status (0 for false, 1 for true): ";
                cin>>p;
                treatments[i].paid = p;
                break;
            }
        }
    }
    if (!found)
    {
        cout<<"Patient ID not found"<<endl;
        return;
    }
    if (!found2)
    {
        cout<<"Treatment not found"<<endl;
        return;
    }
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create file temp.txt"<<endl;
        exit(1);
    }
    bool first = true;
    for (int i=0; i<count; i++)
    {
        if (first)
            first = false;
        else
            tempFile<<endl;
        char hash = '#';
        tempFile<<treatments[i].patientId<<hash<<treatments[i].description
        <<hash<<treatments[i].cost<<hash<<treatments[i].paid;
    }
    tempFile.close();
    remove("treatments.txt");
    rename("temp.txt","treatments.txt");
    ifstream records("bills.txt");
    if (records.fail())
    {
        cout<<"Failed to read file bills.txt"<<endl;
        exit(1);
    }
    int id,cost;
    char hash;
    string status;
    int total = 0;
    while(records>>id)
    {
        records>>hash>>cost>>hash>>status;
        total++;
    }
    records.clear();
    records.seekg(0);
    int* arr = new int[total];
    int index = 0;
    while(records>>id)
    {
        records>>hash>>cost>>hash>>status;
        arr[index] = id;
        index++;
    }
    records.clear();
    records.seekg(0);
    ofstream temp("temp.txt");
    if (temp.fail())
    {
        cout<<"Failed to create file temp.txt";
        exit(1);
    }
    bool first2= true;
    for (int i=0; i<total; i++)
    {
        bool paid = true;
        int total_cost = 0;
        for (int j=0; j<count; j++)
        {
            if(arr[i] == treatments[j].patientId)
            {
                total_cost += treatments[j].cost;
                if(treatments[j].paid == false)
                    paid = false;
            }
        }
        if (first2)
            first2 = false;
        else
            temp<<endl;
        records>>id>>hash>>cost>>hash>>status;
        if (paid)
            temp<<id<<hash<<total_cost<<hash<<"Paid";
        else
            temp<<id<<hash<<total_cost<<hash<<"Unpaid";
    }
    delete [] arr;
    records.close();
    temp.close();
    remove("bills.txt");
    rename("temp.txt", "bills.txt");
}
void generateBill()
{
    ifstream billFile("bills.txt");
    if (billFile.fail())
    {
        cout<<"Failed to open bills.txt"<<endl;
        return;
    }
    int id;
    double total_cost;
    string status;
    char hash;
    cout<<"--- Unpaid Bills ---"<<endl;
    while (billFile>>id>>hash>>total_cost>>hash>>status)
    {
        if (status == "Unpaid")
        {
            cout<<"Patient ID: "<<id<<" | Total Cost: "<<total_cost<<" | Status: "<<status<<endl;
        }
    }
    billFile.close();
}
void searchPatientsBydoc_ID(Appointment* appointments, int total_app, Patient* patients, int total_pat)
{
    int check_id;
    cout<<"Enter Doctor ID to search for patients: ";
    cin>>check_id;
    bool found = false;
    for (int i=0; i<total_app; i++)
    {
        if (appointments[i].doctorId == check_id)
        {
            for (int j=0; j<total_pat; j++)
            {
                if (patients[j].patientId == appointments[i].patientId)
                {
                    cout<<"Patient Name: "<<patients[j].name<<" (ID: "<<patients[j].patientId<<")"<<endl;
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found)
        cout<<"No patients found for this Doctor ID."<<endl;
}
void searchDoctorBySpecialty(Doctor* doctors, int total_doc)
{
    string spec;
    cout<<"Enter Specialty to search: ";
    cin.ignore();
    getline(cin, spec);
    bool found = false;
    for (int i = 0; i < total_doc; i++)
    {
        if (doctors[i].speciality == spec)
        {
            cout<<"Doctor ID: "<<doctors[i].doc_id<<" | Name: "<<doctors[i].name<<" | Experience: "<<doctors[i].experience<<" years"<<endl;
            found = true;
        }
    }
    if (!found)
        cout<<"No doctors found with this specialty."<<endl;
}
void viewTreatmentsByDoctor(Appointment* appointments, int total_app, Treatment* treatments, int total_treat)
{
    int check_id;
    cout<<"Enter Doctor ID to view treatments given: ";
    cin>>check_id;
    bool found = false;
    for (int i=0; i<total_app; i++)
    {
        if (appointments[i].doctorId == check_id)
        {
            for (int j=0; j<total_treat; j++)
            {
                if (treatments[j].patientId == appointments[i].patientId)
                {
                    cout<<"Treatment for Patient "<<treatments[j].patientId<<": "<<treatments[j].description<<endl;
                    found = true;
                }
            }
        }
    }
    if (!found)
        cout<<"No treatments recorded for this Doctor ID."<<endl;
}
void sortDoctorsByExperience(Doctor* doctors, int total_doc)
{
    for (int i=0; i < total_doc-1; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < total_doc; j++)
        {
            if (doctors[j].experience > doctors[max_index].experience)
            {
                max_index = j;
            }
        }
        Doctor temp = doctors[max_index];
        doctors[max_index] = doctors[i];
        doctors[i] = temp;
    }
    cout<<"Doctors have been sorted by years of experience using selection sort."<<endl;
    for (int i = 0; i < total_doc; i++)
    {
        cout<<"Name: "<<doctors[i].name<<" | Experience: "<<doctors[i].experience<<" years | ID: "<<doctors[i].doc_id<<endl;
    }
}