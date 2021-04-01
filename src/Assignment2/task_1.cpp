/**
 * Task 1
 * Written by Sukhrob Ilyosbekov
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 * 
 **/
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

class Time 
{
public:
    // Public properties
    int hours;
    int minutes;
    int seconds;
    bool isAm;

    // Default constructor
    Time()
    {
        // Initialize default time: 12:00:00 AM
        this->hours = 12;
        this->minutes = 0;
        this->seconds = 0;
        isAm = true;
    }

    // Copy constructor
    Time(const Time& time)
    {
        this->hours = time.hours;
        this->minutes = time.minutes;
        this->seconds = time.seconds;
        this->isAm = time.isAm;
    }

    // Add seconds
    void add_seconds(int seconds)
    {
        if (seconds <= 0)
            return;

        this->seconds += seconds;

        while (this->seconds > 59)
        {
            this->seconds -= 60;
            this->minutes++;
        }
        
        while (this->minutes > 59)
        {
            this->minutes -= 60;
            this->hours++;
        }
        
        while (this->hours > 12)
        {
            this->hours -= 12;

            if (this->hours == 12)
                this->isAm = !this->isAm;
        }
    }

    // Convert to string represtation
    string to_string()
    {
        stringstream ss;
        string amTag = isAm ? "AM" : "PM";
        ss << this->hours << ":" << get_zero_suffix(this->minutes) << this->minutes << ":"
           << get_zero_suffix(this->seconds) << this->seconds << " " << amTag;
        return ss.str();
    }

private:
    string get_zero_suffix(int timeValue)
    {
        return timeValue >=0 && timeValue <= 9 ? "0" : ""; 
    }
};


// Tester class (driver code)
class Program
{
public:
    void run()
    {
        char continue_action = 'Y';
        while (continue_action == 'Y' || continue_action == 'y')
        {
            int seconds = 0;
            Time t;
            
            cout << "The time is: " << t.to_string() << endl;
            
        INPUT_NUMBER:
            cout << "Enter time increment in seconds: ";
            cin >> seconds;

            if (seconds < 0)
            {
                clear_input();
                display_input_error("Invalid value, should be positive number.\nPlease try again");
                goto INPUT_NUMBER;
            }

            if (cin.fail())
            {
                clear_input();
                display_input_error("Invalid value, this is not an integer.\nPlease try again");
                goto INPUT_NUMBER;
            }

            t.add_seconds(seconds);
            cout << "The new time is: " << t.to_string() << endl;

            cout << "Do you wish to repeat again (Y/N): ";
            cin >> continue_action;
        }
    }

private:
    void clear_input()
    {
        cin.clear();
        cin.ignore(256,'\n');
    }

    void display_input_error(string errorMsg = "Invalid value, please try again")
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "ERROR: " << errorMsg << endl;
        cout << "-------------------------------------------------------\n" << endl;
    }
};

int main()
{
    Program program;
    program.run();

    system("pause");
    return 0;
}