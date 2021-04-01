/**
 * Task 3
 * Written by Sukhrob Ilyosbekov
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 * 
 **/
#include <iostream>
#include <cstdlib>
using namespace std;

// Get bigger value of two numbers uisng > operator
// Datatype T can be any primitive numeric types: short, int, long, float, double, long double, also can be char or bool 
template<typename T>
T maximum(T value1, T value2)
{
    return value1 >= value2 ? value1 : value2;
}

int main()
{
    int int1 = 34, int2 = 45;
    float float1 = 62.694, float2 = 76.545;
    double double1 = 40.1234567, double2 = 98.6546413;

    cout << "Finding bigger integer between " << int1 << " and " << int2 << " is " << maximum(int1, int2) << endl;
    cout << "Finding bigger float between " << float1 << " and " << float2 << " is " << maximum(float1, float2) << endl;
    cout << "Finding bigger double between " << double1 << " and " << double2 << " is " << maximum(double1, double2) << endl;

    cout << "\n\nUsing function templates, datatype for variables used do not have to be set." 
        << "Therefore, the template function will use the datatype of the variable passed into the function of the templates."
        << "For example, if the variables passed into the function template are int datatype, the function will use the int datatype\n" << endl;

    cout << "The drawback of this is that only certain datatypes work. In this case, only datatypes that calculations can be carried out on will work"
        << "Other than that, only one type of datatype can be used at once. If int datatype is used, both arguments passed have to be int." 
        << "This can be solved through class template with two template classes used." << endl;
    system("pause");
    return 0;
}