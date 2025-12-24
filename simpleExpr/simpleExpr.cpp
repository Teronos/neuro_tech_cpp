#include "simpleExpr.h"

#include <random>
#include <set>

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

    int problem10() {
        size_t size;
        cin >> size;
        vector<int> collect(size);

        for (auto& elem : collect)
            cin >> elem;
        return ranges::max(collect);
    }

    int problem10Other() {
        size_t numbers;
        cin >> numbers;

        auto max = numeric_limits<int>::min();
        int number = max;
        for (auto i = 0; i < numbers; i++) {
            cin >> number;
            if (number > max)
                max = number;
        }
        return max;
    }

    int problem11() {
        size_t numbers;
        cin >> numbers;

        auto countPositive{ 0 }, current{ 0 };
        for (auto i = 0; i < numbers; i++) {
            cin >> current;
            if (current > 0)
                countPositive++;
        }
        return countPositive;
    }

    int problem11Other() {
        size_t size;
        cin >> size;
        vector<int> collect(size);

        for (auto& elem : collect)
            cin >> elem;

        auto positive = views::filter(collect, [](auto num) { return num > 0; });
        return std::transform_reduce(
            positive.begin(), positive.end(), 0, plus{}, [](auto) { return 1; }
        );
    }

    int problem12() {
        string str;
        constexpr auto sep = ' ';
        getline(cin, str);

        auto beginNumber = 0, sum = 0;
        for (auto index = 0; index < str.length() + 1; index++) {
            if (str[index] != sep && index != str.length())
                continue;

            auto number = stoi(str.substr(beginNumber, index));
            auto absNumber = abs(number);
            if (absNumber < 100 && absNumber > 9 && number % 8 == 0)
                sum += number;

            beginNumber = index + 1;
        }

        return sum;
    }

    int problem13() {
        int number;
        vector<int> numbers;
        for (;;) {
            cin >> number;
            if (!number)
                break;
            numbers.push_back(number);
        }
        return ranges::count(numbers, *ranges::max_element(numbers));
    }

    int problem13Other() {
        auto number{ 0 }, maxNumber{ numeric_limits<int>::min() }, count{ 0 };
        for (;;) {
            cin >> number;
            if (!number) {
                break;
            }
            else if (number > maxNumber) {
                maxNumber = number;
                count = 1;
            }
            else if (number == maxNumber) {
                count++;
            }
        }
        return count;
    }

    string problem14() {
        string str;
        constexpr auto sep = ' ';
        getline(cin, str);

        set<int> numbersFromFirst;
        function<void(int)> action = [&](auto number)
            {
                numbersFromFirst.insert(number);
            };

        string generalNumbers;
        for (auto index = 0; index < str.length(); index++) {
            auto symbol = str[index];

            if (symbol == sep) {
                action = [&](auto number)
                    {
                        if (numbersFromFirst.find(number) != numbersFromFirst.end())
                            generalNumbers += format("{} ", number);
                    };
                continue;
            }

            auto number = symbol - '0';
            action(number);
        }
        return generalNumbers;
    }

    string problem14Another() {
        string str;
        constexpr auto sep = ' ';
        getline(cin, str);

        set<int> numbersFromFirst;
        string generalNumbers;
        auto index{ 0 };
        for (;; index++) {
            auto symbol = str[index];

            if (symbol == sep)
                break;

            auto number = symbol - '0';
            numbersFromFirst.insert(number);
        }

        for (; index < str.length(); index++) {
            auto symbol = str[index];
            auto number = symbol - '0';

            if (numbersFromFirst.find(number) != numbersFromFirst.end())
                generalNumbers += format("{} ", number);
        }

        return generalNumbers;
    }
}


namespace Labs
{
    // tbd: refactor
    double genRandomNumber(double min, double max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    // tbd: refactor
    int genRandomInt(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    ComplexNumber::ComplexNumber(const std::vector<double>& v) :
        re_(v[0]), im_(v[1]) {}

    double ComplexNumber::re() const {
        return re_;
    }

    double ComplexNumber::im() const {
        return im_;
    }

    double ComplexNumber::abs() const {
        return sqrt(im_ * im_ + re_ * re_);
    }

    ComplexNumber ComplexNumber::operator*(const ComplexNumber& other) const {
        return {
            re_ * other.re() - im_ * other.im(),
            re_ * other.im() + other.re() * im_
        };
    }

    ComplexNumber ComplexNumber::operator*(double scalar) const {
        return { re_ * scalar, im_ * scalar };
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
        // auto result = ComplexNumber(0, 0);
        // auto index{0};
        // for (auto& coef: *this) {
        //      result = result + x.pow(index) * coef;
        //      index++;
        // }
        // return result;
        return ranges::fold_left(views::enumerate(BasePolynom(*this)),
            ComplexNumber(0, 0), [&](auto acc, auto couple) {
                auto& [index, coef] = couple;
                acc = acc + x.pow(index) * coef;
                return acc;
            }
        );
    }

    Carrier::Carrier() {
        gens_ = { genRandomNumber(-10, 10), genRandomNumber(-10, 10) };
    }

    bool Carrier::operator<(const Carrier& other) const {
        return target_ < other.target();
    }

    double Carrier::newGen(double gen1, double gen2) {
        auto gen = (gen1 + gen2) / 2;
        auto percent = abs(gen / 20);
        return gen + genRandomNumber(-percent, percent);
    }

    // TBD: refactor newChild and mergeForNew
    Carrier Carrier::newChild(const Carrier& otherParent) const {
        vector<double> newGens(gens_.size());
        auto& otherGens = otherParent.gens();
        for (auto i = 0; i < gens_.size(); i++)
            newGens[i] = newGen(gens_[i], otherGens[i]);

        return { newGens };
    }

    void Carrier::mergeForNew(const Carrier& otherParent) {
        auto& otherGens = otherParent.gens();
        for (auto i = 0; i < gens_.size(); i++)
            gens_[i] = newGen(gens_[i], otherGens[i]);
    }

    const vector<double>& Carrier::gens() const {
        return gens_;
    }

    optional<double> Carrier::target() const {
        return target_;
    }
    void Carrier::setTarget(double target) {
        target_ = target;
    }


    Population::Population(const size_t& size, const unsigned numberRandomCarriers) :
        size_(size), numberRandomCarriers_(numberRandomCarriers) {
        contain_.resize(size);
        for (auto i = 0; i < size; i++)
            contain_[i] = {};
    }

    void Population::evo(const FitnessFunction& fitFunc, const unsigned numberEpoch) {
        for (auto i = 0; i < numberEpoch; i++) {
            calcFit(fitFunc);
            crossingover();
        }
        calcFit(fitFunc);
    }

    void Population::calcFit(const FitnessFunction& fitFunc) {
        for (auto& carrier : contain_)
            carrier.setTarget(fitFunc(carrier));

        sort(contain_.begin(), contain_.end());
    }

    const Carrier& Population::bestCarrier() const {
        return contain_.front();
    }

    void Population::crossingover() {
        auto& bestParent = bestCarrier();
        auto indexLastParent = size_ - numberRandomCarriers_;

        for (auto index = 1; index < indexLastParent; index++)
            contain_[index].mergeForNew(bestParent);
            //contain_[index] = bestParent.newChild(contain_[index]);

        for (auto index = indexLastParent; index < size_; index++)
            contain_[index] = {};
    }
    
    StrategyDirection::StrategyDirection() : state(Up) {
        auto value = vector<double>(4);
        contain[Up] = value;
        contain[Left] = value;
        contain[Down] = value;
        contain[Right] = value;
    }

    StateDirection StrategyDirection::random() {
        switch (genRandomInt(0, 3)) {
        case 0:
            return Up;
        case 1:
            return Left;
        case 2:
            return Down;
        case 3:
            return Right;
        }
    }

    ComplexNumber StrategyDirection::toComplex(StateDirection dir) {
        switch (dir) {
        case Up:
            return { 0, 1 };
        case Left:
            return { -1, 0 };
        case Down:
            return { 0, -1 };
        case Right:
            return { 1, 0 };
        }
    }


    // tbd: refactor
    void StrategyDirection::update(StateDirection action, double reward) {
        constexpr auto alpha = 0.8;
        constexpr auto gamma = 0.99;

        auto findBestWish = [&] ()
            {
                return ranges::max(contain[state]);
            };

        auto toInt = [](auto action)
            {
                return static_cast<unsigned>(action);
            };

        auto& cell = contain[state][toInt(action)];
        cell = (1 - alpha) * cell + alpha * (reward + gamma * findBestWish());
        state = action;
    }

    //tbd: refactor
    void StrategyStep::update(StateStep action, double reward) {
        constexpr auto alpha = 0.8;
        constexpr auto gamma = 0.99;

        auto findBestWish = [&]()
            {
                return ranges::max(contain[state]);
            };

        auto toInt = [](auto action)
            {
                return static_cast<unsigned>(action);
            };

        auto& cell = contain[state][toInt(action)];
        cell = (1 - alpha) * cell + alpha * (reward + gamma * findBestWish());
        state = action;
    }

    StrategyStep::StrategyStep() : state(Normal) {
        auto value = vector<double>(3);
        contain[Normal] = value;
        contain[Increase] = value;
        contain[Decrease] = value;
    }

    StateStep StrategyStep::random() {
        switch (genRandomInt(0, 2)) {
        case 0:
            return Normal;
        case 1:
            return Increase;
        case 2:
            return Decrease;
        }
    }

    Environment::Environment(function<double(const ComplexNumber&)> c)
        : closure_(c) {}

    double Environment::reward(const ComplexNumber& currentPos,
        const ComplexNumber& newPos) const {

        auto currentVal = closure_(currentPos);
        auto newVal = closure_(newPos);

        if (newVal < 0.6)
            positionsNearRoot_.push_back(newPos);

        if (newVal < currentVal) {
            if (newVal < 10)
                return 10;
            else if (newVal < 100)
                return 5;
            else 
                return -1; 
        }
        else {
            return -10;
        }
    }


    void Agent::evo(const Environment& env) {
        // TO DO:
        // *) Можно придумать каие-либо дополнительыне условия останова или что-то другое

        constexpr auto epsilon = 0.1;
        for (auto iter = 0; iter < maxIter_; iter++) {

            StateDirection dir{};
            StateStep modif{};

            if (genRandomNumber(0, 1) < epsilon) {
                //случайно прринимаем решение
                dir = StrategyDirection::random();
                modif = StrategyStep::random();
            }
            else {
            // жадным способом, возможно стоит рефакторить на ranges
                
                auto findMaxPosition = [](auto collect)
                    {
                        auto maxElem = collect.front();
                        auto maxIndex = 0;
                        for (auto i = 1; i < collect.size(); i++) {
                            auto elem = collect[i];
                            if (elem > maxElem) {
                                maxElem = elem;
                                maxIndex = i;
                            }
                        }
                        return maxIndex;
                    };

                dir = static_cast<StateDirection>(findMaxPosition(stDirect_.contain[stDirect_.state]));
                modif = static_cast<StateStep>(findMaxPosition(stStep_.contain[stStep_.state]));
            }

            // tbd: refactor
            auto toDouble = [](StateStep mod)
                {
                    switch (mod) {
                    case Normal:
                        return 1.0;
                    case Increase:
                        return 2.0;
                    case Decrease:
                        return 0.5;
                    }
                };

            step_ *= toDouble(modif);

            auto newPosition = position_ + StrategyDirection::toComplex(dir) * step_;
            auto rew = env.reward(position_, newPosition);
            position_ = newPosition;

            stDirect_.update(dir, rew);
            stStep_.update(modif, rew);

            // ниже блок хитростей, стоит подумать может как-то переделать
            if (step_ < 1e-8)
                step_ = 1;
        }
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
            auto poly = Polynom({ {0, 10}, {0, 1} });
            assert(poly.at({ 0, 0 }) == ComplexNumber(0, 10));
            assert(poly.at({ 1, 0 }) == ComplexNumber(0, 11));

            auto poly2 = Labs::Polynom({ {24, 0}, {-50, 0}, {35, 0}, {-10, 0}, {1, 0} });
            constexpr auto epsilonZero = 1e-6;
            assert(poly2.at({ 1, 0 }).abs() < epsilonZero);
            assert(poly2.at({ 2, 0 }).abs() < epsilonZero);
            assert(poly2.at({ 3, 0 }).abs() < epsilonZero);
            assert(poly2.at({ 4, 0 }).abs() < epsilonZero);
        }

        void genAlg() {
            auto poly = Labs::Polynom({ {24, 0}, {-50, 0}, {35, 0}, {-10, 0}, {1, 0} });

            auto fitnessFunc = [&poly](const Labs::Carrier& c)
                {
                    return poly.at(Labs::ComplexNumber(c.gens())).abs();
                };

            auto population = Labs::Population(10, 4);
            population.evo(fitnessFunc, 100);
            assert(population.bestCarrier().target().value() < 1);
        }
    }
}


int main() {
    Labs::Tests::complexNumber();
    Labs::Tests::polynom();
    Labs::Tests::genAlg();

    // roots: 1, 2, 3, 4
    auto poly = Labs::Polynom({ {24, 0}, {-50, 0}, {35, 0}, {-10, 0}, {1, 0} });

    auto closure = [&poly](const Labs::ComplexNumber& c)
        {
            return poly.at(c).abs();
        };

    auto agent = Labs::Agent();
    auto env = Labs::Environment(closure);
    agent.evo(env);

    system("pause");
}