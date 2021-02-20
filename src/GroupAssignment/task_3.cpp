/**
 * Task3
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 **/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

class PetrolAllowanceProgram 
{
public:
    
    void run() {
        string choosedAction;

        cout << "-----------------------------------------------------------------------" << endl;
        cout << "\t\tWelcome to the program! :)" << endl;
        cout << "-----------------------------------------------------------------------" << endl;

        while (true) 
        {
            cout << "\nWhat action do you wish to perform?" << endl;
            cout << "\nType \"run\" to begin calculation or \"quit\" to exit program" << endl;
            cin >> choosedAction;

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
        string staffName;
        float distance = 0.0f;

        cout << "Enter staff name:" << endl;
        clearInput();
        getline(cin, staffName); // TODO: need to add staff name validation

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
        cout << "Name: " << staffName << endl;
        printf("Distance travelled: %.1fkm\n\n", distance);

        float totalPrice = 0.0f;
        float restDistance = distance;

        if (restDistance >= 10) 
        {
            totalPrice += 10.0f * 1.80f;
            restDistance -= 10;
            printf("First 10 km: 10.0km * RM 1.80 = RM %.2f\n", 10.0f * 1.80f);
        }
        else if (restDistance > 0 && restDistance < 10) 
        {
            totalPrice += restDistance * 1.80f;
            printf("First 10 km: %.1fkm * RM 1.80 = RM %.2f\n", restDistance, restDistance * 1.80f);
        }

        //float secondDistance = restDistance - 50;
        if (restDistance >= 50) 
        {
            totalPrice += 50.0f * 1.50f;
            restDistance -= 50;
            printf("Next 50 km: 50.0km * RM 1.50 = %.2f\n", 50.0f * 1.50f);
        }
        else if (restDistance > 10 && restDistance < 50) 
        {
            totalPrice += restDistance * 1.50f;
            printf("*Next 50 km: %.1fkm * RM 1.50 = RM %.2f\n", restDistance, restDistance * 1.50f);
        }

        //float thirdDistance = restDistance - 50;
        if (restDistance >= 50) 
        {
            totalPrice += 50.0f * 1.30f;
            restDistance -= 50;
            printf("Next 50 km: 50.0km * RM 1.30 = %.2f\n", 50.0f * 1.30f);
        }
        else if (restDistance > 0 && restDistance < 50) 
        {
            totalPrice += restDistance * 1.30f;
            printf("*Next 50 km: %.1fkm * RM 1.30 = RM %.2f\n", restDistance, restDistance * 1.30f);     
        }

        //float fourthDistance = restDistance - 100;
        if (restDistance > 110) 
        {
            totalPrice += restDistance * 1.00f;
            printf("Beyond 111km: %.1fkm * RM 1.00 = RM %.2f\n", restDistance, restDistance * 1.00f);
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
    PetrolAllowanceProgram program;
    program.run();

    return 0;  
}