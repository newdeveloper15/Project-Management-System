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

};

struct FileCRUD
{
    private:

        string line;
        int spaceCount;
        int lineCount;

        //int modifyMenu;

        //string fileData;

        string word1, word2, word3, word4;
        string fileProName;
        string inputProName;

        vector<string> fileDataVec = vector<string>();
        bool match;

        FileIO f;

    public:

        FileCRUD()
        {
            line = "";
            spaceCount = 0;
            lineCount = 0;
            //modifyMenu = 0;

            //fileData = "";

            word1 = word2 = word3 = word4 = "";
            fileProName = "";
            inputProName = "";
            match = false;
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

        //void modifyPDFile()
        void modifyProjectName()
        {
            cout<<"\n\nEnter project name to modify : ";
            cin.ignore();
            getline(cin, fileProName);

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

                        //if(spaceCount == 2 && ((!isspace(line[i]) && word3 == "") ||  (isspace(line[i]) && word3 != "")) )
                        //if(lineCount == 1 && spaceCount >= 2 && ((!isspace(line[i]) && word3 == "") ||  (isspace(line[i]) && word3 != "")) )
                        if(spaceCount == 2 && ((!isspace(line[i]) && word3 == "") ||  (isspace(line[i]) && word3 != "") || (!isspace(line[i]) && word3 != "")) )
                        {
                            word3 += line[i];
//                            if(isspace(line[i]))
//                                spaceCount--;
                        }

                        if(spaceCount == 3 && !isspace(line[i]))
                        {
                            word4 += line[i];
                        }

                    }   //end for

                    line = "";

                    cout<<"\nWord3 = " <<word3 <<endl;

                    if(lineCount == 1 && word3 == fileProName)
                    {
                        cout<<"\nEnter project name to change : ";
                        getline(cin, inputProName);

                        line += word1;
                        line += " ";
                        line += word2;
                        line += " ";
                        line += inputProName;

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

                            fileDataVec.push_back(line);                                }
                    }
                    else if(lineCount == 1 && match == false)
                    {
                        inProjectDuration.seekg(0, ios::end);   //set read pointer to end of file
                    }

                    spaceCount = 0;
                    lineCount = 0;
                    line = "";
                    word1 = word2 = word3 = word4 = "";


                }//end while

                if(match == true)
                {
                    cout<<"\n*******************************************************************"<<endl;
                    cout<<"\nProject name updated !\n"<<endl;
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

        }   //end of modifyProjectName()


};

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
            cout<<"\nYear : ";
            cin >> year;

            if(year < 1000 || year > 9999)
            {
                cout<<"\nYear is not valid !"<<endl;
            }

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

        int getMonth()
        {
            return month;
        }

        bool validateDate(int date)
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
            cout<<"\nProject name : ";
            //cin >> projectName;
            cin.ignore();
            getline(cin, projectName);

        }

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
            cout<<"Project description : ";
            //cin >> projectDesc;
            //cin.ignore();
            getline(cin, projectDesc);
            //cin.ignore();
        }

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

        }

        void setProStartDate(string sDate)
        {
            startDate = sDate;
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

        void setProEndDate(string eDate)
        {
            endDate = eDate;
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

        int durationUnit;

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
            durationUnit = 0;
        }

        //parameterized constructor
        Phases(int p, int a, int d, int i, int m, int du)
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
            cout<<"\nEnter planning phase duration : ";
            cin >> planningDuration;
        }

        void setPlanning(int p)
        {
            planningDuration = p;
        }

        int getPlanning()
        {
            return planningDuration;
        }

        void setAnalysis()
        {
            cout<<"Enter analysis phase duration : ";
            cin >> analysisDuration;
        }

        void setAnalysis(int a)
        {
            analysisDuration = a;
        }

        int getAnalysis()
        {
            return analysisDuration;
        }

        void setDesign()
        {
            cout<<"Enter design phase duration : ";
            cin >> designDuration;
        }

        void setDesign(int d)
        {
            designDuration = d;
        }

        int getDesign()
        {
            return designDuration;
        }

        void setImplementation()
        {
            cout<<"Enter implementation phase duration : ";
            cin >> implementationDuration;
        }

        void setImplementation(int i)
        {
            implementationDuration = i;
        }

        int getImplementation()
        {
            return implementationDuration;
        }

        void setMaintenance()
        {
            cout<<"Enter maintenance phase duration : ";
            cin >> maintenanceDuration;
        }

        void setMaintenance(int m)
        {
            maintenanceDuration = m;
        }

        int getMaintenance()
        {
            return maintenanceDuration;
        }

        void setDurationUnit()
        {
            cout<<"Enter duration unit : ";
            cin >> durationUnit;
        }

        void setDurationUnit(int du)
        {
            durationUnit = du;
        }

        int getDurationUnit()
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

        }
};

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
                                cout<<"\nPress 1 to modify Project Name"<<endl;
                                cout<<"Press 2 to modify Project Description"<<endl;
                                cout<<"Press 3 to modify Project Start Date"<<endl;
                                cout<<"Press 4 to modify Project End Date"<<endl;
                                cout<<"Press 5 to modify Project Phase"<<endl;

                                cin >> modifyMenu;

                                switch(modifyMenu)
                                {
                                    case 1:
                                    {
                                        fc.modifyProjectName();
                                    }
                                    break;

                                    case 2:
                                    {

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
