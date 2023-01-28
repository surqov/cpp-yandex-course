#include <iostream>
#include <string>
#include <numeric>

using namespace std;

struct Circle {
    double x;
    double y;
    double r;
};

struct Dumbbell {
    Circle circle1;
    Circle circle2;
    string text;
};

struct DumbbellHash {
    size_t operator()(const Dumbbell& dumbbell){
        const Circle& circle1 = dumbbell.circle1;
        const Circle& circle2 = dumbbell.circle2;
        const std::string& s = dumbbell.text;
        return circle1.x * 37 + circle1.y * (37*37) + circle1.r*(37*37*37) +
                circle2.x * 43 + circle2.y * (43*43) + circle2.r*(43*43*43) +
                s.size();
    }
};

int main() {
    DumbbellHash hash;
    Dumbbell dumbbell{{10, 11.5, 2.3}, {3.14, 15, -8}, "abc"s};
    cout << "Dumbbell hash "s << hash(dumbbell);
}