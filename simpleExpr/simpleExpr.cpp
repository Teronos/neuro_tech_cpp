#include <iostream>
#include <string>
#include <ranges>

using namespace std;


namespace
{
    void argregatorPersolalInfo(int age, double weight) {

        double height;
        wstring name{ L"Vladislav" }, description;

        wcout << "Name: " << name << "\n";
        wcout << "Age: " << age << " Weight: "
            << weight << endl;

        {
            wcout << "Enter height:" << endl;
            cin >> height;
            wcin >> description;
        }
    }

    void argregatorPersolalInfo()
    {
        argregatorPersolalInfo(27, 77.3);
    }
}

namespace problems
{
    // TO DO:
    /*
    * Дано трехзначное натуральное число N.
    * Нужно найти сумму цифр числа N
    */
    int problem1() {
        int N;
        std::cin >> N;
        return N % 10 + (N / 10) % 10 + N / 100;
    }

    int problem1AlexR() {
        int N;
        std::cin >> N;

        auto acc{ 0 };
        while (N) {
            //acc = acc + N % 10;
            acc += N % 10;
            N /= 10;
        }

        return acc;
    }

    int problem1Diamond() {
        std::string number_str;
        std::cin >> number_str;

        auto it = number_str.begin();

        auto acc{ 0 };
        //for (int index = 0; index < number_str.length(); index++)
        //    acc += number_str[index] - '0';

        for (auto symbol : number_str)
            acc += symbol - '0';
        return acc;
    }

    /*
        Дано натуральное шести значное число n,
        найти сумму его четных и нечетных элементов
        и вывести их на экран подряд.
        
        Пример: 531277
        Результат: 1312
    */

    pair<int, int> problem2() {
        string n;
        cin >> n;
        auto accEven = 0, accNotEven = 0;
        for (auto [index, symbol] : std::views::enumerate(n))
        {
            auto number = symbol - '0';
            if (index % 2 == 0)
                accEven += number;
            else
                accNotEven += number;
        }
        return { accEven, accNotEven };
    }

    /*
    На вход подается натуральное число k.
    На вход подается натуральное число n.
    И затем подается n натуральных чисел.
    Нужно найти количество числе равных числу k.

    Пример:
    17
    4
    15
    16
    17
    18

    Результат: 1

    */

    int problem3()
    {
        int k, n;
        cin >> k >> n;
        auto acc{ 0 };
        for (auto i = 0; i < n; i++)
        //while (n--)
        {
            int number;
            cin >> number;

            //acc += number == k;
            if (number == k)
               acc++;
        }
        return acc;
    }

    /*
    На вход подается натуральное число n.
    И затем подается n натуральных чисел.
    Нужно найти среднее арифметическое среди
    всех чисел кратных 3, если таких чисел нет, то вывести -1

    Пример:
    4
    15
    16
    17
    18

    Результат: 16.5
    */

    double problem4()
    {
        int n;
        cin >> n;
        auto count{ 0.0 }, acc{ 0.0 };
        for (auto i = 0; i < n; i++)
        {
            int number;
            cin >> number;
            if (!(number % 3))
            {
                count++;
                acc += number;
            }
        }

        if (count)
            return acc / count;
        return -1;
    }
}


int main() {
    auto result = problems::problem4();
    //cout << result.first << result.second << endl;
    cout << result;

    system("pause");
}