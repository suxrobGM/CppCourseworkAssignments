/**
 * Task2
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 **/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <typeinfo>
using namespace std;

enum Action 
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    HELP,
    QUIT
};

// Template function to validate user input
template <typename T>
T Validate(string text)
{
	T value;
	while (true)
	{
		cout << "\n" << text;
		cin >> value;

		if (!cin.fail())
			if (typeid(T) == typeid(int) || typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(char))
			{
				if (cin.peek() == '\n')
					break;
			}
			else
				break;

		cout << "Error - Invalid value" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	return value;
}


class CalculatorProgram 
{
public:

    // Driver code
    void run()
    {
        string choosedAction;

        cout << "-----------------------------------------------------------------------" << endl;
        cout << "\t\tWelcome to this weak calculator! :D" << endl;
        cout << "-----------------------------------------------------------------------\n" << endl;

        while (true) 
        {
            cout << "What action do you wish to perform?" << endl;
            showChoice();
            cin >> choosedAction;

            if (choosedAction == "help") 
            {
                showChoice();               
            }
            else if (choosedAction == "+")
            {
                calculate(ADD);
            }
            else if (choosedAction == "-")
            {
                calculate(SUBTRACT);
            }
            else if (choosedAction == "*")
            {
                calculate(MULTIPLY);
            }
            else if (choosedAction == "/")
            {
                calculate(DIVIDE);
            }
            else if (choosedAction == "quit") 
            {
                quitProgram();
                return;
            }
            else 
            {
                displayInputError();               
            }
        }
    }

    void calculate(Action action) 
    {
        double num1 = 0;
        double num2 = 0;

        switch (action) 
        {
            case ADD: 
            {
            INPUT_ADD:
                
                num1 = Validate<double>("Please enter 1st number: ");
                num2 = Validate<double>("Please enter 2nd number: ");
                //cout << "Please enter 2 numbers:" << endl;
                //cin >> num1 >> num2;

                if (cin.fail())
                {
                    clearInput();
                    displayInputError();
                    goto INPUT_ADD;
                }

                add(num1, num2);
                break;
            }
            case SUBTRACT: 
            {
            INPUT_SUBTRACT:
                num1 = Validate<double>("Please enter 1st number: ");
                num2 = Validate<double>("Please enter 2nd number: ");
                //cout << "Please enter 2 numbers:" << endl;
                //cin >> num1 >> num2;

                if (cin.fail())
                {
                    clearInput();
                    displayInputError();
                    goto INPUT_SUBTRACT;
                }

                subtract(num1, num2);
                break;
            }   
            case MULTIPLY: 
            {
            INPUT_MULTIPLY:
                num1 = Validate<double>("Please enter 1st number: ");
                num2 = Validate<double>("Please enter 2nd number: ");
                //cout << "Please enter 2 numbers:" << endl;
                //cin >> num1 >> num2;

                if (cin.fail())
                {
                    clearInput();
                    displayInputError();
                    goto INPUT_MULTIPLY;
                }

                multiply(num1, num2);
                break;
            }
            case DIVIDE: 
            {
            INPUT_DIVIDE:
                num1 = Validate<double>("Please enter 1st numbers: ");
                num2 = Validate<double>("Please enter 2nd number: ");
                //cout << "Please enter 2 numbers:" << endl;
                //cin >> num1 >> num2;

                if (cin.fail())
                {
                    clearInput();
                    displayInputError();
                    goto INPUT_DIVIDE;
                }

                if (num2 == 0)
                {
                    clearInput();
                    displayInputError("Divider is zero, please enter non-zero divider.");
                    goto INPUT_DIVIDE;
                }

                divide(num1, num2);
                break;
            }
            case HELP: 
            {
                showChoice();
                break;
            }
            case QUIT: 
            {
                quitProgram();
                break;
            }               
        }      
    }

    void add(double num1, double num2) 
    {
        cout << "\n-------------------------------------------------------" << endl;
        printf("%.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
        cout << "-------------------------------------------------------\n" << endl;
    }

    void subtract(double num1, double num2) 
    {
        cout << "\n-------------------------------------------------------" << endl;
        printf("%.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
        cout << "-------------------------------------------------------\n" << endl;
    }

    void multiply(double num1, double num2) 
    {
        cout << "\n-------------------------------------------------------" << endl;
        printf("%.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
        cout << "-------------------------------------------------------\n" << endl;
    }

    void divide(double num1, double num2) 
    {
        cout << "\n-------------------------------------------------------" << endl;
        printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
        cout << "-------------------------------------------------------\n" << endl;
    }

    // Displays user choices
    void showChoice() 
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "Here a list of available actions:" << endl;
        cout << "\"help\" - displays all available actions" << endl;
        cout << "  \"+\"  - Performs addition between 2 numbers" << endl;
        cout << "  \"-\"  - Performs subtraction between 2 numbers" << endl;
        cout << "  \"*\"  - Performs multiplication between 2 numbers" << endl;
        cout << "  \"/\"  - Performs division between 2 numbers" << endl;
        cout << "\"quit\" - Quits the program" << endl;
        cout << "-------------------------------------------------------\n" << endl;
    }

    // Function to exit from program
    void quitProgram() 
    {
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
    CalculatorProgram program;
    program.run();
    return 0;
}