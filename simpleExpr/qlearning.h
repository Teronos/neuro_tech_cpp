#pragma once

#include "utils.h"
#include <unordered_map>
#include <functional>

namespace Labs {
    using namespace std;
    using namespace utils;

    //double genRandomNumber(double min, double max);

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
        Environment(function<double(const ComplexNumber&)>& c);

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
        double step_{ 1 };
        unsigned maxIter_{ 1000 };
        ComplexNumber position_{};
        StrategyDirection stDirect_{};
        StrategyStep stStep_{};
    };

}
