#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;
void fixTime(fstream&);
int main ()
{
    fstream timeFile("appointments.txt", ios::in);
    if (timeFile.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    fixTime(timeFile);
    return 0;
}
void fixTime(fstream &timeFile)
{
    ofstream tempFile("temp.txt");
    if (tempFile.fail())
    {
        cout<<"Failed to create file temp.txt"<<endl;
        exit(1);
    }
    string extra;
    int hash = 0;
    while (true)
    {
        if (timeFile.peek() == -1)
            break;
        while (hash!=3 && getline(timeFile,extra,'#'))
        {
            hash++;
            tempFile<<extra<<'#';
        }
        int num;
        timeFile>>num;
        bool greater = false;
        if (num > 12)
        {
            num = num - 12;
            greater = true;
        }
        char colon;
        int mins;
        timeFile>>colon>>mins;
        tempFile<<num<<colon;
        if (mins < 10)
            tempFile<<0<<mins;
        else
            tempFile<<mins;
        if (greater)
            tempFile<<" PM"<<endl;
        else
            tempFile<<" AM"<<endl;
        getline(timeFile,extra);
        hash = 0;
    }
    tempFile.close();
    timeFile.close();
    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");
}