#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <ranges>
#include <unordered_map>
#include <algorithm>

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
}

namespace Labs
{
    class ComplexNumber {
    public:
        ComplexNumber(double re, double im) : re_(re), im_(im) {}

        double re() const;
        double im() const;
        double abs() const;
        ComplexNumber pow(unsigned n) const;
        
        ComplexNumber operator*(const ComplexNumber& other) const;
        ComplexNumber operator+(const ComplexNumber& other) const;
        bool operator==(const ComplexNumber& other) const;

    private:
        double re_{};
        double im_{};
    };

    using BasePolynom = std::vector<ComplexNumber>;
    class Polynom : BasePolynom
    {
    public:
        
        Polynom(BasePolynom content) {
            *this = *static_cast<Polynom*>(&content);
        };

        ComplexNumber at(const ComplexNumber& x) const;
    };

    namespace Tests
    {
        void complexNumber();
        void polynom();
    }
}

