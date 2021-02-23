/**
 * Task1
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 **/
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class CalculateTotalAverageProgram
{
public:

    // Driver function
    void run()
    {
        string choosedAction;

        cout << "-----------------------------------------------------------------------" << endl;
        cout << "\t\tWelcome to the program! :)" << endl;
        cout << "This program will calculate total and average of 5 integer numbers" << endl;
        cout << "-----------------------------------------------------------------------" << endl;

        while (true)
        {
            cout << "\nWhat action do you wish to perform?" << endl;
            cout << "\nType \"run\" to begin calculation or \"quit\" to exit program" << endl;
            cin >> choosedAction;
            clearInput();

            if (choosedAction == "run")
            {
                calculate();
            }
            else if (choosedAction == "quit")
            {
                quitProgram();
                break;
            }
            else
            {
                displayInputError();
            }
        }
    }

    void calculate()
    {
        cout << "Please enter 5 integers" << endl;
        int number = 0;
        int sum = 0;
        float average = 0.0f;
        
        for (int i = 1; i <= 5; i++)
        {
        INPUT_NUMBER:
            cout << i << ". ";
            cin >> number;

            if (cin.fail())
            {
                clearInput();
                displayInputError("Invalid value, this is not an integer.\nPlease try again");
                goto INPUT_NUMBER;
            }

            sum += number;
        }

        average = sum / 5.0f;

        cout << "-------------------------------------------------------" << endl;
        printf("Sum: %d\n", sum);
        printf("Average: %.1f\n", average);
        cout << "-------------------------------------------------------" << endl;
    }

    // Function to exit from program
    void quitProgram() {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "Quitted program!" << endl;
        cout << "-------------------------------------------------------\n" << endl;
        exit(0);
    }

private: 
    void clearInput()
    {
        cin.clear();
        cin.ignore(256,'\n');
    }

    void displayInputError(string errorMsg = "Invalid value, please try again")
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "ERROR: " << errorMsg << endl;
        cout << "-------------------------------------------------------\n" << endl;
    }
};

int main()
{
    CalculateTotalAverageProgram program;
    program.run();

    return 0;
}
