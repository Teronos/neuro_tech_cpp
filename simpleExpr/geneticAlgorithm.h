#pragma once

#include <vector>
#include <optional>
#include <functional>

namespace Labs {
    using namespace std;

    class Carrier {
    public:
        Carrier();
        Carrier(const vector<double>& gens) : gens_(gens) {}

        bool operator<(const Carrier& other) const;

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
}