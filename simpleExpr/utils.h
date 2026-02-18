#pragma once

#include <vector>

namespace utils {
    using namespace std;

    double genRandomNumber(double min, double max); 
    int genRandomInt(int min, int max);

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

}