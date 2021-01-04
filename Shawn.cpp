#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

// Global variables

const int ID_SIZE = 3,
          GROUP_SIZE = 4;
const int WNAME = 25,
    WGROUP = 13;

vector<string> ID_LIST;
vector<string> NAME_LIST;

// Using enum for project status
enum status{PENDING, ONTIME, LATE, NOTYET};

struct Project
{
    struct tm deadline;
};

struct Group
{
    vector<string> studentName;
    vector<string> studentID;
    vector<int> projectStatus;
};


// ***********************************************************************
//                          FUNCTION DECLARATION
// ***********************************************************************

// MENU
void mainMenu();
void subMenu1();   // 5 choices
void subMenu2();   // 3 choices
void subMenu3();   // 3 choices
void subMenu4();   // 3 choices

// HEADER
void header1();
void header2(int);
void header4(vector<int>);
// SECTIONS
void section1_1 (vector<Group> &);
void section1_2 (vector<Group>);
void section1_3 (vector<Group>);

void section1_2_Dao (vector<Group>);
void section1_3_Dao (vector<Group>);

void section1_4 (vector<Group>);
// SECTION 2
void section2_1(vector<Project> &);
void section2_2(vector<Group> &, vector<Project> &);

// SECTION 3
void section3_1( vector<Group>, vector<Project>);
void section3_2( vector<Group>, vector<Project>);

void section3_1_Dao( vector<Group>, vector<Project>);

void section4_1(vector<Group>, vector<Project>);
void section4_2(vector<Group>, vector<Project>);

void section5(vector<Group>, vector<Project>);

void section6(vector<Group>, vector<Project>);

// MAIN FUNCTIONS
Group getGroupInfo(int);

string getStudentInfo   (const int, vector<string>&);
string getStudentID     (const int);
void getSubmissionDate  (const int, vector<Project>,
                         const int, vector<Group> &);
void getProjectDeadline (vector<Project> &);
Project getDeadline     (const int);

void fillProjcetStatus(const int, vector<Project>,
                       const int, vector<Group> &);
void fillOutProjectStatus(vector<Group> &, vector<Project>);


// SUB FUNCTIONS
int getInt(const string);
int getChoice(const int);

string getFullName      (const int);
string getPartOfName    (const string);
string capName          (const string);


int findNameIndex(const string);
void save_file_section_4(string, vector<int>, vector<Group>, vector<Project>);

string getStatus(const int);
void displaySection4_1(const int, vector<Group>,
                       vector<Project>, vector<int>);
                

// Get time functions
int getHour();
int getMinute();
int getDate(const int, const int);
int getMonth();
int getYear();
int dayOfMonth(const int, const int);


// BOOL FUNCTIONS
bool ingroupDuplicate (string, vector<string>);
bool studentDuplicate (string);
bool haveSpace  (const string);
bool isText     (const string);
bool isInt      (const string);
bool isID       (const string);
bool nameCheck  (const string, const string);
bool IDinList   (const string);
bool isChoice   (const string, const int);
bool isLeapYear (int);
bool dateInPeriod(struct tm, struct tm, struct tm);

// CONVERTING DATA 
int str_to_int(string);


// ***********************************************************************
//                            M A I N  M E N U
// ***********************************************************************


int main()
{

    int choice;
    vector<Group> group;      // It is easier to pass vector to functions
    vector<Project> project;

    // Run a loop, exit on choice = 6
    do
    {
        // Display main menu
        mainMenu();
        // Get choice for main menu (6 different selections)
        choice = getChoice( 7 );

        // SECTION 1
        if ( choice == 1 )
        {
            do
            {
                subMenu1();
                choice = getChoice( 5 );
                switch (choice)
                {
                case 1:
                    section1_1(group);
                    break;
                case 2:
                    section1_2(group); // Replace "_Dao" to get function of Son
                    break;
                case 3:
                    section1_3(group);  // Replace "_Dao" to get function of Son
                    break;
                case 4:
                    section1_4(group);
                    break;
                default:
                    break;
                }
            } while ( choice != 5 );
            
        }
        
        // SECTION 2
        else if ( choice == 2 )
        {
            do
            {
                subMenu2();
                choice = getChoice( 3 );

                switch (choice)
                {
                case 1:
                    section2_1(project);
                    fillOutProjectStatus(group, project);
                    break;
                case 2:
                    section2_2(group, project);
                    break;
                default:
                    break;
                }
            } while ( choice != 3 );
            
            
        }

        // SECTION 3
        else if ( choice == 3 )
        {
            do
            {
                subMenu3();
                choice = getChoice( 3 );

                switch (choice)
                {
                case 1:
                    section3_1(group, project); // Replace "_Dao" to get function of Son
                    break;
                case 2:
                    section3_2(group, project);
                    break;
                
                default:
                    break;
                }
            } while (choice != 3);
            

        }
        
        // SECTION 4
        else if ( choice == 4 )
        {
            do
            {
                subMenu4();
                choice = getChoice( 3 );
                
                switch (choice)
                {
                case 1:
                    section4_1(group, project);
                    break;
                case 2:
                    section4_2(group, project);
                    break;
                
                default:
                    break;
                }
            } while (choice != 3);
            

        }
        
        // SECTION 5
        else if ( choice == 5 )
        {
            section5(group, project);
        }

        // SECTION 6
        else if ( choice == 6 )
        {
            section6(group, project);
        }
    
    } while ( choice != 7 );
    
    cout << "Thank you!" << endl;
    cout << "Bye bye!" << endl;

}

// ***********************************************************************
//                              MENU SECTION
// ***********************************************************************

void mainMenu()
{
    cout << "\n================== MENU ==================" << endl
         << "| 1. Group information                   |" << endl
         << "| 2. Project information                 |" << endl
         << "| 3. Statistic                           |" << endl
         << "| 4. Overall statistic                   |" << endl
         << "| 5. Group did not submit / late         |" << endl
         << "| 6. Display the whole table             |" << endl
         << "| 7. Quit                                |" << endl
         << "==========================================" << endl;
}

void subMenu1()
{
    cout << "\n======== SECTION 1: GROUP INFORMATION ========\n"
         << "| 1. Input groups information                |\n"
         << "| 2. Display all students group by group     |\n"
         << "| 3. Display a specific group information    |\n"
         << "| 4. Save group information                  |\n"
         << "| 5. Back                                    |\n"
         << "==============================================" << endl;
}

void subMenu2()
{
    cout << "\n======= SECTION 2: PROJECT INFORMATION =======\n"
         << "| 1. Input deadline for projects             |\n"
         << "| 2. Input submission date of groups         |\n"
         << "| 3. Back                                    |\n"
         << "==============================================" << endl;
}

void subMenu3()
{
    cout << "\n================== SECTION 3: STATISTIC ==================\n"
         << "| 1. Display status of a project                          |\n"
         << "| 2. Display status of all projects of a specific group   |\n"
         << "| 3. Back                                                 |\n"
         << "===========================================================" << endl;
}

void subMenu4()
{
    cout << "\n=========== SECTION 4: OVERALL STATISTIC ===========\n"
         << "| 1. Display information of project in the past    |\n"
         << "| 2. Display information of project in a period    |\n"
         << "| 3. Back                                          |\n"
         << "====================================================" << endl;
}

// ***********************************************************************
//                              SECTIONS
// ***********************************************************************

// Vu Tuan Son 1575302
// Section 1.1 GROUP INFORMATION
void section1_1( vector<Group> &group )
{
    cout << "\n---------------------------------------------\n"
         << "|      SECTION 1.1: GROUP INFORMATION       |\n"
         << "---------------------------------------------\n";

    for (int i = 0; i < GROUP_SIZE; i++)
    {
        group.push_back( getGroupInfo(i) );
    }

}

// Vu Tuan Son 1575302
// Section 1.2 DISPLAY ALL STUDENT IN ALL GROUPS
void section1_2(vector<Group> group)
{
    cout << "\n-------------------------------------------------------------\n"
         << "|      SECTION 1.2: DISPLAY ALL STUDENT IN ALL GROUPS       |\n"
         << "-------------------------------------------------------------\n";


    // Display header GROUP, STUDENT NAME, and ID
    header1();
    for (int i = 0; i < group.size(); i++)
    {
        cout << setw(WGROUP) << (i + 1)
             << setw(WNAME) << group[i].studentName[0]
             << group[i].studentID[0] << endl;
        
        for (int j = 1; j < group[i].studentName.size(); j++)
        {
            cout << setw(WGROUP) << "";
            cout << setw(WNAME) << group[i].studentName[j]
                 << group[i].studentID[j] << endl;
        }
        cout << "-----------------------------------------------\n";
    }
    
}



// Vu Tuan Son 1575302
// SECTION 1.3: DISPLAY A SPECIFIC GROUP'S MEMBERS
// User input a specific group number, then display all student
// in the given group
void section1_3( vector<Group> group )
{
    cout << "\n-----------------------------------------------------------\n"
         << "|     SECTION 1.3: DISPLAY A SPECIFIC GROUP'S MEMBERS     |\n"
         << "-----------------------------------------------------------\n";      
    
    // Get group index
    int group_index = getInt("group number") - 1;

    // Display header GROUP, STUDENT NAME, and ID
    header1();

    // Display group number, the first student in group
    cout << setw(WGROUP) << group_index + 1
         << setw(WNAME) << group[group_index].studentName[0]
         << group[group_index].studentID[0] << endl; 
        
        // Then display all the other students
        for (int j = 1; j < group[group_index].studentName.size(); j++)
        {
            cout << setw(WGROUP) << "";
            cout << setw(WNAME) << group[group_index].studentName[j]
                 << group[group_index].studentID[j] << endl;
        }
        cout << "-----------------------------------------------\n";
}

// Mai Quang Dao
void section1_2_Dao(vector<Group> group)
{
    int wGrp = 8,
        wStu = 15,
        wID = 20;
    cout << "\nHere all " << GROUP_SIZE << " information: \n";

    //display the first line of the table
    cout << left << setw(wGrp) << "\nGroup" << setw(wStu) << "Student" << setw(wID) << "ID" << endl;

    //display the content of the table
    for (int grIndex = 0; grIndex < group.size(); grIndex++)
    {
        cout << left << setw(wGrp) << grIndex + 1; //this is outside the inner loop since group numbers are printed once for each group 
        for (int stdIndex = 0; stdIndex < group[grIndex].studentName.size(); stdIndex++)
        {
            if (stdIndex == 0) //the first student displayed doesn't have to leave space for group number
                cout << left << setw(wStu) << group[grIndex].studentName[stdIndex]
                << setw(wID) << group[grIndex].studentID[stdIndex] << endl;

            else //the following members have to
                cout << left << setw(wGrp) << " " << setw(wStu) << group[grIndex].studentName[stdIndex]
                << setw(wID) << group[grIndex].studentID[stdIndex] << endl;
        }
        cout << endl;
    }
}

// Mai Quang Dao
void section1_3_Dao(vector<Group> group)
{
    int wGrp = 8,
        wStu = 15,
        wID = 10;

    int chosen = getInt("group you want to check");

    cout << "\nThese are all group #" << chosen << "'s members: \n";
    cout << left << setw(wGrp) << "Group" << setw(wStu) << "Student" << setw(wID) << "ID" << endl;
    cout << left << setw(wGrp) << chosen;
    chosen--; //decrement this by one since the index starts from zero
    for (int i = 0; i < group[chosen].studentName.size(); i++)
    {
        if (i == 0)
            cout << left << setw(wStu) << group[chosen].studentName[i] << setw(10) << group[chosen].studentID[i] << endl;
        else
            cout << left << setw(wGrp) << " " << setw(wStu) << group[chosen].studentName[i] << setw(wID) << group[chosen].studentID[i] << endl;
    }

}

// Vu Tuan Son 1575302
// SECTION 1.4: SAVE GROUP INFORMATION
void section1_4( vector<Group> group )
{
    cout << "\n-----------------------------------------------\n"
         << "|     SECTION 1.4: SAVE GROUP INFORMATION     |\n"
         << "-----------------------------------------------\n";      
    
    ofstream writeFile;
    // File will be save to this location
    writeFile.open("D:\\CS255CourseProject\\groups_information.txt");

    // First, write header to file
    writeFile << "\n-----------------------------------------------\n";
    writeFile << left;
    writeFile << setw(WGROUP) << "GROUP"
         << setw(WNAME) << "STUDENT NAME"
         << "ID\n";
    writeFile << "-----------------------------------------------\n";

    // Then, write other contents
    for (int i = 0; i < group.size(); i++)
    {
        // This is the first line of group
        writeFile << setw(WGROUP) << (i + 1)            // Group number
             << setw(WNAME) << group[i].studentName[0]  // Student name
             << group[i].studentID[0] << endl;          // Student ID
        
        // The following lines
        for (int j = 1; j < group[i].studentName.size(); j++)
        {
            writeFile << setw(WGROUP) << "";
            writeFile << setw(WNAME) << group[i].studentName[j] // Student name
                 << group[i].studentID[j] << endl;              // Student ID
        }
        writeFile << "-----------------------------------------------\n";
    }
    writeFile.close();  // Close file
    
    cout << "File was saved to: " << "D:\\CS255CourseProject\\groups_information.txt" << endl;
}

// Vu Tuan Son 1575302
// SECTION 2.2 INPUT DEADLINE FOR PROJECTS
void section2_1( vector<Project> &project )
{
    cout << "\n----------------------------------------------------\n"
         << "|     SECTION 2.1: INPUT DEADLINE FOR PROJECTS     |\n"
         << "----------------------------------------------------\n";
    
    int numOfProject;

    numOfProject = getInt("number of project");
    
    for (int i = 0; i < numOfProject; i++)
    {
        project.push_back(getDeadline(i));
    }

}

// Vu Tuan Son 1575302
// SECTION 2.2 INPUT GROUP SUBMISSION DATE
void section2_2( vector<Group> &group, vector<Project> &project )
{
    cout << "\n----------------------------------------------------\n"
         << "|     SECTION 2.2: INPUT GROUP SUBMISSION DATE     |\n"
         << "----------------------------------------------------\n";
    
    char choice;
    int group_index;
    int project_index;
    
    do
    {
        do
        {
            group_index = getInt("group") - 1;
            if ( group_index >= GROUP_SIZE || group_index + 1 == 0 )
            {
                cout << "ERROR!\n";
                cout << "Max of group is " << GROUP_SIZE << endl;
            }
            
        } while ( group_index >= GROUP_SIZE || group_index + 1 == 0 );
        
        do
        {
            project_index = getInt("project") - 1;
            if ( project_index >= project.size() || project_index + 1 == 0  )
            {
                cout << "ERROR!\n";
                cout << "Max of project is " << project.size() << endl;
            }
        } while ( project_index >= project.size() || project_index + 1 == 0 );
        
        
        getSubmissionDate(project_index, project, group_index, group);

        cout << "\nContinue? ";
        cin.get(choice);
        cin.ignore();

    } while ( choice == 'Y' || choice == 'y');
    
}

// Vu Tuan Son 1575302
// SECTION 3.1: DISPLAY A SPECIFIC PROJECT
void section3_1( vector<Group> group, vector<Project> project )
{
    cout << "\n---------------------------------------------------\n"
         << "|     SECTION 3.1: DISPLAY A SPECIFIC PROJECT     |\n"
         << "---------------------------------------------------\n";   
    int project_index;
    

    do
    {
        project_index = getInt("project") - 1;
        if ( project_index >= project.size() )
        {
            cout << "ERROR!\n";
            cout << "Max of project is " << project.size() << endl;
        }
    } while ( project_index >= project.size() );

    cout << "\n-----------------------\n";
    cout << left;

    // Display headers
    cout << setw(WGROUP) << "GROUP"
         << "PROJECT " << project_index + 1;

    cout << "\n-----------------------\n";

    
    // Display status of all projects
    for (int i = 0; i < group.size(); i++)
    {
        cout << setw(WGROUP) << i + 1
             << getStatus(group[i].projectStatus[project_index]) << endl;
    }

    cout << "-----------------------\n";
    

        
}

// Mai Quang Dao
void section3_1_Dao(vector<Group> group, vector<Project> project)
{
    int wPrj = 10,
        wGrp = 7,
        wGrpn = 3;
    int chosen = getInt("project you want to check");

    while (chosen > project.size())
    {
        cout << "Invalid input since there are " << project.size() << " projects";
        chosen = getInt("project you want to check");
    }

    cout << "This is status of project #" << chosen << ": " << endl;
    cout << left << setw(wPrj) << "Project";
    for (int i = 0; i < group.size(); i++)
        cout << left << setw(wGrp) << "Group " << setw(wGrpn) << i + 1;
    cout << endl;
    cout << left << setw(wPrj) << chosen;
    chosen--;
    for (int i = 0; i < group.size(); i++)
    {
        if (group[i].projectStatus[chosen] == PENDING) //1 = pending
            cout << left << setw(wGrp) << "Pending" << setw(wGrpn) << " ";
        else if (group[i].projectStatus[chosen] == ONTIME) //2 = done
            cout << left << setw(wGrp) << "On Time" << setw(wGrpn) << " ";
        else if (group[i].projectStatus[chosen] == LATE) //3 = late
            cout << left << setw(wGrp) << "   Late" << setw(wGrpn) << " ";
        else if (group[i].projectStatus[chosen] == NOTYET)
            cout << left << setw(wGrp) << "Not Yet" << setw(wGrpn) << " ";
    }
}

// Vu Tuan Son 1575302
// SECTION 3.2: DISPLAY STATUS OF ALL PROJECTS OF A GROUP
void section3_2( vector<Group> group, vector<Project> project )
{
    cout << "\n------------------------------------------------------------------\n"
         << "|     SECTION 3.2: DISPLAY STATUS OF ALL PROJECTS OF A GROUP     |\n"
         << "------------------------------------------------------------------\n";
    int group_index;
    
    // Get index of the input group
    do
        {
            group_index = getInt("group") - 1;
            if ( group_index >= GROUP_SIZE )
            {
                cout << "ERROR!\n";
                cout << "Max of group is " << GROUP_SIZE << endl;
            }
            
        } while ( group_index >= GROUP_SIZE );
    
    cout << "\n--------------------------------------------------------------------\n";
    cout << left;

    // Display headers
    header2(project.size());

    // Display informations    
    cout << setw(WGROUP) << (group_index + 1);  // Group numbber
    
    // Display all status of the choosen project
    for (int i = 0; i < group[group_index].projectStatus.size(); i++)
    {
        cout << setw(WGROUP) << getStatus(group[group_index].projectStatus[i]);
    }

    cout << "\n--------------------------------------------------------------------\n";
    
}

// Vu Tuan Son 1575302
// SECTION 4.1: DISPLAY INFORMATION IN THE PAST
void section4_1(vector<Group> group, vector<Project> project)
{
    cout << "\n--------------------------------------------------------\n"
         << "|     SECTION 4.1: DISPLAY INFORMATION IN THE PAST     |\n"
         << "--------------------------------------------------------\n";
    
    time_t now;
    time(&now);                 // Get the current time
    vector<int> past_list;   // to save all project to be printed out

    // Check if project is in the past or not
    // add project_index to the list to be printed out
    // if it is in the past
    for (int i = 0; i < project.size(); i++)
    {
        if (mktime(&project[i].deadline) <= now)
        {
            past_list.push_back(i);                 
        }
    }

    // Header, display project header of past projects
    header4(past_list);
    
    // Display group number and past project status
    for (int i = 0; i < group.size(); i++)
    {
        displaySection4_1(i, group, project, past_list);
    }


    // START WRITING TO FILE Overall_Statistic_Past.txt
    save_file_section_4("Past", past_list, group, project);
    
    cout << "File was saved to: " << "D:\\CS255CourseProject\\Overall_Statistic_Past.txt" << endl;
}

// Vu Tuan Son 1575302
// SECTION 4.2: DISPLAY INFORMATION IN A PERIOD
void section4_2(vector<Group> group, vector<Project> project)
{
    cout << "\n--------------------------------------------------------\n"
         << "|     SECTION 4.2: DISPLAY INFORMATION IN A PERIOD     |\n"
         << "--------------------------------------------------------\n";
    
    struct tm start, end;
    time_t now;
    time(&now);     // Get the current time
    vector<int> period_list;   // to save all project to be printed out

    // Fill struct time start and end. Tried to use memset to fill it
    // But it doesn't work as expected
    // It won't cause any problem because I use only min, hour, day
    // mon, and year to compare with user input
    start = end = *localtime(&now); 

    // GET THE PERIOD OF TIME
    do      
    {
        cout << "\nENTER BEGINNING TIME\n";

        start.tm_year = getYear() - 1900;
        start.tm_mon = getMonth() - 1;
        start.tm_mday = getDate(start.tm_mon + 1, start.tm_year + 1900);

        cout << "\nENTER ENDING TIME\n";

        end.tm_year = getYear() - 1900;
        end.tm_mon = getMonth() - 1;
        end.tm_mday = getDate(start.tm_mon + 1, start.tm_year + 1900);

        // ERROR if start time is less than end time
        if ( mktime(&start) >= mktime(&end) )
        {
            cout << "ERROR!\n";
            cout << "Invalid time period!\n";
        }  
    } while( mktime(&start) >= mktime(&end) );

    // If project deadline is in the given period
    // Write its index into period_list
    for (int i = 0; i < project.size(); i++)
    {
        if ( !dateInPeriod(start, end, project[i].deadline) )
        {
            period_list.push_back(i);
            cout << i << endl;
        }
        
    }

    // Display the period
    cout << "\nPERIOD: from "
         << start.tm_year + 1900 << "/" << start.tm_mon + 1 << "/" << start.tm_mday
         << " to "
         << end.tm_year + 1900 << "/" << end.tm_mon + 1 << "/" << end.tm_mday
         << endl;

    // Display the header
    header4(period_list);
    
    // Display group number and project status of the given period
    for (int i = 0; i < group.size(); i++)
    {
        displaySection4_1(i, group, project, period_list);
    }
    
    save_file_section_4("Period", period_list, group, project);
    cout << "File was saved to: " << "D:\\CS255CourseProject\\Overall_Statistic_Period.txt" << endl;
} 


void section5(vector<Group> group, vector<Project> project)
{
    cout << "\n----------------------------------------------------------\n"
         << "|     SECTION 5: DISPLAY GROUP DID NOT SUBMIT / LATE     |\n"
         << "----------------------------------------------------------\n";
    
    cout << "\nGROUPS SUBMIT LATE ARE";

    string group_name;

    for (int i = 0; i < project.size(); i++)
    {   
        cout << "\nPROJECT " << i + 1 << ": ";
        for (int j = 0; j < group.size(); j++)
        {
            if (group[j].projectStatus[i] == LATE)
            {   
                cout << j + 1 << "  ";
            }
        }
    }

    cout << "\n\nGROUPS DID NOT SUBMIT ARE";

    for (int i = 0; i < project.size(); i++)
    {   
        cout << "\nPROJECT " << i + 1 << ": ";
        for (int j = 0; j < group.size(); j++)
        {
            if (group[j].projectStatus[i] == NOTYET)
            {   
                cout << j + 1 << "  ";
            }
        }
    }
    cout << endl;
}

// Vu Tuan Son 1575302
// SECTION 6: DISPLAY THE WHOLE TABLE
void section6(vector<Group> group, vector<Project> project)
{
    cout << "\n----------------------------------------------\n"
            << "|     SECTION 6: DISPLAY THE WHOLE TABLE     |\n"
            << "----------------------------------------------\n";
    
    cout << left;

    // Display headers
    header2(project.size());

    for (int i = 0; i < group.size(); i++)
    {
        // Display informations    
        cout << setw(WGROUP) << (i + 1);  // Group numbber
        
        // Display all status of the choosen project
        for (int j = 0; j < group[i].projectStatus.size(); j++)
        {
            cout << setw(WGROUP) << getStatus(group[i].projectStatus[j]);
        }
        cout << endl;
    }
    

}


// ***********************************************************************
//                            MAIN FUNCTIONS
// ***********************************************************************

// Vu Tuan Son 1575302
// Get student names and student 
Group getGroupInfo( int index )
{
    Group g;
    int numOfStudent;
    vector<string> groupID_list;
    

    cout << "\nENTER GROUP " << index + 1 << " INFORMATION:" << endl;

    // Get #group members
    do
    {
        numOfStudent = getInt( "number of students in this group" );
        
        if ( numOfStudent == 0 )
        {
            cout << "This group must have at least 1 member!\n";
        }
        
    } while (numOfStudent < 1);   

    // Get name for each member
    for (int i = 0; i < numOfStudent; i++)
    {
        g.studentName.push_back( getStudentInfo(i, groupID_list));
    }

    g.studentID = groupID_list;

    return g;
}

// Vu Tuan Son 1575302
/****************************************************************************
*  Get student's full name and ID                                           *
*  There are 2 parts                                                        *
*  Part 1: Get student fullname                                             *
*  Part 2: Get student ID (which is identification to process conditions)   *
*  Conditions:                                                              *
*       1. ID must match name                                               *
*       2. No duplicate of any student in one group                         *
*       3. One student can be in maximum 2 groups                           *
*  If all conditions is met, return ID                                      *
****************************************************************************/
string getStudentInfo( const int index, vector<string> &groupID_list )
{
    string  first, middle, last,
            fullName, ID;

    while ( true )
    {
        // Get first, middle and full name, then combines them into fullName
        cout << "\nENTER STUDENT " << index + 1 << " NAME\n";
        
        do
        {
            
            first = getPartOfName("First");
            middle = getPartOfName("Middle");
            last = getPartOfName("Last");

            fullName = first + ' ' + middle + ' ' + last;
            
            if ( !isText(fullName) )
            {
                cout << "Input Invalid!" << endl;
            }
            
        }while( !isText(fullName) );

        // Format full name
        fullName = capName(fullName);

        // Get ID
        ID = getStudentID(index);
        
        // ERROR if ID doesn't match NAME
        if ( !nameCheck(fullName, ID) )
        {
            cout << "\nERROR!\n";
            cout << "This ID belongs to " << NAME_LIST[findNameIndex(ID)] << endl;
        }

        // ERROR if the student is in more than 2 groups
        else if ( !studentDuplicate(ID) )
        {
            cout << "\nERROR!\n";
            cout << fullName << " is already in other two groups!\n";
        }

        // ERROR if the student is already in this group
        else if ( !ingroupDuplicate(ID, groupID_list) )
        {
            cout << "\nERROR!\n";
            cout << fullName << "\n" << ID << "\n" << "is already in this group!\n";
        }

        else
        {
            break;
        }
    }
    
    ID_LIST.push_back(ID);
    groupID_list.push_back(ID);
    NAME_LIST.push_back(fullName);

    return fullName;
}


// Vu Tuan Son 1575302
// Return index of Name based on ID
int findNameIndex( const string ID )
{
    for (int i = 0; i < ID_LIST.size(); i++)
    {
        if ( ID_LIST[i] == ID )
        {
            return i;
        }
    }
    return 0;
}


// Vu Tuan Son 1575302
// Get student ID
string getStudentID( const int index )
{
    string input;

    cout << "Enter student " << index + 1 << " ID (" << ID_SIZE << " digits): ";

    do
    {
        cin >> input;
        cin.ignore();

        if ( !isID(input) )
        {
            cout << "Input invalid!" << endl;
            cout << "Enter ID (" << ID_SIZE << " digits): ";
        }     

    } while ( !isID(input) );
     
    return input; 
}

// Vu Tuan Son 1575302
// Get deadline for project
Project getDeadline( const int index )
{
    time_t now;
    Project project;

    time(&now);
    project.deadline = *localtime(&now);

    cout << "\nENTER PROJECT " << index + 1 << " DEADLINE\n";

    project.deadline.tm_year = getYear() - 1900;
    project.deadline.tm_mon = getMonth() - 1;
    project.deadline.tm_mday = getDate(project.deadline.tm_mon + 1,
                                       project.deadline.tm_year + 1900);


    return project;
}


// Vu Tuan Son 1575302
// Get submission date for project[project_index] of group[group_index]
void getSubmissionDate( const int project_index, vector<Project> project,
                        const int group_index, vector<Group> &group )
{
    struct tm submit_time;
    time_t now;
    time(&now);     // Get the current time
    
    cout << "\nENTER SUBMISSION DATE OF PROJECT " << project_index + 1 << endl;

    // Fill struct submit_time. Tried to use memset to fill it
    // But it doesn't work as expected
    // It won't cause any problem because I use only min, hour, day
    // mon, and year to compare with user input
    submit_time = *localtime(&now);  

    submit_time.tm_year = getYear() - 1900;
    submit_time.tm_mon = getMonth() - 1;
    submit_time.tm_mday = getDate(submit_time.tm_mon + 1, submit_time.tm_year + 1900);
    submit_time.tm_hour = getHour();
    submit_time.tm_min = getMinute();

    if (mktime(&submit_time) < mktime(&project[project_index].deadline))
    {
        group[group_index].projectStatus[project_index] = ONTIME;
        cout << "On time!\n";
    }

    else
    {
        group[group_index].projectStatus[project_index] = LATE;
        cout << "Late\n";
    }
}


// Vu Tuan Son 1575302
// Fill all project status of all groups. Before PRESENT will be NOT YET
// Ater PRESENT will be PENDING
void fillOutProjectStatus( vector<Group> &group, vector<Project> project)
{
    // Set index point to the end of group.projectStatus
    // This will help preventing bugs when adding more deadlines
    int i = group[0].projectStatus.size();

    for ( i; i < project.size(); i++ )
    {
        for ( int j = 0; j < group.size(); j++ )
        {
            fillProjcetStatus(i, project, j, group);
        }
        
    }
    
}

// Vu Tuan Son 1575302
// Display all project in the past for section 4.1
// It gets past project index from past_list, then display status of
// group[i].projectStatus[ past project index ]
void displaySection4_1( const int group_index,   vector<Group> group,
                        vector<Project> project, vector<int> past_list )
{
    cout << left;
    // Print out group number
    cout << setw(WGROUP) << (group_index + 1);
    // Print out status of all projects in project_list
    for (int i = 0; i < past_list.size(); i++)
    {
        cout << setw(WGROUP) << getStatus(group[group_index].projectStatus[past_list[i]]);
    }
    
    cout << "\n--------------------------------------------------------------------\n";


    
}



// ***********************************************************************
//                            SUB FUNCTIONS
// ***********************************************************************

// Vu Tuan Son 1575302
// This function will save information to file Overall_Statistic_Period.txt
void save_file_section_4(string fileName, vector<int> print_list,
                         vector<Group> group, vector<Project> project)
{
    fileName = "D:\\CS255CourseProject\\Overall_Statistic_" + fileName + ".txt";
    ofstream writeFile;
    writeFile.open(fileName.c_str());

    // WRITE HEADER
    writeFile << left;
    writeFile << setw(WGROUP) << "GROUP";

    // Display PROJECT # header
    for (int i = 0; i < print_list.size(); i++)
    {
        writeFile  << "PROJECT " << setw(WGROUP - 8) << print_list[i] + 1;
    }

    writeFile << endl;

    // WRITE CONTENTS
    for (int i = 0; i < group.size(); i++)
    {
        // Print out group number
        writeFile << setw(WGROUP) << (i + 1);

        // Print out status of all projects in project_list
        for (int j = 0; j < print_list.size(); j++)
        {
            writeFile << setw(WGROUP) << getStatus(group[i].projectStatus[print_list[j]]);
        }

        writeFile << endl;
    }

    writeFile << endl;

    writeFile.close();
}


// Vu Tuan Son 1575302
// Header: GROUP    STUDENT NAME    ID
void header1()
{
    cout << "\n-----------------------------------------------\n";
    cout << left;
    cout << setw(WGROUP) << "GROUP"
         << setw(WNAME) << "STUDENT NAME"
         << "ID\n";
    cout << "-----------------------------------------------\n";
}

// Vu Tuan Son 1575302
// Full header of input projects
void header2( int num_of_project )
{
    cout << setw(WGROUP) << "\nGROUP";

    // Display PROJECT # header
    for (int i = 0; i < num_of_project; i++)
    {
        cout  << "PROJECT " << setw(WGROUP - 8) << i + 1;
    }
    cout << endl;
}

void header4( vector<int> project_list )
{
    cout << "\n--------------------------------------------------------------------\n";
    cout << left;
    cout << setw(WGROUP) << "GROUP";

    // Display PROJECT # header
    for (int i = 0; i < project_list.size(); i++)
    {
        cout  << "PROJECT " << setw(WGROUP - 8) << project_list[i] + 1;
    }
    cout << "\n--------------------------------------------------------------------\n";
}

// Vu Tuan Son 1575302
// Sub function of fillOutProjectStatus
void fillProjcetStatus( const int project_index, vector<Project> project,
                        const int group_index, vector<Group> &group )
{
    struct tm currentTime;
    time_t now;
    time(&now);

    currentTime = *localtime(&now);

    // Compare current time to deadline
    if ( mktime(&project[project_index].deadline) < now )
    {
        group[group_index].projectStatus.push_back(NOTYET);
    }

    else
    {
        group[group_index].projectStatus.push_back(PENDING);
    }
}

// Vu Tuan Son 1575302
// Return project status name
string getStatus(const int status)
{
    switch (status)
    {
    case PENDING:
        return "Pending";
        break;
    case ONTIME:
        return "On time";
        break;
    case LATE:
        return "Late";
        break;
    case NOTYET:
        return "Not yet";
        break;
    }
    return "ERROR";
}

// Vu Tuan Son 1575302
// Return a choice for a specific number of choices
int getChoice( const int numOfChoice )
{
    string input;

    do
    {
        cout << "Enter your choice: ";
        cin >> input;

        if ( !isInt(input) )
        {
            cout << "Input invalid!" << endl;
        }

        else
        {
            if ( !isChoice( input, numOfChoice ))
            {
                cout << "Input invalid!" << endl;
            }
        }     
        
    } while ( !isChoice( input, numOfChoice ));

    int output = str_to_int(input);
    return output;
}

// Vu Tuan Son 1575302
// Get an integert for "title"
int getInt( const string title )
{
    string input;

    cout << "Enter " << title << ": ";
    do
    {
        cin >> input;
        cin.ignore(1);

        if ( !isInt(input) )
        {
            cout << "Input Invalid!" << endl;
            cout << "Enter number: ";
        }
        
    } while( !isInt(input) );

    int output = str_to_int(input);
    return output;
}

// Vu Tuan Son 1575302
// Get first, middle and last name
string getPartOfName( const string title )
{
    string name;
    while (true)
    {
        cout << title << " name: ";
        getline(cin, name);
        if ( !isText(name) || !haveSpace(name) || name.size() <2)
        {
            cout << "Input Invalid!" << endl;
            cin.clear();
        }
        else
        {
            break;
        }
    }
    return name;
}

// Vu Tuan Son 1575302
// Return fullname in the right format
string capName( string input )
{
    // Lower all characters
    for (int i = 0; i < input.size(); i++)
    {
        input[i] = tolower(input[i]);
    }
    
    // Upper first character and all characters that are after a space
    input[0] = toupper(input[0]);

    for (int i = 1; i < input.size() - 1; i++)
    {
        if (input[i] == ' ')
        {
            input[i + 1] = toupper(input[i + 1]);
        }
        
    }
    
    return input;
}

// Vu Tuan Son 1575302
// Get hour from 0 to 23
int getHour()
{
    int hour;
    do
    {
        hour = getInt("hour (0 - 23)");

        if ( hour > 23 )
        {
            cout << "\nInput Invalid!\n";
        }
        
    } while ( hour > 23 );

    return hour;
}

// Vu Tuan Son 1575302
// Get minute from 0 to 59
int getMinute()
{
    int minute;
    do
    {
        minute = getInt("minute (0 - 59)");

        if ( minute > 59 )
        {
            cout << "\nInput Invalid!\n";
        }
        
    } while ( minute > 59 );

    return minute;
}

// Vu Tuan Son 1575302
// Get date based on month and year, including leap year condition
int getDate( const int month, const int year )
{
    int day;
    do
    {
        day = getInt("date");
        if ( day > dayOfMonth(month, year) || day == 0 )
        {
            cout << "ERROR!\n";
            cout << "Month " << month << " has only " << dayOfMonth(month, year) << " days!\n";
        }
        
    } while ( day > dayOfMonth(month, year) || day == 0 );

    return day;
}

// Vu Tuan Son 1575302
// Get month (12 months)
int getMonth()
{
    int month;
    do
    {
        month = getInt("month");

        if ( month > 12 || month == 0 )
        {
            cout << "\nInput Invalid!\n";
        }
        
    } while ( month > 12 || month == 0);

    return month;
}

// Vu Tuan Son 1575302
// Get year. Year must be between 1900 and 2077
int getYear()
{
    int year;
    do
    {
        year = getInt("year");

        if ( year < 1900 || year > 2077 ) // Cyberpunk 2077??
        {
            cout << "\nInput Invalid!\n";
        }
        
    } while ( year < 1900 || year > 2077 );

    return year;
}

// Vu Tuan Son 1575302
// Return number of days in a month, include leap year case;
int dayOfMonth( const int month, const int year )
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        break;
    
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;
    
    case 2:
        if ( !isLeapYear(year) )
        {
            return 28;
        }
        else
        {
            return 29;
        }
        break;
        
    default:
        break;
    }
    return 0;
}


// ***********************************************************************
//                          BOOL FUNCTIONS
// ***********************************************************************

// Vu Tuan Son 1575302
// Check for duplicates in one group
bool ingroupDuplicate( string ID, vector<string> studentID )
{
    int sum = 0;
    for (int i = 0; i < studentID.size(); i++)
    {
        if ( ID == studentID[i] )
        {
            sum ++;
        }
        
    }

    if ( sum >= 1 )
    {
        return false;
    }
    
    return true;
}

// Vu Tuan Son 1575302
// Check for duplicates using student ID list
bool studentDuplicate( string ID )
{
    int sum = 0;
    for (int i = 0; i < ID_LIST.size(); i++)
    {
        if ( ID == ID_LIST[i] )
        {
            sum ++;
        }
        
    }
    
    if ( sum >= 2 )
    {
        return false;
    }
    
    return true;
}

// Vu Tuan Son 1575302
// Return true if input is ID_SIZE digits
bool isID( const string input )
{
    if ( input.size() != ID_SIZE )
    {
        return false;
    }
    
    for (int i = 0; i < input.size(); i++)
    {
        if ( !isdigit(input[i]) )
        {
            return false;
        }
        
    }
    return true;
    
}

// Vu Tuan Son 1575302
// Return true if input dont' contain any spaces
bool haveSpace( const string input )
{
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ')
        {
            return false;
        }
        
    }
    return true;
}

// Vu Tuan Son 1575302
// Return TRUE if input contains only integers
bool isInt( const string input )
{
    if ( input[0] ==  0 )
    {
        return false;
    }
    
    for (int i = 0; i < input.size(); i++)
    {
        if ( !isdigit(input[i]) )
        {
            return false;
        }
        
    }

    return true;
}

// Vu Tuan Son 1575302
// Return TRUE if and only if input is merely text
bool isText( const string input )
{
    for (int i = 0; i < input.size(); i++)
    {
        if ( !isalpha(input[i]) && input[i] != ' ' )
        {
            return false;
        }
        
    }
    return true;
    
}

// Vu Tuan Son 1575302
// Return true if ID is already in the list
bool IDinList( const string ID )
{
    for (int i = 0; i < ID_LIST.size(); i++)
    {
        if ( ID == ID_LIST[i] )
        {
            return true;
        }
        
    }
    return false;
}

// Vu Tuan Son 1575302
// Return true if name is match ID
bool nameCheck( const string name, const string ID )
{
    int nameIndex;

    if ( IDinList(ID) )
    {
        nameIndex = findNameIndex(ID);
        if ( name != NAME_LIST[nameIndex] )
        {
            return false;
        }
        
    }
    
    return true;
}

// Return true if input is in range from 1 to numOfChoice
bool isChoice( const string input, const int numOfChoice )
{
    for (int i = 1; i <= numOfChoice; i++)
    {
        if ( str_to_int(input) == i )
        {
            return true;
        }

    }
    return false;
}

// Vu Tuan Son 1575302
// Return TRUE if input is a leap year
bool isLeapYear( int year )
{
    if ( year % 4 == 0 )
    {
        if ( year % 100 == 0 )
        {
            if ( year % 400 == 0 )
            {
                return true;
            }

            else
            {
                return false;
            }
        }
        
        else
        {
            return true;
        }
        
    }

    return false;
    
}

// Vu Tuan Son 1575302
// Return true if deadline is out of period
bool dateInPeriod( struct tm start, struct tm end, struct tm deadline )
{   
    if (   mktime(&deadline) < mktime(&start)
        || mktime(&deadline) > mktime(&end) )
    {
        return true;
    }
    
    return false;
}


// ***********************************************************************
//                            CONVERTING DATA
// ***********************************************************************

// Vu Tuan Son 1575302
// Convert string to int
int str_to_int ( string input )
{
    stringstream conv(input);
    int output = 0;
    conv >> output;
    return output;
}
