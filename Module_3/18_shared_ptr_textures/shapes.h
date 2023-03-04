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
        for (int i = 0; i < image.at(0).size(); ++i) {
            for (int j = 0; j < image.size(); ++j) {
                if ((type_ == ShapeType::RECTANGLE) || 
                    (type_ == ShapeType::ELLIPSE && IsPointInEllipse({i, j}, texture_->GetSize()))) {
                        image[i][j] = ? texture_->GetPixelColor({i % texture_->GetSize().width, 
                                                                j % texture_->GetSize().height}) : null_c;
                } 
            }
        }
    }
};