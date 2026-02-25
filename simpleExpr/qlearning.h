#pragma once

#include "utils.h"
#include <unordered_map>
#include <functional>

namespace Labs {
    using namespace std;
    using namespace utils;

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
        using Target = function<double(const ComplexNumber&)>;
        Environment(const Target& c);

        double reward(const ComplexNumber& currentPos,
            const ComplexNumber& newPos) const;

    private:
        mutable vector<ComplexNumber> positionsNearRoot_;
        Target closure_;
    };

    class Agent {
    public:
        Agent() {};

        void evo(const Environment& env);

    private:
        double step_{ 1 };
        size_t maxIter_{ 1000 };
        ComplexNumber position_{};
        StrategyDirection stDirect_{};
        StrategyStep stStep_{};
    };

}
