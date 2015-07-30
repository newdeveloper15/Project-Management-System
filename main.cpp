#include <iostream>
#include <fstream>      //included for file input output
#include <string>
#include <vector>
#include <sstream>  //string to int conversion

using namespace std;

ofstream accOutFile;    //write accounts file
ifstream accInFile;     //read accounts file

ifstream inProjectDuration;
ofstream outProjectDuration;

ifstream inProjectStatus;
ofstream outProjectStatus;

struct FileIO
{

    /**Start**//**Account file**/

    void openAccOutFile()
    {
        accOutFile.open("account.txt", ios::app);
    }

    void closeAccOutFile()
    {
        accOutFile.close();
    }

    void openAccInFile()
    {
        accInFile.open("account.txt", ios::in);
    }

    void closeAccInFile()
    {
        accInFile.close();
    }

    /**End**//**Account file**/


    /**Start**//**Project file**/

    void openOutProjectFile()
    {
        //outProjectDuration.open("projectDetails.txt", ios::app);
        outProjectDuration.open("projectDetails.txt", ios::trunc);
    }

    void closeOutProjectFile()
    {
        outProjectDuration.close();
    }

    void openInProjectFile()
    {
        inProjectDuration.open("projectDetails.txt", ios::in);
    }

    void closeInProjectFile()
    {
        inProjectDuration.close();
    }

    /**End**//**Project file**/

    /**Start**//**Project Status file**/

    void openOutProjectStatusFile()
    {
        outProjectStatus.open("projectStatus.txt", ios::app);
    }

    void closeOutProjectStatusFile()
    {
        outProjectStatus.close();
    }

    void openInProjectStatusFile()
    {
        inProjectStatus.open("projectStatus.txt", ios::in);
    }

    void closeInProjectStatusFile()
    {
        inProjectStatus.close();
    }

    /**End**//**Project Status file**/


    bool emptyAccFileCheck()
    {
        openAccInFile();

        accInFile.seekg(0, ios::end);
        size_t size = accInFile.tellg();

        closeAccInFile();

        if(size == 0)
        {
            return true;
        }
        return false;
    }

    bool emptyPsFileCheck()
    {
        openInProjectStatusFile();

        inProjectStatus.seekg(0, ios::end);
        size_t size = inProjectStatus.tellg();

        closeInProjectStatusFile();

        if(size == 0)
        {
            return true;
        }
        return false;
    }

    bool emptyPdFileCheck()
    {
        openInProjectFile();

        inProjectDuration.seekg(0, ios::end);
        size_t size = inProjectDuration.tellg();

        closeInProjectFile();

        if(size == 0)
        {
            return true;
        }
        return false;
    }


};

/*
struct FileCRUD
{
    private:

        string line;
        int spaceCount;
        int lineCount;

        string word1, word2, word3, word4;
        string fileProName; //this variable have to deleted
        string inputProName;

        string fileInput;   //this variable have to deleted
        string matchInput;

        vector<string> fileDataVec = vector<string>();
        bool match;

        FileIO f;

    public:

        FileCRUD()
        {
            line = "";
            spaceCount = 0;
            lineCount = 0;

            word1 = word2 = word3 = word4 = "";
            fileProName = "";
            inputProName = "";
            match = false;

            fileInput = matchInput = "";
        }

        void writeBack()
        {
            f.openOutProjectFile();

            if(outProjectDuration.is_open())
            {
                for(int i=0; i<fileDataVec.size(); i++)
                    outProjectDuration<<fileDataVec.at(i) <<"\n";
            }
            else
            {
                cout<<"\nUnable to open output project details file to write !"<<endl;
            }

            f.closeOutProjectFile();

            fileDataVec.resize(0);
        }

        void modifyPDFile(int menuNo)
        {
            if(f.emptyPdFileCheck() == false)
            {
                switch(menuNo)
                {
                    case 1:
                    {
                        cout<<"\n\nEnter project name to modify : ";
                        cin.ignore();
                        getline(cin, fileInput);
                    }
                    break;

                    case 2:
                    {
                        cout<<"\n\nEnter project description to modify : ";
                        cin.ignore();
                        getline(cin, fileInput);
                    }
                    break;

                    default:
                    {
                        cout<<"\nInvalid menu number !"<<endl;
                    }

                }   //end switch




                f.openInProjectFile();

                if(inProjectDuration.is_open())
                {
                    while(getline(inProjectDuration, line))
                    {
                        lineCount++;

                        for(int i=0; i<line.length(); i++)
                        {
                            if(isspace(line[i]))
                            {
                                if(lineCount > 2)
                                    spaceCount++;
                                else
                                {
                                    if((lineCount == 1 || lineCount == 2) && spaceCount < 2)
                                        spaceCount++;
                                }
                            }

                            if(spaceCount == 0 && !isspace(line[i]))
                            {
                                word1 += line[i];
                            }

                            if(spaceCount == 1 && !isspace(line[i]))
                            {
                                word2 += line[i];
                            }

                            if(spaceCount == 2 && ((!isspace(line[i]) && word3 == "") ||  (isspace(line[i]) && word3 != "") || (!isspace(line[i]) && word3 != "")) )
                            {
                                word3 += line[i];
                            }

                            if(spaceCount == 3 && !isspace(line[i]))
                            {
                                word4 += line[i];
                            }

                        }   //end for

                        line = "";

                        cout<<"\nWord3 = " <<word3 <<endl;

                        if(menuNo == 1 && lineCount == 1 && word3 == fileInput)
                        {
                            cout<<"\nEnter project name to change : ";
                            getline(cin, matchInput);

                            line += word1;
                            line += " ";
                            line += word2;
                            line += " ";
                            line += matchInput;

                            fileDataVec.push_back(line);

                            match = true;
                        }
                        else if(menuNo == 2 && lineCount == 2 && word3 == fileInput)
                        {
                            cout<<"\nEnter project description to change : ";
                            getline(cin, matchInput);

                            line += word1;
                            line += " ";
                            line += word2;
                            line += " ";
                            line += matchInput;

                            fileDataVec.push_back(line);

                            match = true;
                        }
                        else if(match == true)
                        {
                            if(lineCount == 2)
                            {
                                line += word1;
                                line += " ";
                                line += word2;
                                line += " ";
                                line += word3;

                                fileDataVec.push_back(line);
                            }
                            else
                            {
                                line += word1;
                                line += " ";
                                line += word2;
                                line += " ";
                                line += word3;
                                line += " ";
                                line += word4;

                                fileDataVec.push_back(line);
                            }
                        }
                        else if(menuNo == 1 && lineCount == 1 && match == false)
                        {
                            inProjectDuration.seekg(0, ios::end);   //set read pointer to end of file
                        }
                        else if(menuNo == 2 && lineCount == 2 && match == false)
                        {
                            inProjectDuration.seekg(0, ios::end);   //set read pointer to end of file
                        }


                        spaceCount = 0;
                        lineCount = 0;
                        line = "";
                        word1 = word2 = word3 = word4 = "";


                    }//end while

                    //if(match == true)
                    if(menuNo == 1 && match == true)
                    {
                        cout<<"\n*******************************************************************"<<endl;
                        cout<<"\nProject name updated !\n"<<endl;
                        cout<<"*******************************************************************\n"<<endl;
                    }
                    if(menuNo == 2 && match == true)
                    {
                        cout<<"\n*******************************************************************"<<endl;
                        cout<<"\nProject description updated !\n"<<endl;
                        cout<<"*******************************************************************\n"<<endl;
                    }
                    else
                    {
                        cout<<"\n*******************************************************************"<<endl;
                        cout<<"\nProject not found !\n"<<endl;
                        cout<<"*******************************************************************\n"<<endl;
                    }

                }
                else
                {
                    cout<<"\nUnable to open project details file to modify project name !"<<endl;
                }

                f.closeInProjectFile();

                writeBack();    //write modified file data back to file

            }
            else
            {
                cout<<"\nProject details file is empty !"<<endl;
            }

        }   //end of modifyPDFile()

};  //end of FileCRUD struct
*/

struct Account
{
    private:

        string username, password;

    public:

        string loginStatus;

        FileIO f;

        Account()
        {
            username = "";
            password = "";
            loginStatus = "";
        }

        void setUsername()
        {
            //cout<<setw(8);
            cout<<"    Enter username : ";
            //cin >> username;
            cin.ignore();
            getline(cin, username);
        }

        string getUsername()
        {
            return username;
        }

        void setPassword()
        {
            //cout<<setw(8);
            cout<<"    Enter password : ";
            cin >> password;
        }

        string getPassword()
        {
            return password;
        }

        bool spaceCheck(string un)
        {
            for(int i=0; i<un.length(); i++)
            {
                if(isspace(un[i]))
                    return true;
            }

            return false;
        }

        bool specialCharacterCheck(string un)
        {
            for(int i=0; i<un.length(); i++)
            {
                if(!isalnum(un[i]))
                    return true;
            }

            return false;
        }

        void createAccount()
        {
            f.openAccOutFile();

            do{
                setUsername();

                if(-isdigit(username[0]))
                {
                    cout<<"\n    Username should not start with a digit !\n"<<endl;
                }
                else if(spaceCheck(username))
                {
                    cout<<"\n    Username should not contain space !\n"<<endl;
                }
                else if(specialCharacterCheck(username))
                {
                    cout<<"\n    Username should not contain any special character/s !\n"<<endl;
                }

            }while(isdigit(username[0]) || spaceCheck(username) || specialCharacterCheck(username));

            setPassword();

            if(accOutFile.is_open())
            {
                accOutFile<<username <<" ";
                accOutFile<<password <<"\n";
            }
            else
            {
                cout<<"\nUnable to open output accounts file !"<<endl;
            }

            f.closeAccOutFile();

            cout<<"\n*****************************************************"<<endl;
            cout<<"\n                Account created !"<<endl;
            cout<<"\n*****************************************************"<<endl;

        }   //end of createAccount()

        void login()
        {
            string line;
            string uname = "", pwd = "";
            int spaceCounter = 0;
            bool match = false;

            FileIO f;

            f.openAccOutFile();
            f.closeAccOutFile();

            if(f.emptyAccFileCheck() == false)
            {
                cout<<"\nLogin : \n"<<endl;

                cout<<"\n    Enter username to login : ";
                cin >> username;

                cout<<"    Enter password to login : ";
                cin >> password;

                f.openAccInFile();

                if(accInFile.is_open())
                {
                    while(getline(accInFile, line))
                    {
                        for(int i=0; i<line.length(); i++)
                        {
                            if(isspace(line[i]))
                                spaceCounter++;

                            if(spaceCounter == 0)
                            {
                                uname += line[i];
                            }

                            if(spaceCounter == 1 && !isspace(line[i]))
                            {
                                pwd += line[i];
                            }
                        }

                        if(username == uname && password == pwd)
                        {
                            cout<<"\n******** Access granted : ********"<<endl;
                            match = true;
                            loginStatus = "loggedIn";

                            accInFile.seekg(0, ios::end);   //set the get pointer at the end of the file
                        }

                        //reset variables
                        uname = "";
                        pwd = "";
                        spaceCounter = 0;

                    }   //end of while loop

                    if(match == false)
                    {
                        cout<<"\n*****************************************************"<<endl;
                        cout<<"\n           Invalid username or password !"<<endl;
                        cout<<"\n*****************************************************"<<endl;
                    }
                }
                else
                {
                    cout<<"\nUnable to open input accounts file !"<<endl;
                }

                f.closeAccInFile();

            }   //empty account file check
            else
            {
                cout<<"\nYou must create account first !"<<endl;
            }

        }   //end of login()
};

struct Date
{
    private:

        //string year, month, date;
        int year, month, date;

    public:

        Date()
        {
//            year = "";
//            month = "";
//            date = "";

            year = 0;
            month = 0;
            date = 0;
        }

        bool leapYearCheck(int year)
        {
            if(year % 4 == 0)
            {
                if(year % 100 == 0 )
                {
                    if(year % 400 != 0)
                    {
                        //cout<<"\nNot a leap year !"<<endl;
                        return false;
                    }
                    else
                    {
                        //cout<<"\nLeap year !"<<endl;
                        return true;
                    }
                }
                else
                    return true;
            }
            return false;

        }   //end of leapYearCheck()

        void setYear()
        {
            do
            {
                cout<<"\nYear : ";
                cin >> year;

                if(year < 1000 || year > 9999)
                {
                    cout<<"\nYear is not valid !"<<endl;
                }

            }while(year < 1000 || year > 9999);

        }   //end of setYear()

        void setYear(int newYear)
        {
            string strNewYear = "";

            do
            {
                if(newYear < 1000 || newYear > 9999)
                {
                    //cout<<"\nYear is not valid ! Enter year again : "<<endl;
                    cout<<"\nYear is not valid ! Enter year again OR Press [ENTER] to unchange : "<<endl;
                    getline(cin, strNewYear);
                    //cin >> newYear;

                    if(strNewYear != "")
                    {
                        stringstream strToInt(strNewYear);
                        strToInt >> newYear;
                    }

                    //year = (newYear < 1000 || newYear > 9999) ? -1 : newYear;
                    year = (newYear < 1000 || newYear > 9999 && strNewYear == "") ? -1 : newYear;
                }
                else
                {
                    year = newYear;
                }

            //}while(newYear < 1000 || newYear > 9999);
            //}while(newYear < 1000 || newYear > 9999 && strNewYear != "");
            }while((newYear < 1000 && strNewYear != "") || (newYear > 9999 && strNewYear != ""));

        }   //end of setYear()

        int getYear()
        {
            return year;
        }

        void setMonth()
        {
            do
            {
                cout<<"Month : ";
                cin >> month;

                if(month < 1 || month > 12)
                    cout<<"\nInvalid month"<<endl;

            }while(month < 1 || month > 12);

        }   //end of setMonth()

        void setMonth(int newMonth)
        {
            string strNewMonth = "";

            do
            {
                if(newMonth < 1 || newMonth > 12)
                {
                    cout<<"\nInvalid month ! Enter month again OR Press [ENTER] to unchange : "<<endl;
                    //cin >> newMonth;
                    getline(cin, strNewMonth);

                    if(strNewMonth != "")
                    {
                        stringstream strToInt(strNewMonth);
                        strToInt >> newMonth;
                    }

                    //month = (newMonth < 1 || newMonth > 12) ? -1 : newMonth;
                    month = (newMonth < 1 || newMonth > 12 && strNewMonth == "") ? -1 : newMonth;
                }
                else
                    month = newMonth;

            //}while(newMonth < 1 || newMonth > 12);
            }while((newMonth < 1 && strNewMonth != "") || (newMonth > 12 && strNewMonth != ""));

        }   //end of setMonth()


        int getMonth()
        {
            return month;
        }

        bool validateDate(int date)
        {
//            cout<<"\nInside validate function : "<<endl;
//            cout<<"Year = " <<year <<endl;
//            cout<<"Month = " <<month <<endl;
//            cout<<"Date = " <<date <<endl;

            if(year != 0 && year != -1 && month != 0 && month != -1)
            {
                if(leapYearCheck(year) == false)
                {
                    if(month == 1 || month == 3 || month == 5 || month == 7 ||  month == 8 ||  month == 10 || month == 12)
                    {
                        if(date < 1 || date > 31)
                            //cout<<"\nInvalid date !"<<endl;
                            return false;
                    }
                }
                else
                {
                    if(month == 2 || month == 4 || month == 6 || month == 9 ||  month == 11)
                    {
                        if(date < 1 || date > 30)
                            //cout<<"\nInvalid date !"<<endl;
                            return false;
                    }
                    else if(month == 2)
                    {
                        if(date < 1 || date > 29)
                            //cout<<"\nInvalid date"<<endl;
                            return false;
                    }
                }
            }
            else
                return false;

            return true;

        }   //end of validateDate()

        void setDate()
        {
            do
            {
                cout<<"Date : ";
                cin >> date;

                if(validateDate(date) == false)
                    cout<<"\nInvalid date !"<<endl;

            }while(validateDate(date) == false);

            cout<<""<<endl;

        }   //end of setDate()

        void setDate(int newDate)
        {
            //cout<<"\n\nValidate date function value : " <<validateDate(newDate) <<endl;
            string strNewDate = "";

            do
            {
                //if(validateDate(newDate) == false && (year == 0 || year == -1 || month == 0 || month == -1))
                if(year == 0 || year == -1 || month == 0 || month == -1)
                {
                    if(newDate >= 1 && newDate <= 31)
                    {
                        date = newDate;
                        strNewDate = "";
                    }
                    else
                    {
                        cout<<"\nInvalid date ! Enter date again OR Press [ENTER] to unchange : "<<endl;
                        //cin >> newDate;
                        getline(cin, strNewDate);

                        if(strNewDate != "")
                        {
                            stringstream strToInt(strNewDate);
                            strToInt >> newDate;
                        }
                        else
                            strNewDate = "";

                        //date = (validateDate(newDate)) ? newDate : -1;
                        //date = (validateDate(newDate) && strNewDate != "") ? newDate : -1;
                        date = (newDate >= 1 && newDate <= 31) ? newDate : -1;

                    }
                }
                //else if(validateDate(newDate) == false && (year != 0 && year != -1 && month != 0 && month != -1))
                else if(validateDate(newDate) == false)
                {
                    cout<<"\nInvalid date ! Enter date again OR Press [ENTER] to unchange : "<<endl;
                    //cin >> newDate;
                    getline(cin, strNewDate);

                    if(strNewDate != "")
                    {
                        stringstream strToInt(strNewDate);
                        strToInt >> newDate;
                    }
                    else
                        strNewDate = "";

                    //date = (validateDate(newDate)) ? newDate : -1;
                    date = (validateDate(newDate) && strNewDate != "") ? newDate : -1;

                }
                /**no need of else may be**/
//                else
//                    date = newDate;

            //}while(validateDate(newDate) == false);
            }while(validateDate(newDate) == false && strNewDate != "");

            cout<<""<<endl;

        }   //end of setDate()


        int getDate()
        {
            return date;
        }
};

struct Project
{
    private:

        string projectName;
        string projectDesc;

        string startDate;
        string endDate;

        Date proStartDate;
        Date proEndDate;

    public:

        Project()
        {
            projectName = "";
            projectDesc = "";
            startDate = "";
            endDate = "";
        }

        void setProjectName()
        {
            do
            {
                cout<<"\nProject name : ";
                //cin >> projectName;
                cin.ignore();
                getline(cin, projectName);

                if(projectName == "")
                {
                    cout<<"\nProject name can't be null !"<<endl;
                }

            }while(projectName == "");

        }   //end of setProjectName()

        void setProjectName(string pName)
        {
            projectName = pName;
        }

        string getProjectName()
        {
            return projectName;
        }

        void setProjectDesc()
        {
            do
            {
                cout<<"Project description : ";
                getline(cin, projectDesc);

                if(projectDesc == "")
                {
                    cout<<"\nProject description can't be null !"<<endl;
                }

            }while(projectDesc == "");

        }   //end of setProjectDesc()

        void setProjectDesc(string pDesc)
        {
            projectDesc = pDesc;
        }

        string getProjectDesc()
        {
            return projectDesc;
        }

        void setProStartDate()
        {
            //cout<<"Project start date (dd/mm/yy) : ";
            cout<<"Project start date (yy/mm/dd) : ";
            //cin >> startDate;

            proStartDate.setYear();
            proStartDate.setMonth();
            proStartDate.setDate();

        }   //end of setProStartDate()

        //void setProStartDate(string sDate)
        void setProStartDate(int sYear, int sMonth, int sDate)
        {
            //startDate = sDate;
            proStartDate.setYear(sYear);
            proStartDate.setMonth(sMonth);
            proStartDate.setDate(sDate);
        }

//        string getProStartDate()
//        {
//            return startDate;
//        }

        string getProStartDate()
        {
            stringstream sYear;
            sYear << proStartDate.getYear();

            startDate += sYear.str();
            startDate += "/";

            stringstream sMonth;
            sMonth << proStartDate.getMonth();

            startDate += sMonth.str();
            startDate += "/";

            stringstream sDate;
            sDate << proStartDate.getDate();

            startDate += sDate.str();

            return startDate;

        }   //end of getProStartDate()

        void setProEndDate()
        {
            //cout<<"Project end date (dd/mm/yy) : ";
            cout<<"Project end date (yy/mm/dd) : ";
            //cin >> endDate;
            proEndDate.setYear();
            proEndDate.setMonth();
            proEndDate.setDate();
        }

        //void setProEndDate(string eDate)
        void setProEndDate(int eYear, int eMonth, int eDate)
        {
            //endDate = eDate;
            proEndDate.setYear(eYear);
            proEndDate.setMonth(eMonth);
            proEndDate.setDate(eDate);
        }

//        string getProEndDate()
//        {
//            return endDate;
//        }

        string getProEndDate()
        {
            stringstream sYear;
            sYear << proEndDate.getYear();

            endDate += sYear.str();
            endDate += "/";

            stringstream sMonth;
            sMonth << proEndDate.getMonth();

            endDate += sMonth.str();
            endDate += "/";

            stringstream sDate;
            sDate << proEndDate.getDate();

            endDate += sDate.str();

            return endDate;
        }

        bool validateProDate()
        {
            if(proEndDate.getYear() < proStartDate.getYear())
            {
                return false;
            }
            else if(proEndDate.getYear() == proStartDate.getYear())
            {
                if(proEndDate.getMonth() < proStartDate.getMonth())
                {
                    return false;
                }
                else if(proEndDate.getMonth() == proStartDate.getMonth())
                {
                    if(proEndDate.getDate() < proStartDate.getDate())
                    {
                        return false;
                    }
                }
            }

            return true;

        }   //end of validatProDate()
};

struct Phases
{
    private:

        int planningDuration, analysisDuration, designDuration, implementationDuration,
        maintenanceDuration;

        //int durationUnit;
        string durationUnit;

    public:

        Project project;
        FileIO file;

        //default constructor
        Phases()
        {
            planningDuration = 0;
            analysisDuration = 0;
            designDuration = 0;
            implementationDuration = 0;
            maintenanceDuration = 0;
            //durationUnit = 0;
            durationUnit = "";
        }

        //parameterized constructor
        //Phases(int p, int a, int d, int i, int m, int du)
        Phases(int p, int a, int d, int i, int m, string du)
        {
            planningDuration = p;
            analysisDuration = a;
            designDuration = d;
            implementationDuration = i;
            maintenanceDuration = m;
            durationUnit = du;
        }

        void setPlanning()
        {
            do
            {
                cout<<"\nEnter planning phase duration : ";
                cin >> planningDuration;

                if(planningDuration == 0)
                    cout<<"\nPlanning phase duration can't be zero !"<<endl;
                else if(planningDuration < 0)
                    cout<<"\nPlanning phase duration can't be negative !"<<endl;

            }while(planningDuration <= 0);
        }

        /**Overloaded function setPlanning() is only used in modifyPDFile()**/
        void setPlanning(int p)
        {
            string strDuration = "";

            do
            {
                //if(planningDuration == 0)
                if(p == 0)
                {
                    cout<<"\nPlanning phase duration can't be zero !"<<endl;
                    cout<<"Enter again or Press [ENTER] to unchange : ";
                    //cin >> p;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> p;
                    }

                    //planningDuration = (planningDuration <= 0 ) ? -1 : p;
                    planningDuration = (p <= 0 && strDuration == "") ? -2147483648 : p;
                }
                //else if(planningDuration < 0)
                else if(p < 0)
                {
                    cout<<"\nPlanning phase duration can't be negative !"<<endl;
                    cout<<"Enter again or Press [ENTER] to unchange : ";
                    //cin >> p;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> p;
                    }
                    //planningDuration = (planningDuration <= 0 ) ? -1 : p;
                    planningDuration = (p <= 0  && strDuration == "") ? -2147483648 : p;
                }
                else
                    planningDuration = p;

            //}while(planningDuration <= 0);
            }while(p <= 0 && planningDuration != -2147483648);

        }   //end of setPlanning()

        int getPlanning()
        {
            return planningDuration;
        }

        void setAnalysis()
        {
            do
            {
                cout<<"Enter analysis phase duration : ";
                cin >> analysisDuration;

                if(planningDuration == 0)
                    cout<<"\nAnalysis phase duration can't be zero !"<<endl;
                else if(planningDuration < 0)
                    cout<<"\nAnalysis phase duration can't be negative !"<<endl;

            }while(planningDuration <= 0);
        }

        /**Overloaded function setAnalysis() is only used in modifyPDFile()**/
        void setAnalysis(int a)
        {
            string strDuration = "";
            do
            {
                //if(analysisDuration == 0)
                if(a == 0)
                {
                    cout<<"\nAnalysis phase duration can't be zero !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> a;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> a;
                    }

                    //analysisDuration = (analysisDuration <= 0 ) ? -1 : a;
                    analysisDuration = (a <= 0 && strDuration == "") ? -2147483648 : a;
                }
                //else if(analysisDuration < 0)
                else if(a < 0)
                {
                    cout<<"\nAnalysis phase duration can't be negative !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> a;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> a;
                    }

                    //analysisDuration = (analysisDuration <= 0 ) ? -1 : a;
                    analysisDuration = (a <= 0 && strDuration == "") ? -2147483648 : a;
                }
                else
                    analysisDuration = a;

            //}while(analysisDuration <= 0);
            }while(a <= 0 && analysisDuration != -2147483648);

        }   //end of setAnalysis()

        int getAnalysis()
        {
            return analysisDuration;
        }

        void setDesign()
        {
            do
            {
                cout<<"Enter design phase duration : ";
                cin >> designDuration;

                if(designDuration == 0)
                    cout<<"\nDesign phase duration can't be zero !"<<endl;
                else if(designDuration < 0)
                    cout<<"\nDesign phase duration can't be negative !"<<endl;

            }while(designDuration <= 0);
        }

        void setDesign(int d)
        {
            string strDuration = "";
            do
            {
                //if(designDuration == 0)
                if(d == 0)
                {
                    cout<<"\nDesign phase duration can't be zero !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> d;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> d;
                    }

                    //designDuration = (designDuration <= 0 ) ? -1 : d;
                    designDuration = (d <= 0  && strDuration == "") ? -2147483648 : d;
                }
                //else if(designDuration < 0)
                else if(d < 0)
                {
                    cout<<"\nDesign phase duration can't be negative !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> d;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> d;
                    }

                    //designDuration = (designDuration <= 0 ) ? -1 : d;
                    designDuration = (d <= 0  && strDuration == "") ? -2147483648 : d;
                }
                else
                    designDuration  = d;

            //}while(designDuration <= 0);
            }while(d <= 0 && designDuration != -2147483648);

        }   //end of setDesign()

        int getDesign()
        {
            return designDuration;
        }

        void setImplementation()
        {
            do
            {
                cout<<"Enter implementation phase duration : ";
                cin >> implementationDuration;

                if(implementationDuration == 0)
                    cout<<"\nImplementation phase duration can't be zero !"<<endl;
                else if(implementationDuration < 0)
                    cout<<"\nImplementation phase duration can't be negative !"<<endl;

            }while(implementationDuration <= 0);
        }

        void setImplementation(int i)
        {
            string strDuration = "";

            do
            {
                //if(implementationDuration == 0)
                if(i == 0)
                {
                    cout<<"\nImplementation phase duration can't be zero !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> i;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> i;
                    }

                    //implementationDuration = (implementationDuration <= 0 ) ? -1 : i;
                    implementationDuration = (i <= 0 && strDuration == "") ? -2147483648 : i;
                }
                //else if(implementationDuration < 0)
                else if(i < 0)
                {
                    cout<<"\nImplementation phase duration can't be negative !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> i;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> i;
                    }

                    //implementationDuration = (implementationDuration <= 0 ) ? -1 : i;
                    implementationDuration = (i <= 0 && strDuration == "") ? -2147483648 : i;
                }
                else
                    implementationDuration = i;

            //}while(implementationDuration <= 0);
            }while(i <= 0 && implementationDuration != -2147483648);

        }   //end of setImplementation()

        int getImplementation()
        {
            return implementationDuration;
        }

        void setMaintenance()
        {
            do
            {
                cout<<"Enter maintenance phase duration : ";
                cin >> maintenanceDuration;

                if(maintenanceDuration == 0)
                    cout<<"\nMaintenance phase duration can't be zero !"<<endl;
                else if(maintenanceDuration < 0)
                    cout<<"\nMaintenance phase duration can't be negative !"<<endl;

            }while(maintenanceDuration <= 0);

        }   //end of setMaintenance()

        void setMaintenance(int m)
        {
            string strDuration = "";

            do
            {
                //if(maintenanceDuration == 0)
                if(m == 0)
                {
                    cout<<"\nMaintenance phase duration can't be zero !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> m;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> m;
                    }

                    //maintenanceDuration = (maintenanceDuration <= 0 ) ? -1 : m;
                    maintenanceDuration = (m <= 0  && strDuration == "") ? -2147483648 : m;
                }
                //else if(maintenanceDuration < 0)
                else if(m < 0)
                {
                    cout<<"\nMaintenance phase duration can't be negative !"<<endl;
                    cout<<"Enter again OR Press [ENTER] to unchange : ";
                    //cin >> m;
                    getline(cin, strDuration);

                    if(strDuration != "")
                    {
                        stringstream strToInt(strDuration);
                        strToInt >> m;
                    }

                    //maintenanceDuration = (maintenanceDuration <= 0 ) ? -1 : m;
                    maintenanceDuration = (m <= 0  && strDuration == "") ? -2147483648 : m;
                }
                else
                    maintenanceDuration = m;

            //}while(maintenanceDuration <= 0);
            }while(m <= 0 && maintenanceDuration != -2147483648);

        }   //end of setMaintenance()

        int getMaintenance()
        {
            return maintenanceDuration;
        }

        void setDurationUnit()
        {
            do
            {
                cout<<"Enter duration unit : ";
                cin >> durationUnit;

                if(durationUnit != "hours" && durationUnit != "days" && durationUnit != "weeks" && durationUnit != "months" && durationUnit != "years")
                {
                    cout<<"\nInvalid duration unit !"<<endl;
                }

            }while(durationUnit != "hours" && durationUnit != "days" && durationUnit != "weeks" && durationUnit != "months" && durationUnit != "years");
        }

        //void setDurationUnit(int du)
        void setDurationUnit(string du)
        {
            do
            {
                //if(durationUnit != "hours" && durationUnit != "days" && durationUnit != "weeks" && durationUnit != "months" && durationUnit != "years")
                if(du != "hours" && du != "days" && du != "weeks" && du != "months" && du != "years")
                {
                    cout<<"\nInvalid duration unit !"<<endl;
                    cout<<"Enter duration unit again OR Press [ENTER] to unchange : ";
                    cin >> du;

                    if(du == "")
                    {
                        du = "blank";
                    }

                    //(durationUnit != "hours" && durationUnit != "days" && durationUnit != "weeks" && durationUnit != "months" && durationUnit != "years") ? "" : du;
                    durationUnit = (du != "hours" && du != "days" && du != "weeks" && du != "months" && du != "years" && du != "blank") ? "" : du;
                }
                else
                    durationUnit = du;

            //}while(durationUnit != "hours" && durationUnit != "days" && durationUnit != "weeks" && durationUnit != "months" && durationUnit != "years");
            }while(du != "hours" && du != "days" && du != "weeks" && du != "months" && du != "years" && durationUnit != "blank");

        }   //end of setDurationUnit()

        //int getDurationUnit()
        string getDurationUnit()
        {
            return durationUnit;
        }

        void writeAllDurations()
        {
            //project name and description
            project.setProjectName();
            project.setProjectDesc();

            do
            {
                project.setProStartDate();
                project.setProEndDate();

                if(project.validateProDate() == false)
                {
                    cout<<"\n*******************************************************************"<<endl;
                    cout<<"\n\"Project end date\" is specified before \"project start date\"!"<<endl;
                    cout<<"\nEnter project start date and end date again !\n"<<endl;
                    cout<<"*******************************************************************\n"<<endl;
                }

            }while(project.validateProDate() == false);

            //set project milestones duration
            setPlanning();
            setAnalysis();
            setDesign();
            setImplementation();
            setMaintenance();

            file.openOutProjectFile();

            if(outProjectDuration.is_open())
            {
                outProjectDuration<<"Project Name "<<project.getProjectName() <<"\n";
                outProjectDuration<<"Project Description "<<project.getProjectDesc() <<"\n";
                outProjectDuration<<"Project Start Date "<<project.getProStartDate() <<"\n";
                outProjectDuration<<"Project End Date "<<project.getProEndDate() <<"\n\n";

                outProjectDuration<<"Planning phase duration " <<getPlanning() <<"\n";
                outProjectDuration<<"Analysis phase duration " <<getAnalysis() <<"\n";
                outProjectDuration<<"Design phase duration " <<getDesign() <<"\n";
                outProjectDuration<<"Implementation phase duration " <<getImplementation() <<"\n";
                outProjectDuration<<"Maintenance phase duration " <<getMaintenance() <<"\n";
            }
            else
            {
                cout<<"\nUnable to open output project details file !"<<endl;
            }

            file.closeOutProjectFile();

        }   //end of writeAllDurations()

};  //end of Phases struct

struct FileCRUD
{
    private:

        //string searchInput;
        string modifiedInput;

        string line;
        string word1, word2, word3, word4;
        int lineCount;
        int spaceCount;

        string modifiedYear, modifiedMonth, modifiedDate;
        int intModYear, intModMonth, intModDate;
        int intPhasesDuration;

        vector<string> fileDataVec = vector<string>();

        FileIO fileIO;
        Project pdObject;
        Phases phasesObject;

        Date startDate;
        Date endDate;

    public:

        FileCRUD()
        {
            modifiedInput = "";
            line = "";
            word1 = word2 = word3 = word4 = "";
            lineCount = spaceCount = 0;

            modifiedYear = modifiedMonth = modifiedDate = "";
            intModYear = intModMonth = intModDate = 0;
            intPhasesDuration = 0;
        }

        void searchPDFile(int searchMenu)
        {
            if(fileIO.emptyPdFileCheck() == false)
            {
                lineCount = 0;
                line = "";

                fileIO.openInProjectFile();

                while(getline(inProjectDuration, line))
                {
                    lineCount++;

                    if(searchMenu == 1 && lineCount == 1)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 2 && lineCount == 2)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 3 && lineCount == 3)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 4 && lineCount == 4)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 5 && lineCount == 6)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 6 && lineCount == 7)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 7 && lineCount == 8)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 8 && lineCount == 9)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }
                    else if(searchMenu == 9 && lineCount == 10)
                    {
                        cout<<"\n" <<line <<endl;
                        inProjectDuration.seekg(0, ios::end);   //set file read pointer to end of file
                    }

                    line = "";

                }   //end while

                fileIO.closeInProjectFile();
            }
            else
            {
                cout<<"\nProject Details file is empty !"<<endl;
            }

        }   //end of searchPDFile()

        void modifyProName()
        {
            cout<<"Enter new project name or press [ENTER] to unchange : ";
            cin.ignore();
            getline(cin, modifiedInput);

            if(modifiedInput != "")
            {
                pdObject.setProjectName(modifiedInput);

                //line = word1 +" " +word2 +" " +modifiedInput;
                line = word1 +" " +word2 +" " +pdObject.getProjectName();
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3;
                fileDataVec.push_back(line);
            }

        }   //end of modifyProName()

        void modifyProDesc()
        {
            cout<<"Enter new project description or press [ENTER] to unchange : ";
            //cin.ignore();
            getline(cin, modifiedInput);

            if(modifiedInput != "")
            {
                pdObject.setProjectDesc(modifiedInput);

                //line = word1 +" " +word2 +" " +modifiedInput;
                line = word1 +" " +word2 +" " +pdObject.getProjectDesc();
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3;
                fileDataVec.push_back(line);
            }

        }   //end of modifyProDesc()

        void modifyProStartDate()
        {
            cout<<"\nEnter new project start date : ";

            cout<<"\nNew year or press [ENTER] to unchange : ";
            getline(cin, modifiedYear);

            if(modifiedYear != "")
            {
                stringstream strToInt1(modifiedYear);
                strToInt1 >> intModYear;

                startDate.setYear(intModYear);
            }

            cout<<"New month or press [ENTER] to unchange : ";
            getline(cin, modifiedMonth);

            if(modifiedMonth != "")
            {
                stringstream strToInt2(modifiedMonth);
                strToInt2 >> intModMonth;

                startDate.setMonth(intModMonth);
            }

            cout<<"New date or press [ENTER] to unchange : ";
            getline(cin, modifiedDate);

            //if(modifiedMonth != "")
            if(modifiedDate != "")
            {
                stringstream strToInt3(modifiedDate);
                strToInt3 >> intModDate;

                startDate.setDate(intModDate);
            }

            //if(modifiedInput != "")
            //if(modifiedYear != "" && modifiedMonth != "" && modifiedDate != "")
            if((modifiedYear != "" && startDate.getYear() != -1) && (modifiedMonth != "" && startDate.getMonth() != -1) && (modifiedDate != "" && startDate.getDate() != -1))
            {
                //string to integer conversion
//                stringstream strToInt1(modifiedYear);
//                strToInt1 >> intModYear;
//
//                stringstream strToInt2(modifiedMonth);
//                strToInt2 >> intModMonth;
//
//                stringstream strToInt3(modifiedDate);
//                strToInt3 >> intModDate;

                //pdObject.setProStartDate(intModYear, intModMonth, intModDate);
                //following statement is for test purpose
                pdObject.setProStartDate(startDate.getYear(), startDate.getMonth(), startDate.getDate());

                //line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
                line = word1 +" " +word2 +" " +word3 +" " +pdObject.getProStartDate();
                fileDataVec.push_back(line);
            }
            else
            {
                cout<<"\nProject start date not modified because one of the date field is left blank !"<<endl;

                line = word1 +" " +word2 +" " +word3 +" " +word4;
                fileDataVec.push_back(line);
            }

        }   //end of modifyProStartDate()

        void modifyProEndDate()
        {
            cout<<"\nEnter new project end date : ";

            cout<<"\nNew year or press [ENTER] to unchange : ";
            getline(cin, modifiedYear);

            if(modifiedYear != "")
            {
                stringstream strToInt1(modifiedYear);
                strToInt1 >> intModYear;

                endDate.setYear(intModYear);
            }

            cout<<"New month or press [ENTER] to unchange : ";
            getline(cin, modifiedMonth);

            if(modifiedMonth != "")
            {
                stringstream strToInt2(modifiedMonth);
                strToInt2 >> intModMonth;

                endDate.setMonth(intModMonth);
            }

            cout<<"New date or press [ENTER] to unchange : ";
            getline(cin, modifiedDate);

            //if(modifiedMonth != "")
            if(modifiedDate != "")
            {
                stringstream strToInt3(modifiedDate);
                strToInt3 >> intModDate;

                endDate.setDate(intModDate);
            }

            //if(modifiedInput != "")
            //if(modifiedYear != "" && modifiedMonth != "" && modifiedDate != "")
            if((modifiedYear != "" && endDate.getYear() != -1) && (modifiedMonth != "" && endDate.getMonth() != -1) && (modifiedDate != "" && endDate.getDate() != -1))
            {
                //string to integer conversion
//                stringstream strToInt1(modifiedYear);
//                strToInt1 >> intModYear;
//
//                stringstream strToInt2(modifiedMonth);
//                strToInt2 >> intModMonth;
//
//                stringstream strToInt3(modifiedDate);
//                strToInt3 >> intModDate;

                //pdObject.setProStartDate(intModYear, intModMonth, intModDate);
                //following statement is for test purpose
                pdObject.setProEndDate(endDate.getYear(), endDate.getMonth(), endDate.getDate());

                //line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
                line = word1 +" " +word2 +" " +word3 +" " +pdObject.getProEndDate();
                fileDataVec.push_back(line);
            }
            else
            {
                cout<<"\nProject end date not modified because one of the date field is left blank !"<<endl;

                line = word1 +" " +word2 +" " +word3 +" " +word4;
                fileDataVec.push_back(line);
            }

        }   //end of modifyProEndDate()

        void modifyPlaninningPhaseDuration()
        {
            cout<<"\nEnter new Planning Phase duration or press [ENTER] to unchange : ";
            //cin.ignore();
            getline(cin, modifiedInput);

            stringstream strToInt(modifiedInput);
            strToInt >> intPhasesDuration;

            phasesObject.setPlanning(intPhasesDuration);

            //if(modifiedInput != "")
            if(modifiedInput != "" && phasesObject.getPlanning() != -2147483648)
            {
//                stringstream strToInt(modifiedInput);
//                strToInt >> intPhasesDuration;
//
//                phasesObject.setPlanning(intPhasesDuration);

                stringstream intToStr;
                intToStr << phasesObject.getPlanning();

                modifiedInput = intToStr.str();

                line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3 +" " +word4;
                fileDataVec.push_back(line);
            }

        }   //end of modifyPlaninningPhaseDuration()

        void modifyAnalysisPhaseDuration()
        {
            cout<<"\nEnter new Analysis Phase duration or press [ENTER] to unchange : ";
            //cin.ignore();
            getline(cin, modifiedInput);

            stringstream strToInt(modifiedInput);
            strToInt >> intPhasesDuration;

            phasesObject.setAnalysis(intPhasesDuration);

            //if(modifiedInput != "")
            if(modifiedInput != "" && phasesObject.getAnalysis() != -2147483648)
            {
//                stringstream strToInt(modifiedInput);
//                strToInt >> intPhasesDuration;
//
//                phasesObject.setAnalysis(intPhasesDuration);

                stringstream intToStr;
                intToStr << phasesObject.getAnalysis();

                modifiedInput = intToStr.str();

                line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3 +" " +word4;
                fileDataVec.push_back(line);
            }

        }   //end of modifyAnalysisPhaseDuration()

        void modifyDesignPhaseDuration()
        {
            cout<<"\nEnter new Design Phase duration or press [ENTER] to unchange : ";
            //cin.ignore();
            getline(cin, modifiedInput);

            stringstream strToInt(modifiedInput);
            strToInt >> intPhasesDuration;

            phasesObject.setDesign(intPhasesDuration);

            //if(modifiedInput != "")
            if(modifiedInput != "" && phasesObject.getDesign() != -2147483648)
            {
//                stringstream strToInt(modifiedInput);
//                strToInt >> intPhasesDuration;
//
//                phasesObject.setDesign(intPhasesDuration);

                stringstream intToStr;
                intToStr << phasesObject.getDesign();

                modifiedInput = intToStr.str();

                line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3 +" " +word4;
                fileDataVec.push_back(line);
            }

        }   //end of modifyDesignPhaseDuration()

        void modifyImplementationPhaseDuration()
        {
            cout<<"\nEnter new Implementation Phase duration or press [ENTER] to unchange : ";
            //cin.ignore();
            getline(cin, modifiedInput);

            stringstream strToInt(modifiedInput);
            strToInt >> intPhasesDuration;

            phasesObject.setImplementation(intPhasesDuration);

            //if(modifiedInput != "")
            if(modifiedInput != "" && phasesObject.getImplementation() != -2147483648)
            {
//                stringstream strToInt(modifiedInput);
//                strToInt >> intPhasesDuration;
//
//                phasesObject.setImplementation(intPhasesDuration);

                stringstream intToStr;
                intToStr << phasesObject.getImplementation();

                modifiedInput = intToStr.str();

                line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3 +" " +word4;
                fileDataVec.push_back(line);
            }

        }   //end of modifyImplementationPhaseDuration()

        void modifyMaintenancePhaseDuration()
        {
            cout<<"\nEnter new Maintenance Phase duration or press [ENTER] to unchange : ";
            //cin.ignore();
            getline(cin, modifiedInput);

            stringstream strToInt(modifiedInput);
            strToInt >> intPhasesDuration;

            phasesObject.setMaintenance(intPhasesDuration);

            //if(modifiedInput != "")
            if(modifiedInput != "" && phasesObject.getMaintenance() != -2147483648)
            {
//                stringstream strToInt(modifiedInput);
//                strToInt >> intPhasesDuration;
//
//                phasesObject.setMaintenance(intPhasesDuration);

                stringstream intToStr;
                intToStr << phasesObject.getMaintenance();

                modifiedInput = intToStr.str();

                line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3 +" " +word4;
                fileDataVec.push_back(line);
            }

        }   //end of modifyMaintenancePhaseDuration()

        void modifyDurationUnit()
        {
            cout<<"\nEnter new duration unit or press [ENTER] to unchange : ";
            getline(cin, modifiedInput);

            phasesObject.setDurationUnit(modifiedInput);

            if(modifiedInput != "" && phasesObject.getDurationUnit() != "blank")
            {
                line = word1 +" " +word2 +" " +modifiedInput;
                fileDataVec.push_back(line);
            }
            else
            {
                line = word1 +" " +word2 +" " +word3;
                fileDataVec.push_back(line);
            }

        }   //end of  modifyDurationUnit()

        //void modificationInput()
        void modificationInput(int lineCount)
        {
//            string modifiedYear, modifiedMonth, modifiedDate;
//            int intModYear, intModMonth, intModDate;
//            int intPhasesDuration;
            line = "";

            switch(lineCount)
            {
                case 1:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyProName();

//                        cout<<"Enter new project name or press [ENTER] to unchange : ";
//                        cin.ignore();
//                        getline(cin, modifiedInput);
//
//                        if(modifiedInput != "")
//                        {
//                            pdObject.setProjectName(modifiedInput);
//
//                            //line = word1 +" " +word2 +" " +modifiedInput;
//                            line = word1 +" " +word2 +" " +pdObject.getProjectName();
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 2:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyProDesc();

//                        cout<<"Enter new project description or press [ENTER] to unchange : ";
//                        //cin.ignore();
//                        getline(cin, modifiedInput);
//
//                        if(modifiedInput != "")
//                        {
//                            pdObject.setProjectDesc(modifiedInput);
//
//                            //line = word1 +" " +word2 +" " +modifiedInput;
//                            line = word1 +" " +word2 +" " +pdObject.getProjectDesc();
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 3:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyProStartDate();

//                        cout<<"\nEnter new project start date : ";
//
//                        cout<<"\nNew year or press [ENTER] to unchange : ";
//                        getline(cin, modifiedYear);
//                        cout<<"New month or press [ENTER] to unchange : ";
//                        getline(cin, modifiedMonth);
//                        cout<<"New date or press [ENTER] to unchange : ";
//                        getline(cin, modifiedDate);
//
//                        //if(modifiedInput != "")
//                        if(modifiedYear != "" && modifiedMonth != "" && modifiedDate != "")
//                        {
//                            //string to integer conversion
//                            stringstream strToInt1(modifiedYear);
//                            strToInt1 >> intModYear;
//
//                            stringstream strToInt2(modifiedMonth);
//                            strToInt2 >> intModMonth;
//
//                            stringstream strToInt3(modifiedDate);
//                            strToInt3 >> intModDate;
//
//                            pdObject.setProStartDate(intModYear, intModMonth, intModDate);
//
//                            //line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
//                            line = word1 +" " +word2 +" " +word3 +" " +pdObject.getProStartDate();
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3 +" " +word4;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 4:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyProEndDate();

//                        cout<<"\nEnter new project end date : ";
//
//                        cout<<"\nNew year or press [ENTER] to unchange : ";
//                        getline(cin, modifiedYear);
//                        cout<<"New month or press [ENTER] to unchange : ";
//                        getline(cin, modifiedMonth);
//                        cout<<"New date or press [ENTER] to unchange : ";
//                        getline(cin, modifiedDate);
//
//                        //if(modifiedInput != "")
//                        if(modifiedYear != "" && modifiedMonth != "" && modifiedDate != "")
//                        {
//                            //string to integer conversion
//                            stringstream strToInt1(modifiedYear);
//                            strToInt1 >> intModYear;
//
//                            stringstream strToInt2(modifiedMonth);
//                            strToInt2 >> intModMonth;
//
//                            stringstream strToInt3(modifiedDate);
//                            strToInt3 >> intModDate;
//
//                            pdObject.setProEndDate(intModYear, intModMonth, intModDate);
//
//                            //line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
//                            line = word1 +" " +word2 +" " +word3 +" " +pdObject.getProEndDate();
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3 +" " +word4;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 5:
                {
                    if(word1 == "" && word2 == "" && word3 == "")   //blank line
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 6:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyPlaninningPhaseDuration();

//                        cout<<"\nEnter new Planning Phase duration or press [ENTER] to unchange : ";
//                        //cin.ignore();
//                        getline(cin, modifiedInput);
//
//                        if(modifiedInput != "")
//                        {
//                            stringstream strToInt(modifiedInput);
//                            strToInt >> intPhasesDuration;
//
//                            phasesObject.setPlanning(intPhasesDuration);
//
//                            stringstream intToStr;
//                            intToStr << phasesObject.getPlanning();
//
//                            modifiedInput = intToStr.str();
//
//                            line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3 +" " +word4;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 7:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyAnalysisPhaseDuration();

//                        cout<<"\nEnter new Analysis Phase duration or press [ENTER] to unchange : ";
//                        //cin.ignore();
//                        getline(cin, modifiedInput);
//
//                        if(modifiedInput != "")
//                        {
//                            stringstream strToInt(modifiedInput);
//                            strToInt >> intPhasesDuration;
//
//                            phasesObject.setAnalysis(intPhasesDuration);
//
//                            stringstream intToStr;
//                            intToStr << phasesObject.getAnalysis();
//
//                            modifiedInput = intToStr.str();
//
//                            line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3 +" " +word4;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 8:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyDesignPhaseDuration();

//                        cout<<"\nEnter new Design Phase duration or press [ENTER] to unchange : ";
//                        //cin.ignore();
//                        getline(cin, modifiedInput);
//
//                        if(modifiedInput != "")
//                        {
//                            stringstream strToInt(modifiedInput);
//                            strToInt >> intPhasesDuration;
//
//                            phasesObject.setDesign(intPhasesDuration);
//
//                            stringstream intToStr;
//                            intToStr << phasesObject.getDesign();
//
//                            modifiedInput = intToStr.str();
//
//                            line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3 +" " +word4;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 9:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyImplementationPhaseDuration();

//                        cout<<"\nEnter new Implementation Phase duration or press [ENTER] to unchange : ";
//                        //cin.ignore();
//                        getline(cin, modifiedInput);
//
//                        if(modifiedInput != "")
//                        {
//                            stringstream strToInt(modifiedInput);
//                            strToInt >> intPhasesDuration;
//
//                            phasesObject.setImplementation(intPhasesDuration);
//
//                            stringstream intToStr;
//                            intToStr << phasesObject.getImplementation();
//
//                            modifiedInput = intToStr.str();
//
//                            line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3 +" " +word4;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                case 10:
                {
                    if(word1 != "" && word2 != "" && word3 != "")   //not blank line
                    {
                        modifyMaintenancePhaseDuration();

//                        cout<<"\nEnter new Maintenance Phase duration or press [ENTER] to unchange : ";
//                        //cin.ignore();
//                        getline(cin, modifiedInput);
//
//                        if(modifiedInput != "")
//                        {
//                            stringstream strToInt(modifiedInput);
//                            strToInt >> intPhasesDuration;
//
//                            phasesObject.setMaintenance(intPhasesDuration);
//
//                            stringstream intToStr;
//                            intToStr << phasesObject.getMaintenance();
//
//                            modifiedInput = intToStr.str();
//
//                            line = word1 +" " +word2 +" " +word3 +" " +modifiedInput;
//                            fileDataVec.push_back(line);
//                        }
//                        else
//                        {
//                            line = word1 +" " +word2 +" " +word3 +" " +word4;
//                            fileDataVec.push_back(line);
//                        }
                    }
                    else
                    {
                        fileDataVec.push_back("");
                    }
                }
                break;

                default:
                {
                    cout<<"\nInvalid line number to modify Project Details file data !"<<endl;
                }

            }   //end switch

        }   //end of modificationInput()

        void modifyPDFile()
        {
            if(fileIO.emptyPdFileCheck() == false)
            {
                lineCount = spaceCount = 0;
                line = word1 = word2 = word3 = word4 = "";

                fileIO.openInProjectFile();

                while(getline(inProjectDuration, line))
                {
                    lineCount++;

                    for(int i=0; i<line.length(); i++)
                    {
                        if(isspace(line[i]))
                        {
                            if(lineCount > 2)
                                spaceCount++;
                            else
                            {
                                if((lineCount == 1 || lineCount == 2) && spaceCount < 2)
                                    spaceCount++;
                            }
                        }

    //                    if((lineCount == 1 || lineCount == 2) && spaceCount <= 2 && isspace(line[i]))
    //                    {
    //                        spaceCount++;
    //                    }
    //                    else if(lineCount > 2 && isspace(line[i]))
    //                    {
    //                        spaceCount++;
    //                    }

                        if(spaceCount == 0 && !isspace(line[i]))
                        {
                            word1 += line[i];
                        }

                        if(spaceCount == 1 && !isspace(line[i]))
                        {
                            word2 += line[i];
                        }

                        if(lineCount == 1 || lineCount == 2)
                        {
                            //if(lineCount == 1 && spaceCount == 2 && !isspace(line[i]))
                            if(spaceCount == 2 && ((!isspace(line[i]) && word3 == "") ||  (isspace(line[i]) && word3 != "") || (!isspace(line[i]) && word3 != "")) )
                            {
                                word3 += line[i];
                            }
                        }
                        else
                        {
                            if(spaceCount == 2 && !isspace(line[i]))
                            {
                                word3 += line[i];
                            }

                            if(spaceCount == 3 && !isspace(line[i]))
                            {
                                word4 += line[i];
                            }
                        }


                    }   //end for

                    modificationInput(lineCount);   //get input for modification and store result in fileDataVec vector

                    word1 = word2 = word3 = word4 = line = "";
                    spaceCount = 0;

                }   //end while

                fileIO.closeInProjectFile();

                writeBack();

                if(fileIO.emptyPdFileCheck() == false)
                {
                    cout<<"\nProject details file modified successfuly !"<<endl;
                    cout<<"All records are saved\n"<<endl;
                }

                fileDataVec.clear();    //remove all elements from fileDataVec vector
            }
            else
            {
                cout<<"\nProject Details file is empty !"<<endl;
            }

        }   //end of modifyPDFile()

        void writeBack()
        {
            fileIO.openOutProjectFile();

            if(outProjectDuration.is_open())
            {
                for(int i=0; i<fileDataVec.size(); i++)
                    outProjectDuration<<fileDataVec[i] <<"\n";
            }
            else
            {
                cout<<"\nUnable to open project details file to write back file data after modification !"<<endl;
            }

            fileIO.closeOutProjectFile();
        }

};  //end of FileCRUD struct

struct GanttChart
{
    private:

        string duration;
        int intDuration;

        vector<int> phasesDurationVec = vector<int>();

        int lineCount, spaceCount;
        string line;

    public:

        FileIO file;

        GanttChart()
        {
            duration = "";
            intDuration = 0;

            lineCount = 0;
            spaceCount = 0;
            line = "";
        }

        void readMileStoneDurations()
        {
            phasesDurationVec.resize(0);
            lineCount = 0;

            file.openInProjectFile();

            if(inProjectDuration.is_open())
            {
                while(getline(inProjectDuration, line))
                {
                    lineCount++;

                    //if(lineCount >= 4)
                    if(lineCount >= 6)
                    {
                        for(int i=0; i<line.length(); i++)
                        {
                            if(isspace(line[i]))
                            {
                                spaceCount++;
                            }

                            if(spaceCount == 3 && !isspace(line[i]))
                            {
                                duration += line[i];
                            }

                        }   //end of for loop

                        stringstream strToInt(duration);
                        strToInt >> intDuration;

                        phasesDurationVec.push_back(intDuration);

                        spaceCount = 0;
                        duration = "";

                    }//end-if

                }   //end of while loop
            }
            else
            {
                cout<<"\nUnable to open input project duration file !"<<endl;
            }

            file.closeInProjectFile();
        }

        void printGanttChart()
        {
            readMileStoneDurations();

            cout<<"\n\n*****************************************************"<<endl;

            cout<<"\nProject duration gantt chart"<<endl;
            cout<<"Duration unit : Week\n\n"<<endl;

//            for(int i=0; i<phasesDurationVec.size(); i++)
//                cout<<phasesDurationVec.at(i) <<" ";

            int limit = 0;

            for(int i=0; i<phasesDurationVec.size(); i++)
            {
                for(int value=1; value<=phasesDurationVec.at(i); value++)
                {
                    cout<<value <<" ";
                }
                cout<<""<<endl;

                limit += (phasesDurationVec.at(i) * 2);

                //for(int spaces=1; spaces<=phasesDurationVec.at(i)+1; spaces++)
                for(int spaces=1; spaces<=limit; spaces++)
                {
                    cout<<" ";
                }
            }

            cout<<"\n\n*****************************************************\n"<<endl;

            //phasesDurationVec.resize(0);
        }
};

struct ProjectStatus
{
    private:

        string phaseName;
        string line;
        int spaceCount;

        string word1, word2, word3, word4, word5;
        string newStr;
        vector<string> updatedLinesVec = vector<string>();

        bool phaseMatch;

    public:

        FileIO f;
        GanttChart g;

        ProjectStatus()
        {
            phaseName = "";
            line ="";
            spaceCount = 0;

            word1 = word2 = word3 = word4 = word5 = "";

            phaseMatch = false;
        }

        void writeFile()
        {

            if(updatedLinesVec.size() > 1)
            {
                outProjectStatus.open("projectStatus.txt", ios::trunc);
                //outProjectStatus.seekp(0, ios::beg);

                for(int i=0; i<updatedLinesVec.size(); i++)
                {
                    outProjectStatus<<updatedLinesVec.at(i) <<"\n";
                }

                outProjectStatus.close();

                if(phaseMatch == true)
                {
                    cout<<"\n*****************************************************"<<endl;
                    cout<<"\n           " <<phaseName << " Phase status updated !"<<endl;
                    cout<<"\n*****************************************************"<<endl;
                }
                else
                {
                    cout<<"\n*****************************************************"<<endl;
                    cout<<"\n          Invalid phase name specified !"<<endl;
                    cout<<"\n*****************************************************"<<endl;

                }
            }

            updatedLinesVec.resize(0);

        }   //end of writeFile()

        void updateProjectStatus()
        {
            string status;
            phaseMatch = false;

            //g.readMileStoneDurations();

            f.openOutProjectStatusFile();

            if(outProjectStatus.is_open())
            {

                if(f.emptyPsFileCheck() == true)
                {
                    outProjectStatus<<"Planning phase status : Incomplete" <<"\n";

                    outProjectStatus<<"Analysis phase status : Incomplete" <<"\n";

                    outProjectStatus<<"Design phase status : Incomplete" <<"\n";

                    outProjectStatus<<"Implementation phase status : Incomplete" <<"\n";

                    outProjectStatus<<"Maintenance phase status : Incomplete" <<"\n";
                    cout<<"\n*****************************************************"<<endl;
                    cout<<"\n    Writing initial Project status completed !\n"<<endl;
                    cout<<"*****************************************************\n"<<endl;
                }
                else
                {
                    cout<<"\nEnter phase name to update : ";
                    cin >> phaseName;

                    f.openInProjectStatusFile();

                    while(getline(inProjectStatus, line))
                    {
                        for(int i=0; i<line.length(); i++)
                        {
                            if(isspace(line[i]))
                            {
                                spaceCount++;
                            }

                            if(spaceCount == 0 && !isspace(line[i]))
                            {
                                word1 += line[i];
                            }

                            if(spaceCount == 1 && !isspace(line[i]))
                            {
                                word2 += line[i];
                            }

                            if(spaceCount == 2 && !isspace(line[i]))
                            {
                                word3 += line[i];
                            }

                            if(spaceCount == 3 && !isspace(line[i]))
                            {
                                word4 += line[i];
                            }

                            if(spaceCount == 4 && !isspace(line[i]))
                            {
                                word5 += line[i];
                            }

                        }   //end of for loop

                        if(phaseName == word1)
                        {
                            //cout<<"\n\nPhase found !!!"<<endl;

                            newStr = word1 +" " +word2 +" " +word3 +" " +word4 +" Complete";
                            updatedLinesVec.push_back(newStr);

                            phaseMatch = true;

                            //inProjectStatus.seekg(0, ios::end);
                        }
                        else
                        {
                            newStr = word1 +" " +word2 +" " +word3 +" " +word4 +" " +word5;
                            updatedLinesVec.push_back(newStr);
                        }

                        spaceCount = 0;
                        word1 = word2 = word3 = word4 = word5 = "";

                    }   //end of while loop


                    f.closeInProjectStatusFile();
                }
            }
            else
            {
                cout<<"\nUnable to open output project status file !"<<endl;
            }

            f.closeOutProjectStatusFile();

            writeFile();

        }   //end of updateProjectStatus()

        void printProjectStatus()
        {
            if(f.emptyPsFileCheck() == false)
            {
                f.openInProjectStatusFile();

                if(inProjectStatus.is_open())
                {
                    cout<<"\n\n*********************************************"<<endl;
                    cout<<"\nProject Status : \n"<<endl;

                    while(getline(inProjectStatus, line))
                    {
                        cout<<line <<endl;
                    }
                    cout<<"\n*********************************************\n"<<endl;
                }
                else
                    cout<<"\nUnable to open input project status file !"<<endl;

                f.closeInProjectStatusFile();
            }
            else
            {
                cout<<"\n*******************************************************************"<<endl;
                cout<<"\nProject Status file is empty ! Update Project status file first. !\n"<<endl;
                cout<<"*******************************************************************\n"<<endl;
            }

        }   //end of printProjectStatus()
};

int main()
{
    //Struct objects
    Account a;
    Phases p;
    GanttChart g;
    ProjectStatus ps;
    FileIO f;
    FileCRUD fc;

    int menuOption;
    int projectMenu;
    int modifyMenu;
    int searchFileMenu;
    //char repeat;


    cout<<"********************************************************************************"<<endl;
    cout<<"********************* WELCOME TO PROJECT MANAGEMENT SYSTEM *********************"<<endl;
    cout<<"********************************************************************************"<<endl;

    do{

        cout<<"\nPress 1 to create account"<<endl;
        cout<<"\nPress 2 to login into Project Management System (PMS)"<<endl;
        cout<<"\nPress 3 to exit"<<endl;

        cin >> menuOption;

        switch(menuOption)
        {
            case 1:
            {
                cout<<"\nCreate account : \n"<<endl;
//                a.setUsername();
//                a.setPassword();
                a.createAccount();
            }
            break;

            case 2:
            {
                a.login();

                if(f.emptyAccFileCheck() == false && a.loginStatus == "loggedIn")
                {

                    do{
                        cout<<"\nPress 1 to set project milestones duration"<<endl;
                        cout<<"\nPress 2 to enter to update project status"<<endl;
                        cout<<"\nPress 3 to print project Gantt Chart"<<endl;
                        cout<<"\nPress 4 to print project status"<<endl;
                        cout<<"\nPress 5 to go to file CRUD operations menu"<<endl;
                        cout<<"\nPress 6 to logout from Project Management System (PMS)"<<endl;

                        cin >> projectMenu;

                        switch(projectMenu)
                        {
                            case 1:
                            {
                                p.writeAllDurations();
                            }
                            break;

                            case 2:
                            {
                                ps.updateProjectStatus();
                            }
                            break;

                            case 3:
                            {
                                g.printGanttChart();
                            }
                            break;

                            case 4:
                            {
                                //print project status
                                ps.printProjectStatus();
                            }
                            break;

                            case 5:
                            {
//                                cout<<"\nPress 1 to modify Project Name"<<endl;
//                                cout<<"Press 2 to modify Project Description"<<endl;
//                                cout<<"Press 3 to modify Project Start Date"<<endl;
//                                cout<<"Press 4 to modify Project End Date"<<endl;
//                                cout<<"Press 5 to modify Project Phase"<<endl;

                                cout<<"\nPress 1 to modify Project details file"<<endl;
                                cout<<"Press 2 to search Project details file"<<endl;
                                cout<<"Press 3 to delete content from Project details file"<<endl;

                                cin >> modifyMenu;

                                switch(modifyMenu)
                                {
                                    case 1:
                                    {
                                        //fc.modifyProjectName();
                                        //fc.modifyPDFile(modifyMenu);
                                        fc.modifyPDFile();
                                    }
                                    break;

                                    case 2:
                                    {
                                        cout<<"\nPress 1 to search Project Name"<<endl;
                                        cout<<"Press 2 to search Project Description"<<endl;
                                        cout<<"Press 3 to search Project Start Date"<<endl;
                                        cout<<"Press 4 to search Project End Date"<<endl;
                                        cout<<"Press 5 to search Planning Phase Duration"<<endl;
                                        cout<<"Press 6 to search Analysis Phase Duration"<<endl;
                                        cout<<"Press 7 to search Design Phase Duration"<<endl;
                                        cout<<"Press 8 to search Implementation Phase Duration"<<endl;
                                        cout<<"Press 9 to search Maintenance Phase Duration"<<endl;

                                        cin >> searchFileMenu;

                                        fc.searchPDFile(searchFileMenu);

                                    }
                                    break;

                                    default:
                                    {
                                        cout<<"\nInvalid modify project file menu input !"<<endl;
                                    }

                                }   //end swtich

                            }
                            break;

                            case 6:
                            {
                                a.loginStatus = "loggedOut";
                                cout<<"\n******** You are successfully logged out from the system ! ********"<<endl;
                            }
                            break;

                            default:
                            {
                                cout<<"\nInvalid project menu option !"<<endl;
                            }

                        }//end of switch

                    //}while(projectMenu != 4);
                    //}while(projectMenu != 5);
                    }while(projectMenu != 6);

                }

            }
            break;

            case 3:
            {
                cout<<"\n\n********************************************************************************"<<endl;
                cout<<"**************** THANK YOU FOR USING PROJECT MANAGEMENT SYSTEM *****************"<<endl;
                cout<<"**************************** PROGRAM TERMINATED !!! ****************************"<<endl;
                cout<<"********************************************************************************\n"<<endl;
            }
            break;

            default:
            {
                cout<<"\nInvalid menu option !"<<endl;
            }

        }   //end of switch

    }while(menuOption != 3);


    return 0;

}   //end of main()
