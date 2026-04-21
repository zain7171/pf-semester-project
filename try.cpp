#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;
void fixTime(fstream&);
int main ()
{
    fstream app_file("appointments.txt", ios::in);
    if (app_file.fail())
    {
        cout<<"Failed to open file appointments.txt"<<endl;
        exit(1);
    }
    fixTime(app_file);
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