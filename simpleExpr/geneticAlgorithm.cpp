#include "geneticAlgorithm.h"
#include "utils.h"

#include <algorithm>

namespace Labs {
    using namespace utils;

    Carrier::Carrier() {
        gens_ = { genRandomNumber(-10, 10), genRandomNumber(-10, 10)};
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

}