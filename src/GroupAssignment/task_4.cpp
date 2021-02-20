/**
 * Task3
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 **/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

class Order 
{
public:
    string name;
    float price;
    float discount;
    int quantity;

    Order() 
    {
        name = "";
    }

    Order(string name, float price, float discount, int quantity) 
    {
        this->name = name;
        this->price = price;
        this->quantity = quantity;
        this->discount = discount;
    }

    float getSubtotal() 
    {
        return price * quantity * ((100.0f - discount) / 100.0f);
    }
};

class RestaurantOrderProgram 
{
private:
    vector<Order*>* _orders;
    Order* _currentOrder;
    string _customerName;
    string _customerIC;
    bool _isContinueOrdering;

public:
    RestaurantOrderProgram() 
    {
        _orders = new vector<Order*>();
        _currentOrder = new Order();
        _customerName = "";
        _customerIC = "";
    }

    void run() 
    {
        string choosedAction;
        
        while (true) 
        {
            if (!_isContinueOrdering) 
            {
                welcomeMessage();
                cout << "What would you like to do?" << endl;
                cout << "Type \"order\" to begin placing order or \"quit\" to exit program" << endl;
                cin >> choosedAction;
            }
            else 
            {
                choosedAction = "order";
            }

            if (choosedAction == "order") 
            {
                showMenu();

                cout << "What would you like to order?" << endl;

            INPUT_MENU_CHOICE:
                cout << "Place order by entering the number next to the book: " << endl;
                int menuChoice;
                cin >> menuChoice;

                if (cin.fail())
                {
                    clearInput();
                    displayInputError();
                    goto INPUT_MENU_CHOICE;
                }

                if (menuChoice < 1 || menuChoice > 7)
                {
                    clearInput();
                    displayInputError("Invaild choice, the value should be between 1 and 7");
                    goto INPUT_MENU_CHOICE;
                }
                

                switch (menuChoice) 
                {
                    case 1: 
                    {
                        _currentOrder = new Order("Story Book", 27.5f, 5.0f, 0);
                        showItem();
                        showSubtotal();

                        if (!_isContinueOrdering) 
                        {
                            showReceipt();
                        }
                        break;
                    }
                    case 2: 
                    {
                        _currentOrder = new Order("Documentary Book", 38.5f, 0, 0);
                        showItem();
                        showSubtotal();

                        if (!_isContinueOrdering) 
                        {
                            showReceipt();
                        }
                        break;
                    }
                    case 3: 
                    {
                        _currentOrder = new Order("Cookery Book", 14.0f, 5.0f, 0);
                        showItem();
                        showSubtotal();

                        if (!_isContinueOrdering) 
                        {
                            showReceipt();
                        }
                        break;
                    }
                    case 4: 
                    {
                        _currentOrder = new Order("Magazine", 18.0f, 10.0f, 0);
                        showItem();
                        showSubtotal();

                        if (!_isContinueOrdering) 
                        {
                            showReceipt();
                        }
                        break;
                    }
                    case 5: 
                    {
                        _currentOrder = new Order("Religious", 22.0f, 0, 0);
                        showItem();
                        showSubtotal();

                        if (!_isContinueOrdering) 
                        {
                            showReceipt();
                        }
                        break;
                    }
                    case 6: 
                    {
                        _currentOrder = new Order("Journals", 15.0f, 5.0f, 0);
                        showItem();
                        showSubtotal();

                        if (!_isContinueOrdering) 
                        {
                            showReceipt();
                        }
                        break;
                    }
                    case 7: 
                    {
                        _isContinueOrdering = false;
                        showReceipt();
                        break;
                    }    
                    default: 
                    {
                        displayInputError();
                        break;
                    }
                }
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

    void showMenu()
    {
        cout << "\n-----------------------------------------------------------------------" << endl;
        cout << "\t\t\t ORDER" << endl;
        cout << "\t\t\t---------\n" << endl;
        
        if (!_isContinueOrdering) 
        {
            inputNameIC();
        }

        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Here is our menu, please have a look: \n" << endl;
        cout << " (1) Story Book - RM 27.50 (5.0% Discount)" << endl;
        cout << " (2) Documentary Book - RM 38.50" << endl;
        cout << " (3) Cookery Book - RM 14.00 (5.0% Discount)" << endl;
        cout << " (4) Magazine - RM 18.00 (10.0% Discount)" << endl;
        cout << " (5) Religious - RM 22.00" << endl;
        cout << " (6) Journals - RM 15.00 (5.0% Discount)" << endl;
        cout << " (7) Checkout" << endl;
        cout << "-----------------------------------------------------------------------" << endl;      
    }

    void showItem() 
    {
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "\t\t\t ITEM:" << endl;
        cout << "\t\t\t---------" << endl;
        cout << "Order: " << _currentOrder->name << endl;
        cout << "Price: " << _currentOrder->price << endl;
        cout << "Current quantity: 0" << endl;
        cout << "-----------------------------------------------------------------------" << endl;

    INPUT_QUANTITY:
        cout << "Please enter the quantity: " << endl;
        cin >> _currentOrder->quantity;

        if (cin.fail())
        {
            clearInput();
            displayInputError();
            goto INPUT_QUANTITY;
        }

        if (_currentOrder->quantity <= 0)
        {
            clearInput();
            displayInputError("Invalid quantity value, it should be positive integer number.");
            goto INPUT_QUANTITY;
        }
        
        _orders->push_back(_currentOrder);
    }

    void showSubtotal() 
    {
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "\t\t\t SUBTOTAL:" << endl;
        cout << "\t\t\t---------" << endl;
        cout << "Order: " << endl;

        float subtotal = 0.0f;
        for (vector<Order*>::iterator it = _orders->begin(); it != _orders->end(); ++it)
        {
            cout << (*it)->name;
            if ((*it)->discount > 0) 
            {
                printf(" : %d * RM %.2f - %.2f%% = RM %.2f\n", (*it)->quantity, (*it)->price, (*it)->discount, (*it)->getSubtotal());    
            } 
            else 
            {
                printf(" : %d * RM %.2f = RM %.2f\n", (*it)->quantity, (*it)->price, (*it)->getSubtotal());
            }
            
            subtotal += (*it)->getSubtotal();
        }
        
        printf("Subtotal: RM %.2f\n", subtotal);
        cout << "-----------------------------------------------------------------------\n" << endl;

        cout << "Would you like to continue ordering?" << endl;
        cout << "Enter \"y\" to add more items or \"n\" to checkout" << endl;
        string userSelect;
        cin >> userSelect;

        if (userSelect == "y") 
        {
            _isContinueOrdering = true;
        } 
        else 
        {
            _isContinueOrdering = false;
        }
    }

    void showReceipt() 
    {
        if (_orders->size() == 0)
        {
            cout << "\nYou did not order any books.\n" << endl;
            return;
        }

        cout << "\n-----------------------------------------------------------------------" << endl;
        cout << "\t\t\t RECEIPT" << endl;
        cout << "\t\t\t---------\n" << endl;
        cout << "Thank you for visiting shop!\n" << endl;
        cout << "Name:\t" << _customerName << endl;
        cout << "IC / Passport: " << _customerIC << endl;
        cout << "\nOrder:\n" << endl;
        
        float subtotal = 0.0f;
        for (vector<Order*>::iterator it = _orders->begin(); it != _orders->end(); ++it) 
        {
            cout << (*it)->name;
            if ((*it)->discount > 0) 
            {
                printf(" : %d * RM %.2f - %.2f%% = RM %.2f\n", (*it)->quantity, (*it)->price, (*it)->discount, (*it)->getSubtotal());    
            } 
            else 
            {
                printf(" : %d * RM %.2f = RM %.2f\n", (*it)->quantity, (*it)->price, (*it)->getSubtotal());
            }

            subtotal += (*it)->getSubtotal();
        }

        float sst = subtotal * 0.02f;
        float grandTotal = subtotal + sst;

        printf("\nSubtotal: RM %.2f\n", subtotal);
        printf("SST: RM %.2f\n", sst);
        printf("Grand Total: RM %.2f\n", grandTotal);
        cout << "\n\t\tPlease enjoy your books!" << endl;
        cout << "-----------------------------------------------------------------------\n" << endl;
    }

    void inputNameIC() 
    {
        printf("Please enter your name: ");
        clearInput();
        getline(cin, _customerName); // TODO: Validate customer name

        printf("Please enter your IC / Passport number: ");
        cin >> _customerIC; // TODO: Validate passport or IC number
    }

    void welcomeMessage() 
    {
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "\t\tWelcome To the Book store!" << endl;
        cout << "-----------------------------------------------------------------------\n" << endl;
    }

    void quitProgram() 
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "Quitted program!" << endl;
        cout << "-------------------------------------------------------\n" << endl;
        exit(0); // Exit from console
    }

    // Destructor to clean objects from heap
    ~RestaurantOrderProgram()
    {
        _orders->clear();
        delete _orders;
        delete _currentOrder;
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
    RestaurantOrderProgram* program = new RestaurantOrderProgram();
    program->run();

    delete program;
    return 0;
}