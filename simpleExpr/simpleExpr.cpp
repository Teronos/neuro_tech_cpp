#include "simpleExpr.h"
#include "utils.h"

#include "geneticAlgorithm.h"

#include <random>
#include <set>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;


namespace Labs
{
    // tbd: refactor

    using namespace utils;
   
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

   // auto agent = Labs::Agent();
   // auto env = Labs::Environment(closure);
    //agent.evo(env);

    ifstream f("example.json");
    json data = json::parse(f);

    double age;
    if (auto found = data.find("age"); found != data.end())
        age = *found;

    string name;
    if (auto found = data.find("name"); found != data.end())
        name = *found;

    unordered_map<string, int> dict;
    if (auto found = data.find("dict"); found != data.end())
        dict = *found;

    json metaInfo;
    if (auto found = data.find("meta_info"); found != data.end())
        metaInfo = *found;

    json workLocations;
    if (auto found = metaInfo.find("work_locations"); found != metaInfo.end())
        workLocations = *found;


    auto loc = workLocations.dump();
    vector<unordered_map<string, string>> locations = workLocations;



    system("pause");
}