#include "utils.h"

#include <random>
#include <algorithm>
#include <ranges>

namespace utils {

    double genRandomNumber(double min, double max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    // tbd: refactor
    int genRandomInt(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }


    ComplexNumber::ComplexNumber(const std::vector<double>& v) :
        re_(v[0]), im_(v[1]) {
    }

    double ComplexNumber::re() const {
        return re_;
    }

    double ComplexNumber::im() const {
        return im_;
    }

    double ComplexNumber::abs() const {
        return sqrt(im_ * im_ + re_ * re_);
    }

    ComplexNumber ComplexNumber::operator*(const ComplexNumber& other) const {
        return {
            re_ * other.re() - im_ * other.im(),
            re_ * other.im() + other.re() * im_
        };
    }

    ComplexNumber ComplexNumber::operator*(double scalar) const {
        return { re_ * scalar, im_ * scalar };
    }

    ComplexNumber ComplexNumber::pow(unsigned n) const {
        if (n == 0)
            return { 1, 0 };
        if (n == 1)
            return { re_, im_ };
        return *this * pow(n - 1);
    }

    ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
        return { re_ + other.re(), im_ + other.im() };
    }

    bool ComplexNumber::operator==(const ComplexNumber& other) const {
        return re_ == other.re() && im_ == other.im_;
    }


    ComplexNumber Polynom::at(const ComplexNumber& x) const {
        // auto result = ComplexNumber(0, 0);
        // auto index{0};
        // for (auto& coef: *this) {
        //      result = result + x.pow(index) * coef;
        //      index++;
        // }
        // return result;
        return ranges::fold_left(views::enumerate(BasePolynom(*this)),
            ComplexNumber(0, 0), [&](auto acc, auto couple) {
                auto& [index, coef] = couple;
                acc = acc + x.pow(index) * coef;
                return acc;
            }
        );
    }
}