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

// Return name of student
string getName(int stdNum)
{
    string name;
    
    cout << "Enter student " << stdNum + 1 << " name:";
    while (true)
    {
        getline(cin, name);
        cin.ignore();
        for (int i = 0; i < name.size(); i++)
        {
            if ( !isString(name) )
            {
                cout << "Inter Invalid!" << endl;
                cout << "Enter name: ";
            }
            
        } 
    }
    return name;
    
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
        if (input[i] = '.')
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
        if ( !isalpha(input[i]) )
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
