#include <iostream>
#include <string>

using namespace std;


int main() {
    int age{ 27 };

    int ageAnother;
    ageAnother = 27;

    int zeroInt{};

    double weight{ 76.12 }, height;
    string name{ "Vladislav" }, description;

    cout << "Name: " << name << "\n";
    cout << "Age: " << age << endl;
    {
        cout << "Enter height:" << endl;
        cin >> height;
    }
    
    system("pause");
}