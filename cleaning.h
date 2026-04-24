#ifndef CLEANING_H
#define CLEANING_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
void fixTime(fstream &timeFile)
{
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create file temp.txt"<<endl;
        exit(1);
    }
    string line;
    int hash = 0;
    while (true)
    {
        if (timeFile.peek() == -1)
            break;
        else
        {
            while (hash!=3 && getline(timeFile,line,'#'))
            {
                hash++;
                tempFile<<line<<'#';
            }
            int num;
            char colon;
            int mins;
            bool less_mins = false;
            timeFile>>num>>colon>>mins;
            if (mins < 10)
                less_mins = true;
            char check = timeFile.peek();
            if (check == ' ')
            {
                string end;
                timeFile>>end;
                if (less_mins)
                    tempFile<<num<<colon<<0<<mins<<" "<<end;
                else
                    tempFile<<num<<colon<<mins<<" "<<end;
            }
            else
            {
                if (num > 12)
                {
                    num = num - 12;
                    if (less_mins)
                        tempFile<<num<<colon<<0<<mins<<" PM";
                    else
                        tempFile<<num<<colon<<mins<<" PM";  
                }
                else if (num < 12)
                {
                    if (less_mins)
                        tempFile<<num<<colon<<0<<mins<<" AM";
                    else
                        tempFile<<num<<colon<<mins<<" AM";
                }
            }
            hash = 0;
        }
    }
    tempFile.close();
    timeFile.close();
    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");
}
void fixDate(fstream &dateFile)
{
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create file temp.txt"<<endl;
        exit(1);
    }
    bool first = true;
    while (true)
    {
        if (dateFile.peek() == -1)
            break;
        else
        {
            if (first)
                first = false;
            else
                tempFile<<endl;
            int x,y;
            char hash;
            dateFile>>x>>hash>>y>>hash;
            tempFile<<x<<hash<<y<<hash;
            int month;
            char dash;
            int date;
            int year;
            dateFile>>month;
            if (month > 12)
            {
                year = month;
                dateFile>>dash>>month>>dash>>date;
                tempFile<<month<<dash<<date<<dash<<year;
                string s;
                getline(dateFile,s);
                tempFile<<s;
            }
            else
            {
                dateFile>>dash>>date>>dash>>year;
                tempFile<<month<<dash<<date<<dash<<year;
                string s;
                getline(dateFile,s);
                tempFile<<s;
            }
        }
    }
    tempFile.close();
    dateFile.close();
    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");
}
void fixGenderPatient(ifstream &genderFile)
{
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout << "Failed to create file temp.txt" << endl;
        exit(1);
    }
    string line;
    bool firstRecord = true;
    while (true)
    {
        if (genderFile.peek() == -1)
            break;
        else
        {
            getline(genderFile, line);
            string tokens[10];
            for(int i = 0; i < 10; i++) tokens[i] = "";
            int count = 0;
            string currentToken = "";
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == '#')
                {
                    if (count < 10) tokens[count++] = currentToken;
                    currentToken = "";
                }
                else
                    currentToken += line[i];
            }
            if (count < 10) tokens[count++] = currentToken;
            string id = tokens[0];
            string name = "", age = "", gender = "", contact = "";
            string balance = tokens[count - 1];
            bool isValid = true;
            for (int i = 1; i < count - 1; i++)
            {
                string t = tokens[i];
                if (t == "")
                    continue;
                if (t == "M" || t == "m" || t == "Male")
                    gender = "Male";
                else if (t == "F" || t == "f" || t == "Female")
                    gender = "Female";
                else if (isdigit(t[0]) && t.length() <= 3)
                    age = t;
                else if (isdigit(t[0]) && t.length() > 6)
                {
                    for(int j = 0; j < t.length(); j++)
                    {
                        if(!isdigit(t[j])) isValid = false;
                    }
                    contact = t;
                }
                else
                    name = t;
            }
            if (id == "" || name == "" || contact == "")
                isValid = false;
            if (contact.length() < 11)
                isValid = false;
            if (isValid)
            {
                if (!firstRecord)
                    tempFile << endl;
                tempFile << id << "#" << name << "#" << age << "#" << gender << "#" << contact << "#" << balance;
                firstRecord = false;
            }
        }
    }
    tempFile.close();
    genderFile.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");
}
#endif