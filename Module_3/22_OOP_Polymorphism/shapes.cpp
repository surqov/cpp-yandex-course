// Макрос _USE_MATH_DEFINES необходим, чтобы при подключении <cmath> была объявлена константа M_PI
#define _USE_MATH_DEFINES
// Макрос _USE_MATH_DEFINES следует объявить ДО подключения других заголовочных файлов,
// которые могут подключить <cmath> неявно
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

enum class Color { RED, GREEN, BLUE };

const double PI = M_PI; 

ostream& operator<<(ostream& out, Color color) {
    switch (color) {
        case Color::RED:
            out << "red"s;
            break;
        case Color::GREEN:
            out << "green"s;
            break;
        case Color::BLUE:
            out << "blue"s;
            break;
    }
    return out;
}

class Shape {
public:
    Shape(const Color& color) 
    : _color(color){
    }

    Color GetColor() const {
        return _color;
    }

    void SetColor(const Color& color) {
        _color = color;
    }

    virtual double GetArea() const {
        return 0.0;
    }

    virtual std::string GetType() const {
        return "Shape"s;
    }

private:
    Color _color;
};

class Rectangle : public Shape {
public:
    Rectangle(const int height, const int width, const Color& color)
    : Shape(color)
    , _height(height)
    , _width(width) {
    }

    void SetSize(const int width, const int height) {
        _height = height;
        _width = width;
    }

    double GetArea() const override {
        return _height * _width;
    }

    double GetWidth() const {
        return _width;
    }

    double GetHeight() const {
        return _height;
    }

    std::string GetType() const override {
        return "Rectangle"s;
    }

private:
    int _height = 0.0;
    int _width = 0.0;

};

class Circle : public Shape {
public:
    Circle(const double radius, const Color& color) 
    : Shape(color)
    , _radius(radius) {
    }

    double GetRadius() const {
        return _radius;
    }

    void SetRadius(const double radius) {
        _radius = radius;
    }

    double GetArea() const override {
        return PI * _radius * _radius;
    }

    std::string GetType() const override {
        return "Circle"s;
    }

private:
    double _radius;
};

// Возвращает суммарную площадь фигур, указатели на которые находятся в переданной коллекции collection
template <typename ShapeCollection>
double CalcSumArea(const ShapeCollection& collection) {
    double area = 0.0;
    for (const auto& item : collection) {
        area += item->GetArea();
    }
    return area;
}

void PrintShapeInfo(const Shape& shape) {
    cout << shape.GetType() << ": color: "s << shape.GetColor() << ", area:"s << shape.GetArea() << endl;
}

int main() {
    Circle c{10.0, Color::RED};
    Rectangle r{10, 20, Color::BLUE};
    Shape sh{Color::GREEN};

    const Shape* shapes[] = {&c, &r, &sh};

    assert(sh.GetType() == "Shape"s);
    assert(c.GetType() == "Circle"s);
    assert(r.GetType() == "Rectangle"s);

    assert(sh.GetColor() == Color::GREEN);
    assert(c.GetColor() == Color::RED);
    assert(r.GetColor() == Color::BLUE);
    sh.SetColor(Color::BLUE);
    c.SetColor(Color::GREEN);
    r.SetColor(Color::RED);
    assert(sh.GetColor() == Color::BLUE);
    assert(c.GetColor() == Color::GREEN);
    assert(r.GetColor() == Color::RED);

    assert(std::abs(r.GetArea() - 200.0) < 1e-5);
    assert(std::abs(c.GetArea() - 314.15) < 1e-2);
    c.SetRadius(1.0);
    assert(std::abs(c.GetArea() - 3.1415) < 1e-4);
    r.SetSize(5, 7);
    assert(r.GetWidth() == 5);
    assert(r.GetHeight() == 7);
    assert(std::abs(r.GetArea() - 35.0) < 1e-5);

    assert(abs(CalcSumArea(shapes) - 38.1416) < 1e-4);

    for (const Shape* shape : shapes) {
        PrintShapeInfo(*shape);
    }
    cout << "Total area: " << CalcSumArea(shapes) << endl;
}