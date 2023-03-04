#pragma once
#include "common.h"
#include <stdexcept>

class Texture {
public:
    explicit Texture(Image image)
        : image_(std::move(image)) {
    }

    Size GetSize() const {
        return GetImageSize(image_);
    }

    char GetPixelColor(Point p) const {
        try {
            return image_.at(p.y).at(p.x);
        } catch (const std::out_of_range&) {
            return ' ';
        }
    }

private:
    Image image_;
};