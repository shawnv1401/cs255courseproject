#include <iostream>
#include <string>
#include <cstring>

#include <sstream>
#include <vector>

using namespace std;

struct Project
{
    bool onTime;
    int deadline;
};

struct Group
{
    int numStudent;
    vector<string> studentName;

    Project project;
};


void mainMenu();

int getInt(string);
string getFullName(int);

string getPartOfName(string);
string capName(string);


bool haveSpace(string);
bool isNumber(string);
bool isString(string);


int str_to_int(string);
double str_to_double(string);
bool is_choice(string);
void menu1();


Group getGroupInfo(int);


// M A I N  M E N U

int main()
{

    string a;
    a = getFullName(0);
    cout << a;

}




Group getGroupInfo(int groupNum)
{
    Group g;

    cout << "Enter group " << groupNum + 1 << " information:" << endl;
    g.numStudent = getInt("number of students in this group");

    for (int i = 0; i < g.numStudent; i++)
    {
        g.studentName[i] = getFullName(i);
    }
    return g;
}




void mainMenu()
{
    cout << "================== MENU ==================" << endl
         << "| 1. Group information                   |" << endl
         << "| 2. Project information                 |" << endl
         << "| 3. Statistic                           |" << endl
         << "| 4. Overall statistic                   |" << endl
         << "| 5. Find late submition groups          |" << endl
         << "| 6. Quit                                |" << endl
         << "==========================================" << endl;
}

// Return input in integer with title is "Enter *title*: ".
int getInt(string title)
{
    string input;

    cout << "Enter " << title << ": ";
    while (true)
    {
        cin >> input;
        if ( !is_choice(input) )
        {
            cout << "Input Invalid!" << endl;
            cout << "Enter number: ";
        }
        else
            break;
        
    }

    int output = str_to_int(input);
    return output;
}

// Get first, middle and last name
string getPartOfName(string title)
{
    string name;
    while (true)
    {
        cout << title << " name: ";
        getline(cin, name);
        if ( !isString(name) || !haveSpace(name) )
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

string capName(string input)
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


// Return full name of a student number stdNum + 1
string getFullName(int stdNum)
{
    string first, middle, last, fullName;
    
    // Get first, middle and full name, then combines them into fullName
    cout << "Enter student " << stdNum + 1 << " name\n";
    do
    {
        
        first = getPartOfName("First");
        middle = getPartOfName("Middle");
        last = getPartOfName("Last");

        fullName = first + ' ' + middle + ' ' + last;
        
        if ( !isString(fullName) )
        {
            cout << "Input Invalid!" << endl;
        }
        
    }while( !isString(fullName) );

    // Format full name
    fullName = capName(fullName);

    return fullName;
}

bool haveSpace(string input)
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

// Return TRUE if and only if input is integer or double
bool isNumber(string input)
{
    int dot = 0;
    if (!isdigit(input[0]))
    {
        return false;
    }
    
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '.')
        {
            dot++;
        }
        else if (isalpha(input[i]))
        {
            return false;
        } 
    }

    if (dot > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

// Return TRUE if and only if input is string
bool isString(string input)
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

// Return TRUE if and only if input is 1, 2, 3, 4, 5, or 6
bool is_choice(string input)
{
    if (isNumber(input))
    {
        int choice = str_to_int(input);
        switch (choice)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            return true;
            break;
        
        default:
            return false;
            break;
        }
    }
    else
        return false;
    
    return NULL;
}

// Vu Tuan Son 1575302
// Convert string to int
int str_to_int (string input)
{
    stringstream conv(input);
    int output = 0;
    conv >> output;
    return output;
}

// Vu Tuan Son 1575302
// Convert string to double
double str_to_double (string input)
{
    stringstream conv(input);
    double output = 0.0;
    conv >> output;
    return output;
}

