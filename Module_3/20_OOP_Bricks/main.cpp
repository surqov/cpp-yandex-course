#include <cassert>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class House {
 public:
    House() = default;

    House(const int length, const int width, const int height) 
    : _length(length)
    , _width(width)
    , _height(height) {
    }

    int GetLength() const {
        return _length;
    }

    int GetWidth() const {
        return _width;
    }

    int GetHeight() const {
        return _height;
    }

 private:
    int _length = 0;
    int _width = 0;
    int _height = 0;
};

class Resources {
  public:
    Resources() = default;

    Resources(const int brick_count) 
    : _brick_count(brick_count) {
    }

    void TakeBricks(const int count_) {
        if (GetBrickCount() < count_ || count_ < 0) {
            throw std::out_of_range("Wrong bricks count"s);
        }
        _brick_count -= count_;
    }

    int GetBrickCount() const {
        return _brick_count;
    }

  private:
    unsigned _brick_count = 0;
};

struct HouseSpecification {
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder {
  public:
    Builder(Resources& resources) 
    : _resources(&resources) {
    }

    House BuildHouse(const HouseSpecification& house_spec) {
        int needed_bricks = (house_spec.length + house_spec.width) * house_spec.height * 64;
        try {
            _resources->TakeBricks(needed_bricks);
        } catch (const std::out_of_range& m) {
            throw std::runtime_error(""s);
        }
        return House(house_spec.length, 
                house_spec.width,
                house_spec.height);
    }

  private:
    Resources* _resources;
};

int main() {
    Resources resources{10000};
    Builder builder1{resources};
    Builder builder2{resources};

    House house1 = builder1.BuildHouse(HouseSpecification{12, 9, 3});
    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{8, 6, 3});
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{4, 3, 2});
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;


    //5968 bricks left
    //3280 bricks left
    //2384 bricks left 
}