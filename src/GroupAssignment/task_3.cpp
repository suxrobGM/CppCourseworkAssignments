/**
 * Task3
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 **/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <limits>
using namespace std;

class PetrolAllowanceProgram 
{
private:
    bool _isFirstRun;
    string _staffName;

public:
    void run() {
        string choosedAction;
        _isFirstRun = true;
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "\t\tWelcome to the program! :)" << endl;
        cout << "-----------------------------------------------------------------------" << endl;

        while (true) 
        {
            cout << "\nWhat action do you wish to perform?" << endl;
            cout << "\nType \"run\" to begin calculation or \"quit\" to exit program" << endl;
            cin >> choosedAction;

            cout << endl;
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
        float distance = 0.0f;

        if (_isFirstRun)
        {
            clearInput();

        INPUT_NAME:
            cout << "Enter staff name:" << endl;
            getline(cin, _staffName); // TODO: need to add staff name validation

            bool isValidName = validateName(_staffName);

            if (!isValidName)
            {
                displayInputError("Staff name is invalid, please enter right name.");
                goto INPUT_NAME;
            }

            _isFirstRun = false;
        }
        
    INPUT_DISTANCE:
        cout << "Enter distance travelled in kilometers" << endl;
        cin >> distance;

        if (cin.fail())
        {
            clearInput();
            displayInputError("Invalid value, this is not a number.");
            goto INPUT_DISTANCE;
        }
        
        cout << "\n-------------------------------------------------------\n" << endl;
        cout << "Final receipt:\n" << endl;
        cout << "Name: " << _staffName << endl;
        printf("Distance travelled: %.1fkm\n\n", distance);

        float totalPrice = 0.0f;
        float currentDistancePrice = 0.0f;
        float restDistance = distance;
        bool distanceFinished = false;

        // First distance
        if (restDistance >= 10.0f)
        {
            currentDistancePrice = 10.0f * 1.80f;
            totalPrice += currentDistancePrice;
            restDistance -= 10.0f;
            printf("First 10 km: 10.0km * RM 1.80 = RM %.2f\n", currentDistancePrice);
        }
        else if (restDistance > 0 && restDistance < 10.0f)
        {
            currentDistancePrice = restDistance * 1.80f;
            totalPrice += currentDistancePrice;
            printf("First 10 km: %0.1fkm * RM 1.80 = RM %.2f\n", restDistance, currentDistancePrice);
            distanceFinished = true;
        }
        
        // Second distance
        if (restDistance >= 50.0f)
        {
            currentDistancePrice = 50.0f * 1.50f;
            totalPrice += currentDistancePrice;
            restDistance -= 50.0f;
            printf("Next 50 km: 50.0km * RM 1.50 = RM %.2f\n", currentDistancePrice);
        }
        else if (!distanceFinished && restDistance > 10 && restDistance < 50)
        {
            currentDistancePrice = restDistance * 1.50f;
            totalPrice += currentDistancePrice;
            printf("Next 50 km: %0.1fkm * RM 1.50 = RM %.2f\n", restDistance, currentDistancePrice);
            distanceFinished = true;
        }

        // Third distance
        if (restDistance >= 50.0f)
        {
            currentDistancePrice = 50.0f * 1.30f;
            totalPrice += currentDistancePrice;
            restDistance -= 50.0f;
            printf("Next 50 km: 50.0km * RM 1.30 = RM %.2f\n", currentDistancePrice);
        }
        else if (!distanceFinished && restDistance > 0 && restDistance < 50)
        {
            currentDistancePrice = restDistance * 1.30f;
            totalPrice += currentDistancePrice;
            printf("Next 50 km: %0.1fkm * RM 1.30 = RM %.2f\n", restDistance, currentDistancePrice);
            distanceFinished = true;
        }

        // Fourth distance
        if (!distanceFinished && restDistance > 0)
        {
            currentDistancePrice = restDistance * 1.00f;
            totalPrice += currentDistancePrice;
            printf("Beyond 110 km: %0.1fkm * RM 1.00 = RM %.2f\n", restDistance, currentDistancePrice);
        }


        if (totalPrice > 150) 
        {
            printf("Allowance: RM %.2f + 5%% = RM %.2f\n", totalPrice, totalPrice * 1.05f);
        } 
        else 
        {
            printf("Allowance: RM %.2f\n", totalPrice);
        }
        
        cout << "\n-------------------------------------------------------\n" << endl;
    }

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
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    void displayInputError(string errorMsg = "Invalid value, please try again")
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "ERROR: " << errorMsg << endl;
        cout << "-------------------------------------------------------\n" << endl;
    }

    // Check that staff name does not contain numbers and other symbols
    bool validateName(string name)
    {
        bool isValid = true;
        int strLength = name.size();

        if (strLength == 0)
            return false;

        if (strLength == 1 && (name[0] == ' ' || name[0] == '\n'))
            return false;

        for (size_t i = 0; i < strLength; i++)
        {
            if (name[i] == ' ')
            {
                continue;
            }
            
            if (!isalpha(name[i]))
            {
                isValid = false;
                break;
            }
        }
        
        return isValid;
    }
};


int main() 
{
    PetrolAllowanceProgram program;
    program.run();

    return 0;  
}