#include "simpleExpr.h"
#include "utils.h"

#include "geneticAlgorithm.h"
#include "qlearning.h"

#include <iostream>
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

            auto poly2 = Polynom({ {24, 0}, {-50, 0}, {35, 0}, {-10, 0}, {1, 0} });
            constexpr auto epsilonZero = 1e-6;
            assert(poly2.at({ 1, 0 }).abs() < epsilonZero);
            assert(poly2.at({ 2, 0 }).abs() < epsilonZero);
            assert(poly2.at({ 3, 0 }).abs() < epsilonZero);
            assert(poly2.at({ 4, 0 }).abs() < epsilonZero);
        }

        void genAlg() {
            auto poly = Polynom({ {24, 0}, {-50, 0}, {35, 0}, {-10, 0}, {1, 0} });

            auto fitnessFunc = [&poly](const Carrier& c)
                {
                    return poly.at(ComplexNumber(c.gens())).abs();
                };

            auto population = Population(10, 4);
            population.evo(fitnessFunc, 100);
            assert(population.bestCarrier().target().value() < 1);
        }

        void qLearning() {
            // tbd: дописать тест
           
            auto poly = Polynom({ {24, 0}, {-50, 0}, {35, 0}, {-10, 0}, {1, 0} });

            auto closure = [&poly] (auto& c)
                {
                    return poly.at(c).abs();
                };

            auto agent = Agent();
            auto env = Environment(closure);
            agent.evo(env);
        }
    }
}


int main() {
    Labs::Tests::complexNumber();
    Labs::Tests::polynom();
    Labs::Tests::genAlg();

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

    json output, functionGraph;
    output["type"] = "plot_points";
    functionGraph["x_points"] = vector<double>({ 0, 1, 2, 3, 4, 5 });
    functionGraph["y_points"] = vector<double>({ 0, 1, 0, 2, 0, -4 });
    output["values"] = functionGraph;
    
    cout << output.dump();
  
    //system("pause");
}