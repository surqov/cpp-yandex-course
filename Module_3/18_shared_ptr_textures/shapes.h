#pragma once
#include "texture.h"

#include <memory>

// Поддерживаемые виды фигур: прямоугольник и эллипс
enum class ShapeType { RECTANGLE, ELLIPSE};
char null_c = '.';

class Shape {
private:
Point pos_ = {0, 0};
Size size_ = {0, 0};
std::shared_ptr<Texture> texture_ = nullptr;
ShapeType type_;

public:
    // Фигура после создания имеет нулевые координаты и размер,
    // а также не имеет текстуры
    explicit Shape(ShapeType type)
        : type_(type) {    
    }

    void SetPosition(Point pos) {
        pos_ = pos;
    }

    void SetSize(Size size) {
        size_ = size;
    }

    void SetTexture(std::shared_ptr<Texture> texture) {
        texture_ = std::move(texture);
    }

    // Рисует фигуру на указанном изображении
	// В зависимости от типа фигуры должен рисоваться либо эллипс, либо прямоугольник
    // Пиксели фигуры, выходящие за пределы текстуры, а также в случае, когда текстура не задана,
    // должны отображаться с помощью символа точка '.'
    // Части фигуры, выходящие за границы объекта image, должны отбрасываться.
    void Draw(Image& image) const {
        int image_width = image.at(0).size();
        int image_height = image.size();
        for (int y = pos_.y, texture_y = 0; texture_y < size_.height; ++y, ++texture_y) {
            for (int x = pos_.x, texture_x = 0; texture_x < size_.width; ++x, ++texture_x) {
                if ((type_ == ShapeType::RECTANGLE) || 
                (type_ == ShapeType::ELLIPSE && IsPointInEllipse({texture_x, texture_y}, {size_.width, size_.height}))) {
                    image[y][x] = (x < image_width) && (y < image_height)
                                ? texture_->GetPixelColor({texture_x, texture_y})
                                : null_c;
                } 
            }
        }
    }
};