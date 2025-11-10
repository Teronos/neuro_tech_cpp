#include "simpleExpr.h"

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
    using namespace std;
    // TO DO:
    /*
    * Дано трехзначное натуральное число N.
    * Нужно найти сумму цифр числа N
    */
    int problem1() {
        int N;
        cin >> N;
        return N % 10 + (N / 10) % 10 + N / 100;
    }

    int problem1AlexR() {
        int N;
        cin >> N;

        auto acc{ 0 };
        while (N) {
            //acc = acc + N % 10;
            acc += N % 10;
            N /= 10;
        }

        return acc;
    }

    int problem1Diamond() {
        string number_str;
        cin >> number_str;

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
        for (auto [index, symbol] : views::enumerate(n))
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

    unsigned problem5() {
        unsigned number;
        cin >> number;

        unsigned minValue = numeric_limits<unsigned>::max(), count{};

        for (auto i = 0; i < number; i++) {
            unsigned value;
            cin >> value;

            if (value < minValue) {
                minValue = value;
                count = 0;
            }
            else if (value == minValue) {
                count++;
            }
        }
        return count;
    }

    unsigned problem5Another()
    {
        unsigned number;
        cin >> number;

        auto values = ranges::iota_view{ 0u, number } | // 0 1 ... number-1
            views::transform(
                [](auto index) {
                    unsigned value;
                    cin >> value;
                    return value;
                })// a b ... z
            | ranges::to<vector>();

        auto minValue = *ranges::min_element(values);
        return ranges::count(values, minValue);
    }

    int problem6()
    {
        constexpr auto fibNumber = [](auto n)
            {
                constexpr auto helper = [] (auto n, auto current, auto next, auto& impl)
                    {
                        if (n == 0)
                            return current;
                        return impl(n - 1, next, current + next, impl);
                    };

                return helper(n, 0, 1, helper);
            };

        static_assert(fibNumber(7) == 13);

        int value;
        cin >> value;

        for (auto i = 0; i < value; i++)
        {
            auto fibVale = fibNumber(i);
            if (fibVale == value)
                return i;
            else if (fibVale > value)
                break;
        }
        return -1;
    }

    int problem7()
    {
        unsigned a, b;
        cin >> a >> b;

        for (auto number = b - 1; number > a; number--) if (!(number % 7))
            return number;
        return -1;
    }

    string problem8()
    {
        unordered_map<string, const char*> mapDna{
            {string("T"), "A"},
            {string("A"), "T"},
            {string("C"), "G"},
            {string("G"), "C"},
        };

        string dna;
        cin >> dna;
        return dna | views::transform(
            [&](auto symbol)
            {
                string s(1, symbol);
                return *mapDna[s];
            }) | ranges::to<string>();
    }

    string problem9()
    {
        unsigned maxNumber;
        cin >> maxNumber;

        constexpr int basic = 2;
        auto result = string();
        for (auto num = 1; num <= maxNumber; num *= basic)
            result += format("{} ", num);
        return result;
    }
}


namespace Labs
{
    double ComplexNumber::re() const {
        return re_;
    }

    double ComplexNumber::im() const {
        return im_;
    }

    double ComplexNumber::abs() const {
        return std::sqrt(im_ * im_ + re_ * re_);
    }

    ComplexNumber ComplexNumber::operator*(const ComplexNumber& other) const {
        return {
            re_ * other.re() - im_ * other.im(),
            re_ * other.im() + other.re() * im_
        };
    }

    ComplexNumber ComplexNumber::pow(unsigned n) const {
        if (n == 0)
            return {1, 0};
        if (n == 1)
            return { re_, im_ };
        return *this * pow(n - 1);
    }

    ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
        return { re_ + other.re(), im_ + other.im() };
    }

    bool ComplexNumber::operator==(const ComplexNumber& other) const {
        return re_ == other.re() && im_ == other.im_;
    }


    ComplexNumber Polynom::at(const ComplexNumber& x) const {
        return ranges::fold_left(views::enumerate(BasePolynom(*this)),
            ComplexNumber(0, 0), [&](auto acc, auto couple) {
                auto& [index, coef] = couple;
                acc = acc + x.pow(index) * coef;
                return acc;
            }
        );
    }

    namespace Tests
    {
        void complexNumber() {
            auto imaginary = ComplexNumber(0, 1);
            auto real = ComplexNumber(2, 0);
            assert(imaginary + real == ComplexNumber(2, 1));
            assert(real.pow(5) == ComplexNumber(32, 0));
        }

        void polynom() {
            auto poly = Polynom({ ComplexNumber(0, 10), ComplexNumber(0, 1) });
            assert(poly.at(ComplexNumber(0, 0)) == ComplexNumber(0, 10));
            assert(poly.at(ComplexNumber(1, 0)) == ComplexNumber(0, 11));
        }
    }
}


int main() {
    Labs::Tests::complexNumber();
    Labs::Tests::polynom();

    system("pause");
}