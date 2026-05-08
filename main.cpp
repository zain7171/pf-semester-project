#include"cleaning.h"
#include<cstring>
using namespace std;

// Patient structure to store patient details
struct Patient
{
    int patientId;
    string name;
    int age;
    string gender;
    string contact;
    double balance;
};

// Doctor structure to store doctor details
struct Doctor
{
    int doc_id;
    string name;
    string speciality;
    int experience;
};

// Appointment structure to store appointment details
struct Appointment
{
    int patientId;
    int doctorId;
    char date[11];
    char time[10];
};

// Treatment structure to store treatment and billing details
struct Treatment
{
    int patientId;
    string description;
    double cost;
    bool paid;
};

// Function declarations
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
    // Open appointments file and fix any 24-hour times to 12-hour AM/PM format
    fstream app_file("appointments.txt", ios::in);
    if (app_file.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    fixTime(app_file);

    // Reopen appointments file and fix any YYYY-MM-DD dates to MM-DD-YYYY format
    app_file.clear();
    app_file.open("appointments.txt", ios::in);
    if (app_file.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    fixDate(app_file);

    // Open patients file and fix gender shorthand (M -> Male, F -> Female)
    // Also removes records with missing name, contact, or invalid phone numbers
    ifstream patientFile("patients.txt");
    if (patientFile.fail())
    {
        cout<<"Failed to open file patients.txt"<<endl;
        exit(1);
    }
    fixGenderPatient(patientFile);

    // Reopen patients file and remove any records with duplicate patient IDs
    patientFile.clear();
    patientFile.open("patients.txt");
    if (patientFile.fail())
    {
        cout<<"Failed to open file patients.txt"<<endl;
        exit(1);
    }
    checkDuplicate(patientFile);

    // Count total valid patient and doctor records for dynamic memory allocation
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

    // Dynamically allocate array for patients based on count from file
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

    // Dynamically allocate array for doctors based on count from file
    Doctor* doctors = new Doctor[total_doc];

    // Load all patient records from file into the patients array
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

    // Load all doctor records from file into the doctors array
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

    // Count and load all appointment records into dynamically allocated array
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

    // Count and load all treatment records into dynamically allocated array
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

    // Display system header and prompt employee login
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

    // Keep asking for credentials until correct ID and password are entered
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

    // Main menu loop — keeps running until employee selects Exit (6)
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
            // Patient Management submenu
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
            // Doctor Management submenu
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
            // Appointments submenu
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
            // Treatments and Billing submenu
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
            // Search and Reports submenu
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

    // Free all dynamically allocated memory before program exits
    delete[] patients;
    delete[] doctors;
    delete[] appointments;
    delete[] treatments;
    return 0;
}

// Counts non-empty lines in a file to determine how many records exist
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

// Reads one patient record from file into a Patient struct
// peek() skips blank lines, ignore() clears leftover newline after reading balance
void fillPatients(ifstream &inFile, Patient &p)
{
    int id,age;
    string name,gender,contact;
    double balance;
    char hash;
    string line;
    while (inFile.peek() == '\n')
        inFile.ignore();
    inFile>>id>>hash;
    getline(inFile,name,'#');
    inFile>>age>>hash;
    getline(inFile,gender,'#');
    getline(inFile,contact,'#');
    inFile>>balance;
    inFile.ignore();
    p.age = age;
    p.balance = balance;
    p.contact = contact;
    p.gender = gender;
    p.name = name;
    p.patientId = id;
}

// Reads one doctor record from file into a Doctor struct
// peek() skips blank lines, ignore() clears leftover newline after reading experience
void fillDoctors(ifstream &inFile, Doctor &d)
{
    int id,experience;
    string name, speciality;
    char hash;
    while (inFile.peek() == '\n')
        inFile.ignore();
    inFile>>id>>hash;
    getline(inFile,name,'#');
    getline(inFile,speciality,'#');
    inFile>>experience;
    inFile.ignore();
    d.doc_id = id;
    d.experience = experience;
    d.name = name;
    d.speciality = speciality;
}

// Reads one appointment record from file into an Appointment struct
// Uses getline with '#' delimiter for date and newline for time
void fillAppointments(ifstream &inFile, Appointment &a)
{
    int patID,docID;
    char date[11];
    char time[10];
    char hash;
    while (inFile.peek() == '\n')
        inFile.ignore();
    inFile>>patID>>hash>>docID>>hash;
    inFile.getline(date,11,'#');
    inFile.getline(time,10);
    a.patientId = patID;
    a.doctorId = docID;
    strcpy(a.date, date);
    strcpy(a.time, time);
}

// Reads one treatment record from file into a Treatment struct
// Converts "true"/"false" string to bool for the paid field
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

// Adds a new patient — checks for duplicate ID and validates all fields
// Only allocates memory and writes to file after all validations pass
void addPatient(Patient* &patients, int &count)
{
    int new_id;
    cout<<"Enter ID: ";
    cin>>new_id;

    // Reject if patient ID already exists in the system
    for (int i = 0; i < count; i++)
    {
        if (patients[i].patientId == new_id)
        {
            cout<<"Error: Patient with ID "<<new_id<<" already exists."<<endl;
            return;
        }
    }
    int new_age;
    cout<<"Enter age: ";
    cin>>new_age;
    if (new_age <= 0)
    {
        cout<<"Error: Age must be greater than zero."<<endl;
        return;
    }
    cin.ignore();
    string new_name;
    cout<<"Enter name: ";
    getline(cin,new_name);
    if (new_name.empty())
    {
        cout<<"Error: Name cannot be empty."<<endl;
        return;
    }
    string new_gender;
    cout<<"Enter gender: ";
    getline(cin,new_gender);
    if (new_gender.empty())
    {
        cout<<"Error: Gender cannot be empty."<<endl;
        return;
    }
    string new_contact;
    cout<<"Enter contact: ";
    getline(cin,new_contact);
    if (new_contact.empty())
    {
        cout<<"Error: Contact cannot be empty."<<endl;
        return;
    }
    // Contact must be exactly 11 digits with no letters
    if (new_contact.length() != 11)
    {
        cout<<"Error: Contact must be exactly 11 digits."<<endl;
        return;
    }
    for (int i = 0; i < new_contact.length(); i++)
    {
        if (!isdigit(new_contact[i]))
        {
            cout<<"Error: Contact must contain digits only."<<endl;
            return;
        }
    }
    double new_balance;
    cout<<"Enter balance: ";
    cin>>new_balance;
    if (new_balance < 0)
    {
        cout<<"Error: Balance cannot be negative."<<endl;
        return;
    }

    // All validations passed — now expand array and add new patient
    Patient* temp = new Patient[count+1];
    for (int i=0; i<count; i++)
        temp[i] = patients[i];
    delete[] patients;
    patients = temp;
    patients[count].patientId = new_id;
    patients[count].age = new_age;
    patients[count].name = new_name;
    patients[count].gender = new_gender;
    patients[count].contact = new_contact;
    patients[count].balance = new_balance;

    // Append new patient record to patients.txt
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
    cout<<"Patient added successfully."<<endl;
}

// Updates a specific field of an existing patient record
// Rewrites entire patients.txt after updating the value in memory
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

    // Find the patient and update the chosen field in memory
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

    // Rewrite entire patients.txt with updated data
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

// Deletes a patient by ID — shrinks the array and rewrites patients.txt
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

    // Copy all patients except the deleted one into a new smaller array
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

    // Rewrite patients.txt without the deleted record
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

// Displays details of a single patient searched by ID
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

// Adds a new doctor — checks for duplicate ID and validates all fields
// Only allocates memory and writes to file after all validations pass
void addDoctor(Doctor* &doctors, int &count)
{
    int new_id;
    cout<<"Enter ID: ";
    cin>>new_id;

    // Reject if doctor ID already exists in the system
    for (int i=0; i<count; i++)
    {
        if (doctors[i].doc_id == new_id)
        {
            cout<<"Error: Doctor with ID "<<new_id<<" already exists."<<endl;
            return;
        }
    }
    int new_exp;
    cout<<"Enter experience: ";
    cin>>new_exp;
    if (new_exp < 0)
    {
        cout<<"Error: Experience cannot be negative."<<endl;
        return;
    }
    cin.ignore();
    string new_name;
    cout<<"Enter name: ";
    getline(cin,new_name);
    if (new_name.empty())
    {
        cout<<"Error: Name cannot be empty."<<endl;
        return;
    }
    string new_speciality;
    cout<<"Enter speciality: ";
    getline(cin,new_speciality);
    if (new_speciality.empty())
    {
        cout<<"Error: Speciality cannot be empty."<<endl;
        return;
    }

    // All validations passed — now expand array and add new doctor
    Doctor* temp = new Doctor[count+1];
    for (int i=0; i<count; i++)
        temp[i] = doctors[i];
    delete [] doctors;
    doctors = temp;
    doctors[count].doc_id = new_id;
    doctors[count].experience = new_exp;
    doctors[count].name = new_name;
    doctors[count].speciality = new_speciality;

    // Append new doctor record to doctors.txt
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
    cout<<"Doctor added successfully."<<endl;
}

// Updates a specific field of an existing doctor record
// Rewrites entire doctors.txt after updating the value in memory
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

    // Find the doctor and update the chosen field in memory
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
                cin.ignore();
            }
            break;
        }
    }

    // Rewrite entire doctors.txt with updated data
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create file temp.txt"<<endl;
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

// Deletes a doctor by ID — shrinks the array and rewrites doctors.txt
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

    // Copy all doctors except the deleted one into a new smaller array
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

    // Rewrite doctors.txt without the deleted record
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

// Displays all doctors currently loaded in memory
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

// Schedules an appointment — checks patient balance against treatment cost
// Deducts cost from balance, updates patients.txt, appends to appointments.txt
// Also adds a new treatment record for the patient
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

    // Find patient and matching treatment, check if balance is sufficient
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

    // Update patients.txt with new deducted balance
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

    // Expand appointments array and collect appointment details from user
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

    // Append new appointment to appointments.txt
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

    // Expand treatments array and add new treatment record for this appointment
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

// Cancels a specific appointment — shows all appointments for the patient
// then asks for doctor ID to identify which exact appointment to remove
void cancelAppointment(Appointment* &appointments, int &count)
{
    int check_id;
    cout<<"Enter Patient ID to cancel appointment: ";
    cin>>check_id;
    bool found = false;

    // Display all appointments for this patient so user can choose which to cancel
    for (int i=0; i<count; i++)
    {
        if (appointments[i].patientId == check_id)
        {
            found = true;
            cout<<"Appointment "<<i+1<<": Doctor ID: "<<appointments[i].doctorId
            <<" | Date: "<<appointments[i].date
            <<" | Time: "<<appointments[i].time<<endl;
        }
    }
    if (!found)
    {
        cout<<"Patient ID not found in appointments."<<endl;
        return;
    }

    // Use patient ID + doctor ID combination to identify exact appointment
    int doc_id;
    cout<<"Enter Doctor ID of appointment to cancel: ";
    cin>>doc_id;
    bool found2 = false;
    for (int i=0; i<count; i++)
    {
        if (appointments[i].patientId == check_id && appointments[i].doctorId == doc_id)
        {
            found2 = true;
            break;
        }
    }
    if (!found2)
    {
        cout<<"No appointment found for this Patient and Doctor combination."<<endl;
        return;
    }

    // Copy all appointments except the cancelled one into a new smaller array
    Appointment* temp = new Appointment[count-1];
    int index = 0;
    for (int i=0; i<count; i++)
    {
        if (appointments[i].patientId == check_id && appointments[i].doctorId == doc_id)
            continue;
        temp[index] = appointments[i];
        index++;
    }
    delete [] appointments;
    appointments = temp;
    count--;

    // Rewrite appointments.txt without the cancelled appointment
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
    cout<<"Appointment cancelled successfully."<<endl;
}

// Displays all appointments currently loaded in memory
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

// Appends the most recently added treatment (last element) to treatments.txt
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

// Displays all treatments for a specific patient searched by ID
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
            cout<<"Payment Status (1 for paid, 0 unpaid): "<<treatments[i].paid<<endl;
        }
    }
    if (t_count == 0)
        cout<<"No treatments found for this Patient ID."<<endl;
}

// Updates payment status of a specific treatment for a patient
// After updating treatments.txt, checks if ALL treatments for that patient
// are paid — only then marks the bill as Paid in bills.txt
void updatePayment(Treatment *treatments, int count)
{
    int check_id;
    cout<<"Enter Patient ID to update payment status: ";
    cin>>check_id;
    cin.ignore();
    bool found = false;
    bool found2 = false;
    string d;
    cout<<"Enter treatment: ";
    getline(cin,d);

    // Find the matching treatment and update its paid status in memory
    for (int i=0; i<count; i++)
    {
        if (treatments[i].patientId == check_id)
        {
            found = true;
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

    // Rewrite treatments.txt with updated payment status
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
        tempFile<<treatments[i].patientId<<hash
        <<treatments[i].description<<hash
        <<treatments[i].cost<<hash;
        if (treatments[i].paid == 1)
            tempFile<<"true";
        else
            tempFile<<"false";
    }
    tempFile.close();
    remove("treatments.txt");
    rename("temp.txt","treatments.txt");

    // Check if every treatment for this patient is now paid
    bool allPaid = true;
    for (int i=0; i<count; i++)
    {
        if (treatments[i].patientId == check_id && treatments[i].paid == false)
        {
            allPaid = false;
            break;
        }
    }

    // Update bills.txt — mark Paid only if all treatments are paid, otherwise keep Unpaid
    ofstream b_file("temp.txt");
    if (b_file.fail())
    {
        cout<<"Failed to create file temp.txt"<<endl;
        exit(1);
    }
    ifstream b_read("bills.txt");
    if (b_read.fail())
    {
        cout<<"Failed to open bills.txt"<<endl;
        exit(1);
    }
    int b_id;
    double b_cost;
    string b_status;
    char b_hash;
    bool b_first = true;
    while (b_read>>b_id>>b_hash>>b_cost>>b_hash>>b_status)
    {
        if (b_first)
            b_first = false;
        else
            b_file<<endl;
        if (b_id == check_id)
        {
            if (allPaid)
                b_file<<b_id<<b_hash<<b_cost<<b_hash<<"Paid";
            else
                b_file<<b_id<<b_hash<<b_cost<<b_hash<<"Unpaid";
        }
        else
            b_file<<b_id<<b_hash<<b_cost<<b_hash<<b_status;
    }
    b_read.close();
    b_file.close();
    remove("bills.txt");
    rename("temp.txt","bills.txt");
    cout<<"Payment status updated successfully."<<endl;
}

// Reads bills.txt and displays all bills with their payment status
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
    cout<<"--- All Bills ---"<<endl;
    while (billFile>>id>>hash>>total_cost>>hash>>status)
    {
        cout<<"Patient ID: "<<id<<" | Total Cost: "<<total_cost<<" | Status: "<<status<<endl;
    }
    billFile.close();
}

// Searches appointments by doctor ID and displays matching patient names
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

// Searches doctors array by specialty and displays all matching doctors
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

// Finds all appointments for a doctor then displays treatments for those patients
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

// Sorts doctors array by experience in descending order using selection sort
// Displays sorted list after sorting is complete
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