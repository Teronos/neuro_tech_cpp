#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <ranges>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <sstream>


namespace problems
{
    int problem1();
    int problem1AlexR();
    int problem1Diamond();

    std::pair<int, int> problem2();

    int problem3();

    double problem4();

    unsigned problem5();
    unsigned problem5Another();

    int problem6();

    int problem7();

    std::string problem8();

    std::string problem9();

    int problem10();
    int problem10Other();

    int problem11();
    int problem11Other();

    int problem12();

    int problem13();
    int problem13Other();

    std::string problem14();
    std::string problem14Another();
}

namespace Labs
{
    using namespace std;

    double genRandomNumber(double min, double max);

    class ComplexNumber {
    public:
        ComplexNumber(const vector<double>& v);
        ComplexNumber(double re = 0, double im = 0) : re_(re), im_(im) {}

        double re() const;
        double im() const;
        double abs() const;
        ComplexNumber pow(unsigned n) const;
        
        ComplexNumber operator*(const ComplexNumber& other) const;
        ComplexNumber operator*(double scalar) const;

        ComplexNumber operator+(const ComplexNumber& other) const;
        bool operator==(const ComplexNumber& other) const;

    private:
        double re_{};
        double im_{};
    };

    using BasePolynom = vector<ComplexNumber>;
    class Polynom : BasePolynom
    {
    public:
        
        Polynom(BasePolynom content) {
            *this = *static_cast<Polynom*>(&content);
        };

        ComplexNumber at(const ComplexNumber& x) const;
    };


    class Carrier {
    public:
        Carrier();
        Carrier(const vector<double>& gens) : gens_(gens) {}

        bool operator<(const Carrier& other) const ;

        Carrier newChild(const Carrier& otherParent) const;
        void mergeForNew(const Carrier& otherParent);
        const vector<double>& gens() const;

        optional<double> target() const;
        void setTarget(double);

    private:
        static double newGen(double gen1, double gen2);

    private:
        vector<double> gens_;
        optional<double> target_;
    };

    class Population {
    public:
        using FitnessFunction = function<double(const Carrier&)>;

        Population(const size_t& size, const unsigned numberRandomCarriers);

        void evo(const FitnessFunction& fitFunc, const unsigned numberEpoch);
        const Carrier& bestCarrier() const;

    private:
        void calcFit(const FitnessFunction& fitFunction);
        void crossingover();

    private:
        size_t size_;
        unsigned numberRandomCarriers_;
        vector<Carrier> contain_;
    };

    enum StateDirection {
        Up,
        Left,
        Down,
        Right
    };

    enum StateStep {
        Normal,
        Increase,
        Decrease
    };


    // tbd: refactor with templates + concepts
    struct StrategyDirection {
        StrategyDirection();

        void update(StateDirection action, double reward);

        static StateDirection random();
        static ComplexNumber toComplex(StateDirection dir);

        unordered_map<StateDirection, vector<double>> contain;
        StateDirection state;
    };

    // tbd: refactor with templates + concepts
    struct StrategyStep {
        StrategyStep();

        void update(StateStep action, double reward);

        static StateStep random();

        unordered_map<StateStep, vector<double>> contain;
        StateStep state;
    };

    class Environment {
    public:
        Environment(function<double(const ComplexNumber&)> c);

        double reward(const ComplexNumber& currentPos,
            const ComplexNumber& newPos) const;

    private:
        mutable vector<ComplexNumber> positionsNearRoot_;
        function<double(const ComplexNumber&)> closure_;
    };

    class Agent {
    public:
        Agent() {};

        void evo(const Environment& env);

    private:
        double step_{1};
        unsigned maxIter_{1000};
        ComplexNumber position_{};
        StrategyDirection stDirect_{};
        StrategyStep stStep_{};
    };

    namespace Tests
    {
        void complexNumber();
        void polynom();
        void genAlg();
    }
}

