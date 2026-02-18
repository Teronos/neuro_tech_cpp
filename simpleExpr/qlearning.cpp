#include "qlearning.h"

#include <vector>
#include <algorithm>
#include <ranges>
#include <functional>


namespace Labs {

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

    Environment::Environment(function<double(const ComplexNumber&)>& c)
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
}