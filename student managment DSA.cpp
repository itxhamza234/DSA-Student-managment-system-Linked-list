#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> //using library setw()
using namespace std;

class node
{
public:
    int adID;   //admission no
    int rollNo;
    string name;
    string fname; //fathername
    string dob;
    string address;
    node* next;
    node* prev;
};

class Student
{
private:
    node* head;
    // using data type file handling
    int aID;   //admission no
    int rNo;
    string nameStudent;
    string fathername; //fathername
    string d;//Date of birth
    string addrss; //address
public:
    Student()
    {
        head = NULL;

    }
    //Insert Data
    void Insert(int aNO, int roll, string name, string fathername, string dob, string address)
    {
        node* curr;
        //create New Node
        node* temp = new node;
        //Store date Node
        temp->rollNo = roll;
        temp->adID = aNO;
        temp->name = name;
        temp->fname = fathername;
        temp->dob = dob;
        temp->address = address;
        temp->next = NULL;
        if (head == NULL)
        {
            temp->prev = NULL;
            head = temp;
            SaveToFile();
        }
        else
        {
            curr = head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = temp;
            temp->prev = curr;
            SaveToFile();
        }
    }
    //Save Data to File
    void SaveToFile()
    {
        fstream file;
        file.open("student.txt", ios::out | ios::app);
        node* curr = head;
        file << curr->adID << " " << curr->rollNo << " " << curr->name << " " << curr->fname << " " << curr->dob << " " << curr->address << endl;
        curr = curr->next;
        file.close();
        cout << endl << endl;
        cout << "\t\t\t\t Data Saved To File Successfully!" << endl;
        system("pause");
        system("cls");
    }

    //Search Student Record
    void StudentSearchRecord()
    {
        int found = 0;
        int searchRollNo;
        cout << "\t\t\t\t------------------------" << endl;
        cout << "\t\t\t\t Enter Search Roll No#: ";
        cin >> searchRollNo;
        node* curr = head;
        while (curr != NULL) {
            if (searchRollNo == curr->rollNo)
            {
                cout << "\t\t\t\t Student Admission No#: " << curr->adID << endl;
                cout << "\t\t\t\t Student Roll No#: " << curr->rollNo << endl;
                cout << "\t\t\t\t Student Name: " << curr->name << endl;
                cout << "\t\t\t\t Student Father Name: " << curr->fname << endl;
                cout << "\t\t\t\t Student Address: " << curr->address << endl;
                cout << "\t\t\t\t Student Date of Birth(DD/MM/YYYY): " << curr->dob << endl;;
                found++;
                cout << endl << endl;
                cout << "\t\t\t\t Student Record Searched Successfully...." << endl;
                system("pause");
                system("cls");
                break;
            }
            curr = curr->next;
        }
        if (found == 0)
        {
            cout << endl << endl;
            cout << "\t\t\t\t Roll No# Not Found....!" << endl;
            system("pause");
            system("cls");
        }
    }

    //Count Student 
    void CountStudent()
    {
        int count = 0;
        node* curr = head;
        while (curr != NULL)
        {
            count++;
            curr = curr->next;
        }
        cout << endl << endl;
        cout << "\t\t\t\t Total Students: " << count << endl;
        system("pause");
        system("cls");
    }

    //Update Function
    void Update()
    {
        int found = 0;
        node* curr = head;
        int adNO;
        cout << "\t\t\t\t------------------------" << endl;
        cout << "\t\t\t\t Enter Admission No#: ";
        cin >> adNO;
        while (curr != NULL)
        {
            if (adNO == curr->adID)
            {
                int a;
                string f, n, addrss, d;
                cout << "\t\t\t\t Enter Roll No#: ";
                cin >> curr->rollNo;
                cout << "\t\t\t\t Enter Name: ";
                cin >> curr->name;
                cout << "\t\t\t\t Enter Father Name: ";
                cin >> curr->fname;
                cout << "\t\t\t\t Enter Address: ";
                cin >> curr->address;
                cout << "\t\t\t\t Enter Date Of Birth(DD/MM/YYYY): ";
                cin >> curr->dob;
                UpdateRecordFileHandlng(curr->adID, curr->rollNo, curr->name, curr->fname, curr->dob, curr->address);
                found++;
                cout << endl;
                cout << "\t\t\t\t Student Record Updated Successfully...." << endl;
                system("pause");
                system("cls");
                break;
            }
            curr = curr->next;
        }
        if (found == 0)
        {
            cout << endl << endl;
            cout << "\t\t\t\t Addmission No# not found!" << endl;
            system("pause");
            system("cls");
        }
    }
    //Update FileHandlng 
    void UpdateRecordFileHandlng(int a, int roll, string name, string fname, string dob, string address)
    {
        fstream file, file1;
        file.open("student.txt", ios::in);
        {
            file1.open("student1.txt", ios::app | ios::in);
            file >> aID >> rNo >> nameStudent >> fathername >> d >> addrss;

            while (!file.eof())
            {
                if (aID == a)
                {
                    file1 << a << ", " << roll << ", " << name << ", " << fname << ", " << dob << ", " << address << endl;
                }
                else
                {
                    file1 << aID << ", " << rNo << ", " << nameStudent << ", " << fathername << ", " << d << ", " << addrss << endl;;

                }
                file >> aID >> rNo >> nameStudent >> fathername >> d >> addrss;
            }
        }
        file.close();
        file1.close();
        remove("student.txt");
        rename("student1.txt", "student.txt");
    }


    //Delete Student Data
    void DeleteStudent()
    {
        int found = 0;
        int AddmissionNo;
        cout << endl << endl;
        cout << "\t\t\t\t------------------------" << endl;
        cout << "\t\t\t\t Enter Addmission No#: ";
        cin >> AddmissionNo;
        node* current = head;
        node* temp = NULL;
        while (current != NULL)
        {
            if (current->adID == AddmissionNo)
            {
                if (current == head)
                    head = current->next;
                else if (current == temp)
                    temp = current->prev;
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                RemoveFileHandlingStudent(current->adID);
                delete current;
                found++;
                system("pause");
                system("cls");
                break;
            }
            current = current->next;
        }
        if (found == 0)
        {
            cout << endl << endl;
            cout << "\t\t\t\t Student Data not Found" << endl;
            system("pause");
            system("cls");
        }
    }



    //Remove FileHandling Student
    void RemoveFileHandlingStudent(int a)
    {

        fstream f, f1;
        f.open("student.txt", ios::in);
        {
            f1.open("student1.txt", ios::out | ios::app);
            f >> aID >> rNo >> nameStudent >> fathername >> d >> addrss;
            while (!f.eof())
            {
                if (aID == a)
                {
                    cout << endl << endl;
                    cout << "\t\t\t\t  Student Removed Successfully...." << endl;
                    break;
                }
                else
                {
                    f1 << aID << " " << rNo << " " << nameStudent << " " << fathername << " " << d << " " << addrss << endl;;
                }
                f >> aID >> rNo >> nameStudent >> fathername >> d >> addrss;
            }
            f1.close();
            f.close();
            remove("student.txt");
            rename("student1.txt", "student.txt");
        }
    }
    //Display
    void Display()
    {
        int a = 1;//a++ count student no
        int found = 0;
        node* curr = head;
        cout << endl << endl;
        cout << "\t-------------------------------------------------------------------------------------------------------" << endl;
        cout << right << setw(5) << "\t| No. |" << setw(17) << "Admission No. |" << setw(12) << "Roll No. |" << setw(16) << "Student Name |" << setw(16) << "Father Name |" << setw(20) << "Date of Birth |" << setw(15) << "Address |" << endl;
        cout << "\t-------------------------------------------------------------------------------------------------------" << endl;
        while (curr != NULL)
        {

            cout << "\t" << right << setw(5) << a++ << setw(17) << curr->adID << setw(12) << curr->rollNo << setw(16) << curr->name << setw(16) << curr->fname << setw(20) << curr->dob << setw(15) << curr->address << endl;

            //			
            //			cout << "Roll No: " << curr->rollNo << endl;
            //			cout << "Your Name: " << curr->name << endl;
            //			cout << "CGPA: " << curr->cgpa << endl;
            curr = curr->next;
            found++;
            
            
        }
        cout << endl;
        system("pause");
        system("cls");

    }




    //Load Data from File
    void LoadFromFile()
    {
        //using data type file handling
        int aID;   //admission no
        int rNo;
        string nameStudent;
        string fathername; //fathername
        string d;//Date of birth
        string addrss; //address
        Student s;
        fstream file;
        file.open("student.txt", ios::in);
        if (!file)
        {
            cout << "\t\t\t\t Error Opening File....." << endl;
        }
        else
        {
            while (file >> aID >> rNo >> nameStudent >> fathername >> d >> addrss)
            {
                // s.Insert(aID, rNo, nameStudent, fathername, d, addrss);
                 //file >> aID >> rNo >> nameStudent >> fathername >> d >> addrss;
                node* curr;
                //create New Node
                node* temp = new node;
                //Store date Node
                temp->rollNo = aID;
                temp->adID = rNo;
                temp->name = nameStudent;
                temp->fname = fathername;
                temp->dob = d;
                temp->address = addrss;
                temp->next = NULL;
                if (head == NULL)
                {
                    temp->prev = NULL;
                    head = temp;
                }
                else
                {
                    curr = head;
                    while (curr->next != NULL) {
                        curr = curr->next;
                    }
                    curr->next = temp;
                    temp->prev = curr;
                }


            }
            cout << endl << endl;
            cout << "\t\t\t\t Data Loaded From File Successfully....." << endl;
            system("pause");
            system("cls");
        }

        file.close();

    }
};

int main()
{
    node* head = NULL;
    Student s;
    int choice;
    while (true)
    {

        cout << endl << endl;
        cout << "\t\t\t\t======================================================\n";
        cout << "\t\t\t\t|...............STUDENT MANAGEMENT SYSTEM............|\n";
        cout << "\t\t\t\t======================================================\n";

        cout << "\t\t\t\t| (1). Insert Student Data: " << endl;
        cout << "\t\t\t\t| (2). Search Student Data: " << endl;
        cout << "\t\t\t\t| (3). Total Student: " << endl;
        cout << "\t\t\t\t| (4). Update Student Data: " << endl;
        cout << "\t\t\t\t| (5). Delete Student Data: " << endl;
        cout << "\t\t\t\t| (6). Display Student Data: " << endl;
        cout << "\t\t\t\t| (7). Load Student Data From File: " << endl;
        cout << "\t\t\t\t| (8). Exit" << endl;
        cout << "\t\t\t\t| Enter Your Choice: ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
        {
            int roll, aNO;
            string name, fathername, dob, address;
            cout << "\t\t\t\t------------------------" << endl;
            cout << "\t\t\t\t Enter Admission No#: ";
            while (true)
            {
                cin >> aNO;
                node* check = head;
                int i = 0;
                while (check != NULL)
                {
                    if (check->adID == aNO)
                    {
                        i++;
                        break;
                    }
                    check = check->next;
                }
                if (i == 1)
                {
                    cout << endl << endl;
                    cout << "\t\t\t\t Already Exist Please Enter New Admission No#......." << endl;
                    system("pause");
                    system("cls");
                    main();
                }
                else
                {
                    break;
                }
            }
            cout << "\t\t\t\t Enter Roll No#: ";
            cin >> roll;
            cout << "\t\t\t\t Enter Name: ";
            cin >> name;
            cout << "\t\t\t\t Enter Father Name: ";
            cin >> fathername;
            cout << "\t\t\t\t Enter Address: ";
            cin >> address;
            cout << "\t\t\t\t Enter Date of Birth(DD/MM/YYYY): ";
            cin >> dob;
            s.Insert(aNO, roll, name, fathername, dob, address);
            break;
        }
        case 2:
            s.StudentSearchRecord();
            break;
        case 3:
            s.CountStudent();
            break;
        case 4:
            s.Update();
            break;
        case 5:
            s.DeleteStudent();
            break;
        case 6:
            s.Display();
            break;
        case 7:
            s.LoadFromFile();
            break;
        case 8:
            return 0;
        default:
            cout << "\t\t\t\t Invalid Choice....." << endl;
        }
    }
    return 0;
}